#pragma once

#include "../definition/StretchedLatLon.h"

namespace SmartMet
{
namespace GRIB1
{

class StretchedLatLonImpl : public StretchedLatLon
{
  public:
                      StretchedLatLonImpl();
                      StretchedLatLonImpl(const StretchedLatLonImpl& other);
    virtual           ~StretchedLatLonImpl();

    GridDefinition*   createGridDefinition() const;

    T::Coordinate_vec getGridOriginalCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
