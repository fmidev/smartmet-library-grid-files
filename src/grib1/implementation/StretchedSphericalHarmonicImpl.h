#pragma once

#include "grib1/definition/StretchedSphericalHarmonic.h"

namespace SmartMet
{
namespace GRIB1
{

class StretchedSphericalHarmonicImpl : public StretchedSphericalHarmonic
{
  public:

                      StretchedSphericalHarmonicImpl();
                      StretchedSphericalHarmonicImpl(const StretchedSphericalHarmonicImpl& other);
    virtual           ~StretchedSphericalHarmonicImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
