#pragma once

#include "grib1/definition/SpaceView.h"

namespace SmartMet
{
namespace GRIB1
{

class SpaceViewImpl : public SpaceView
{
  public:

                      SpaceViewImpl();
                      SpaceViewImpl(const SpaceViewImpl& other);
    virtual           ~SpaceViewImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
