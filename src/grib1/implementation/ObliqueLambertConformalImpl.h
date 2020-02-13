#pragma once

#include "../definition/ObliqueLambertConformal.h"

namespace SmartMet
{
namespace GRIB1
{

class ObliqueLambertConformalImpl : public ObliqueLambertConformal
{
  public:

                      ObliqueLambertConformalImpl();
                      ObliqueLambertConformalImpl(const ObliqueLambertConformalImpl& other);
    virtual           ~ObliqueLambertConformalImpl();

    GridDefinition*   createGridDefinition() const;

    T::Coordinate_vec getGridOriginalCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);

  protected:

    mutable OGRSpatialReference*          mSr_lambertConformal;
    mutable OGRCoordinateTransformation*  mCt_latlon2lambert;
    mutable OGRCoordinateTransformation*  mCt_lambert2latlon;
};

}  // namespace GRIB1
}  // namespace SmartMet
