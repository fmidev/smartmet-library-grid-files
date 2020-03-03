#pragma once

#include "GridFile.h"

#include <boost/filesystem.hpp>
#include <boost/iostreams/device/mapped_file.hpp>


namespace bf = boost::filesystem;

typedef boost::iostreams::mapped_file_params MappedFileParams;
typedef boost::iostreams::mapped_file MappedFile;


namespace SmartMet
{
namespace GRID
{

typedef std::unique_ptr<MappedFile> MappedFile_uptr;
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
    virtual bool          isPhysical() const;
    virtual bool          isVirtual() const;
    virtual bool          isMemoryMapped() const;
    virtual void          mapToMemory();

    virtual void          print(std::ostream& stream,uint level,uint optionFlags) const;
    virtual void          read(std::string filename);
    virtual void          read(MemoryReader& memoryReader);
    virtual void          write(std::string filename);
    virtual void          write(DataWriter& dataWriter);

  private:

    //void                  read();
    GRID::Message*        createMessage(uint messageIndex,GRID::MessageInfo& messageInfo);
    void                  readGrib1Message(MemoryReader& memoryReader, uint messageIndex);
    void                  readGrib2Message(MemoryReader& memoryReader, uint messageIndex);
    uchar                 readMessageType(MemoryReader& memoryReader);
    MessagePos_vec        searchMessageLocations(MemoryReader& memoryReader);

  protected:

    bool                  mIsMemoryMapped;
    bool                  mIsRead;
    char*                 mMemoryPtr;
    long long             mFileSize;
    ThreadLock            mMemoryMappingLock;
    MappedFile_uptr       mMappedFile;
};



}  // namespace GRID
}  // namespace SmartMet
