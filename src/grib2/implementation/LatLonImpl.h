#pragma once

#include "../definition/LatLon.h"

namespace SmartMet
{
namespace GRIB2
{

class LatLonImpl : public LatLon
{
  public:

                        LatLonImpl();
                        LatLonImpl(const LatLonImpl& other);
                ~LatLonImpl() override;

    GridDefinition*     createGridDefinition() const override;

    bool                getGridMetricCellSize(double& width,double& height) const override;
    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    T::Dimensions       getGridDimensions() const override;
    std::size_t         getGridColumnCount() const override;
    std::size_t         getGridRowCount() const override;
    std::string         getGridGeometryString() const override;
    T::Coordinate_svec  getGridLatLonCoordinates() const override;
    bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const override;
    bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const override;
    bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const override;
    bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const override;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const override;
    bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const override;
    bool                reverseXDirection() const override;
    bool                reverseYDirection() const override;

    void                initSpatialReference() override;
    void                print(std::ostream& stream,uint level,uint optionFlags) const override;
    void                read(MemoryReader& memoryReader) override;

  private:

    void                init() const;

    mutable uint        mNi;
    mutable uint        mNj;
    mutable double      mDx;
    mutable double      mDy;
    mutable double      mStartX;
    mutable double      mStartY;
    mutable bool        mInitialized;
};


}
}

