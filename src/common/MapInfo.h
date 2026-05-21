#pragma once

#include "ThreadLock.h"
#include <string>
#include <filesystem>
#include <macgyver/MappedFile.h>

namespace bf = std::filesystem;


namespace SmartMet
{

typedef boost::iostreams::mapped_file_params MappedFileParams;

using Fmi::MappedFile;
typedef std::unique_ptr<MappedFile> MappedFile_uptr;


// ====================================================================================
/*! \brief Descriptor for a memory-mapped file region (local or remote).
 *
 *  Holds the server address, protocol, file size, and a pointer into the mapped
 *  memory region.  Used by `MemoryMapper` to track active mappings and by
 *  `GridFile` to carry mapping state for a grid file. */
// ====================================================================================

class MapInfo
{
  public:

    /*! \brief Construct a zeroed descriptor. */
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

    /*! \brief Copy constructor (does not transfer the MappedFile handle). */
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

    uint            protocol;      //!< Transport protocol (see MapInfo::Protocol)
    uint            serverType;    //!< Server category (see MapInfo::ServerType)
    std::string     server;        //!< Server hostname or URL (empty for local files)
    std::string     filename;      //!< File path on the server (or local path)
    std::size_t     fileSize;      //!< On-disk file size in bytes
    std::size_t     allocatedSize; //!< Size of the virtual memory reservation in bytes
    time_t          mappingTime;   //!< Unix timestamp when the mapping was established
    char*           memoryPtr;     //!< Base address of the mapped region (nullptr if not yet mapped)
    bool            mappingError;  //!< True if the last mapping attempt failed
    MappedFile_uptr mappedFile;    //!< Boost-mapped file handle (non-null for local file mappings)

  public:

    /*! \brief Transport protocol constants for `MapInfo::protocol`. */
    class Protocol
    {
      public:

        constexpr static const uint None  = 0; //!< No network protocol (local file)
        constexpr static const uint HTTP  = 1; //!< Plain HTTP
        constexpr static const uint HTTPS = 2; //!< TLS-encrypted HTTP
    };

    /*! \brief Server type constants for `MapInfo::serverType`. */
    class ServerType
    {
      public:

        constexpr static const uint None     = 0; //!< Unknown / not specified
        constexpr static const uint Filesys  = 1; //!< Local filesystem
        constexpr static const uint S3       = 2; //!< Amazon S3 or compatible object store
        constexpr static const uint THREDDS  = 3; //!< THREDDS Data Server
        constexpr static const uint HTTPD    = 4; //!< Generic HTTP server
    };
};

typedef std::shared_ptr<MapInfo> MapInfo_sptr;


}  // namespace SmartMet
