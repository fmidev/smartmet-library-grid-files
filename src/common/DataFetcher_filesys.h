#pragma once

#include "DataFetcher.h"
#include "ThreadLock.h"
#include "ModificationLock.h"
#include <vector>
#include <set>

namespace SmartMet
{

/*! \brief A cached stdio file handle with an associated lock and last-use timestamp. */
struct FileHandle
{
  FILE *fileHandle;                 //!< Open file handle
  SmartMet::ThreadLock threadLock;  //!< Per-handle mutex (prevents concurrent seeks)
  time_t lastUsed;                  //!< Unix timestamp of the last access (for LRU eviction)
};




// ====================================================================================
/*! \brief DataFetcher implementation for local filesystem access.
 *
 *  Maintains a pool of open `FILE*` handles (up to `fileHandleLimit`) to avoid
 *  the overhead of repeated `fopen`/`fclose` for memory-mapped page fetches. */
// ====================================================================================

class DataFetcher_filesys : public DataFetcher
{
  public:
                      DataFetcher_filesys();
    virtual           ~DataFetcher_filesys();

    //! \overload DataFetcher::getData()
    int               getData(uint serverType,uint protocol,const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr);
    //! \overload DataFetcher::getFileList()
    void              getFileList(uint serverType,uint protocol,const char *server,const char *dir,std::vector<std::string> &filePatterns,std::vector<FileRec>& fileList);
    //! \overload DataFetcher::getFileSize()
    Int64             getFileSize(uint serverType,uint protocol,const char *server,const char *filename);
    //! \overload DataFetcher::getFileHeaders()
    void              getFileHeaders(uint serverType,uint protocol,const char *server,const char *filename,std::map<std::string,std::string>& headers);

    /*! \brief Set the maximum number of simultaneously open file handles.
     *  \param[in] fileHandleLimit  Maximum handle pool size. */
    void              setFileHandleLimit(std::size_t fileHandleLimit);

  protected:

    void              checkFileHandles();
    FileHandle*       getFileHandle(const char *filename);
    void              getFileList(const char *dirName,std::vector<std::string> &filePatterns,std::set<std::string> &dirList,std::vector<FileRec>& fileList);

    ModificationLock  mModificationLock;  //!< Guards mFileHandles
    time_t            mLastChecked;       //!< Last handle-pool cleanup timestamp
    std::size_t       mFileHandleLimit;   //!< Maximum number of open handles

    std::map<std::string,FileHandle*> mFileHandles; //!< Open handle pool keyed by file path
};

}  // namespace SmartMet
