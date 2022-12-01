#include "Client.h"
#include "GeneralFunctions.h"
#include <macgyver/Exception.h>
#include "ShowFunction.h"

#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{


Client::Client()
{
  FUNCTION_TRACE
  try
  {
    mActive = false;
    mAuthenticationMethod = 0;
    mDebugEnabled = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




Client::~Client()
{
}




int Client::getData(const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr)
{
  throw Fmi::Exception(BCP,"Should be implemented in the child class!");
}




int Client::getHeaderData(const char *server,const char *filename,int dataSize,char *dataPtr)
{
  throw Fmi::Exception(BCP,"Should be implemented in the child class!");
}




bool Client::isActive()
{
  return mActive;
}




void Client::setActive(bool active)
{
  mActive = active;
}



void Client::setDebugEnabled(bool enabled)
{
  mDebugEnabled = enabled;
}




void Client::setAuthentication(uint authenticationMethod,const char *username,const char *password)
{
  FUNCTION_TRACE
  try
  {
    mAuthenticationMethod = authenticationMethod;
    mUsername = username;
    mPassword = password;
    //printf("SET AUTH %u:%s:%s\n",authenticationMethod,username,password);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




struct curl_slist* Client::addAuthenticationHeaders(const char *server,const char *filename,struct curl_slist *headerList)
{
  FUNCTION_TRACE
  try
  {
    if (mAuthenticationMethod == 1)
    {
      time_t currentTime = time(0);

      std::string timeStamp = utcTimeFromTimeT(currentTime);
      std::string date = timeStamp.substr(0,8);
      //std::string username = "test";
      //std::string password = "testtest";
      std::string dateRegion = "eu-north-1";
      std::string dateRegionService = "s3";
      std::string signing = "aws4_request";

      char canonicalRequest[10000];
      char *r = canonicalRequest;
      r += sprintf(r,"GET\n");
      r += sprintf(r,"%s\n",filename);
      r += sprintf(r,"\n");
      r += sprintf(r,"host:%s\n",server);
      r += sprintf(r,"x-amz-content-sha256:e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855\n");
      r += sprintf(r,"x-amz-date:%sZ\n",timeStamp.c_str());
      r += sprintf(r,"\n");
      r += sprintf(r,"host;x-amz-content-sha256;x-amz-date\n");
      r += sprintf(r,"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");


      char hexHash[100];
      hash_sha256((unsigned char*)canonicalRequest,strlen(canonicalRequest),hexHash);

      //printf("CANONICAL REQUEST:\n%s\n",canonicalRequest);

      char stringToSign[10000];
      char *p = stringToSign;
      p += sprintf(p,"AWS4-HMAC-SHA256\n");
      p += sprintf(p,"%sZ\n",timeStamp.c_str());
      p += sprintf(p,"%s/%s/%s/%s\n",date.c_str(),dateRegion.c_str(),dateRegionService.c_str(),signing.c_str());
      p += sprintf(p,"%s",hexHash);

      //printf("STRING TO SIGN:\n%s\n",stringToSign);

      char hexSignature[100];
      if (signature_aws_s3_v4(mUsername.c_str(),mPassword.c_str(),date.c_str(),dateRegion.c_str(),dateRegionService.c_str(),stringToSign,hexSignature) == 0)
      {
        //printf("SIGNATURE : %s\n",hexSignature);

        headerList = curl_slist_append(headerList,"x-amz-content-sha256:e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");

        char tmp[1000];
        sprintf(tmp,"x-amz-date:%sZ",timeStamp.c_str());
        headerList = curl_slist_append(headerList, tmp);

        sprintf(tmp,"Authorization: AWS4-HMAC-SHA256 Credential=%s/%s/%s/%s/%s,SignedHeaders=host;x-amz-content-sha256;x-amz-date,Signature=%s",
            mUsername.c_str(),date.c_str(),dateRegion.c_str(),dateRegionService.c_str(),signing.c_str(),hexSignature);

        headerList = curl_slist_append(headerList, tmp);
      }
    }

    return headerList;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




size_t curl_responseProcessing(char *ptr, size_t size, size_t nmemb, void *userdata)
{
  FUNCTION_TRACE
  try
  {
    //printf("### RECEIVE %ld\n",nmemb);
    Client::Response *response = (Client::Response*)userdata;

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





void curl_dump(const char *text,FILE *stream, unsigned char *ptr, size_t size)
{
  size_t i;
  size_t c;
  unsigned int width=0x10;

  fprintf(stream, "%s, %10.10ld bytes (0x%8.8lx)\n",
          text, (long)size, (long)size);

  for(i=0; i<size; i+= width)
  {
    fprintf(stream, "%4.4lx: ", (long)i);

    /* show hex to the left */
    for(c = 0; c < width; c++)
    {
      if(i+c < size)
        fprintf(stream, "%02x ", ptr[i+c]);
      else
        fputs("   ", stream);
    }

    /* show data on the right */
    for(c = 0; (c < width) && (i+c < size); c++)
    {
      char x = (ptr[i+c] >= 0x20 && ptr[i+c] < 0x80) ? ptr[i+c] : '.';
      fputc(x, stream);
    }

    fputc('\n', stream); /* newline */
  }
}



int curl_trace(CURL *handle, curl_infotype type,char *data, size_t size,void *userp)
{
  const char *text;
  (void)handle; /* prevent compiler warning */
  (void)userp;

  switch (type)
  {
    case CURLINFO_TEXT:
      fprintf(stderr, "== Info: %s", data);
      return 0;
    default: /* in case a new one is introduced to shock us */
      return 0;

    case CURLINFO_HEADER_OUT:
      text = "=> Send header";
      break;
    case CURLINFO_DATA_OUT:
      text = "=> Send data";
      break;
    case CURLINFO_SSL_DATA_OUT:
      text = "=> Send SSL data";
      break;
    case CURLINFO_HEADER_IN:
      text = "<= Recv header";
      break;
    case CURLINFO_DATA_IN:
      text = "<= Recv data";
      break;
    case CURLINFO_SSL_DATA_IN:
      text = "<= Recv SSL data";
      break;
  }

  curl_dump(text, stderr, (unsigned char *)data, size);
  return 0;
}




}


