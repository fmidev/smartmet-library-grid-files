#include "ProductDefinition.h"
#include "Properties.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"
#include <boost/date_time/gregorian/gregorian.hpp>


namespace SmartMet
{
namespace GRIB2
{


ProductDefinition::ProductDefinition()
{
}





/*! \brief The copy constructor of the class. */

ProductDefinition::ProductDefinition(const ProductDefinition& other)
{
}





/*! \brief The destructor of the class. */

ProductDefinition::~ProductDefinition()
{
}





ProductDefinition* ProductDefinition::createProductDefinition() const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





bool ProductDefinition::setProperty(uint propertyId,long long value)
{
  try
  {
    if (propertyId >= Property::ProductSection::ParameterSettings::FirstProperty  &&  propertyId <= Property::ProductSection::ParameterSettings::LastProperty)
    {
      return setProperty_ParameterSettings(propertyId,value);
    }

    if (propertyId >= Property::ProductSection::HorizontalSettings::FirstProperty  &&  propertyId <= Property::ProductSection::HorizontalSettings::LastProperty)
    {
      return setProperty_HorizontalSettings(propertyId,value);
    }

    if (propertyId >= Property::ProductSection::StatisticalSettings::FirstProperty  &&  propertyId <= Property::ProductSection::StatisticalSettings::LastProperty)
    {
      return setProperty_StatisticalSettings(propertyId,value);
    }

    if (propertyId >= Property::ProductSection::EpsSettings::FirstProperty  &&  propertyId <= Property::ProductSection::EpsSettings::LastProperty)
    {
      return setProperty_EpsSettings(propertyId,value);
    }

    if (propertyId >= Property::ProductSection::DerivedSettings::FirstProperty  &&  propertyId <= Property::ProductSection::DerivedSettings::LastProperty)
    {
      return setProperty_DerivedSettings(propertyId,value);
    }

    if (propertyId >= Property::ProductSection::RectangularClusterSettings::FirstProperty  &&  propertyId <= Property::ProductSection::RectangularClusterSettings::LastProperty)
    {
      return setProperty_RectangularClusterSettings(propertyId,value);
    }

    if (propertyId >= Property::ProductSection::ProbabilitySettings::FirstProperty  &&  propertyId <= Property::ProductSection::ProbabilitySettings::LastProperty)
    {
      return setProperty_DerivedSettings(propertyId,value);
    }

    if (propertyId >= Property::ProductSection::PercentileSettings::FirstProperty  &&  propertyId <= Property::ProductSection::PercentileSettings::LastProperty)
    {
      return setProperty_PercentileSettings(propertyId,value);
    }

    if (propertyId >= Property::ProductSection::CategoricalSettings::FirstProperty  &&  propertyId <= Property::ProductSection::CategoricalSettings::LastProperty)
    {
      return setProperty_CategoricalSettings(propertyId,value);
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::setProperty_ParameterSettings(uint propertyId,long long value)
{
  try
  {
    ParameterSettings *p = getParameter();
    if (p == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::ParameterSettings::ParameterCategory:
        p->setParameterCategory(value);
        return true;

      case Property::ProductSection::ParameterSettings::ParameterNumber:
        p->setParameterNumber(value);
        return true;

      case Property::ProductSection::ParameterSettings::TypeOfGeneratingProcess:
        p->setTypeOfGeneratingProcess(value);
        return true;

      case Property::ProductSection::ParameterSettings::BackgroundProcess:
        p->setBackgroundProcess(value);
        return true;

      case Property::ProductSection::ParameterSettings::GeneratingProcessIdentifier:
        p->setGeneratingProcessIdentifier(value);
        return true;

      case Property::ProductSection::ParameterSettings::HoursAfterDataCutoff:
        p->setHoursAfterDataCutoff(value);
        return true;

      case Property::ProductSection::ParameterSettings::MinutesAfterDataCutoff:
        p->setMinutesAfterDataCutoff(value);
        return true;

      case Property::ProductSection::ParameterSettings::IndicatorOfUnitOfTimeRange:
        p->setIndicatorOfUnitOfTimeRange(value);
        return true;

      case Property::ProductSection::ParameterSettings::ForecastTime:
        p->setForecastTime(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::setProperty_HorizontalSettings(uint propertyId,long long value)
{
  try
  {
    HorizontalSettings *h = getHorizontal();
    if (h == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::HorizontalSettings::TypeOfFirstFixedSurface:
        h->setTypeOfFirstFixedSurface(value);
        return true;

      case Property::ProductSection::HorizontalSettings::ScaleFactorOfFirstFixedSurface:
        h->setScaleFactorOfFirstFixedSurface(value);
        return true;

      case Property::ProductSection::HorizontalSettings::ScaledValueOfFirstFixedSurface:
        h->setScaledValueOfFirstFixedSurface(value);
        return true;

      case Property::ProductSection::HorizontalSettings::TypeOfSecondFixedSurface:
        h->setTypeOfSecondFixedSurface(value);
        return true;

      case Property::ProductSection::HorizontalSettings::ScaleFactorOfSecondFixedSurface:
        h->setScaleFactorOfSecondFixedSurface(value);
        return true;

      case Property::ProductSection::HorizontalSettings::ScaledValueOfSecondFixedSurface:
        h->setScaledValueOfSecondFixedSurface(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::setProperty_StatisticalSettings(uint propertyId,long long value)
{
  try
  {
    StatisticalSettings *p = getStatistical();
    if (p == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::StatisticalSettings::YearOfEndOfOverallTimeInterval:
        p->setYearOfEndOfOverallTimeInterval(value);
        return true;

      case Property::ProductSection::StatisticalSettings::MonthOfEndOfOverallTimeInterval:
        p->setMonthOfEndOfOverallTimeInterval(value);
        return true;

      case Property::ProductSection::StatisticalSettings::DayOfEndOfOverallTimeInterval:
        p->setDayOfEndOfOverallTimeInterval(value);
        return true;

      case Property::ProductSection::StatisticalSettings::HourOfEndOfOverallTimeInterval:
        p->setHourOfEndOfOverallTimeInterval(value);
        return true;

      case Property::ProductSection::StatisticalSettings::MinuteOfEndOfOverallTimeInterval:
        p->setMinuteOfEndOfOverallTimeInterval(value);
        return true;

      case Property::ProductSection::StatisticalSettings::SecondOfEndOfOverallTimeInterval:
        p->setSecondOfEndOfOverallTimeInterval(value);
        return true;

      case Property::ProductSection::StatisticalSettings::NumberOfTimeRange:
        p->setNumberOfTimeRange(value);
        return true;

      case Property::ProductSection::StatisticalSettings::NumberOfMissingInStatisticalProcess:
        p->setNumberOfMissingInStatisticalProcess(value);
        return true;

      case Property::ProductSection::StatisticalSettings::TypeOfStatisticalProcessing:
        p->setTypeOfStatisticalProcessing(value);
        return true;

      case Property::ProductSection::StatisticalSettings::TypeOfTimeIncrement:
        p->setTypeOfTimeIncrement(value);
        return true;

      case Property::ProductSection::StatisticalSettings::IndicatorOfUnitForTimeRange:
        p->setIndicatorOfUnitForTimeRange(value);
        return true;

      case Property::ProductSection::StatisticalSettings::LengthOfTimeRange:
        p->setLengthOfTimeRange(value);
        return true;

      case Property::ProductSection::StatisticalSettings::IndicatorOfUnitForTimeIncrement:
        p->setIndicatorOfUnitForTimeIncrement(value);
        return true;

      case Property::ProductSection::StatisticalSettings::TimeIncrement:
        p->setTimeIncrement(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::setProperty_EpsSettings(uint propertyId,long long value)
{
  try
  {
    EpsSettings *p = getEps();
    if (p == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::EpsSettings::TypeOfEnsembleForecast:
        p->setTypeOfEnsembleForecast(value);
        return true;

      case Property::ProductSection::EpsSettings::PerturbationNumber:
        p->setPerturbationNumber(value);
        return true;

      case Property::ProductSection::EpsSettings::NumberOfForecastsInEnsemble:
        p->setNumberOfForecastsInEnsemble(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::setProperty_DerivedSettings(uint propertyId,long long value)
{
  try
  {
    DerivedSettings *p = getDerived();
    if (p == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::DerivedSettings::DerivedForecast:
        p->setDerivedForecast(value);
        return true;

      case Property::ProductSection::DerivedSettings::NumberOfForecastsInEnsemble:
        p->setNumberOfForecastsInEnsemble(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::setProperty_RectangularClusterSettings(uint propertyId,long long value)
{
  try
  {
    RectangularClusterSettings *p = getRectangularCluster();
    if (p == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::RectangularClusterSettings::ClusterIdentifier:
        p->setClusterIdentifier(value);
        return true;

      case Property::ProductSection::RectangularClusterSettings::NH:
        p->setNH(value);
        return true;

      case Property::ProductSection::RectangularClusterSettings::NL:
        p->setNL(value);
        return true;

      case Property::ProductSection::RectangularClusterSettings::TotalNumberOfClusters:
        p->setTotalNumberOfClusters(value);
        return true;

      case Property::ProductSection::RectangularClusterSettings::ClusteringMethod:
        p->setClusteringMethod(value);
        return true;

      case Property::ProductSection::RectangularClusterSettings::NorthernLatitudeOfClusterDomain:
        p->setNorthernLatitudeOfClusterDomain(value);
        return true;

      case Property::ProductSection::RectangularClusterSettings::SouthernLatitudeOfClusterDomain:
        p->setSouthernLatitudeOfClusterDomain(value);
        return true;

      case Property::ProductSection::RectangularClusterSettings::EasternLongitudeOfClusterDomain:
        p->setEasternLongitudeOfClusterDomain(value);
        return true;

      case Property::ProductSection::RectangularClusterSettings::WesternLongitudeOfClusterDomain:
        p->setWesternLongitudeOfClusterDomain(value);
        return true;

      case Property::ProductSection::RectangularClusterSettings::NumberOfForecastsInTheCluster:
        p->setNumberOfForecastsInTheCluster(value);
        return true;

      case Property::ProductSection::RectangularClusterSettings::ScaleFactorOfStandardDeviation:
        p->setScaleFactorOfStandardDeviation(value);
        return true;

      case Property::ProductSection::RectangularClusterSettings::ScaledValueOfStandardDeviation:
        p->setScaledValueOfStandardDeviation(value);
        return true;

      case Property::ProductSection::RectangularClusterSettings::ScaleFactorOfDistanceFromEnsembleMean:
        p->setScaleFactorOfDistanceFromEnsembleMean(value);
        return true;

      case Property::ProductSection::RectangularClusterSettings::ScaledValueOfDistanceFromEnsembleMean:
        p->setScaledValueOfDistanceFromEnsembleMean(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::setProperty_ProbabilitySettings(uint propertyId,long long value)
{
  try
  {
    ProbabilitySettings *p = getProbability();
    if (p == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::ProbabilitySettings::ForecastProbabilityNumber:
        p->setForecastProbabilityNumber(value);
        return true;

      case Property::ProductSection::ProbabilitySettings::TotalNumberOfForecastProbabilities:
        p->setTotalNumberOfForecastProbabilities(value);
        return true;

      case Property::ProductSection::ProbabilitySettings::ProbabilityType:
        p->setProbabilityType(value);
        return true;

      case Property::ProductSection::ProbabilitySettings::ScaleFactorOfLowerLimit:
        p->setScaleFactorOfLowerLimit(value);
        return true;

      case Property::ProductSection::ProbabilitySettings::ScaledValueOfLowerLimit:
        p->setScaledValueOfLowerLimit(value);
        return true;

      case Property::ProductSection::ProbabilitySettings::ScaleFactorOfUpperLimit:
        p->setScaleFactorOfUpperLimit(value);
        return true;

      case Property::ProductSection::ProbabilitySettings::ScaledValueOfUpperLimit:
        p->setScaledValueOfUpperLimit(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::setProperty_PercentileSettings(uint propertyId,long long value)
{
  try
  {
    PercentileSettings *p = getPercentile();
    if (p == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::PercentileSettings::PercentileValue:
        p->setPercentileValue(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::setProperty_CategoricalSettings(uint propertyId,long long value)
{
  try
  {
    CategoricalSettings *p = getCategorical();
    if (p == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::CategoricalSettings::NumberOfCategories:
        p->setNumberOfCategories(value);
        return true;

      case Property::ProductSection::CategoricalSettings::CategoryType:
        p->setCategoryType(value);
        return true;

      case Property::ProductSection::CategoricalSettings::CodeFigure:
        p->setCodeFigure(value);
        return true;

      case Property::ProductSection::CategoricalSettings::ScaleFactorOfLowerLimit:
        p->setScaleFactorOfLowerLimit(value);
        return true;

      case Property::ProductSection::CategoricalSettings::ScaledValueOfLowerLimit:
        p->setScaledValueOfLowerLimit(value);
        return true;

      case Property::ProductSection::CategoricalSettings::ScaleFactorOfUpperLimit:
        p->setScaleFactorOfUpperLimit(value);
        return true;

      case Property::ProductSection::CategoricalSettings::ScaledValueOfUpperLimit:
        p->setScaledValueOfUpperLimit(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void ProductDefinition::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
}





uint ProductDefinition::getTemplateNumber() const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





const T::UInt8_opt ProductDefinition::getGribParameterCategory() const
{
  try
  {
    T::UInt8_opt val(0);
    const ParameterSettings *p = getParameter();
    if (p != nullptr)
      return p->getParameterCategory();

    return val;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}





const T::UInt8_opt ProductDefinition::getGribParameterNumber() const
{
  try
  {
    T::UInt8_opt val(0);
    const ParameterSettings *p = getParameter();
    if (p != nullptr)
      return p->getParameterNumber();

    return val;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}





T::UInt8_opt ProductDefinition::getGeneratingProcessIdentifier() const
{
  try
  {
    T::UInt8_opt val(0);
    const ParameterSettings *p = getParameter();
    if (p != nullptr)
      return p->getGeneratingProcessIdentifier();

    return val;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}




/*! \brief The method returns the start time of the current forecast data. In some cases
    the reference time is needed for calculating the actual forecast time.

        \param referenceTime  The possible reference time.
        \return               The forecast time.
*/

T::TimeString ProductDefinition::getForecastTime(T::TimeString referenceTime) const
{
  try
  {
    const ParameterSettings *p = getParameter();
    if (p != nullptr)
      return countForecastStartTime(referenceTime,*p);

    return referenceTime;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}




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





T::TimeString ProductDefinition::countForecastStartTime(T::TimeString referenceTime,const ParameterSettings& parameter) const
{
  try
  {
    T::TimeStamp refTime = toTimeStamp(referenceTime);
    T::TimeStamp tt = refTime;

    auto forecastTimeP = parameter.getForecastTime();
    if (!forecastTimeP)
    {
      parameter.print(std::cout,0,0);
      throw SmartMet::Spine::Exception(BCP, "The 'parameter.forecastTime' value not defined!");
    }

    auto indicator = parameter.getIndicatorOfUnitOfTimeRange();
    if (!indicator)
      throw SmartMet::Spine::Exception(BCP, "The 'parameter.indicatorOfUnitOfTimeRange' value not defined!");

    uint forecastTime = *forecastTimeP;

    switch (*indicator)
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}





HorizontalSettings* ProductDefinition::getHorizontal() const
{
  // The method is possible implemented in a child class.
  return nullptr;
}





ParameterSettings*  ProductDefinition::getParameter() const
{
  // The method is possible implemented in a child class.
  return nullptr;
}




StatisticalSettings* ProductDefinition::getStatistical() const
{
  // The method is possible implemented in a child class.
  return nullptr;
}





EpsSettings* ProductDefinition::getEps() const
{
  // The method is possible implemented in a child class.
  return nullptr;
}





DerivedSettings* ProductDefinition::getDerived() const
{
  // The method is possible implemented in a child class.
  return nullptr;
}





RectangularClusterSettings* ProductDefinition::getRectangularCluster() const
{
  // The method is possible implemented in a child class.
  return nullptr;
}





ProbabilitySettings* ProductDefinition::getProbability() const
{
  // The method is possible implemented in a child class.
  return nullptr;
}





PercentileSettings* ProductDefinition::getPercentile() const
{
  // The method is possible implemented in a child class.
  return nullptr;
}





CategoricalSettings* ProductDefinition::getCategorical() const
{
  // The method is possible implemented in a child class.
  return nullptr;
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
