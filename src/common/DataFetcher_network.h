#pragma once

#include "DataFetcher.h"
#include "ThreadLock.h"
#include "Client.h"
#include "XmlElement.h"

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
                  DataFetcher_network();
    virtual       ~DataFetcher_network();

    int           getData(uint serverType,uint protocol,const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr);
    void          getFileList(uint serverType,uint protocol,const char *server,const char *dir,std::vector<std::string> &filePatterns,std::vector<FileRec>& fileList);
    long long     getFileSize(uint serverType,uint protocol,const char *server,const char *filename);
    void          getFileHeaders(uint serverType,uint protocol,const char *server,const char *filename,std::map<std::string,std::string>& headers);

  protected:

    Client*       newClient(uint protocol);
    Client*       getClient(const char *serverAddress,uint serverType,uint protocol);
    bool          getFileList(uint protocol,const char *server,XmlElement& rootElement,std::vector<std::string> &filePatterns,std::vector<FileRec>& fileList,std::string& lastKey);
    void          getFileList_S3(uint protocol,const char *server,const char *dir,std::vector<std::string> &filePatterns,std::vector<FileRec>& fileList);


    ThreadLock    mThreadLock;
    Client_vecmap mClients;

  public:

    class Protocol
    {
      public:
        static const uint HTTP  = 1;
        static const uint HTTPS = 2;
    };
};

}  // namespace SmartMet
