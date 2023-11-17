#pragma once

#include "../definition/EquatorialAzimuthalEquidistant.h"


namespace SmartMet
{
namespace GRIB2
{

class EquatorialAzimuthalEquidistantImpl : public EquatorialAzimuthalEquidistant
{
  public:
                        EquatorialAzimuthalEquidistantImpl();
                        EquatorialAzimuthalEquidistantImpl(const EquatorialAzimuthalEquidistantImpl& other);
    virtual             ~EquatorialAzimuthalEquidistantImpl();

    GridDefinition*     createGridDefinition() const;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const;
    T::Dimensions       getGridDimensions() const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void                initSpatialReference();
    void                read(MemoryReader& memoryReader);
};

}
}
