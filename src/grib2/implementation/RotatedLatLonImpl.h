#pragma once

#include "../definition/RotatedLatLon.h"


namespace SmartMet
{
namespace GRIB2
{

class RotatedLatLonImpl : public RotatedLatLon
{
  public:

                      RotatedLatLonImpl();
                      RotatedLatLonImpl(const RotatedLatLonImpl& other);
    virtual           ~RotatedLatLonImpl();

    GridDefinition*   createGridDefinition() const;

    bool              getGridCellSize(double& width,double& height) const;
    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    std::string       getGridGeometryString() const;
    T::Coordinate_vec getGridLatLonCoordinates() const;
    bool              getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    bool              getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;
    bool              getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    bool              getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    bool              getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool              getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    bool              reverseXDirection() const;
    bool              reverseYDirection() const;

    void              initSpatialReference();
    void              print(std::ostream& stream,uint level,uint optionFlags) const;
    void              read(MemoryReader& memoryReader);

  private:

    void              init() const;

    mutable uint      mNi;
    mutable uint      mNj;
    mutable double    mDx;
    mutable double    mDy;
    mutable double    mStartX;
    mutable double    mStartY;
    mutable double    mSouthPoleLat;
    mutable double    mSouthPoleLon;
    mutable bool      mInitialized;
    mutable OGRSpatialReference*          mSr_rotatedLatlon;
    mutable OGRCoordinateTransformation*  mCt_latlon2rotatedLatlon;
    mutable OGRCoordinateTransformation*  mCt_rotatedLatlon2latlon;
};

}
}


