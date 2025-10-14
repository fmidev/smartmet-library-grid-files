#include "AggregateAtmosphericChemicalProductImpl.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralFunctions.h"


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

AggregateAtmosphericChemicalProductImpl::AggregateAtmosphericChemicalProductImpl()
{
}





/*! \brief The copy constructor of the class. */

AggregateAtmosphericChemicalProductImpl::AggregateAtmosphericChemicalProductImpl(const AggregateAtmosphericChemicalProductImpl& other)
:AggregateAtmosphericChemicalProduct(other)
{
}





/*! \brief The destructor of the class. */

AggregateAtmosphericChemicalProductImpl::~AggregateAtmosphericChemicalProductImpl()
{
}





/*! \brief The method creates a duplicate of the current object. */

ProductDefinition* AggregateAtmosphericChemicalProductImpl::createProductDefinition() const
{
  try
  {
    return (ProductDefinition*)new AggregateAtmosphericChemicalProductImpl(*this);
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

void AggregateAtmosphericChemicalProductImpl::read(MemoryReader& memoryReader)
{
  try
  {
    AggregateAtmosphericChemicalProduct::read(memoryReader);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





const T::UInt8_opt AggregateAtmosphericChemicalProductImpl::getGribParameterCategory() const
{
  try
  {
    return mParameterChemical.getParameterCategory();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





const T::UInt8_opt AggregateAtmosphericChemicalProductImpl::getGribParameterNumber() const
{
  try
  {
    return mParameterChemical.getParameterNumber();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





T::UInt8_opt AggregateAtmosphericChemicalProductImpl::getGeneratingProcessIdentifier() const
{
  try
  {
    return mParameterChemical.getGeneratingProcessIdentifier();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}




T::TimeString AggregateAtmosphericChemicalProductImpl::countForecastStartTime(T::TimeString referenceTime) const
{
  try
  {
    T::TimeStamp refTime = toTimeStamp(referenceTime);
    T::TimeStamp tt = refTime;

    auto forecastTimeP = mParameterChemical.getForecastTime();
    if (!forecastTimeP)
    {
      throw Fmi::Exception(BCP, "The 'mParameterChemical.forecastTime' value not defined!");
    }

    auto indicator = mParameterChemical.getIndicatorOfUnitOfTimeRange();
    if (!indicator)
      throw Fmi::Exception(BCP, "The 'mParameterChemical.indicatorOfUnitOfTimeRange' value not defined!");

    int ft = *forecastTimeP;
    int forecastTime = ft;
    if (ft < 0)
      forecastTime = -ft;

    Fmi::TimeDuration dt;

    switch (*indicator)
    {
      case 0: // m Minute
        dt = Fmi::TimeDuration(0,forecastTime,0);
        break;

      case 1: //  h Hour
        dt = Fmi::TimeDuration(forecastTime,0,0);
        break;

      case 2: //  D Day
        dt = Fmi::TimeDuration(24*forecastTime,0,0);
        break;

      case 3: //  M Month
      case 4: //  Y Year
      case 5: //  10Y Decade (10 years)
      case 6: //  30Y Normal (30 years)
      case 7: //  C Century (100 years)
        throw Fmi::Exception(BCP, "Not implemented!");

      case 10: //  3h 3 hours
        dt = Fmi::TimeDuration(3*forecastTime,0,0);
        break;

      case 11: //  6h 6 hours
        dt = Fmi::TimeDuration(6*forecastTime,0,0);
        break;

      case 12: //  12h 12 hours
        dt = Fmi::TimeDuration(12*forecastTime,0,0);
        break;

      case 13: //  s Second
        dt = Fmi::TimeDuration(0,0,forecastTime);
        break;
    }

    if (ft >= 0)
      tt = refTime + dt;
    else
      tt = refTime - dt;

    return toString(tt);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}


/*! \brief The method returns the start time of the current forecast data. In some cases
    the reference time is needed for calculating the actual forecast time.

        \param referenceTime  The possible reference time.
        \return               The forecast time.
*/

T::TimeString AggregateAtmosphericChemicalProductImpl::getForecastTime(T::TimeString referenceTime) const
{
  try
  {
    std::string t1;
    std::string t2;

    t1 = countForecastStartTime(referenceTime);

    StatisticalSettings *s = getStatistical();
    if (s != nullptr)
    {
      t2 = countForecastEndTime(*s);
      if (t2 > t1)
        return t2;
    }

    return t1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





/*! \brief The method returns the parameter level.

         \return   The parameter level.
*/

T::ParamLevel AggregateAtmosphericChemicalProductImpl::getGribParameterLevel() const
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

T::ParamLevelId AggregateAtmosphericChemicalProductImpl::getGribParameterLevelId() const
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
