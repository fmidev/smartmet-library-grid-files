#pragma once

#include "Client.h"


namespace SmartMet
{


class HttpClient : public Client
{
  public:
              HttpClient();
    virtual   ~HttpClient();

    int       getData(const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr);
    int       getHeaderData(const char *server,const char *filename,int dataSize,char *dataPtr);

  protected:

    CURL*     curl;

};

typedef HttpClient* HttpClient_ptr;
typedef std::vector<HttpClient_ptr> HttpClient_ptr_vec;

}
