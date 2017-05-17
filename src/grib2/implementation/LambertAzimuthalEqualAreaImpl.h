#pragma once

#include "grib2/definition/LambertAzimuthalEqualArea.h"


namespace SmartMet
{
namespace GRIB2
{

class LambertAzimuthalEqualAreaImpl : public LambertAzimuthalEqualArea
{
  public:

                      LambertAzimuthalEqualAreaImpl();
                      LambertAzimuthalEqualAreaImpl(const LambertAzimuthalEqualAreaImpl& other);
    virtual           ~LambertAzimuthalEqualAreaImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}



