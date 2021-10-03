#pragma once

#include "../definition/CrossSection.h"


namespace SmartMet
{
namespace GRIB2
{

class CrossSectionImpl : public CrossSection
{
  public:

                        CrossSectionImpl();
                        CrossSectionImpl(const CrossSectionImpl& other);
                ~CrossSectionImpl() override;

    GridDefinition*     createGridDefinition() const override;

    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    T::Dimensions       getGridDimensions() const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;

    void                initSpatialReference() override;
    void                read(MemoryReader& memoryReader) override;
};

}
}
