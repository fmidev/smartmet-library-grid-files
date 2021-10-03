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
                ~VirtualGridFile() override;

    void                addMessage(Message *message) override;
    void                addPhysicalGridFile(GRID::GridFile_sptr physicalGridFile);

    Message*            getMessageByIndex(std::size_t index) override;
    T::FileType getFileType() const override;
    std::string getFileTypeString() const override;
    std::size_t         getNumberOfMessages() override;
    std::size_t         getNumberOfPhysicalGridFiles();
    GRID::GridFile_sptr getPhysicalGridFileByIndex(std::size_t index);

    bool        isMemoryMapped() const override;
    bool        isPhysical() const override;
    bool        isVirtual() const override;

    void        mapToMemory() override;

    void        print(std::ostream& stream,uint level,uint optionFlags) const override;

  protected:

    MessagePtr_vec      mMessageList;
    GridFile_sptr_vec   mPhysicalGridFileList;
};


using VirtualGridFilePtr = VirtualGridFile *;

}  // namespace GRID
}  // namespace SmartMet
