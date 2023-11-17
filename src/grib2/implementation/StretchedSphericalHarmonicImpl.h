#pragma once

#include "../definition/StretchedSphericalHarmonic.h"


namespace SmartMet
{
namespace GRIB2
{

class StretchedSphericalHarmonicImpl : public StretchedSphericalHarmonic
{
  public:
                        StretchedSphericalHarmonicImpl();
                        StretchedSphericalHarmonicImpl(const StretchedSphericalHarmonicImpl& other);
    virtual             ~StretchedSphericalHarmonicImpl();

    GridDefinition*     createGridDefinition() const;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const;
    T::Dimensions       getGridDimensions() const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void                initSpatialReference();
    void                read(MemoryReader& memoryReader);
};

}
}


