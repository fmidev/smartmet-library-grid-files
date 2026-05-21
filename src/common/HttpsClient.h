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
    virtual   ~HttpsClient();

    //! \overload Client::getData()
    int       getData(const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr);
    //! \overload Client::getHeaderData()
    int       getHeaderData(const char *server,const char *filename,int dataSize,char *dataPtr);

  protected:

    CURL*     curl; //!< libcurl easy handle (TLS-enabled)
};

typedef HttpsClient* HttpsClient_ptr;
typedef std::vector<HttpsClient_ptr> HttpsClient_ptr_vec;

}
