#pragma once

#include <cstdint>
#include <vector>
#include <set>
#include <boost/optional.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <gdal/ogr_spatialref.h>
#include <float.h>
#include <string>

#include "common/Coordinate.h"
#include "common/Dimensions.h"
#include "common/Typedefs.h"



namespace SmartMet
{


namespace T
{

typedef std::size_t Hash;
typedef std::uint64_t FilePosition;
typedef std::string ParamId;
typedef std::int32_t ParamLevel;
typedef std::uint8_t ParamLevelId;
typedef float ParamValue;
//#define ParamValueMissing FLT_MAX
#define ParamValueMissing -16777216
//std::numeric_limits<double>::quiet_NaN()

//typedef std::uint32_t FmiParamId;
//typedef std::uint32_t FmiParamLevel;
//typedef std::uint8_t FmiParamLevelId;

typedef std::vector<ParamId> ParamId_vec;
typedef std::vector<ParamLevel> ParamLevel_vec;
typedef std::vector<ParamValue> ParamValue_vec;
typedef ParamValue_vec* ParamValue_vec_ptr;
typedef std::vector<Coordinate> Coordinate_vec;
typedef boost::optional<Dimensions> Dimensions_opt;

typedef std::vector<std::size_t> Index_vec;
typedef boost::posix_time::ptime TimeStamp;
typedef std::string TimeString;

typedef OGRSpatialReference SpatialReference;
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
typedef boost::optional<std::uint32_t> UInt32_opt;
typedef boost::optional<std::uint64_t> UInt64_opt;
typedef boost::optional<std::float_t> Float_opt;

typedef std::vector<int> IndexVector;

typedef unsigned long long SessionId;

typedef short ForecastType;
typedef short ForecastNumber;
typedef int   GeometryId;


enum class ParamKeyType
{
   UNKNOWN      = 0,
   FMI_ID       = 1,
   FMI_NAME     = 2,
   GRIB_ID      = 3,
   NEWBASE_ID   = 4,
   NEWBASE_NAME = 5,
   CDM_ID       = 6,
   CDM_NAME     = 7,
   BUILD_IN     = 100
};

enum class ParamLevelIdType
{
    ANY       = 0,
    FMI       = 1,
    GRIB1     = 2,
    GRIB2     = 3,
    IGNORE    = 100
};


enum class FileType
{
  Unknown = 0,
  Grib1   = 1,
  Grib2   = 2,
  Virtual = 3
};



enum class GridLayout
{
  Regular,
  Irregular,
  Points,               // No 'shapeOfEarth'; no coordinate transformations
  Data                  // No coordinates
};



enum class AreaInterpolationMethod
{
  None = 0,           // Numbers 0 - 9 reserved for build-in interpolation types
  Linear = 1,
  Nearest = 2,
  External = 10,      // Numbers 10 - 254 reserved for external interpolation types
  Undefined = 255
};


enum class TimeInterpolationMethod
{
  None = 0,           // Numbers 0 - 9 reserved for build-in interpolation types
  Linear = 1,
  Nearest = 2,
  External = 10,      // Numbers 10 - 254 reserved for external interpolation types
  Undefined = 255
};


enum class LevelInterpolationMethod
{
  None = 0,           // Numbers 0 - 9 reserved for build-in interpolation types
  Linear = 1,
  Nearest = 2,
  External = 10,      // Numbers 10 - 254 reserved for external interpolation types
  Undefined = 255
};



enum CoordinateType
{
  UNKNOWN               = 0,
  LATLON_COORDINATES    = 1,
  GRID_COORDINATES      = 2,
  ORIGINAL_COORDINATES  = 3
};




enum class GridProjection
{
  Unknown = 0,
  LatLon = 1,
  RotatedLatLon = 2,
  StretchedLatLon = 3,
  StretchedRotatedLatLon = 4,
  VariableResolutionLatLon = 5,
  VariableResolutionRotatedLatLon = 6,
  Mercator = 7,
  TransverseMercator = 8,
  PolarStereographic = 9,
  LambertConformal = 10,
  ObliqueLambertConformal = 11,
  Albers = 12,
  Gaussian = 13,
  RotatedGaussian = 14,
  StretchedGaussian = 15,
  StretchedRotatedGaussian = 16,
  SphericalHarmonic = 17,
  RotatedSphericalHarmonic = 18,
  StretchedSphericalHarmonic = 19,
  StretchedRotatedSphericalHarmonic = 20,
  SpaceView = 21,
  Triangular = 22,
  Unstructured = 23,
  EquatorialAzimuthalEquidistant = 24,
  AzimuthRange = 25,
  IrregularLatLon = 26,
  LambertAzimuthalEqualArea = 27,
  CrossSection = 28,
  Hovmoller = 29,
  TimeSection = 30,
  GnomonicProjection = 31,
  SimplePolyconicProjection = 32,
  MillersCylindricalProjection = 33
};


std::string get_fileTypeString(FileType fileType);
std::string get_gridLayoutString(GridLayout layout);
std::string get_areaIntepolationMethodString(AreaInterpolationMethod interpolationMethod);
std::string get_timeIntepolationMethodString(TimeInterpolationMethod interpolationMethod);
std::string get_levelIntepolationMethodString(LevelInterpolationMethod interpolationMethod);
std::string get_gridProjectionString(GridProjection gridType);


}
}
