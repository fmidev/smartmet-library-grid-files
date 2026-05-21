#pragma once

#include <memory>
#include <map>
#include <string>
#include <vector>

#include "Typedefs.h"

namespace SmartMet
{

// ====================================================================================
/*! \brief Abstract base class for fetching raw byte ranges from local or remote files.
 *
 *  Concrete subclasses provide filesystem access (`DataFetcher_filesys`) and
 *  HTTP/S3 access (`DataFetcher_network`).  The `MemoryMapper` selects the
 *  appropriate fetcher based on the server type encoded in a `MapInfo`. */
// ====================================================================================

class DataFetcher
{
  public:

    /*! \brief Metadata record for a single file returned by getFileList(). */
    class FileRec
    {
      public:
        uint        serverType;   //!< Server type (see DataFetcher::ServerType)
        uint        protocol;     //!< Protocol (see MapInfo::Protocol)
        std::string server;       //!< Server hostname or URL
        std::string filename;     //!< File path relative to the server
        time_t      lastModified; //!< Last-modified timestamp
        std::size_t size;         //!< File size in bytes
    };

    /*! \brief Server category constants (mirrors MapInfo::ServerType). */
    class ServerType
    {
    public:
      enum
      {
        Unknown  = 0, //!< Unknown
        Filesys  = 1, //!< Local filesystem
        S3       = 2, //!< Amazon S3 or compatible
        THREDDS  = 3, //!< THREDDS Data Server
        HTTPD    = 4  //!< Generic HTTP server
      };
    };

    /*! \brief Credentials for authenticating to a server. */
    class AccessInfo
    {
      public:
        uint authenticationMethod = 0; //!< Authentication method code (0 = none)
        std::string username;          //!< Login name
        std::string password;          //!< Password or token
    };

    typedef std::map<std::string,AccessInfo> AccessMap; //!< Per-server credential map

  public:
                        DataFetcher();
    virtual             ~DataFetcher();

    /*! \brief Register credentials for a server.
     *  \param[in] server                 Hostname or URL prefix to match.
     *  \param[in] authenticationMethod   Method code.
     *  \param[in] username               Login name.
     *  \param[in] password               Password or token. */
    virtual void        addAccessInfo(const char *server,uint authenticationMethod,const char *username,const char *password);

    /*! \brief Look up credentials for \p server.
     *  \param[in] server  Hostname or URL.
     *  \return Pointer to the matching AccessInfo, or nullptr. */
    virtual AccessInfo* getAccessInfo(const char *server);

    /*! \brief Fetch a byte range from a file.
     *  \param[in]  serverType    Server category constant.
     *  \param[in]  protocol      Protocol constant.
     *  \param[in]  server        Server hostname or URL.
     *  \param[in]  filename      File path on the server.
     *  \param[in]  filePosition  Byte offset to start reading from.
     *  \param[in]  dataSize      Number of bytes to read.
     *  \param[out] dataPtr       Caller-allocated destination buffer.
     *  \return Number of bytes fetched, or a negative error code. */
    virtual int         getData(uint serverType,uint protocol,const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr);

    /*! \brief List files in a directory matching given patterns.
     *  \param[in]  serverType    Server category.
     *  \param[in]  protocol      Protocol.
     *  \param[in]  server        Server hostname or URL.
     *  \param[in]  dir           Directory path.
     *  \param[in]  filePatterns  Glob patterns to match.
     *  \param[out] fileList      Receives matching FileRec entries. */
    virtual void        getFileList(uint serverType,uint protocol,const char *server,const char *dir,std::vector<std::string> &filePatterns,std::vector<FileRec>& fileList);

    /*! \brief Return the size of a file.
     *  \param[in] serverType  Server category.
     *  \param[in] protocol    Protocol.
     *  \param[in] server      Server hostname or URL.
     *  \param[in] filename    File path.
     *  \return File size in bytes, or a negative error code. */
    virtual Int64       getFileSize(uint serverType,uint protocol,const char *server,const char *filename);

    /*! \brief Retrieve HTTP response headers for a file.
     *  \param[in]  serverType  Server category.
     *  \param[in]  protocol    Protocol.
     *  \param[in]  server      Server hostname or URL.
     *  \param[in]  filename    File path.
     *  \param[out] headers     Receives header name → value pairs. */
    virtual void        getFileHeaders(uint serverType,uint protocol,const char *server,const char *filename,std::map<std::string,std::string>& headers);

    /*! \brief Enable or disable verbose debug logging.
     *  \param[in] enabled  True to enable debug output. */
    virtual void        setDebugEnabled(bool enabled);

    /*! \brief Load credentials from a file and merge into mAccessMap.
     *  \param[in] filename  Path to the credentials file. */
    virtual void        setAccessFile(const char *filename);

    /*! \brief Load a credentials file into \p mAccessMap.
     *  \param[in]     filename    Path to the credentials file.
     *  \param[in,out] mAccessMap  Credentials map to populate. */
    static void         loadAccessFile(const char *filename,AccessMap& mAccessMap);

    /*! \brief Parse a URL into its component parts.
     *  \param[in]  urlStr    Full URL string.
     *  \param[out] protocol  Protocol code.
     *  \param[out] server    Hostname extracted from the URL.
     *  \param[out] filename  Path extracted from the URL. */
    static void         splitUrl(const char *urlStr,uint& protocol,std::string& server,std::string& filename);

    /*! \brief Parse HTTP response headers from a raw buffer.
     *  \param[in]  data      Buffer containing the raw HTTP headers.
     *  \param[in]  dataSize  Size of \p data in bytes.
     *  \param[out] headers   Receives header name → value pairs. */
    static void         parseHeaders(char *data,int dataSize,std::map<std::string,std::string>& headers);


  protected:

    bool                mDebugEnabled; //!< True when debug logging is active
    AccessMap           mAccessMap;    //!< Per-server authentication credentials
};

typedef std::shared_ptr<DataFetcher> DataFetcher_sptr;
typedef std::map<uint,DataFetcher_sptr> DataFetcher_sptr_map;

}  // namespace SmartMet
