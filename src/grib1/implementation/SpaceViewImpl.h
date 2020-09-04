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
    virtual             ~SpaceViewImpl();

    GridDefinition*     createGridDefinition() const;

    T::Coordinate_svec  getGridOriginalCoordinates() const;
    T::Dimensions       getGridDimensions() const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void                initSpatialReference();
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
