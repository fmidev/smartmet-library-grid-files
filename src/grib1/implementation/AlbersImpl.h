#pragma once

#include "grib1/definition/Albers.h"

namespace SmartMet
{
namespace GRIB1
{

class AlbersImpl : public Albers
{
  public:

                      AlbersImpl();
                      AlbersImpl(const AlbersImpl& other);
    virtual           ~AlbersImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
