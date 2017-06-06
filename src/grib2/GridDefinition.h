#pragma once

#include "grid/Coordinate.h"
#include "grid/Dimensions.h"
#include "grid/Typedefs.h"
#include "common/MemoryReader.h"
#include "common/AttributeList.h"
#include <gdal/ogr_spatialref.h>


namespace SmartMet
{
namespace GRIB2
{

// Base class for grid definitions

class GridDefinition
{
  public:

    GridDefinition();
    virtual ~GridDefinition();

    virtual T::Hash             countHash(); // Do not call this, call getHash() instead.
    virtual void                getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    virtual void                getGridLatlonAreaCoordinates(double& firstLat,double& firstLon,double& lastLat,double& lastLon) const;
    virtual void                getGridOriginalAreaCoordinates(double& x1,double& y1,double& x2,double& y2) const;
    virtual T::Coordinate_vec   getGridCoordinates() const;
    virtual T::Dimensions_opt   getGridDimensions() const;
    virtual bool                getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const;
    virtual bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    virtual void                getOriginalCoordinatesByLatLon(double lat,double lon,double& x,double& y) const;
    virtual void                getLatLonByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    T::SpatialReference*        getSpatialReference();
    T::GridLayout               getGridLayout();
    T::Hash                     getHash();
    virtual void                initSpatialReference();
    bool                        isGridGlobal() const;
    virtual void                print(std::ostream& stream,uint level,uint optionFlags) const;
    virtual void                read(MemoryReader& memoryReader) {}

  protected:

    /*! \brief The spatial reference. */
    T::SpatialReference         mSpatialReference;

    /*! \brief The grid layout. */
    T::GridLayout               mGridLayout;

    /*! \brief The hash of the grid. */
    T::Hash                     mHash;

    /*! \brief The indication flag for the global grid. */
    bool                        mGlobal;

  private:

    /*! \brief The pointer to the original spatial reference (or actually to its clone). */
    mutable OGRSpatialReference*          mOrigSpatialReference;

    /*! \brief The coordinate transformer used for converting latlon coordinates to the original coordinates. */
    mutable OGRCoordinateTransformation*  mCoordinateTranformation_latlon2orig;

    /*! \brief The coordinate transformer used for converting original coordinates to the latlon coordinates. */
    mutable OGRCoordinateTransformation*  mCoordinateTranformation_orig2latlon;

};

typedef std::unique_ptr<GridDefinition> GridDefinition_uptr;

}  // namespace GRIB2
}  // namespace SmartMet