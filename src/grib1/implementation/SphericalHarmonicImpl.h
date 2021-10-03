#pragma once

#include "../definition/SphericalHarmonic.h"

namespace SmartMet
{
namespace GRIB1
{

class SphericalHarmonicImpl : public SphericalHarmonic
{
  public:

                        SphericalHarmonicImpl();
                        SphericalHarmonicImpl(const SphericalHarmonicImpl& other);
                ~SphericalHarmonicImpl() override;

    GridDefinition*     createGridDefinition() const override;

    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    T::Dimensions       getGridDimensions() const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;

    void                initSpatialReference() override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB1
}  // namespace SmartMet
