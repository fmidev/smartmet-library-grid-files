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
                ~RotatedLatLonImpl() override;

    GridDefinition*     createGridDefinition() const override;

    bool                getGridMetricCellSize(double& width,double& height) const override;
    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    T::Dimensions       getGridDimensions() const override;
    std::string         getGridGeometryString() const override;
    //T::Coordinate_svec  getGridLatLonCoordinates() const;
    bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const override;
    bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const override;
    bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const override;
    bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const override;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const override;
    bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const override;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const override;
    void                getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const override;
    bool                reverseXDirection() const override;
    bool                reverseYDirection() const override;
    std::string         getProj4() override;
    std::string         getWKT() override;

    bool                getProperty(uint propertyId,long long& value) override;

    bool                setProperty(uint propertyId,long long value) override;
    bool                setProperty(uint propertyId,double value) override;

    void                initSpatialReference() override;
    void                print(std::ostream& stream,uint level,uint optionFlags) const override;
    void                read(MemoryReader& memoryReader) override;

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
