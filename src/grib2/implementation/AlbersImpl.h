#pragma once

#include "../definition/Albers.h"

namespace SmartMet
{
namespace GRIB2
{

class AlbersImpl : public Albers
{
  public:

                      AlbersImpl();
                      AlbersImpl(const AlbersImpl& other);
    virtual           ~AlbersImpl();

    GridDefinition*   createGridDefinition() const;

    T::Coordinate_vec getGridOriginalCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}
