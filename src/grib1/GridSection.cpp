#include "GridSection.h"
#include "Message.h"
#include "../identification/GridDef.h"
#include "../common/Dimensions.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"
#include "../common/GeneralDefinitions.h"

#include "../grib1/implementation/LatLonImpl.h"
#include "../grib1/implementation/MercatorImpl.h"
#include "../grib1/implementation/LambertConformalImpl.h"
#include "../grib1/implementation/GaussianImpl.h"
#include "../grib1/implementation/PolarStereographicImpl.h"
#include "../grib1/implementation/AlbersImpl.h"
#include "../grib1/implementation/RotatedLatLonImpl.h"
#include "../grib1/implementation/ObliqueLambertConformalImpl.h"
#include "../grib1/implementation/RotatedGaussianImpl.h"
#include "../grib1/implementation/StretchedLatLonImpl.h"
#include "../grib1/implementation/StretchedGaussianImpl.h"
#include "../grib1/implementation/StretchedRotatedLatLonImpl.h"
#include "../grib1/implementation/StretchedRotatedGaussianImpl.h"
#include "../grib1/implementation/SphericalHarmonicImpl.h"
#include "../grib1/implementation/RotatedSphericalHarmonicImpl.h"
#include "../grib1/implementation/StretchedSphericalHarmonicImpl.h"
#include "../grib1/implementation/StretchedRotatedSphericalHarmonicImpl.h"
#include "../grib1/implementation/SpaceViewImpl.h"


namespace SmartMet
{
namespace GRIB1
{



/*! \brief The constructor of the class. */

GridSection::GridSection()
{
  try
  {
    mMessage = nullptr;
    mFilePosition = 0;
    mNumberOfPoints = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The copy constructor of the class. */

GridSection::GridSection(const GridSection& other)
:GRID::MessageSection(other)
{
  try
  {
    mMessage = nullptr;
    mFilePosition = other.mFilePosition;
    mSectionLength = other.mSectionLength;
    mNumberOfVerticalCoordinateValues = other.mNumberOfVerticalCoordinateValues;
    mPvlLocation = other.mPvlLocation;
    mDataRepresentationType = other.mDataRepresentationType;
    mNumberOfPoints = other.mNumberOfPoints;
    mVerticalCoordinates = other.mVerticalCoordinates;

    if (other.mGridDefinition)
    {
      GridDefinition* def = other.mGridDefinition->createGridDefinition();
      mGridDefinition.reset(def);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The destructor of the class. */

GridSection::~GridSection()
{
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current section.
*/

void GridSection::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
  try
  {
    char name[300];

    sprintf(name,"%sgrid.numberOfVerticalCoordinateValues",prefix.c_str());
    attributeList.addAttribute(name,toString(mNumberOfVerticalCoordinateValues));

    sprintf(name,"%sgrid.pvlLocation",prefix.c_str());
    attributeList.addAttribute(name,toString(mPvlLocation));

    sprintf(name,"%sgrid.dataRepresentationType",prefix.c_str());
    attributeList.addAttribute(name,toString(mDataRepresentationType));

    sprintf(name,"%sgrid.dataRepresentationString",prefix.c_str());
    attributeList.addAttribute(name,getGridProjectionString());

    sprintf(name,"%sgrid.numberOfValues",prefix.c_str());
    attributeList.addAttribute(name,toString(getGridOriginalValueCount()));

    sprintf(name,"%sgrid.def.",prefix.c_str());
    if (mGridDefinition)
      mGridDefinition->getAttributeList(name,attributeList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    if (mGridDefinition)
      return mGridDefinition->getProperty(propertyId,value);

    switch (propertyId)
    {
      case Property::GridSection::NumberOfVerticalCoordinateValues:
        value = mNumberOfVerticalCoordinateValues;
        return true;

      case Property::GridSection::PvlLocation:
        value = mPvlLocation;
        return true;

      case Property::GridSection::DataRepresentationType:
        value = mDataRepresentationType;
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method is used for setting a (long long) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool GridSection::setProperty(uint propertyId,long long value)
{
  try
  {
    if (mGridDefinition)
      return mGridDefinition->setProperty(propertyId,value);

    switch (propertyId)
    {
      case Property::GridSection::NumberOfVerticalCoordinateValues:
        setNumberOfVerticalCoordinateValues(value);
        return true;

      case Property::GridSection::PvlLocation:
        setPvlLocation(value);
        return true;

      case Property::GridSection::DataRepresentationType:
        setDataRepresentationType(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method is used for setting a (double) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool GridSection::setProperty(uint propertyId,double value)
{
  try
  {
    if (mGridDefinition)
      return mGridDefinition->setProperty(propertyId,value);

    return setProperty(propertyId,C_INT64(value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridSection::setNumberOfVerticalCoordinateValues(long long value)
{
  try
  {
    mNumberOfVerticalCoordinateValues = static_cast<std::uint8_t>(value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridSection::setPvlLocation(long long value)
{
  try
  {
    mPvlLocation = static_cast<std::uint8_t>(value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridSection::setDataRepresentationType(long long value)
{
  try
  {
    if (!mGridDefinition)
    {
      mDataRepresentationType = static_cast<std::uint8_t>(value);
      auto gridDefinition = createGridDefinition(mDataRepresentationType);
      mGridDefinition.reset(gridDefinition);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method sets the pointer to the Message -object in which the current section
    object belongs to. This helps the object to reference information in other sections.

        \param message    The Message -object pointer.
*/

void GridSection::setMessagePtr(Message *message)
{
  try
  {
    mMessage = message;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GridSection::read(MemoryReader& memoryReader)
{
  try
  {
    mFilePosition = memoryReader.getGlobalReadPosition();

    auto rPos = memoryReader.getReadPosition();

    mSectionLength = memoryReader.read_uint24();
    memoryReader >> mNumberOfVerticalCoordinateValues;
    memoryReader >> mPvlLocation;
    memoryReader >> mDataRepresentationType;

    auto gridDefinition = createGridDefinition(mDataRepresentationType);
    mGridDefinition.reset(gridDefinition);
    gridDefinition->read(memoryReader);

    if (mNumberOfVerticalCoordinateValues > 0)
    {
      memoryReader.setReadPosition(rPos + mPvlLocation - 1);

      for (uint t=0; t<mNumberOfVerticalCoordinateValues; t++)
      {
        std::uint32_t v = 0;
        memoryReader >> v;
        mVerticalCoordinates.push_back(v);
      }
    }

    if (mNumberOfVerticalCoordinateValues == 0  &&  mPvlLocation != 255)
    {
      memoryReader.setReadPosition(rPos + mPvlLocation - 1);
      std::vector<std::uint32_t> rowPositions;
      rowPositions.push_back(0);

      auto d = getGridDimensions();
      uint rows = 0;
      if (d.getDimensions() == 2)
        rows = d.ny();

      for (uint y=0; y<rows; y++)
      {
        std::uint16_t len = 0;
        memoryReader >> len;
        //printf("ROW %u  %u\n",rows,len);
        mNumberOfPoints += len;
        rowPositions.push_back(mNumberOfPoints);
      }
    }

    memoryReader.setReadPosition(rPos + mSectionLength);

    try
    {
      if (mGridDefinition != nullptr)
        mGridDefinition->initSpatialReference();
    }
    catch (...)
    {
      SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
      exception.printError();
    }

    // Initializing the hash.

    getGridHash();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

void GridSection::write(DataWriter& dataWriter)
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"Grid definition is missing!");

    mSectionLength = 0;
    mFilePosition = dataWriter.getWritePosition();
    mDataRepresentationType = (std::uint8_t)mGridDefinition->getTemplateNumber();

    dataWriter.write_uint24(mSectionLength);
    dataWriter << mNumberOfVerticalCoordinateValues;
    dataWriter << mPvlLocation;
    dataWriter << mDataRepresentationType;

    mGridDefinition->write(dataWriter);

    if (mNumberOfVerticalCoordinateValues == mVerticalCoordinates.size())
    {
      for (uint t=0; t<mNumberOfVerticalCoordinateValues; t++)
      {
        dataWriter << mVerticalCoordinates[t];
      }
    }

    // Updata the section length

    ulonglong fPos = dataWriter.getWritePosition();
    mSectionLength = fPos - mFilePosition;
    dataWriter.setWritePosition(mFilePosition);
    dataWriter.write_uint24(mSectionLength);
    dataWriter.setWritePosition(fPos);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the section start position in the grib file.

        \return  The section's start position in the grib file.
*/

T::FilePosition GridSection::getFilePosition() const
{
  try
  {
    return mFilePosition;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the length of the section (in the grib file).

        \return  The length of the section expressed in bytes.
*/

std::uint32_t GridSection::getSectionLength() const
{
  try
  {
    return mSectionLength;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the name of the section. */

std::string GridSection::getSectionName() const
{
  try
  {
    return std::string("Grid");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the section number. */

std::uint8_t GridSection::getSectionNumber() const
{
  try
  {
    return (std::uint8_t)Message::SectionNumber::grid_section;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grid definition string (=> Projection name).

        \return   The projection used in the current grid (LatLon, Mercator, etc.)
*/

std::string GridSection::getGridProjectionString() const
{
  try
  {
    return Identification::gridDef.getGribTableValue(1,0,"6",mDataRepresentationType);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridPointByOriginalCoordinates(x,y,grid_i,grid_j);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns. In this case we can find out the grid
    dimensions by using the "getGridOriginalRowCount()" and "getGridOriginalColumnCount()"
    methods.

        \return   The grid dimensions.
*/

T::Dimensions GridSection::getGridDimensions() const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridDimensions();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the number of rows used in the original grid.

        \return   The number of the grid rows.
*/

std::size_t GridSection::getGridOriginalRowCount() const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridOriginalRowCount();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the number of columns used in the given original grid row.

        \param row    The grid row index (= j-position).
        \return       The number of columns in the given grid row.
*/

std::size_t GridSection::getGridOriginalColumnCount(std::size_t row) const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridOriginalColumnCount(row);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the maximum number of the columns used in the original grid.
    If the grid is irregular, this method returns the length of the longest row.

        \return   The maximum number of the columns in the grid.
*/

std::size_t GridSection::getGridOriginalColumnCount() const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridOriginalColumnCount();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the number of original values defined in the original grid.

        \return   The number of the values in the original grid.
*/

std::size_t GridSection::getGridOriginalValueCount() const
{
  try
  {
    if (mNumberOfPoints > 0)
      return mNumberOfPoints;

    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridOriginalValueCount();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridOriginalValueIndex(grid_i,grid_j);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grid latlon coordinates in the given grid point (= integer coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return        The method return true if the latlon values were succesfully returned.
*/

bool GridSection::getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridLatLonCoordinatesByGridPoint(grid_i,grid_j,lat,lon);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridLatLonCoordinatesByOriginalCoordinates(x,y,lat,lon);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridOriginalCoordinatesByGridPoint(grid_i,grid_j,x,y);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridOriginalCoordinatesByGridPosition(grid_i,grid_j,x,y);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridLatLonCoordinatesByGridPosition(grid_i,grid_j,lat,lon);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridOriginalCoordinatesByLatLonCoordinates(lat,lon,x,y);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grid geometry identifer.

        \return   The grid geometry identifier.
*/

T::GeometryId GridSection::getGridGeometryId() const
{
  try
  {
    if (mGridDefinition != nullptr)
      return mGridDefinition->getGridGeometryId();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
  try
  {
    if (mGridDefinition != nullptr)
      return mGridDefinition->getGridGeometryString();

    std::string str;
    return str;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
  try
  {
    if (mGridDefinition)
      return mGridDefinition->setGridGeometryId(geometryId);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

        \return   The grid coordinates.
*/

T::Coordinate_vec GridSection::getGridCoordinates() const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridCoordinates();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






/*! \brief The method returns all grid coordinates as a latlon coordinate vector. If the grid
    original coordiantes were not latlon coordinates then the original coordinates are converted
    to the latlon coordinates.

        \return   The grid latlon coordinates.
*/

T::Coordinate_vec GridSection::getGridLatLonCoordinates() const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridLatLonCoordinates();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grid hash value.

        \return   The grid hash value.
*/

T::Hash GridSection::getGridHash() const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridHash();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief This method can be used for finding out if the grid is global (i.e. goes
    around the globe).
    If the grid is global then we should be able to interpolate over the grid borders.

        \return   The method returns 'true' if the grid data is global. Otherwise
                  it returns 'false'.
*/

bool GridSection::isGridGlobal() const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->isGridGlobal();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief This method can be used for finding out the grid projection type (Mercator, LatLon, PolarStereographic, etc.).

        \return   The type of the grid projection (expressed as an enum value).
*/

T::GridProjection GridSection::getGridProjection() const
{
  try
  {
    if (mGridDefinition == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridProjection();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief This method can be used for finding out the grid layout.

        \return   The layout of the grid (expressed as an enum value).
*/

T::GridLayout GridSection::getGridLayout() const
{
  try
  {
    if (mGridDefinition == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to nullptr!");

    return mGridDefinition->getGridLayout();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the pointer to the spatial reference of the current grid.

        \return   The pointer to the spatial reference.
*/

T::SpatialRef* GridSection::getSpatialReference() const
{
  try
  {
    if (mGridDefinition != nullptr)
      return mGridDefinition->getSpatialReference();

    return nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






/*! \brief The method returns 'true' if the grid horizontal values are in the reverse order.

        \return   The method returns 'true' if the grid horizontal values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool GridSection::reverseXDirection() const
{
  try
  {
    if (mGridDefinition != nullptr)
      return mGridDefinition->reverseXDirection();

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns 'true' if the grid vertical values are in the reverse order.

        \return   The method returns 'true' if the grid vertical values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool GridSection::reverseYDirection() const
{
  try
  {
    if (mGridDefinition != nullptr)
      return mGridDefinition->reverseYDirection();

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief This method creates a GridDefinition object according to the given
    data representation type.

        \param dataRepresentationType   The type of the GridDefinition object.
        \return                         The pointer to the new GridDefinition object.
*/

GridDefinition* GridSection::createGridDefinition(std::uint8_t  dataRepresentationType)
{
  try
  {
    switch (dataRepresentationType)
    {
      case 0: // Latitude/longitude grid - equidistant cylindrical or Plate Carrée projection
        return new LatLonImpl();

      case 1: // Mercator projection
        return new MercatorImpl();

      case 2: // Gnomonic projection
        throw SmartMet::Spine::Exception(BCP,"'Gnomonic projection' not implemented!");

      case 3: // Lambert conformal, secant or tangent, conic or bi-polar, projection
        return new LambertConformalImpl();

      case 4: // Gaussian latitude/longitude grid
        return new GaussianImpl();

      case 5: // Polar stereographic projection
        return new PolarStereographicImpl();

      case 6: // Fmi Transverse Mercator (UTM) projection
        throw SmartMet::Spine::Exception(BCP,"'Fmi Transverse Mercator' not implemented!");

      case 7: // Simple polyconic projection
        throw SmartMet::Spine::Exception(BCP,"'Simple polyconic' not implemented!");

      case 8: // Albers equal-area, secant or tangent, conic or bi-polar, projection
        return new AlbersImpl();

      case 9: // Miller's cylindrical projection
        throw SmartMet::Spine::Exception(BCP,"'Miller's cylindrical' Not implemented!");

      case 10: // Rotated latitude/longitude grid
        return new RotatedLatLonImpl();

      case 13: // Oblique Lambert conformal, secant or tangent, conic or bi-polar, projection
        return new ObliqueLambertConformalImpl();

      case 14: // Rotated Gaussian latitude/longitude grid
        return new RotatedGaussianImpl();

      case 20: // Stretched latitude/longitude grid
        return new StretchedLatLonImpl();

      case 24: // Stretched Gaussian latitude/longitude grid
        return new StretchedGaussianImpl();

      case 30: // Stretched and rotated latitude/longitude grids
        return new StretchedRotatedLatLonImpl();

      case 34: // Stretched and rotated Gaussian latitude/longitude grids
        return new StretchedRotatedGaussianImpl();

      case 50: // Spherical harmonic coefficients
        return new SphericalHarmonicImpl();

      case 60: // Rotated spherical harmonic coefficients
        return new RotatedSphericalHarmonicImpl();

      case 70: // Stretched spherical harmonics
        return new StretchedSphericalHarmonicImpl();

      case 80: // Stretched and rotated spherical harmonic coefficients
        return new StretchedRotatedSphericalHarmonicImpl();

      case 90: // Space view, perspective orthographic
        return new SpaceViewImpl();

      default:
        throw SmartMet::Spine::Exception(BCP,"Unsupported grid definition!");
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    stream << space(level) << "SECTION ["<< toString(getSectionNumber()) << "] " << getSectionName() << "\n";
    stream << space(level) << "- filePosition                     = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- sectionLength                    = " << toString(mSectionLength) << "\n";
    stream << space(level) << "- numberOfVerticalCoordinateValues = " << toString(mNumberOfVerticalCoordinateValues) << "\n";
    stream << space(level) << "- pvlLocation                      = " << toString(mPvlLocation) << "\n";
    stream << space(level) << "- dataRepresentationType           = " << toString(mDataRepresentationType) << "\n";
    stream << space(level) << "- dataRepresentationString         = " << getGridProjectionString() << "\n";
    stream << space(level) << "- numberOfValues                   = " << toString(getGridOriginalValueCount()) << "\n";

    if (mGridDefinition)
      mGridDefinition->print(stream,level+1,optionFlags);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet
