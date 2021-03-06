#include "AerosolOpticalPropertiesProductImpl.h"
#include <macgyver/Exception.h>


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

AerosolOpticalPropertiesProductImpl::AerosolOpticalPropertiesProductImpl()
{
}





/*! \brief The copy constructor of the class. */

AerosolOpticalPropertiesProductImpl::AerosolOpticalPropertiesProductImpl(const AerosolOpticalPropertiesProductImpl& other)
:AerosolOpticalPropertiesProduct(other)
{
}





/*! \brief The destructor of the class. */

AerosolOpticalPropertiesProductImpl::~AerosolOpticalPropertiesProductImpl()
{
}





/*! \brief The method creates a duplicate of the current object. */

ProductDefinition* AerosolOpticalPropertiesProductImpl::createProductDefinition() const
{
  try
  {
    return (ProductDefinition*)new AerosolOpticalPropertiesProductImpl(*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method reads and initializes all data related to the current object.
    The purpose of this method is to get access to the read operation that takes place
    in the parent class (which is automatically generated). This means in practice that
    we first call the read operation in the parent class. After that we can ensure that
    the result of the read operation was correct (i.e. attribute values are valid, etc).
    We can also modify or update some attribute values if needed.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void AerosolOpticalPropertiesProductImpl::read(MemoryReader& memoryReader)
{
  try
  {
    AerosolOpticalPropertiesProduct::read(memoryReader);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the start time of the current forecast data. In some cases
    the reference time is needed for calculating the actual forecast time.

        \param referenceTime  The possible reference time.
        \return               The forecast time.
*/

T::TimeString AerosolOpticalPropertiesProductImpl::getForecastTime(T::TimeString referenceTime) const
{
  throw Fmi::Exception(BCP, "Not implemented!");
}





/*! \brief The method returns the parameter level.

         \return   The parameter level.
*/

T::ParamLevel AerosolOpticalPropertiesProductImpl::getGribParameterLevel() const
{
  throw Fmi::Exception(BCP, "Not implemented!");
}





/*! \brief The method returns the type of the parameter level.

         \return   The parameter level type (= enum value).
*/

T::ParamLevelId AerosolOpticalPropertiesProductImpl::getGribParameterLevelId() const
{
  throw Fmi::Exception(BCP, "Not implemented!");
}


}  // namespace GRIB2
}  // namespace SmartMet
