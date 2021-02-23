#pragma once

#include "../definition/PolarStereographic.h"

namespace SmartMet
{
namespace GRIB1
{

class PolarStereographicImpl : public PolarStereographic
{
  public:

                        PolarStereographicImpl();
                        PolarStereographicImpl(const PolarStereographicImpl& other);
    virtual             ~PolarStereographicImpl();

    GridDefinition*     createGridDefinition() const;

    bool                getGridMetricCellSize(double& width,double& height) const;
    T::Coordinate_svec  getGridOriginalCoordinates() const;
    T::Dimensions       getGridDimensions() const;
    std::size_t         getGridColumnCount() const;
    std::size_t         getGridRowCount() const;
    std::string         getGridGeometryString() const;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool                reverseXDirection() const;
    bool                reverseYDirection() const;

    bool                getProperty(uint propertyId,long long& value);
    bool                setProperty(uint propertyId,long long value);

    void                initSpatialReference();
    void                print(std::ostream& stream,uint level,uint optionFlags) const;
    void                read(MemoryReader& memoryReader);

  protected:

    void                init() const;

    mutable double      mDxx;
    mutable double      mDyy;
    mutable double      mStartX;
    mutable double      mStartY;
    mutable bool        mInitialized;

};

}  // namespace GRIB1
}  // namespace SmartMet
