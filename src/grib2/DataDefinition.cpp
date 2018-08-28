#include "DataDefinition.h"
#include "../common/Exception.h"


namespace SmartMet
{
namespace GRIB2
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





uint DataDefinition::getTemplateNumber() const
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
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}


}  // namespace GRIB2
}  // namespace SmartMet
