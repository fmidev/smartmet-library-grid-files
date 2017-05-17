#pragma once

#include "grib2/definition/Gaussian.h"


namespace SmartMet
{
namespace GRIB2
{

class GaussianImpl : public Gaussian
{
  public:
                      GaussianImpl();
                      GaussianImpl(const GaussianImpl& other);
    virtual           ~GaussianImpl();

    void              getGridLatlonAreaCoordinates(double& firstLat,double& firstLon,double& lastLat,double& lastLon) const;
    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const;
    bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              print(std::ostream& stream,uint level,uint optionFlags) const;
    void              read(MemoryReader& memoryReader);
};


}
}


