#pragma once

#include "../../common/Dimensions.h"
#include "../definition/PolarStereographic.h"
#include <boost/optional.hpp>

namespace SmartMet
{
namespace GRIB2
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

    bool                setProperty(uint propertyId,long long value);

    void                initSpatialReference();
    void                print(std::ostream& stream,uint level,uint optionFlags) const;
    void                read(MemoryReader& memoryReader);

  protected:

    mutable OGRSpatialReference*          mSr_polarSterographic;
    mutable OGRCoordinateTransformation*  mCt_latlon2pst;
    mutable OGRCoordinateTransformation*  mCt_pst2latlon;

};

}
}

