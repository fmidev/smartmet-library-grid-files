#pragma once

#include "../definition/StretchedRotatedLatLon.h"

namespace SmartMet
{
namespace GRIB1
{

class StretchedRotatedLatLonImpl : public StretchedRotatedLatLon
{
  public:

                      StretchedRotatedLatLonImpl();
                      StretchedRotatedLatLonImpl(const StretchedRotatedLatLonImpl& other);
    virtual           ~StretchedRotatedLatLonImpl();

    GridDefinition*   createGridDefinition() const;

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
