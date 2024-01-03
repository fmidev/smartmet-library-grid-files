#include "Properties.h"
#include <macgyver/Exception.h>


namespace SmartMet
{
namespace GRIB2
{

Property gribProperty;



Property::Property()
{
  try
  {
    addProperty("Grib2.IndicatorSection.Discipline",IndicatorSection::Discipline);
    addProperty("Grib2.IndicatorSection.EditionNumber",IndicatorSection::EditionNumber);

    addProperty("Grib2.IdentificationSection.Centre",IdentificationSection::Centre);
    addProperty("Grib2.IdentificationSection.SubCentre",IdentificationSection::SubCentre);
    addProperty("Grib2.IdentificationSection.TablesVersion",IdentificationSection::TablesVersion);
    addProperty("Grib2.IdentificationSection.LocalTablesVersion",IdentificationSection::LocalTablesVersion);
    addProperty("Grib2.IdentificationSection.SignificanceOfReferenceTime",IdentificationSection::SignificanceOfReferenceTime);
    addProperty("Grib2.IdentificationSection.Year",IdentificationSection::Year);
    addProperty("Grib2.IdentificationSection.Month",IdentificationSection::Month);
    addProperty("Grib2.IdentificationSection.Day",IdentificationSection::Day);
    addProperty("Grib2.IdentificationSection.Hour",IdentificationSection::Hour);
    addProperty("Grib2.IdentificationSection.Minute",IdentificationSection::Minute);
    addProperty("Grib2.IdentificationSection.Second",IdentificationSection::Second);
    addProperty("Grib2.IdentificationSection.ProductionStatusOfProcessedData",IdentificationSection::ProductionStatusOfProcessedData);
    addProperty("Grib2.IdentificationSection.TypeOfProcessedData",IdentificationSection::TypeOfProcessedData);

    addProperty("Grib2.GridSection.SourceOfGridDefinition",GridSection::SourceOfGridDefinition);
    addProperty("Grib2.GridSection.NumberOfGridPoints",GridSection::NumberOfGridPoints);
    addProperty("Grib2.GridSection.NumberOfOctetsForNumberOfPoints",GridSection::NumberOfOctetsForNumberOfPoints);
    addProperty("Grib2.GridSection.InterpretationOfNumberOfPoints",GridSection::InterpretationOfNumberOfPoints);
    addProperty("Grib2.GridSection.GridDefinitionTemplateNumber",GridSection::GridDefinitionTemplateNumber);

    addProperty("Grib2.GridSection.EarthShape.ShapeOfTheEarth",GridSection::EarthShape::ShapeOfTheEarth);
    addProperty("Grib2.GridSection.EarthShape.ScaleFactorOfRadiusOfSphericalEarth",GridSection::EarthShape::ScaleFactorOfRadiusOfSphericalEarth);
    addProperty("Grib2.GridSection.EarthShape.ScaledValueOfRadiusOfSphericalEarth",GridSection::EarthShape::ScaledValueOfRadiusOfSphericalEarth);
    addProperty("Grib2.GridSection.EarthShape.ScaleFactorOfEarthMajorAxis",GridSection::EarthShape::ScaleFactorOfEarthMajorAxis);
    addProperty("Grib2.GridSection.EarthShape.ScaledValueOfEarthMajorAxis",GridSection::EarthShape::ScaledValueOfEarthMajorAxis);
    addProperty("Grib2.GridSection.EarthShape.ScaleFactorOfEarthMinorAxis",GridSection::EarthShape::ScaleFactorOfEarthMinorAxis);
    addProperty("Grib2.GridSection.EarthShape.ScaledValueOfEarthMinorAxis",GridSection::EarthShape::ScaledValueOfEarthMinorAxis);

    addProperty("Grib2.GridSection.Grid.Ni",GridSection::Grid::Ni);
    addProperty("Grib2.GridSection.Grid.Nj",GridSection::Grid::Nj);
    addProperty("Grib2.GridSection.Grid.BasicAngleOfTheInitialProductionDomain",GridSection::Grid::BasicAngleOfTheInitialProductionDomain);
    addProperty("Grib2.GridSection.Grid.SubdivisionsOfBasicAngle",GridSection::Grid::SubdivisionsOfBasicAngle);
    addProperty("Grib2.GridSection.Grid.LatitudeOfFirstGridPoint",GridSection::Grid::LatitudeOfFirstGridPoint);
    addProperty("Grib2.GridSection.Grid.LongitudeOfFirstGridPoint",GridSection::Grid::LongitudeOfFirstGridPoint);
    addProperty("Grib2.GridSection.Grid.LatitudeOfLastGridPoint",GridSection::Grid::LatitudeOfLastGridPoint);
    addProperty("Grib2.GridSection.Grid.LongitudeOfLastGridPoint",GridSection::Grid::LongitudeOfLastGridPoint);
    addProperty("Grib2.GridSection.Grid.ResolutionAndComponentFlags",GridSection::Grid::ResolutionAndComponentFlags);

    addProperty("Grib2.GridSection.Rotation.LatitudeOfSouthernPole",GridSection::Rotation::LatitudeOfSouthernPole);
    addProperty("Grib2.GridSection.Rotation.LongitudeOfSouthernPole",GridSection::Rotation::LongitudeOfSouthernPole);
    addProperty("Grib2.GridSection.Rotation.AngleOfRotation",GridSection::Rotation::AngleOfRotation);

    addProperty("Grib2.GridSection.LatLon.IDirectionIncrement",GridSection::LatLon::IDirectionIncrement);
    addProperty("Grib2.GridSection.LatLon.JDirectionIncrement",GridSection::LatLon::JDirectionIncrement);
    addProperty("Grib2.GridSection.LatLon.ScanningMode",GridSection::LatLon::ScanningMode);

    addProperty("Grib2.GridSection.PolarStereographic.Nx",GridSection::PolarStereographic::Nx);
    addProperty("Grib2.GridSection.PolarStereographic.Ny",GridSection::PolarStereographic::Ny);
    addProperty("Grib2.GridSection.PolarStereographic.LatitudeOfFirstGridPoint",GridSection::PolarStereographic::LatitudeOfFirstGridPoint);
    addProperty("Grib2.GridSection.PolarStereographic.LongitudeOfFirstGridPoint",GridSection::PolarStereographic::LongitudeOfFirstGridPoint);
    addProperty("Grib2.GridSection.PolarStereographic.ResolutionAndComponentFlags",GridSection::PolarStereographic::ResolutionAndComponentFlags);
    addProperty("Grib2.GridSection.PolarStereographic.LaD",GridSection::PolarStereographic::LaD);
    addProperty("Grib2.GridSection.PolarStereographic.OrientationOfTheGrid",GridSection::PolarStereographic::OrientationOfTheGrid);
    addProperty("Grib2.GridSection.PolarStereographic.Dx",GridSection::PolarStereographic::Dx);
    addProperty("Grib2.GridSection.PolarStereographic.Dy",GridSection::PolarStereographic::Dy);
    addProperty("Grib2.GridSection.PolarStereographic.ProjectionCentreFlag",GridSection::PolarStereographic::ProjectionCentreFlag);
    addProperty("Grib2.GridSection.PolarStereographic.ScanningMode",GridSection::PolarStereographic::ScanningMode);

    addProperty("Grib2.GridSection.LambertConformal.Nx",GridSection::LambertConformal::Nx);
    addProperty("Grib2.GridSection.LambertConformal.Ny",GridSection::LambertConformal::Ny);
    addProperty("Grib2.GridSection.LambertConformal.LatitudeOfFirstGridPoint",GridSection::LambertConformal::LatitudeOfFirstGridPoint);
    addProperty("Grib2.GridSection.LambertConformal.LongitudeOfFirstGridPoint",GridSection::LambertConformal::LongitudeOfFirstGridPoint);
    addProperty("Grib2.GridSection.LambertConformal.ResolutionAndComponentFlags",GridSection::LambertConformal::ResolutionAndComponentFlags);
    addProperty("Grib2.GridSection.LambertConformal.LaD",GridSection::LambertConformal::LaD);
    addProperty("Grib2.GridSection.LambertConformal.LoV",GridSection::LambertConformal::LoV);
    addProperty("Grib2.GridSection.LambertConformal.Dx",GridSection::LambertConformal::Dx);
    addProperty("Grib2.GridSection.LambertConformal.Dy",GridSection::LambertConformal::Dy);
    addProperty("Grib2.GridSection.LambertConformal.ProjectionCentreFlag",GridSection::LambertConformal::ProjectionCentreFlag);
    addProperty("Grib2.GridSection.LambertConformal.ScanningMode",GridSection::LambertConformal::ScanningMode);
    addProperty("Grib2.GridSection.LambertConformal.Latin1",GridSection::LambertConformal::Latin1);
    addProperty("Grib2.GridSection.LambertConformal.Latin2",GridSection::LambertConformal::Latin2);
    addProperty("Grib2.GridSection.LambertConformal.LatitudeOfSouthernPole",GridSection::LambertConformal::LatitudeOfSouthernPole);
    addProperty("Grib2.GridSection.LambertConformal.LongitudeOfSouthernPole",GridSection::LambertConformal::LongitudeOfSouthernPole);

    addProperty("Grib2.GridSection.Mercator.Ni",GridSection::Mercator::Ni);
    addProperty("Grib2.GridSection.Mercator.Nj",GridSection::Mercator::Nj);
    addProperty("Grib2.GridSection.Mercator.LatitudeOfFirstGridPoint",GridSection::Mercator::LatitudeOfFirstGridPoint);
    addProperty("Grib2.GridSection.Mercator.LongitudeOfFirstGridPoint",GridSection::Mercator::LongitudeOfFirstGridPoint);
    addProperty("Grib2.GridSection.Mercator.LaD",GridSection::Mercator::LaD);
    addProperty("Grib2.GridSection.Mercator.LatitudeOfLastGridPoint",GridSection::Mercator::LatitudeOfLastGridPoint);
    addProperty("Grib2.GridSection.Mercator.LongitudeOfLastGridPoint",GridSection::Mercator::LongitudeOfLastGridPoint);
    addProperty("Grib2.GridSection.Mercator.OrientationOfTheGrid",GridSection::Mercator::OrientationOfTheGrid);
    addProperty("Grib2.GridSection.Mercator.Di",GridSection::Mercator::Di);
    addProperty("Grib2.GridSection.Mercator.Dj",GridSection::Mercator::Dj);
    addProperty("Grib2.GridSection.Mercator.ResolutionAndComponentFlags",GridSection::Mercator::ResolutionAndComponentFlags);
    addProperty("Grib2.GridSection.Mercator.ScanningMode",GridSection::Mercator::ScanningMode);

    addProperty("Grib2.ProductSection.ProductDefinitionTemplateNumber",ProductSection::ProductDefinitionTemplateNumber);

    addProperty("Grib2.ProductSection.ParameterSettings.ParameterCategory",ProductSection::ParameterSettings::ParameterCategory);
    addProperty("Grib2.ProductSection.ParameterSettings.ParameterNumber",ProductSection::ParameterSettings::ParameterNumber);
    addProperty("Grib2.ProductSection.ParameterSettings.TypeOfGeneratingProcess",ProductSection::ParameterSettings::TypeOfGeneratingProcess);
    addProperty("Grib2.ProductSection.ParameterSettings.BackgroundProcess",ProductSection::ParameterSettings::BackgroundProcess);
    addProperty("Grib2.ProductSection.ParameterSettings.GeneratingProcessIdentifier",ProductSection::ParameterSettings::GeneratingProcessIdentifier);
    addProperty("Grib2.ProductSection.ParameterSettings.HoursAfterDataCutoff",ProductSection::ParameterSettings::HoursAfterDataCutoff);
    addProperty("Grib2.ProductSection.ParameterSettings.MinutesAfterDataCutoff",ProductSection::ParameterSettings::MinutesAfterDataCutoff);
    addProperty("Grib2.ProductSection.ParameterSettings.IndicatorOfUnitOfTimeRange",ProductSection::ParameterSettings::IndicatorOfUnitOfTimeRange);
    addProperty("Grib2.ProductSection.ParameterSettings.ForecastTime",ProductSection::ParameterSettings::ForecastTime);

    addProperty("Grib2.ProductSection.HorizontalSettings.TypeOfFirstFixedSurface",ProductSection::HorizontalSettings::TypeOfFirstFixedSurface);
    addProperty("Grib2.ProductSection.HorizontalSettings.ScaleFactorOfFirstFixedSurface",ProductSection::HorizontalSettings::ScaleFactorOfFirstFixedSurface);
    addProperty("Grib2.ProductSection.HorizontalSettings.ScaledValueOfFirstFixedSurface",ProductSection::HorizontalSettings::ScaledValueOfFirstFixedSurface);
    addProperty("Grib2.ProductSection.HorizontalSettings.TypeOfSecondFixedSurface",ProductSection::HorizontalSettings::TypeOfSecondFixedSurface);
    addProperty("Grib2.ProductSection.HorizontalSettings.ScaleFactorOfSecondFixedSurface",ProductSection::HorizontalSettings::ScaleFactorOfSecondFixedSurface);
    addProperty("Grib2.ProductSection.HorizontalSettings.ScaledValueOfSecondFixedSurface",ProductSection::HorizontalSettings::ScaledValueOfSecondFixedSurface);

    addProperty("Grib2.ProductSection.StatisticalSettings.YearOfEndOfOverallTimeInterval",ProductSection::StatisticalSettings::YearOfEndOfOverallTimeInterval);
    addProperty("Grib2.ProductSection.StatisticalSettings.MonthOfEndOfOverallTimeInterval",ProductSection::StatisticalSettings::MonthOfEndOfOverallTimeInterval);
    addProperty("Grib2.ProductSection.StatisticalSettings.DayOfEndOfOverallTimeInterval",ProductSection::StatisticalSettings::DayOfEndOfOverallTimeInterval);
    addProperty("Grib2.ProductSection.StatisticalSettings.HourOfEndOfOverallTimeInterval",ProductSection::StatisticalSettings::HourOfEndOfOverallTimeInterval);
    addProperty("Grib2.ProductSection.StatisticalSettings.MinuteOfEndOfOverallTimeInterval",ProductSection::StatisticalSettings::MinuteOfEndOfOverallTimeInterval);
    addProperty("Grib2.ProductSection.StatisticalSettings.SecondOfEndOfOverallTimeInterval",ProductSection::StatisticalSettings::SecondOfEndOfOverallTimeInterval);
    addProperty("Grib2.ProductSection.StatisticalSettings.NumberOfTimeRange",ProductSection::StatisticalSettings::NumberOfTimeRange);
    addProperty("Grib2.ProductSection.StatisticalSettings.NumberOfMissingInStatisticalProcess",ProductSection::StatisticalSettings::NumberOfMissingInStatisticalProcess);
    addProperty("Grib2.ProductSection.StatisticalSettings.TypeOfStatisticalProcessing",ProductSection::StatisticalSettings::TypeOfStatisticalProcessing);
    addProperty("Grib2.ProductSection.StatisticalSettings.TypeOfTimeIncrement",ProductSection::StatisticalSettings::TypeOfTimeIncrement);
    addProperty("Grib2.ProductSection.StatisticalSettings.IndicatorOfUnitForTimeRange",ProductSection::StatisticalSettings::IndicatorOfUnitForTimeRange);
    addProperty("Grib2.ProductSection.StatisticalSettings.LengthOfTimeRange",ProductSection::StatisticalSettings::LengthOfTimeRange);
    addProperty("Grib2.ProductSection.StatisticalSettings.IndicatorOfUnitForTimeIncrement",ProductSection::StatisticalSettings::IndicatorOfUnitForTimeIncrement);
    addProperty("Grib2.ProductSection.StatisticalSettings.TimeIncrement",ProductSection::StatisticalSettings::TimeIncrement);

    addProperty("Grib2.ProductSection.EpsSettings.TypeOfEnsembleForecast",ProductSection::EpsSettings::TypeOfEnsembleForecast);
    addProperty("Grib2.ProductSection.EpsSettings.PerturbationNumber",ProductSection::EpsSettings::PerturbationNumber);
    addProperty("Grib2.ProductSection.EpsSettings.NumberOfForecastsInEnsemble",ProductSection::EpsSettings::NumberOfForecastsInEnsemble);

    addProperty("Grib2.ProductSection.DerivedSettings.DerivedForecast",ProductSection::DerivedSettings::DerivedForecast);
    addProperty("Grib2.ProductSection.DerivedSettings.NumberOfForecastsInEnsemble",ProductSection::DerivedSettings::NumberOfForecastsInEnsemble);

    addProperty("Grib2.ProductSection.RectangularClusterSettings.ClusterIdentifier",ProductSection::RectangularClusterSettings::ClusterIdentifier);
    addProperty("Grib2.ProductSection.RectangularClusterSettings.NH",ProductSection::RectangularClusterSettings::NH);
    addProperty("Grib2.ProductSection.RectangularClusterSettings.NL",ProductSection::RectangularClusterSettings::NL);
    addProperty("Grib2.ProductSection.RectangularClusterSettings.TotalNumberOfClusters",ProductSection::RectangularClusterSettings::TotalNumberOfClusters);
    addProperty("Grib2.ProductSection.RectangularClusterSettings.ClusteringMethod",ProductSection::RectangularClusterSettings::ClusteringMethod);
    addProperty("Grib2.ProductSection.RectangularClusterSettings.NorthernLatitudeOfClusterDomain",ProductSection::RectangularClusterSettings::NorthernLatitudeOfClusterDomain);
    addProperty("Grib2.ProductSection.RectangularClusterSettings.SouthernLatitudeOfClusterDomain",ProductSection::RectangularClusterSettings::SouthernLatitudeOfClusterDomain);
    addProperty("Grib2.ProductSection.RectangularClusterSettings.EasternLongitudeOfClusterDomain",ProductSection::RectangularClusterSettings::EasternLongitudeOfClusterDomain);
    addProperty("Grib2.ProductSection.RectangularClusterSettings.WesternLongitudeOfClusterDomain",ProductSection::RectangularClusterSettings::WesternLongitudeOfClusterDomain);
    addProperty("Grib2.ProductSection.RectangularClusterSettings.NumberOfForecastsInTheCluster",ProductSection::RectangularClusterSettings::NumberOfForecastsInTheCluster);
    addProperty("Grib2.ProductSection.RectangularClusterSettings.ScaleFactorOfStandardDeviation",ProductSection::RectangularClusterSettings::ScaleFactorOfStandardDeviation);
    addProperty("Grib2.ProductSection.RectangularClusterSettings.ScaledValueOfStandardDeviation",ProductSection::RectangularClusterSettings::ScaledValueOfStandardDeviation);
    addProperty("Grib2.ProductSection.RectangularClusterSettings.ScaleFactorOfDistanceFromEnsembleMean",ProductSection::RectangularClusterSettings::ScaleFactorOfDistanceFromEnsembleMean);
    addProperty("Grib2.ProductSection.RectangularClusterSettings.ScaledValueOfDistanceFromEnsembleMean",ProductSection::RectangularClusterSettings::ScaledValueOfDistanceFromEnsembleMean);

    addProperty("Grib2.ProductSection.ProbabilitySettings.ForecastProbabilityNumber",ProductSection::ProbabilitySettings::ForecastProbabilityNumber);
    addProperty("Grib2.ProductSection.ProbabilitySettings.TotalNumberOfForecastProbabilities",ProductSection::ProbabilitySettings::TotalNumberOfForecastProbabilities);
    addProperty("Grib2.ProductSection.ProbabilitySettings.ProbabilityType",ProductSection::ProbabilitySettings::ProbabilityType);
    addProperty("Grib2.ProductSection.ProbabilitySettings.ScaleFactorOfLowerLimit",ProductSection::ProbabilitySettings::ScaleFactorOfLowerLimit);
    addProperty("Grib2.ProductSection.ProbabilitySettings.ScaledValueOfLowerLimit",ProductSection::ProbabilitySettings::ScaledValueOfLowerLimit);
    addProperty("Grib2.ProductSection.ProbabilitySettings.ScaleFactorOfUpperLimit",ProductSection::ProbabilitySettings::ScaleFactorOfUpperLimit);
    addProperty("Grib2.ProductSection.ProbabilitySettings.ScaledValueOfUpperLimit",ProductSection::ProbabilitySettings::ScaledValueOfUpperLimit);

    addProperty("Grib2.ProductSection.PercentileSettings.PercentileValue",ProductSection::PercentileSettings::PercentileValue);

    addProperty("Grib2.ProductSection.CategoricalSettings.NumberOfCategories",ProductSection::CategoricalSettings::NumberOfCategories);
    addProperty("Grib2.ProductSection.CategoricalSettings.CategoryType",ProductSection::CategoricalSettings::CategoryType);
    addProperty("Grib2.ProductSection.CategoricalSettings.CodeFigure",ProductSection::CategoricalSettings::CodeFigure);
    addProperty("Grib2.ProductSection.CategoricalSettings.ScaleFactorOfLowerLimit",ProductSection::CategoricalSettings::ScaleFactorOfLowerLimit);
    addProperty("Grib2.ProductSection.CategoricalSettings.ScaledValueOfLowerLimit",ProductSection::CategoricalSettings::ScaledValueOfLowerLimit);
    addProperty("Grib2.ProductSection.CategoricalSettings.ScaleFactorOfUpperLimit",ProductSection::CategoricalSettings::ScaleFactorOfUpperLimit);
    addProperty("Grib2.ProductSection.CategoricalSettings.ScaledValueOfUpperLimit",ProductSection::CategoricalSettings::ScaledValueOfUpperLimit);

    addProperty("Grib2.RepresentationSection.RepresentationTemplateNumber",RepresentationSection::RepresentationTemplateNumber);

    addProperty("Grib2.RepresentationSection.Packing.ReferenceValue",RepresentationSection::Packing::ReferenceValue);
    addProperty("Grib2.RepresentationSection.Packing.BinaryScaleFactor",RepresentationSection::Packing::BinaryScaleFactor);
    addProperty("Grib2.RepresentationSection.Packing.DecimalScaleFactor",RepresentationSection::Packing::DecimalScaleFactor);
    addProperty("Grib2.RepresentationSection.Packing.BitsPerValue",RepresentationSection::Packing::BitsPerValue);

    addProperty("Grib2.RepresentationSection.OriginalValues.TypeOfOriginalFieldValues",RepresentationSection::OriginalValues::TypeOfOriginalFieldValues);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





Property::~Property()
{
  try
  {
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.printError();
  }
}




void Property::addProperty(const char *name,uint id)
{
  try
  {
    propertyMap.insert(std::pair<std::string,uint>(name,id));
    propertyVector.push_back(std::pair<std::string,uint>(name,id));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint Property::getPropertyId(const char *name)
{
  try
  {
    auto it = propertyMap.find(name);
    if (it != propertyMap.end())
      return it->second;

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string Property::getPropertyName(uint id)
{
  try
  {
    for (auto it = propertyMap.begin(); it != propertyMap.end(); ++it)
    {
      if (it->second == id)
        return it->first;
    }

    return "";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::PropertyMap& Property::getPropertyMap()
{
  try
  {
    return propertyMap;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::PropertyVec& Property::getPropertyVector()
{
  try
  {
    // Property id vector is used, because the properties should be set in a correct order.
    return propertyVector;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
}
