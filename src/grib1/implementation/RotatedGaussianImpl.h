#pragma once

#include "../definition/RotatedGaussian.h"

namespace SmartMet
{
namespace GRIB1
{

class RotatedGaussianImpl : public RotatedGaussian
{
  public:
                      RotatedGaussianImpl();
                      RotatedGaussianImpl(const RotatedGaussianImpl& other);
    virtual           ~RotatedGaussianImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
