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

    GridDefinition*   createGridDefinition() const;

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    std::string       getGridGeometryString() const;
    bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    bool              getGridCellSize(double& width,double& height) const;

    bool              setProperty(uint propertyId,long long value);

    void              initSpatialReference();
    void              print(std::ostream& stream,uint level,uint optionFlags) const;
    void              read(MemoryReader& memoryReader);

  protected:

    mutable OGRSpatialReference*          mSr_mercator;
    mutable OGRCoordinateTransformation*  mCt_latlon2mercator;
    mutable OGRCoordinateTransformation*  mCt_mercator2latlon;
};


}
}


