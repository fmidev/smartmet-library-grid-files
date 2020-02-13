#pragma once

#include "../definition/CrossSection.h"


namespace SmartMet
{
namespace GRIB2
{

class CrossSectionImpl : public CrossSection
{
  public:

                      CrossSectionImpl();
                      CrossSectionImpl(const CrossSectionImpl& other);
    virtual           ~CrossSectionImpl();

    GridDefinition*   createGridDefinition() const;

    T::Coordinate_vec getGridOriginalCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}
