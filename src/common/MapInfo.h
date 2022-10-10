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
      server = "127.0.0.1";
      port = 80;
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
    std::string server;
    int         port;
    std::string filename;
    std::size_t fileSize;
    std::size_t allocatedSize;
    char*       memoryPtr;
    bool        mappingError;
};


}  // namespace SmartMet
