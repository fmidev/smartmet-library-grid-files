#pragma once

#include "../grid/Typedefs.h"
#include "../common/Coordinate.h"
#include "../common/Dimensions.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../common/AttributeList.h"

#include <gdal/ogr_spatialref.h>
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

    virtual void                getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    virtual T::Dimensions       getGridDimensions() const;
    virtual T::GeometryId       getGridGeometryId() const;
    virtual std::string         getGridGeometryString() const;
    virtual std::string         getGridGeometryName();
    virtual void                getGridCellAverageSize(double& width,double& height);
    virtual T::Coordinate_vec   getGridCoordinates() const;
    T::Hash                     getGridHash();
    virtual bool                getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    virtual T::Coordinate_vec   getGridLatLonCoordinates() const;
    virtual bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    virtual bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;
    virtual bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    T::GridLayout               getGridLayout();
    virtual bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    virtual bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    virtual bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    virtual std::size_t         getGridOriginalColumnCount(std::size_t row) const;
    virtual std::size_t         getGridOriginalColumnCount() const;
    virtual std::size_t         getGridOriginalRowCount() const;
    virtual std::uint32_t       getGridOriginalValueCount() const;
    virtual int                 getGridOriginalValueIndex(uint grid_i,uint grid_j) const;
    virtual bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    virtual bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    virtual T::GridProjection   getGridProjection() const;
    virtual uint                getTemplateNumber() const;

    virtual bool                reverseXDirection() const;
    virtual bool                reverseYDirection() const;
    virtual void                initSpatialReference();
    virtual void                initRowPositions(std::vector<std::uint32_t>& rowPositions);

    virtual void                setGridGeometryId(T::GeometryId geometryId);
    virtual void                setGridGeometryName(std::string geometryName);

    T::SpatialRef*              getSpatialReference();
    bool                        isGridGlobal() const;

    virtual void                read(MemoryReader& memoryReader);
    virtual void                write(DataWriter& dataWriter);
    virtual void                print(std::ostream& stream,uint level,uint optionFlags) const;

   protected:

    virtual double              getMajorAxis(uchar resolutionAndComponentFlags);
    virtual double              getMinorAxis(uchar resolutionAndComponentFlags);
    virtual double              getFlattening(uchar resolutionAndComponentFlags);

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


   private:

     /*! \brief The pointer to the original spatial reference (or actually to its clone). */
     mutable OGRSpatialReference*         mOrigSpatialReference;

     /*! \brief The coordinate transformer used for converting latlon coordinates to the original coordinates. */
     mutable OGRCoordinateTransformation* mCoordinateTranformation_latlon2orig;

     /*! \brief The coordinate transformer used for converting original coordinates to the latlon coordinates. */
     mutable OGRCoordinateTransformation* mCoordinateTranformation_orig2latlon;
};

typedef GridDefinition* GridDef_ptr;
typedef std::shared_ptr<GridDefinition> GridDefinition_sptr;
typedef std::vector<GridDef_ptr> GridDef_pvec;
typedef std::map<uint,GridDef_ptr> GridDefinition_pmap;
typedef std::map<std::string,GridDef_ptr> GridDef_map;


}  // namespace GRID
}  // namespace SmartMet
