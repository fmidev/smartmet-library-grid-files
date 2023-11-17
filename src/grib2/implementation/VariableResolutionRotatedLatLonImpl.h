#pragma once

#include "../definition/VariableResolutionRotatedLatLon.h"


namespace SmartMet
{
namespace GRIB2
{

class VariableResolutionRotatedLatLonImpl : public VariableResolutionRotatedLatLon
{
  public:
                        VariableResolutionRotatedLatLonImpl();
                        VariableResolutionRotatedLatLonImpl(const VariableResolutionRotatedLatLonImpl& other);
    virtual             ~VariableResolutionRotatedLatLonImpl();

    GridDefinition*     createGridDefinition() const;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const;
    T::Dimensions       getGridDimensions() const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void                initSpatialReference();
    void                read(MemoryReader& memoryReader);
};


}
}
