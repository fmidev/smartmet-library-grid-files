#include "VirtualGridFile.h"


namespace SmartMet
{
namespace GRID
{


VirtualGridFile::VirtualGridFile()
{
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





VirtualGridFile::VirtualGridFile(VirtualGridFile *gridFile)
:GridFile(gridFile)
{
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





VirtualGridFile::~VirtualGridFile()
{
  try
  {
    for (auto it = mMessageList.begin(); it != mMessageList.begin(); ++it)
      delete *it;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





void VirtualGridFile::addPhysicalGridFile(GRID::GridFile_sptr physicalGridFile)
{
  try
  {
    mPhysicalGridFileList.emplace_back(physicalGridFile);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::size_t VirtualGridFile::getNumberOfPhysicalGridFiles()
{
  try
  {
    return mPhysicalGridFileList.size();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





GRID::GridFile_sptr VirtualGridFile::getPhysicalGridFileByIndex(std::size_t index)
{
  try
  {
    return mPhysicalGridFileList[index];
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool VirtualGridFile::isMemoryMapped() const
{
  try
  {
    for (auto it = mPhysicalGridFileList.begin(); it != mPhysicalGridFileList.end(); ++it)
    {
      if (!(*it)->isMemoryMapped())
        return false;
    }

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void VirtualGridFile::mapToMemory()
{
  try
  {
    for (auto it = mPhysicalGridFileList.begin(); it != mPhysicalGridFileList.end(); ++it)
    {
      (*it)->mapToMemory();
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool VirtualGridFile::isPhysical() const
{
  try
  {
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




bool VirtualGridFile::isVirtual() const
{
  try
  {
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void VirtualGridFile::addMessage(Message *message)
{
  try
  {
    mMessageList.emplace_back(message);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





Message* VirtualGridFile::getMessageByIndex(std::size_t index)
{
  try
  {
    if (index < mMessageList.size())
      return mMessageList[index];

    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::size_t VirtualGridFile::getNumberOfMessages()
{
  try
  {
    return mMessageList.size();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief This method can be used for finding out the type of the file. The child classes
    should override this method.

        \return   The type of the file (expressed as an enum value).
*/

T::FileType VirtualGridFile::getFileType() const
{
  try
  {
    return T::FileTypeValue::Virtual;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the type of the file expressed as a string. The child
    classes should override this method.

        \return   The type of the file (expressed as a string).
*/

std::string VirtualGridFile::getFileTypeString() const
{
  try
  {
    return std::string("Virtual");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void VirtualGridFile::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << "VirtualGridFile\n";
    GridFile::print(stream,level+1,optionFlags);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



}  // namespace GRID
}  // namespace SmartMet
