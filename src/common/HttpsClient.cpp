#include "HttpsClient.h"
#include "GeneralFunctions.h"
#include <macgyver/Exception.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


namespace SmartMet
{


HttpsClient::HttpsClient()
{
  try
  {
    mActive = false;
    curl = curl_easy_init();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




HttpsClient::~HttpsClient()
{
  if (curl != nullptr)
    curl_easy_cleanup(curl);
}





size_t HttpsClient_responseProcessing(char *ptr, size_t size, size_t nmemb, void *userdata)
{
  try
  {
    //printf("RECEIVE %ld\n",nmemb);
    HttpsClient::Response *response = (HttpsClient::Response*)userdata;

    for (size_t t=0; t<nmemb; t++)
    {
      char ch = ptr[t];
      if (response->dataSize < response->maxSize)
      {
        response->data[response->dataSize] = ch;
        response->dataSize++;
      }
    }
    return nmemb;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





int HttpsClient::getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr)
{
  try
  {
    if (!curl)
      return 0;

    // printf("*** SEND REQUEST %s  : %ld : %d\n",info.filename.c_str(),filePosition,dataSize);

    info.port = 443;

    char tmp[1000];
    sprintf(tmp,"https://%s:%u%s",info.server.c_str(),info.port,info.filename.c_str());
    //printf("SEND [%s]\n",tmp);

    Response response;
    response.data = dataPtr;
    response.maxSize = dataSize;
    response.dataSize = 0;

    curl_easy_setopt(curl,CURLOPT_PROXY,"");
    curl_easy_setopt(curl, CURLOPT_URL,tmp);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,HttpsClient_responseProcessing);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    struct curl_slist *list = NULL;
    sprintf(tmp,"Range: bytes=%ld-%ld\r\n",filePosition,filePosition+dataSize-1);
    list = curl_slist_append(list, tmp);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);


    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));

    curl_slist_free_all(list);

    return response.dataSize;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}

