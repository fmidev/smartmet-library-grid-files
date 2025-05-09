#include "TimeIntervalAggregateForecastImpl.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralFunctions.h"

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

TimeIntervalAggregateForecastImpl::TimeIntervalAggregateForecastImpl()
{
}





/*! \brief The copy constructor of the class. */

TimeIntervalAggregateForecastImpl::TimeIntervalAggregateForecastImpl(const TimeIntervalAggregateForecastImpl& other)
:TimeIntervalAggregateForecast(other)
{
}





/*! \brief The destructor of the class. */

TimeIntervalAggregateForecastImpl::~TimeIntervalAggregateForecastImpl()
{
}





/*! \brief The method creates a duplicate of the current object. */

ProductDefinition* TimeIntervalAggregateForecastImpl::createProductDefinition() const
{
  try
  {
    return (ProductDefinition*)new TimeIntervalAggregateForecastImpl(*this);
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

void TimeIntervalAggregateForecastImpl::read(MemoryReader& memoryReader)
{
  try
  {
    TimeIntervalAggregateForecast::read(memoryReader);
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

T::TimeString TimeIntervalAggregateForecastImpl::getForecastTime(T::TimeString referenceTime) const
{
  try
  {
    return countForecastStartTime(referenceTime,mParameter);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





/*! \brief The method returns the parameter level.

         \return   The parameter level.
*/

T::ParamLevel TimeIntervalAggregateForecastImpl::getGribParameterLevel() const
{
  try
  {
    if (mHorizontal.getScaledValueOfFirstFixedSurface())
      return *mHorizontal.getScaledValueOfFirstFixedSurface(); // * std::pow(10.0,*mHorizontal.getScaleFactorOfFirstFixedSurface());

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





/*! \brief The method returns the type of the parameter level.

         \return   The parameter level type (= enum value).
*/

T::ParamLevelId TimeIntervalAggregateForecastImpl::getGribParameterLevelId() const
{
  try
  {
    if (mHorizontal.getTypeOfFirstFixedSurface())
      return *mHorizontal.getTypeOfFirstFixedSurface();

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



}  // namespace GRIB2
}  // namespace SmartMet
