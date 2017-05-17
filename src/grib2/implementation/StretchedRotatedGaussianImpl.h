#pragma once

#include "grib2/definition/StretchedRotatedGaussian.h"


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

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}

