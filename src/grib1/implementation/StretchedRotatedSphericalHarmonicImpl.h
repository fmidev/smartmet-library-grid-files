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
                ~StretchedRotatedSphericalHarmonicImpl() override;

    GridDefinition*     createGridDefinition() const override;

    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    T::Dimensions       getGridDimensions() const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;

    void                initSpatialReference() override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB1
}  // namespace SmartMet
