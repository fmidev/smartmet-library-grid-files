#pragma once

#include "../definition/Triangular.h"


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

    GridDefinition*   createGridDefinition() const;

    T::Coordinate_vec getGridOriginalCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}


