#pragma once

#include "grib2/definition/TransverseMercator.h"


namespace SmartMet
{
namespace GRIB2
{

class TransverseMercatorImpl : public TransverseMercator
{
  public:
                      TransverseMercatorImpl();
                      TransverseMercatorImpl(const TransverseMercatorImpl& other);
    virtual           ~TransverseMercatorImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};


}
}


