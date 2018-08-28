#pragma once

#include "../definition/StretchedRotatedGaussian.h"


namespace SmartMet
{
namespace GRIB2
{

class StretchedRotatedGaussianImpl : public StretchedRotatedGaussian
{
  public:

                      StretchedRotatedGaussianImpl();
                      StretchedRotatedGaussianImpl(const StretchedRotatedGaussianImpl& other);
    virtual           ~StretchedRotatedGaussianImpl();

    GridDefinition*   createGridDefinition() const;

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}

