#include "BitmapSection.h"
#include "Message.h"
#include "../identification/GridDef.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"
#include "../common/BitArrayReader.h"

#include <iostream>


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class.

        \param message  A pointer to the message object.
*/

BitmapSection::BitmapSection(Message *message)
{
  try
  {
    mMessage = message;
    mFilePosition = 0;
    mBitmapDataPtr = NULL;
    mBitmapDataSizeInBytes = 0;
    mHash = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",NULL);
  }
}





/*! \brief The destructor of the class. */

BitmapSection::~BitmapSection()
{
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current section.
*/

void BitmapSection::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
  try
  {
    char name[300];
    std::uint8_t tablesVersion = mMessage->getTablesVersion();

    sprintf(name,"%sbitmap.indicator",prefix.c_str());
    attributeList.addAttribute(name,toString(getBitMapIndicator()));

    sprintf(name,"%sbitmap.indicatorString",prefix.c_str());
    attributeList.addAttribute(name,Identification::gridDef.getGribTableValue(2,tablesVersion,"6.0",getBitMapIndicator()));

    sprintf(name,"%sbitmap.sizeInBytes",prefix.c_str());
    attributeList.addAttribute(name,toString(mBitmapDataSizeInBytes));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void BitmapSection::read(MemoryReader& memoryReader)
{
  try
  {
    const std::size_t section_fixed_size = 6;
    mBitmapDataPtr = nullptr;
    mBitmapDataSizeInBytes = 0;

    mFilePosition = memoryReader.getGlobalReadPosition();

    memoryReader >> mSectionLength;
    if (missing(mSectionLength))
    {
      SmartMet::Spine::Exception exception(BCP,"Section length cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-4));
      throw exception;
    }

    memoryReader >> mNumberOfSection;
    memoryReader >> mBitmapIndicator;


    if (!missing(mBitmapIndicator))
    {
      if (*mBitmapIndicator >= 1 && *mBitmapIndicator <= 253)
        throw SmartMet::Spine::Exception(BCP,"Local GRIB bitmaps are not supported");

      if (*mBitmapIndicator == 0)
        mBitmapDataPtr = memoryReader.getReadPtr();

      mBitmapDataSizeInBytes = *mSectionLength - section_fixed_size;
      memoryReader.read_null(mBitmapDataSizeInBytes);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the section start position in the grib file.

        \return  The section's start position in the grib file.
*/

T::FilePosition BitmapSection::getFilePosition() const
{
  try
  {
    return mFilePosition;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the length of the section (in the grib file).

         \return  The length of the section expressed in bytes.
*/

std::uint32_t BitmapSection::getSectionLength() const
{
  try
  {
    return *mSectionLength;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the name of the section. */

std::string BitmapSection::getSectionName() const
{
  try
  {
    return std::string("Bitmap");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the default section number. */

std::uint8_t BitmapSection::getSectionNumber() const
{
  try
  {
    return (std::uint8_t)Message::SectionNumber::bitmap_section;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




/*! \brief The method returns the section number that was read from the grib file. */

std::uint8_t BitmapSection::getNumberOfSection() const
{
  try
  {
    // No missing check necessary here, we cannot know the section type without the number anyway
    return *mNumberOfSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method bitmap indicator (see Code Table 6.0).

        \return  The bitmap indicator.
*/

T::UInt8_opt BitmapSection::getBitMapIndicator() const
{
  try
  {
    // Is missing if there is no bit map
    return mBitmapIndicator;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the pointer to the (memory mapped) bitmap data.

        \return  The pointer to the bitmap data.
*/

T::Data_ptr BitmapSection::getBitmapDataPtr() const
{
  try
  {
    return mBitmapDataPtr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the bitmap size in bytes.

        \return  The bitmap size in bytes.
*/

std::size_t BitmapSection::getBitmapDataSizeInBytes() const
{
  try
  {
    return mBitmapDataSizeInBytes;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





long long BitmapSection::getHash()
{
  try
  {
    if (mHash != 0)
      return mHash;

    for (std::size_t t=0; t<mBitmapDataSizeInBytes; t++)
      mHash += (long long)(t+ mBitmapDataPtr[t] * t);

    return mHash;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void BitmapSection::getIndexVector(uint numOfValues,T::IndexVector& indexVector)
{
  try
  {
    int idx = 0;
    BitArrayReader bitmapReader(mBitmapDataPtr,mBitmapDataSizeInBytes*8);
    for (uint i=0; i<numOfValues; i++)
    {
      if (bitmapReader.readBit())
      {
        indexVector.push_back(idx);
        idx++;
      }
      else
      {
        indexVector.push_back(-1);
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void BitmapSection::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    std::uint8_t tablesVersion = mMessage->getTablesVersion();

    stream << space(level) << "SECTION ["<< toString(getSectionNumber()) << "] " << getSectionName() << "\n";
    stream << space(level) << "- filePosition        = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- sectionLength       = " << toString(mSectionLength) << "\n";
    stream << space(level) << "- numberOfSection     = " << toString(mNumberOfSection) << "\n";
    stream << space(level) << "- bitMapIndicator     = " << toString(getBitMapIndicator()) << " : " << Identification::gridDef.getGribTableValue(2,tablesVersion,"6.0",getBitMapIndicator()) << "\n";
    stream << space(level) << "- bitMapLengthInBytes = " << toString(mBitmapDataSizeInBytes) << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}

}  // namespace GRIB2
}  // namespace SmartMet
