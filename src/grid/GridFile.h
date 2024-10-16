#pragma once

#include "Message.h"
#include "GridPointValue.h"
#include "Typedefs.h"
#include "../common/MemoryReader.h"
#include "../common/MemoryMapper.h"
#include "../netcdf/NetCdfFile.h"
#include "../querydata/QueryDataFile.h"

#include <memory>
#include <vector>


namespace SmartMet
{
namespace GRID
{


// ====================================================================================
/*! \brief The main purpose of this class is to hide differences of different grib/grid
    files (GRIB1, GRIB2, etc) so that applications do not need to know what kind
    of grib/grid files they are using.

    The class maps the current file into the memory and redirects incoming requests to
    the actual implementation. */
// ====================================================================================


typedef std::map<uint,Message*> Message_ptr_map;
typedef std::map<unsigned long long,long long> RequestCounters;
typedef std::vector<std::pair<uchar,ulonglong>> MessagePos_vec;


class GridFile
{
  public:
                          GridFile();
                          GridFile(const GridFile& other);
                          GridFile(GridFile *gridFile);
    virtual               ~GridFile();

    virtual void          addDependence(uint fileId);
    virtual void          addMessage(Message *message);

    virtual GridFile*     createGridFile();

    virtual time_t        getAccessTime() const;
    virtual time_t        getCheckTime() const;
    virtual time_t        getDeletionTime() const;
    virtual std::string   getDeletionTimeStr() const;
    virtual uint          getFileId() const;
    virtual std::string   getFileName() const;
    virtual std::string   getMappingFileName() const;
    virtual T::FileType   getFileType() const;
    virtual std::string   getFileTypeString() const;
    virtual uint          getGenerationId() const;
    virtual uint          getFlags() const;
    virtual char*         getMemoryPtr();
    virtual Message*      getMessageByIndex(std::size_t index);
    virtual time_t        getModificationTime() const;
    virtual std::size_t   getNumberOfMessages();
    virtual uchar         getProtocol() const;
    virtual uchar         getServerType() const;
    virtual std::string   getServer() const;

    virtual uint          getProducerId() const;
    virtual long long     getSize();
    virtual uint          getSourceId() const;

    virtual bool          hasMessagePositionError() const;
    virtual bool          hasMemoryMapperError() const;

    virtual bool          isMemoryMapped() const;
    virtual bool          isNetworkFile() const;

    virtual void          mapToMemory();

    virtual Message*      newMessage(T::FileType fileType);
    virtual Message*      newMessage(uint messageIndex,MessageInfo& messageInfo);

    virtual void          print(std::ostream& stream,uint level,uint optionFlags) const;

    virtual void          read(const std::string& filename);
    virtual void          read(const std::string& filename,uint maxMessages);
    virtual void          read(MemoryReader& memoryReader);
    virtual void          read(MemoryReader& memoryReader,uint maxMessages);

    virtual long long     getRequestCounters(RequestCounters& requestCounters);
    virtual void          resetRequestCounters();

    virtual void          setAccessTime(time_t checkTime);
    virtual void          setCheckTime(time_t checkTime);
    virtual void          setDeletionTime(time_t deletionTime);
    virtual void          setDeletionTime(const std::string& deletionTime);
    virtual void          setFileId(uint fileId);
    virtual void          setFileName(const std::string& fileName);
    virtual void          setMappingFileName(const std::string& fileName);
    virtual void          setGenerationId(uint generationId);
    virtual void          setFlags(uint groupFlags);
    virtual void          setProducerId(uint producerId);
    virtual void          setProtocol(uchar protocol);
    virtual void          setServerType(uchar serverType);
    virtual void          setServer(const std::string& server);
    virtual void          setSize(long long size);
    virtual void          setSourceId(uint sourceId);

    virtual void          write(const std::string& filename);
    virtual void          write(DataWriter& dataWriter);

  private:

    GRID::Message*        createMessage(uint messageIndex,GRID::MessageInfo& messageInfo);
    long long             countSize();
    void                  readFmig1Message(MemoryReader& memoryReader, uint messageIndex);
    void                  readNetCDFMessage(MemoryReader& memoryReader, uint messageIndex);
    void                  readGrib1Message(MemoryReader& memoryReader, uint messageIndex);
    void                  readGrib2Message(MemoryReader& memoryReader, uint messageIndex);
    uchar                 readMessageType(MemoryReader& memoryReader);
    MessagePos_vec        searchMessageLocations(MemoryReader& memoryReader,uint maxMessages);

  protected:

    time_t                mAccessTime;
    time_t                mCheckTime;
    time_t                mDeletionTime;      // The file should not be accessed after this time
    uint                  mFileId;
    time_t                mFileModificationTime;
    std::string           mFileName;
    uint                  mGenerationId;
    uint                  mFlags;
    MessageInfo_map       mMessagePositions;
    Message_ptr_map       mMessages;
    uint                  mProducerId;
    MapInfo_sptr          mMemoryMapInfo;
    uint                  mSourceId;
    bool                  mIsRead;
    ThreadLock            mMemoryMappingLock;
    bool                  mMessagePositionError;
    NetCDF::NetCdfFile*   mNetCdfFile;

    QueryData::QueryDataFile* mQueryDataFile;

  public:

    class Flags
    {
      public:
        static const uint LocalCacheExpected = 1;     // The file shoud be cached locally if possible
        static const uint LocalCacheReady    = 2;    // The file is cached locally
    };
};


typedef std::shared_ptr<GridFile> GridFile_sptr;
typedef std::vector<GridFile_sptr> GridFile_sptr_vec;


}  // namespace GRID
}  // namespace SmartMet
