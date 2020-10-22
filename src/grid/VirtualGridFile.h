#pragma once

#include "GridFile.h"


namespace SmartMet
{
namespace GRID
{


// ====================================================================================
/*! \brief The main purpose of this class is ...
*/
// ====================================================================================


class VirtualGridFile : public GridFile
{
  public:
                        VirtualGridFile();
                        VirtualGridFile(VirtualGridFile *gridFile);
    virtual             ~VirtualGridFile();

    void                addMessage(Message *message);
    void                addPhysicalGridFile(GRID::GridFile_sptr physicalGridFile);

    Message*            getMessageByIndex(std::size_t index);
    virtual T::FileType getFileType() const;
    virtual std::string getFileTypeString() const;
    std::size_t         getNumberOfMessages();
    std::size_t         getNumberOfPhysicalGridFiles();
    GRID::GridFile_sptr getPhysicalGridFileByIndex(std::size_t index);

    virtual bool        isMemoryMapped() const;
    virtual bool        isPhysical() const;
    virtual bool        isVirtual() const;

    virtual void        mapToMemory();

    virtual void        print(std::ostream& stream,uint level,uint optionFlags) const;

  protected:

    MessagePtr_vec      mMessageList;
    GridFile_sptr_vec   mPhysicalGridFileList;
};


typedef VirtualGridFile* VirtualGridFilePtr;

}  // namespace GRID
}  // namespace SmartMet
