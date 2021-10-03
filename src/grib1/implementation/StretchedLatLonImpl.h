#pragma once

#include "../definition/StretchedLatLon.h"

namespace SmartMet
{
namespace GRIB1
{

class StretchedLatLonImpl : public StretchedLatLon
{
  public:
                        StretchedLatLonImpl();
                        StretchedLatLonImpl(const StretchedLatLonImpl& other);
                ~StretchedLatLonImpl() override;

    GridDefinition*     createGridDefinition() const override;

    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    T::Dimensions       getGridDimensions() const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;

    void                initSpatialReference() override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB1
}  // namespace SmartMet
