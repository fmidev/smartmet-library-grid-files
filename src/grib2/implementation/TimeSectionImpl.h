#pragma once

#include "../definition/TimeSection.h"


namespace SmartMet
{
namespace GRIB2
{

class TimeSectionImpl : public TimeSection
{
  public:

                        TimeSectionImpl();
                        TimeSectionImpl(const TimeSectionImpl& other);
                ~TimeSectionImpl() override;

    GridDefinition*     createGridDefinition() const override;

    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    T::Dimensions       getGridDimensions() const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;

    void                initSpatialReference() override;
    void                read(MemoryReader& memoryReader) override;
};

}
}



