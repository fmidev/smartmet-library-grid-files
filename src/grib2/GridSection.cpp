#include "GridSection.h"
#include "Message.h"
#include "../identification/GridDef.h"
#include "../common/Dimensions.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"
#include "../common/ShowFunction.h"

#include "implementation/LatLonImpl.h"                             //  "3.0"
#include "implementation/RotatedLatLonImpl.h"                      //  "3.1"
#include "implementation/StretchedLatLonImpl.h"                    //  "3.2"
#include "implementation/StretchedRotatedLatLonImpl.h"             //  "3.3"
#include "implementation/VariableResolutionLatLonImpl.h"           //  "3.4"
#include "implementation/VariableResolutionRotatedLatLonImpl.h"    //  "3.5"
#include "implementation/MercatorImpl.h"                           //  "3.10"
#include "implementation/TransverseMercatorImpl.h"                 //  "3.12"
#include "implementation/PolarStereographicImpl.h"                 //  "3.20"
#include "implementation/LambertConformalImpl.h"                   //  "3.30"
#include "implementation/AlbersImpl.h"                             //  "3.31"
#include "implementation/GaussianImpl.h"                           //  "3.40"
#include "implementation/RotatedGaussianImpl.h"                    //  "3.41"
#include "implementation/StretchedGaussianImpl.h"                  //  "3.42"
#include "implementation/StretchedRotatedGaussianImpl.h"           //  "3.43"
#include "implementation/SphericalHarmonicImpl.h"                  //  "3.50"
#include "implementation/RotatedSphericalHarmonicImpl.h"           //  "3.51"
#include "implementation/StretchedSphericalHarmonicImpl.h"         //  "3.52"
#include "implementation/StretchedRotatedSphericalHarmonicImpl.h"  //  "3.53"
#include "implementation/SpaceViewImpl.h"                          //  "3.90"
#include "implementation/TriangularImpl.h"                         //  "3.100"
#include "implementation/UnstructuredImpl.h"                       //  "3.101"
#include "implementation/EquatorialAzimuthalEquidistantImpl.h"     //  "3.110"
#include "implementation/AzimuthRangeImpl.h"                       //  "3.120"
#include "implementation/IrregularLatLonImpl.h"                    //  "3.130"
#include "implementation/LambertAzimuthalEqualAreaImpl.h"          //  "3.140"
#include "implementation/CrossSectionImpl.h"                       //  "3.1000"
#include "implementation/HovmollerImpl.h"                          //  "3.1100"
#include "implementation/TimeSectionImpl.h"                        //  "3.1200"

#include <iostream>
#include <macgyver/StringConversion.h>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF



namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

GridSection::GridSection()
{
  FUNCTION_TRACE
  try
  {
    mMessage = nullptr;
    mFilePosition = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

GridSection::GridSection(const GridSection& other)
:GRID::MessageSection(other)
{
  FUNCTION_TRACE
  try
  {
    mMessage = nullptr;
    mFilePosition = other.mFilePosition;
    mSectionLength = other.mSectionLength;
    mNumberOfSection = other.mNumberOfSection;
    mSourceOfGridDefinition = other.mSourceOfGridDefinition;
    mNumberOfGridPoints = other.mNumberOfGridPoints;
    mNumberOfOctetsForNumberOfPoints = other.mNumberOfOctetsForNumberOfPoints;
    mInterpretationOfNumberOfPoints = other.mInterpretationOfNumberOfPoints;
    mGridDefinitionTemplateNumber = other.mGridDefinitionTemplateNumber;
    mDataPoints = other.mDataPoints;

    if (other.mGridDefinition)
    {
      GridDefinition *def = other.mGridDefinition->createGridDefinition();
      mGridDefinition.reset(def);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

GridSection::~GridSection()
{
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current section.
*/

void GridSection::getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const
{
  FUNCTION_TRACE
  try
  {
    char name[300];

    sprintf(name,"%sgrid.sourceOfGridDefinition",prefix.c_str());
    attributeList.addAttribute(name,toString(getSourceOfGridDefinition()));

    sprintf(name,"%sgrid.numberOfGridPoints",prefix.c_str());
    attributeList.addAttribute(name,toString(getNumberOfGridPoints()));

    sprintf(name,"%sgrid.numberOfOctetsForNumberOfPoints",prefix.c_str());
    attributeList.addAttribute(name,toString(getNumberOfOctetsForNumberOfPoints()));

    sprintf(name,"%sgrid.interpretationOfNumberOfPoints",prefix.c_str());
    attributeList.addAttribute(name,toString(getInterpretationOfNumberOfPoints()));

    sprintf(name,"%sgrid.gridDefinitionTemplateNumber",prefix.c_str());
    attributeList.addAttribute(name,toString(getGridDefinitionTemplateNumber()));

    sprintf(name,"%sgrid.def.",prefix.c_str());
    if (mGridDefinition)
      mGridDefinition->getAttributeList(name,attributeList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the pointer to the Message -object in which the current section
    object belongs to. This helps the object to reference information in other sections.

        \param message    The Message -object pointer.
*/

void GridSection::setMessagePtr(Message *message)
{
  FUNCTION_TRACE
  try
  {
    mMessage = message;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for fetching a (long long ) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the requested property is returned in this parameter.
        \return            The method returns true if the value of the requested property was found.
*/

bool GridSection::getProperty(uint propertyId,long long& value)
{
  try
  {
    switch (propertyId)
    {
      case Property::GridSection::SourceOfGridDefinition:
        value = *mSourceOfGridDefinition;
        return true;

      case Property::GridSection::NumberOfGridPoints:
        value = *mNumberOfGridPoints;
        return true;

      case Property::GridSection::NumberOfOctetsForNumberOfPoints:
        value = *mNumberOfOctetsForNumberOfPoints;
        return true;

      case Property::GridSection::InterpretationOfNumberOfPoints:
        value = *mInterpretationOfNumberOfPoints;
        return true;

      case Property::GridSection::GridDefinitionTemplateNumber:
        value = *mGridDefinitionTemplateNumber;
        return true;
    }

    if (mGridDefinition)
      return mGridDefinition->getProperty(propertyId,value);

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridSection::getProperties(T::PropertySettingVec& properties)
{
  try
  {

    if (mSourceOfGridDefinition)
      properties.emplace_back((uint)Property::GridSection::SourceOfGridDefinition,*mSourceOfGridDefinition);

    if (mNumberOfGridPoints)
      properties.emplace_back((uint)Property::GridSection::NumberOfGridPoints,*mNumberOfGridPoints);

    if (mNumberOfOctetsForNumberOfPoints)
      properties.emplace_back((uint)Property::GridSection::NumberOfOctetsForNumberOfPoints,*mNumberOfOctetsForNumberOfPoints);

    if (mInterpretationOfNumberOfPoints)
      properties.emplace_back((uint)Property::GridSection::InterpretationOfNumberOfPoints,*mInterpretationOfNumberOfPoints);

    if (mGridDefinitionTemplateNumber)
      properties.emplace_back((uint)Property::GridSection::GridDefinitionTemplateNumber,*mGridDefinitionTemplateNumber);

    if (mGridDefinition)
      return mGridDefinition->getProperties(properties);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






/*! \brief The method is used for setting a (long long) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool GridSection::setProperty(uint propertyId,long long value)
{
  FUNCTION_TRACE
  try
  {
    switch (propertyId)
    {
      case Property::GridSection::SourceOfGridDefinition:
        setSourceOfGridDefinition(value);
        return true;

      case Property::GridSection::NumberOfGridPoints:
        setNumberOfGridPoints(value);
        return true;

      case Property::GridSection::NumberOfOctetsForNumberOfPoints:
        setNumberOfOctetsForNumberOfPoints(value);
        return true;

      case Property::GridSection::InterpretationOfNumberOfPoints:
        setInterpretationOfNumberOfPoints(value);
        return true;

      case Property::GridSection::GridDefinitionTemplateNumber:
        setGridDefinition((std::uint16_t)value);
        return true;
    }

    if (mGridDefinition)
      return mGridDefinition->setProperty(propertyId,value);

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GridSection::read(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  try
  {
    mFilePosition = memoryReader.getGlobalReadPosition();

    memoryReader >> mSectionLength;
    if (missing(mSectionLength))
    {
      Fmi::Exception exception(BCP,"Section length cannot be MISSING!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-4));
      throw exception;
    }

    memoryReader >> mNumberOfSection;
    memoryReader >> mSourceOfGridDefinition;

    memoryReader >> mNumberOfGridPoints;
    if (missing(mNumberOfGridPoints))
    {
      Fmi::Exception exception(BCP,"Number of grid points cannot be MISSING");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-4));
      throw exception;
    }

    memoryReader >> mNumberOfOctetsForNumberOfPoints;
    if (missing(mNumberOfOctetsForNumberOfPoints))
    {
      Fmi::Exception exception(BCP,"Number of octets for number of points cannot be MISSING");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    memoryReader >> mInterpretationOfNumberOfPoints;

    if (missing(mInterpretationOfNumberOfPoints))
    {
      // A missing value makes no sense, the value should be zero if there are no points
      Fmi::Exception exception(BCP,"Interpretation of number of points cannot be missing");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    auto rPos = memoryReader.getGlobalReadPosition();

    memoryReader >> mGridDefinitionTemplateNumber;

    try
    {
      if (mGridDefinitionTemplateNumber)
      {
        auto gridDefinition = createGridDefinition(*mGridDefinitionTemplateNumber);
        mGridDefinition.reset(gridDefinition);
        gridDefinition->read(memoryReader);
      }
    }
    catch (...)
    {
      Fmi::Exception exception(BCP,"Cannot create a grid definition!",nullptr);
      exception.addParameter("Read position",uint64_toHex(rPos));
      throw exception;
    }

    if (*mNumberOfOctetsForNumberOfPoints != 0)
    {
      Fmi::Exception exception(BCP,"GridSection does not support reading optional numbers yet!");
      throw exception;
      //      exception.printError();;

      // TODO: Read the datapoints
    }

    if (mGridDefinition)
    {
      auto geomId = getGridGeometryId();
      if (geomId == 0)
      {
        auto gs = getGridGeometryString();
        auto def = Identification::gridDef.getGrib2DefinitionByGeometryString(gs);
        if (def)
        {
          mGridDefinition->setGridGeometryId(def->getGridGeometryId());
          mGridDefinition->setEarthSemiMajor(def->getEarthSemiMajor());
          mGridDefinition->setEarthSemiMinor(def->getEarthSemiMinor());
        }
      }
      /*
      else
      {
        auto def = Identification::gridDef.getGrib2DefinitionByGeometryId(geomId);
        if (def)
        {
          mGridDefinition = def;
        }
      }
      */

      mGridDefinition->countHash();
      mGridDefinition->initSpatialReference();
    }

    getGridHash();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed failed!",nullptr);
  }
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

void GridSection::write(DataWriter& dataWriter)
{
  FUNCTION_TRACE
  try
  {
    mNumberOfOctetsForNumberOfPoints = 0;
    mInterpretationOfNumberOfPoints = 0;

    if (!mGridDefinition)
      throw Fmi::Exception(BCP,"Grid definition missing");

    mFilePosition = dataWriter.getWritePosition();

    mSectionLength = 0;
    mNumberOfSection = (std::uint8_t)Message::SectionNumber::grid_section;
    mGridDefinitionTemplateNumber = mGridDefinition->getTemplateNumber();

    dataWriter << mSectionLength;
    dataWriter << mNumberOfSection;
    dataWriter << mSourceOfGridDefinition;
    dataWriter << mNumberOfGridPoints;
    dataWriter << mNumberOfOctetsForNumberOfPoints;
    dataWriter << mInterpretationOfNumberOfPoints;
    dataWriter << mGridDefinitionTemplateNumber;

    mGridDefinition->write(dataWriter);


    // Updating the section length.

    ulonglong fPos = dataWriter.getWritePosition();
    mSectionLength = fPos - mFilePosition;
    dataWriter.setWritePosition(mFilePosition);
    dataWriter << mSectionLength;
    dataWriter.setWritePosition(fPos);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the section start position in the grib file.

        \return  The section's start position in the grib file.
*/

T::FilePosition GridSection::getFilePosition() const
{
  FUNCTION_TRACE
  try
  {
    return mFilePosition;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the length of the section (in the grib file).

         \return  The length of the section expressed in bytes.
*/

std::uint32_t GridSection::getSectionLength() const
{
  FUNCTION_TRACE
  try
  {
    if (mSectionLength)
      return *mSectionLength;

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the name of the section. */

std::string GridSection::getSectionName() const
{
  FUNCTION_TRACE
  try
  {
    return std::string("Grid");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the default section number. */

std::uint8_t GridSection::getSectionNumber() const
{
  FUNCTION_TRACE
  try
  {
    return (std::uint8_t)Message::SectionNumber::grid_section;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the section number that was read from the grib file. */

std::uint8_t GridSection::getNumberOfSection() const
{
  FUNCTION_TRACE
  try
  {
    if (mNumberOfSection)
      return *mNumberOfSection;

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the source of the grid definition (see Code Table 3.0). */

T::UInt8_opt GridSection::getSourceOfGridDefinition() const
{
  FUNCTION_TRACE
  try
  {
    return mSourceOfGridDefinition;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the number of the grid points.

      \return   The number of the grid points.
*/

std::uint32_t GridSection::getNumberOfGridPoints() const
{
  FUNCTION_TRACE
  try
  {
    if (mNumberOfGridPoints)
      return *mNumberOfGridPoints;

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the number of octets for an optional list of numbers defining number of points.

      \return   The number of octets for an optional list of numbers defining number of points.
*/

std::uint8_t GridSection::getNumberOfOctetsForNumberOfPoints() const
{
  FUNCTION_TRACE
  try
  {
    if (mNumberOfOctetsForNumberOfPoints)
      return *mNumberOfOctetsForNumberOfPoints;

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the interpretation of list of numbers defining number
    of points (see Code Table 3.11).

      \return   The interpretation of list of numbers defining number of points.
*/

std::uint8_t GridSection::getInterpretationOfNumberOfPoints() const
{
  FUNCTION_TRACE
  try
  {
    if (mInterpretationOfNumberOfPoints)
      return *mInterpretationOfNumberOfPoints;

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid definition template number (see Code Table 3.1).

       \return   The grid definition template number.
*/

T::UInt16_opt GridSection::getGridDefinitionTemplateNumber() const
{
  FUNCTION_TRACE
  try
  {
    return mGridDefinitionTemplateNumber;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns. In this case we can find out the grid
    dimensions by using the "getGridRowCount()" and "getGridColumnCount()"
    methods.

      \return   The grid dimensions.
*/

T::Dimensions GridSection::getGridDimensions() const
{
  FUNCTION_TRACE
  try
  {
    const auto noctets = getNumberOfOctetsForNumberOfPoints();
    const auto interpretation = getInterpretationOfNumberOfPoints();

    // We can handle only normal grids for which source==0

    if (!mGridDefinition)
      return {};

    // Cannot handle irregular grids. Note that if interpretation=3, there is a separate list
    // of latitudes and hence it might be possible that the grid is regular, not just using
    // any of the standard projections. TODO: Handle it if an example is found.
    if (noctets != 0 || interpretation)
      return {};

    // Unknown grid?
    if (!mGridDefinition)
      return {};

    return mGridDefinition->getGridDimensions();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid geometry identifer.

        \return   The grid geometry identifier.
*/

T::GeometryId GridSection::getGridGeometryId() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition)
      return mGridDefinition->getGridGeometryId();

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridSection::getGridCellAverageSize(double& width,double& height) const
{
  FUNCTION_TRACE
  try
  {
    width = 0;
    height = 0;

    if (mGridDefinition != nullptr)
      mGridDefinition->getGridCellAverageSize(width,height);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridSection::getGridMetricCellSize(double& width,double& height) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition)
      return mGridDefinition->getGridMetricCellSize(width,height);

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridSection::getGridMetricSize(double& width,double& height) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition)
      return mGridDefinition->getGridMetricSize(width,height);

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridSection::getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight)
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition)
      return mGridDefinition->getGridMetricArea(topLeft,topRight,bottomLeft,bottomRight);

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridSection::getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight)
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition)
      return mGridDefinition->getGridLatLonArea(topLeft,topRight,bottomLeft,bottomRight);

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns the grid geometry string. This string can be used for comparing
    geometries in different grid files. For example, is is possible that a GRIB 1 message has
    the same geometry string as a GRIB 2 message, which means that they have same geometries.
    This comparison is more reliable than the hash comparison.

        \return   The grid geometry string.
*/

std::string GridSection::getGridGeometryString() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition)
      return mGridDefinition->getGridGeometryString();

    std::string str;
    return str;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

       \return   The grid coordinates.
*/

T::Coordinate_svec GridSection::getGridOriginalCoordinates() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridOriginalCoordinates();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






/*! \brief The method returns all grid coordinates as a latlon coordinate vector. If the grid
    original coordiantes were not latlon coordinates then the original coordinates are converted
    to the latlon coordinates.

        \return   The grid latlon coordinates.
*/

T::Coordinate_svec GridSection::getGridLatLonCoordinates() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridLatLonCoordinates();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid latlon coordinates in the given grid point (= integer coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return   The method return true if the latlon values were succesfully returned.
*/

bool GridSection::getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridLatLonCoordinatesByGridPoint(grid_i,grid_j,lat,lon);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid latlon coordinates in the given grid position (= double coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return        The method return true if the latlon values were succesfully returned.
*/

bool GridSection::getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridLatLonCoordinatesByGridPosition(grid_i,grid_j,lat,lon);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid latlon coordinates according the grid original (projection) coordinates.

        \param x       The x-coordinate in the original projection.
        \param y       The y-coordinate in the original projection.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return        The method return true if the latlon values were succesfully returned.
*/

bool GridSection::getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridLatLonCoordinatesByOriginalCoordinates(x,y,lat,lon);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid original (projection) coordinates in the given grid point (= integer coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param x       The x-coordinate in the original projection is returned in this parameter.
        \param y       The y-coordinate in the original projection is returned in this parameter.
        \return        The method return true if the original coordinates were succesfully returned.
*/

bool GridSection::getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridOriginalCoordinatesByGridPoint(grid_i,grid_j,x,y);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid original (projection) coordinates in the given grid position (= double coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param x       The x-coordinate in the original projection is returned in this parameter.
        \param y       The y-coordinate in the original projection is returned in this parameter.
        \return        The method return true if the original coordinates were succesfully returned.
*/

bool GridSection::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridOriginalCoordinatesByGridPosition(grid_i,grid_j,x,y);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid original (projection) coordinates by the given latlon position.

        \param lat  The latitude value.
        \param lon  The longitude value.
        \param x    The x-coordinate in the original projection is returned in this parameter.
        \param y    The y-coordinate in the original projection is returned in this parameter.
        \return     The method return true if the original coordinates were succesfully returned.
*/

bool GridSection::getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridOriginalCoordinatesByLatLonCoordinates(lat,lon,x,y);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the hash value that was calculated over the grid
    attributes.

       \return   The hash value of the grid attributes.
*/

T::Hash GridSection::getGridHash() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition != nullptr)
      return mGridDefinition->getGridHash();

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief This method calculates the estimated grid position by using the latlon coordinates.
    The estimated grid position is returned in the 'grid_i' and 'grid_j' parameters.

        \param lat     The latitude.
        \param lon     The longitude.
        \param grid_i  The returned grid i-position.
        \param grid_j  The returned grid j-position.
        \return        Returns 'false' if the given coordinates are outside of the grid.
*/

bool GridSection::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridSection::getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const
{
  FUNCTION_TRACE
  try
  {
    if (!mGridDefinition)
      throw Fmi::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridPointListByLatLonCoordinates(latlon,points);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




bool GridSection::getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridPointByLatLonCoordinatesNoCache(lat,lon,grid_i,grid_j);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief This method calculates the estimated grid position by using the original coordinates.
    The estimated grid position is returned in the 'grid_i' and 'grid_j' parameters.

      \param x       The original x-coordinate.
      \param y       The original y-coordinate.
      \param grid_i  The returned grid i-position.
      \param grid_j  The returned grid j-position.
      \return        Returns 'false' if the given coordinates are outside of the grid.
*/

bool GridSection::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridPointByOriginalCoordinates(x,y,grid_i,grid_j);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief This method can be used for finding out the grid projection type (Mercator, LatLon, PolarStereographic, etc.).

        \return   The type of the grid projection (expressed as an enum value).
*/

T::GridProjection GridSection::getGridProjection() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridProjection();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the number of rows used in the original grid.

     \return   The number of the grid rows.
*/

std::size_t GridSection::getGridRowCount() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition != nullptr)
      return mGridDefinition->getGridRowCount();

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the number of columns used in the given original grid row.

      \return       The number of columns in the given grid row.
*/

std::size_t GridSection::getGridColumnCount() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition != nullptr)
      return mGridDefinition->getGridColumnCount();

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the number of original values defined in the original grid.

      \return   The number of the values in the original grid.
*/

std::size_t GridSection::getGridOriginalValueCount() const
{
  FUNCTION_TRACE
  try
  {
    auto d = getGridDimensions();
    if (d.getDimensions() == 2)
      return d.ny() * d.nx();

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the index of given grid position in the original grid data.
    In the case of irregular grid the grid rows might contain different number of
    columns. If the given grid position is outside of the grid data then the method
    returns -1. This is the case when the grid column (grid_i) is bigger than
    the length of the given grid row (grid_j), or if the given grid row (grid_j)
    is bigger than the actual number of grid rows.

      \param grid_i    The grid i-position.
      \param grid_j    The grid j-position.

      \return          The index of the original data position. If the position
                       is outside of the grid data then the method return -1.
*/

int GridSection::getGridOriginalValueIndex(uint grid_i,uint grid_j) const
{
  FUNCTION_TRACE
  try
  {
    auto d = getGridDimensions();
    if (d.getDimensions() == 2)
    {
      if (grid_j >= d.ny())
        return -1;

      if (grid_i >= d.nx() &&  !isGridGlobal())
        return -1;

      return (grid_j * d.nx() + (grid_i % d.nx()));
    }
    return -1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void GridSection::initSpatialReference()
{
  try
  {
    if (mGridDefinition != nullptr)
      mGridDefinition->initSpatialReference();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridSection::getWKT()
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition != nullptr)
      return mGridDefinition->getWKT();

    return std::string("");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridSection::getProj4()
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition != nullptr)
      return mGridDefinition->getProj4();

    return std::string("");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns the pointer to the spatial reference of the current grid.

        \return   The pointer to the spatial reference.
*/

T::SpatialRef* GridSection::getSpatialReference() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition != nullptr)
      return mGridDefinition->getSpatialReference();

    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns 'true' if the grid horizontal values are in the reverse order.

        \return   The method returns 'true' if the grid horizontal values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool GridSection::reverseXDirection() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition != nullptr)
      return mGridDefinition->reverseXDirection();

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns 'true' if the grid vertical values are in the reverse order.

        \return   The method returns 'true' if the grid vertical values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool GridSection::reverseYDirection() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition != nullptr)
      return mGridDefinition->reverseYDirection();

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






/*! \brief The method returns 'true' if the grid is global (i.e. goes around the globe).
    If the grid is global then we should be able to interpolate over the grid borders.

      \return   The method returns 'true' if the grid data is global. Otherwise
                it returns 'false'
*/

bool GridSection::isGridGlobal() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->isGridGlobal();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridSection::isRelativeUV() const
{
  try
  {
    if (!mGridDefinition)
      throw Fmi::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->isRelativeUV();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void GridSection::setNumberOfSection(std::uint8_t section)
{
  FUNCTION_TRACE
  try
  {
    mNumberOfSection = section;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridSection::setSourceOfGridDefinition(T::UInt8_opt source)
{
  FUNCTION_TRACE
  try
  {
    mSourceOfGridDefinition = source;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridSection::setNumberOfGridPoints(std::uint32_t gridPoints)
{
  FUNCTION_TRACE
  try
  {
    mNumberOfGridPoints = gridPoints;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridSection::setNumberOfOctetsForNumberOfPoints(std::uint8_t octets)
{
  FUNCTION_TRACE
  try
  {
    mNumberOfOctetsForNumberOfPoints = octets;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridSection::setInterpretationOfNumberOfPoints(std::uint8_t points)
{
  FUNCTION_TRACE
  try
  {
    mInterpretationOfNumberOfPoints = points;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method set the grid geometry identifer.

   This identifier can be used for identifying different geometries. Usually geometry identifiers are defined
   in a configuration file and when a grid file read the geometry is automatically identified. However, there might
   be cases that the geometry cannot be automatically identified (because it is not defined in the configuration file).
   It is also possible that we might want to use our own geometry identifiers and this method allows us to set it
   in place.

        \param   The grid geometry identifier.
*/

void GridSection::setGridGeometryId(T::GeometryId geometryId)
{
  FUNCTION_TRACE
  try
  {
    if (mGridDefinition)
      return mGridDefinition->setGridGeometryId(geometryId);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridSection::setGridDefinition(std::uint16_t templateNumber)
{
  try
  {
    GridDefinition *gridDefinition = GridSection::createGridDefinition(templateNumber);

    if (gridDefinition == nullptr)
      throw Fmi::Exception(BCP,"Grid definition creation failed!");

    mGridDefinitionTemplateNumber = templateNumber;
    mGridDefinition.reset(gridDefinition);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method create a GridDefinition object accorind to the given
    grid defintion template number.

      \return   The pointer to the created GridDefinition object.
*/

GridDefinition* GridSection::createGridDefinition(std::uint16_t templateNumber)
{
  FUNCTION_TRACE
  try
  {
    switch (templateNumber)
    {
      case 0:
        return new LatLonImpl();
      case 1:
        return new RotatedLatLonImpl();
      case 2:
        return new StretchedLatLonImpl();
      case 3:
        return new StretchedRotatedLatLonImpl();
      case 4:
        return new VariableResolutionLatLonImpl();
      case 5:
        return new VariableResolutionRotatedLatLonImpl();
      case 10:
        return new MercatorImpl();
      case 12:
        return new TransverseMercatorImpl();
      case 20:
        return new PolarStereographicImpl();
      case 30:
        return new LambertConformalImpl();
      case 31:
        return new AlbersImpl();
      case 40:
        return new GaussianImpl();
      case 41:
        return new RotatedGaussianImpl();
      case 42:
        return new StretchedGaussianImpl();
      case 43:
        return new StretchedRotatedGaussianImpl();
      case 50:
        return new SphericalHarmonicImpl();
      case 51:
        return new RotatedSphericalHarmonicImpl();
      case 52:
        return new StretchedSphericalHarmonicImpl();
      case 53:
        return new StretchedRotatedSphericalHarmonicImpl();
      case 90:
        return new SpaceViewImpl();
      case 100:
        return new TriangularImpl();
      case 101:
        return new UnstructuredImpl();
      case 110:
        return new EquatorialAzimuthalEquidistantImpl();
      case 120:
        return new AzimuthRangeImpl();
      case 130:
        return new IrregularLatLonImpl();
      case 140:
        return new LambertAzimuthalEqualAreaImpl();
      case 1000:
        return new CrossSectionImpl();
      case 1100:
        return new HovmollerImpl();
      case 1200:
        return new TimeSectionImpl();
      default:
        throw Fmi::Exception(BCP,"Unknown grid definition template number '" +
                                 Fmi::to_string(templateNumber) + "'!");
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Creation of a grid definition failed!",nullptr);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void GridSection::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    //std::uint8_t tablesVersion = mMessage->getTablesVersion();

    stream << space(level) << "SECTION ["<< toString(getSectionNumber()) << "] " << getSectionName() << "\n";
    stream << space(level) << "- filePosition                    = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- sectionLength                   = " << toString(mSectionLength) << "\n";
    stream << space(level) << "- numberOfSection                 = " << toString(mNumberOfSection) << "\n";
    stream << space(level) << "- sourceOfGridDefinition          = " << toString(getSourceOfGridDefinition()) << "\n";
    stream << space(level) << "- numberOfGridPoints              = " << toString(getNumberOfGridPoints()) << "\n";
    stream << space(level) << "- numberOfOctetsForNumberOfPoints = " << toString(getNumberOfOctetsForNumberOfPoints()) << "\n";
    stream << space(level) << "- interpretationOfNumberOfPoints  = " << toString(getInterpretationOfNumberOfPoints()) << "\n";
    stream << space(level) << "- gridDefinitionTemplateNumber    = " << toString(getGridDefinitionTemplateNumber()) << "\n";
    //stream << space(level) << "- gridDefinitionString            = " << getGridProjectionString() << "\n";

    // Dump the projection details: code table 3.1
    auto gridnumber = getGridDefinitionTemplateNumber();

    if (missing(gridnumber))
    {
      auto source = getSourceOfGridDefinition();
      if (missing(source))
        stream << space(level) << "!!! A grid definition does not apply to this product !!!\n";
      else if (*source == 1)
        stream << space(level) << "!!! Grid is predetermined by the originating center !!!\n";
      else
        stream << space(level) << "!!! Unknown Grid Definition Template Number !!!\n";
    }

    if (mGridDefinition)
      mGridDefinition->print(stream,level+1,optionFlags);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}  // namespace GRIB2
}  // namespace SmartMet
