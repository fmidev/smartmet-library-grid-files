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
    virtual           ~LambertAzimuthalEqualAreaImpl();

    GridDefinition*   createGridDefinition() const;

    T::Coordinate_vec getGridOriginalCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}



