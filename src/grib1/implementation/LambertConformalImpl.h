#pragma once

#include "../definition/LambertConformal.h"

namespace SmartMet
{
namespace GRIB1
{

class LambertConformalImpl : public LambertConformal
{
  public:

                        LambertConformalImpl();
                        LambertConformalImpl(const LambertConformalImpl& other);
    virtual             ~LambertConformalImpl();

    GridDefinition*     createGridDefinition() const;

    bool                getGridMetricCellSize(double& width,double& height) const;
    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const;
    T::Dimensions       getGridDimensions() const;
    std::size_t         getGridColumnCount() const;
    std::size_t         getGridRowCount() const;
    std::string         getGridGeometryString() const;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    bool                reverseXDirection() const;
    bool                reverseYDirection() const;

    bool                getProperty(uint propertyId,long long& value);
    void                getProperties(T::PropertySettingVec& properties);
    bool                setProperty(uint propertyId,long long value);

    void                initSpatialReference();
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
