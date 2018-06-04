#pragma once

#include "../definition/StretchedRotatedLatLon.h"


namespace SmartMet
{
namespace GRIB2
{

class StretchedRotatedLatLonImpl : public StretchedRotatedLatLon
{
  public:

                      StretchedRotatedLatLonImpl();
                      StretchedRotatedLatLonImpl(const StretchedRotatedLatLonImpl& other);
    virtual           ~StretchedRotatedLatLonImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};


}
}


