#include "TimeIntervalCategoricalForecastImpl.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

TimeIntervalCategoricalForecastImpl::TimeIntervalCategoricalForecastImpl()
{
}





/*! \brief The destructor of the class. */

TimeIntervalCategoricalForecastImpl::~TimeIntervalCategoricalForecastImpl()
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

void TimeIntervalCategoricalForecastImpl::read(MemoryReader& memoryReader)
{
  try
  {
    TimeIntervalCategoricalForecast::read(memoryReader);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the parameter level.

         \return   The parameter level.
*/

T::ParamLevel TimeIntervalCategoricalForecastImpl::getGribParameterLevel() const
{
  try
  {
    if (mHorizontal.getScaledValueOfFirstFixedSurface())
      return *mHorizontal.getScaledValueOfFirstFixedSurface();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}





/*! \brief The method returns the type of the parameter level.

         \return   The parameter level type (= enum value).
*/

T::ParamLevelId TimeIntervalCategoricalForecastImpl::getGribParameterLevelId() const
{
  try
  {
    if (mHorizontal.getScaledValueOfFirstFixedSurface())
      return *mHorizontal.getTypeOfFirstFixedSurface();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}



}  // namespace GRIB2
}  // namespace SmartMet