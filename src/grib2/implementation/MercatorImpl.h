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
    virtual             ~MercatorImpl();

    GridDefinition*     createGridDefinition() const;

    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const;
    T::Dimensions       getGridDimensions() const;
    std::string         getGridGeometryString() const;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    bool                getGridMetricCellSize(double& width,double& height) const;

    void                getProperties(T::PropertySettingVec& properties);
    bool                setProperty(uint propertyId,long long value);

    void                initSpatialReference();
    void                print(std::ostream& stream,uint level,uint optionFlags) const;
    void                read(MemoryReader& memoryReader);
};


}
}


