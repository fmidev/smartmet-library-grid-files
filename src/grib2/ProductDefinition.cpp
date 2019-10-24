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





/*! \brief The method is used for fetching a (long long ) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the requested property is returned in this parameter.
        \return            The method returns true if the value of the requested property was found.
*/

bool ProductDefinition::getProperty(uint propertyId,long long& value)
{
  try
  {
    if (getProperty_ParameterSettings(propertyId,value))
      return true;

    if (getProperty_HorizontalSettings(propertyId,value))
      return true;

    if (getProperty_StatisticalSettings(propertyId,value))
      return true;

    if (getProperty_EpsSettings(propertyId,value))
      return true;

    if (getProperty_DerivedSettings(propertyId,value))
      return true;

    if (getProperty_RectangularClusterSettings(propertyId,value))
      return true;

    if (getProperty_DerivedSettings(propertyId,value))
      return true;

    if (getProperty_PercentileSettings(propertyId,value))
      return true;

    if (getProperty_CategoricalSettings(propertyId,value))
      return true;

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::getProperty_ParameterSettings(uint propertyId,long long& value)
{
  try
  {
    ParameterSettings *p = getParameter();
    if (p == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::ParameterSettings::ParameterCategory:
        value = *p->getParameterCategory();
        return true;

      case Property::ProductSection::ParameterSettings::ParameterNumber:
        value = *p->getParameterNumber();
        return true;

      case Property::ProductSection::ParameterSettings::TypeOfGeneratingProcess:
        value = *p->getTypeOfGeneratingProcess();
        return true;

      case Property::ProductSection::ParameterSettings::BackgroundProcess:
        value = *p->getBackgroundProcess();
        return true;

      case Property::ProductSection::ParameterSettings::GeneratingProcessIdentifier:
        value = *p->getGeneratingProcessIdentifier();
        return true;

      case Property::ProductSection::ParameterSettings::HoursAfterDataCutoff:
        value = *p->getHoursAfterDataCutoff();
        return true;

      case Property::ProductSection::ParameterSettings::MinutesAfterDataCutoff:
        value = *p->getMinutesAfterDataCutoff();
        return true;

      case Property::ProductSection::ParameterSettings::IndicatorOfUnitOfTimeRange:
        value = *p->getIndicatorOfUnitOfTimeRange();
        return true;

      case Property::ProductSection::ParameterSettings::ForecastTime:
        value = *p->getForecastTime();
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::getProperty_HorizontalSettings(uint propertyId,long long& value)
{
  try
  {
    HorizontalSettings *h = getHorizontal();
    if (h == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::HorizontalSettings::TypeOfFirstFixedSurface:
        value = *h->getTypeOfFirstFixedSurface();
        return true;

      case Property::ProductSection::HorizontalSettings::ScaleFactorOfFirstFixedSurface:
        value = *h->getScaleFactorOfFirstFixedSurface();
        return true;

      case Property::ProductSection::HorizontalSettings::ScaledValueOfFirstFixedSurface:
        value = *h->getScaledValueOfFirstFixedSurface();
        return true;

      case Property::ProductSection::HorizontalSettings::TypeOfSecondFixedSurface:
        value = *h->getTypeOfSecondFixedSurface();
        return true;

      case Property::ProductSection::HorizontalSettings::ScaleFactorOfSecondFixedSurface:
        value = *h->getScaleFactorOfSecondFixedSurface();
        return true;

      case Property::ProductSection::HorizontalSettings::ScaledValueOfSecondFixedSurface:
        value = *h->getScaledValueOfSecondFixedSurface();
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::getProperty_StatisticalSettings(uint propertyId,long long& value)
{
  try
  {
    StatisticalSettings *p = getStatistical();
    if (p == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::StatisticalSettings::YearOfEndOfOverallTimeInterval:
        value = *p->getYearOfEndOfOverallTimeInterval();
        return true;

      case Property::ProductSection::StatisticalSettings::MonthOfEndOfOverallTimeInterval:
        value = *p->getMonthOfEndOfOverallTimeInterval();
        return true;

      case Property::ProductSection::StatisticalSettings::DayOfEndOfOverallTimeInterval:
        value = *p->getDayOfEndOfOverallTimeInterval();
        return true;

      case Property::ProductSection::StatisticalSettings::HourOfEndOfOverallTimeInterval:
        value = *p->getHourOfEndOfOverallTimeInterval();
        return true;

      case Property::ProductSection::StatisticalSettings::MinuteOfEndOfOverallTimeInterval:
        value = *p->getMinuteOfEndOfOverallTimeInterval();
        return true;

      case Property::ProductSection::StatisticalSettings::SecondOfEndOfOverallTimeInterval:
        value = *p->getSecondOfEndOfOverallTimeInterval();
        return true;

      case Property::ProductSection::StatisticalSettings::NumberOfTimeRange:
        value = *p->getNumberOfTimeRange();
        return true;

      case Property::ProductSection::StatisticalSettings::NumberOfMissingInStatisticalProcess:
        value = *p->getNumberOfMissingInStatisticalProcess();
        return true;

      case Property::ProductSection::StatisticalSettings::TypeOfStatisticalProcessing:
        value = *p->getTypeOfStatisticalProcessing();
        return true;

      case Property::ProductSection::StatisticalSettings::TypeOfTimeIncrement:
        value = *p->getTypeOfTimeIncrement();
        return true;

      case Property::ProductSection::StatisticalSettings::IndicatorOfUnitForTimeRange:
        value = *p->getIndicatorOfUnitForTimeRange();
        return true;

      case Property::ProductSection::StatisticalSettings::LengthOfTimeRange:
        value = *p->getLengthOfTimeRange();
        return true;

      case Property::ProductSection::StatisticalSettings::IndicatorOfUnitForTimeIncrement:
        value = *p->getIndicatorOfUnitForTimeIncrement();
        return true;

      case Property::ProductSection::StatisticalSettings::TimeIncrement:
        value = *p->getTimeIncrement();
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::getProperty_EpsSettings(uint propertyId,long long& value)
{
  try
  {
    EpsSettings *p = getEps();
    if (p == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::EpsSettings::TypeOfEnsembleForecast:
        value = *p->getTypeOfEnsembleForecast();
        return true;

      case Property::ProductSection::EpsSettings::PerturbationNumber:
        value = *p->getPerturbationNumber();
        return true;

      case Property::ProductSection::EpsSettings::NumberOfForecastsInEnsemble:
        value = *p->getNumberOfForecastsInEnsemble();
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::getProperty_DerivedSettings(uint propertyId,long long& value)
{
  try
  {
    DerivedSettings *p = getDerived();
    if (p == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::DerivedSettings::DerivedForecast:
        value = *p->getDerivedForecast();
        return true;

      case Property::ProductSection::DerivedSettings::NumberOfForecastsInEnsemble:
        value = *p->getNumberOfForecastsInEnsemble();
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::getProperty_RectangularClusterSettings(uint propertyId,long long& value)
{
  try
  {
    RectangularClusterSettings *p = getRectangularCluster();
    if (p == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::RectangularClusterSettings::ClusterIdentifier:
        value = *p->getClusterIdentifier();
        return true;

      case Property::ProductSection::RectangularClusterSettings::NH:
        value = *p->getNH();
        return true;

      case Property::ProductSection::RectangularClusterSettings::NL:
        value = *p->getNL();
        return true;

      case Property::ProductSection::RectangularClusterSettings::TotalNumberOfClusters:
        value = *p->getTotalNumberOfClusters();
        return true;

      case Property::ProductSection::RectangularClusterSettings::ClusteringMethod:
        value = *p->getClusteringMethod();
        return true;

      case Property::ProductSection::RectangularClusterSettings::NorthernLatitudeOfClusterDomain:
        value = *p->getNorthernLatitudeOfClusterDomain();
        return true;

      case Property::ProductSection::RectangularClusterSettings::SouthernLatitudeOfClusterDomain:
        value = *p->getSouthernLatitudeOfClusterDomain();
        return true;

      case Property::ProductSection::RectangularClusterSettings::EasternLongitudeOfClusterDomain:
        value = *p->getEasternLongitudeOfClusterDomain();
        return true;

      case Property::ProductSection::RectangularClusterSettings::WesternLongitudeOfClusterDomain:
        value = *p->getWesternLongitudeOfClusterDomain();
        return true;

      case Property::ProductSection::RectangularClusterSettings::NumberOfForecastsInTheCluster:
        value = *p->getNumberOfForecastsInTheCluster();
        return true;

      case Property::ProductSection::RectangularClusterSettings::ScaleFactorOfStandardDeviation:
        value = *p->getScaleFactorOfStandardDeviation();
        return true;

      case Property::ProductSection::RectangularClusterSettings::ScaledValueOfStandardDeviation:
        value = *p->getScaledValueOfStandardDeviation();
        return true;

      case Property::ProductSection::RectangularClusterSettings::ScaleFactorOfDistanceFromEnsembleMean:
        value = *p->getScaleFactorOfDistanceFromEnsembleMean();
        return true;

      case Property::ProductSection::RectangularClusterSettings::ScaledValueOfDistanceFromEnsembleMean:
        value = *p->getScaledValueOfDistanceFromEnsembleMean();
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::getProperty_ProbabilitySettings(uint propertyId,long long& value)
{
  try
  {
    ProbabilitySettings *p = getProbability();
    if (p == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::ProbabilitySettings::ForecastProbabilityNumber:
        value = *p->getForecastProbabilityNumber();
        return true;

      case Property::ProductSection::ProbabilitySettings::TotalNumberOfForecastProbabilities:
        value = *p->getTotalNumberOfForecastProbabilities();
        return true;

      case Property::ProductSection::ProbabilitySettings::ProbabilityType:
        value = *p->getProbabilityType();
        return true;

      case Property::ProductSection::ProbabilitySettings::ScaleFactorOfLowerLimit:
        value = *p->getScaleFactorOfLowerLimit();
        return true;

      case Property::ProductSection::ProbabilitySettings::ScaledValueOfLowerLimit:
        value = *p->getScaledValueOfLowerLimit();
        return true;

      case Property::ProductSection::ProbabilitySettings::ScaleFactorOfUpperLimit:
        value = *p->getScaleFactorOfUpperLimit();
        return true;

      case Property::ProductSection::ProbabilitySettings::ScaledValueOfUpperLimit:
        value = *p->getScaledValueOfUpperLimit();
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::getProperty_PercentileSettings(uint propertyId,long long& value)
{
  try
  {
    PercentileSettings *p = getPercentile();
    if (p == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::PercentileSettings::PercentileValue:
        value = *p->getPercentileValue();
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ProductDefinition::getProperty_CategoricalSettings(uint propertyId,long long& value)
{
  try
  {
    CategoricalSettings *p = getCategorical();
    if (p == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::ProductSection::CategoricalSettings::NumberOfCategories:
        value = *p->getNumberOfCategories();
        return true;

      case Property::ProductSection::CategoricalSettings::CategoryType:
        value = *p->getCategoryType();
        return true;

      case Property::ProductSection::CategoricalSettings::CodeFigure:
        value = *p->getCodeFigure();
        return true;

      case Property::ProductSection::CategoricalSettings::ScaleFactorOfLowerLimit:
        value = *p->getScaleFactorOfLowerLimit();
        return true;

      case Property::ProductSection::CategoricalSettings::ScaledValueOfLowerLimit:
        value = *p->getScaledValueOfLowerLimit();
        return true;

      case Property::ProductSection::CategoricalSettings::ScaleFactorOfUpperLimit:
        value = *p->getScaleFactorOfUpperLimit();
        return true;

      case Property::ProductSection::CategoricalSettings::ScaledValueOfUpperLimit:
        value = *p->getScaledValueOfUpperLimit();
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method is used for setting a (long long) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool ProductDefinition::setProperty(uint propertyId,long long value)
{
  try
  {
    if (setProperty_ParameterSettings(propertyId,value))
      return true;

    if (setProperty_HorizontalSettings(propertyId,value))
      return true;

    if (setProperty_StatisticalSettings(propertyId,value))
      return true;

    if (setProperty_EpsSettings(propertyId,value))
      return true;

    if (setProperty_DerivedSettings(propertyId,value))
      return true;

    if (setProperty_RectangularClusterSettings(propertyId,value))
      return true;

    if (setProperty_DerivedSettings(propertyId,value))
      return true;

    if (setProperty_PercentileSettings(propertyId,value))
      return true;

    if (setProperty_CategoricalSettings(propertyId,value))
      return true;

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
    std::string t1;
    std::string t2;

    const ParameterSettings *p = getParameter();
    if (p != nullptr)
      t1 = countForecastStartTime(referenceTime,*p);

    StatisticalSettings *s = getStatistical();
    if (s != nullptr)
    {
      t2 = countForecastEndTime(*s);
      if (t2 > t1)
        return t2;
    }

    if (p != nullptr)
      return t1;

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
      //parameter.print(std::cout,0,0);
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
