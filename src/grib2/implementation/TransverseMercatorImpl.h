#pragma once

#include "../definition/TransverseMercator.h"


namespace SmartMet
{
namespace GRIB2
{

class TransverseMercatorImpl : public TransverseMercator
{
  public:
                        TransverseMercatorImpl();
                        TransverseMercatorImpl(const TransverseMercatorImpl& other);
    virtual             ~TransverseMercatorImpl();

    GridDefinition*     createGridDefinition() const;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const;
    T::Dimensions       getGridDimensions() const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void                initSpatialReference();
    void                read(MemoryReader& memoryReader);
};


}
}


