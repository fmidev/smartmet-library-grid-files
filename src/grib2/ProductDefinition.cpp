#include "ProductDefinition.h"
#include "Properties.h"
#include <macgyver/Exception.h>
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
/*
ProductDefinition::ProductDefinition(const ProductDefinition& other)
{
}
*/




/*! \brief The destructor of the class. */

ProductDefinition::~ProductDefinition()
{
}





ProductDefinition* ProductDefinition::createProductDefinition() const
{
  throw Fmi::Exception(BCP,"Not implemented!");
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void ProductDefinition::getProperties(T::PropertySettingVec& properties)
{
  try
  {
    getProperties_ParameterSettings(properties);
    getProperties_HorizontalSettings(properties);
    getProperties_StatisticalSettings(properties);
    getProperties_EpsSettings(properties);
    getProperties_DerivedSettings(properties);
    getProperties_RectangularClusterSettings(properties);
    getProperties_DerivedSettings(properties);
    getProperties_PercentileSettings(properties);
    getProperties_CategoricalSettings(properties);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductDefinition::getProperties_ParameterSettings(T::PropertySettingVec& properties)
{
  try
  {
    ParameterSettings *p = getParameter();
    if (p == nullptr)
      return;


    if (p->getParameterCategory())
      properties.emplace_back((uint)Property::ProductSection::ParameterSettings::ParameterCategory,*p->getParameterCategory());

    if (p->getParameterNumber())
      properties.emplace_back((uint)Property::ProductSection::ParameterSettings::ParameterNumber,*p->getParameterNumber());

    if (p->getTypeOfGeneratingProcess())
      properties.emplace_back((uint)Property::ProductSection::ParameterSettings::TypeOfGeneratingProcess,*p->getTypeOfGeneratingProcess());

    if (p->getBackgroundProcess())
      properties.emplace_back((uint)Property::ProductSection::ParameterSettings::BackgroundProcess,*p->getBackgroundProcess());

    if (p->getGeneratingProcessIdentifier())
      properties.emplace_back((uint)Property::ProductSection::ParameterSettings::GeneratingProcessIdentifier,*p->getGeneratingProcessIdentifier());

    if (p->getHoursAfterDataCutoff())
      properties.emplace_back((uint)Property::ProductSection::ParameterSettings::HoursAfterDataCutoff,*p->getHoursAfterDataCutoff());

    if (p->getMinutesAfterDataCutoff())
      properties.emplace_back((uint)Property::ProductSection::ParameterSettings::MinutesAfterDataCutoff,*p->getMinutesAfterDataCutoff());

    if (p->getIndicatorOfUnitOfTimeRange())
      properties.emplace_back((uint)Property::ProductSection::ParameterSettings::IndicatorOfUnitOfTimeRange,*p->getIndicatorOfUnitOfTimeRange());

    if (p->getForecastTime())
      properties.emplace_back((uint)Property::ProductSection::ParameterSettings::ForecastTime,*p->getForecastTime());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductDefinition::getProperties_HorizontalSettings(T::PropertySettingVec& properties)
{
  try
  {
    HorizontalSettings *h = getHorizontal();
    if (h == nullptr)
      return;

    if (h->getTypeOfFirstFixedSurface())
      properties.emplace_back((uint)Property::ProductSection::HorizontalSettings::TypeOfFirstFixedSurface,*h->getTypeOfFirstFixedSurface());

    if (h->getScaleFactorOfFirstFixedSurface())
      properties.emplace_back((uint)Property::ProductSection::HorizontalSettings::ScaleFactorOfFirstFixedSurface,*h->getScaleFactorOfFirstFixedSurface());

    if (h->getScaledValueOfFirstFixedSurface())
      properties.emplace_back((uint)Property::ProductSection::HorizontalSettings::ScaledValueOfFirstFixedSurface,*h->getScaledValueOfFirstFixedSurface());

    if (h->getTypeOfSecondFixedSurface())
      properties.emplace_back((uint)Property::ProductSection::HorizontalSettings::TypeOfSecondFixedSurface,*h->getTypeOfSecondFixedSurface());

    if (h->getScaleFactorOfSecondFixedSurface())
      properties.emplace_back((uint)Property::ProductSection::HorizontalSettings::ScaleFactorOfSecondFixedSurface,*h->getScaleFactorOfSecondFixedSurface());

    if (h->getScaledValueOfSecondFixedSurface())
      properties.emplace_back((uint)Property::ProductSection::HorizontalSettings::ScaledValueOfSecondFixedSurface,*h->getScaledValueOfSecondFixedSurface());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductDefinition::getProperties_StatisticalSettings(T::PropertySettingVec& properties)
{
  try
  {
    StatisticalSettings *p = getStatistical();
    if (p == nullptr)
      return;

    if (p->getYearOfEndOfOverallTimeInterval())
      properties.emplace_back((uint)Property::ProductSection::StatisticalSettings::YearOfEndOfOverallTimeInterval,*p->getYearOfEndOfOverallTimeInterval());

    if (p->getMonthOfEndOfOverallTimeInterval())
      properties.emplace_back((uint)Property::ProductSection::StatisticalSettings::MonthOfEndOfOverallTimeInterval,*p->getMonthOfEndOfOverallTimeInterval());

    if (p->getDayOfEndOfOverallTimeInterval())
      properties.emplace_back((uint)Property::ProductSection::StatisticalSettings::DayOfEndOfOverallTimeInterval,*p->getDayOfEndOfOverallTimeInterval());

    if (p->getHourOfEndOfOverallTimeInterval())
      properties.emplace_back((uint)Property::ProductSection::StatisticalSettings::HourOfEndOfOverallTimeInterval,*p->getHourOfEndOfOverallTimeInterval());

    if (p->getMinuteOfEndOfOverallTimeInterval())
      properties.emplace_back((uint)Property::ProductSection::StatisticalSettings::MinuteOfEndOfOverallTimeInterval,*p->getMinuteOfEndOfOverallTimeInterval());

    if (p->getSecondOfEndOfOverallTimeInterval())
      properties.emplace_back((uint)Property::ProductSection::StatisticalSettings::SecondOfEndOfOverallTimeInterval,*p->getSecondOfEndOfOverallTimeInterval());

    if (p->getNumberOfTimeRange())
      properties.emplace_back((uint)Property::ProductSection::StatisticalSettings::NumberOfTimeRange,*p->getNumberOfTimeRange());

    if (p->getNumberOfMissingInStatisticalProcess())
      properties.emplace_back((uint)Property::ProductSection::StatisticalSettings::NumberOfMissingInStatisticalProcess,*p->getNumberOfMissingInStatisticalProcess());

    if (p->getTypeOfStatisticalProcessing())
      properties.emplace_back((uint)Property::ProductSection::StatisticalSettings::TypeOfStatisticalProcessing,*p->getTypeOfStatisticalProcessing());

    if (p->getTypeOfTimeIncrement())
      properties.emplace_back((uint)Property::ProductSection::StatisticalSettings::TypeOfTimeIncrement,*p->getTypeOfTimeIncrement());

    if (p->getIndicatorOfUnitForTimeRange())
      properties.emplace_back((uint)Property::ProductSection::StatisticalSettings::IndicatorOfUnitForTimeRange,*p->getIndicatorOfUnitForTimeRange());

    if (p->getLengthOfTimeRange())
      properties.emplace_back((uint)Property::ProductSection::StatisticalSettings::LengthOfTimeRange,*p->getLengthOfTimeRange());

    if (p->getIndicatorOfUnitForTimeIncrement())
      properties.emplace_back((uint)Property::ProductSection::StatisticalSettings::IndicatorOfUnitForTimeIncrement,*p->getIndicatorOfUnitForTimeIncrement());

    if (p->getTimeIncrement())
      properties.emplace_back((uint)Property::ProductSection::StatisticalSettings::TimeIncrement,*p->getTimeIncrement());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductDefinition::getProperties_EpsSettings(T::PropertySettingVec& properties)
{
  try
  {
    EpsSettings *p = getEps();
    if (p == nullptr)
      return;

    if (p->getTypeOfEnsembleForecast())
      properties.emplace_back((uint)Property::ProductSection::EpsSettings::TypeOfEnsembleForecast,*p->getTypeOfEnsembleForecast());

    if (p->getPerturbationNumber())
      properties.emplace_back((uint)Property::ProductSection::EpsSettings::PerturbationNumber,*p->getPerturbationNumber());

    if (p->getNumberOfForecastsInEnsemble())
      properties.emplace_back((uint)Property::ProductSection::EpsSettings::NumberOfForecastsInEnsemble,*p->getNumberOfForecastsInEnsemble());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductDefinition::getProperties_DerivedSettings(T::PropertySettingVec& properties)
{
  try
  {
    DerivedSettings *p = getDerived();
    if (p == nullptr)
      return;

    if (p->getDerivedForecast())
      properties.emplace_back((uint)Property::ProductSection::DerivedSettings::DerivedForecast,*p->getDerivedForecast());

    if (p->getNumberOfForecastsInEnsemble())
      properties.emplace_back((uint)Property::ProductSection::DerivedSettings::NumberOfForecastsInEnsemble,*p->getNumberOfForecastsInEnsemble());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductDefinition::getProperties_RectangularClusterSettings(T::PropertySettingVec& properties)
{
  try
  {
    RectangularClusterSettings *p = getRectangularCluster();
    if (p == nullptr)
      return;

    if (p->getClusterIdentifier())
      properties.emplace_back((uint)Property::ProductSection::RectangularClusterSettings::ClusterIdentifier,*p->getClusterIdentifier());

    if (p->getNH())
      properties.emplace_back((uint)Property::ProductSection::RectangularClusterSettings::NH,*p->getNH());

    if (p->getNL())
      properties.emplace_back((uint)Property::ProductSection::RectangularClusterSettings::NL,*p->getNL());

    if (p->getTotalNumberOfClusters())
      properties.emplace_back((uint)Property::ProductSection::RectangularClusterSettings::TotalNumberOfClusters,*p->getTotalNumberOfClusters());

    if (p->getClusteringMethod())
      properties.emplace_back((uint)Property::ProductSection::RectangularClusterSettings::ClusteringMethod,*p->getClusteringMethod());

    if (p->getNorthernLatitudeOfClusterDomain())
      properties.emplace_back((uint)Property::ProductSection::RectangularClusterSettings::NorthernLatitudeOfClusterDomain,*p->getNorthernLatitudeOfClusterDomain());

    if (p->getSouthernLatitudeOfClusterDomain())
      properties.emplace_back((uint)Property::ProductSection::RectangularClusterSettings::SouthernLatitudeOfClusterDomain,*p->getSouthernLatitudeOfClusterDomain());

    if (p->getEasternLongitudeOfClusterDomain())
      properties.emplace_back((uint)Property::ProductSection::RectangularClusterSettings::EasternLongitudeOfClusterDomain,*p->getEasternLongitudeOfClusterDomain());

    if (p->getWesternLongitudeOfClusterDomain())
      properties.emplace_back((uint)Property::ProductSection::RectangularClusterSettings::WesternLongitudeOfClusterDomain,*p->getWesternLongitudeOfClusterDomain());

    if (p->getNumberOfForecastsInTheCluster())
      properties.emplace_back((uint)Property::ProductSection::RectangularClusterSettings::NumberOfForecastsInTheCluster,*p->getNumberOfForecastsInTheCluster());

    if (p->getScaleFactorOfStandardDeviation())
      properties.emplace_back((uint)Property::ProductSection::RectangularClusterSettings::ScaleFactorOfStandardDeviation,*p->getScaleFactorOfStandardDeviation());

    if (p->getScaledValueOfStandardDeviation())
      properties.emplace_back((uint)Property::ProductSection::RectangularClusterSettings::ScaledValueOfStandardDeviation,*p->getScaledValueOfStandardDeviation());

    if (p->getScaleFactorOfDistanceFromEnsembleMean())
      properties.emplace_back((uint)Property::ProductSection::RectangularClusterSettings::ScaleFactorOfDistanceFromEnsembleMean,*p->getScaleFactorOfDistanceFromEnsembleMean());

    if (p->getScaledValueOfDistanceFromEnsembleMean())
      properties.emplace_back((uint)Property::ProductSection::RectangularClusterSettings::ScaledValueOfDistanceFromEnsembleMean,*p->getScaledValueOfDistanceFromEnsembleMean());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductDefinition::getProperties_ProbabilitySettings(T::PropertySettingVec& properties)
{
  try
  {
    ProbabilitySettings *p = getProbability();
    if (p == nullptr)
      return;

    if (p->getForecastProbabilityNumber())
      properties.emplace_back((uint)Property::ProductSection::ProbabilitySettings::ForecastProbabilityNumber,*p->getForecastProbabilityNumber());

    if (p->getTotalNumberOfForecastProbabilities())
      properties.emplace_back((uint)Property::ProductSection::ProbabilitySettings::TotalNumberOfForecastProbabilities,*p->getTotalNumberOfForecastProbabilities());

    if (p->getProbabilityType())
      properties.emplace_back((uint)Property::ProductSection::ProbabilitySettings::ProbabilityType,*p->getProbabilityType());

    if (p->getScaleFactorOfLowerLimit())
      properties.emplace_back((uint)Property::ProductSection::ProbabilitySettings::ScaleFactorOfLowerLimit,*p->getScaleFactorOfLowerLimit());

    if (p->getScaledValueOfLowerLimit())
      properties.emplace_back((uint)Property::ProductSection::ProbabilitySettings::ScaledValueOfLowerLimit,*p->getScaledValueOfLowerLimit());

    if (p->getScaleFactorOfUpperLimit())
      properties.emplace_back((uint)Property::ProductSection::ProbabilitySettings::ScaleFactorOfUpperLimit,*p->getScaleFactorOfUpperLimit());

    if (p->getScaledValueOfUpperLimit())
      properties.emplace_back((uint)Property::ProductSection::ProbabilitySettings::ScaledValueOfUpperLimit,*p->getScaledValueOfUpperLimit());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductDefinition::getProperties_PercentileSettings(T::PropertySettingVec& properties)
{
  try
  {
    PercentileSettings *p = getPercentile();
    if (p == nullptr)
      return;

    if (p->getPercentileValue())
      properties.emplace_back((uint)Property::ProductSection::PercentileSettings::PercentileValue,*p->getPercentileValue());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductDefinition::getProperties_CategoricalSettings(T::PropertySettingVec& properties)
{
  try
  {
    CategoricalSettings *p = getCategorical();
    if (p == nullptr)
      return;

    if (p->getNumberOfCategories())
      properties.emplace_back((uint)Property::ProductSection::CategoricalSettings::NumberOfCategories,*p->getNumberOfCategories());

    if (p->getCategoryType())
      properties.emplace_back((uint)Property::ProductSection::CategoricalSettings::CategoryType,*p->getCategoryType());

    if (p->getCodeFigure())
      properties.emplace_back((uint)Property::ProductSection::CategoricalSettings::CodeFigure,*p->getCodeFigure());

    if (p->getScaleFactorOfLowerLimit())
      properties.emplace_back((uint)Property::ProductSection::CategoricalSettings::ScaleFactorOfLowerLimit,*p->getScaleFactorOfLowerLimit());

    if (p->getScaledValueOfLowerLimit())
      properties.emplace_back((uint)Property::ProductSection::CategoricalSettings::ScaledValueOfLowerLimit,*p->getScaledValueOfLowerLimit());

    if (p->getScaleFactorOfUpperLimit())
      properties.emplace_back((uint)Property::ProductSection::CategoricalSettings::ScaleFactorOfUpperLimit,*p->getScaleFactorOfUpperLimit());

    if (p->getScaledValueOfUpperLimit())
      properties.emplace_back((uint)Property::ProductSection::CategoricalSettings::ScaledValueOfUpperLimit,*p->getScaledValueOfUpperLimit());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductDefinition::getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const
{
}





bool ProductDefinition::hasAttributeValue(const char *attributeName, const char *attributeValue) const
{
  return false;
}





bool ProductDefinition::getAttributeValue(const char *attributeName, std::string& attributeValue) const
{
  return false;
}





uint ProductDefinition::getTemplateNumber() const
{
  throw Fmi::Exception(BCP,"Not implemented!");
}





const T::UInt8_opt ProductDefinition::getGribParameterCategory() const
{
  try
  {
    T::UInt8_opt val(0);
    const ParameterSettings *p = getParameter();
    if (p != nullptr)
      return p->getParameterCategory();

    const PostprocSettings *pp = getPostproc();
    if (pp != nullptr)
      return pp->getParameterCategory();

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
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

    const PostprocSettings *pp = getPostproc();
    if (pp != nullptr)
      return pp->getParameterNumber();

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
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

    const PostprocSettings *pp = getPostproc();
    if (pp != nullptr)
      return pp->getGeneratingProcessIdentifier();

    return val;
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

T::TimeString ProductDefinition::getForecastTime(T::TimeString referenceTime) const
{
  try
  {
    std::string t1;
    std::string t2;

    const ParameterSettings *p = getParameter();
    const PostprocSettings *pp = nullptr;
    if (p != nullptr)
    {
      t1 = countForecastStartTime(referenceTime,*p);
    }
    else
    {
      pp = getPostproc();
      if (pp != nullptr)
        t1 = countForecastStartTime(referenceTime,*pp);
    }

    StatisticalSettings *s = getStatistical();
    if (s != nullptr)
    {
      t2 = countForecastEndTime(*s);
      if (t2 > t1)
        return t2;
    }

    if (p != nullptr ||  pp != nullptr)
      return t1;

    return referenceTime;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}




/*! \brief The method returns the parameter level.

         \return   The parameter level.
*/


T::ParamLevel ProductDefinition::getGribParameterLevel() const
{
  try
  {
    auto horizontal = getHorizontal();
    if (horizontal && horizontal->getScaledValueOfFirstFixedSurface())
      return *horizontal->getScaledValueOfFirstFixedSurface();

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


T::ParamLevelId ProductDefinition::getGribParameterLevelId() const
{
  try
  {
    auto horizontal = getHorizontal();
    if (horizontal->getScaledValueOfFirstFixedSurface())
      return *horizontal->getTypeOfFirstFixedSurface();

    if (horizontal->getScaledValueOfSecondFixedSurface())
      return *horizontal->getTypeOfSecondFixedSurface();

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
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
      throw Fmi::Exception(BCP, "The 'parameter.forecastTime' value not defined!");
    }

    auto indicator = parameter.getIndicatorOfUnitOfTimeRange();
    if (!indicator)
      throw Fmi::Exception(BCP, "The 'parameter.indicatorOfUnitOfTimeRange' value not defined!");

    int ft = *forecastTimeP;
    int forecastTime = ft;
    if (ft < 0)
      forecastTime = -ft;

    boost::posix_time::time_duration dt;

    switch (*indicator)
    {
      case 0: // m Minute
        dt = boost::posix_time::time_duration(0,forecastTime,0);
        break;

      case 1: //  h Hour
        dt = boost::posix_time::time_duration(forecastTime,0,0);
        break;

      case 2: //  D Day
        dt = boost::posix_time::time_duration(24*forecastTime,0,0);
        break;

      case 3: //  M Month
      case 4: //  Y Year
      case 5: //  10Y Decade (10 years)
      case 6: //  30Y Normal (30 years)
      case 7: //  C Century (100 years)
        throw Fmi::Exception(BCP, "Not implemented!");

      case 10: //  3h 3 hours
        dt = boost::posix_time::time_duration(3*forecastTime,0,0);
        break;

      case 11: //  6h 6 hours
        dt = boost::posix_time::time_duration(6*forecastTime,0,0);
        break;

      case 12: //  12h 12 hours
        dt = boost::posix_time::time_duration(12*forecastTime,0,0);
        break;

      case 13: //  s Second
        dt = boost::posix_time::time_duration(0,0,forecastTime);
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





T::TimeString ProductDefinition::countForecastStartTime(T::TimeString referenceTime,const PostprocSettings& parameter) const
{
  try
  {
    T::TimeStamp refTime = toTimeStamp(referenceTime);
    T::TimeStamp tt = refTime;

    auto forecastTimeP = parameter.getForecastTime();
    if (!forecastTimeP)
    {
      throw Fmi::Exception(BCP, "The 'parameter.forecastTime' value not defined!");
    }

    auto indicator = parameter.getIndicatorOfUnitOfTimeRange();
    if (!indicator)
      throw Fmi::Exception(BCP, "The 'parameter.indicatorOfUnitOfTimeRange' value not defined!");

    int ft = *forecastTimeP;
    int forecastTime = ft;
    if (ft < 0)
      forecastTime = -ft;

    boost::posix_time::time_duration dt;

    switch (*indicator)
    {
      case 0: // m Minute
        dt = boost::posix_time::time_duration(0,forecastTime,0);
        break;

      case 1: //  h Hour
        dt = boost::posix_time::time_duration(forecastTime,0,0);
        break;

      case 2: //  D Day
        dt = boost::posix_time::time_duration(24*forecastTime,0,0);
        break;

      case 3: //  M Month
      case 4: //  Y Year
      case 5: //  10Y Decade (10 years)
      case 6: //  30Y Normal (30 years)
      case 7: //  C Century (100 years)
        throw Fmi::Exception(BCP, "Not implemented!");

      case 10: //  3h 3 hours
        dt = boost::posix_time::time_duration(3*forecastTime,0,0);
        break;

      case 11: //  6h 6 hours
        dt = boost::posix_time::time_duration(6*forecastTime,0,0);
        break;

      case 12: //  12h 12 hours
        dt = boost::posix_time::time_duration(12*forecastTime,0,0);
        break;

      case 13: //  s Second
        dt = boost::posix_time::time_duration(0,0,forecastTime);
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
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
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





PostprocSettings* ProductDefinition::getPostproc() const
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
  throw Fmi::Exception(BCP,"Not implemented!");
}


}  // namespace GRIB2
}  // namespace SmartMet
