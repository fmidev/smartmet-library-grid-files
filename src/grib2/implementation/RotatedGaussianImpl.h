#pragma once

#include "grib2/definition/RotatedGaussian.h"


namespace SmartMet
{
namespace GRIB2
{

class RotatedGaussianImpl : public RotatedGaussian
{
  public:

                      RotatedGaussianImpl();
                      RotatedGaussianImpl(const RotatedGaussianImpl& other);
    virtual           ~RotatedGaussianImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}


