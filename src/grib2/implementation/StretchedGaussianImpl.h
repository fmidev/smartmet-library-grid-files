#pragma once

#include "grib2/definition/StretchedGaussian.h"


namespace SmartMet
{
namespace GRIB2
{

class StretchedGaussianImpl : public StretchedGaussian
{
  public:
                      StretchedGaussianImpl();
                      StretchedGaussianImpl(const StretchedGaussianImpl& other);
    virtual           ~StretchedGaussianImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}


