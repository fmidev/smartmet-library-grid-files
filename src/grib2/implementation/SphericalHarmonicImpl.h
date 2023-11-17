#pragma once

#include "../definition/SphericalHarmonic.h"


namespace SmartMet
{
namespace GRIB2
{

class SphericalHarmonicImpl : public SphericalHarmonic
{
  public:
                        SphericalHarmonicImpl();
                        SphericalHarmonicImpl(const SphericalHarmonicImpl& other);
    virtual             ~SphericalHarmonicImpl();

    GridDefinition*     createGridDefinition() const;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const;
    T::Dimensions       getGridDimensions() const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void                initSpatialReference();
    void                read(MemoryReader& memoryReader);
};

}
}


