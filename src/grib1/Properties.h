#pragma once


namespace SmartMet
{
namespace GRIB1
{

namespace Property
{

    class ProductSection
    {
      public:
        static const uint FirstProperty                             = 1100;
        static const uint TableVersion                              = FirstProperty + 0;
        static const uint Centre                                    = FirstProperty + 1;
        static const uint GeneratingProcessIdentifier               = FirstProperty + 2;
        static const uint GridDefinitionNumber                      = FirstProperty + 3;
        static const uint SectionFlags                              = FirstProperty + 4;
        static const uint IndicatorOfParameter                      = FirstProperty + 5;
        static const uint IndicatorOfTypeOfLevel                    = FirstProperty + 6;
        static const uint Level                                     = FirstProperty + 7;
        static const uint YearOfCentury                             = FirstProperty + 8;
        static const uint Month                                     = FirstProperty + 9;
        static const uint Day                                       = FirstProperty + 10;
        static const uint Hour                                      = FirstProperty + 11;
        static const uint Minute                                    = FirstProperty + 12;
        static const uint UnitOfTimeRange                           = FirstProperty + 13;
        static const uint P1                                        = FirstProperty + 14;
        static const uint P2                                        = FirstProperty + 15;
        static const uint TimeRangeIndicator                        = FirstProperty + 16;
        static const uint NumberIncludedInAverage                   = FirstProperty + 17;
        static const uint NumberMissingFromAveragesOrAccumulations  = FirstProperty + 18;
        static const uint CenturyOfReferenceTimeOfData              = FirstProperty + 19;
        static const uint SubCentre                                 = FirstProperty + 20;
        static const uint DecimalScaleFactor                        = FirstProperty + 21;
        static const uint ForecastType                              = FirstProperty + 22;
        static const uint ForecastNumber                            = FirstProperty + 23;
        static const uint LastProperty                              = FirstProperty + 99;
    };

    class DataSection
    {
      public:
        static const uint FirstProperty                             = 1200;
        static const uint Flags                                     = FirstProperty + 0;
        static const uint BinaryScaleFactor                         = FirstProperty + 1;
        static const uint ReferenceValue                            = FirstProperty + 2;
        static const uint BitsPerValue                              = FirstProperty + 3;
        static const uint PackingMethod                             = FirstProperty + 4;
        static const uint LastProperty                              = FirstProperty + 99;
    };


}  // namespace property
}  // namespace GRID
}  // namespace SmartMet
