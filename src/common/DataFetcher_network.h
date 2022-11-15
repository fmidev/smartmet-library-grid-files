#pragma once

#include "DataFetcher.h"
#include "ThreadLock.h"
#include "Client.h"

namespace SmartMet
{

struct Response
{
  char *data;
  uint dataSize;
  uint maxSize;
};

typedef std::map<std::string,Client_ptr_vec> Client_vecmap;



class AccessInfo
{
  public:
    uint authenticationMethod = 0;
    std::string username;
    std::string password;
};

typedef std::map<std::string,AccessInfo> AccessMap;





class DataFetcher_network : public DataFetcher
{
  public:
                  DataFetcher_network(uint protocol,AccessMap *accessMap);
    virtual       ~DataFetcher_network();

    virtual int   getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr);

  protected:

    AccessInfo*   getAccessInfo(const char *server);
    Client*       newClient();
    Client*       getClient(const char *serverAddress,uint serviceType);

    uint          mProtocol;
    ThreadLock    mThreadLock;
    Client_vecmap mClients;
    AccessMap*    mAccessMap;

  public:

    class Protocol
    {
      public:
        static const uint HTTP  = 1;
        static const uint HTTPS = 2;
    };
};

}  // namespace SmartMet
