#pragma once

#include "../common/Coordinate.h"
#include "../common/Dimensions.h"
#include "../common/Typedefs.h"

#include <cstdint>
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

typedef std::size_t   Hash;            //!< General-purpose hash value
typedef std::uint32_t ProducerId;      //!< Numeric identifier for a data producer
typedef std::uint64_t GenerationId;    //!< Identifier for a data generation (forecast run)
typedef std::uint64_t FileId;          //!< Unique identifier for a grid file
typedef std::uint64_t FilePosition;    //!< Byte offset within a grid file
typedef std::string   ParamId;         //!< String parameter identifier (FMI name or numeric string)
typedef std::uint32_t NewbaseParamId;  //!< FMI Newbase parameter identifier
typedef std::uint32_t FmiParamId;      //!< FMI internal parameter identifier
typedef std::uint32_t GribParamId;     //!< GRIB parameter identifier
typedef std::int32_t  ParamLevel;      //!< Vertical level value
typedef std::int16_t  ParamLevelId;    //!< Vertical level type identifier
typedef std::int16_t  ForecastType;    //!< Forecast type code (deterministic, ensemble member, …)
typedef std::int16_t  ForecastNumber;  //!< Ensemble member number (or -1 for deterministic)
typedef std::int32_t  GeometryId;      //!< Grid geometry identifier


typedef std::uint32_t StorageId;     //!< Storage slot identifier
typedef std::uint32_t SourceId;      //!< Data source identifier
typedef std::uint32_t MessageIndex;  //!< Zero-based message index within a grid file
typedef std::uint64_t EventId;       //!< Event sequence number


typedef float ParamValue;              //!< Grid parameter value type (32-bit float)
typedef ParamValue* ParamValue_ptr;    //!< Raw pointer to a ParamValue array
#define ParamValueMissing -16777216    //!< Sentinel value indicating a missing grid point



/*! \brief A (propertyId, value-as-string) pair used to batch-set Message properties. */
class PropertySetting
{
  public:

    PropertySetting() {propertyId = 0;}
    PropertySetting(uint id,std::string value) {propertyId = id; propertyValue = value;}
    PropertySetting(uint id,char value) {propertyId = id; propertyValue = std::to_string(value);}
    PropertySetting(uint id,uchar value) {propertyId = id; propertyValue = std::to_string(value);}
    PropertySetting(uint id,short value) {propertyId = id; propertyValue = std::to_string(value);}
    PropertySetting(uint id,unsigned short value) {propertyId = id; propertyValue = std::to_string(value);}
    PropertySetting(uint id,int value) {propertyId = id; propertyValue = std::to_string(value);}
    PropertySetting(uint id,uint value) {propertyId = id; propertyValue = std::to_string(value);}
    PropertySetting(uint id,Int64 value) {propertyId = id; propertyValue = std::to_string(value);}
    PropertySetting(uint id,UInt64 value) {propertyId = id; propertyValue = std::to_string(value);}
    PropertySetting(uint id,float value) {propertyId = id; propertyValue = std::to_string(value);}
    PropertySetting(uint id,double value) {propertyId = id; propertyValue = std::to_string(value);}

    uint        propertyId;   //!< Numeric property identifier (corresponds to a Message getter/setter)
    std::string propertyValue; //!< Value serialised as a string
};

typedef std::vector<PropertySetting> PropertySettingVec; //!< List of property assignments

typedef std::vector<ParamId>    ParamId_vec;        //!< List of string parameter identifiers
typedef std::vector<ParamLevel> ParamLevel_vec;     //!< List of vertical level values
typedef std::vector<ParamValue> ParamValue_vec;     //!< Dense grid value array
typedef ParamValue_vec*         ParamValue_vec_ptr; //!< Pointer to a grid value array
typedef std::vector<Coordinate> Coordinate_vec;     //!< List of (x,y) coordinate pairs

typedef std::vector<std::size_t> Index_vec;         //!< Generic index list
typedef Fmi::DateTime            TimeStamp;         //!< Point-in-time type (boost::posix_time)
typedef std::string              TimeString;        //!< ISO-8601 time string

typedef OGRSpatialReference                 SpatialRef;      //!< OGR spatial reference wrapper
typedef std::shared_ptr<OGRSpatialReference> SpatialRef_sptr; //!< Shared spatial reference
typedef unsigned char*                       Data_ptr;        //!< Raw byte pointer for packed grid data

typedef std::vector<Data_ptr> Data_ptr_vec; //!< List of raw data pointers

typedef std::vector<int> IndexVector; //!< List of integer grid indices

typedef std::uint64_t SessionId; //!< Unique identifier for a client session

typedef std::set<T::GeometryId>               GeometryId_set; //!< Set of geometry identifiers

typedef std::map<std::string,uint>            PropertyMap; //!< Map from property name to numeric id
typedef std::vector<std::pair<std::string,uint>> PropertyVec; //!< Ordered list of (name, id) pairs

typedef uchar ParamKeyType; //!< Discriminant for the parameter identifier namespace in use

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


typedef uchar FileType; //!< Discriminant for the grid file format

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


typedef uchar CoordinateType; //!< Discriminant for the coordinate system in use

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


typedef ushort GridProjection; //!< Numeric code identifying a map projection

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
