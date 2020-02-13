#pragma once

#include "../definition/Gaussian.h"

namespace SmartMet
{
namespace GRIB1
{

class GaussianImpl : public Gaussian
{
  public:

                      GaussianImpl();
                      GaussianImpl(const GaussianImpl& other);
    virtual           ~GaussianImpl();

    GridDefinition*   createGridDefinition() const;

    T::Coordinate_vec getGridOriginalCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;

    void              initSpatialReference();
    void              print(std::ostream& stream,uint level,uint optionFlags) const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
