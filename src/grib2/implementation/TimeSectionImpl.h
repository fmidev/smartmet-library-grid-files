#pragma once

#include "grib2/definition/TimeSection.h"


namespace SmartMet
{
namespace GRIB2
{

class TimeSectionImpl : public TimeSection
{
  public:

                      TimeSectionImpl();
                      TimeSectionImpl(const TimeSectionImpl& other);
    virtual           ~TimeSectionImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}



