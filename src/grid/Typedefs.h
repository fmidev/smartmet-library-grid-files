#pragma once

#include "../common/Coordinate.h"
#include "../common/Dimensions.h"
#include "../common/Typedefs.h"

#include <cstdint>
#include <utility>
#include <vector>
#include <set>
#include <optional>
#include <macgyver/DateTime.h>
#include <ogr_spatialref.h>
#include <float.h>
#include <string>



namespace SmartMet
{


/*! \brief Top-level namespace for SmartMet shared type aliases and enumeration helpers. */
namespace T
{

using Hash = std::size_t;            //!< General-purpose hash value
using ProducerId = std::uint32_t;      //!< Numeric identifier for a data producer
using GenerationId = std::uint64_t;    //!< Identifier for a data generation (forecast run)
using FileId = std::uint64_t;          //!< Unique identifier for a grid file
using FilePosition = std::uint64_t;    //!< Byte offset within a grid file
using ParamId = std::string;         //!< String parameter identifier (FMI name or numeric string)
using NewbaseParamId = std::uint32_t;  //!< FMI Newbase parameter identifier
using FmiParamId = std::uint32_t;      //!< FMI internal parameter identifier
using GribParamId = std::uint32_t;     //!< GRIB parameter identifier
using ParamLevel = std::int32_t;      //!< Vertical level value
using ParamLevelId = std::int16_t;    //!< Vertical level type identifier
using ForecastType = std::int16_t;    //!< Forecast type code (deterministic, ensemble member, …)
using ForecastNumber = std::int16_t;  //!< Ensemble member number (or -1 for deterministic)
using GeometryId = std::int32_t;      //!< Grid geometry identifier


using StorageId = std::uint32_t;     //!< Storage slot identifier
using SourceId = std::uint32_t;      //!< Data source identifier
using MessageIndex = std::uint32_t;  //!< Zero-based message index within a grid file
using EventId = std::uint64_t;       //!< Event sequence number


using ParamValue = float;              //!< Grid parameter value type (32-bit float)
using ParamValue_ptr = ParamValue*;    //!< Raw pointer to a ParamValue array
#define ParamValueMissing -16777216    //!< Sentinel value indicating a missing grid point



/*! \brief A (propertyId, value-as-string) pair used to batch-set Message properties. */
class PropertySetting
{
  public:

    PropertySetting() : propertyId(0) {}
    PropertySetting(uint id,std::string value) : propertyId(id), propertyValue(std::move(value)) { }
    PropertySetting(uint id,char value) : propertyId(id) { propertyValue = std::to_string(value);}
    PropertySetting(uint id,uchar value) : propertyId(id) { propertyValue = std::to_string(value);}
    PropertySetting(uint id,short value) : propertyId(id) { propertyValue = std::to_string(value);}
    PropertySetting(uint id,unsigned short value) : propertyId(id) { propertyValue = std::to_string(value);}
    PropertySetting(uint id,int value) : propertyId(id) { propertyValue = std::to_string(value);}
    PropertySetting(uint id,uint value) : propertyId(id) { propertyValue = std::to_string(value);}
    PropertySetting(uint id,Int64 value) : propertyId(id) { propertyValue = std::to_string(value);}
    PropertySetting(uint id,UInt64 value) : propertyId(id) { propertyValue = std::to_string(value);}
    PropertySetting(uint id,float value) : propertyId(id) { propertyValue = std::to_string(value);}
    PropertySetting(uint id,double value) : propertyId(id) { propertyValue = std::to_string(value);}

    uint        propertyId;   //!< Numeric property identifier (corresponds to a Message getter/setter)
    std::string propertyValue; //!< Value serialised as a string
};

using PropertySettingVec = std::vector<PropertySetting>; //!< List of property assignments

using ParamId_vec = std::vector<ParamId>;        //!< List of string parameter identifiers
using ParamLevel_vec = std::vector<ParamLevel>;     //!< List of vertical level values
using ParamValue_vec = std::vector<ParamValue>;     //!< Dense grid value array
using ParamValue_vec_ptr = ParamValue_vec*; //!< Pointer to a grid value array
using Coordinate_vec = std::vector<Coordinate>;     //!< List of (x,y) coordinate pairs

using Index_vec = std::vector<std::size_t>;         //!< Generic index list
using TimeStamp = Fmi::DateTime;         //!< Point-in-time type (boost::posix_time)
using TimeString = std::string;        //!< ISO-8601 time string

using SpatialRef = OGRSpatialReference;      //!< OGR spatial reference wrapper
using SpatialRef_sptr = std::shared_ptr<OGRSpatialReference>; //!< Shared spatial reference
using Data_ptr = unsigned char*;        //!< Raw byte pointer for packed grid data

using Data_ptr_vec = std::vector<Data_ptr>; //!< List of raw data pointers

using IndexVector = std::vector<int>; //!< List of integer grid indices

using SessionId = std::uint64_t; //!< Unique identifier for a client session

using GeometryId_set = std::set<T::GeometryId>; //!< Set of geometry identifiers

using PropertyMap = std::map<std::string,uint>; //!< Map from property name to numeric id
using PropertyVec = std::vector<std::pair<std::string,uint>>; //!< Ordered list of (name, id) pairs

using ParamKeyType = uchar; //!< Discriminant for the parameter identifier namespace in use

/*! \brief Constants for ParamKeyType — identifies which identifier system a parameter key belongs to. */
class ParamKeyTypeValue
{
  public:
  enum : ParamKeyType
  {
    UNKNOWN      = 0,   //!< Unknown / not set
    FMI_ID       = 1,   //!< FMI numeric parameter id
    FMI_NAME     = 2,   //!< FMI parameter name string
    GRIB_ID      = 3,   //!< GRIB parameter number
    NEWBASE_ID   = 4,   //!< Newbase numeric id
    NEWBASE_NAME = 5,   //!< Newbase parameter name string
    NETCDF_NAME  = 6,   //!< NetCDF variable name
    BUILD_IN     = 100  //!< Built-in / derived parameter
  };
};


using FileType = uchar; //!< Discriminant for the grid file format

/*! \brief Constants for FileType. */
class FileTypeValue
{
  public:
  enum : FileType
  {
    Unknown   = 0,  //!< Format could not be determined
    Grib1     = 1,  //!< GRIB edition 1
    Grib2     = 2,  //!< GRIB edition 2
    NetCdf3   = 3,  //!< NetCDF classic (CDF-1 / CDF-2)
    NetCdf4   = 4,  //!< NetCDF-4 (HDF5-based)
    QueryData = 5,  //!< FMI native QueryData format
    GeoTiff   = 6,  //!< GeoTIFF raster
    Grib      = 9   //!< Mixed GRIB (contains both GRIB1 and GRIB2 messages)
  };
};


/*! \brief Vertical level coordinate scale (linear, logarithmic, or integer count). */
class ParamLevelType
{
  public:
  enum : unsigned char
  {
    Undefined   = 0, //!< Not specified
    Linear      = 1, //!< Linear coordinate scale
    Logarithmic = 2, //!< Logarithmic coordinate scale
    Number      = 3  //!< Integer level number (e.g. ensemble member)
  };
};


/*! \brief Horizontal spatial interpolation methods.
 *
 *  Values 0–99 are built-in; values ≥ 1000 are user-defined external methods. */
class AreaInterpolationMethod
{
  public:
  enum : short
  {
    Undefined      = -1,  //!< Not specified
    None           = 0,   //!< No interpolation
    Linear         = 1,   //!< Bilinear interpolation
    Nearest        = 2,   //!< Nearest-grid-point selection
    Min            = 3,   //!< Minimum of surrounding grid points
    Max            = 4,   //!< Maximum of surrounding grid points
    Landscape      = 9,   //!< Landscape-aware interpolation
    Forbidden      = 10,  //!< Require an exact grid point match
    List           = 500, //!< Return grid corner values
    ListWithAngles = 501, //!< Return grid corner values with wind direction angles
    External       = 1000 //!< First user-defined external method
  };
};


/*! \brief Temporal interpolation methods.
 *
 *  Values 0–999 are built-in; values ≥ 1000 are user-defined. */
class TimeInterpolationMethod
{
  public:
  enum : short
  {
    Undefined = -1,  //!< Not specified
    None      = 0,   //!< No interpolation
    Linear    = 1,   //!< Linear time interpolation
    Nearest   = 2,   //!< Select the nearest time step
    Min       = 3,   //!< Minimum over bracketing time steps
    Max       = 4,   //!< Maximum over bracketing time steps
    Previous  = 6,   //!< Select the most recent past time step
    Next      = 7,   //!< Select the next future time step
    Forbidden = 10,  //!< Require an exact time match
    Transfer  = 15,  //!< Optical-flow-based transfer interpolation
    External  = 1000 //!< First user-defined external method
  };
};


/*! \brief Vertical level interpolation methods.
 *
 *  Values 0–999 are built-in; values ≥ 1000 are user-defined. */
class LevelInterpolationMethod
{
  public:
  enum : short
  {
    Undefined   = -1,  //!< Not specified
    None        = 0,   //!< No interpolation
    Linear      = 1,   //!< Linear interpolation in level space
    Nearest     = 2,   //!< Select the nearest level
    Min         = 3,   //!< Minimum of bracketing levels
    Max         = 4,   //!< Maximum of bracketing levels
    Logarithmic = 5,   //!< Logarithmic interpolation (e.g. pressure)
    Previous    = 6,   //!< Select the closest level below
    Next        = 7,   //!< Select the closest level above
    Forbidden   = 10,  //!< Require an exact level match
    External    = 1000 //!< First user-defined external method
  };
};


using CoordinateType = uchar; //!< Discriminant for the coordinate system in use

/*! \brief Constants for CoordinateType. */
class CoordinateTypeValue
{
  public:
  enum : CoordinateType
  {
    UNKNOWN              = 0, //!< Unknown / not set
    LATLON_COORDINATES   = 1, //!< Geographic coordinates (degrees latitude/longitude)
    GRID_COORDINATES     = 2, //!< Pixel/grid-index coordinates
    ORIGINAL_COORDINATES = 3  //!< Native projection coordinates (metres or degrees)
  };
};


using GridProjection = ushort; //!< Numeric code identifying a map projection

/*! \brief Constants for GridProjection — mirrors GRIB2 grid definition template numbers. */
class GridProjectionValue
{
  public:
  enum : GridProjection
  {
    Unknown                             = 0,
    LatLon                              = 1,  //!< Regular latitude/longitude
    RotatedLatLon                       = 2,  //!< Rotated latitude/longitude
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
    Gaussian                            = 13, //!< Gaussian latitude/longitude
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


/*! \brief GRIB data packing / compression methods. */
class CompressionMethod
{
  public:
  enum : ushort
  {
    Undefined                                               = 0,
    None                                                    = 1,  //!< Uncompressed data

    GridPointData_SimplePacking                             = 10, //!< Simple packing
    GridPointData_SimplePackingWithPreprocessing            = 11,
    GridPointData_SimplePackingWithLogarithmicPreprocessing = 12,
    GridPointData_ComplexPacking                            = 13, //!< Second-order / complex packing
    GridPointData_ComplexPackingAndSpatialDifferencing      = 14,
    GridPointData_IEEE_packing                              = 15, //!< IEEE 754 float/double
    GridPointData_JPEG_2000                                 = 16, //!< JPEG 2000 lossy compression
    GridPointData_PNG                                       = 17, //!< PNG lossless compression
    GridPointMatrixValues_SimplePacking                     = 30,

    SphericalHarmonics_SimplePacking                        = 40,
    SphericalHarmonics_ComplexPacking                       = 41,

    SpectralData_SimplePacking                              = 50,
    SpectralData_ComplexPacking                             = 51
  };
};


/*! \brief Convert a FileType code to a human-readable string.
 *  \param[in] fileType  FileType constant.
 *  \return String such as "GRIB1", "NetCdf4", etc. */
std::string get_fileTypeString(FileType fileType);

/*! \brief Convert an area interpolation method code to a human-readable string.
 *  \param[in] interpolationMethod  AreaInterpolationMethod constant.
 *  \return String representation. */
std::string get_areaInterpolationMethodString(short interpolationMethod);

/*! \brief Convert a time interpolation method code to a human-readable string.
 *  \param[in] interpolationMethod  TimeInterpolationMethod constant.
 *  \return String representation. */
std::string get_timeInterpolationMethodString(short interpolationMethod);

/*! \brief Convert a level interpolation method code to a human-readable string.
 *  \param[in] interpolationMethod  LevelInterpolationMethod constant.
 *  \return String representation. */
std::string get_levelInterpolationMethodString(short interpolationMethod);

/*! \brief Convert a grid projection code to a human-readable string.
 *  \param[in] projection  GridProjection constant.
 *  \return String representation. */
std::string get_gridProjectionString(GridProjection projection);


}
}
