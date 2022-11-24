#include "DataFetcher_filesys.h"
#include "GeneralFunctions.h"
#include "AutoThreadLock.h"
#include <macgyver/Exception.h>
#include <sys/stat.h>
#include <dirent.h>

namespace SmartMet
{

DataFetcher_filesys::DataFetcher_filesys()
{
  mLastChecked = time(0);
}




DataFetcher_filesys::~DataFetcher_filesys()
{
  for (auto it = mFileHandles.begin(); it != mFileHandles.end(); ++it)
  {
    fclose(it->second->fileHandle);
    delete it->second;
  }
}




void DataFetcher_filesys::checkFileHandles()
{
  try
  {
    SmartMet::AutoThreadLock lock(&mThreadLock);
    if ((time(0) - mLastChecked) > 3600)
    {
      std::vector<std::string> deleteList;
      time_t old = time(0) - 3600;
      for (auto it = mFileHandles.begin(); it != mFileHandles.end(); ++it)
      {
        if (it->second->lastUsed < old)
        {
          deleteList.push_back(it->first);
        }
      }

      for (auto it = deleteList.begin(); it != deleteList.end(); ++it)
      {
        auto itm = mFileHandles.find(*it);
        if (itm != mFileHandles.end())
        {
          fclose(itm->second->fileHandle);
          delete itm->second;
          mFileHandles.erase(itm);
        }
      }

      mLastChecked = time(0);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




FileHandle* DataFetcher_filesys::getFileHandle(const char *filename)
{
  try
  {
    time_t currentTime = time(0);

    if ((currentTime - mLastChecked) > 3600)
      checkFileHandles();

    auto fh = mFileHandles.find(filename);
    if (fh != mFileHandles.end())
    {
      fh->second->lastUsed = currentTime;
      return fh->second;
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
  try
  {
    FileHandle *fh = getFileHandle(filename);
    if (!fh || !fh->fileHandle)
    {
      Fmi::Exception exception(BCP,"Cannot get the file handle!");
      exception.addParameter("filename",filename);
      throw exception;
    }

    AutoThreadLock tlock(&fh->threadLock);

    fseek(fh->fileHandle,filePosition,SEEK_SET);
    return fread(dataPtr,1,dataSize,fh->fileHandle);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void DataFetcher_filesys::getFileList(const char *dirName,std::vector<std::string> &filePatterns,std::set<std::string> &dirList,std::vector<FileRec>& fileList)
{
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
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}  // namespace SmartMet
