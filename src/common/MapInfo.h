#pragma once

#include "ThreadLock.h"
#include <string>


namespace SmartMet
{

class MapInfo
{
  public:

    MapInfo()
    {
      protocol = 0;
      serverType = 1;
      server = ""; // "127.0.0.1";
      fileSize = 0;
      allocatedSize = 0;
      memoryPtr = nullptr;
      mappingError = false;
    }

    virtual ~MapInfo()
    {
    }

  public:

    uint        protocol;
    uint        serverType;
    std::string server;
    std::string filename;
    std::size_t fileSize;
    std::size_t allocatedSize;
    char*       memoryPtr;
    bool        mappingError;

  public:

    class Protocol
    {
      public:

        static const uint None  = 0;
        static const uint HTTP  = 1;
        static const uint HTTPS = 2;
    };

    class ServerType
    {
      public:

        static const uint None     = 0;
        static const uint Filesys  = 1;
        static const uint S3       = 2;
        static const uint THREDDS  = 3;
        static const uint HTTPD    = 4;
    };
};


}  // namespace SmartMet
