#pragma once

#include "DataFetcher.h"
#include "AutoThreadLock.h"
#include <vector>
#include <set>

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

    int           getData(uint serverType,uint protocol,const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr);
    void          getFileList(uint serverType,uint protocol,const char *server,const char *dir,std::vector<std::string> &filePatterns,std::vector<FileRec>& fileList);
    long long     getFileSize(uint serverType,uint protocol,const char *server,const char *filename);
    void          getFileHeaders(uint serverType,uint protocol,const char *server,const char *filename,std::map<std::string,std::string>& headers);

  protected:

    void          checkFileHandles();
    FileHandle*   getFileHandle(const char *filename);
    void          getFileList(const char *dirName,std::vector<std::string> &filePatterns,std::set<std::string> &dirList,std::vector<FileRec>& fileList);

    ThreadLock    mThreadLock;
    time_t        mLastChecked;

    std::map<std::string,FileHandle*> mFileHandles;
};

}  // namespace SmartMet
