#pragma once

#include "../definition/StretchedRotatedLatLon.h"
#include "../../common/Coordinate.h"

namespace SmartMet
{
namespace GRIB1
{

class StretchedRotatedLatLonImpl : public StretchedRotatedLatLon
{
  public:

                        StretchedRotatedLatLonImpl();
                        StretchedRotatedLatLonImpl(const StretchedRotatedLatLonImpl& other);
    ~StretchedRotatedLatLonImpl() override;
    StretchedRotatedLatLonImpl& operator=(const StretchedRotatedLatLonImpl&) = default;

    GridDefinition*     createGridDefinition() const override;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const override;
    T::Dimensions       getGridDimensions() const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;

    void                initSpatialReference() override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB1
}  // namespace SmartMet
