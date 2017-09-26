#pragma once

#include "grib2/definition/Hovmoller.h"


namespace SmartMet
{
namespace GRIB2
{

class HovmollerImpl : public Hovmoller
{
  public:

                      HovmollerImpl();
                      HovmollerImpl(const HovmollerImpl& other);
    virtual           ~HovmollerImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}


