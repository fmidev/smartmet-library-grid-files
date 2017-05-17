#pragma once

#include "grib1/definition/StretchedLatLon.h"

namespace SmartMet
{
namespace GRIB1
{

class StretchedLatLonImpl : public StretchedLatLon
{
  public:
                      StretchedLatLonImpl();
                      StretchedLatLonImpl(const StretchedLatLonImpl& other);
    virtual           ~StretchedLatLonImpl();

    void              getGridLatlonAreaCoordinates(double& firstLat,double& firstLon,double& lastLat,double& lastLon) const;
    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
