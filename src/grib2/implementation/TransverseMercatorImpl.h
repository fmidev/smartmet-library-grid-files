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
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    std::string         getGridGeometryString() const;
    bool                reverseXDirection() const;
    bool                reverseYDirection() const;

    void                initSpatialReference();
    void                read(MemoryReader& memoryReader);
};


}
}


