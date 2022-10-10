#include "DataFetcher_HTTP.h"
#include "AutoThreadLock.h"
#include <macgyver/Exception.h>

namespace SmartMet
{

DataFetcher_HTTP::DataFetcher_HTTP()
{
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




DataFetcher_HTTP::~DataFetcher_HTTP()
{
  try
  {
    for (auto convec = mConnections.begin(); convec != mConnections.end(); ++convec)
    {
      for (auto con = convec->second.begin(); con != convec->second.end(); ++con)
      {
        (*con)->closeConnection();
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




TcpClient* DataFetcher_HTTP::getConnection(const char *serverAddress,int serverPort)
{
  try
  {
    AutoThreadLock lock(&threadLock);

    char key[100];
    sprintf(key,"%s:%d",serverAddress,serverPort);

    auto convec = mConnections.find(key);
    if (convec != mConnections.end())
    {
      for (auto it = convec->second.begin();it != convec->second.end(); ++it)
      {
        if (!(*it)->isActive())
        {
          if (!(*it)->isConnected())
          {
            try
            {
              (*it)->openConnection(serverAddress,serverPort);
            }
            catch (...)
            {
              throw Fmi::Exception(BCP,"Connection open failed!",nullptr);
            }
          }

          (*it)->setActive(true);
          return *it;
        }
      }

      TcpClient *conn = new TcpClient();
      try
      {
        conn->openConnection(serverAddress,serverPort);
      }
      catch (...)
      {
        delete conn;
        throw Fmi::Exception(BCP,"Connection open failed!",nullptr);
      }

      conn->setActive(true);
      convec->second.push_back(conn);
      return conn;
    }
    else
    {
      TcpClient_ptr_vec vec;
      TcpClient *conn = new TcpClient();
      try
      {
        conn->openConnection(serverAddress,serverPort);
      }
      catch (...)
      {
        delete conn;
        throw Fmi::Exception(BCP,"Connection open failed!",nullptr);
      }

      conn->setActive(true);
      vec.push_back(conn);
      mConnections.insert(std::pair<std::string,TcpClient_ptr_vec>(key,vec));
      return conn;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Cannot get a connection!",nullptr);
  }
}




void DataFetcher_HTTP::sendRequest(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr)
{
  try
  {
    printf("*** SEND REQUEST %s  : %ld : %d\n",info.filename.c_str(),filePosition,dataSize);
    TcpClient *connection = getConnection(info.server.c_str(),info.port);

    if (!connection)
    {
      Fmi::Exception exception(BCP,"Cannot get a valid connection!");
      throw exception;
    }

    char request[5000];
    char *p = request;

    p += sprintf(p,"GET %s HTTP/1.1\r\n",info.filename.c_str());
    p += sprintf(p,"Host: %s\r\n",info.server.c_str());
    p += sprintf(p,"Connection: keep-alive\r\n");
    p += sprintf(p,"Content-Length: 0\r\n");
    p += sprintf(p,"User-Agent: FMI SmartMet Server\r\n");
    p += sprintf(p,"Range: bytes=%ld-%ld\r\n",filePosition,filePosition+dataSize);
    p += sprintf(p,"Accept: */*\r\n");
    p += sprintf(p,"\r\n");

    //printf("%s",request);

    try
    {
      int n = connection->writeAll(request,strlen(request));
      printf("SEND %d\n",n);
      if (n < 0)
      {
        connection->closeConnection();
        connection->openConnection(info.server.c_str(),info.port);
        n = connection->writeAll(request,strlen(request));
        printf("RESEND %d\n",n);
      }

    }
    catch (...)
    {
      connection->setActive(false);
      Fmi::Exception exception(BCP,"Socket write failed!",nullptr);
      throw exception;
    }

    int contentLength = 0;
    try
    {
      char buf[5000];
      while (connection->readLine(buf,5000) > 0)
      {
        printf("%s\n",buf);
        if (strncasecmp(buf,"Content-Length",14) == 0)
        {
          char *p = strchr(buf+14,':');
          if (p)
            contentLength = atoi(p+1);
        }
      }
    }
    catch (...)
    {
      connection->setActive(false);
      Fmi::Exception exception(BCP,"HTTP header read failed!",nullptr);
      throw exception;
    }

    if (contentLength != dataSize)
    {
      connection->setActive(false);
      Fmi::Exception exception(BCP,"Invalid content length!");
      exception.addParameter("received contentLength",std::to_string(contentLength));
      exception.addParameter("expected contentLength",std::to_string(dataSize));
      throw exception;
    }

    try
    {
      int n = connection->readAll(dataPtr,dataSize);
      printf("READ %d/%d\n",n,dataSize);
    }
    catch (...)
    {
      connection->setActive(false);
      Fmi::Exception exception(BCP,"HTTP body read failed!",nullptr);
      throw exception;
    }
    connection->setActive(false);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Cannot get data over an HTTP connection!",nullptr);
  }
}




int DataFetcher_HTTP::getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr)
{
  try
  {
    sendRequest(info,filePosition,dataSize,dataPtr);
    return dataSize;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Cannot get data!",nullptr);
  }
}




}  // namespace SmartMet
