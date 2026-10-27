#pragma once

#include "../definition/AzimuthRange.h"

namespace SmartMet
{
namespace GRIB2
{

class AzimuthRangeImpl : public AzimuthRange
{
  public:
                        AzimuthRangeImpl();
                        AzimuthRangeImpl(const AzimuthRangeImpl& other);
    ~AzimuthRangeImpl() override;
    AzimuthRangeImpl& operator=(const AzimuthRangeImpl&) = default;

    GridDefinition*     createGridDefinition() const override;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const override;
    T::Dimensions       getGridDimensions() const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;

    void                initSpatialReference() override;
    void                read(MemoryReader& memoryReader) override;
};

}
}
