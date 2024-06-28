#include "DataFetcher_filesys.h"
#include "GeneralFunctions.h"
#include "AutoThreadLock.h"
#include "AutoWriteLock.h"
#include "AutoReadLock.h"
#include "ShowFunction.h"
#include <macgyver/Exception.h>
#include <sys/stat.h>
#include <dirent.h>

#define FUNCTION_TRACE FUNCTION_TRACE_OFF



namespace SmartMet
{

#define CHECK_INTERVAL 120


DataFetcher_filesys::DataFetcher_filesys()
{
  FUNCTION_TRACE
  mLastChecked = time(0);
  mFileHandleLimit = 10000;
}




DataFetcher_filesys::~DataFetcher_filesys()
{
  FUNCTION_TRACE
  for (auto it = mFileHandles.begin(); it != mFileHandles.end(); ++it)
  {
    if (it->second->fileHandle)
      fclose(it->second->fileHandle);

    delete it->second;
  }
}



void DataFetcher_filesys::setFileHandleLimit(std::size_t fileHandleLimit)
{
  FUNCTION_TRACE
  try
  {
    mFileHandleLimit = fileHandleLimit;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void DataFetcher_filesys::checkFileHandles()
{
  FUNCTION_TRACE
  try
  {
    time_t interv = (time(0) - mLastChecked);
    if (interv > CHECK_INTERVAL || (mFileHandles.size() > mFileHandleLimit  && interv > 30))
    {
      //printf("CHECK FILES %ld\n",mFileHandles.size());
      std::vector<std::string> deleteList;
      mLastChecked = time(0);
      time_t deleteLimit = mLastChecked - 600;
      if (mFileHandles.size() > mFileHandleLimit)
        deleteLimit = mLastChecked - 30;

      for (auto it = mFileHandles.begin(); it != mFileHandles.end(); ++it)
      {
        if (it->second->lastUsed < deleteLimit)
        {
          if (it->second->threadLock.tryLock())
          {
            fclose(it->second->fileHandle);
            it->second->fileHandle = NULL;
            deleteList.push_back(it->first);
            it->second->threadLock.unlock();
          }
        }
      }

      for (auto it = deleteList.begin(); it != deleteList.end(); ++it)
      {
        auto itm = mFileHandles.find(*it);
        if (itm != mFileHandles.end())
        {
          delete itm->second;
          mFileHandles.erase(itm);
        }
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




FileHandle* DataFetcher_filesys::getFileHandle(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    time_t currentTime = time(0);

    {
      AutoReadLock lock(&mModificationLock);
      auto fh = mFileHandles.find(filename);
      if (fh != mFileHandles.end())
      {
        if (fh->second->fileHandle)
        {
          fh->second->lastUsed = currentTime;
          return fh->second;
        }
      }
    }

    time_t interv = (time(0) - mLastChecked);

    if (interv > CHECK_INTERVAL || (mFileHandles.size() > mFileHandleLimit  && interv > 30))
    {
      AutoWriteLock lock(&mModificationLock);
      checkFileHandles();
    }

    AutoWriteLock lock(&mModificationLock);
    auto fh = mFileHandles.find(filename);
    if (fh != mFileHandles.end())
    {
      if (fh->second->fileHandle)
      {
        fh->second->lastUsed = currentTime;
        return fh->second;
      }
    }

    FileHandle *f = new FileHandle;
    f->fileHandle = fopen(filename,"r");
    if (f->fileHandle != NULL)
    {
      f->lastUsed = currentTime;
      mFileHandles.insert(std::pair<std::string,FileHandle*>(filename,f));
      return f;
    }
    delete f;
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





int DataFetcher_filesys::getData(uint serverType,uint protocol,const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr)
{
  FUNCTION_TRACE
  try
  {
    for (uint t=0; t<5; t++)
    {
      FileHandle *fh = getFileHandle(filename);
      if (!fh || !fh->fileHandle)
      {
        Fmi::Exception exception(BCP,"Cannot get the file handle!");
        exception.addParameter("filename",filename);
        throw exception;
      }

      AutoThreadLock lock(&fh->threadLock);
      if (fh->fileHandle)
      {
        fseek(fh->fileHandle,filePosition,SEEK_SET);
        int n = fread(dataPtr,1,dataSize,fh->fileHandle);
        if (n < dataSize)
        {
          if (feof(fh->fileHandle))
          {
            // We have reached the ene of the file
            return dataSize;
          }
          else
          {
            printf("### WARNING: Cannot read all requested data (%s) filepos = %ld  %d/%d\n",filename,filePosition,n,dataSize);
          }
        }

        return n;
      }

      // We got file handle, but it was closed. Let's try again.
      time_usleep(0,10000);
    }

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void DataFetcher_filesys::getFileList(const char *dirName,std::vector<std::string> &filePatterns,std::set<std::string> &dirList,std::vector<FileRec>& fileList)
{
  FUNCTION_TRACE
  try
  {
    char *path = realpath(dirName, nullptr);
    if (path == nullptr)
    {
      return;
    }

    if (dirList.find(path) != dirList.end())
      return;  // Dir already processed

    DIR *dp = opendir(dirName);
    if (dp == nullptr)
    {
      return;
    }

    dirList.insert(std::string(dirName));

    bool ind = true;

    while (ind)
    {
      struct dirent *ep = readdir(dp);
      if (ep != nullptr)
      {
        char fullName[2000];
        sprintf(fullName, "%s/%s", path, ep->d_name);

        if (ep->d_type == DT_DIR && strcmp(ep->d_name, "..") != 0 &&
            strcmp(ep->d_name, ".") != 0)
        {
          getFileList(fullName,filePatterns, dirList, fileList);
        }
        else
        {
          struct stat s;
          if (stat(fullName, &s) == 0)
          {
            if (ep->d_type == DT_REG)
            {
              if (filePatterns.size() == 0 || patternMatch(fullName,filePatterns))
              {
                FileRec rec;
                rec.filename = fullName;
                rec.size = s.st_size;
                rec.lastModified = s.st_mtime;
                rec.serverType = ServerType::Filesys;
                rec.protocol = 0;
                fileList.emplace_back(rec);
              }
            }
            else if (ep->d_type == DT_UNKNOWN)
            {
              if ((s.st_mode & S_IFDIR) != 0 && strcmp(ep->d_name, "..") != 0 &&  strcmp(ep->d_name, ".") != 0)
              {
                getFileList(fullName, filePatterns, dirList, fileList);
              }
              else if (s.st_mode & S_IFREG)
              {
                if (filePatterns.size() == 0 || patternMatch(fullName,filePatterns))
                {
                  FileRec rec;
                  rec.filename = fullName;
                  rec.size = s.st_size;
                  rec.lastModified = s.st_mtime;
                  rec.serverType = ServerType::Filesys;
                  rec.protocol = 0;
                  fileList.emplace_back(rec);
                }
              }
            }
          }
        }
      }
      else
      {
        ind = false;
      }
    }
    closedir(dp);
    free(path);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void DataFetcher_filesys::getFileList(uint serverType,uint protocol,const char *server,const char *dir,std::vector<std::string> &filePatterns,std::vector<FileRec>& fileList)
{
  FUNCTION_TRACE
  try
  {
    std::set<std::string> dirList;
    getFileList(dir,filePatterns,dirList,fileList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



long long DataFetcher_filesys::getFileSize(uint serverType,uint protocol,const char *server,const char *filename)
{
  FUNCTION_TRACE
  try
  {
    struct stat buf;
    if (stat(filename, &buf) == 0)
      return (long long)buf.st_size;

    return -1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void DataFetcher_filesys::getFileHeaders(uint serverType,uint protocol,const char *server,const char *filename,std::map<std::string,std::string>& headers)
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}  // namespace SmartMet
