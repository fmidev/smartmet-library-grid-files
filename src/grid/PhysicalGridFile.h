#pragma once

#include "GridFile.h"
#include "../netcdf/NetCdfFile.h"

#include <boost/filesystem.hpp>
#include <boost/iostreams/device/mapped_file.hpp>


namespace bf = boost::filesystem;

using MappedFileParams = boost::iostreams::mapped_file_params;
using MappedFile = boost::iostreams::mapped_file;


namespace SmartMet
{
namespace GRID
{

using MappedFile_uptr = std::unique_ptr<MappedFile>;
using MessagePos_vec = std::vector<std::pair<uchar, ulonglong>>;


// ====================================================================================
/*! \brief The main purpose of this class is ...
*/
// ====================================================================================


class PhysicalGridFile : public GridFile
{
  public:
                          PhysicalGridFile();
                          PhysicalGridFile(const PhysicalGridFile& other);
    virtual               ~PhysicalGridFile();

    virtual Message*      getMessageByIndex(std::size_t index);
    virtual char*         getMemoryPtr();
    virtual std::size_t   getNumberOfMessages();
    virtual long long     getSize();

    virtual bool          isMemoryMapped() const;
    virtual bool          isPhysical() const;
    virtual bool          isVirtual() const;

    virtual bool          hasMessagePositionError() const;

    virtual void          mapToMemory();

    virtual void          print(std::ostream& stream,uint level,uint optionFlags) const;

    virtual void          read(const std::string& filename);
    virtual void          read(MemoryReader& memoryReader);

    virtual void          write(const std::string& filename);
    virtual void          write(DataWriter& dataWriter);

  private:

    //void                  read();
    GRID::Message*        createMessage(uint messageIndex,GRID::MessageInfo& messageInfo);
    void                  readFmig1Message(MemoryReader& memoryReader, uint messageIndex);
    void                  readNetCDFMessage(MemoryReader& memoryReader, uint messageIndex);
    void                  readGrib1Message(MemoryReader& memoryReader, uint messageIndex);
    void                  readGrib2Message(MemoryReader& memoryReader, uint messageIndex);
    uchar                 readMessageType(MemoryReader& memoryReader);
    MessagePos_vec        searchMessageLocations(MemoryReader& memoryReader);

  protected:

    long long             mFileSize;
    bool                  mIsMemoryMapped;
    bool                  mIsRead;
    MappedFile_uptr       mMappedFile;
    ThreadLock            mMemoryMappingLock;
    char*                 mMemoryPtr;
    bool                  mMessagePositionError;
    NetCDF::NetCdfFile*   mNetCdfFile;
};



}  // namespace GRID
}  // namespace SmartMet
