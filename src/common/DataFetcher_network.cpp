#include "DataFetcher_network.h"
#include "AutoThreadLock.h"
#include "HttpClient.h"
#include "HttpsClient.h"
#include "GeneralFunctions.h"

#include <macgyver/Exception.h>
#include <curl/curl.h>

namespace SmartMet
{

DataFetcher_network::DataFetcher_network(uint protocol,AccessMap *accessMap)
{
  try
  {
    mProtocol = protocol;
    mAccessMap = accessMap;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




DataFetcher_network::~DataFetcher_network()
{
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





AccessInfo* DataFetcher_network::getAccessInfo(const char *server)
{
  try
  {
    if (!mAccessMap)
      return NULL;

    auto rec = mAccessMap->find(server);
    if (rec != mAccessMap->end())
    {
      return &rec->second;
    }

    return NULL;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




Client* DataFetcher_network::newClient()
{
  try
  {
    switch (mProtocol)
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




Client* DataFetcher_network::getClient(const char *serverAddress,uint serverType)
{
  try
  {
    AutoThreadLock lock(&mThreadLock);

    char key[100];
    sprintf(key,"%s:%u",serverAddress,serverType);

    auto convec = mClients.find(key);
    if (convec != mClients.end())
    {
      //printf("Connections %ld:%ld\n",mClients.size(),convec->second.size());

      for (auto it = convec->second.begin();it != convec->second.end(); ++it)
      {
        if (!(*it)->isActive())
        {
          (*it)->setActive(true);
          return *it;
        }
      }

      if (convec->second.size() >= 10)
        return nullptr;

      Client *conn = newClient();
      conn->setActive(true);
      AccessInfo *accessInfo = getAccessInfo(serverAddress);
      if (accessInfo)
        conn->setAuthentication(accessInfo->authenticationMethod,accessInfo->username.c_str(),accessInfo->password.c_str());
      else
        printf("NO AUTH %s\n",serverAddress);

      convec->second.push_back(conn);
      //printf("Connections %ld:%ld\n",mClients.size(),convec->second.size());
      return conn;
    }
    else
    {
      Client_ptr_vec vec;
      Client *conn = newClient();
      AccessInfo *accessInfo = getAccessInfo(serverAddress);
      if (accessInfo)
        conn->setAuthentication(accessInfo->authenticationMethod,accessInfo->username.c_str(),accessInfo->password.c_str());
      else
        printf("NO AUTH %s\n",serverAddress);
      conn->setActive(true);
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





int DataFetcher_network::getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr)
{
  try
  {
    Client *client = nullptr;
    uint cnt = 0;
    while (!client)
    {
      client = getClient(info.server.c_str(),info.serverType);
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
      auto res = client->getData(info,filePosition,dataSize,dataPtr);
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


}  // namespace SmartMet
