#include "RepresentationDefinition.h"
#include "Properties.h"
#include <macgyver/Exception.h>


namespace SmartMet
{
namespace GRIB2
{


RepresentationDefinition::RepresentationDefinition()
{
}





/*! \brief The copy constructor of the class. */

RepresentationDefinition::RepresentationDefinition(const RepresentationDefinition& other)
{
}





/*! \brief The destructor of the class. */

RepresentationDefinition::~RepresentationDefinition()
{
}





RepresentationDefinition* RepresentationDefinition::createRepresentationDefinition() const
{
  throw Fmi::Exception(BCP,"Not implemented!");
}





/*! \brief The method is used for fetching a (long long ) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the requested property is returned in this parameter.
        \return            The method returns true if the value of the requested property was found.
*/

bool RepresentationDefinition::getProperty(uint propertyId,long long& value)
{
  try
  {
    if (getProperty_Packing(propertyId,value))
      return true;

    if (getProperty_OriginalValues(propertyId,value))
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool RepresentationDefinition::getProperty_Packing(uint propertyId,long long& value)
{
  try
  {
    PackingSettings *packing = getPacking();
    if (packing == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::RepresentationSection::Packing::ReferenceValue:
      {
        value = packing->getReferenceValue();
        return true;
      }
      break;

      case Property::RepresentationSection::Packing::BinaryScaleFactor:
        value = *packing->getBinaryScaleFactor();
        return true;

      case Property::RepresentationSection::Packing::DecimalScaleFactor:
        value = *packing->getDecimalScaleFactor();
        return true;

      case Property::RepresentationSection::Packing::BitsPerValue:
        value = *packing->getBitsPerValue();
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool RepresentationDefinition::getProperty_OriginalValues(uint propertyId,long long& value)
{
  try
  {
    OriginalValuesSettings *originalValues = getOriginalValues();
    if (originalValues == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::RepresentationSection::OriginalValues::TypeOfOriginalFieldValues:
        value = *originalValues->getTypeOfOriginalFieldValues();
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a (long long) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool RepresentationDefinition::setProperty(uint propertyId,long long value)
{
  try
  {
    if (setProperty_Packing(propertyId,value))
      return true;

    if (setProperty_OriginalValues(propertyId,value))
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool RepresentationDefinition::setProperty_Packing(uint propertyId,long long value)
{
  try
  {
    PackingSettings *packing = getPacking();
    if (packing == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::RepresentationSection::Packing::ReferenceValue:
        packing->setReferenceValue(value);
        return true;

      case Property::RepresentationSection::Packing::BinaryScaleFactor:
        packing->setBinaryScaleFactor(value);
        return true;

      case Property::RepresentationSection::Packing::DecimalScaleFactor:
        packing->setDecimalScaleFactor(value);
        return true;

      case Property::RepresentationSection::Packing::BitsPerValue:
        packing->setBitsPerValue(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool RepresentationDefinition::setProperty_OriginalValues(uint propertyId,long long value)
{
  try
  {
    OriginalValuesSettings *originalValues = getOriginalValues();
    if (originalValues == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::RepresentationSection::OriginalValues::TypeOfOriginalFieldValues:
        originalValues->setTypeOfOriginalFieldValues(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void RepresentationDefinition::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
}





uint RepresentationDefinition::getTemplateNumber() const
{
  throw Fmi::Exception(BCP,"Not implemented!");
}






bool RepresentationDefinition::getValueByIndex(Message *message,uint index,T::ParamValue& value) const
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





PackingSettings* RepresentationDefinition::getPacking() const
{
  return nullptr;
}





OriginalValuesSettings*  RepresentationDefinition::getOriginalValues() const
{
  return nullptr;
}





void RepresentationDefinition::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  throw Fmi::Exception(BCP,"Not implemented!");
}





void RepresentationDefinition::encodeValues(Message *message,T::ParamValue_vec& values)
{
  throw Fmi::Exception(BCP,"Not implemented!");
}





/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void RepresentationDefinition::read(MemoryReader& memoryReader)
{
  throw Fmi::Exception(BCP,"Not implemented!");
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

void RepresentationDefinition::write(DataWriter& dataWriter)
{
  throw Fmi::Exception(BCP,"Not implemented!");
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void RepresentationDefinition::print(std::ostream& stream,uint level,uint optionFlags) const
{
  throw Fmi::Exception(BCP,"Not implemented!");
}


}  // namespace GRIB2
}  // namespace SmartMet
