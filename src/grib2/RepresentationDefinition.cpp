#include "RepresentationDefinition.h"
#include "Properties.h"
#include "../common/Exception.h"


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
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RepresentationDefinition::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
}





uint RepresentationDefinition::getTemplateNumber() const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}






bool RepresentationDefinition::getValueByIndex(Message *message,uint index,T::ParamValue& value) const
{
  try
  {
    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





void RepresentationDefinition::encodeValues(Message *message,T::ParamValue_vec& values)
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





void RepresentationDefinition::read(MemoryReader& memoryReader)
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





void RepresentationDefinition::write(DataWriter& dataWriter)
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void RepresentationDefinition::print(std::ostream& stream,uint level,uint optionFlags) const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}


}  // namespace GRIB2
}  // namespace SmartMet
