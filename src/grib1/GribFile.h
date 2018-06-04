#pragma once

#include "Message.h"
#include "../grid/PhysicalGridFile.h"


namespace SmartMet
{
namespace GRIB1
{

// ====================================================================================
/*! \brief This class implements functionality that is needed in order to access
    data in a GRIB 1 file.

    The class is inherited from the GRID::GribFile class, which offers a lot of general
    methods to access GRIB data. This class implements only such methods that cannot
    be implemented in its parent class.
*/
// ====================================================================================

class GribFile : public GRID::PhysicalGridFile
{
  public:

                        GribFile();
    virtual             ~GribFile();

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

}  // namespace GRIB1
}  // namespace SmartMet
