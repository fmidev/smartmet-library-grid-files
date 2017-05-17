#pragma once

#include "grib2/definition/VariableResolutionRotatedLatLon.h"


namespace SmartMet
{
namespace GRIB2
{

class VariableResolutionRotatedLatLonImpl : public VariableResolutionRotatedLatLon
{
  public:
                      VariableResolutionRotatedLatLonImpl();
                      VariableResolutionRotatedLatLonImpl(const VariableResolutionRotatedLatLonImpl& other);
    virtual           ~VariableResolutionRotatedLatLonImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};


}
}
