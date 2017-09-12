#include "ProcessedCrossSectionProductImpl.h"
#include "common/Exception.h"


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

ProcessedCrossSectionProductImpl::ProcessedCrossSectionProductImpl()
{
}





/*! \brief The destructor of the class. */

ProcessedCrossSectionProductImpl::~ProcessedCrossSectionProductImpl()
{
}





/*! \brief The method reads and initializes all data related to the current object.
    The purpose of this method is to get access to the read operation that takes place
    in the parent class (which is automatically generated). This means in practice that
    we first call the read operation in the parent class. After that we can ensure that
    the result of the read operation was correct (i.e. attribute values are valid, etc).
    We can also modify or update some attribute values if needed.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void ProcessedCrossSectionProductImpl::read(MemoryReader& memoryReader)
{
  try
  {
    ProcessedCrossSectionProduct::read(memoryReader);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the start time of the current forecast data. In some cases
    the reference time is needed for calculating the actual forecast time.

        \param referenceTime  The possible reference time.
        \return               The forecast time.
*/

T::TimeString ProcessedCrossSectionProductImpl::getForecastTime(T::TimeString referenceTime) const
{
  throw SmartMet::Spine::Exception(BCP, "Not implemented!");
}





/*! \brief The method returns the parameter level.

         \return   The parameter level.
*/

T::ParamLevel ProcessedCrossSectionProductImpl::getGribParameterLevel() const
{
  throw SmartMet::Spine::Exception(BCP, "Not implemented!");
}





/*! \brief The method returns the type of the parameter level.

         \return   The parameter level type (= enum value).
*/

T::ParamLevelId ProcessedCrossSectionProductImpl::getGribParameterLevelId() const
{
  throw SmartMet::Spine::Exception(BCP, "Not implemented!");
}



}  // namespace GRIB2
}  // namespace SmartMet
