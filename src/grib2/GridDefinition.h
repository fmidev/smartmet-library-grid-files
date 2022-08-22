#pragma once

#include "../common/Coordinate.h"
#include "../common/CoordinateConversions.h"
#include "../common/Dimensions.h"
#include "../grid/Typedefs.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../common/AttributeList.h"
#include "definition/EarthShapeSettings.h"
#include "definition/LatLonSettings.h"
#include "definition/RotationSettings.h"

#include <macgyver/CacheStats.h>
#include <ogr_spatialref.h>
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
                                GridDefinition(const GridDefinition& other);
    virtual                     ~GridDefinition();

    virtual T::Hash             countHash() const; // Do not call this, call getGridHash() instead.
    virtual GridDefinition*     createGridDefinition() const;
    virtual void                getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const;
    virtual T::GeometryId       getGridGeometryId() const;
    virtual std::string         getGridGeometryString() const;
    virtual void                getGridCellAverageSize(double& width,double& height) const;
    virtual T::Dimensions       getGridDimensions() const;
    T::Hash                     getGridHash() const;
    virtual bool                getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    virtual T::Coordinate_svec  getGridLatLonCoordinates() const;
    virtual bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    virtual bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;
    virtual bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    virtual bool                getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    virtual bool                getGridMetricCellSize(double& width,double& height) const;
    virtual bool                getGridMetricSize(double& width,double& height) const;
    virtual T::Coordinate_svec  getGridOriginalCoordinates() const;
    virtual bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    virtual bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    virtual bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    virtual bool                getGridOriginalCoordinatesByLatLonCoordinatesNoCache(double lat,double lon,double& x,double& y) const;
    virtual void                getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const;
    virtual bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    virtual bool                getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j) const;
    virtual bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    T::GridProjection           getGridProjection();
    virtual std::size_t         getGridColumnCount() const;
    virtual std::size_t         getGridRowCount() const;
    virtual uint                getTemplateNumber() const;
    T::SpatialRef*              getSpatialReference();
    virtual std::string         getWKT();
    virtual std::string         getProj4();
    virtual void                initSpatialReference();
    bool                        isGridGlobal() const;
    bool                        isRelativeUV() const;
    virtual bool                reverseXDirection() const;
    virtual bool                reverseYDirection() const;

    virtual EarthShapeSettings* getEarthShape() const;
    virtual LatLonSettings *    getLatLon() const;
    virtual RotationSettings*   getRotation() const;
    virtual ResolutionSettings* getResolution() const;

    virtual void                setGridGeometryId(T::GeometryId geometryId);

    virtual bool                getProperty(uint propertyId,long long& value);
    virtual bool                setProperty(uint propertyId,long long value);

    virtual void                read(MemoryReader& memoryReader);
    virtual void                write(DataWriter& dataWriter);
    virtual void                print(std::ostream& stream,uint level,uint optionFlags) const;

    // These methos are used for overiding the earth shape parameters in the grid file

    virtual double              getEarthSemiMajor();
    virtual double              getEarthSemiMinor();
    virtual void                setEarthSemiMajor(double value);
    virtual void                setEarthSemiMinor(double value);

  protected:

    virtual bool                getProperty_EarthShape(uint propertyId,long long& value);
    virtual bool                getProperty_Grid(uint propertyId,long long& value);
    virtual bool                getProperty_Rotation(uint propertyId,long long& value);
    virtual bool                getProperty_LatLon(uint propertyId,long long& value);

    virtual bool                setProperty_EarthShape(uint propertyId,long long value);
    virtual bool                setProperty_Grid(uint propertyId,long long value);
    virtual bool                setProperty_Rotation(uint propertyId,long long value);
    virtual bool                setProperty_LatLon(uint propertyId,long long value);

    virtual double              getMajorAxis(EarthShapeSettings& earthSettings);
    virtual double              getMinorAxis(EarthShapeSettings& earthSettings);
    virtual double              getFlattening(EarthShapeSettings& earthSettings);

    virtual void                insertTranformIntoCache(std::size_t hash,double lat,double lon,double x,double y) const;
    virtual bool                getTransformFromCache(std::size_t hash,double lat,double lon,double& x,double& y) const;


    /*! \brief The spatial reference. */
    T::SpatialRef               mSpatialReference;
    OGRSpatialReference         mLatlonSpatialReference;

    double                      mEarth_semiMajor;
    double                      mEarth_semiMinor;

    /*! \brief The hash of the grid. */
    mutable T::Hash             mHash;

    /*! \brief The geometry identifier. */
    T::GeometryId               mGeometryId;

    /*! \brief The grid projection. */
    T::GridProjection           mGridProjection;

    /*! \brief The indication flag for the global grid. */
    bool                        mGlobal;
};


typedef GridDefinition* GridDef_ptr;
typedef std::vector<GridDefinition*> GridDef_pvec;
typedef std::map<std::string,GridDefinition*> GridDef_map;
typedef std::map<uint,GridDefinition*> GridDefinition_pmap;
typedef std::shared_ptr<GridDefinition> GridDefinition_sptr;
typedef std::shared_ptr<GridDefinition> GridDef_sptr;
typedef std::map<std::string,GridDef_sptr> GridDef_spmap;
typedef std::vector<GridDefinition_sptr> GridDefinition_spvec;

extern Fmi::Cache::CacheStats coordinateCache_stats;
extern Fmi::Cache::CacheStats transformCache1_stats;
extern Fmi::Cache::CacheStats transformCache2_stats;


}  // namespace GRIB2
}  // namespace SmartMet
