#pragma once

#include "../definition/AzimuthRange.h"

namespace SmartMet
{
namespace GRIB2
{

class AzimuthRangeImpl : public AzimuthRange
{
  public:
                      AzimuthRangeImpl();
                      AzimuthRangeImpl(const AzimuthRangeImpl& other);
    virtual           ~AzimuthRangeImpl();

    GridDefinition*   createGridDefinition() const;

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}
