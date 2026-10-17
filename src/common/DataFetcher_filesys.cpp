#include "DataFetcher_filesys.h"
#include "GeneralFunctions.h"
#include "AutoThreadLock.h"
#include "AutoWriteLock.h"
#include "AutoReadLock.h"
#include "ShowFunction.h"
#include <macgyver/Exception.h>
#include <cstring>
#include <sys/stat.h>
#include <dirent.h>

#define FUNCTION_TRACE FUNCTION_TRACE_OFF



namespace SmartMet
{

#define CHECK_INTERVAL 120


/*! \brief Default constructor for DataFetcher_filesys. */

DataFetcher_filesys::DataFetcher_filesys()
{
  FUNCTION_TRACE
  mLastChecked = time(nullptr);
  mFileHandleLimit = 10000;
}




/*! \brief Destructor that closes any open file handles. */

DataFetcher_filesys::~DataFetcher_filesys()
{
  FUNCTION_TRACE
  for (auto& mFileHandle : mFileHandles)
  {
    if (mFileHandle.second->fileHandle)
      (void)fclose(mFileHandle.second->fileHandle);

    delete mFileHandle.second;
  }
}



/*! \brief Sets the maximum number of cached open file handles. */

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




/*! \brief Closes and removes stale or excess cached file handles. */

void DataFetcher_filesys::checkFileHandles()
{
  FUNCTION_TRACE
  try
  {
    time_t interv = (time(nullptr) - mLastChecked);
    if (interv > CHECK_INTERVAL || (mFileHandles.size() > mFileHandleLimit  && interv > 30))
    {
      //printf("CHECK FILES %ld\n",mFileHandles.size());
      std::vector<std::string> deleteList;
      mLastChecked = time(nullptr);
      time_t deleteLimit = mLastChecked - 600;
      if (mFileHandles.size() > mFileHandleLimit)
        deleteLimit = mLastChecked - 30;

      for (auto& mFileHandle : mFileHandles)
      {
        if (mFileHandle.second->lastUsed < deleteLimit)
        {
          if (mFileHandle.second->threadLock.tryLock())
          {
            (void)fclose(mFileHandle.second->fileHandle);  // read-only cache handle
            mFileHandle.second->fileHandle = nullptr;
            deleteList.push_back(mFileHandle.first);
            mFileHandle.second->threadLock.unlock();
          }
        }
      }

      for (auto& it : deleteList)
      {
        auto itm = mFileHandles.find(it);
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




/*! \brief Returns an open file handle for the file, opening it if necessary. */

FileHandle* DataFetcher_filesys::getFileHandle(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    time_t currentTime = time(nullptr);

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

    AutoWriteLock lock(&mModificationLock);

    time_t interv = (time(nullptr) - mLastChecked);
    if (interv > CHECK_INTERVAL || (mFileHandles.size() > mFileHandleLimit  && interv > 30))
      checkFileHandles();

    auto fh = mFileHandles.find(filename);
    if (fh != mFileHandles.end())
    {
      if (fh->second->fileHandle)
      {
        fh->second->lastUsed = currentTime;
        return fh->second;
      }
    }

    auto *f = new FileHandle;
    f->fileHandle = fopen(filename,"r");
    if (f->fileHandle != nullptr)
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





/*! \brief Reads a range of bytes from a local file into the given buffer. */

int DataFetcher_filesys::getData(uint /*serverType*/,uint /*protocol*/,const char * /*server*/,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr)
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
        if (fseek(fh->fileHandle,filePosition,SEEK_SET) != 0)
          return 0;

        int n = fread(dataPtr,1,dataSize,fh->fileHandle);
        if (n < dataSize)
        {
          if (feof(fh->fileHandle))
          {
            // We have reached the end of the file. The rest of the page must not contain
            // stale data from earlier use of the buffer.
            memset(dataPtr + n, 0, dataSize - n);
            return dataSize;
          }
          printf("### WARNING: Cannot read all requested data (%s) filepos = %zu  %d/%d\n",filename,filePosition,n,dataSize);
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




namespace
{
/*! \brief The type of a directory entry. */

enum class EntryType
{
  Directory,
  File,
  Other
};



/*! \brief Checks if the entry is "." or "..". */

bool isDotEntry(const struct dirent *ep)
{
  return (strcmp(ep->d_name, "..") == 0  ||  strcmp(ep->d_name, ".") == 0);
}



/*! \brief Classifies the directory entry. The file status is read into s unless the entry
    is known to be a directory. */

EntryType classifyEntry(const struct dirent *ep,const char *fullName,struct stat& s)
{
  if (ep->d_type == DT_DIR && !isDotEntry(ep))
    return EntryType::Directory;

  if (stat(fullName, &s) != 0)
    return EntryType::Other;

  if (ep->d_type == DT_REG || ep->d_type == DT_LNK)
    return EntryType::File;

  if (ep->d_type != DT_UNKNOWN)
    return EntryType::Other;

  if ((s.st_mode & S_IFDIR) != 0 && !isDotEntry(ep))
    return EntryType::Directory;

  if ((s.st_mode & S_IFREG)  || (s.st_mode & S_IFLNK))
    return EntryType::File;

  return EntryType::Other;
}



/*! \brief Adds the file into the file list. */

void addFileRecord(const char *fullName,const struct stat& s,std::vector<DataFetcher::FileRec>& fileList)
{
  DataFetcher::FileRec rec;
  rec.filename = fullName;
  rec.size = s.st_size;
  rec.lastModified = s.st_mtime;
  rec.serverType = DataFetcher::ServerType::Filesys;
  rec.protocol = 0;
  fileList.emplace_back(rec);
}
}  // namespace





/*! \brief Recursively lists matching files under a directory into the given vector. */

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

        struct stat s{};
        EntryType type = classifyEntry(ep,fullName,s);

        if (type == EntryType::Directory)
        {
          getFileList(fullName,filePatterns, dirList, fileList);
        }
        else if (type == EntryType::File  &&  (filePatterns.empty() || patternMatch(fullName,filePatterns)))
        {
          addFileRecord(fullName,s,fileList);
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



/*! \brief Lists files matching the given patterns under the given directory. */

void DataFetcher_filesys::getFileList(uint /*serverType*/,uint /*protocol*/,const char * /*server*/,const char *dir,std::vector<std::string> &filePatterns,std::vector<FileRec>& fileList)
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



/*! \brief Returns the size of the given local file, or -1 on error. */

Int64 DataFetcher_filesys::getFileSize(uint /*serverType*/,uint /*protocol*/,const char * /*server*/,const char *filename)
{
  FUNCTION_TRACE
  try
  {
    struct stat buf{};
    if (stat(filename, &buf) == 0)
      return (Int64)buf.st_size;

    return -1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



/*! \brief No-op file headers retrieval for local files. */

void DataFetcher_filesys::getFileHeaders(uint /*serverType*/,uint /*protocol*/,const char * /*server*/,const char * /*filename*/,std::map<std::string,std::string>& /*headers*/)
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
