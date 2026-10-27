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
    ~LambertConformalImpl() override;
    LambertConformalImpl& operator=(const LambertConformalImpl&) = default;

    GridDefinition*     createGridDefinition() const override;

    bool                getGridMetricCellSize(double& width,double& height) const override;
    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const override;
    T::Dimensions       getGridDimensions() const override;
    std::size_t         getGridColumnCount() const override;
    std::size_t         getGridRowCount() const override;
    std::string         getGridGeometryString() const override;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const override;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const override;
    bool                reverseXDirection() const override;
    bool                reverseYDirection() const override;

    bool                getProperty(uint propertyId,Int64& value) override;
    void                getProperties(T::PropertySettingVec& properties) override;
    bool                setProperty(uint propertyId,Int64 value) override;

    void                initSpatialReference() override;
    void                read(MemoryReader& memoryReader) override;

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
