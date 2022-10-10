#pragma once

#include "ThreadLock.h"

#include <string>
#include <vector>

namespace SmartMet
{


class TcpClient
{
  public:
    TcpClient();
    ~TcpClient();

    void openConnection(const char *serverAddress,int serverPort);
    void closeConnection();

    bool isActive();
    void setActive(bool active);

    bool isConnected();

    int  writeData(char *data,int size);
    int  readData(char *data,int size);
    int  writeAll(char *data,int size);
    int  readAll(char *data,int size);
    int  readLine(char *data,int size);

  protected:

    std::string mServerAddress;
    int         mServerPort;
    int         mSockfd;
    bool        mActive;
};

typedef TcpClient* TcpClient_ptr;
typedef std::vector<TcpClient_ptr> TcpClient_ptr_vec;

}
