#include "DataFetcher_network.h"
#include "AutoThreadLock.h"
#include "HttpClient.h"
#include "HttpsClient.h"
#include "GeneralFunctions.h"

#include <macgyver/Exception.h>
#include <macgyver/TimeParser.h>
#include <curl/curl.h>

#include "ShowFunction.h"
#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{

DataFetcher_network::DataFetcher_network()
{
  FUNCTION_TRACE
  try
  {
    mDebugEnabled = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




DataFetcher_network::~DataFetcher_network()
{
  FUNCTION_TRACE
  try
  {
    AutoThreadLock lock(&mThreadLock);
    for (auto convec = mClients.begin(); convec != mClients.end(); ++convec)
    {
      for (auto con = convec->second.begin(); con != convec->second.end(); ++con)
      {
        delete (*con);
      }
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





Client* DataFetcher_network::newClient(uint protocol)
{
  FUNCTION_TRACE
  try
  {
    switch (protocol)
    {
      case Protocol::HTTP:
        return new HttpClient();

      case Protocol::HTTPS:
        return new HttpsClient();
    }
    return new HttpClient();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Cannot get a connection!",nullptr);
  }
}




Client* DataFetcher_network::getClient(const char *serverAddress,uint serverType,uint protocol)
{
  FUNCTION_TRACE
  try
  {
    AutoThreadLock lock(&mThreadLock);

    char key[100];
    sprintf(key,"%s:%u:%u",serverAddress,serverType,protocol);

    auto convec = mClients.find(key);
    if (convec != mClients.end())
    {
      //printf("Connections %ld:%ld\n",mClients.size(),convec->second.size());

      for (auto it = convec->second.begin();it != convec->second.end(); ++it)
      {
        if (!(*it)->isActive())
        {
          (*it)->setActive(true);
          (*it)->setDebugEnabled(mDebugEnabled);
          return *it;
        }
      }

      if (convec->second.size() >= 100)
        return nullptr;

      Client *conn = newClient(protocol);
      conn->setActive(true);
      conn->setDebugEnabled(mDebugEnabled);
      AccessInfo *accessInfo = getAccessInfo(serverAddress);
      if (accessInfo)
        conn->setAuthentication(accessInfo->authenticationMethod,accessInfo->username.c_str(),accessInfo->password.c_str());
      //else
      //  printf("NO AUTH %s\n",serverAddress);

      convec->second.push_back(conn);
      //printf("Connections %ld:%ld\n",mClients.size(),convec->second.size());
      return conn;
    }
    else
    {
      Client_ptr_vec vec;
      Client *conn = newClient(protocol);
      AccessInfo *accessInfo = getAccessInfo(serverAddress);
      if (accessInfo)
        conn->setAuthentication(accessInfo->authenticationMethod,accessInfo->username.c_str(),accessInfo->password.c_str());
      //else
      //  printf("NO AUTH %s\n",serverAddress);
      conn->setActive(true);
      conn->setDebugEnabled(mDebugEnabled);
      vec.push_back(conn);
      mClients.insert(std::pair<std::string,Client_ptr_vec>(key,vec));
      return conn;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Cannot get a connection!",nullptr);
  }
}





int DataFetcher_network::getData(uint serverType,uint protocol,const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr)
{
  FUNCTION_TRACE
  try
  {
    Client *client = nullptr;
    uint cnt = 0;
    while (!client)
    {
      client = getClient(server,serverType,protocol);
      if (!client)
      {
        cnt++;
        if (cnt == 1000)
          return 0;

        time_usleep(0,1000);
      }
    }

    if (client)
    {
      auto res = client->getData(server,filename,filePosition,dataSize,dataPtr);
      client->setActive(false);
      return res;
    }
    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Cannot get data!",nullptr);
  }
}




bool DataFetcher_network::getFileList(uint protocol,const char *server,XmlElement& rootElement,std::vector<std::string> &filePatterns,std::vector<FileRec>& fileList,std::string& lastKey)
{
  FUNCTION_TRACE
  try
  {
    bool truncated = false;
    for (auto a = rootElement.elementList.begin(); a != rootElement.elementList.end(); ++a)
    {
      if (strcasecmp((*a)->tag.c_str(), "ListBucketResult") == 0)
      {
        std::string name;
        for (auto b = (*a)->elementList.begin(); b != (*a)->elementList.end(); ++b)
        {
          if (strcasecmp((*b)->tag.c_str(), "IsTruncated") == 0)
          {
            if (strcasecmp((*b)->value.c_str(),"true") == 0)
              truncated = true;
          }
          if (strcasecmp((*b)->tag.c_str(), "Name") == 0)
          {
            name = (*b)->value;
          }
          else
          if (strcasecmp((*b)->tag.c_str(), "Contents") == 0)
          {
            FileRec rec;
            rec.serverType = ServerType::S3;
            rec.protocol = protocol;
            rec.server = server;
            for (auto c = (*b)->elementList.begin(); c != (*b)->elementList.end(); ++c)
            {
              if (strcasecmp((*c)->tag.c_str(), "Key") == 0)
              {
                if (truncated)
                  lastKey = (*c)->value;

                rec.filename = "/" + name + "/" + (*c)->value;
              }
              else
              if (strcasecmp((*c)->tag.c_str(), "LastModified") == 0)
              {
                auto tt = Fmi::TimeParser::parse((*c)->value);
                rec.lastModified = toTimeT(tt);
              }
              else
              if (strcasecmp((*c)->tag.c_str(), "Size") == 0)
              {
                rec.size = atoll((*c)->value.c_str());
              }
            }

            if (filePatterns.size() == 0 || patternMatch(rec.filename.c_str(),filePatterns))
              fileList.push_back(rec);
          }
        }
      }
    }
    return truncated;
  }
  catch (Fmi::Exception& e)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void DataFetcher_network::getFileList(uint serverType,uint protocol,const char *server,const char *dir,std::vector<std::string> &filePatterns,std::vector<FileRec>& fileList)
{
  FUNCTION_TRACE
  try
  {
    switch (serverType)
    {
      case ServerType::Unknown:
        return;

      case ServerType::Filesys:
        return;

      case ServerType::S3:
        getFileList_S3(protocol,server,dir,filePatterns,fileList);
        return;

      case ServerType::THREDDS:
        return;

      case ServerType::HTTPD:
        return;
    }
  }
  catch (Fmi::Exception& e)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void DataFetcher_network::getFileList_S3(uint protocol,const char *server,const char *dir,std::vector<std::string> &filePatterns,std::vector<FileRec>& fileList)
{
  FUNCTION_TRACE
  try
  {
    int dataSize = 1000000;
    char data[dataSize];
    bool truncated = false;
    std::string lastKey;
    char fname[1000];

    do
    {
      if (truncated)
        sprintf(fname,"%s?marker=%s",dir,lastKey.c_str());
      else
        strcpy(fname,dir);

      int n = getData(ServerType::S3,protocol,server,fname,dataSize,dataSize,data);
      //printf("READ %d\n",n);
      if (n <= 0)
        return;

      XmlElement xml;
      XmlElement::parseXml(data,n,xml);
      truncated = getFileList(protocol,server,xml,filePatterns,fileList,lastKey);
    } while (truncated);

  }
  catch (Fmi::Exception& e)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void DataFetcher_network::getFileHeaders(uint serverType,uint protocol,const char *server,const char *filename,std::map<std::string,std::string>& headers)
{
  FUNCTION_TRACE
  try
  {
    Client *client = nullptr;
    uint cnt = 0;
    while (!client)
    {
      client = getClient(server,serverType,protocol);
      if (!client)
      {
        cnt++;
        if (cnt == 1000)
          return;

        time_usleep(0,1000);
      }
    }

    if (client)
    {
      int dataSize = 20000;
      char data[dataSize];

      auto n = client->getHeaderData(server,filename,dataSize,data);
      client->setActive(false);
      parseHeaders(data,n,headers);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



long long DataFetcher_network::getFileSize(uint serverType,uint protocol,const char *server,const char *filename)
{
  FUNCTION_TRACE
  try
  {
    std::map<std::string,std::string> headers;
    getFileHeaders(serverType,protocol,server,filename,headers);
    auto it = headers.find("CONTENT-RANGE");
    if (it != headers.end())
    {
      char *p = (char*)it->second.c_str();
      char *n = strstr(p,"/");
      if (n)
        return atoll(n+1);
    }

    return -1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



}  // namespace SmartMet
