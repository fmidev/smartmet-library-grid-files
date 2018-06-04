#pragma once

#include "../definition/VariableResolutionLatLon.h"

namespace SmartMet
{
namespace GRIB2
{

class VariableResolutionLatLonImpl : public VariableResolutionLatLon
{
  public:

                      VariableResolutionLatLonImpl();
                      VariableResolutionLatLonImpl(const VariableResolutionLatLonImpl& other);
    virtual           ~VariableResolutionLatLonImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}


