#pragma once

#include "Message.h"
#include "GridPointValue.h"
#include "Typedefs.h"
#include "../common/MemoryReader.h"
#include "../common/MemoryMapper.h"
#include "../netcdf/NetCdfFile.h"
#include "../geotiff/GeoTiffFile.h"
#include "../querydata/QueryDataFile.h"

#include <memory>
#include <vector>


namespace SmartMet
{
namespace GRID
{


// ====================================================================================
/*! \brief Format-neutral entry point for reading GRIB1, GRIB2, NetCDF, QueryData, and GeoTIFF files.
 *
 *  GridFile memory-maps a file, detects its format, and exposes a uniform Message-based
 *  interface.  Applications work with GridFile and Message without needing to know the
 *  underlying file format.  Remote files (HTTP / S3) are supported via MemoryMapper. */
// ====================================================================================


typedef std::map<uint,Message*>              Message_ptr_map; //!< Map from message index to Message pointer
typedef std::map<UInt64,Int64>               RequestCounters; //!< Per-message request counters (key = message hash)
typedef std::vector<std::pair<uchar,UInt64>> MessagePos_vec;  //!< (format-byte, file-offset) pairs from a scan


class GridFile
{
  public:
                          GridFile();
                          /*! \brief Copy constructor (shallow: shares meta-data, not the memory map). */
                          GridFile(const GridFile& other);
                          /*! \brief Construct a wrapper around an existing GridFile instance.
                           *  \param[in] gridFile  Source GridFile to copy metadata from. */
                          GridFile(GridFile *gridFile);
    virtual               ~GridFile();

    /*! \brief Register a file that this file depends on (e.g. a shared bitmap file).
     *  \param[in] fileId  Identifier of the dependency file. */
    virtual void          addDependence(T::FileId fileId);

    /*! \brief Attach a pre-created Message object to this file.
     *  \param[in] message  Message to add; ownership is transferred. */
    virtual void          addMessage(Message *message);

    /*! \brief Create and return a new empty GridFile of the same concrete type.
     *  \return Heap-allocated GridFile subclass; caller owns the memory. */
    virtual GridFile*     createGridFile();

    /*! \brief Return the last time this file was accessed.
     *  \return Unix timestamp. */
    virtual time_t        getAccessTime() const;

    /*! \brief Return the scheduled re-check time for this file's metadata.
     *  \return Unix timestamp. */
    virtual time_t        getCheckTime() const;

    /*! \brief Return the time after which this file must not be accessed.
     *  \return Unix timestamp, or 0 if no expiry is set. */
    virtual time_t        getDeletionTime() const;

    /*! \brief Return the deletion time formatted as an ISO-8601 string. */
    virtual std::string   getDeletionTimeStr() const;

    /*! \brief Return the unique file identifier assigned by the content server.
     *  \return File identifier. */
    virtual T::FileId     getFileId() const;

    /*! \brief Return the file path as known to the content server. */
    virtual std::string   getFileName() const;

    /*! \brief Return the path to the local mapping/cache file (may be empty).*/
    virtual std::string   getMappingFileName() const;

    /*! \brief Return the detected file format type.
     *  \return One of T::FileTypeValue constants. */
    virtual T::FileType   getFileType() const;

    /*! \brief Return the file type as a human-readable string. */
    virtual std::string   getFileTypeString() const;

    /*! \brief Return the generation (forecast run) identifier.
     *  \return Generation identifier. */
    virtual T::GenerationId getGenerationId() const;

    /*! \brief Return the bit-flag word for this file.
     *  \return Flag word; see GridFile::Flags for bit definitions. */
    virtual uint          getFlags() const;

    /*! \brief Return the base address of the memory-mapped file data.
     *  \return Pointer into mapped memory, or nullptr if not mapped. */
    virtual char*         getMemoryPtr();

    /*! \brief Return the message at the given zero-based index.
     *  \param[in] index  Zero-based message index.
     *  \return Pointer to the Message, or nullptr if the index is out of range. */
    virtual Message*      getMessageByIndex(std::size_t index);

    /*! \brief Return the file's on-disk modification time.
     *  \return Unix timestamp. */
    virtual time_t        getModificationTime() const;

    /*! \brief Return the total number of messages in this file. */
    virtual std::size_t   getNumberOfMessages();

    /*! \brief Return the transport protocol used to fetch this file.
     *  \return Protocol byte (see MapInfo::Protocol). */
    virtual uchar         getProtocol() const;

    /*! \brief Return the server type that hosts this file.
     *  \return Server type byte (see MapInfo::ServerType). */
    virtual uchar         getServerType() const;

    /*! \brief Return the server hostname or URL that hosts this file. */
    virtual std::string   getServer() const;

    /*! \brief Return the producer identifier for this file.
     *  \return Producer identifier. */
    virtual T::ProducerId getProducerId() const;

    /*! \brief Return the total file size in bytes (computed from messages if needed).
     *  \return File size in bytes. */
    virtual Int64         getSize();

    /*! \brief Return the data source identifier.
     *  \return Source identifier. */
    virtual T::SourceId   getSourceId() const;

    /*! \brief Return true if a message-position parse error occurred during read. */
    virtual bool          hasMessagePositionError() const;

    /*! \brief Return true if the memory-mapper reported an error for this file. */
    virtual bool          hasMemoryMapperError() const;

    /*! \brief Return true if the file is currently memory-mapped. */
    virtual bool          isMemoryMapped() const;

    /*! \brief Return true if the file resides on a remote server (HTTP / S3). */
    virtual bool          isNetworkFile() const;

    /*! \brief Memory-map the file if not already mapped.  Triggers lazy loading for network files. */
    virtual void          mapToMemory();

    /*! \brief Create and return a new empty Message of the given file type.
     *  \param[in] fileType  Target file format (T::FileTypeValue constant).
     *  \return Heap-allocated Message; caller owns the memory. */
    virtual Message*      newMessage(T::FileType fileType);

    /*! \brief Create a new Message using pre-parsed position metadata.
     *  \param[in] messageIndex  Zero-based index within this file.
     *  \param[in] messageInfo   Position and type metadata for the message.
     *  \return Heap-allocated Message; caller owns the memory. */
    virtual Message*      newMessage(T::MessageIndex messageIndex,MessageInfo& messageInfo);

    /*! \brief Print file metadata and optionally message content to a stream.
     *  \param[in] stream      Output stream.
     *  \param[in] level       Indentation level.
     *  \param[in] optionFlags PrintFlag bit mask. */
    virtual void          print(std::ostream& stream,uint level,uint optionFlags) const;

    /*! \brief Open and parse the file at \p filename.
     *  \param[in] filename  Path to the grid file. */
    virtual void          read(const std::string& filename);

    /*! \brief Open and parse up to \p maxMessages messages from \p filename.
     *  \param[in] filename    Path to the grid file.
     *  \param[in] maxMessages Maximum number of messages to parse. */
    virtual void          read(const std::string& filename,uint maxMessages);

    /*! \brief Parse the file from an already-open MemoryReader.
     *  \param[in] memoryReader  Reader positioned at the start of the file. */
    virtual void          read(MemoryReader& memoryReader);

    //! \overload
    virtual void          read(MemoryReader& memoryReader,uint maxMessages);

    /*! \brief Retrieve per-message request counters into \p requestCounters.
     *  \param[out] requestCounters  Populated with (hash → count) pairs.
     *  \return Total request count across all messages. */
    virtual Int64         getRequestCounters(RequestCounters& requestCounters);

    /*! \brief Reset all per-message request counters to zero. */
    virtual void          resetRequestCounters();

    /*! \brief Update the last-access timestamp.
     *  \param[in] accessTime  New access time (Unix timestamp). */
    virtual void          setAccessTime(time_t accessTime);

    /*! \brief Set the scheduled metadata re-check time.
     *  \param[in] checkTime  New check time (Unix timestamp). */
    virtual void          setCheckTime(time_t checkTime);

    /*! \brief Set the time after which this file must not be accessed.
     *  \param[in] deletionTime  Expiry time (Unix timestamp). */
    virtual void          setDeletionTime(time_t deletionTime);

    //! \overload
    virtual void          setDeletionTime(const std::string& deletionTime);

    /*! \brief Assign a file identifier (set by the content server).
     *  \param[in] fileId  Identifier to assign. */
    virtual void          setFileId(T::FileId fileId);

    /*! \brief Set the file path.
     *  \param[in] fileName  Path string. */
    virtual void          setFileName(const std::string& fileName);

    /*! \brief Set the path to the local mapping/cache file.
     *  \param[in] fileName  Mapping file path. */
    virtual void          setMappingFileName(const std::string& fileName);

    /*! \brief Set the generation (forecast run) identifier.
     *  \param[in] generationId  Generation identifier. */
    virtual void          setGenerationId(T::GenerationId generationId);

    /*! \brief Set the flags word.
     *  \param[in] flags  Bit flags (see GridFile::Flags). */
    virtual void          setFlags(uint flags);

    /*! \brief Set the producer identifier.
     *  \param[in] producerId  Producer identifier. */
    virtual void          setProducerId(T::ProducerId producerId);

    /*! \brief Set the transport protocol byte.
     *  \param[in] protocol  Protocol value (see MapInfo::Protocol). */
    virtual void          setProtocol(uchar protocol);

    /*! \brief Set the server type byte.
     *  \param[in] serverType  Server type (see MapInfo::ServerType). */
    virtual void          setServerType(uchar serverType);

    /*! \brief Set the server hostname or URL.
     *  \param[in] server  Server address string. */
    virtual void          setServer(const std::string& server);

    /*! \brief Override the stored file size.
     *  \param[in] size  Size in bytes. */
    virtual void          setSize(Int64 size);

    /*! \brief Set the data source identifier.
     *  \param[in] sourceId  Source identifier. */
    virtual void          setSourceId(T::SourceId sourceId);

    /*! \brief Write the file's messages to a new file at \p filename.
     *  \param[in] filename  Output path. */
    virtual void          write(const std::string& filename);

    /*! \brief Serialise all messages to a DataWriter.
     *  \param[in] dataWriter  Target writer. */
    virtual void          write(DataWriter& dataWriter);

  private:

    GRID::Message*        createMessage(T::MessageIndex messageIndex,GRID::MessageInfo& messageInfo);
    Int64                 countSize();
    void                  readFmig1Message(MemoryReader& memoryReader, T::MessageIndex messageIndex);
    void                  readGrib1Message(MemoryReader& memoryReader, T::MessageIndex messageIndex);
    void                  readGrib2Message(MemoryReader& memoryReader, T::MessageIndex messageIndex);
    uchar                 readMessageType(MemoryReader& memoryReader);
    MessagePos_vec        searchMessageLocations(MemoryReader& memoryReader,uint maxMessages);

  protected:

    time_t                mAccessTime;             //!< Last access time (Unix timestamp)
    time_t                mCheckTime;              //!< Scheduled metadata re-check time
    time_t                mDeletionTime;           //!< Expiry time; file must not be accessed after this
    T::FileId             mFileId;                 //!< File identifier assigned by the content server
    time_t                mFileModificationTime;   //!< On-disk file modification time
    std::string           mFileName;               //!< File path (local or remote URL)
    T::GenerationId       mGenerationId;           //!< Forecast generation (run) identifier
    uint                  mFlags;                  //!< Bit flags (see GridFile::Flags)
    MessageInfo_map       mMessagePositions;       //!< Pre-scanned (offset, length) info per message index
    Message_ptr_map       mMessages;               //!< Parsed Message objects keyed by index
    T::ProducerId         mProducerId;             //!< Data producer identifier
    MapInfo_sptr          mMemoryMapInfo;          //!< Memory-map descriptor (nullptr if not mapped)
    T::SourceId           mSourceId;               //!< Data source identifier
    bool                  mIsRead;                 //!< True after read() has been called
    ThreadLock            mMemoryMappingLock;      //!< Guards concurrent mapToMemory() calls
    bool                  mMessagePositionError;   //!< True if a parsing error occurred during scanning
    NetCDF::NetCdfFile*   mNetCdfFile;             //!< NetCDF file handle (non-null for NetCDF files)
    GeoTiff::GeoTiffFile* mGeoTiffFile;            //!< GeoTIFF file handle (non-null for GeoTIFF files)

    QueryData::QueryDataFile* mQueryDataFile;      //!< QueryData file handle (non-null for QueryData files)

  public:

    /*! \brief Bit-flag constants for the GridFile::mFlags member. */
    class Flags
    {
      public:
        constexpr static const uint LocalCacheExpected = 1; //!< The file should be cached locally if possible
        constexpr static const uint LocalCacheReady    = 2; //!< The file has been successfully cached locally
    };
};


typedef std::shared_ptr<GridFile> GridFile_sptr;
typedef std::vector<GridFile_sptr> GridFile_sptr_vec;


}  // namespace GRID
}  // namespace SmartMet
