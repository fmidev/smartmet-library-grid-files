#pragma once

#include "../definition/StretchedGaussian.h"

namespace SmartMet
{
namespace GRIB1
{

class StretchedGaussianImpl : public StretchedGaussian
{
  public:

                      StretchedGaussianImpl();
                      StretchedGaussianImpl(const StretchedGaussianImpl& other);
    virtual           ~StretchedGaussianImpl();

    GridDefinition*   createGridDefinition() const;

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
