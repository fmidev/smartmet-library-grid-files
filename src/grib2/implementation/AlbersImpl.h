#pragma once

#include "../definition/Albers.h"

namespace SmartMet
{
namespace GRIB2
{

class AlbersImpl : public Albers
{
  public:

                        AlbersImpl();
                        AlbersImpl(const AlbersImpl& other);
    ~AlbersImpl() override;
    AlbersImpl& operator=(const AlbersImpl&) = default;

    GridDefinition*     createGridDefinition() const override;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const override;
    T::Dimensions       getGridDimensions() const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;

    void                initSpatialReference() override;
    void                read(MemoryReader& memoryReader) override;
};

}
}
