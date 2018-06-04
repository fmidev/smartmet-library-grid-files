#include "DataSection.h"
#include "Message.h"
#include "SecondOrderPacking.h"
#include "SimplePacking.h"
#include "SphericalHarmonicsSimplePacking.h"
#include "SphericalHarmonicsComplexPacking.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"
#include "../common/GeneralDefinitions.h"


namespace SmartMet
{
namespace GRIB1
{



/*! \brief The constructor of the class.

        \param message  A pointer to the message object.
*/

DataSection::DataSection(Message *message)
{
  try
  {
    mMessage = message;
    mFilePosition = 0;
    mSectionLength = 0;
    mFlags = 0;
    mBinaryScaleFactor = 0;
    mReferenceValue = 0;
    mBitsPerValue = 0;
    mDataPtr = NULL;
    mDataLength = 0;
    mDataLengthMax = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The destructor of the class. */

DataSection::~DataSection()
{
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current section.
*/

void DataSection::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
  try
  {
    char name[300];

    sprintf(name,"%sdata.binaryScaleFactor",prefix.c_str());
    attributeList.addAttribute(name,toString(mBinaryScaleFactor));

    sprintf(name,"%sdata.referenceValue",prefix.c_str());
    attributeList.addAttribute(name,toString(mReferenceValue));

    sprintf(name,"%sdata.bitsPerValue",prefix.c_str());
    attributeList.addAttribute(name,toString(mBitsPerValue));

    sprintf(name,"%sdata.size",prefix.c_str());
    attributeList.addAttribute(name,toString(mDataLength));

    sprintf(name,"%sdata.flags",prefix.c_str());
    attributeList.addAttribute(name,toString(mFlags));

    char val[1000];
    char *p = val;

    if (mFlags & SphercicalHarmonicCoefficients)
      p += sprintf(p,"Spherical harmonic coefficients;");
    else
      p += sprintf(p,"Grid-point data;");;

    if (mFlags & ComplexPacking)
      p += sprintf(p,"Complex or second-order packing;");
    else
      p += sprintf(p,"Simple packing;");;

    if (mFlags & IntegerValues)
      p += sprintf(p,"Integer values (in the original data) are represented;");
    else
      p += sprintf(p,"Floating point values (in the original data) are represented;");

    if (mFlags & AdditionalFlags)
      p += sprintf(p,"Additional flags used;");
    else
      p += sprintf(p,"No additional flags;");

    sprintf(name,"%sdata.flagsString",prefix.c_str());
    attributeList.addAttribute(name,val);

    sprintf(name,"%sdata.def.",prefix.c_str());
    if (mDataDefinition)
      mDataDefinition->getAttributeList(name,attributeList);

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void DataSection::read(MemoryReader& memoryReader)
{
  try
  {
    mFilePosition = memoryReader.getGlobalReadPosition();

    auto rPos = memoryReader.getReadPosition();

    mSectionLength = memoryReader.read_uint24();
    memoryReader >> mFlags;
    memoryReader >> mBinaryScaleFactor;
    mReferenceValue = memoryReader.read_ibmFloat();
    memoryReader >> mBitsPerValue;

    if ((mFlags & SphercicalHarmonicCoefficients) == 0)
    {
      if ((mFlags & ComplexPacking) == 0)
      {
        auto dataDefinition = new SimplePacking();
        mDataDefinition.reset(dataDefinition);
        dataDefinition->read(memoryReader);
      }
      else
      {
        auto dataDefinition = new SecondOrderPacking();
        mDataDefinition.reset(dataDefinition);
        dataDefinition->read(memoryReader);
      }
    }
    else
    {
      if ((mFlags & ComplexPacking) == 0)
      {
        auto dataDefinition = new SphericalHarmonicsSimplePacking();
        mDataDefinition.reset(dataDefinition);
        dataDefinition->read(memoryReader);
      }
      else
      {
        auto dataDefinition = new SphericalHarmonicsComplexPacking();
        mDataDefinition.reset(dataDefinition);
        dataDefinition->read(memoryReader);
      }
    }

    mDataLength = mSectionLength - (memoryReader.getReadPosition() - rPos);
    mDataLengthMax = memoryReader.getDataSize() - (memoryReader.getReadPosition() - rPos);

    mDataPtr = memoryReader.getReadPtr();
    memoryReader.setReadPosition(rPos + mSectionLength);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the section start position in the grib file.

        \return  The section's start position in the grib file.
*/

T::FilePosition DataSection::getFilePosition() const
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

std::uint32_t DataSection::getSectionLength() const
{
  try
  {
    return mSectionLength;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the name of the section. */

std::string DataSection::getSectionName() const
{
  try
  {
    return std::string("Data");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the section number. */

std::uint8_t DataSection::getSectionNumber() const
{
  try
  {
    return (std::uint8_t)Message::SectionNumber::data_section;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::Data_ptr DataSection::getDataPtr() const
{
  try
  {
    return mDataPtr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




std::uint8_t DataSection::getFlags() const
{
  try
  {
    return mFlags;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::int16_t DataSection::getBinaryScaleFactor() const
{
  try
  {
    return mBinaryScaleFactor;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::float_t DataSection::getReferenceValue() const
{
  try
  {
    return mReferenceValue;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::uint8_t DataSection::getBitsPerValue() const
{
  try
  {
    return mBitsPerValue;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::size_t DataSection::getDataSize() const
{
  try
  {
    return mDataLength;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::size_t DataSection::getDataSizeMax() const
{
  try
  {
    return mDataLengthMax;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool DataSection::getValueByIndex(uint index,T::ParamValue& value) const
{
  try
  {
    if (mDataDefinition)
      return mDataDefinition->getValueByIndex(mMessage,index,value);

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





PackingMethod DataSection::getPackingMethod() const
{
  try
  {
    if (mDataDefinition)
      return mDataDefinition->getPackingMethod();

    return PackingMethod::UNKNOWN;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




void DataSection::decodeValues(T::ParamValue_vec& decodedValues) const
{
  try
  {
    if (mDataDefinition)
      mDataDefinition->decodeValues(mMessage,decodedValues);
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

void DataSection::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "SECTION ["<< toString(getSectionNumber()) << "] " << getSectionName() << "\n";
    stream << space(level) << "- filePosition      = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- sectionLength     = " << toString(mSectionLength) << "\n";
    stream << space(level) << "- flags             = " << toString(mFlags) << "\n";

    if (mFlags & SphercicalHarmonicCoefficients)
      stream << space(level) << "   * Spherical harmonic coefficients\n";
    else
      stream << space(level) << "   * Grid-point data\n";

    if (mFlags & ComplexPacking)
      stream << space(level) << "   * Complex or second-order packing\n";
    else
      stream << space(level) << "   * Simple packing\n";

    if (mFlags & IntegerValues)
      stream << space(level) << "   * Integer values (in the original data) are represented\n";
    else
      stream << space(level) << "   * Floating point values (in the original data) are represented\n";

    if (mFlags & AdditionalFlags)
      stream << space(level) << "   * Additional flags used\n";
    else
      stream << space(level) << "   * No additional flags \n";

    stream << space(level) << "- binaryScaleFactor = " << toString(mBinaryScaleFactor) << "\n";
    stream << space(level) << "- referenceValue    = " << toString(mReferenceValue) << "\n";
    stream << space(level) << "- bitsPerValue      = " << toString(mBitsPerValue) << "\n";
    stream << space(level) << "- dataLength        = " << toString(mDataLength) << "\n";

    if (mDataDefinition)
      mDataDefinition->print(stream,level+1,optionFlags);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet

