#pragma once

#include "grib1/definition/RotatedLatLon.h"

namespace SmartMet
{
namespace GRIB1
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

}  // namespace GRIB1
}  // namespace SmartMet
