#pragma once

#include "DataFetcher.h"

namespace SmartMet
{

struct FileHandle
{
  FILE *fileHandle;
  SmartMet::ThreadLock threadLock;
  time_t lastUsed;
};


class DataFetcher_filesys : public DataFetcher
{
  public:
                  DataFetcher_filesys();
    virtual       ~DataFetcher_filesys();

    virtual int   getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr);

  protected:

    void          checkFileHandles();
    FileHandle*   getFileHandle(const char *filename);

    ThreadLock    mThreadLock;
    time_t        mLastChecked;

    std::map<std::string,FileHandle*> mFileHandles;
};

}  // namespace SmartMet
