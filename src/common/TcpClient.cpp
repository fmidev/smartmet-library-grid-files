#include "TcpClient.h"
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


namespace SmartMet
{


/*! \brief Default constructor for TcpClient. */

TcpClient::TcpClient()
{
  try
  {
    mActive = false;
    mServerPort = 0;
    mSockfd = -1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Destructor that shuts down and closes any open socket. */

TcpClient::~TcpClient()
{

  if (mSockfd >= 0)
  {
    shutdown(mSockfd,SHUT_RDWR);
    close(mSockfd);
    mSockfd = -1;
  }
}




/*! \brief Opens a TCP connection to the given server and port. */

void TcpClient::openConnection(const char *serverAddress,int serverPort)
{
  try
  {
    if (mSockfd >= 0)
    {
      shutdown(mSockfd,SHUT_RDWR);
      close(mSockfd);
      mSockfd = -1;
    }

    mServerAddress = serverAddress;
    mServerPort = serverPort;

    struct sockaddr_in serv_addr;
    struct hostent *server = gethostbyname(serverAddress);
    if(server == NULL)
    {
      Fmi::Exception exception(BCP,"Unknown server!");
      exception.addParameter("serverAddress",serverAddress);
      throw exception;
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*) server->h_addr, (char*) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(mServerPort);

    mSockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (mSockfd < 0)
      throw Fmi::Exception(BCP,"Socket allocation failed!");

    if (connect(mSockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
    {
      close(mSockfd);
      mSockfd = -1;
      Fmi::Exception exception(BCP,"Connection failed!");
      exception.addParameter("serverAddress",serverAddress);
      exception.addParameter("serverPort",std::to_string(serverPort));
      throw exception;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Closes the TCP connection if currently open. */

void TcpClient::closeConnection()
{
  try
  {
    if (mSockfd >= 0)
    {
      shutdown(mSockfd,SHUT_RDWR);
      close(mSockfd);
      mSockfd = -1;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Returns true if the TCP socket is currently connected. */

bool TcpClient::isConnected()
{
  try
  {
    if (mSockfd < 0)
      return false;

    char data;
    if (recv(mSockfd,&data,1, MSG_PEEK | MSG_DONTWAIT) >= 0)
      return true;

    closeConnection();
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Sends bytes on the socket using a single non-blocking send. */

int TcpClient::writeData(char *data,int size)
{
  try
  {
    if (mSockfd < 0)
      throw Fmi::Exception(BCP,"Not connected!");

    int n = send(mSockfd,data,size,MSG_DONTWAIT);
    return n;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Reads bytes from the socket using a single non-blocking recv. */

int TcpClient::readData(char *data,int size)
{
  try
  {
    if (mSockfd < 0)
      throw Fmi::Exception(BCP,"Not connected!");

    int n = recv(mSockfd,data,size,MSG_DONTWAIT);
    return n;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Writes the entire buffer to the socket, looping until all bytes are sent. */

int TcpClient::writeAll(char *data,int size)
{
  try
  {
    if (mSockfd < 0)
      throw Fmi::Exception(BCP,"Not connected!");


    int writeCnt = 0;
    while (writeCnt < size)
    {
      int n = send(mSockfd,data+writeCnt,size-writeCnt,MSG_WAITALL);
      if (n < 0)
        return n;

      if (n > 0)
        writeCnt += n;

      if (n == 0)
        time_usleep(0,100);
    }
    return writeCnt;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Reads a line from the socket up to a newline or the buffer size. */

int TcpClient::readLine(char *data,int size)
{
  try
  {
    if (mSockfd < 0)
      throw Fmi::Exception(BCP,"Not connected!");

    int readCnt = 0;
    while (readCnt < size)
    {
      int n = recv(mSockfd,&data[readCnt],1,MSG_WAITALL);
      if (n <= 0)
      {
        return readCnt;
      }

      if (data[readCnt] == '\n')
      {
        data[readCnt] = '\0';
        return readCnt;
      }

      if (data[readCnt] == '\r')
        data[readCnt] = '\0';
      else
        readCnt += n;
    }
    return readCnt;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Reads exactly the requested number of bytes from the socket. */

int TcpClient::readAll(char *data,int size)
{
  try
  {
    if (mSockfd < 0)
      throw Fmi::Exception(BCP,"Not connected!");

    int readCnt = 0;
    while (readCnt < size)
    {
      int n = recv(mSockfd,data+readCnt,size-readCnt,MSG_WAITALL);
      if (n < 0)
        return n;

      if (n > 0)
        readCnt += n;

      if (n == 0)
        time_usleep(0,100);
    }
    return readCnt;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



}
