#pragma once

#include "Client.h"


namespace SmartMet
{


// ====================================================================================
/*! \brief Client implementation for HTTPS (TLS) using libcurl. */
// ====================================================================================

class HttpsClient : public Client
{
  public:
              HttpsClient();
    ~HttpsClient() override;
    HttpsClient(const HttpsClient&) = delete;
    HttpsClient& operator=(const HttpsClient&) = delete;

    //! \overload Client::getData()
    int       getData(const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr) override;
    //! \overload Client::getHeaderData()
    int       getHeaderData(const char *server,const char *filename,int dataSize,char *dataPtr) override;

  protected:

    CURL*     curl; //!< libcurl easy handle (TLS-enabled)
};

using HttpsClient_ptr = HttpsClient*;
using HttpsClient_ptr_vec = std::vector<HttpsClient_ptr>;

}
