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


class DataFetcher_network : public DataFetcher
{
  public:
                  DataFetcher_network(uint clientType);
    virtual       ~DataFetcher_network();

    virtual int   getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr);

  protected:

    Client*       newClient();
    Client*       getClient(const char *serverAddress,int serverPort);

    uint          mClientType;
    ThreadLock    mThreadLock;
    Client_vecmap mClients;

  public:

    class ClientType
    {
      public:
        static const uint HTTP  = 1;
        static const uint HTTPS = 2;
    };
};

}  // namespace SmartMet
