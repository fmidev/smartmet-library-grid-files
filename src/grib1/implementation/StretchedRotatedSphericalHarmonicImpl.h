#pragma once

#include "../definition/StretchedRotatedSphericalHarmonic.h"

namespace SmartMet
{
namespace GRIB1
{

class StretchedRotatedSphericalHarmonicImpl : public StretchedRotatedSphericalHarmonic
{
  public:

                      StretchedRotatedSphericalHarmonicImpl();
                      StretchedRotatedSphericalHarmonicImpl(const StretchedRotatedSphericalHarmonicImpl& other);
    virtual           ~StretchedRotatedSphericalHarmonicImpl();

    GridDefinition*   createGridDefinition() const;

    T::Coordinate_vec getGridOriginalCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
