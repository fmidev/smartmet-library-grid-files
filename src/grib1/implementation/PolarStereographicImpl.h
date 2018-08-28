#pragma once

#include "../definition/PolarStereographic.h"

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

    GridDefinition*   createGridDefinition() const;

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    std::string       getGridGeometryString() const;
    bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    bool              reverseXDirection() const;
    bool              reverseYDirection() const;

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
