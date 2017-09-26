#pragma once

#include "grib1/definition/StretchedRotatedGaussian.h"

namespace SmartMet
{
namespace GRIB1
{

class StretchedRotatedGaussianImpl : public StretchedRotatedGaussian
{
  public:

                      StretchedRotatedGaussianImpl();
                      StretchedRotatedGaussianImpl(const StretchedRotatedGaussianImpl& other);
    virtual           ~StretchedRotatedGaussianImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
