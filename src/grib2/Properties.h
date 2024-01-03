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


    static const uint FirstProperty                                 = 2000;

    class IndicatorSection
    {
      public:
        static const uint FirstProperty                               = Property::FirstProperty;
        static const uint Discipline                                  = FirstProperty + 0;
        static const uint EditionNumber                               = FirstProperty + 1;
        static const uint LastProperty                                = FirstProperty + 1;
    };


    class IdentificationSection
    {
      public:
        static const uint FirstProperty                               = IndicatorSection::LastProperty + 1;
        static const uint Centre                                      = FirstProperty + 0;
        static const uint SubCentre                                   = FirstProperty + 1;
        static const uint TablesVersion                               = FirstProperty + 2;
        static const uint LocalTablesVersion                          = FirstProperty + 3;
        static const uint SignificanceOfReferenceTime                 = FirstProperty + 4;
        static const uint Year                                        = FirstProperty + 5;
        static const uint Month                                       = FirstProperty + 6;
        static const uint Day                                         = FirstProperty + 7;
        static const uint Hour                                        = FirstProperty + 8;
        static const uint Minute                                      = FirstProperty + 9;
        static const uint Second                                      = FirstProperty + 10;
        static const uint ProductionStatusOfProcessedData             = FirstProperty + 11;
        static const uint TypeOfProcessedData                         = FirstProperty + 12;
        static const uint LastProperty                                = FirstProperty + 12;
    };


    class LocalSection
    {
      public:
        static const uint FirstProperty                               = IdentificationSection::LastProperty +1;
        static const uint LastProperty                                = FirstProperty + 0;
    };


    class GridSection
    {
      public:
        static const uint FirstProperty                               = LocalSection::LastProperty + 1;
        static const uint SourceOfGridDefinition                      = FirstProperty + 0;
        static const uint NumberOfGridPoints                          = FirstProperty + 1;
        static const uint NumberOfOctetsForNumberOfPoints             = FirstProperty + 2;
        static const uint InterpretationOfNumberOfPoints              = FirstProperty + 3;
        static const uint GridDefinitionTemplateNumber                = FirstProperty + 4;


        class EarthShape
        {
          public:
            static const uint FirstProperty                           = GridSection::FirstProperty + 5;
            static const uint ShapeOfTheEarth                         = FirstProperty + 0;
            static const uint ScaleFactorOfRadiusOfSphericalEarth     = FirstProperty + 1;
            static const uint ScaledValueOfRadiusOfSphericalEarth     = FirstProperty + 2;
            static const uint ScaleFactorOfEarthMajorAxis             = FirstProperty + 3;
            static const uint ScaledValueOfEarthMajorAxis             = FirstProperty + 4;
            static const uint ScaleFactorOfEarthMinorAxis             = FirstProperty + 5;
            static const uint ScaledValueOfEarthMinorAxis             = FirstProperty + 6;
            static const uint LastProperty                            = FirstProperty + 6;
        };

        class Grid
        {
          public:
            static const uint FirstProperty                           = EarthShape::LastProperty + 1;
            static const uint Ni                                      = FirstProperty + 0;
            static const uint Nj                                      = FirstProperty + 1;
            static const uint BasicAngleOfTheInitialProductionDomain  = FirstProperty + 2;
            static const uint SubdivisionsOfBasicAngle                = FirstProperty + 3;
            static const uint LatitudeOfFirstGridPoint                = FirstProperty + 4;
            static const uint LongitudeOfFirstGridPoint               = FirstProperty + 5;
            static const uint LatitudeOfLastGridPoint                 = FirstProperty + 6;
            static const uint LongitudeOfLastGridPoint                = FirstProperty + 7;
            static const uint ResolutionAndComponentFlags             = FirstProperty + 8;
            static const uint LastProperty                            = FirstProperty + 8;
        };

        class Rotation
        {
          public:
            static const uint FirstProperty                           = Grid::LastProperty + 1;
            static const uint LatitudeOfSouthernPole                  = FirstProperty + 0;
            static const uint LongitudeOfSouthernPole                 = FirstProperty + 1;
            static const uint AngleOfRotation                         = FirstProperty + 2;
            static const uint LastProperty                            = FirstProperty + 2;
        };


        class LatLon
        {
          public:
            static const uint FirstProperty                           = Rotation::LastProperty + 1;
            static const uint IDirectionIncrement                     = FirstProperty + 0;
            static const uint JDirectionIncrement                     = FirstProperty + 1;
            static const uint ScanningMode                            = FirstProperty + 2;
            static const uint LastProperty                            = FirstProperty + 2;
        };

        class PolarStereographic
        {
          public:
            static const uint FirstProperty                           = LatLon::LastProperty + 1;
            static const uint Nx                                      = FirstProperty + 0;
            static const uint Ny                                      = FirstProperty + 1;
            static const uint LatitudeOfFirstGridPoint                = FirstProperty + 2;
            static const uint LongitudeOfFirstGridPoint               = FirstProperty + 3;
            static const uint ResolutionAndComponentFlags             = FirstProperty + 4;
            static const uint LaD                                     = FirstProperty + 5;
            static const uint OrientationOfTheGrid                    = FirstProperty + 6;
            static const uint Dx                                      = FirstProperty + 7;
            static const uint Dy                                      = FirstProperty + 8;
            static const uint ProjectionCentreFlag                    = FirstProperty + 9;
            static const uint ScanningMode                            = FirstProperty + 10;
            static const uint LastProperty                            = FirstProperty + 10;
        };

        class LambertConformal
        {
          public:
            static const uint FirstProperty                           = PolarStereographic::LastProperty + 1;
            static const uint Nx                                      = FirstProperty + 0;
            static const uint Ny                                      = FirstProperty + 1;
            static const uint LatitudeOfFirstGridPoint                = FirstProperty + 2;
            static const uint LongitudeOfFirstGridPoint               = FirstProperty + 3;
            static const uint ResolutionAndComponentFlags             = FirstProperty + 4;
            static const uint LaD                                     = FirstProperty + 5;
            static const uint LoV                                     = FirstProperty + 6;
            static const uint Dx                                      = FirstProperty + 7;
            static const uint Dy                                      = FirstProperty + 8;
            static const uint ProjectionCentreFlag                    = FirstProperty + 9;
            static const uint ScanningMode                            = FirstProperty + 10;
            static const uint Latin1                                  = FirstProperty + 11;
            static const uint Latin2                                  = FirstProperty + 12;
            static const uint LatitudeOfSouthernPole                  = FirstProperty + 13;
            static const uint LongitudeOfSouthernPole                 = FirstProperty + 14;
            static const uint LastProperty                            = FirstProperty + 14;
        };


        class Mercator
        {
          public:
            static const uint FirstProperty                           = LambertConformal::LastProperty + 1;
            static const uint Ni                                      = FirstProperty + 0;
            static const uint Nj                                      = FirstProperty + 1;
            static const uint LatitudeOfFirstGridPoint                = FirstProperty + 2;
            static const uint LongitudeOfFirstGridPoint               = FirstProperty + 3;
            static const uint LaD                                     = FirstProperty + 4;
            static const uint LatitudeOfLastGridPoint                 = FirstProperty + 5;
            static const uint LongitudeOfLastGridPoint                = FirstProperty + 6;
            static const uint OrientationOfTheGrid                    = FirstProperty + 7;
            static const uint Di                                      = FirstProperty + 8;
            static const uint Dj                                      = FirstProperty + 9;
            static const uint ResolutionAndComponentFlags             = FirstProperty + 10;
            static const uint ScanningMode                            = FirstProperty + 11;
            static const uint LastProperty                            = FirstProperty + 11;
        };

        static const uint LastProperty                          = Mercator::LastProperty;
    };


    class ProductSection
    {
      public:
        static const uint FirstProperty                         = GridSection::LastProperty + 1;
        static const uint ProductDefinitionTemplateNumber       = FirstProperty + 0;
        static const uint NV                                    = FirstProperty + 1;

        class ParameterSettings
        {
          public:
            static const uint FirstProperty                     = ProductSection::FirstProperty + 10;
            static const uint ParameterCategory                 = FirstProperty + 0;
            static const uint ParameterNumber                   = FirstProperty + 1;
            static const uint TypeOfGeneratingProcess           = FirstProperty + 2;
            static const uint BackgroundProcess                 = FirstProperty + 3;
            static const uint GeneratingProcessIdentifier       = FirstProperty + 4;
            static const uint HoursAfterDataCutoff              = FirstProperty + 5;
            static const uint MinutesAfterDataCutoff            = FirstProperty + 6;
            static const uint IndicatorOfUnitOfTimeRange        = FirstProperty + 7;
            static const uint ForecastTime                      = FirstProperty + 8;
            static const uint LastProperty                      = FirstProperty + 8;
        };

        class HorizontalSettings
        {
          public:
            static const uint FirstProperty                     = ParameterSettings::LastProperty + 1;
            static const uint TypeOfFirstFixedSurface           = FirstProperty + 0;
            static const uint ScaleFactorOfFirstFixedSurface    = FirstProperty + 1;
            static const uint ScaledValueOfFirstFixedSurface    = FirstProperty + 2;
            static const uint TypeOfSecondFixedSurface          = FirstProperty + 3;
            static const uint ScaleFactorOfSecondFixedSurface   = FirstProperty + 4;
            static const uint ScaledValueOfSecondFixedSurface   = FirstProperty + 5;
            static const uint LastProperty                      = FirstProperty + 5;
        };


        class StatisticalSettings
        {
          public:
            static const uint FirstProperty                         = HorizontalSettings::LastProperty + 1;
            static const uint YearOfEndOfOverallTimeInterval        = FirstProperty + 0;
            static const uint MonthOfEndOfOverallTimeInterval       = FirstProperty + 1;
            static const uint DayOfEndOfOverallTimeInterval         = FirstProperty + 2;
            static const uint HourOfEndOfOverallTimeInterval        = FirstProperty + 3;
            static const uint MinuteOfEndOfOverallTimeInterval      = FirstProperty + 4;
            static const uint SecondOfEndOfOverallTimeInterval      = FirstProperty + 5;
            static const uint NumberOfTimeRange                     = FirstProperty + 6;
            static const uint NumberOfMissingInStatisticalProcess   = FirstProperty + 7;
            static const uint TypeOfStatisticalProcessing           = FirstProperty + 8;
            static const uint TypeOfTimeIncrement                   = FirstProperty + 9;
            static const uint IndicatorOfUnitForTimeRange           = FirstProperty + 10;
            static const uint LengthOfTimeRange                     = FirstProperty + 11;
            static const uint IndicatorOfUnitForTimeIncrement       = FirstProperty + 12;
            static const uint TimeIncrement                         = FirstProperty + 13;
            static const uint LastProperty                          = FirstProperty + 13;
        };


        class EpsSettings
        {
          public:
            static const uint FirstProperty                         = StatisticalSettings::LastProperty + 1;
            static const uint TypeOfEnsembleForecast                = FirstProperty + 0;
            static const uint PerturbationNumber                    = FirstProperty + 1;
            static const uint NumberOfForecastsInEnsemble           = FirstProperty + 2;
            static const uint LastProperty                          = FirstProperty + 2;
        };


        class DerivedSettings
        {
          public:
            static const uint FirstProperty                         = EpsSettings::LastProperty + 1;
            static const uint DerivedForecast                       = FirstProperty + 0;
            static const uint NumberOfForecastsInEnsemble           = FirstProperty + 1;
            static const uint LastProperty                          = FirstProperty + 1;
        };


        class RectangularClusterSettings
        {
          public:
            static const uint FirstProperty                         = DerivedSettings::LastProperty + 1;
            static const uint ClusterIdentifier                     = FirstProperty + 0;
            static const uint NH                                    = FirstProperty + 1;
            static const uint NL                                    = FirstProperty + 2;
            static const uint TotalNumberOfClusters                 = FirstProperty + 3;
            static const uint ClusteringMethod                      = FirstProperty + 4;
            static const uint NorthernLatitudeOfClusterDomain       = FirstProperty + 5;
            static const uint SouthernLatitudeOfClusterDomain       = FirstProperty + 6;
            static const uint EasternLongitudeOfClusterDomain       = FirstProperty + 7;
            static const uint WesternLongitudeOfClusterDomain       = FirstProperty + 8;
            static const uint NumberOfForecastsInTheCluster         = FirstProperty + 9;
            static const uint ScaleFactorOfStandardDeviation        = FirstProperty + 10;
            static const uint ScaledValueOfStandardDeviation        = FirstProperty + 11;
            static const uint ScaleFactorOfDistanceFromEnsembleMean = FirstProperty + 12;
            static const uint ScaledValueOfDistanceFromEnsembleMean = FirstProperty + 13;
            static const uint LastProperty                          = FirstProperty + 13;
        };


        class ProbabilitySettings
        {
          public:
            static const uint FirstProperty                         = RectangularClusterSettings::LastProperty + 1;
            static const uint ForecastProbabilityNumber             = FirstProperty + 0;
            static const uint TotalNumberOfForecastProbabilities    = FirstProperty + 1;
            static const uint ProbabilityType                       = FirstProperty + 2;
            static const uint ScaleFactorOfLowerLimit               = FirstProperty + 3;
            static const uint ScaledValueOfLowerLimit               = FirstProperty + 4;
            static const uint ScaleFactorOfUpperLimit               = FirstProperty + 5;
            static const uint ScaledValueOfUpperLimit               = FirstProperty + 6;
            static const uint LastProperty                          = FirstProperty + 6;
        };


        class PercentileSettings
        {
          public:
            static const uint FirstProperty                         = ProbabilitySettings::LastProperty + 1;
            static const uint PercentileValue                       = FirstProperty + 0;
            static const uint LastProperty                          = FirstProperty + 0;
        };


        class CategoricalSettings
        {
          public:
            static const uint FirstProperty                         = PercentileSettings::LastProperty + 1;
            static const uint NumberOfCategories                    = FirstProperty + 0;
            static const uint CategoryType                          = FirstProperty + 1;
            static const uint CodeFigure                            = FirstProperty + 2;
            static const uint ScaleFactorOfLowerLimit               = FirstProperty + 3;
            static const uint ScaledValueOfLowerLimit               = FirstProperty + 4;
            static const uint ScaleFactorOfUpperLimit               = FirstProperty + 5;
            static const uint ScaledValueOfUpperLimit               = FirstProperty + 6;
            static const uint LastProperty                          = FirstProperty + 6;
        };

        static const uint LastProperty                          = CategoricalSettings::LastProperty;
    };


    class RepresentationSection
    {
      public:
        static const uint FirstProperty                         = ProductSection::LastProperty + 1;
        static const uint RepresentationTemplateNumber          = FirstProperty + 0;

        class Packing
        {
          public:
            static const uint FirstProperty                     = RepresentationSection::FirstProperty + 10;
            static const uint ReferenceValue                    = FirstProperty + 0;
            static const uint BinaryScaleFactor                 = FirstProperty + 1;
            static const uint DecimalScaleFactor                = FirstProperty + 2;
            static const uint BitsPerValue                      = FirstProperty + 3;
            static const uint LastProperty                      = FirstProperty + 3;
        };

        class OriginalValues
        {
          public:
            static const uint FirstProperty                     = Packing::LastProperty + 1;
            static const uint TypeOfOriginalFieldValues         = FirstProperty + 0;
            static const uint LastProperty                      = FirstProperty + 0;
        };

        static const uint LastProperty                          = OriginalValues::LastProperty;
    };


    class BitmapSection
    {
      public:
        static const uint FirstProperty                         = RepresentationSection::LastProperty;
        static const uint LastProperty                          = FirstProperty + 0;
    };


    class DataSection
    {
      public:
        static const uint FirstProperty                         = BitmapSection::LastProperty;
        static const uint LastProperty                          = FirstProperty + 0;
    };


    static const uint LastProperty                              = DataSection::LastProperty;

  protected:

    T::PropertyMap    propertyMap;
    T::PropertyVec    propertyVector;

};  // class Propetry


extern Property gribProperty;

}  // namespace GRIB2
}  // namespace SmartMet
