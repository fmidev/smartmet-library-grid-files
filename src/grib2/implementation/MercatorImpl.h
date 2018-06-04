#pragma once

#include "../definition/Mercator.h"


namespace SmartMet
{
namespace GRIB2
{

class MercatorImpl : public Mercator
{
  public:
                      MercatorImpl();
                      MercatorImpl(const MercatorImpl& other);
    virtual           ~MercatorImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    void              initSpatialReference();
    bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    void              print(std::ostream& stream,uint level,uint optionFlags) const;
    void              read(MemoryReader& memoryReader);

  protected:

    mutable OGRSpatialReference*          mSr_mercator;
    mutable OGRCoordinateTransformation*  mCt_latlon2mercator;
    mutable OGRCoordinateTransformation*  mCt_mercator2latlon;
};


}
}


