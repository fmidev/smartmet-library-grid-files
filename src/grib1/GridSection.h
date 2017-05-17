#pragma once

#include "grid/Coordinate.h"
#include "grid/Dimensions.h"
#include "grid/MessageSection.h"
#include "common/MemoryReader.h"
#include "GridDefinition.h"

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

                          GridSection(Message *message);
    virtual               ~GridSection();

    // ### Common methods for all message sections

    void                  getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    T::FilePosition       getFilePosition() const;
    std::uint32_t         getSectionLength() const;
    std::string           getSectionName() const;
    std::uint8_t          getSectionNumber() const;
    void                  print(std::ostream& stream,uint level,uint optionFlags) const;

    // ### Section specific methods

    T::GridProjection     getGridProjection() const;
    std::string           getGridProjectionString() const;
    T::Coordinate_vec     getGridCoordinates() const;
    T::Dimensions_opt     getGridDimensions() const;
    std::size_t           getGridOriginalRowCount() const;
    std::size_t           getGridOriginalColumnCount(std::size_t row) const;
    std::size_t           getGridOriginalColumnCount() const;
    std::size_t           getGridOriginalValueCount() const;
    int                   getGridOriginalValueIndex(uint grid_i,uint grid_j) const;
    bool                  getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                  getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    void                  getGridLatlonAreaCoordinates(double& firstLat,double& firstLon,double& lastLat,double& lastLon) const;
    void                  getGridOriginalAreaCoordinates(double& x1,double& y1,double& x2,double& y2) const;
    T::GridLayout         getGridLayout() const;
    T::Hash               getHash() const;
    T::SpatialReference*  getSpatialReference() const;
    bool                  isGridGlobal() const;
    void                  read(MemoryReader& memoryReader);

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
    GridDefinition_uptr   mGridDefinition;

    /*! \brief The type of the grid. */
    T::GridProjection     mGridProjection;

    /*! \brief The number of the grid point (calculated when the grid is irregular). */
    std::uint32_t         mNumberOfPoints;
};


typedef std::shared_ptr<GridSection> GridSection_sptr;

}  // namespace GRIB1
}  // namespace SmartMet
