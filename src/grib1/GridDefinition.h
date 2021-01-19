#pragma once

#include "../grid/Typedefs.h"
#include "../common/Coordinate.h"
#include "../common/Dimensions.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../common/AttributeList.h"
#include "../common/CoordinateConversions.h"
#include "definition/GridAreaSettings.h"
#include "definition/ScanningModeSettings.h"
#include "definition/ResolutionFlagsSettings.h"
#include "definition/RotationSettings.h"

#include <ogr_spatialref.h>
#include <map>


namespace SmartMet
{
namespace GRIB1
{

// Base class for grid definitions

class GridDefinition
{
 public:

                                GridDefinition();
                                GridDefinition(const GridDefinition& other);
    virtual                     ~GridDefinition();

    virtual T::Hash             countHash(); // Do not call this, call getGridHash() instead.
    virtual GridDefinition*     createGridDefinition() const;

    virtual void                getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const;
    virtual T::Dimensions       getGridDimensions() const;
    virtual T::GeometryId       getGridGeometryId() const;
    virtual std::string         getGridGeometryString() const;
    virtual std::string         getGridGeometryName();
    T::Hash                     getGridHash();
    virtual bool                getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    virtual T::Coordinate_svec  getGridLatLonCoordinates() const;
    virtual bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    virtual bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;
    virtual bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    T::GridLayout               getGridLayout();
    virtual bool                getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    virtual void                getGridCellAverageSize(double& width,double& height);
    virtual bool                getGridMetricCellSize(double& width,double& height) const;
    virtual bool                getGridMetricSize(double& width,double& height) const;
    virtual T::Coordinate_svec  getGridOriginalCoordinates() const;
    virtual bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    virtual bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    virtual bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    virtual bool                getGridOriginalCoordinatesByLatLonCoordinatesNoCache(double lat,double lon,double& x,double& y) const;
    virtual std::size_t         getGridOriginalColumnCount(std::size_t row) const;
    virtual std::size_t         getGridOriginalColumnCount() const;
    virtual std::size_t         getGridOriginalRowCount() const;
    virtual std::uint32_t       getGridOriginalValueCount() const;
    virtual int                 getGridOriginalValueIndex(uint grid_i,uint grid_j) const;
    virtual bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    virtual bool                getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j) const;
    virtual void                getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const;
    virtual bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    virtual T::GridProjection   getGridProjection() const;
    virtual std::size_t         getGridColumnCount() const;
    virtual std::size_t         getGridRowCount() const;
    virtual uint                getTemplateNumber() const;

    virtual bool                reverseXDirection() const;
    virtual bool                reverseYDirection() const;
    virtual void                initSpatialReference();
    virtual void                initRowPositions(std::vector<std::uint32_t>& rowPositions);

    virtual void                setGridGeometryId(T::GeometryId geometryId);
    virtual void                setGridGeometryName(const std::string& geometryName);

    virtual bool                getProperty(uint propertyId,long long& value);
    virtual bool                getProperty(uint propertyId,double& value);

    virtual bool                setProperty(uint propertyId,long long value);
    virtual bool                setProperty(uint propertyId,double value);

    T::SpatialRef*              getSpatialReference();
    virtual std::string         getWKT();
    virtual std::string         getProj4();
    bool                        isGridGlobal() const;
    bool                        isRelativeUV() const;

    virtual void                read(MemoryReader& memoryReader);
    virtual void                write(DataWriter& dataWriter);
    virtual void                print(std::ostream& stream,uint level,uint optionFlags) const;

    virtual GridAreaSettings*        getGridArea() const;
    virtual ScanningModeSettings*    getScanningMode() const;
    virtual ResolutionFlagsSettings* getResolutionFlags() const;
    virtual RotationSettings*        getRotation() const;

   protected:

    virtual double              getMajorAxis(uchar resolutionAndComponentFlags);
    virtual double              getMinorAxis(uchar resolutionAndComponentFlags);
    virtual double              getFlattening(uchar resolutionAndComponentFlags);

    virtual bool                getProperty_gridArea(uint propertyId,long long& value);
    virtual bool                getProperty_scanningMode(uint propertyId,long long& value);
    virtual bool                getProperty_resolutionFlags(uint propertyId,long long& value);
    virtual bool                getProperty_rotation(uint propertyId,long long& value);
    virtual bool                getProperty_rotation(uint propertyId,double& value);

    virtual bool                setProperty_gridArea(uint propertyId,long long value);
    virtual bool                setProperty_scanningMode(uint propertyId,long long value);
    virtual bool                setProperty_resolutionFlags(uint propertyId,long long value);
    virtual bool                setProperty_rotation(uint propertyId,long long value);
    virtual bool                setProperty_rotation(uint propertyId,double value);

    /*! \brief The spatial reference. */
     T::SpatialRef              mSpatialReference;


     /*! \brief The grid layout. */
     T::GridLayout              mGridLayout;

     /*! \brief The hash of the grid. */
     T::Hash                    mHash;

     /*! \brief The indication flag for the global grid. */
     bool                       mGlobal;

     /*! \brief The start indexes of the grid rows when the grid is irregular. */
     std::vector<std::uint32_t> mRowPositions;

     /*! \brief The geometry identifier. */
     T::GeometryId              mGeometryId;

     /*! \brief The geometry name. */
     std::string                mGeometryName;

     /*! \brief The grid projection. */
     T::GridProjection          mGridProjection;

     OGRSpatialReference        mLatlonSpatialReference;
};

typedef GridDefinition* GridDef_ptr;
typedef std::shared_ptr<GridDefinition> GridDefinition_sptr;
typedef std::vector<GridDef_ptr> GridDef_pvec;
typedef std::map<uint,GridDef_ptr> GridDefinition_pmap;
typedef std::map<std::string,GridDef_ptr> GridDef_map;


}  // namespace GRID
}  // namespace SmartMet
