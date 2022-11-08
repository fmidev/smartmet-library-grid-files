#include "HttpClient.h"
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


HttpClient::HttpClient()
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




HttpClient::~HttpClient()
{
  if (curl != nullptr)
    curl_easy_cleanup(curl);
}





int HttpClient::getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr)
{
  try
  {
    if (!curl)
      return 0;

    // printf("*** SEND REQUEST %s  : %ld : %d\n",info.filename.c_str(),filePosition,dataSize);

    Response response;
    response.data = dataPtr;
    response.maxSize = dataSize;
    response.dataSize = 0;

    char url[1000];
    sprintf(url,"http://%s%s",info.server.c_str(),info.filename.c_str());
    //printf("URL [%s]\n",url);

    curl_easy_setopt(curl, CURLOPT_URL,url);
    curl_easy_setopt(curl, CURLOPT_PROXY,"");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,curl_responseProcessing);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

#ifdef CURL_DEBUG
    curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, curl_trace);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif

    struct curl_slist *headerList = NULL;

    char tmp[1000];
    sprintf(tmp,"Range: bytes=%ld-%ld",filePosition,filePosition+dataSize-1);
    headerList = curl_slist_append(headerList, tmp);

    headerList = addAuthenticationHeaders(info,headerList);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));

    curl_slist_free_all(headerList);

    return response.dataSize;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}

