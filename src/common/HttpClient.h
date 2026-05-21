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
    virtual   ~HttpClient();

    //! \overload Client::getData()
    int       getData(const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr);
    //! \overload Client::getHeaderData()
    int       getHeaderData(const char *server,const char *filename,int dataSize,char *dataPtr);

  protected:

    CURL*     curl; //!< libcurl easy handle
};

typedef HttpClient* HttpClient_ptr;
typedef std::vector<HttpClient_ptr> HttpClient_ptr_vec;

}
