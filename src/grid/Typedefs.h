#pragma once

#include <cstdint>
#include <vector>
#include <boost/optional.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <gdal/ogr_spatialref.h>
#include <float.h>
#include <string>

#include "Coordinate.h"
#include "Dimensions.h"


namespace SmartMet
{


template <typename A>
bool missing(const A& obj)
{
  return !obj;
}



namespace T
{

typedef std::size_t Hash;
typedef std::uint64_t FilePosition;
typedef std::string ParamId;
typedef std::uint32_t ParamLevel;
typedef std::uint8_t ParamLevelId;
typedef float ParamValue;
#define ParamValueMissing FLT_MAX
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

enum class ParamKeyType
{
   FMI_ID       = 0,
   FMI_NAME     = 1,
   GRIB_ID      = 2,
   NEWBASE_ID   = 3,
   NEWBASE_NAME = 4,
   CDM_ID       = 5,
   CDM_NAME     = 6
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
  Grib2   = 2
};



enum class GridLayout
{
  Regular,
  Irregular,
  Points,               // No 'shapeOfEarth'; no coordinate transformations
  Data                  // No coordinates
};



enum class InterpolationMethod
{
  Unknown = 0,
  Linear = 1,
  Nearest = 2
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
  Unknown,
  LatLon,
  RotatedLatLon,
  StretchedLatLon,
  StretchedRotatedLatLon,
  VariableResolutionLatLon,
  VariableResolutionRotatedLatLon,
  Mercator,
  TransverseMercator,
  PolarStereographic,
  LambertConformal,
  ObliqueLambertConformal,
  Albers,
  Gaussian,
  RotatedGaussian,
  StretchedGaussian,
  StretchedRotatedGaussian,
  SphericalHarmonic,
  RotatedSphericalHarmonic,
  StretchedSphericalHarmonic,
  StretchedRotatedSphericalHarmonic,
  SpaceView,
  Triangular,
  Unstructured,
  EquatorialAzimuthalEquidistant,
  AzimuthRange,
  IrregularLatLon,
  LambertAzimuthalEqualArea,
  CrossSection,
  Hovmoller,
  TimeSection,
  GnomonicProjection,
  SimplePolyconicProjection,
  MillersCylindricalProjection
};


std::string get_fileTypeString(FileType fileType);
std::string get_gridLayoutString(GridLayout layout);
std::string get_intepolationMethodString(InterpolationMethod interpolationMethod);
std::string get_gridProjectionString(GridProjection gridType);


}
}