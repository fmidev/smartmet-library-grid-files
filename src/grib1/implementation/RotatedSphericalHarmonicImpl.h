#pragma once

#include "../definition/RotatedSphericalHarmonic.h"

namespace SmartMet
{
namespace GRIB1
{

class RotatedSphericalHarmonicImpl : public RotatedSphericalHarmonic
{
  public:
                        RotatedSphericalHarmonicImpl();
                        RotatedSphericalHarmonicImpl(const RotatedSphericalHarmonicImpl& other);
    virtual             ~RotatedSphericalHarmonicImpl();

    GridDefinition*     createGridDefinition() const;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const;
    T::Dimensions       getGridDimensions() const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void                initSpatialReference();
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
