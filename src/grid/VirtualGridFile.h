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

    void                addPhysicalGridFile(GRID::GridFile_sptr physicalGridFile);
    std::size_t         getNumberOfPhysicalGridFiles();
    GRID::GridFile_sptr getPhysicalGridFileByIndex(std::size_t index);

    void                addMessage(Message *message);
    Message*            getMessageByIndex(std::size_t index);
    std::size_t         getNumberOfMessages();

    virtual T::FileType getFileType() const;
    virtual std::string getFileTypeString() const;

    virtual bool        isPhysical() const;
    virtual bool        isVirtual() const;
    virtual bool        isMemoryMapped() const;
    virtual void        mapToMemory();

    virtual void        print(std::ostream& stream,uint level,uint optionFlags) const;

  protected:

    MessagePtr_vec      mMessageList;

    std::vector<GRID::GridFile_sptr> mPhysicalGridFileList;
};


typedef VirtualGridFile* VirtualGridFilePtr;

}  // namespace GRID
}  // namespace SmartMet
