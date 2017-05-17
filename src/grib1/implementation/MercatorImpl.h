#pragma once

#include "grib1/definition/Mercator.h"

namespace SmartMet
{
namespace GRIB1
{

class MercatorImpl : public Mercator
{
  public:

                      MercatorImpl();
                      MercatorImpl(const MercatorImpl& other);
    virtual           ~MercatorImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);

  protected:

    mutable OGRSpatialReference*          mSr_mercator;
    mutable OGRCoordinateTransformation*  mCt_latlon2mercator;
    mutable OGRCoordinateTransformation*  mCt_mercator2latlon;
};

}  // namespace GRIB1
}  // namespace SmartMet
