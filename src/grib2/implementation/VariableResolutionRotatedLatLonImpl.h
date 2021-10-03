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
                ~VariableResolutionRotatedLatLonImpl() override;

    GridDefinition*     createGridDefinition() const override;

    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    T::Dimensions       getGridDimensions() const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;

    void                initSpatialReference() override;
    void                read(MemoryReader& memoryReader) override;
};


}
}
