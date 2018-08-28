#pragma once

#include "GridDefinition.h"
#include "../common/DataWriter.h"
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

    std::uint8_t          getNumberOfSection() const;
    T::UInt8_opt          getSourceOfGridDefinition() const;
    std::uint32_t         getNumberOfGridPoints() const;
    std::uint8_t          getNumberOfOctetsForNumberOfPoints() const;
    std::uint8_t          getInterpretationOfNumberOfPoints() const;

    T::Coordinate_vec     getGridCoordinates() const;
    T::Dimensions         getGridDimensions() const;
    T::UInt16_opt         getGridDefinitionTemplateNumber() const;
    T::GeometryId         getGridGeometryId() const;
    std::string           getGridGeometryString() const;
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
    T::SpatialRef*        getSpatialReference() const;
    bool                  isGridGlobal() const;
    bool                  reverseXDirection() const;
    bool                  reverseYDirection() const;

    void                  setNumberOfSection(std::uint8_t section);
    void                  setSourceOfGridDefinition(T::UInt8_opt source);
    void                  setNumberOfGridPoints(std::uint32_t gridPoints);
    void                  setNumberOfOctetsForNumberOfPoints(std::uint8_t octets);
    void                  setInterpretationOfNumberOfPoints(std::uint8_t points);
    void                  setGridDefinition(std::uint16_t templateNumber);

    void                  setGridGeometryId(T::GeometryId geometryId);
    void                  setMessagePtr(Message *message);

    bool                  setProperty(uint propertyId,long long value);

    void                  read(MemoryReader& memoryReader);
    void                  write(DataWriter& dataWriter);
    void                  print(std::ostream& stream,uint level,uint optionFlags) const;

  private:

    GridDefinition*       createGridDefinition(std::uint16_t templateNumber);

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
    GridDefinition_sptr   mGridDefinition;  // abstract interface to the grid definition

    /*! \brief  The optional list of numbers defining number of points. */
    std::vector<unsigned int> mDataPoints;

  public:

    class Template
    {
      public:
        const static std::uint16_t LatLon = 0;
        const static std::uint16_t RotatedLatLon = 1;
        const static std::uint16_t StretchedLatLon = 2;
        const static std::uint16_t StretchedRotatedLatLon = 3;
        const static std::uint16_t VariableResolutionLatLon = 4;
        const static std::uint16_t VariableResolutionRotatedLatLon = 5;
        const static std::uint16_t Mercator = 10;
        const static std::uint16_t TransverseMercator = 12;
        const static std::uint16_t PolarStereographic = 20;
        const static std::uint16_t LambertConformal = 30;
        const static std::uint16_t Albers = 31;
        const static std::uint16_t Gaussian = 40;
        const static std::uint16_t RotatedGaussian = 41;
        const static std::uint16_t StretchedGaussian = 42;
        const static std::uint16_t StretchedRotatedGaussian = 43;
        const static std::uint16_t SphericalHarmonic = 50;
        const static std::uint16_t RotatedSphericalHarmonic = 51;
        const static std::uint16_t StretchedSphericalHarmonic = 52;
        const static std::uint16_t StretchedRotatedSphericalHarmonic = 53;
        const static std::uint16_t SpaceView = 90;
        const static std::uint16_t Triangular = 100;
        const static std::uint16_t Unstructured = 101;
        const static std::uint16_t EquatorialAzimuthalEquidistant = 110;
        const static std::uint16_t AzimuthRange = 120;
        const static std::uint16_t IrregularLatLon = 130;
        const static std::uint16_t LambertAzimuthalEqualArea = 140;
        const static std::uint16_t CrossSection = 1000;
        const static std::uint16_t Hovmoller = 1100;
        const static std::uint16_t TimeSection = 1200;
    };
};

typedef std::shared_ptr<GridSection> GridSect_sptr;

}  // namespace GRIB2
}  // namespace SmartMet
