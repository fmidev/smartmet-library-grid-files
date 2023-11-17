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
    virtual             ~ObliqueLambertConformalImpl();

    GridDefinition*     createGridDefinition() const;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const;
    T::Dimensions       getGridDimensions() const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void                initSpatialReference();
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
