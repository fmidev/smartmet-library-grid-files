#pragma once

#include "grib2/definition/LatLon.h"

namespace SmartMet
{
namespace GRIB2
{

class LatLonImpl : public LatLon
{
  public:

                      LatLonImpl();
                      LatLonImpl(const LatLonImpl& other);
    virtual           ~LatLonImpl();

    void              getGridLatlonAreaCoordinates(double& firstLat,double& firstLon,double& lastLat,double& lastLon) const;
    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    void              initSpatialReference();
    bool              getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const;
    bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    void              getOriginalCoordinatesByLatLon(double lat,double lon,double& x,double& y) const;
    void              getLatLonByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    void              print(std::ostream& stream,uint level,uint optionFlags) const;
    void              read(MemoryReader& memoryReader);
};


}
}

