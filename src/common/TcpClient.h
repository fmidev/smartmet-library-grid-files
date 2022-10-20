#pragma once

#include "Client.h"


namespace SmartMet
{


class TcpClient : public Client
{
  public:
            TcpClient();
    virtual ~TcpClient();

    void    openConnection(const char *serverAddress,int serverPort);
    void    closeConnection();

    bool    isConnected();

    int     writeData(char *data,int size);
    int     readData(char *data,int size);
    int     writeAll(char *data,int size);
    int     readAll(char *data,int size);
    int     readLine(char *data,int size);

  protected:

    std::string   mServerAddress;
    int           mServerPort;
    int           mSockfd;
};

typedef TcpClient* TcpClient_ptr;
typedef std::vector<TcpClient_ptr> TcpClient_ptr_vec;

}
