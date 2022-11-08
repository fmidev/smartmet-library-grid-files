#pragma once

#include "Client.h"


namespace SmartMet
{


class HttpClient : public Client
{
  public:
              HttpClient();
    virtual   ~HttpClient();

    int       getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr);

  protected:

    CURL*     curl;

};

typedef HttpClient* HttpClient_ptr;
typedef std::vector<HttpClient_ptr> HttpClient_ptr_vec;

}
