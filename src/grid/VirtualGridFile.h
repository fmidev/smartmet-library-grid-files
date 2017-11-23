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

    virtual void        addPhysicalGridFile(GRID::GridFile_sptr physicalGridFile);

    virtual void        addMessage(Message *message);
    virtual Message*    getMessageByIndex(std::size_t index);
    virtual std::size_t getNumberOfMessages();

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



}  // namespace GRID
}  // namespace SmartMet
