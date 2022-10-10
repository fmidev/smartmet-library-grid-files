#pragma once

#include "DataFetcher.h"
#include "ThreadLock.h"
#include "TcpClient.h"

namespace SmartMet
{

class DataFetcher_HTTP : public DataFetcher
{
  public:
                    DataFetcher_HTTP();
    virtual         ~DataFetcher_HTTP();

    virtual int     getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr);

  protected:

    TcpClient*      getConnection(const char *serverAddress,int serverPort);
    void            sendRequest(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr);

    ThreadLock      threadLock;

    std::map<std::string,TcpClient_ptr_vec> mConnections;

};

}  // namespace SmartMet
