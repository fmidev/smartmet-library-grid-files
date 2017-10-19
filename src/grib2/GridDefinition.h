#pragma once

#include "common/Coordinate.h"
#include "common/Dimensions.h"
#include "grid/Typedefs.h"
#include "common/MemoryReader.h"
#include "common/AttributeList.h"
#include <gdal/ogr_spatialref.h>
#include <map>


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

    virtual T::Hash             countHash(); // Do not call this, call getGridHash() instead.
    virtual void                getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    virtual T::GeometryId       getGridGeometryId() const;
    virtual std::string         getGridGeometryName();
    virtual T::Coordinate_vec   getGridCoordinates() const;
    virtual T::Dimensions_opt   getGridDimensions() const;
    T::Hash                     getGridHash();
    virtual T::Coordinate_vec   getGridLatLonCoordinates() const;
    virtual bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    virtual bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    T::GridLayout               getGridLayout();
    virtual bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    virtual bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    virtual bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    virtual bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    T::GridProjection           getGridProjection();

    T::SpatialReference*        getSpatialReference();
    virtual void                initSpatialReference();
    bool                        isGridGlobal() const;
    virtual void                print(std::ostream& stream,uint level,uint optionFlags) const;
    virtual void                setGridGeometryId(T::GeometryId geometryId);
    virtual void                setGridGeometryName(std::string geometryName);
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

    /*! \brief The geometry identifier. */
    T::GeometryId               mGeometryId;

    /*! \brief The geometry identifier. */
    std::string                 mGeometryName;

    /*! \brief The grid projection. */
    T::GridProjection           mGridProjection;

  private:

    /*! \brief The pointer to the original spatial reference (or actually to its clone). */
    mutable OGRSpatialReference*          mOrigSpatialReference;

    /*! \brief The coordinate transformer used for converting latlon coordinates to the original coordinates. */
    mutable OGRCoordinateTransformation*  mCoordinateTranformation_latlon2orig;

    /*! \brief The coordinate transformer used for converting original coordinates to the latlon coordinates. */
    mutable OGRCoordinateTransformation*  mCoordinateTranformation_orig2latlon;

};

typedef GridDefinition* GridDefinition_ptr;
typedef std::unique_ptr<GridDefinition> GridDefinition_uptr;
typedef std::vector<GridDefinition*> GridDefinition_pvec;
typedef std::map<uint,GridDefinition*> GridDefinition_pmap;
typedef std::shared_ptr<GridDefinition> GridDefinition_sptr;
typedef std::vector<GridDefinition_sptr> GridDefinition_spvec;


}  // namespace GRIB2
}  // namespace SmartMet
