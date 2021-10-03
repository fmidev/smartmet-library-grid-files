#pragma once

#include "../definition/Mercator.h"

namespace SmartMet
{
namespace GRIB1
{

class MercatorImpl : public Mercator
{
  public:

                        MercatorImpl();
                        MercatorImpl(const MercatorImpl& other);
                ~MercatorImpl() override;

    GridDefinition*     createGridDefinition() const override;

    bool                getGridMetricCellSize(double& width,double& height) const override;
    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    T::Dimensions       getGridDimensions() const override;
    std::string         getGridGeometryString() const override;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const override;
    bool                reverseXDirection() const override;
    bool                reverseYDirection() const override;

    bool                getProperty(uint propertyId,long long& value) override;
    bool                setProperty(uint propertyId,long long value) override;

    void                initSpatialReference() override;
    void                print(std::ostream& stream,uint level,uint optionFlags) const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB1
}  // namespace SmartMet
