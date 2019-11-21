#pragma once

#include "../definition/LambertConformal.h"


namespace SmartMet
{
namespace GRIB2
{

class LambertConformalImpl : public LambertConformal
{
  public:

                      LambertConformalImpl();
                      LambertConformalImpl(const LambertConformalImpl& other);
    virtual           ~LambertConformalImpl();

    GridDefinition*   createGridDefinition() const;

    bool              getGridCellSize(double& width,double& height) const;
    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    std::string       getGridGeometryString() const;
    bool              getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    bool              reverseXDirection() const;
    bool              reverseYDirection() const;

    bool              setProperty(uint propertyId,long long value);

    void              initSpatialReference();
    void              print(std::ostream& stream,uint level,uint optionFlags) const;
    void              read(MemoryReader& memoryReader);

  protected:

    mutable OGRSpatialReference*          mSr_lambertConformal;
    mutable OGRCoordinateTransformation*  mCt_latlon2lambert;
    mutable OGRCoordinateTransformation*  mCt_lambert2latlon;

  private:

    void              init() const;

    mutable double    mDxx;
    mutable double    mDyy;
    mutable double    mStartX;
    mutable double    mStartY;
    mutable bool      mInitialized;
};


}
}



