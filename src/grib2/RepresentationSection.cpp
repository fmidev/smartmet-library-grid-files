#include "RepresentationSection.h"
#include "Message.h"
#include "../identification/GridDef.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"

#include "implementation/GridDataRepresentationImpl.h"                       // "5.0"
#include "implementation/MatrixDataRepresentationImpl.h"                     // "5.1"
#include "implementation/ComplexGridDataRepresentationImpl.h"                // "5.2"
#include "implementation/ComplexDifferenceGridDataRepresentationImpl.h"      // "5.3"
#include "implementation/FloatingPointGridDataRepresentationImpl.h"          // "5.4"
#include "implementation/PreprocessedGridDataRepresentationImpl.h"           // "5.6"
#include "implementation/JpegGridDataRepresentationImpl.h"                   // "5.40"
#include "implementation/PngGridDataRepresentationImpl.h"                    // "5.41"
#include "implementation/SpectralGridDataRepresentationImpl.h"               // "5.42"
#include "implementation/SpectralDataRepresentationImpl.h"                   // "5.50"
#include "implementation/SphericalHarmonicsDataRepresentationImpl.h"         // "5.51"
#include "implementation/LogarithmicGridDataRepresentationImpl.h"            // "5.61"
#include "implementation/ComplexSphericalHarmonicsDataRepresentationImpl.h"  // "5.50000"

#include <iostream>

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class.

        \param message  A pointer to the message object.
*/

RepresentationSection::RepresentationSection()
{
  try
  {
    mMessage = nullptr;
    mFilePosition = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

RepresentationSection::RepresentationSection(const RepresentationSection& other)
:GRID::MessageSection(other)
{
  try
  {
    mMessage = nullptr;
    mFilePosition = other.mFilePosition;
    mSectionLength = other.mSectionLength;
    mNumberOfSection = other.mNumberOfSection;
    mNumberOfValues = other.mNumberOfValues;
    mDataRepresentationTemplateNumber = other.mDataRepresentationTemplateNumber;

    if (other.mRepresentationDefinition)
    {
      RepresentationDefinition *def = other.mRepresentationDefinition->createRepresentationDefinition();
      mRepresentationDefinition.reset(def);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






void RepresentationSection::setMessagePtr(Message *message)
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





bool RepresentationSection::getProperty(uint propertyId,long long& value)
{
  try
  {
    switch (propertyId)
    {
      case Property::RepresentationSection::RepresentationTemplateNumber:
        value = *mDataRepresentationTemplateNumber;
        return true;
    }

    if (mRepresentationDefinition)
      return mRepresentationDefinition->getProperty(propertyId,value);

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool RepresentationSection::setProperty(uint propertyId,long long value)
{
  try
  {
    switch (propertyId)
    {
      case Property::RepresentationSection::RepresentationTemplateNumber:
        setRepresentationDefinition((std::uint16_t)value);
        return true;
    }

    if (mRepresentationDefinition)
      return mRepresentationDefinition->setProperty(propertyId,value);

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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

    if (mDataRepresentationTemplateNumber)
    {
      auto representationDefinition = createRepresentationDefinition(*mDataRepresentationTemplateNumber);
      mRepresentationDefinition.reset(representationDefinition);
      representationDefinition->read(memoryReader);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RepresentationSection::write(DataWriter& dataWriter)
{
  try
  {
    if (!mRepresentationDefinition)
      throw SmartMet::Spine::Exception(BCP,"Missing representation definition");

    if (missing(mNumberOfValues))
      throw SmartMet::Spine::Exception(BCP,"Number of values in section cannot be missing");

    mFilePosition = dataWriter.getWritePosition();
    mDataRepresentationTemplateNumber = mRepresentationDefinition->getTemplateNumber();
    mNumberOfSection = GRIB2::Message::SectionNumber::representation_section;

    dataWriter << mSectionLength;
    dataWriter << mNumberOfSection;
    dataWriter << mNumberOfValues;
    dataWriter << mDataRepresentationTemplateNumber;

    mRepresentationDefinition->write(dataWriter);

    ulonglong fPos = dataWriter.getWritePosition();
    mSectionLength = fPos - mFilePosition;
    dataWriter.setWritePosition(mFilePosition);
    dataWriter << mSectionLength;
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

T::FilePosition RepresentationSection::getFilePosition() const
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

std::uint32_t RepresentationSection::getSectionLength() const
{
  try
  {
    if (mSectionLength)
      return *mSectionLength;

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the section number that was read from the grib file. */

std::uint8_t RepresentationSection::getNumberOfSection() const
{
  try
  {
    // No missing check necessary here, we cannot know the section type without the number
    // anyway
    if (mNumberOfSection)
      return *mNumberOfSection;

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::uint32_t RepresentationSection::getNumberOfValues() const
{
  try
  {
    if (mNumberOfValues)
      return *mNumberOfValues;

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RepresentationSection::setNumberOfValues(std::uint32_t numOfValues)
{
  try
  {
    mNumberOfValues = numOfValues;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string RepresentationSection::getDataRepresentationString() const
{
  try
  {
    std::uint8_t tablesVersion = mMessage->getTablesVersion();
    return Identification::gridDef.getGribTableValue(2,tablesVersion,"5.0",getDataRepresentationTemplateNumber());
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RepresentationSection::encodeValues(Message *message,T::ParamValue_vec& values)
{
  try
  {
    if (!mRepresentationDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mRepresentationDefinition' attribute points to nullptr!");

    mRepresentationDefinition->encodeValues(mMessage,values);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





RepresentationDefinition_sptr RepresentationSection::getRepresentationDefinition()
{
  try
  {
    return mRepresentationDefinition;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RepresentationSection::setRepresentationDefinition(RepresentationDefinition *representationDefinition)
{
  try
  {
    if (representationDefinition == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'representationDefinition' parameter points to nullptr!");

    mDataRepresentationTemplateNumber = representationDefinition->getTemplateNumber();
    mRepresentationDefinition.reset(representationDefinition);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RepresentationSection::setRepresentationDefinition(std::uint16_t templateNumber)
{
  try
  {
    RepresentationDefinition *representationDefinition = createRepresentationDefinition(templateNumber);
    if (representationDefinition == nullptr)
    {
      SmartMet::Spine::Exception exception(BCP,"Unsupported template number!");
      exception.addParameter("Template number",std::to_string(templateNumber));
      throw exception;
    }

    mDataRepresentationTemplateNumber = templateNumber;
    mRepresentationDefinition.reset(representationDefinition);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





RepresentationDefinition* RepresentationSection::createRepresentationDefinition(std::uint16_t templateNumber)
{
  try
  {
    switch (templateNumber)
    {
      case Template::GridDataRepresentation:
        return new GridDataRepresentationImpl();

      case Template::MatrixDataRepresentation:
        return new MatrixDataRepresentationImpl();

      case Template::ComplexGridDataRepresentation:
        return new ComplexGridDataRepresentationImpl();

      case Template::ComplexDifferenceGridDataRepresentation:
        return new ComplexDifferenceGridDataRepresentationImpl();

      case Template::FloatingPointGridDataRepresentation:
        return new FloatingPointGridDataRepresentationImpl();

      case Template::PreprocessedGridDataRepresentation:
        return new PreprocessedGridDataRepresentationImpl();

      case Template::JpegGridDataRepresentation:
        return new JpegGridDataRepresentationImpl();

      case Template::PngGridDataRepresentation:
        return new PngGridDataRepresentationImpl();

      case Template::SpectralGridDataRepresentation:
        return new SpectralGridDataRepresentationImpl();

      case Template::SpectralDataRepresentation:
        return new SpectralDataRepresentationImpl();

      case Template::SphericalHarmonicsDataRepresentation:
        return new SphericalHarmonicsDataRepresentationImpl();

      case Template::LogarithmicGridDataRepresentation:
        return new LogarithmicGridDataRepresentationImpl();

      case Template::ComplexSphericalHarmonicsDataRepresentation:
        return new ComplexSphericalHarmonicsDataRepresentationImpl();
    }

    Spine::Exception exception(BCP,"Unknown representation definition template number!'");
    exception.addParameter("Template number",std::to_string(templateNumber));
    throw exception;
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}  // namespace GRIB2
}  // namespace SmartMet
