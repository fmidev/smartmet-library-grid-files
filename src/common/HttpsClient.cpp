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

#include "ShowFunction.h"
#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{


HttpsClient::HttpsClient()
{
  FUNCTION_TRACE
  try
  {
    mActive = false;
    curl = curl_easy_init();
    mDebugEnabled = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




HttpsClient::~HttpsClient()
{
  FUNCTION_TRACE
  if (curl != nullptr)
    curl_easy_cleanup(curl);
}





int HttpsClient::getHeaderData(const char *server,const char *filename,int dataSize,char *dataPtr)
{
  FUNCTION_TRACE
  try
  {
    if (!curl)
      return 0;

    //printf("*** SEND HEADER REQUEST %s  : %ld : %ld\n",filename,dataSize,dataPtr);
    Response response;
    response.data = dataPtr;
    response.maxSize = dataSize;
    response.dataSize = 0;

    char url[1000];
    sprintf(url,"https://%s%s",server,filename);
    //printf("URL [%s]\n",url);

    curl_easy_setopt(curl, CURLOPT_URL,url);
    curl_easy_setopt(curl, CURLOPT_PROXY,"");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,curl_responseProcessing);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

    if (mDebugEnabled)
    {
      curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, curl_trace);
      curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    }

    struct curl_slist *headerList = NULL;

    headerList = addAuthenticationHeaders(server,filename,headerList);
    if (headerList)
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));

    if (headerList)
      curl_slist_free_all(headerList);


    response.data[response.dataSize] = '\0';
    //printf("%s\n",response.data);

    return response.dataSize;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




int HttpsClient::getData(const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr)
{
  FUNCTION_TRACE
  try
  {
    if (!curl)
      return 0;

    //printf("*** SEND REQUEST %s  : %ld : %d\n",filename,filePosition,dataSize);
    Response response;
    response.data = dataPtr;
    response.maxSize = dataSize;
    response.dataSize = 0;

    char url[1000];
    sprintf(url,"https://%s%s",server,filename);
    //printf("URL [%s]\n",url);

    curl_easy_setopt(curl, CURLOPT_URL,url);
    curl_easy_setopt(curl, CURLOPT_PROXY,"");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,curl_responseProcessing);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

    if (mDebugEnabled)
    {
      curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, curl_trace);
      curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    }

    struct curl_slist *headerList = NULL;

    if ((int)filePosition != dataSize)
    {
      char tmp[1000];
      sprintf(tmp,"Range: bytes=%ld-%ld",filePosition,filePosition+dataSize-1);
      headerList = curl_slist_append(headerList, tmp);
    }

    headerList = addAuthenticationHeaders(server,filename,headerList);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));

    curl_slist_free_all(headerList);

    //printf("### DATA %u\n",response.dataSize);
    return response.dataSize;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



}

