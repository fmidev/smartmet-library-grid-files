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
    virtual             ~TimeSectionImpl();

    GridDefinition*     createGridDefinition() const;

    T::Coordinate_svec  getGridOriginalCoordinates() const;
    T::Dimensions       getGridDimensions() const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void                initSpatialReference();
    void                read(MemoryReader& memoryReader);
};

}
}



