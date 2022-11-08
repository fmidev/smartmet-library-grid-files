#pragma once

#include "Client.h"


namespace SmartMet
{


class HttpsClient : public Client
{
  public:
              HttpsClient();
    virtual   ~HttpsClient();

    int       getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr);

  protected:

    CURL*     curl;
};

typedef HttpsClient* HttpsClient_ptr;
typedef std::vector<HttpsClient_ptr> HttpsClient_ptr_vec;

}
