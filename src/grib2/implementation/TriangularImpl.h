#pragma once

#include "../definition/Triangular.h"


namespace SmartMet
{
namespace GRIB2
{

class TriangularImpl : public Triangular
{
  public:
                        TriangularImpl();
                        TriangularImpl(const TriangularImpl& other);
    ~TriangularImpl() override;
    TriangularImpl& operator=(const TriangularImpl&) = default;

    GridDefinition*     createGridDefinition() const override;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const override;
    T::Dimensions       getGridDimensions() const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;

    void                initSpatialReference() override;
    void                read(MemoryReader& memoryReader) override;
};

}
}


