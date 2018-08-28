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



/*! \brief The constructor of the class. */

DataSection::DataSection()
{
  try
  {
    mMessage = nullptr;
    mFilePosition = 0;
    mSectionLength = 0;
    mFlags = 0;
    mBinaryScaleFactor = 0;
    mReferenceValue = 0;
    mBitsPerValue = 0;
    mDataPtr = nullptr;
    mDataSize = 0;
    mDataSizeMax = 0;
    mReleaseData = false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

DataSection::DataSection(const DataSection& other)
:GRID::MessageSection(other)
{
  try
  {
    mMessage = nullptr;
    mFilePosition = other.mFilePosition;
    mSectionLength = other.mSectionLength;
    mFlags = other.mFlags;
    mBinaryScaleFactor = other.mBinaryScaleFactor;
    mReferenceValue = other.mReferenceValue;
    mBitsPerValue = other.mBitsPerValue;
    mDataSize = other.mDataSize;
    mDataSizeMax = other.mDataSizeMax;
    mReleaseData = false;
    mDataPtr = nullptr;

    if (mDataSize >  0  &&  other.mDataPtr != nullptr)
    {
      mDataPtr = new uchar[mDataSize];
      memcpy(mDataPtr,other.mDataPtr,mDataSize);
      mReleaseData = true;
    }

    if (other.mDataDefinition)
      mDataDefinition.reset(other.mDataDefinition->createDataDefinition());
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Copy constructor failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

DataSection::~DataSection()
{
  try
  {
    if (mReleaseData &&  mDataPtr != nullptr)
    {
      delete mDataPtr;
      mDataPtr = nullptr;
    }
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





void DataSection::setMessagePtr(Message *message)
{
  try
  {
    mMessage = message;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool DataSection::setProperty(uint propertyId,long long value)
{
  try
  {
    switch (propertyId)
    {
      case Property::DataSection::Flags:
        setFlags(value);
        return true;

      case Property::DataSection::BinaryScaleFactor:
        setBinaryScaleFactor(value);
        return true;

      case Property::DataSection::ReferenceValue:
        setReferenceValue(value);
        return true;

      case Property::DataSection::BitsPerValue:
        setBitsPerValue(value);
        return true;

      case Property::DataSection::PackingMethod:
        //setPackingMethod(value);
        return true;
    }
    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
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
    attributeList.addAttribute(name,toString(mDataSize));

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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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

    mDataSize = mSectionLength - (memoryReader.getReadPosition() - rPos);
    mDataSizeMax = memoryReader.getDataSize() - (memoryReader.getReadPosition() - rPos);

    mDataPtr = memoryReader.getReadPtr();
    memoryReader.setReadPosition(rPos + mSectionLength);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataSection::setDataDefinition(T::CompressionMethod compressionMethod)
{
  try
  {
    DataDefinition *dataDefinition = nullptr;

    switch (compressionMethod)
    {
      case T::CompressionMethod::Undefined:
        break;

      case T::CompressionMethod::None:
        break;

      case T::CompressionMethod::GridPointData_SimplePacking:
        dataDefinition = new SimplePacking();
        mFlags = (mFlags & ~SphercicalHarmonicCoefficients);
        mFlags = (mFlags & ~ComplexPacking);
        break;

      case T::CompressionMethod::GridPointData_SimplePackingWithPreprocessing:
        break;

      case T::CompressionMethod::GridPointData_SimplePackingWithLogarithmicPreprocessing:
        break;

      case T::CompressionMethod::GridPointData_ComplexPacking:
        dataDefinition = new SecondOrderPacking();
        mFlags = (mFlags & ~SphercicalHarmonicCoefficients);
        mFlags = (mFlags | ComplexPacking);
        break;

      case T::CompressionMethod::GridPointData_ComplexPackingAndSpatialDifferencing:
        break;

      case T::CompressionMethod::GridPointData_IEEE_packing:
        break;

      case T::CompressionMethod::GridPointData_JPEG_2000:
        break;

      case T::CompressionMethod::GridPointData_PNG:
        break;

      case T::CompressionMethod::GridPointMatrixValues_SimplePacking:
        break;

      case T::CompressionMethod::SphericalHarmonics_SimplePacking:
        dataDefinition = new SphericalHarmonicsSimplePacking();
        mFlags = (mFlags | SphercicalHarmonicCoefficients);
        mFlags = (mFlags & ~ComplexPacking);
        break;

      case T::CompressionMethod::SphericalHarmonics_ComplexPacking:
        dataDefinition = new SphericalHarmonicsComplexPacking();
        mFlags = (mFlags | SphercicalHarmonicCoefficients);
        mFlags = (mFlags | ComplexPacking);
        break;

      case T::CompressionMethod::SpectralData_SimplePacking:
        break;

      case T::CompressionMethod::SpectralData_ComplexPacking:
        break;
    }

    if (dataDefinition == nullptr)
    {
      SmartMet::Spine::Exception exception(BCP,"Unsupported compression method!");
      exception.addParameter("CompressionMethod",std::to_string((uint)compressionMethod));
      throw exception;
    }

    mDataDefinition.reset(dataDefinition);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}







void DataSection::write(DataWriter& dataWriter)
{
  try
  {
    if (!mDataDefinition)
      throw SmartMet::Spine::Exception(BCP,"The data definition is missing!");

    mFilePosition = dataWriter.getWritePosition();

    mSectionLength = 0;

    dataWriter.write_uint24(mSectionLength);
    dataWriter << mFlags;
    dataWriter << mBinaryScaleFactor;
    dataWriter.write_ibmFloat(mReferenceValue);
    dataWriter << mBitsPerValue;

    mDataDefinition->write(dataWriter);

    if (mDataPtr != nullptr &&  mDataSize > 0)
      dataWriter.write_data(mDataPtr,mDataSize);

    // Updata the section length

    ulonglong fPos = dataWriter.getWritePosition();
    mSectionLength = fPos - mFilePosition;
    dataWriter.setWritePosition(mFilePosition);
    dataWriter.write_uint24(mSectionLength);
    dataWriter.setWritePosition(fPos);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::size_t DataSection::getDataSize() const
{
  try
  {
    return mDataSize;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::size_t DataSection::getDataSizeMax() const
{
  try
  {
    return mDataSizeMax;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataSection::setFlags(std::uint8_t flags)
{
  try
  {
    mFlags = flags;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataSection::setBinaryScaleFactor(std::int16_t binaryScaleFactor)
{
  try
  {
    mBinaryScaleFactor = binaryScaleFactor;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataSection::setReferenceValue(std::float_t referenceValue)
{
  try
  {
    mReferenceValue = referenceValue;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataSection::setBitsPerValue(std::uint8_t bitsPerValue)
{
  try
  {
    mBitsPerValue = bitsPerValue;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataSection::setData(T::Data_ptr data,std::size_t size)
{
  try
  {
    if (mReleaseData &&  mDataPtr != nullptr)
    {
      delete mDataPtr;
      mDataPtr = nullptr;
      mDataSize = 0;
    }

    mDataPtr = data;
    mDataSize = size;
    mReleaseData = true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataSection::setDataDefinition(DataDefinition *dataDefinition)
{
  try
  {
    mDataDefinition.reset(dataDefinition);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    stream << space(level) << "- dataSize          = " << toString(mDataSize) << "\n";

    if (mDataDefinition)
      mDataDefinition->print(stream,level+1,optionFlags);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet

