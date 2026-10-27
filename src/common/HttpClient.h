#pragma once

#include "Client.h"


namespace SmartMet
{


// ====================================================================================
/*! \brief Client implementation for plain HTTP using libcurl. */
// ====================================================================================

class HttpClient : public Client
{
  public:
              HttpClient();
    ~HttpClient() override;
    HttpClient(const HttpClient&) = delete;
    HttpClient& operator=(const HttpClient&) = delete;

    //! \overload Client::getData()
    int       getData(const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr) override;
    //! \overload Client::getHeaderData()
    int       getHeaderData(const char *server,const char *filename,int dataSize,char *dataPtr) override;

  protected:

    CURL*     curl; //!< libcurl easy handle
};

using HttpClient_ptr = HttpClient*;
using HttpClient_ptr_vec = std::vector<HttpClient_ptr>;

}
