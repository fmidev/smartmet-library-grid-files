#include "DataDefinition.h"
#include "Message.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"
#include "../common/GeneralDefinitions.h"


namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class. */

DataDefinition::DataDefinition()
{
}





/*! \brief The copy constructor of the class. */

DataDefinition::DataDefinition(const DataDefinition& other)
{
}





/*! \brief The destructor of the class. */

DataDefinition::~DataDefinition()
{
}





void DataDefinition::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
}





PackingMethod DataDefinition::getPackingMethod() const
{
  try
  {
    return PackingMethod::UNKNOWN;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




bool DataDefinition::getValueByIndex(Message *message,uint index,T::ParamValue& value) const
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




/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void DataDefinition::read(MemoryReader& memoryReader)
{
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

void DataDefinition::write(DataWriter& dataWriter)
{
}





DataDefinition* DataDefinition::createDataDefinition() const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





void DataDefinition::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





void DataDefinition::encodeValues(Message *message,T::ParamValue_vec& values)
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void DataDefinition::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "* DataDefiniton\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




}
}
