#pragma once

#include "grib2/definition/Triangular.h"


namespace SmartMet
{
namespace GRIB2
{

class TriangularImpl : public Triangular
{
  public:
                      TriangularImpl();
                      TriangularImpl(const TriangularImpl& other);
    virtual           ~TriangularImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}


