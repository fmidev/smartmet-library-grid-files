#include "grib2/RepresentationSection.h"
#include "identification/GribDef.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "Message.h"

#include "grib2/implementation/GridDataRepresentationImpl.h"                       // "5.0"
#include "grib2/implementation/MatrixDataRepresentationImpl.h"                     // "5.1"
#include "grib2/implementation/ComplexGridDataRepresentationImpl.h"                // "5.2"
#include "grib2/implementation/ComplexDifferenceGridDataRepresentationImpl.h"      // "5.3"
#include "grib2/implementation/FloatingPointGridDataRepresentationImpl.h"          // "5.4"
#include "grib2/implementation/PreprocessedGridDataRepresentationImpl.h"           // "5.6"
#include "grib2/implementation/JpegGridDataRepresentationImpl.h"                   // "5.40"
#include "grib2/implementation/PngGridDataRepresentationImpl.h"                    // "5.41"
#include "grib2/implementation/SpectralGridDataRepresentationImpl.h"               // "5.42"
#include "grib2/implementation/SpectralDataRepresentationImpl.h"                   // "5.50"
#include "grib2/implementation/SphericalHarmonicsDataRepresentationImpl.h"         // "5.51"
#include "grib2/implementation/LogarithmicGridDataRepresentationImpl.h"            // "5.61"
#include "grib2/implementation/ComplexSphericalHarmonicsDataRepresentationImpl.h"  // "5.50000"

#include <iostream>

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class.

        \param message  A pointer to the message object.
*/

RepresentationSection::RepresentationSection(Message *message)
{
  try
  {
    mMessage = message;
    mFilePosition = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",NULL);
  }
}





/*! \brief The destructor of the class. */

RepresentationSection::~RepresentationSection()
{
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current section.
*/

void RepresentationSection::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
  try
  {
    char name[300];

    sprintf(name,"%srepresentation.numberOfValues",prefix.c_str());
    attributeList.addAttribute(name,toString(getNumberOfValues()));


    sprintf(name,"%srepresentation.dataRepresentationTemplateNumber",prefix.c_str());
    attributeList.addAttribute(name,toString(getDataRepresentationTemplateNumber()));

    sprintf(name,"%srepresentation.dataRepresentationString",prefix.c_str());
    attributeList.addAttribute(name,getDataRepresentationString());

    sprintf(name,"%srepresentation.def.",prefix.c_str());
    if (mRepresentationDefinition)
      mRepresentationDefinition->getAttributeList(name,attributeList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void RepresentationSection::read(MemoryReader& memoryReader)
{
  try
  {
    mFilePosition = memoryReader.getGlobalReadPosition();

    memoryReader >> mSectionLength;
    if (missing(mSectionLength))
    {
      SmartMet::Spine::Exception exception(BCP,"Section length cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-4));
      throw exception;
    }

    memoryReader >> mNumberOfSection;

    memoryReader >> mNumberOfValues;
    if (missing(mNumberOfValues))
    {
      SmartMet::Spine::Exception exception(BCP,"Number of values in section cannot be missing");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-4));
      throw exception;
    }

    memoryReader >> mDataRepresentationTemplateNumber;
    if (missing(mDataRepresentationTemplateNumber))
    {
      SmartMet::Spine::Exception exception(BCP,"Data representation template number cannot be missing");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-2));
      throw exception;
    }

    auto representationDefinition = createRepresentationDefinition(mDataRepresentationTemplateNumber);
    mRepresentationDefinition.reset(representationDefinition);
    representationDefinition->read(memoryReader);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the section start position in the grib file.

        \return  The section's start position in the grib file.
*/

T::FilePosition RepresentationSection::getFilePosition() const
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

std::uint32_t RepresentationSection::getSectionLength() const
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

std::string RepresentationSection::getSectionName() const
{
  try
  {
    return std::string("Representation");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the default section number. */

std::uint8_t RepresentationSection::getSectionNumber() const
{
  try
  {
    return (std::uint8_t)Message::SectionNumber::representation_section;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the section number that was read from the grib file. */

std::uint8_t RepresentationSection::getNumberOfSection() const
{
  try
  {
    // No missing check necessary here, we cannot know the section type without the number
    // anyway
    return *mNumberOfSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::uint32_t RepresentationSection::getNumberOfValues() const
{
  try
  {
    return *mNumberOfValues;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string RepresentationSection::getDataRepresentationString() const
{
  try
  {
    std::uint8_t tablesVersion = mMessage->getTablesVersion();
    return Identification::gribDef.getTableValue(2,tablesVersion,"5.0",getDataRepresentationTemplateNumber());
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::uint16_t RepresentationSection::getDataRepresentationTemplateNumber() const
{
  try
  {
    return *mDataRepresentationTemplateNumber;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool RepresentationSection::getValueByIndex(uint index,T::ParamValue& value) const
{
  try
  {
    if (mRepresentationDefinition)
      return mRepresentationDefinition->getValueByIndex(mMessage,index,value);

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void RepresentationSection::decodeValues(T::ParamValue_vec& decodedValues) const
{
  try
  {
    if (mRepresentationDefinition)
      mRepresentationDefinition->decodeValues(mMessage,decodedValues);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





RepresentationDefinition* RepresentationSection::createRepresentationDefinition(T::UInt16_opt number)
{
  try
  {
    // Unknown representation?
    if (missing(number))
      return nullptr;

    switch (*number)
    {
      case 0:
        return new GridDataRepresentationImpl();
      case 1:
        return new MatrixDataRepresentationImpl();
      case 2:
        return new ComplexGridDataRepresentationImpl();
      case 3:
        return new ComplexDifferenceGridDataRepresentationImpl();
      case 4:
        return new FloatingPointGridDataRepresentationImpl();
      case 6:
        return new PreprocessedGridDataRepresentationImpl();
      case 40:
        return new JpegGridDataRepresentationImpl();
      case 41:
        return new PngGridDataRepresentationImpl();
      case 42:
        return new SpectralGridDataRepresentationImpl();
      case 50:
        return new SpectralDataRepresentationImpl();
      case 51:
        return new SphericalHarmonicsDataRepresentationImpl();
      case 61:
        return new LogarithmicGridDataRepresentationImpl();
      case 50000:
        return new ComplexSphericalHarmonicsDataRepresentationImpl();
      case 40000:
        throw SmartMet::Spine::Exception(BCP,"Representation template 5.40000 not supported, use 5.40 instead!");
      case 40010:
        throw SmartMet::Spine::Exception(BCP,"Representation template 5.40010 not supported, use 5.41 instead!");
      case 50001:
        throw SmartMet::Spine::Exception(BCP,
            "Representation template 5.50001 not supported for lack of documentation!");
      case 50002:
        throw SmartMet::Spine::Exception(BCP,
            "Representation template 5.50002 not supported for lack of documentation!");
      default:
        throw SmartMet::Spine::Exception(BCP,"Unknown representation definition template number '" +
                                 std::to_string(static_cast<int>(*number)) + "'!");
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

void RepresentationSection::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "SECTION ["<< toString(getSectionNumber()) << "] " << getSectionName() << "\n";
    stream << space(level) << "- filePosition                     = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- sectionLength                    = " << toString(mSectionLength) << "\n";
    stream << space(level) << "- numberOfSection                  = " << toString(mNumberOfSection) << "\n";
    stream << space(level) << "- numberOfValues                   = " << toString(getNumberOfValues()) << "\n";
    stream << space(level) << "- dataRepresentationTemplateNumber = " << toString(getDataRepresentationTemplateNumber()) << "\n";
    stream << space(level) << "- dataRepresentationString         = " << getDataRepresentationString() << "\n";

    if (mRepresentationDefinition)
      mRepresentationDefinition->print(stream,level+1,optionFlags);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}  // namespace GRIB2
}  // namespace SmartMet
