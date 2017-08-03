#include "ProductDefinition.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include <boost/date_time/gregorian/gregorian.hpp>


namespace SmartMet
{
namespace GRIB2
{


ProductDefinition::ProductDefinition()
{
}





/*! \brief The destructor of the class. */

ProductDefinition::~ProductDefinition()
{
}





void ProductDefinition::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
}




const T::UInt8_opt ProductDefinition::getGribParameterCategory() const
{
  try
  {
    T::UInt8_opt val;
    const ParameterSettings *p = getParameter();
    if (p != NULL)
      return p->getParameterCategory();

    return val;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}




const T::UInt8_opt ProductDefinition::getGribParameterNumber() const
{
  try
  {
    T::UInt8_opt val;
    const ParameterSettings *p = getParameter();
    if (p != NULL)
      return p->getParameterNumber();

    return val;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}





T::UInt8_opt ProductDefinition::getGeneratingProcessIdentifier() const
{
  try
  {
    T::UInt8_opt val;
    const ParameterSettings *p = getParameter();
    if (p != NULL)
      return p->getGeneratingProcessIdentifier();

    return val;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}




/*! \brief The method returns the start time of the current forecast data. In some cases
    the reference time is needed for calculating the actual forecast time.

        \param referenceTime  The possible reference time.
        \return               The forecast time.
*/

T::TimeString ProductDefinition::getForecastStartTime(T::TimeString referenceTime) const
{
  try
  {
    const ParameterSettings *p = getParameter();
    if (p != NULL)
      return countForecastStartTime(referenceTime,*p);

    return referenceTime;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}





/*! \brief The method returns the end time of the current forecast data. In some cases
    the reference time is needed for calculating the actual forecast time.

        \param referenceTime  The possible reference time.
        \return               The forecast time.
*/

T::TimeString ProductDefinition::getForecastEndTime(T::TimeString referenceTime) const
{
  try
  {
    const StatisticalSettings *s = getStatistical();

    if (s != NULL)
      return countForecastEndTime(*s);

    return getForecastStartTime(referenceTime);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}




#if 0
/*! \brief This method returns the parameter identified defined in the "paramId.def" file. */

std::uint64_t ProductDefinition::getParameterId(std::uint8_t discipline) const
{
  try
  {
    std::size_t parameterCount = Identification::gribDef.getGrib2ParameterCount();
    if (parameterCount == 0)
      return 0;

    std::uint64_t paramId = 0;

    // We have to go through all parameters and try to find the best match.

    uint maxMatchPoints = 0;

    for (std::size_t t=0; t<parameterCount; t++)
    {
      const Parameter *p = Identification::gribDef.getGrib2ParameterByIndex(t);
      if (p != NULL  &&  p->discipline == discipline)
      {
         uint matchPoints = getParameterMatchPoints(*p);
         if (matchPoints > maxMatchPoints)
         {
           maxMatchPoints = matchPoints;
           paramId = p->parameterId;
         }
      }
    }

    return paramId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}
#endif




/*! \brief The method returns the parameter level.

         \return   The parameter level.
*/


T::ParamLevel ProductDefinition::getGribParameterLevel() const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





/*! \brief The method returns the type of the parameter level.

         \return   The parameter level type (= enum value).
*/


T::ParamLevelId ProductDefinition::getGribParameterLevelId() const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}



#if 0

/*! \brief This is a helper method needed for the identification of the current data (=> parameterId).
    The method counts how many of the attributes in the given parameter definition
    match to the attributes of the current data. This information helps the parameter
    identification method to select the closest parameter definition and this way
    it might find the correct parameterId for the current data.

         \return   The number of matching attributes.
*/

uint ProductDefinition::getParameterMatchPoints(const GRIB2::Parameter& p) const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}

#endif


T::TimeString ProductDefinition::countForecastStartTime(T::TimeString referenceTime,const ParameterSettings& parameter) const
{
  try
  {
    T::TimeStamp refTime = toTimeStamp(referenceTime);
    T::TimeStamp tt = refTime;

    uint forecastTime = (uint)(*parameter.getForecastTime());

    switch (*parameter.getIndicatorOfUnitOfTimeRange())
    {
      case 0: // m Minute
        tt = refTime + boost::posix_time::time_duration(0,forecastTime,0);
        break;

      case 1: //  h Hour
        tt = refTime + boost::posix_time::time_duration(forecastTime,0,0);
        break;

      case 2: //  D Day
        tt = refTime + boost::posix_time::time_duration(24*forecastTime,0,0);
        break;

      case 3: //  M Month
      case 4: //  Y Year
      case 5: //  10Y Decade (10 years)
      case 6: //  30Y Normal (30 years)
      case 7: //  C Century (100 years)
        throw SmartMet::Spine::Exception(BCP, "Not implemented!");

      case 10: //  3h 3 hours
        tt = refTime + boost::posix_time::time_duration(3*forecastTime,0,0);
        break;

      case 11: //  6h 6 hours
        tt = refTime + boost::posix_time::time_duration(6*forecastTime,0,0);
        break;

      case 12: //  12h 12 hours
        tt = refTime + boost::posix_time::time_duration(12*forecastTime,0,0);
        break;

      case 13: //  s Second
        tt = refTime + boost::posix_time::time_duration(0,0,forecastTime);
        break;
    }

    return toString(tt);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}





T::TimeString ProductDefinition::countForecastEndTime(const StatisticalSettings& stat) const
{
  try
  {
    return toString(
        T::TimeStamp(boost::gregorian::date(
        *stat.getYearOfEndOfOverallTimeInterval(),
        *stat.getMonthOfEndOfOverallTimeInterval(),
        *stat.getDayOfEndOfOverallTimeInterval()),
        boost::posix_time::time_duration(
            *stat.getHourOfEndOfOverallTimeInterval(),
            *stat.getMinuteOfEndOfOverallTimeInterval(),
            *stat.getSecondOfEndOfOverallTimeInterval())));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}





const HorizontalSettings* ProductDefinition::getHorizontal() const
{
  try
  {
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}





const ParameterSettings*  ProductDefinition::getParameter() const
{
  try
  {
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}




const StatisticalSettings* ProductDefinition::getStatistical() const
{
  try
  {
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}





const EpsSettings* ProductDefinition::getEps() const
{
  try
  {
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void ProductDefinition::print(std::ostream& stream,uint level,uint optionFlags) const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}


}  // namespace GRIB2
}  // namespace SmartMet
