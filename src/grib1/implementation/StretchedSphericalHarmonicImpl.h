#pragma once

#include "../definition/StretchedSphericalHarmonic.h"

namespace SmartMet
{
namespace GRIB1
{

class StretchedSphericalHarmonicImpl : public StretchedSphericalHarmonic
{
  public:

                        StretchedSphericalHarmonicImpl();
                        StretchedSphericalHarmonicImpl(const StretchedSphericalHarmonicImpl& other);
    virtual             ~StretchedSphericalHarmonicImpl();

    GridDefinition*     createGridDefinition() const;

    T::Coordinate_svec  getGridOriginalCoordinates() const;
    T::Dimensions       getGridDimensions() const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void                initSpatialReference();
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
