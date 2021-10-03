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
                  ~PhysicalGridFile() override;

    Message*      getMessageByIndex(std::size_t index) override;
    char*         getMemoryPtr() override;
    std::size_t   getNumberOfMessages() override;
    long long     getSize() override;

    bool          isMemoryMapped() const override;
    bool          isPhysical() const override;
    bool          isVirtual() const override;

    bool          hasMessagePositionError() const override;

    void          mapToMemory() override;

    void          print(std::ostream& stream,uint level,uint optionFlags) const override;

    void          read(const std::string& filename) override;
    virtual void          read(MemoryReader& memoryReader);

    void          write(const std::string& filename) override;
    void          write(DataWriter& dataWriter) override;

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
