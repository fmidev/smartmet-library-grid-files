#pragma once

#include "../definition/LambertAzimuthalEqualArea.h"


namespace SmartMet
{
namespace GRIB2
{

class LambertAzimuthalEqualAreaImpl : public LambertAzimuthalEqualArea
{
  public:

                        LambertAzimuthalEqualAreaImpl();
                        LambertAzimuthalEqualAreaImpl(const LambertAzimuthalEqualAreaImpl& other);
    virtual             ~LambertAzimuthalEqualAreaImpl();

    GridDefinition*     createGridDefinition() const;


    bool                getGridMetricCellSize(double& width,double& height) const;
    T::Dimensions       getGridDimensions() const;
    std::size_t         getGridColumnCount() const;
    std::size_t         getGridRowCount() const;
    std::string         getGridGeometryString() const;
    T::Coordinate_svec  getGridOriginalCoordinates() const;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                reverseXDirection() const;
    bool                reverseYDirection() const;

    void                initSpatialReference();
    void                print(std::ostream& stream,uint level,uint optionFlags) const;
    void                read(MemoryReader& memoryReader);

  protected:

    mutable OGRSpatialReference*          mSr_lambertConformal;
    mutable OGRCoordinateTransformation*  mCt_latlon2lambert;
    mutable OGRCoordinateTransformation*  mCt_lambert2latlon;

  private:

    void                init() const;

    mutable double      mDxx;
    mutable double      mDyy;
    mutable double      mStartX;
    mutable double      mStartY;
    mutable bool        mInitialized;
};

}
}



