#pragma once

#include "../definition/StretchedGaussian.h"


namespace SmartMet
{
namespace GRIB2
{

class StretchedGaussianImpl : public StretchedGaussian
{
  public:
                        StretchedGaussianImpl();
                        StretchedGaussianImpl(const StretchedGaussianImpl& other);
    virtual             ~StretchedGaussianImpl();

    GridDefinition*     createGridDefinition() const;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const;
    T::Dimensions       getGridDimensions() const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void                initSpatialReference();
    void                read(MemoryReader& memoryReader);
};

}
}


