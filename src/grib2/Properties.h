#pragma once

#include "../grid/Typedefs.h"

#include <map>
#include <vector>
#include <string>


namespace SmartMet
{
namespace GRIB2
{

class Property
{
  public:

                      Property();
    virtual           ~Property();

    void              addProperty(const char *name,uint id);
    uint              getPropertyId(const char *name);
    std::string       getPropertyName(uint id);
    T::PropertyMap&   getPropertyMap();
    T::PropertyVec&   getPropertyVector();


    constexpr static uint FirstProperty                       = 2000;

    class IndicatorSection
    {
      public:
        constexpr static uint FirstProperty                     = Property::FirstProperty;
        constexpr static uint Discipline                        = FirstProperty + 0;
        constexpr static uint EditionNumber                     = FirstProperty + 1;
        constexpr static uint LastProperty                      = FirstProperty + 1;
    };


    class IdentificationSection
    {
      public:
        constexpr static uint FirstProperty                     = IndicatorSection::LastProperty + 1;
        constexpr static uint Centre                            = FirstProperty + 0;
        constexpr static uint SubCentre                         = FirstProperty + 1;
        constexpr static uint TablesVersion                     = FirstProperty + 2;
        constexpr static uint LocalTablesVersion                = FirstProperty + 3;
        constexpr static uint SignificanceOfReferenceTime       = FirstProperty + 4;
        constexpr static uint Year                              = FirstProperty + 5;
        constexpr static uint Month                             = FirstProperty + 6;
        constexpr static uint Day                               = FirstProperty + 7;
        constexpr static uint Hour                              = FirstProperty + 8;
        constexpr static uint Minute                            = FirstProperty + 9;
        constexpr static uint Second                            = FirstProperty + 10;
        constexpr static uint ProductionStatusOfProcessedData   = FirstProperty + 11;
        constexpr static uint TypeOfProcessedData               = FirstProperty + 12;
        constexpr static uint LastProperty                      = FirstProperty + 12;
    };


    class LocalSection
    {
      public:
        constexpr static uint FirstProperty                     = IdentificationSection::LastProperty +1;
        constexpr static uint LastProperty                      = FirstProperty + 0;
    };


    class GridSection
    {
      public:
        constexpr static uint FirstProperty                     = LocalSection::LastProperty + 1;
        constexpr static uint SourceOfGridDefinition            = FirstProperty + 0;
        constexpr static uint NumberOfGridPoints                = FirstProperty + 1;
        constexpr static uint NumberOfOctetsForNumberOfPoints   = FirstProperty + 2;
        constexpr static uint InterpretationOfNumberOfPoints    = FirstProperty + 3;
        constexpr static uint GridDefinitionTemplateNumber      = FirstProperty + 4;


        class EarthShape
        {
          public:
            constexpr static uint FirstProperty                 = GridSection::FirstProperty + 5;
            constexpr static uint ShapeOfTheEarth               = FirstProperty + 0;
            constexpr static uint ScaleFactorOfRadiusOfSphericalEarth = FirstProperty + 1;
            constexpr static uint ScaledValueOfRadiusOfSphericalEarth = FirstProperty + 2;
            constexpr static uint ScaleFactorOfEarthMajorAxis   = FirstProperty + 3;
            constexpr static uint ScaledValueOfEarthMajorAxis   = FirstProperty + 4;
            constexpr static uint ScaleFactorOfEarthMinorAxis   = FirstProperty + 5;
            constexpr static uint ScaledValueOfEarthMinorAxis   = FirstProperty + 6;
            constexpr static uint LastProperty                  = FirstProperty + 6;
        };

        class Grid
        {
          public:
            constexpr static uint FirstProperty                 = EarthShape::LastProperty + 1;
            constexpr static uint Ni                            = FirstProperty + 0;
            constexpr static uint Nj                            = FirstProperty + 1;
            constexpr static uint BasicAngleOfTheInitialProductionDomain = FirstProperty + 2;
            constexpr static uint SubdivisionsOfBasicAngle      = FirstProperty + 3;
            constexpr static uint LatitudeOfFirstGridPoint      = FirstProperty + 4;
            constexpr static uint LongitudeOfFirstGridPoint     = FirstProperty + 5;
            constexpr static uint LatitudeOfLastGridPoint       = FirstProperty + 6;
            constexpr static uint LongitudeOfLastGridPoint      = FirstProperty + 7;
            constexpr static uint ResolutionAndComponentFlags   = FirstProperty + 8;
            constexpr static uint LastProperty                  = FirstProperty + 8;
        };

        class Rotation
        {
          public:
            constexpr static uint FirstProperty                 = Grid::LastProperty + 1;
            constexpr static uint LatitudeOfSouthernPole        = FirstProperty + 0;
            constexpr static uint LongitudeOfSouthernPole       = FirstProperty + 1;
            constexpr static uint AngleOfRotation               = FirstProperty + 2;
            constexpr static uint LastProperty                  = FirstProperty + 2;
        };


        class LatLon
        {
          public:
            constexpr static uint FirstProperty                 = Rotation::LastProperty + 1;
            constexpr static uint IDirectionIncrement           = FirstProperty + 0;
            constexpr static uint JDirectionIncrement           = FirstProperty + 1;
            constexpr static uint ScanningMode                  = FirstProperty + 2;
            constexpr static uint LastProperty                  = FirstProperty + 2;
        };

        class PolarStereographic
        {
          public:
            constexpr static uint FirstProperty                 = LatLon::LastProperty + 1;
            constexpr static uint Nx                            = FirstProperty + 0;
            constexpr static uint Ny                            = FirstProperty + 1;
            constexpr static uint LatitudeOfFirstGridPoint      = FirstProperty + 2;
            constexpr static uint LongitudeOfFirstGridPoint     = FirstProperty + 3;
            constexpr static uint ResolutionAndComponentFlags   = FirstProperty + 4;
            constexpr static uint LaD                           = FirstProperty + 5;
            constexpr static uint OrientationOfTheGrid          = FirstProperty + 6;
            constexpr static uint Dx                            = FirstProperty + 7;
            constexpr static uint Dy                            = FirstProperty + 8;
            constexpr static uint ProjectionCentreFlag          = FirstProperty + 9;
            constexpr static uint ScanningMode                  = FirstProperty + 10;
            constexpr static uint LastProperty                  = FirstProperty + 10;
        };

        class LambertConformal
        {
          public:
            constexpr static uint FirstProperty                 = PolarStereographic::LastProperty + 1;
            constexpr static uint Nx                            = FirstProperty + 0;
            constexpr static uint Ny                            = FirstProperty + 1;
            constexpr static uint LatitudeOfFirstGridPoint      = FirstProperty + 2;
            constexpr static uint LongitudeOfFirstGridPoint     = FirstProperty + 3;
            constexpr static uint ResolutionAndComponentFlags   = FirstProperty + 4;
            constexpr static uint LaD                           = FirstProperty + 5;
            constexpr static uint LoV                           = FirstProperty + 6;
            constexpr static uint Dx                            = FirstProperty + 7;
            constexpr static uint Dy                            = FirstProperty + 8;
            constexpr static uint ProjectionCentreFlag          = FirstProperty + 9;
            constexpr static uint ScanningMode                  = FirstProperty + 10;
            constexpr static uint Latin1                        = FirstProperty + 11;
            constexpr static uint Latin2                        = FirstProperty + 12;
            constexpr static uint LatitudeOfSouthernPole        = FirstProperty + 13;
            constexpr static uint LongitudeOfSouthernPole       = FirstProperty + 14;
            constexpr static uint LastProperty                  = FirstProperty + 14;
        };


        class Mercator
        {
          public:
            constexpr static uint FirstProperty                 = LambertConformal::LastProperty + 1;
            constexpr static uint Ni                            = FirstProperty + 0;
            constexpr static uint Nj                            = FirstProperty + 1;
            constexpr static uint LatitudeOfFirstGridPoint      = FirstProperty + 2;
            constexpr static uint LongitudeOfFirstGridPoint     = FirstProperty + 3;
            constexpr static uint LaD                           = FirstProperty + 4;
            constexpr static uint LatitudeOfLastGridPoint       = FirstProperty + 5;
            constexpr static uint LongitudeOfLastGridPoint      = FirstProperty + 6;
            constexpr static uint OrientationOfTheGrid          = FirstProperty + 7;
            constexpr static uint Di                            = FirstProperty + 8;
            constexpr static uint Dj                            = FirstProperty + 9;
            constexpr static uint ResolutionAndComponentFlags   = FirstProperty + 10;
            constexpr static uint ScanningMode                  = FirstProperty + 11;
            constexpr static uint LastProperty                  = FirstProperty + 11;
        };

        constexpr static uint LastProperty                = Mercator::LastProperty;
    };


    class ProductSection
    {
      public:
        constexpr static uint FirstProperty               = GridSection::LastProperty + 1;
        constexpr static uint ProductDefinitionTemplateNumber = FirstProperty + 0;
        constexpr static uint NV                          = FirstProperty + 1;

        class ParameterSettings
        {
          public:
            constexpr static uint FirstProperty           = ProductSection::FirstProperty + 10;
            constexpr static uint ParameterCategory       = FirstProperty + 0;
            constexpr static uint ParameterNumber         = FirstProperty + 1;
            constexpr static uint TypeOfGeneratingProcess = FirstProperty + 2;
            constexpr static uint BackgroundProcess       = FirstProperty + 3;
            constexpr static uint GeneratingProcessIdentifier = FirstProperty + 4;
            constexpr static uint HoursAfterDataCutoff    = FirstProperty + 5;
            constexpr static uint MinutesAfterDataCutoff  = FirstProperty + 6;
            constexpr static uint IndicatorOfUnitOfTimeRange = FirstProperty + 7;
            constexpr static uint ForecastTime            = FirstProperty + 8;
            constexpr static uint LastProperty            = FirstProperty + 8;
        };

        class HorizontalSettings
        {
          public:
            constexpr static uint FirstProperty           = ParameterSettings::LastProperty + 1;
            constexpr static uint TypeOfFirstFixedSurface = FirstProperty + 0;
            constexpr static uint ScaleFactorOfFirstFixedSurface = FirstProperty + 1;
            constexpr static uint ScaledValueOfFirstFixedSurface = FirstProperty + 2;
            constexpr static uint TypeOfSecondFixedSurface = FirstProperty + 3;
            constexpr static uint ScaleFactorOfSecondFixedSurface = FirstProperty + 4;
            constexpr static uint ScaledValueOfSecondFixedSurface = FirstProperty + 5;
            constexpr static uint LastProperty            = FirstProperty + 5;
        };


        class StatisticalSettings
        {
          public:
            constexpr static uint FirstProperty               = HorizontalSettings::LastProperty + 1;
            constexpr static uint YearOfEndOfOverallTimeInterval = FirstProperty + 0;
            constexpr static uint MonthOfEndOfOverallTimeInterval = FirstProperty + 1;
            constexpr static uint DayOfEndOfOverallTimeInterval = FirstProperty + 2;
            constexpr static uint HourOfEndOfOverallTimeInterval = FirstProperty + 3;
            constexpr static uint MinuteOfEndOfOverallTimeInterval = FirstProperty + 4;
            constexpr static uint SecondOfEndOfOverallTimeInterval = FirstProperty + 5;
            constexpr static uint NumberOfTimeRange           = FirstProperty + 6;
            constexpr static uint NumberOfMissingInStatisticalProcess = FirstProperty + 7;
            constexpr static uint TypeOfStatisticalProcessing = FirstProperty + 8;
            constexpr static uint TypeOfTimeIncrement         = FirstProperty + 9;
            constexpr static uint IndicatorOfUnitForTimeRange = FirstProperty + 10;
            constexpr static uint LengthOfTimeRange           = FirstProperty + 11;
            constexpr static uint IndicatorOfUnitForTimeIncrement = FirstProperty + 12;
            constexpr static uint TimeIncrement               = FirstProperty + 13;
            constexpr static uint LastProperty                = FirstProperty + 13;
        };


        class EpsSettings
        {
          public:
            constexpr static uint FirstProperty               = StatisticalSettings::LastProperty + 1;
            constexpr static uint TypeOfEnsembleForecast      = FirstProperty + 0;
            constexpr static uint PerturbationNumber          = FirstProperty + 1;
            constexpr static uint NumberOfForecastsInEnsemble = FirstProperty + 2;
            constexpr static uint LastProperty                = FirstProperty + 2;
        };


        class DerivedSettings
        {
          public:
            constexpr static uint FirstProperty               = EpsSettings::LastProperty + 1;
            constexpr static uint DerivedForecast             = FirstProperty + 0;
            constexpr static uint NumberOfForecastsInEnsemble = FirstProperty + 1;
            constexpr static uint LastProperty                = FirstProperty + 1;
        };


        class RectangularClusterSettings
        {
          public:
            constexpr static uint FirstProperty               = DerivedSettings::LastProperty + 1;
            constexpr static uint ClusterIdentifier           = FirstProperty + 0;
            constexpr static uint NH                          = FirstProperty + 1;
            constexpr static uint NL                          = FirstProperty + 2;
            constexpr static uint TotalNumberOfClusters       = FirstProperty + 3;
            constexpr static uint ClusteringMethod            = FirstProperty + 4;
            constexpr static uint NorthernLatitudeOfClusterDomain = FirstProperty + 5;
            constexpr static uint SouthernLatitudeOfClusterDomain = FirstProperty + 6;
            constexpr static uint EasternLongitudeOfClusterDomain = FirstProperty + 7;
            constexpr static uint WesternLongitudeOfClusterDomain = FirstProperty + 8;
            constexpr static uint NumberOfForecastsInTheCluster = FirstProperty + 9;
            constexpr static uint ScaleFactorOfStandardDeviation = FirstProperty + 10;
            constexpr static uint ScaledValueOfStandardDeviation = FirstProperty + 11;
            constexpr static uint ScaleFactorOfDistanceFromEnsembleMean = FirstProperty + 12;
            constexpr static uint ScaledValueOfDistanceFromEnsembleMean = FirstProperty + 13;
            constexpr static uint LastProperty                = FirstProperty + 13;
        };


        class ProbabilitySettings
        {
          public:
            constexpr static uint FirstProperty               = RectangularClusterSettings::LastProperty + 1;
            constexpr static uint ForecastProbabilityNumber   = FirstProperty + 0;
            constexpr static uint TotalNumberOfForecastProbabilities = FirstProperty + 1;
            constexpr static uint ProbabilityType             = FirstProperty + 2;
            constexpr static uint ScaleFactorOfLowerLimit     = FirstProperty + 3;
            constexpr static uint ScaledValueOfLowerLimit     = FirstProperty + 4;
            constexpr static uint ScaleFactorOfUpperLimit     = FirstProperty + 5;
            constexpr static uint ScaledValueOfUpperLimit     = FirstProperty + 6;
            constexpr static uint LastProperty                = FirstProperty + 6;
        };


        class PercentileSettings
        {
          public:
            constexpr static uint FirstProperty               = ProbabilitySettings::LastProperty + 1;
            constexpr static uint PercentileValue             = FirstProperty + 0;
            constexpr static uint LastProperty                = FirstProperty + 0;
        };


        class CategoricalSettings
        {
          public:
            constexpr static uint FirstProperty               = PercentileSettings::LastProperty + 1;
            constexpr static uint NumberOfCategories          = FirstProperty + 0;
            constexpr static uint CategoryType                = FirstProperty + 1;
            constexpr static uint CodeFigure                  = FirstProperty + 2;
            constexpr static uint ScaleFactorOfLowerLimit     = FirstProperty + 3;
            constexpr static uint ScaledValueOfLowerLimit     = FirstProperty + 4;
            constexpr static uint ScaleFactorOfUpperLimit     = FirstProperty + 5;
            constexpr static uint ScaledValueOfUpperLimit     = FirstProperty + 6;
            constexpr static uint LastProperty                = FirstProperty + 6;
        };

        constexpr static uint LastProperty                = CategoricalSettings::LastProperty;
    };


    class RepresentationSection
    {
      public:
        constexpr static uint FirstProperty               = ProductSection::LastProperty + 1;
        constexpr static uint RepresentationTemplateNumber = FirstProperty + 0;

        class Packing
        {
          public:
            constexpr static uint FirstProperty           = RepresentationSection::FirstProperty + 10;
            constexpr static uint ReferenceValue          = FirstProperty + 0;
            constexpr static uint BinaryScaleFactor       = FirstProperty + 1;
            constexpr static uint DecimalScaleFactor      = FirstProperty + 2;
            constexpr static uint BitsPerValue            = FirstProperty + 3;
            constexpr static uint LastProperty            = FirstProperty + 3;
        };

        class OriginalValues
        {
          public:
            constexpr static uint FirstProperty           = Packing::LastProperty + 1;
            constexpr static uint TypeOfOriginalFieldValues = FirstProperty + 0;
            constexpr static uint LastProperty            = FirstProperty + 0;
        };

        constexpr static uint LastProperty                = OriginalValues::LastProperty;
    };


    class BitmapSection
    {
      public:
        constexpr static uint FirstProperty               = RepresentationSection::LastProperty;
        constexpr static uint LastProperty                = FirstProperty + 0;
    };


    class DataSection
    {
      public:
        constexpr static uint FirstProperty               = BitmapSection::LastProperty;
        constexpr static uint LastProperty                = FirstProperty + 0;
    };


    constexpr static uint LastProperty                    = DataSection::LastProperty;

  protected:

    T::PropertyMap    propertyMap;
    T::PropertyVec    propertyVector;

};  // class Propetry


extern Property gribProperty;

}  // namespace GRIB2
}  // namespace SmartMet
