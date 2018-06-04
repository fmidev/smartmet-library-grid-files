#pragma once

#include "../grid/PhysicalGridFile.h"
#include "Message.h"


namespace SmartMet
{
namespace GRIB2
{

class GribFile : public GRID::PhysicalGridFile
{
  public:

                        GribFile();
    virtual             ~GribFile();

    // ### Common methods for all file types

    void                deleteUsers();
    T::FileType         getFileType() const;
    std::string         getFileTypeString() const;
    GRID::Message*      getMessageByIndex(std::size_t index);
    std::size_t         getNumberOfMessages();
    void                print(std::ostream& stream,uint level,uint optionFlags) const;
    void                read(std::string filename);
    void                read(MemoryReader& memoryReader);

  private:

    T::Data_ptr_vec     searchMessageLocations(MemoryReader& memoryReader);
    void                readMessage(MemoryReader& memoryReader,uint messageIndex);

    /*! \brief  The message object pointers. */
    std::vector<Message*> mMessages;
};

}  // namespace GRID
}  // namespace SmartMet
