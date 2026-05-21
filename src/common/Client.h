#pragma once

#include "MapInfo.h"

#include <curl/curl.h>
#include <string>
#include <vector>
#include <map>


namespace SmartMet
{


// ====================================================================================
/*! \brief Abstract base class for HTTP/HTTPS data fetching via libcurl.
 *
 *  Concrete subclasses (`HttpClient`, `HttpsClient`) wrap a `CURL*` handle for
 *  a single server connection.  The pool in `DataFetcher_network` recycles idle
 *  clients to avoid connection setup overhead on repeated page fetches. */
// ====================================================================================

class Client
{
  public:
                  Client();
    virtual       ~Client();

    /*! \brief Fetch a byte range from a file on the server.
     *  \param[in]  server        Hostname or URL.
     *  \param[in]  filename      File path on the server.
     *  \param[in]  filePosition  Byte offset to start reading from.
     *  \param[in]  dataSize      Number of bytes to fetch.
     *  \param[out] dataPtr       Caller-allocated destination buffer.
     *  \return Number of bytes received, or a negative error code. */
    virtual int   getData(const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr);

    /*! \brief Fetch HTTP response headers for a file.
     *  \param[in]  server    Hostname or URL.
     *  \param[in]  filename  File path.
     *  \param[in]  dataSize  Maximum number of header bytes to receive.
     *  \param[out] dataPtr   Destination buffer.
     *  \return Number of bytes received. */
    virtual int   getHeaderData(const char *server,const char *filename,int dataSize,char *dataPtr);

    /*! \brief Return true if this client is not currently in use. */
    virtual bool  isActive();

    /*! \brief Mark this client as active (in use) or idle.
     *  \param[in] active  True while the client is being used. */
    virtual void  setActive(bool active);

    /*! \brief Enable or disable libcurl verbose tracing.
     *  \param[in] enabled  True to enable debug output. */
    virtual void  setDebugEnabled(bool enabled);

    /*! \brief Configure authentication credentials.
     *  \param[in] authenticationMethod  Method code (0 = none).
     *  \param[in] username              Login name.
     *  \param[in] password              Password or token. */
    virtual void  setAuthentication(uint authenticationMethod,const char *username,const char *password);

  protected:

    struct curl_slist* addAuthenticationHeaders(const char *server,const char *filename,struct curl_slist *headerList);

    bool          mActive;               //!< True while this client is in use
    bool          mDebugEnabled;         //!< True when libcurl verbose tracing is on
    uint          mAuthenticationMethod; //!< Authentication method code
    std::string   mUsername;             //!< Login name
    std::string   mPassword;             //!< Password or token


  public:

    /*! \brief libcurl response accumulation buffer. */
    class Response
    {
      public:
        char *data;    //!< Dynamically grown receive buffer
        uint dataSize; //!< Bytes currently written into data
        uint maxSize;  //!< Allocated capacity of data
    };
};


/*! \brief libcurl write callback that appends received bytes to a Response buffer. */
size_t curl_responseProcessing(char *ptr, size_t size, size_t nmemb, void *userdata);
/*! \brief libcurl debug callback that prints protocol trace to stderr. */
int    curl_trace(CURL *handle, curl_infotype type,char *data, size_t size,void *userp);

typedef Client* Client_ptr;
typedef std::vector<Client_ptr> Client_ptr_vec;

}
