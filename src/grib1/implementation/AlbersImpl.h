#pragma once

#include "../definition/Albers.h"

namespace SmartMet
{
namespace GRIB1
{

class AlbersImpl : public Albers
{
  public:

                        AlbersImpl();
                        AlbersImpl(const AlbersImpl& other);
    virtual             ~AlbersImpl();

    GridDefinition*     createGridDefinition() const;

    bool                getGridMetricCellSize(double& width,double& height) const;
    T::Coordinate_svec  getGridOriginalCoordinates() const;
    T::Dimensions       getGridDimensions() const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void                initSpatialReference();
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
