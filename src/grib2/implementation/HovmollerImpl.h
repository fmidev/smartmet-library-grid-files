#pragma once

#include "../definition/Hovmoller.h"


namespace SmartMet
{
namespace GRIB2
{

class HovmollerImpl : public Hovmoller
{
  public:

                        HovmollerImpl();
                        HovmollerImpl(const HovmollerImpl& other);
    virtual             ~HovmollerImpl();

    GridDefinition*     createGridDefinition() const;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const;
    T::Dimensions       getGridDimensions() const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void                initSpatialReference();
    void                read(MemoryReader& memoryReader);
};

}
}


