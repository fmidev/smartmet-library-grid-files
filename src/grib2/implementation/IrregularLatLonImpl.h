#pragma once

#include "grib2/definition/IrregularLatLon.h"


namespace SmartMet
{
namespace GRIB2
{

class IrregularLatLonImpl : public IrregularLatLon
{
  public:
                      IrregularLatLonImpl();
                      IrregularLatLonImpl(const IrregularLatLonImpl& other);
    virtual           ~IrregularLatLonImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}
