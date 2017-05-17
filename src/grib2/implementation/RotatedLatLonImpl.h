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
    bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    void              getOriginalCoordinatesByLatLon(double lat,double lon,double& x,double& y) const;
    void              getLatLonByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    void              initSpatialReference();
    void              print(std::ostream& stream,uint level,uint optionFlags) const;
    void              read(MemoryReader& memoryReader);
};

}
}


