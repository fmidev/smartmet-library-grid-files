#pragma once

#include "MapInfo.h"

#include <curl/curl.h>
#include <string>
#include <vector>
#include <map>


namespace SmartMet
{


class Client
{
  public:
                  Client();
    virtual       ~Client();

    virtual void  setAuthentication(uint authenticationMethod,const char *username,const char *password);
    virtual int   getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr);

    virtual bool  isActive();
    virtual void  setActive(bool active);

  protected:

    struct curl_slist* addAuthenticationHeaders(MapInfo& info,struct curl_slist *headerList);

    bool          mActive;
    uint          mAuthenticationMethod;
    std::string   mUsername;
    std::string   mPassword;


  public:

    class Response
    {
      public:
        char *data;
        uint dataSize;
        uint maxSize;
    };
};



size_t curl_responseProcessing(char *ptr, size_t size, size_t nmemb, void *userdata);
int    curl_trace(CURL *handle, curl_infotype type,char *data, size_t size,void *userp);

typedef Client* Client_ptr;
typedef std::vector<Client_ptr> Client_ptr_vec;

}
