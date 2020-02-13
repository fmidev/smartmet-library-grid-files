#pragma once

#include "../definition/IrregularLatLon.h"


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

    GridDefinition*   createGridDefinition() const;

    T::Coordinate_vec getGridOriginalCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}

