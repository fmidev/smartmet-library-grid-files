#pragma once

#include "../definition/RotatedGaussian.h"


namespace SmartMet
{
namespace GRIB2
{

class RotatedGaussianImpl : public RotatedGaussian
{
  public:

                        RotatedGaussianImpl();
                        RotatedGaussianImpl(const RotatedGaussianImpl& other);
    virtual             ~RotatedGaussianImpl();

    GridDefinition*     createGridDefinition() const;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const;
    T::Dimensions       getGridDimensions() const;

    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    void                initSpatialReference();
    void                read(MemoryReader& memoryReader);
};

}
}



