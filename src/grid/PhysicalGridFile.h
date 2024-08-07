#pragma once

#include "GridFile.h"
#include "../netcdf/NetCdfFile.h"
#include "../querydata/QueryDataFile.h"


namespace bf = std::filesystem;


namespace SmartMet
{
namespace GRID
{

typedef std::vector<std::pair<uchar,ulonglong>> MessagePos_vec;



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
    virtual void          setSize(long long size);

    virtual bool          isMemoryMapped() const;
    virtual bool          isPhysical() const;
    virtual bool          isVirtual() const;
    virtual bool          isNetworkFile() const;

    virtual bool          hasMessagePositionError() const;

    virtual void          mapToMemory();

    virtual void          print(std::ostream& stream,uint level,uint optionFlags) const;

    virtual void          read(const std::string& filename);
    virtual void          read(const std::string& filename,uint maxMessages);
    virtual void          read(MemoryReader& memoryReader);
    virtual void          read(MemoryReader& memoryReader,uint maxMessages);

    //virtual void          write(const std::string& filename);
    //virtual void          write(DataWriter& dataWriter);

  private:

    GRID::Message*        createMessage(uint messageIndex,GRID::MessageInfo& messageInfo);
    void                  readFmig1Message(MemoryReader& memoryReader, uint messageIndex);
    void                  readNetCDFMessage(MemoryReader& memoryReader, uint messageIndex);
    void                  readGrib1Message(MemoryReader& memoryReader, uint messageIndex);
    void                  readGrib2Message(MemoryReader& memoryReader, uint messageIndex);
    uchar                 readMessageType(MemoryReader& memoryReader);
    MessagePos_vec        searchMessageLocations(MemoryReader& memoryReader,uint maxMessages);

  protected:

    bool                      mIsRead;
    ThreadLock                mMemoryMappingLock;
    bool                      mMessagePositionError;
    NetCDF::NetCdfFile*       mNetCdfFile;
    QueryData::QueryDataFile* mQueryDataFile;
};



}  // namespace GRID
}  // namespace SmartMet
