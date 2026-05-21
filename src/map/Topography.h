#pragma once

#include "../common/AutoWriteLock.h"
#include "../common/AutoReadLock.h"
#include "../common/ConfigurationFile.h"
#include "../common/BitLine.h"
#include "../common/Typedefs.h"
#include "../grid/Typedefs.h"


namespace SmartMet
{
namespace Map
{


// ====================================================================================
/*! \brief Global topography service providing land/sea classification and elevation
 *  shading for arbitrary geographic coordinates.
 *
 *  Three datasets are managed independently and loaded on first use:
 *  - Land-sea mask  (binary bit-plane, used for isLand() queries)
 *  - Land shading   (float elevation image for terrain shading)
 *  - Sea shading    (float depth/colour image for ocean shading)
 *
 *  All datasets are rectangular pixel grids covering the full globe
 *  (−180..+180 lon, −90..+90 lat) loaded from files named in the configuration. */
// ====================================================================================

class Topography
{
  public:
                Topography();
    virtual     ~Topography();

    void        init(const char* configFile,bool initLandSeaMask,bool initLandShading,bool initSeaShading);

    void        isLand(const T::Coordinate_vec& coordinates,std::vector<bool>& land);
    void        getLand(const T::Coordinate_vec& coordinates,std::vector<float>& land);
    void        getShading(const T::Coordinate_vec& coordinates,std::vector<float>& shadings);
    void        getLandShading(const T::Coordinate_vec& coordinates,std::vector<float>& shadings);
    void        getSeaShading(const T::Coordinate_vec& coordinates,std::vector<float>& shadings);

  protected:

    void        loadLandSeaMask();
    void        loadLandShading();
    void        loadSeaShading();

  protected:

    bool        mInitialized;             //!< True after init() has been called.

    float*      mLandShading;             //!< Flat pixel array for land elevation shading.
    std::string mLandShading_file;        //!< Path to the land-shading raster file.
    uint        mLandShading_width;       //!< Width of the land-shading raster in pixels.
    uint        mLandShading_height;      //!< Height of the land-shading raster in pixels.
    bool        mLandShading_initialized; //!< True once the land-shading raster is loaded.
    uint        mLandShading_size;        //!< Total number of pixels (width * height).
    double      mLandShading_dx;          //!< Pixels per degree of longitude.
    double      mLandShading_dy;          //!< Pixels per degree of latitude.

    float*      mSeaShading;              //!< Flat pixel array for sea depth/colour shading.
    std::string mSeaShading_file;         //!< Path to the sea-shading raster file.
    uint        mSeaShading_width;        //!< Width of the sea-shading raster in pixels.
    uint        mSeaShading_height;       //!< Height of the sea-shading raster in pixels.
    bool        mSeaShading_initialized;  //!< True once the sea-shading raster is loaded.
    uint        mSeaShading_size;         //!< Total number of pixels (width * height).
    double      mSeaShading_dx;           //!< Pixels per degree of longitude.
    double      mSeaShading_dy;           //!< Pixels per degree of latitude.


    BitLine     mLandSeaMask;             //!< Packed bit-plane (1 = land, 0 = sea) for the land-sea mask.
    std::string mLandSeaMask_file;        //!< Path to the land-sea mask raster file.
    uint        mLandSeaMask_width;       //!< Width of the land-sea mask in pixels.
    uint        mLandSeaMask_height;      //!< Height of the land-sea mask in pixels.
    bool        mLandSeaMask_initialized; //!< True once the land-sea mask is loaded.
    double      mLandSeaMask_size;        //!< Total number of bits (width * height).
    double      mLandSeaMask_dx;          //!< Pixels per degree of longitude.
    double      mLandSeaMask_dy;          //!< Pixels per degree of latitude.

    ConfigurationFile mConfigurationFile; //!< Parsed configuration file supplying raster paths.
    ModificationLock  mModificationLock;  //!< Read/write lock guarding lazy dataset loading.

  public:

    /*! \brief Return true if the given lon/lat coordinate falls on land. */
    inline bool isLand(double lon,double lat)
    {
      if (!mLandSeaMask_initialized)
        loadLandSeaMask();

      if (!mLandSeaMask_size)
        return false;

      if (lon >= 180)
        lon = lon - 360;

      if (lat >= 90)
        lat = lat - 90;

      int x = C_INT(round((lon+180)*mLandSeaMask_dx));
      int y = C_INT(round((lat+90)*mLandSeaMask_dy));

      uint pos = y*mLandSeaMask_width + x;

      if (mLandSeaMask.getBit(pos))
        return true;

      return false;
    }


    /*! \brief Return the shading value for lon/lat, selecting land or sea shading automatically. */
    inline float getShading(double lon,double lat)
    {
      if (isLand(lon,lat))
        return getLandShading(lon,lat);
      else
        return getSeaShading(lon,lat);
    }


    /*! \brief Return the land elevation shading value at lon/lat (0 if outside the raster). */
    inline float getLandShading(double lon,double lat)
    {
      if (!mLandShading_initialized)
        loadLandShading();

      int sx = C_INT(round((lon+180)*mLandShading_dx));
      int sy = mLandShading_height-C_INT(round((lat+90)*mLandShading_dy))-1;
      uint spos = sy*mLandShading_width + sx;

      if (spos < mLandShading_size)
        return (double)mLandShading[spos];

      return 0;
    }


    /*! \brief Return the sea depth shading value at lon/lat (0 if outside the raster). */
    inline float getSeaShading(double lon,double lat)
    {
      if (!mSeaShading_initialized)
        loadSeaShading();

      int sx = C_INT(round((lon+180)*mSeaShading_dx));
      int sy = mSeaShading_height-C_INT(round((lat+90)*mSeaShading_dy))-1;
      uint spos = sy*mSeaShading_width + sx;

      if (spos < mSeaShading_size)
        return (double)mSeaShading[spos];

      return 0;
    }



};

extern Topography topography;  //!< Global singleton topography instance initialised from the grid-files configuration.


}  // namespace Map
}  // namespace SmartMet
