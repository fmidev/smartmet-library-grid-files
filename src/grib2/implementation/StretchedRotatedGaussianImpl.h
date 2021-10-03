#pragma once

#include "../definition/StretchedRotatedGaussian.h"


namespace SmartMet
{
namespace GRIB2
{

class StretchedRotatedGaussianImpl : public StretchedRotatedGaussian
{
  public:

                        StretchedRotatedGaussianImpl();
                        StretchedRotatedGaussianImpl(const StretchedRotatedGaussianImpl& other);
                ~StretchedRotatedGaussianImpl() override;

    GridDefinition*     createGridDefinition() const override;

    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    T::Dimensions       getGridDimensions() const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;

    void                initSpatialReference() override;
    void                read(MemoryReader& memoryReader) override;
};

}
}

