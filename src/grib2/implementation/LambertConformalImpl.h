#pragma once

#include "../definition/LambertConformal.h"


namespace SmartMet
{
namespace GRIB2
{

class LambertConformalImpl : public LambertConformal
{
  public:

                        LambertConformalImpl();
                        LambertConformalImpl(const LambertConformalImpl& other);
                ~LambertConformalImpl() override;

    GridDefinition*     createGridDefinition() const override;

    bool                getGridMetricCellSize(double& width,double& height) const override;
    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    T::Dimensions       getGridDimensions() const override;
    std::size_t         getGridColumnCount() const override;
    std::size_t         getGridRowCount() const override;
    std::string         getGridGeometryString() const override;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const override;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const override;
    bool                reverseXDirection() const override;
    bool                reverseYDirection() const override;

    bool                setProperty(uint propertyId,long long value) override;

    void                initSpatialReference() override;
    void                print(std::ostream& stream,uint level,uint optionFlags) const override;
    void                read(MemoryReader& memoryReader) override;

  private:

    void                init() const;

    mutable double      mDxx;
    mutable double      mDyy;
    mutable double      mStartX;
    mutable double      mStartY;
    mutable bool        mInitialized;
};


}
}



