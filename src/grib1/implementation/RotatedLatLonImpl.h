#pragma once

#include "../definition/RotatedLatLon.h"

namespace SmartMet
{
namespace GRIB1
{

class RotatedLatLonImpl : public RotatedLatLon
{
  public:

                        RotatedLatLonImpl();
                        RotatedLatLonImpl(const RotatedLatLonImpl& other);
    virtual             ~RotatedLatLonImpl();

    GridDefinition*     createGridDefinition() const;

    bool                getGridMetricCellSize(double& width,double& height) const;
    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const;
    T::Dimensions       getGridDimensions() const;
    std::string         getGridGeometryString() const;
    //T::Coordinate_svec  getGridLatLonCoordinates() const;
    bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;
    bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    void                getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const;
    bool                reverseXDirection() const;
    bool                reverseYDirection() const;
    std::string         getProj4();
    std::string         getWKT();

    bool                getProperty(uint propertyId,long long& value);
    void                getProperties(T::PropertySettingVec& properties);
    bool                setProperty(uint propertyId,long long value);
    bool                setProperty(uint propertyId,double value);

    void                initSpatialReference();
    void                print(std::ostream& stream,uint level,uint optionFlags) const;
    void                read(MemoryReader& memoryReader);

  private:

    void                init() const;

    mutable double      mDx;
    mutable double      mDy;
    mutable double      mStartX;
    mutable double      mStartY;
    mutable double      mSouthPoleLat;
    mutable double      mSouthPoleLon;
    mutable bool        mInitialized;
    mutable std::string mProj4;
};

}  // namespace GRIB1
}  // namespace SmartMet
