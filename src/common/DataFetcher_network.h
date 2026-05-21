#pragma once

#include "DataFetcher.h"
#include "ThreadLock.h"
#include "Client.h"
#include "XmlElement.h"

namespace SmartMet
{

/*! \brief HTTP response buffer used by DataFetcher_network internals. */
struct Response
{
  char *data;    //!< Dynamically allocated response body
  uint dataSize; //!< Number of bytes currently in \p data
  uint maxSize;  //!< Allocated capacity of \p data
};

typedef std::map<std::string,Client_ptr_vec> Client_vecmap;




// ====================================================================================
/*! \brief DataFetcher implementation for HTTP and HTTPS (including S3) access.
 *
 *  Manages a pool of reusable `Client` connections, keyed by server address and
 *  protocol.  Handles THREDDS directory listings via XML parsing and S3 bucket
 *  listings via REST API. */
// ====================================================================================

class DataFetcher_network : public DataFetcher
{
  public:
                  DataFetcher_network();
    virtual       ~DataFetcher_network();

    //! \overload DataFetcher::getData()
    int           getData(uint serverType,uint protocol,const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr);
    //! \overload DataFetcher::getFileList()
    void          getFileList(uint serverType,uint protocol,const char *server,const char *dir,std::vector<std::string> &filePatterns,std::vector<FileRec>& fileList);
    //! \overload DataFetcher::getFileSize()
    Int64         getFileSize(uint serverType,uint protocol,const char *server,const char *filename);
    //! \overload DataFetcher::getFileHeaders()
    void          getFileHeaders(uint serverType,uint protocol,const char *server,const char *filename,std::map<std::string,std::string>& headers);

  protected:

    Client*       newClient(uint protocol);
    Client*       getClient(const char *serverAddress,uint serverType,uint protocol);
    bool          getFileList(uint protocol,const char *server,XmlElement& rootElement,std::vector<std::string> &filePatterns,std::vector<FileRec>& fileList,std::string& lastKey);
    void          getFileList_S3(uint protocol,const char *server,const char *dir,std::vector<std::string> &filePatterns,std::vector<FileRec>& fileList);

    ThreadLock    mThreadLock; //!< Guards the client pool
    Client_vecmap mClients;    //!< Reusable HTTP client pool keyed by server type

  public:

    /*! \brief Protocol constants used by this fetcher. */
    class Protocol
    {
      public:
        constexpr static const uint HTTP  = 1; //!< Plain HTTP
        constexpr static const uint HTTPS = 2; //!< TLS-encrypted HTTP
    };
};

}  // namespace SmartMet
