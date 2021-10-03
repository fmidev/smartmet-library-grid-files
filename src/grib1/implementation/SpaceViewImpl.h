#pragma once

#include "../definition/SpaceView.h"

namespace SmartMet
{
namespace GRIB1
{

class SpaceViewImpl : public SpaceView
{
  public:

                        SpaceViewImpl();
                        SpaceViewImpl(const SpaceViewImpl& other);
                ~SpaceViewImpl() override;

    GridDefinition*     createGridDefinition() const override;

    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    T::Dimensions       getGridDimensions() const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;

    void                initSpatialReference() override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB1
}  // namespace SmartMet
