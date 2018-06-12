#pragma once

#include "../definition/LambertConformal.h"

namespace SmartMet
{
namespace GRIB1
{

class LambertConformalImpl : public LambertConformal
{
  public:

                      LambertConformalImpl();
                      LambertConformalImpl(const LambertConformalImpl& other);
    virtual           ~LambertConformalImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    std::string       getGridGeometryString() const;
    bool              getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    bool              reverseXDirection() const;
    bool              reverseYDirection() const;

    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);

  protected:

    mutable OGRSpatialReference*          mSr_lambertConformal;
    mutable OGRCoordinateTransformation*  mCt_latlon2lambert;
    mutable OGRCoordinateTransformation*  mCt_lambert2latlon;

};

}  // namespace GRIB1
}  // namespace SmartMet
