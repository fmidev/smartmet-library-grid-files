#pragma once

#include "../definition/LatLon.h"

namespace SmartMet
{
namespace GRIB2
{

class LatLonImpl : public LatLon
{
  public:

                      LatLonImpl();
                      LatLonImpl(const LatLonImpl& other);
    virtual           ~LatLonImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    std::string       getGridGeometryString() const;
    T::Coordinate_vec getGridLatLonCoordinates() const;
    bool              getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    bool              getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;
    bool              getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    bool              getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    bool              getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool              getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    bool              reverseXDirection() const;
    bool              reverseYDirection() const;

    void              initSpatialReference();
    void              print(std::ostream& stream,uint level,uint optionFlags) const;
    void              read(MemoryReader& memoryReader);
};


}
}

