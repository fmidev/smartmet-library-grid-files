#pragma once

#include "grib1/definition/SphericalHarmonic.h"

namespace SmartMet
{
namespace GRIB1
{

class SphericalHarmonicImpl : public SphericalHarmonic
{
  public:

                      SphericalHarmonicImpl();
                      SphericalHarmonicImpl(const SphericalHarmonicImpl& other);
    virtual           ~SphericalHarmonicImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
