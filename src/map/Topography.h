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

    bool        mInitialized;

    float*      mLandShading;
    std::string mLandShading_file;
    uint        mLandShading_width;
    uint        mLandShading_height;
    bool        mLandShading_initialized;
    uint        mLandShading_size;
    double      mLandShading_dx;
    double      mLandShading_dy;

    float*      mSeaShading;
    std::string mSeaShading_file;
    uint        mSeaShading_width;
    uint        mSeaShading_height;
    bool        mSeaShading_initialized;
    uint        mSeaShading_size;
    double      mSeaShading_dx;
    double      mSeaShading_dy;


    BitLine     mLandSeaMask;
    std::string mLandSeaMask_file;
    uint        mLandSeaMask_width;
    uint        mLandSeaMask_height;
    bool        mLandSeaMask_initialized;
    double      mLandSeaMask_size;
    double      mLandSeaMask_dx;
    double      mLandSeaMask_dy;

    ConfigurationFile mConfigurationFile;
    ModificationLock  mModificationLock;

  public:

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


    inline float getShading(double lon,double lat)
    {
      if (isLand(lon,lat))
        return getLandShading(lon,lat);
      else
        return getSeaShading(lon,lat);
    }


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

extern Topography topography;


}  // namespace Map
}  // namespace SmartMet
