#include "RepresentationDefinition.h"
#include "common/Exception.h"


namespace SmartMet
{
namespace GRIB2
{


RepresentationDefinition::RepresentationDefinition()
{
}





/*! \brief The destructor of the class. */

RepresentationDefinition::~RepresentationDefinition()
{
}





void RepresentationDefinition::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
}





bool RepresentationDefinition::getValueByIndex(Message *message,uint index,T::ParamValue& value) const
{
  try
  {
    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void RepresentationDefinition::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





void RepresentationDefinition::read(MemoryReader& memoryReader)
{
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
