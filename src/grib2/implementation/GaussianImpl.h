#pragma once

#include "../definition/Gaussian.h"


namespace SmartMet
{
namespace GRIB2
{

class GaussianImpl : public Gaussian
{
  public:
                        GaussianImpl();
                        GaussianImpl(const GaussianImpl& other);
                ~GaussianImpl() override;

    GridDefinition*     createGridDefinition() const override;

    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    T::Dimensions       getGridDimensions() const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const override;

    void                initSpatialReference() override;
    void                print(std::ostream& stream,uint level,uint optionFlags) const override;
    void                read(MemoryReader& memoryReader) override;
};


}
}


