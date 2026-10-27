#pragma once

#include "../definition/ObliqueLambertConformal.h"

namespace SmartMet
{
namespace GRIB1
{

class ObliqueLambertConformalImpl : public ObliqueLambertConformal
{
  public:

                        ObliqueLambertConformalImpl();
                        ObliqueLambertConformalImpl(const ObliqueLambertConformalImpl& other);
    ~ObliqueLambertConformalImpl() override;
    ObliqueLambertConformalImpl& operator=(const ObliqueLambertConformalImpl&) = default;

    GridDefinition*     createGridDefinition() const override;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const override;
    T::Dimensions       getGridDimensions() const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;

    void                initSpatialReference() override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB1
}  // namespace SmartMet
