#pragma once

#include "Client.h"


namespace SmartMet
{


// ====================================================================================
/*! \brief Simple TCP socket client for raw byte-stream connections. */
// ====================================================================================

class TcpClient : public Client
{
  public:
            TcpClient();
    virtual ~TcpClient();

    /*! \brief Open a TCP connection to the given server.
     *  \param[in] serverAddress  Hostname or IP address.
     *  \param[in] serverPort     Port number. */
    void    openConnection(const char *serverAddress,int serverPort);

    /*! \brief Close the active TCP connection. */
    void    closeConnection();

    /*! \brief Return true if the socket is currently connected. */
    bool    isConnected();

    /*! \brief Write up to \p size bytes from \p data to the socket.
     *  \param[in] data  Source buffer.
     *  \param[in] size  Number of bytes to write.
     *  \return Bytes written, or a negative error code. */
    int     writeData(char *data,int size);

    /*! \brief Read up to \p size bytes from the socket into \p data.
     *  \param[out] data  Destination buffer.
     *  \param[in]  size  Maximum bytes to read.
     *  \return Bytes read, or a negative error code. */
    int     readData(char *data,int size);

    /*! \brief Write exactly \p size bytes, retrying until all are sent.
     *  \param[in] data  Source buffer.
     *  \param[in] size  Number of bytes to write.
     *  \return \p size on success, or a negative error code. */
    int     writeAll(char *data,int size);

    /*! \brief Read exactly \p size bytes, blocking until all arrive.
     *  \param[out] data  Destination buffer.
     *  \param[in]  size  Number of bytes expected.
     *  \return \p size on success, or a negative error code. */
    int     readAll(char *data,int size);

    /*! \brief Read one newline-terminated line from the socket.
     *  \param[out] data  Destination buffer (null-terminated on success).
     *  \param[in]  size  Maximum characters to read.
     *  \return Number of characters read (excluding the newline). */
    int     readLine(char *data,int size);

  protected:

    std::string   mServerAddress; //!< Server hostname or IP address
    int           mServerPort;    //!< Server port number
    int           mSockfd;        //!< POSIX socket file descriptor (-1 when not connected)
};

typedef TcpClient* TcpClient_ptr;
typedef std::vector<TcpClient_ptr> TcpClient_ptr_vec;

}
