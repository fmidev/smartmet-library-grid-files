#pragma once

#include "../grid/PhysicalGridFile.h"
#include "Message.h"


namespace SmartMet
{
namespace GRIB2
{

typedef std::map<uint,Message*> Message_pmap;


class GribFile : public GRID::PhysicalGridFile
{
  public:

                    GribFile();
                    GribFile(const GribFile& other);
    virtual         ~GribFile();

    // ### Common methods for all file types

    GRID::GridFile* createGridFile();
    void            deleteUsers();
    T::FileType     getFileType() const;
    std::string     getFileTypeString() const;
    GRID::Message*  getMessageByIndex(std::size_t index);
    std::size_t     getNumberOfMessages();

    GRID::Message*  newMessage();
    GRID::Message*  newMessage(uint messageIndex,GRID::MessageInfo& messageInfo);
    void            addMessage(GRID::Message *message);
    void            addMessage(GRIB2::Message *message);

    void            clearCachedValues(uint hitsRequired,uint timePeriod) const;
    void            read(std::string filename);
    void            read(MemoryReader& memoryReader);
    void            write(std::string filename);
    void            write(DataWriter& dataWriter);
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

  private:

    T::Data_ptr_vec searchMessageLocations(MemoryReader& memoryReader);
    void            readMessage(MemoryReader& memoryReader,uint messageIndex);

    /*! \brief  The message object pointers. */
    Message_pmap    mMessages;
};

}  // namespace GRIB2
}  // namespace SmartMet
