#pragma once

#include "../definition/Mercator.h"


namespace SmartMet
{
namespace GRIB2
{

class MercatorImpl : public Mercator
{
  public:
                        MercatorImpl();
                        MercatorImpl(const MercatorImpl& other);
    ~MercatorImpl() override;

    GridDefinition*     createGridDefinition() const override;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const override;
    T::Dimensions       getGridDimensions() const override;
    std::string         getGridGeometryString() const override;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const override;
    bool                getGridMetricCellSize(double& width,double& height) const override;

    void                getProperties(T::PropertySettingVec& properties) override;
    bool                setProperty(uint propertyId,Int64 value) override;

    void                initSpatialReference() override;
    void                print(std::ostream& stream,uint level,uint optionFlags) const override;
    void                read(MemoryReader& memoryReader) override;
};


}
}


