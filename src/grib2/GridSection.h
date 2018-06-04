#pragma once

#include "GridDefinition.h"
#include "../common/MemoryReader.h"
#include "../grid/MessageSection.h"
#include "../common/Dimensions.h"
#include "../common/Coordinate.h"

#include <boost/optional.hpp>
#include <memory>
#include <vector>

namespace SmartMet
{
namespace GRIB2
{

class Message;


// ====================================================================================
/*!
  \brief This class is used for accessing information that is found from
  the Grid section in a GRIB file.

  When a message in a GRIB file is read, the Message class creates
  a new GridSection object and calls its read() method in order to read
  the section information into the object. After that the section information
  can be easily accessed through the current object.
*/
// ====================================================================================


/*
  --------------------------------------------------------------------------------------
  SECTION 3 - GRID DEFINITION SECTION
  --------------------------------------------------------------------------------------
  Octet   Contents
  --------------------------------------------------------------------------------------
  1-4     Length of section in octets (nn)
  5       Number of section (3)
  6       Source of grid definition (see Code Table 3.0)
  7-10    Number of data points
  11      Number of octets for optional list of numbers defining number of points
  12      Interpretation of list of numbers defining number of points (see Code Table 3.11)
  13-14   Grid Definition Template Number (= N) (see Code Table 3.1)
  15-xx   Grid Definition Template (see Template 3.N, where N is the Grid Definition
          Template Number given in  octets 13-14)
  [xx+1]-nn Optional list of numbers defining number of points
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

    std::uint8_t          getNumberOfSection() const;
    T::UInt8_opt          getSourceOfGridDefinition() const;
    std::uint32_t         getNumberOfGridPoints() const;
    std::uint8_t          getNumberOfOctetsForNumberOfPoints() const;
    std::uint8_t          getInterpretationOfNumberOfPoints() const;

    T::Coordinate_vec     getGridCoordinates() const;
    T::Dimensions_opt     getGridDimensions() const;
    T::UInt16_opt         getGridDefinitionTemplateNumber() const;
    T::GeometryId         getGridGeometryId() const;
    T::Hash               getGridHash() const;
    T::Coordinate_vec     getGridLatLonCoordinates() const;
    bool                  getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    bool                  getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;
    bool                  getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    bool                  getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    bool                  getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool                  getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    std::size_t           getGridOriginalRowCount() const;
    std::size_t           getGridOriginalColumnCount() const;
    std::size_t           getGridOriginalColumnCount(std::size_t row) const;
    std::size_t           getGridOriginalValueCount() const;
    int                   getGridOriginalValueIndex(uint grid_i,uint grid_j) const;
    bool                  getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                  getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    T::GridLayout         getGridLayout() const;
    T::GridProjection     getGridProjection() const;
    std::string           getGridProjectionString() const;
    T::SpatialReference*  getSpatialReference() const;
    bool                  reverseXDirection() const;
    bool                  reverseYDirection() const;
    bool                  isGridGlobal() const;
    void                  read(MemoryReader& memoryReader);
    void                  setGridGeometryId(T::GeometryId geometryId);

  private:

    GridDefinition*       createGridDefinition(T::UInt16_opt number);

    /*! \brief The pointer to the message object. */
    Message*              mMessage;

    /*! \brief The section start position in the file. */
    T::FilePosition       mFilePosition;

    /*! \brief The length of the section. */
    T::UInt32_opt         mSectionLength;

    /*! \brief The section number. */
    T::UInt8_opt          mNumberOfSection;

    /*! \brief The source of the grid definition (see Code Table 3.0). */
    T::UInt8_opt          mSourceOfGridDefinition;

    /*! \brief The number of grid points. */
    T::UInt32_opt         mNumberOfGridPoints;

    /*! \brief The Number of octets for optional list of numbers defining number of points. */
    T::UInt8_opt          mNumberOfOctetsForNumberOfPoints;

    /*! \brief The Interpretation of list of numbers defining number of points (see Code Table 3.11) */
    T::UInt8_opt          mInterpretationOfNumberOfPoints;

    /*! \brief The grid definition template number (see Code Table 3.1). */
    T::UInt16_opt         mGridDefinitionTemplateNumber;

    /*! \brief The pointer to the GridDefinition object. */
    GridDefinition_uptr   mGridDefinition;  // abstract interface to the grid definition

    /*! \brief  The optional list of numbers defining number of points. */
    std::vector<unsigned int> mDataPoints;
};

typedef std::shared_ptr<GridSection> GridSection_sptr;

}  // namespace GRIB2
}  // namespace SmartMet
