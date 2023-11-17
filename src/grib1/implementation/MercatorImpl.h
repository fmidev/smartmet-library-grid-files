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
    virtual             ~MercatorImpl();

    GridDefinition*     createGridDefinition() const;

    bool                getGridMetricCellSize(double& width,double& height) const;
    T::Coordinate_svec  getGridOriginalCoordinatesNoCache() const;
    T::Dimensions       getGridDimensions() const;
    std::string         getGridGeometryString() const;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    bool                reverseXDirection() const;
    bool                reverseYDirection() const;

    bool                getProperty(uint propertyId,long long& value);
    bool                setProperty(uint propertyId,long long value);

    void                initSpatialReference();
    void                print(std::ostream& stream,uint level,uint optionFlags) const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB1
}  // namespace SmartMet
