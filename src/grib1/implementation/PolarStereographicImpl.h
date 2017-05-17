#pragma once

#include "grib1/definition/PolarStereographic.h"

namespace SmartMet
{
namespace GRIB1
{

class PolarStereographicImpl : public PolarStereographic
{
  public:

                      PolarStereographicImpl();
                      PolarStereographicImpl(const PolarStereographicImpl& other);
    virtual           ~PolarStereographicImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              print(std::ostream& stream,uint level,uint optionFlags) const;
    void              read(MemoryReader& memoryReader);

  protected:

    mutable OGRSpatialReference*          mSr_polarSterographic;
    mutable OGRCoordinateTransformation*  mCt_latlon2pst;
    mutable OGRCoordinateTransformation*  mCt_pst2latlon;
};

}  // namespace GRIB1
}  // namespace SmartMet
