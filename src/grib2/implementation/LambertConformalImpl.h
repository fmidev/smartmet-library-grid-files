#pragma once

#include "grib2/definition/LambertConformal.h"


namespace SmartMet
{
namespace GRIB2
{

class LambertConformalImpl : public LambertConformal
{
  public:

                      LambertConformalImpl();
                      LambertConformalImpl(const LambertConformalImpl& other);
    virtual           ~LambertConformalImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              print(std::ostream& stream,uint level,uint optionFlags) const;
    void              read(MemoryReader& memoryReader);

  protected:

    mutable OGRSpatialReference*          mSr_lambertConformal;
    mutable OGRCoordinateTransformation*  mCt_latlon2lambert;
    mutable OGRCoordinateTransformation*  mCt_lambert2latlon;

};


}
}



