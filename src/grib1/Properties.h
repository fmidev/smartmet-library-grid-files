#pragma once

#include "../grid/Typedefs.h"

#include <map>
#include <vector>
#include <string>


namespace SmartMet
{
namespace GRIB1
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


    constexpr static const uint FirstProperty                       = 1000;

    class IndicatorSection
    {
      public:
        constexpr static const uint FirstProperty                   = Property::FirstProperty;
        constexpr static const uint EditionNumber                   = FirstProperty + 0;
        constexpr static const uint LastProperty                    = FirstProperty + 0;
    };

    class ProductSection
    {
      public:
        constexpr static const uint FirstProperty                   = IndicatorSection::LastProperty + 1;
        constexpr static const uint TableVersion                    = FirstProperty + 0;
        constexpr static const uint Centre                          = FirstProperty + 1;
        constexpr static const uint GeneratingProcessIdentifier     = FirstProperty + 2;
        constexpr static const uint GridDefinitionNumber            = FirstProperty + 3;
        constexpr static const uint SectionFlags                    = FirstProperty + 4;
        constexpr static const uint IndicatorOfParameter            = FirstProperty + 5;
        constexpr static const uint IndicatorOfTypeOfLevel          = FirstProperty + 6;
        constexpr static const uint Level                           = FirstProperty + 7;
        constexpr static const uint YearOfCentury                   = FirstProperty + 8;
        constexpr static const uint Month                           = FirstProperty + 9;
        constexpr static const uint Day                             = FirstProperty + 10;
        constexpr static const uint Hour                            = FirstProperty + 11;
        constexpr static const uint Minute                          = FirstProperty + 12;
        constexpr static const uint UnitOfTimeRange                 = FirstProperty + 13;
        constexpr static const uint P1                              = FirstProperty + 14;
        constexpr static const uint P2                              = FirstProperty + 15;
        constexpr static const uint TimeRangeIndicator              = FirstProperty + 16;
        constexpr static const uint NumberIncludedInAverage         = FirstProperty + 17;
        constexpr static const uint NumberMissingFromAveragesOrAccumulations = FirstProperty + 18;
        constexpr static const uint CenturyOfReferenceTimeOfData    = FirstProperty + 19;
        constexpr static const uint SubCentre                       = FirstProperty + 20;
        constexpr static const uint DecimalScaleFactor              = FirstProperty + 21;
        constexpr static const uint ForecastType                    = FirstProperty + 22;
        constexpr static const uint ForecastNumber                  = FirstProperty + 23;
        constexpr static const uint LastProperty                    = FirstProperty + 99;
    };

    class DataSection
    {
      public:
        constexpr static const uint FirstProperty                   = ProductSection::LastProperty + 1;
        constexpr static const uint Flags                           = FirstProperty + 0;
        constexpr static const uint BinaryScaleFactor               = FirstProperty + 1;
        constexpr static const uint ReferenceValue                  = FirstProperty + 2;
        constexpr static const uint BitsPerValue                    = FirstProperty + 3;
        constexpr static const uint PackingMethod                   = FirstProperty + 4;
        constexpr static const uint LastProperty                    = FirstProperty + 4;
    };

    class GridSection
    {
      public:
        constexpr static const uint FirstProperty                   = DataSection::LastProperty + 1;
        constexpr static const uint NumberOfVerticalCoordinateValues = FirstProperty + 0;
        constexpr static const uint PvlLocation                     = FirstProperty + 1;
        constexpr static const uint DataRepresentationType          = FirstProperty + 2;

        class LatLon
        {
          public:
            constexpr static const uint FirstProperty               = GridSection::FirstProperty + 3;
            constexpr static const uint Ni                          = FirstProperty + 0;
            constexpr static const uint Nj                          = FirstProperty + 1;
            constexpr static const uint IDirectionIncrement         = FirstProperty + 2;
            constexpr static const uint JDirectionIncrement         = FirstProperty + 3;
            constexpr static const uint LastProperty                = FirstProperty + 3;
        };

        class RotatedLatLon
        {
          public:
            constexpr static const uint FirstProperty               = LatLon::LastProperty + 1;
            constexpr static const uint Ni                          = FirstProperty + 0;
            constexpr static const uint Nj                          = FirstProperty + 1;
            constexpr static const uint IDirectionIncrement         = FirstProperty + 2;
            constexpr static const uint JDirectionIncrement         = FirstProperty + 3;
            constexpr static const uint LastProperty                = FirstProperty + 3;
        };


        class PolarStereographic
        {
          public:
            constexpr static const uint FirstProperty               = RotatedLatLon::LastProperty + 1;
            constexpr static const uint Nx                          = FirstProperty + 0;
            constexpr static const uint Ny                          = FirstProperty + 1;
            constexpr static const uint LatitudeOfFirstGridPoint    = FirstProperty + 2;
            constexpr static const uint LongitudeOfFirstGridPoint   = FirstProperty + 3;
            constexpr static const uint OrientationOfTheGrid        = FirstProperty + 4;
            constexpr static const uint DxInMetres                  = FirstProperty + 5;
            constexpr static const uint DyInMetres                  = FirstProperty + 6;
            constexpr static const uint ProjectionCentreFlag        = FirstProperty + 7;
            constexpr static const uint LastProperty                = FirstProperty + 7;
        };


        class LambertConformal
        {
          public:
            constexpr static const uint FirstProperty               = PolarStereographic::LastProperty + 1;
            constexpr static const uint Nx                          = FirstProperty + 0;
            constexpr static const uint Ny                          = FirstProperty + 1;
            constexpr static const uint LatitudeOfFirstGridPoint    = FirstProperty + 2;
            constexpr static const uint LongitudeOfFirstGridPoint   = FirstProperty + 3;
            constexpr static const uint LoV                         = FirstProperty + 4;
            constexpr static const uint DxInMetres                  = FirstProperty + 5;
            constexpr static const uint DyInMetres                  = FirstProperty + 6;
            constexpr static const uint ProjectionCentreFlag        = FirstProperty + 7;
            constexpr static const uint Latin1                      = FirstProperty + 8;
            constexpr static const uint Latin2                      = FirstProperty + 9;
            constexpr static const uint LatitudeOfSouthernPole      = FirstProperty + 10;
            constexpr static const uint LongitudeOfSouthernPole     = FirstProperty + 11;
            constexpr static const uint LastProperty                = FirstProperty + 11;
        };


        class Mercator
        {
          public:
            constexpr static const uint FirstProperty               = LambertConformal::LastProperty + 1;
            constexpr static const uint Ni                          = FirstProperty + 0;
            constexpr static const uint Nj                          = FirstProperty + 1;
            constexpr static const uint Latin                       = FirstProperty + 2;
            constexpr static const uint DiInMetres                  = FirstProperty + 3;
            constexpr static const uint DjInMetres                  = FirstProperty + 4;
            constexpr static const uint LastProperty                = FirstProperty + 4;
        };


        class GridArea
        {
          public:
            constexpr static const uint FirstProperty               = Mercator::LastProperty + 1;
            constexpr static const uint LatitudeOfFirstGridPoint    = FirstProperty + 0;
            constexpr static const uint LongitudeOfFirstGridPoint   = FirstProperty + 1;
            constexpr static const uint LatitudeOfLastGridPoint     = FirstProperty + 2;
            constexpr static const uint LongitudeOfLastGridPoint    = FirstProperty + 3;
            constexpr static const uint LastProperty                = FirstProperty + 3;
        };

        class ResolutionFlags
        {
          public:
            constexpr static const uint FirstProperty               = GridArea::LastProperty + 1;
            constexpr static const uint ResolutionAndComponentFlags = FirstProperty + 0;
            constexpr static const uint LastProperty                = FirstProperty + 0;
        };

        class ScanningMode
        {
          public:
            constexpr static const uint FirstProperty               = ResolutionFlags::LastProperty + 1;
            constexpr static const uint ScanMode                    = FirstProperty + 0;
            constexpr static const uint LastProperty                = FirstProperty + 0;
        };

        class Rotation
        {
          public:
            constexpr static const uint FirstProperty               = ScanningMode::LastProperty + 1;
            constexpr static const uint LatitudeOfSouthernPole      = FirstProperty + 0;
            constexpr static const uint LongitudeOfSouthernPole     = FirstProperty + 1;
            constexpr static const uint AngleOfRotationInDegrees    = FirstProperty + 2;
            constexpr static const uint LastProperty                = FirstProperty + 2;
        };

        constexpr static const uint LastProperty                    = Rotation::LastProperty;
    };

    constexpr static const uint LastProperty                        = ProductSection::LastProperty;


  protected:

    T::PropertyMap    propertyMap;
    T::PropertyVec    propertyVector;

};  // class Property


extern Property gribProperty;

}  // namespace GRIB1
}  // namespace SmartMet
