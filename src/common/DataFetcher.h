#pragma once

#include <memory>
#include <map>
#include <vector>

namespace SmartMet
{

class DataFetcher
{
  public:

    class FileRec
    {
      public:
        uint        serverType;
        uint        protocol;
        std::string server;
        std::string filename;
        time_t      lastModified;
        std::size_t size;
    };

    class ServerType
    {
      public:
        static const uint Unknown          = 0;
        static const uint Filesys          = 1;    // Local file system
        static const uint S3               = 2;    // S3
        static const uint THREDDS          = 3;    // THREDDS data server
        static const uint HTTPD            = 4;    // HTTPD
    };

    class AccessInfo
    {
      public:
        uint authenticationMethod = 0;
        std::string username;
        std::string password;
    };

    typedef std::map<std::string,AccessInfo> AccessMap;

  public:
                        DataFetcher();
    virtual             ~DataFetcher();

    virtual void        addAccessInfo(const char *server,uint authenticationMethod,const char *username,const char *password);
    virtual AccessInfo* getAccessInfo(const char *server);
    virtual int         getData(uint serverType,uint protocol,const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr);
    virtual void        getFileList(uint serverType,uint protocol,const char *server,const char *dir,std::vector<std::string> &filePatterns,std::vector<FileRec>& fileList);
    virtual long long   getFileSize(uint serverType,uint protocol,const char *server,const char *filename);
    virtual void        getFileHeaders(uint serverType,uint protocol,const char *server,const char *filename,std::map<std::string,std::string>& headers);
    virtual void        setDebugEnabled(bool enabled);
    virtual void        setAccessFile(const char *filename);

    static void         loadAccessFile(const char *filename,AccessMap&  mAccessMap);
    static void         splitUrl(const char *urlStr,uint& protocol,std::string& server,std::string& filename);
    static void         parseHeaders(char *data,int dataSize,std::map<std::string,std::string>& headers);


  protected:

    bool                mDebugEnabled;
    AccessMap           mAccessMap;
};

typedef std::shared_ptr<DataFetcher> DataFetcher_sptr;
typedef std::map<uint,DataFetcher_sptr> DataFetcher_sptr_map;

}  // namespace SmartMet
