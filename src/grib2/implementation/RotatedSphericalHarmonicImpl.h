#pragma once

#include "../definition/RotatedSphericalHarmonic.h"


namespace SmartMet
{
namespace GRIB2
{

class RotatedSphericalHarmonicImpl : public RotatedSphericalHarmonic
{
  public:

                      RotatedSphericalHarmonicImpl();
                      RotatedSphericalHarmonicImpl(const RotatedSphericalHarmonicImpl& other);
    virtual           ~RotatedSphericalHarmonicImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};


}
}

