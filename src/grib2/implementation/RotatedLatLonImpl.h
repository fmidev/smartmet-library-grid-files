#pragma once

#include "grib2/definition/RotatedLatLon.h"


namespace SmartMet
{
namespace GRIB2
{

class RotatedLatLonImpl : public RotatedLatLon
{
  public:

                      RotatedLatLonImpl();
                      RotatedLatLonImpl(const RotatedLatLonImpl& other);
    virtual           ~RotatedLatLonImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    T::Coordinate_vec getGridLatLonCoordinates() const;
    bool              getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    bool              getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    bool              getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    bool              getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;

    void              initSpatialReference();
    void              print(std::ostream& stream,uint level,uint optionFlags) const;
    void              read(MemoryReader& memoryReader);
};

}
}


