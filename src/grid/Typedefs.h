#pragma once

#include "../common/Coordinate.h"
#include "../common/Dimensions.h"
#include "../common/Typedefs.h"

#include <cstdint>
#include <vector>
#include <set>
#include <boost/optional.hpp>
#include <macgyver/DateTime.h>
#include <ogr_spatialref.h>
#include <float.h>
#include <string>



namespace SmartMet
{


namespace T
{

typedef std::size_t Hash;
typedef std::uint64_t FilePosition;
typedef std::string ParamId;
typedef std::uint32_t NewbaseParamId;
typedef std::uint32_t FmiParamId;
typedef std::uint32_t GribParamId;
typedef std::int32_t ParamLevel;
typedef std::int16_t ParamLevelId;
typedef float ParamValue;
typedef ParamValue* ParamValue_ptr;
#define ParamValueMissing -16777216

typedef std::vector<ParamId> ParamId_vec;
typedef std::vector<ParamLevel> ParamLevel_vec;
typedef std::vector<ParamValue> ParamValue_vec;
typedef ParamValue_vec* ParamValue_vec_ptr;
typedef std::vector<Coordinate> Coordinate_vec;

typedef std::vector<std::size_t> Index_vec;
typedef Fmi::DateTime TimeStamp;
typedef std::string TimeString;

typedef OGRSpatialReference SpatialRef;
typedef unsigned char* Data_ptr;

typedef std::vector<Data_ptr> Data_ptr_vec;

typedef std::int8_t Int8;
typedef std::int16_t Int16;
typedef std::int32_t Int32;
typedef std::int64_t Int64;
typedef std::uint8_t UInt8;
typedef std::uint16_t UInt16;
typedef std::uint32_t UInt32;
typedef std::uint64_t UInt64;

typedef boost::optional<std::int8_t> Int8_opt;
typedef boost::optional<std::int16_t> Int16_opt;
typedef boost::optional<std::int32_t> Int32_opt;
typedef boost::optional<std::int64_t> Int64_opt;
typedef boost::optional<std::uint8_t> UInt8_opt;
typedef boost::optional<std::uint16_t> UInt16_opt;
typedef boost::optional<std::uint24_t> UInt24_opt;
typedef boost::optional<std::uint32_t> UInt32_opt;
typedef boost::optional<std::uint64_t> UInt64_opt;
typedef boost::optional<std::float_t> Float_opt;

typedef std::vector<int> IndexVector;

typedef unsigned long long SessionId;

typedef short ForecastType;
typedef short ForecastNumber;
typedef int   GeometryId;
typedef std::set<T::GeometryId> GeometryId_set;


typedef uchar ParamKeyType;

class ParamKeyTypeValue
{
  public:
  enum : ParamKeyType
    {
     UNKNOWN      = 0,
     FMI_ID       = 1,
     FMI_NAME     = 2,
     GRIB_ID      = 3,
     NEWBASE_ID   = 4,
     NEWBASE_NAME = 5,
     NETCDF_NAME  = 6,
     BUILD_IN     = 100
    };
};


/*
typedef uchar ParamLevelIdType;

class ParamLevelIdTypeValue
{
  public:
    static const ParamLevelIdType ANY       = 0;
    static const ParamLevelIdType FMI       = 1;
    static const ParamLevelIdType GRIB1     = 2;
    static const ParamLevelIdType GRIB2     = 3;
    static const ParamLevelIdType IGNORE    = 100;
};
*/


typedef uchar FileType;

class FileTypeValue
{
  public:
  enum : FileType
    {
     Unknown   = 0,
     Grib1     = 1,
     Grib2     = 2,
     NetCdf3   = 3,
     NetCdf4   = 4,
     QueryData = 5,
     Grib      = 9,  // Contains Grib1 and Grib2 messages
     Fmig1     = 10,
     Virtual   = 200
    };
};

/*
typedef uchar GridLayout;

class GridLayoutValue
{
  public:
    static const GridLayout Unknown   = 0;
    static const GridLayout Regular   = 1;
    static const GridLayout Irregular = 2;
    static const GridLayout Points    = 3;   // No 'shapeOfEarth'; no coordinate transformations
    static const GridLayout Data      = 4;   // No coordinates
};
*/


class AreaInterpolationMethod
{
  public:
  enum : short
    {
     Undefined      = -1,
     None           = 0,     // Numbers 0 - 99 reserved for build-in interpolation types
     Linear         = 1,
     Nearest        = 2,
     Min            = 3,
     Max            = 4,
     Landscape      = 9,
     Forbidden      = 10,    // Requested point needs to match a grid point (or to be very close to it)
     List           = 500,   // Returns grid corner values
     ListWithAngles = 501,   // Returns grid corner values and angles
     External       = 1000   // Numbers 1000 - 65535 reserved for external interpolation types
    };
};


class TimeInterpolationMethod
{
  public:
  enum : short
    {
     Undefined    = -1,
     None         = 0,       // Numbers 0 - 999 reserved for build-in interpolation types
     Linear       = 1,
     Nearest      = 2,
     Min          = 3,
     Max          = 4,
     Previous     = 6,
     Next         = 7,
     Forbidden    = 10,      // Requested time needs to match the grid time (or to be very close to it)
     External     = 1000     // Numbers 1000 - 65535 reserved for external interpolation types
    };
};


class LevelInterpolationMethod
{
  public:
  enum : short
    {
     Undefined    = -1,
     None         = 0,       // Numbers 0 - 999 reserved for build-in interpolation types
     Linear       = 1,
     Nearest      = 2,
     Min          = 3,
     Max          = 4,
     Logarithmic  = 5,
     Previous     = 6,
     Next         = 7,
     Forbidden    = 10,      // Requested level needs to match the grid level (or to be very close to it)
     External     = 1000     // Numbers 1000 - 65535 reserved for external interpolation types
    };
};


typedef uchar CoordinateType;

class CoordinateTypeValue
{
  public:
  enum : CoordinateType
    {
     UNKNOWN               = 0,
     LATLON_COORDINATES    = 1,
     GRID_COORDINATES      = 2,
     ORIGINAL_COORDINATES  = 3
    };
};



typedef ushort GridProjection;

class GridProjectionValue
{
  public:
  enum : GridProjection
    {
     Unknown                             = 0,
     LatLon                              = 1,
     RotatedLatLon                       = 2,
     StretchedLatLon                     = 3,
     StretchedRotatedLatLon              = 4,
     VariableResolutionLatLon            = 5,
     VariableResolutionRotatedLatLon     = 6,
     Mercator                            = 7,
     TransverseMercator                  = 8,
     PolarStereographic                  = 9,
     LambertConformal                    = 10,
     ObliqueLambertConformal             = 11,
     Albers                              = 12,
     Gaussian                            = 13,
     RotatedGaussian                     = 14,
     StretchedGaussian                   = 15,
     StretchedRotatedGaussian            = 16,
     SphericalHarmonic                   = 17,
     RotatedSphericalHarmonic            = 18,
     StretchedSphericalHarmonic          = 19,
     StretchedRotatedSphericalHarmonic   = 20,
     SpaceView                           = 21,
     Triangular                          = 22,
     Unstructured                        = 23,
     EquatorialAzimuthalEquidistant      = 24,
     AzimuthRange                        = 25,
     IrregularLatLon                     = 26,
     LambertAzimuthalEqualArea           = 27,
     CrossSection                        = 28,
     Hovmoller                           = 29,
     TimeSection                         = 30,
     GnomonicProjection                  = 31,
     SimplePolyconicProjection           = 32,
     MillersCylindricalProjection        = 33
    };
};


class CompressionMethod
{
  public:
  enum : ushort
    {
     Undefined                                               = 0,
     None                                                    = 1,

     GridPointData_SimplePacking                             = 10,
     GridPointData_SimplePackingWithPreprocessing            = 11,
     GridPointData_SimplePackingWithLogarithmicPreprocessing = 12,
     GridPointData_ComplexPacking                            = 13,  // = SecondOrderPacking
     GridPointData_ComplexPackingAndSpatialDifferencing      = 14,
     GridPointData_IEEE_packing                              = 15,
     GridPointData_JPEG_2000                                 = 16,
     GridPointData_PNG                                       = 17,
     GridPointMatrixValues_SimplePacking                     = 30,

     SphericalHarmonics_SimplePacking                        = 40,
     SphericalHarmonics_ComplexPacking                       = 41,

     SpectralData_SimplePacking                              = 50,
     SpectralData_ComplexPacking                             = 51
    };
};



std::string get_fileTypeString(FileType fileType);
//std::string get_gridLayoutString(GridLayout layout);
std::string get_areaInterpolationMethodString(short interpolationMethod);
std::string get_timeInterpolationMethodString(short interpolationMethod);
std::string get_levelInterpolationMethodString(short interpolationMethod);
std::string get_gridProjectionString(GridProjection projection);


}
}
