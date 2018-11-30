#pragma once

#include "../common/Coordinate.h"
#include "../common/Dimensions.h"
#include "../common/Typedefs.h"

#include <cstdint>
#include <vector>
#include <set>
#include <boost/optional.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <gdal/ogr_spatialref.h>
#include <float.h>
#include <string>



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

typedef std::vector<ParamId> ParamId_vec;
typedef std::vector<ParamLevel> ParamLevel_vec;
typedef std::vector<ParamValue> ParamValue_vec;
typedef ParamValue_vec* ParamValue_vec_ptr;
typedef std::vector<Coordinate> Coordinate_vec;

typedef std::vector<std::size_t> Index_vec;
typedef boost::posix_time::ptime TimeStamp;
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
typedef boost::optional<std::uint32_t> UInt32_opt;
typedef boost::optional<std::uint64_t> UInt64_opt;
typedef boost::optional<std::float_t> Float_opt;

typedef std::vector<int> IndexVector;

typedef unsigned long long SessionId;

typedef short ForecastType;
typedef short ForecastNumber;
typedef int   GeometryId;

typedef uchar ParamKeyType;

class ParamKeyTypeValue
{
  public:
    static const ParamKeyType UNKNOWN      = 0;
    static const ParamKeyType FMI_ID       = 1;
    static const ParamKeyType FMI_NAME     = 2;
    static const ParamKeyType GRIB_ID      = 3;
    static const ParamKeyType NEWBASE_ID   = 4;
    static const ParamKeyType NEWBASE_NAME = 5;
    static const ParamKeyType CDM_ID       = 6;
    static const ParamKeyType CDM_NAME     = 7;
    static const ParamKeyType BUILD_IN     = 100;
};



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



typedef uchar FileType;

class FileTypeValue
{
  public:
    static const FileType Unknown = 0;
    static const FileType Grib1   = 1;
    static const FileType Grib2   = 2;
    static const FileType Virtual = 3;
};


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



class AreaInterpolationMethod
{
  public:
    static const short Undefined      = -1;
    static const short None           = 0;     // Numbers 0 - 99 reserved for build-in interpolation types
    static const short Linear         = 1;
    static const short Nearest        = 2;
    static const short Min            = 3;
    static const short Max            = 4;
    static const short List           = 500;   // Returns grid corner values
    static const short ListWithAngles = 501;   // Returns grid corner values and angles
    static const short External       = 1000;  // Numbers 1000 - 65535 reserved for external interpolation types
};


class TimeInterpolationMethod
{
  public:
    static const short Undefined    = -1;
    static const short None         = 0;       // Numbers 0 - 999 reserved for build-in interpolation types
    static const short Linear       = 1;
    static const short Nearest      = 2;
    static const short Min          = 3;
    static const short Max          = 4;
    static const short External     = 1000;    // Numbers 1000 - 65535 reserved for external interpolation types
};


class LevelInterpolationMethod
{
  public:
    static const short Undefined    = -1;
    static const short None         = 0;       // Numbers 0 - 999 reserved for build-in interpolation types
    static const short Linear       = 1;
    static const short Nearest      = 2;
    static const short Min          = 3;
    static const short Max          = 4;
    static const short Logarithmic  = 5;
    static const short External     = 1000;    // Numbers 1000 - 65535 reserved for external interpolation types
};


typedef uchar CoordinateType;

class CoordinateTypeValue
{
  public:
    static const CoordinateType UNKNOWN               = 0;
    static const CoordinateType LATLON_COORDINATES    = 1;
    static const CoordinateType GRID_COORDINATES      = 2;
    static const CoordinateType ORIGINAL_COORDINATES  = 3;
};



typedef ushort GridProjection;

class GridProjectionValue
{
  public:
    static const GridProjection Unknown                             = 0;
    static const GridProjection LatLon                              = 1;
    static const GridProjection RotatedLatLon                       = 2;
    static const GridProjection StretchedLatLon                     = 3;
    static const GridProjection StretchedRotatedLatLon              = 4;
    static const GridProjection VariableResolutionLatLon            = 5;
    static const GridProjection VariableResolutionRotatedLatLon     = 6;
    static const GridProjection Mercator                            = 7;
    static const GridProjection TransverseMercator                  = 8;
    static const GridProjection PolarStereographic                  = 9;
    static const GridProjection LambertConformal                    = 10;
    static const GridProjection ObliqueLambertConformal             = 11;
    static const GridProjection Albers                              = 12;
    static const GridProjection Gaussian                            = 13;
    static const GridProjection RotatedGaussian                     = 14;
    static const GridProjection StretchedGaussian                   = 15;
    static const GridProjection StretchedRotatedGaussian            = 16;
    static const GridProjection SphericalHarmonic                   = 17;
    static const GridProjection RotatedSphericalHarmonic            = 18;
    static const GridProjection StretchedSphericalHarmonic          = 19;
    static const GridProjection StretchedRotatedSphericalHarmonic   = 20;
    static const GridProjection SpaceView                           = 21;
    static const GridProjection Triangular                          = 22;
    static const GridProjection Unstructured                        = 23;
    static const GridProjection EquatorialAzimuthalEquidistant      = 24;
    static const GridProjection AzimuthRange                        = 25;
    static const GridProjection IrregularLatLon                     = 26;
    static const GridProjection LambertAzimuthalEqualArea           = 27;
    static const GridProjection CrossSection                        = 28;
    static const GridProjection Hovmoller                           = 29;
    static const GridProjection TimeSection                         = 30;
    static const GridProjection GnomonicProjection                  = 31;
    static const GridProjection SimplePolyconicProjection           = 32;
    static const GridProjection MillersCylindricalProjection        = 33;
};


class CompressionMethod
{
  public:
    static const ushort Undefined                                               = 0;
    static const ushort None                                                    = 1;

    static const ushort GridPointData_SimplePacking                             = 10;
    static const ushort GridPointData_SimplePackingWithPreprocessing            = 11;
    static const ushort GridPointData_SimplePackingWithLogarithmicPreprocessing = 12;
    static const ushort GridPointData_ComplexPacking                            = 13;  // = SecondOrderPacking
    static const ushort GridPointData_ComplexPackingAndSpatialDifferencing      = 14;
    static const ushort GridPointData_IEEE_packing                              = 15;
    static const ushort GridPointData_JPEG_2000                                 = 16;
    static const ushort GridPointData_PNG                                       = 17;
    static const ushort GridPointMatrixValues_SimplePacking                     = 30;

    static const ushort SphericalHarmonics_SimplePacking                        = 40;
    static const ushort SphericalHarmonics_ComplexPacking                       = 41;

    static const ushort SpectralData_SimplePacking                              = 50;
    static const ushort SpectralData_ComplexPacking                             = 51;
};



std::string get_fileTypeString(FileType fileType);
std::string get_gridLayoutString(GridLayout layout);
std::string get_areaInterpolationMethodString(short interpolationMethod);
std::string get_timeInterpolationMethodString(short interpolationMethod);
std::string get_levelInterpolationMethodString(short interpolationMethod);
std::string get_gridProjectionString(GridProjection projection);


}
}
