#include "DataFetcher_filesys.h"
#include "AutoThreadLock.h"
#include <macgyver/Exception.h>

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





int DataFetcher_filesys::getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr)
{
  try
  {
    FileHandle *fh = getFileHandle(info.filename.c_str());
    if (!fh || !fh->fileHandle)
    {
      Fmi::Exception exception(BCP,"Cannot get the file handle!");
      exception.addParameter("filename",info.filename);
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




}  // namespace SmartMet
