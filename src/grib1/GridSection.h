#pragma once

#include "GridDefinition.h"
#include "../common/Coordinate.h"
#include "../common/Dimensions.h"
#include "../grid/MessageSection.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"

#include <vector>

namespace SmartMet
{
namespace GRIB1
{

class Message;


// ====================================================================================
/*!
  \brief This class is used for accessing information that is  found from
  the Grid section in a GRIB file.

  When a message in a GRIB file is read, the Message class creates a new GridSection
  object and calls its read() method in order to read the section information into
  the object. After that the section information can be easily accessed through
  the current object.
*/
// ====================================================================================

/*
  --------------------------------------------------------------------------------------
  Section 2 - Grid description section
  --------------------------------------------------------------------------------------
  Octet   Contents
  --------------------------------------------------------------------------------------
  1-3     Length of section (octets)
  4       NV -- number of vertical coordinate parameters
  5       PV -- location (octet number) of the list of vertical coordinate parameters,
          if present; or PL -- location (octet number) of the list of numbers of points
          in each row (if no vertical coordinate parameters are present), if present;
          or 255 (all bits set to 1) if neither are present
  6       Data representation type (see Code table 6)
  7-32    Grid definition (according to data representation type - octet 6 above)
  33-42   Extensions of grid definition for rotation or stretching of the coordinate
          system or Lambert conformal projection or Mercator projection
  33-44   Extensions of grid definition for space view perspective projection
  33-52   Extensions of grid definition for stretched and rotated coordinate system
          PV  List of vertical coordinate parameters (length = NV x 4 octets); if
          present, then PL = 4NV + PV
          PL  List of numbers of points in each row (length = NROWS x 2 octets, where
          NROWS is the total number of rows defined within the grid description)
  --------------------------------------------------------------------------------------
*/


class GridSection : public GRID::MessageSection
{
  public:

                          GridSection();
                          GridSection(const GridSection& other);
    virtual               ~GridSection();

    // ### Common methods for all message sections

    void                  getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    T::FilePosition       getFilePosition() const;
    std::uint32_t         getSectionLength() const;
    std::string           getSectionName() const;
    std::uint8_t          getSectionNumber() const;

    // ### Section specific methods

    T::Dimensions         getGridDimensions() const;
    T::GeometryId         getGridGeometryId() const;
    std::string           getGridGeometryString() const;
    T::Hash               getGridHash() const;
    bool                  getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    T::Coordinate_svec    getGridLatLonCoordinates() const;
    bool                  getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    bool                  getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;
    bool                  getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    T::GridLayout         getGridLayout() const;
    bool                  getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    bool                  getGridMetricCellSize(double& width,double& height) const;
    bool                  getGridMetricSize(double& width,double& height) const;
    T::Coordinate_svec    getGridOriginalCoordinates() const;
    bool                  getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    bool                  getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool                  getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    std::size_t           getGridOriginalRowCount() const;
    std::size_t           getGridOriginalColumnCount(std::size_t row) const;
    std::size_t           getGridOriginalColumnCount() const;
    std::size_t           getGridOriginalValueCount() const;
    int                   getGridOriginalValueIndex(uint grid_i,uint grid_j) const;
    bool                  getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                  getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                  getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    T::GridProjection     getGridProjection() const;
    std::string           getGridProjectionString() const;
    std::size_t           getGridColumnCount() const;
    std::size_t           getGridRowCount() const;
    T::SpatialRef*        getSpatialReference() const;
    void                  initSpatialReference();
    bool                  isGridGlobal() const;
    bool                  isRelativeUV() const;
    bool                  reverseXDirection() const;
    bool                  reverseYDirection() const;

    void                  setGridGeometryId(T::GeometryId geometryId);
    void                  setMessagePtr(Message *message);

    bool                  getProperty(uint propertyId,long long& value);

    bool                  setProperty(uint propertyId,long long value);
    bool                  setProperty(uint propertyId,double value);

    void                  setNumberOfVerticalCoordinateValues(long long value);
    void                  setPvlLocation(long long value);
    void                  setDataRepresentationType(long long value);

    void                  read(MemoryReader& memoryReader);
    void                  write(DataWriter& dataWriter);
    void                  print(std::ostream& stream,uint level,uint optionFlags) const;

  private:

    GridDefinition*       createGridDefinition(std::uint8_t  dataRepresentationType);

    /*! \brief The pointer to the message object. */
    Message*              mMessage;

    /*! \brief The section start position in the file. */
    T::FilePosition       mFilePosition;

    /*! \brief The length of the section. */
    std::uint32_t         mSectionLength;

    /*! \brief The number of optional vertical coordinate values. */
    std::uint8_t          mNumberOfVerticalCoordinateValues;

    /*! \brief The location (octet number) of the list of vertical coordinate parameters, if present. */
    std::uint8_t          mPvlLocation;

    /*! \brief The data representation type (see Code table 6). */
    std::uint8_t          mDataRepresentationType;

    /*! \brief The pointer to the GridDefinition object. */
    GridDefinition_sptr   mGridDefinition;

    /*! \brief The number of the grid point (calculated when the grid is irregular). */
    std::uint32_t         mNumberOfPoints;

    std::vector<std::uint32_t>  mVerticalCoordinates;
};


typedef std::shared_ptr<GridSection> GridSect_sptr;

}  // namespace GRIB1
}  // namespace SmartMet
