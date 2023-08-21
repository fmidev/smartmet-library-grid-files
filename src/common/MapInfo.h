#pragma once

#include "ThreadLock.h"
#include <string>
#include <boost/filesystem.hpp>
#include <macgyver/MappedFile.h>

namespace bf = boost::filesystem;


namespace SmartMet
{

typedef boost::iostreams::mapped_file_params MappedFileParams;

using Fmi::MappedFile;
typedef std::unique_ptr<MappedFile> MappedFile_uptr;


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
      mappingTime = 0;
    }

    MapInfo(const MapInfo& info)
    {
      protocol = info.protocol;
      serverType = info.serverType;
      server = info.server;
      fileSize = info.fileSize;
      filename = info.filename;
      allocatedSize = info.allocatedSize;
      memoryPtr = info.memoryPtr;
      mappingError = info.mappingError;
      mappingTime = info.mappingTime;
    }

    virtual ~MapInfo()
    {
      if (mappedFile)
        mappedFile->close();
    }

  public:

    uint            protocol;
    uint            serverType;
    std::string     server;
    std::string     filename;
    std::size_t     fileSize;
    std::size_t     allocatedSize;
    time_t          mappingTime;
    char*           memoryPtr;
    bool            mappingError;
    MappedFile_uptr mappedFile;

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
