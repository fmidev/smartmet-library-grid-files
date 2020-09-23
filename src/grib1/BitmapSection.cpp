#include "BitmapSection.h"
#include "Message.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"
#include "../common/GeneralDefinitions.h"
#include "../common/BitArrayReader.h"


namespace SmartMet
{
namespace GRIB1
{



/*! \brief The constructor of the class. */

BitmapSection::BitmapSection()
{
  try
  {
    mMessage = nullptr;
    mFilePosition = 0;
    mSectionLength = 0;
    mNumberOfUnusedBits = 0;
    mTableReference = 0;
    mReleaseData = false;
    mBitmapDataPtr = nullptr;
    mBitmapDataSizeInBytes = 0;
    mHash = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

BitmapSection::BitmapSection(const BitmapSection& other)
:GRID::MessageSection(other)
{
  try
  {
    mMessage = nullptr;
    mFilePosition = other.mFilePosition;
    mSectionLength = other.mSectionLength;
    mNumberOfUnusedBits = other.mNumberOfUnusedBits;
    mTableReference = other.mTableReference;
    mBitmapDataSizeInBytes = other.mBitmapDataSizeInBytes;
    mHash = other.mHash;
    mReleaseData = false;
    mBitmapDataPtr = nullptr;

    if (other.mBitmapDataSizeInBytes > 0  &&  other.mBitmapDataPtr != nullptr)
    {
      mBitmapDataPtr = new uchar[mBitmapDataSizeInBytes];
      memcpy(mBitmapDataPtr,other.mBitmapDataPtr,mBitmapDataSizeInBytes);
      mReleaseData = true;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Copy constructor failed",nullptr);
  }
}





/*! \brief The destructor of the class. */

BitmapSection::~BitmapSection()
{
  try
  {
    if (mReleaseData &&  mBitmapDataPtr != nullptr)
    {
      delete mBitmapDataPtr;
      mBitmapDataPtr = nullptr;
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current section.
*/

void BitmapSection::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
  try
  {
    char name[300];

    sprintf(name,"%sbitmap.numberOfUnusedBits",prefix.c_str());
    attributeList.addAttribute(name,toString(mNumberOfUnusedBits));

    sprintf(name,"%sbitmap.sizeInBytes",prefix.c_str());
    attributeList.addAttribute(name,toString(mBitmapDataSizeInBytes));

    sprintf(name,"%sbitmap.tableReference",prefix.c_str());
    attributeList.addAttribute(name,toString(mTableReference));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the pointer to the Message -object in which the current section
    object belongs to. This helps the object to reference information in other sections.

        \param message    The Message -object pointer.
*/

void BitmapSection::setMessagePtr(Message *message)
{
  try
  {
    mMessage = message;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void BitmapSection::read(MemoryReader& memoryReader)
{
  try
  {
    mFilePosition = memoryReader.getGlobalReadPosition();

    auto rPos = memoryReader.getReadPosition();

    mSectionLength = memoryReader.read_uint24();
    memoryReader >> mNumberOfUnusedBits;
    memoryReader >>  mTableReference;
    mBitmapDataPtr = memoryReader.getReadPtr();

    mBitmapDataSizeInBytes = mSectionLength - (memoryReader.getReadPosition() - rPos);

    memoryReader.setReadPosition(rPos + mSectionLength);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

void BitmapSection::write(DataWriter& dataWriter)
{
  try
  {
    mFilePosition = dataWriter.getWritePosition();

    mSectionLength = 6 + mBitmapDataSizeInBytes;

    dataWriter.write_uint24(mSectionLength);
    dataWriter << mNumberOfUnusedBits;
    dataWriter << mTableReference;

    if (mBitmapDataPtr != nullptr  && mBitmapDataSizeInBytes > 0)
      dataWriter.write_data(mBitmapDataPtr,mBitmapDataSizeInBytes);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the length of the section (in the grib file).

         \return  The length of the section expressed in bytes.
*/

std::uint32_t BitmapSection::getSectionLength() const
{
  try
  {
    return mSectionLength;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the section number. */

std::uint8_t BitmapSection::getSectionNumber() const
{
  try
  {
    return (std::uint8_t)Message::SectionNumber::bitmap_section;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the data pointer to the bitmap. */

T::Data_ptr BitmapSection::getBitmapDataPtr() const
{
  try
  {
    return mBitmapDataPtr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the bitmap data size in bytes. */

std::size_t BitmapSection::getBitmapDataSizeInBytes() const
{
  try
  {
    return mBitmapDataSizeInBytes;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





long long BitmapSection::getHash()
{
  try
  {
    if (mHash != 0)
      return mHash;

    for (std::size_t t=0; t<mBitmapDataSizeInBytes; t++)
      mHash += (long long)(t + mBitmapDataPtr[t] * t);

    return mHash;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void BitmapSection::setNumberOfUnusedBits(std::uint8_t unusedBits)
{
  try
  {
    mNumberOfUnusedBits = unusedBits;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void BitmapSection::setTableReference(std::uint16_t reference)
{
  try
  {
    mTableReference = reference;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the bitmap data. The data will be released when the object
 * is distroyed.

        \param data         Pointer to the bitmap data.
        \param size         Size of the bitmap data in bytes.
*/

void BitmapSection::setBitmapData(T::Data_ptr data,std::size_t size)
{
  try
  {
    if (mReleaseData &&  mBitmapDataPtr != nullptr)
    {
      delete mBitmapDataPtr;
      mBitmapDataPtr = nullptr;
      mBitmapDataSizeInBytes = 0;
    }

    mBitmapDataPtr = data;
    mBitmapDataSizeInBytes = size;
    mReleaseData = true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    stream << space(level) << "SECTION ["<< toString(getSectionNumber()) << "] " << getSectionName() << "\n";
    stream << space(level) << "- filePosition       = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- sectionLength      = " << toString(mSectionLength) << "\n";
    stream << space(level) << "- numberOfUnusedBits = " << toString(mNumberOfUnusedBits) << "\n";
    stream << space(level) << "- bitmapSizeInBytes  = " << toString(mBitmapDataSizeInBytes) << "\n";
    stream << space(level) << "- tableReference     = " << toString(mTableReference) << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}
}
