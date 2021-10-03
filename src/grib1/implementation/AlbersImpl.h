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
                ~AlbersImpl() override;

    GridDefinition*     createGridDefinition() const override;

    bool                getGridMetricCellSize(double& width,double& height) const override;
    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    T::Dimensions       getGridDimensions() const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;

    void                initSpatialReference() override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB1
}  // namespace SmartMet
