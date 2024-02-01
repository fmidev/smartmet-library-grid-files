#pragma once

#include "../definition/LatLon.h"

namespace SmartMet
{
namespace GRIB1
{

class LatLonImpl : public LatLon
{
  public:

                        LatLonImpl();
                        LatLonImpl(const LatLonImpl& other);
    virtual             ~LatLonImpl();

    GridDefinition*     createGridDefinition() const;

    bool                getGridMetricCellSize(double& width,double& height) const;
    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const;
    T::Dimensions       getGridDimensions() const;
    std::size_t         getGridColumnCount() const;
    std::size_t         getGridRowCount() const;
    std::string         getGridGeometryString() const;
    T::Coordinate_svec  getGridLatLonCoordinates() const;
    bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;
    bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    bool                reverseXDirection() const;
    bool                reverseYDirection() const;

    bool                getProperty(uint propertyId,long long& value);
    void                getProperties(T::PropertySettingVec& properties);
    bool                setProperty(uint propertyId,long long value);

    void                initSpatialReference();
    void                print(std::ostream& stream,uint level,uint optionFlags) const;
    void                read(MemoryReader& memoryReader);

  private:

    void                init() const;

    mutable double      mDx;
    mutable double      mDy;
    mutable double      mStartX;
    mutable double      mStartY;
    mutable bool        mInitialized;
};

}  // namespace GRIB1
}  // namespace SmartMet
