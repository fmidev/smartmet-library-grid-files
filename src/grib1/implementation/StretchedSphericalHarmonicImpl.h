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
    ~StretchedSphericalHarmonicImpl() override;
    StretchedSphericalHarmonicImpl& operator=(const StretchedSphericalHarmonicImpl&) = default;

    GridDefinition*     createGridDefinition() const override;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const override;
    T::Dimensions       getGridDimensions() const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;

    void                initSpatialReference() override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB1
}  // namespace SmartMet
