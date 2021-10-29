#include "Message.h"
#include "QueryDataFile.h"
#include "../common/ShowFunction.h"
#include "../grid/PrintOptions.h"
#include "../grid/GridFile.h"
#include "../common/GeneralFunctions.h"
#include "../identification/GridDef.h"
#include <macgyver/StringConversion.h>
#include <macgyver/Exception.h>
#include <macgyver/FastMath.h>
#include <arpa/inet.h>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{
namespace QueryData
{

/*! \brief The constructor of the class. */

Message::Message()
{
  FUNCTION_TRACE
  try
  {
    mGridFile = nullptr;
    mMessageIndex = 0;
    mFileType = T::FileTypeValue::QueryData;
    mParameterIndex = 0;
    mLevelIndex = 0;
    mTimeIndex = 0;
    mColumns = 0;
    mRows = 0;
    mParameterLevel = 0;
    mForecastType = 0;
    mForecastNumber = 0;
    mForecastTimeT = 0;
    mIsRead = false;
    mQueryDataFile = nullptr;
    mGeometryId = 0;
    mGeometryDef = nullptr;
    mProjectionId = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

Message::Message(const Message& message)
:GRID::Message(message)
{
  FUNCTION_TRACE
  try
  {
    mGridFile = message.mGridFile;
    mProjectionId = message.mProjectionId;
    mColumns = message.mColumns;
    mRows = message.mRows;
    mParameterIndex = message.mParameterIndex;
    mLevelIndex = message.mLevelIndex;
    mTimeIndex = message.mTimeIndex;
    mParameterLevelId = message.mParameterLevelId;
    mParameterLevel = message.mParameterLevel;
    mGeometryId = message.mGeometryId;
    mForecastType = message.mForecastType;
    mForecastNumber = message.mForecastNumber;
    mForecastTime = message.mForecastTime;
    mForecastTimeT = message.mForecastTimeT;
    mQueryDataFile = message.mQueryDataFile;
    mGeometryDef = message.mGeometryDef;
    mIsRead = message.mIsRead;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





Message::Message(GRID::GridFile *gridFile,QueryDataFile *queryDataFile,uint messageIndex,QueryData::MessageInfo& messageInfo)
{
  FUNCTION_TRACE
  try
  {
    mGridFile = gridFile;
    mQueryDataFile = queryDataFile;
    mMessageIndex = messageIndex;
    mFileType = T::FileTypeValue::QueryData;
    mColumns = messageInfo.mColumns;
    mRows = messageInfo.mRows;
    mParameterIndex = messageInfo.mParameterIndex;
    mLevelIndex = messageInfo.mLevelIndex;
    mTimeIndex = messageInfo.mTimeIndex;
    mNewbaseParameterId = messageInfo.mNewbaseId;

    mFmiParameterLevelId = messageInfo.mParameterLevelId;
    mParameterLevel = messageInfo.mParameterLevel;
    mForecastType = 1;
    mForecastNumber = 0;
    mForecastTimeT = messageInfo.mForecastTimeT;
    mForecastTime = utcTimeFromTimeT(mForecastTimeT);

    mGeometryId = messageInfo.mGeometryId;
    mGeometryDef = nullptr;
    if (mGeometryId != 0)
      mGeometryDef = Identification::gridDef.getGrib2DefinitionByGeometryId(mGeometryId);

    mFmiParameterId = Identification::gridDef.getFmiParameterIdByNewbaseId(mNewbaseParameterId);
    if (mFmiParameterId == 0)
    {
      printf("**** MISSING DIRECT PARAMETER MAPPING: Newbase-Id (%d) => FMI-Id ****\n",mNewbaseParameterId);
      printf("(We cannot name the parameter with FMI-NAME if the mapping requires conversion)\n");
    }

    Identification::FmiParameterDef fmiDef;
    if (mFmiParameterId != 0  &&  Identification::gridDef.getFmiParameterDefById(mFmiParameterId,fmiDef))
    {
      mFmiParameterId = fmiDef.mFmiParameterId;
      mFmiParameterName = stringFactory.create(fmiDef.mParameterName);
      mFmiParameterUnits = stringFactory.create(fmiDef.mParameterUnits);
        //mFmiParameterLevelId = Identification::gridDef.getFmiLevelId(*this);

      Identification::NewbaseParameterDef nbDef;
      if (Identification::gridDef.getNewbaseParameterDefByFmiId(mFmiParameterId,nbDef))
      {
        mNewbaseParameterName = stringFactory.create(nbDef.mParameterName);
      }

      Identification::FmiParameterId_grib gribPm;
      if (Identification::gridDef.getGribParameterMappingByFmiId(mFmiParameterId,gribPm))
      {
        Identification::GribParameterDef gribDef;
        if (Identification::gridDef.getGribParameterDefById(gribPm.mGribParameterId,gribDef))
        {
          mGribParameterId  = gribDef.mGribParameterId;
          mGribParameterName = stringFactory.create(gribDef.mParameterName);
          mGribParameterUnits  = stringFactory.create(gribDef.mParameterUnits);
        }
      }
    }

    if (mGeometryDef)
      mProjectionId = mGeometryDef->getGridProjection();

    mIsRead = true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The destructor of the class. */

Message::~Message()
{
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current message.
*/

void Message::getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const
{
  FUNCTION_TRACE
  try
  {
    char name[300];
    if (mGeometryDef)
    {
      sprintf(name, "%sProjection.", prefix.c_str());
      return mGeometryDef->getAttributeList(name,attributeList);
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the file identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \return  The grid file identifier.
*/

uint Message::getFileId() const
{
  FUNCTION_TRACE
  try
  {
    return mGridFile->getFileId();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the producer identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \return  The grid producer identifier.
*/

uint Message::getProducerId() const
{
  FUNCTION_TRACE
  try
  {
    return mGridFile->getProducerId();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the generation identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \return  The grid generation identifier.
*/

uint Message::getGenerationId() const
{
  FUNCTION_TRACE
  try
  {
    return mGridFile->getGenerationId();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method can be used in order to find out the message's start
    position in the grib file.

        \return  The message's start position in the grib file.
*/

T::FilePosition Message::getFilePosition() const
{
  FUNCTION_TRACE
  try
  {
    return 0;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





T::FileType Message::getMessageType() const
{
  FUNCTION_TRACE
  try
  {
    return mFileType;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}






/*! \brief The method returns the reference time of the current grid. The forecast
    times are calculated from this.

        \return   The reference time of the current grid.
*/

T::TimeString Message::getReferenceTime() const
{
  {
    FUNCTION_TRACE
    try
    {
      return std::string("1970101T000000");
    }
    catch (...)
    {
      Fmi::Exception exception(BCP,"Operation failed!",nullptr);
      exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
      throw exception;
    }
  }
}





/*! \brief The method returns the forecast start time. This is calculated from the reference
    time and other time parameters (=> NormalProduct->parameter()).

        \return   The forecast start time of the current message.
*/

T::TimeString Message::getForecastTime() const
{
  FUNCTION_TRACE
  try
  {
    return mForecastTime;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the forecast start time. This is calculated from the reference
    time and other time parameters (=> NormalProduct->parameter()).

        \return   The forecast start time of the current message.
*/

time_t Message::getForecastTimeT() const
{
  FUNCTION_TRACE
  try
  {
    return mForecastTimeT;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}




/*! \brief The method returns the hash of the grid.

        \return   The hash of the grid.
*/

T::Hash Message::getGridHash() const
{
  FUNCTION_TRACE
  try
  {
    if (mGeometryDef)
      return mGeometryDef->getGridHash();

    return 0;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief This method can be used for finding out the grid projection type (Mercator, LatLon, PolarStereographic, etc.).

        \return   The type of the grid projection (expressed as an enum value).
*/

T::GridProjection Message::getGridProjection() const
{
  try
  {
    return mProjectionId;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

         \return   The grid coordinates.
*/

T::Coordinate_svec Message::getGridOriginalCoordinates() const
{
  FUNCTION_TRACE
  try
  {
    if (mGeometryDef)
      return mGeometryDef->getGridOriginalCoordinates();

    T::Coordinate_svec empty;
    return empty;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns all grid coordinates as a latlon coordinate vector. If the grid
    original coordiantes were not latlon coordinates then the original coordinates are converted
    to the latlon coordinates.

        \return   The grid latlon coordinates.
*/

T::Coordinate_svec Message::getGridLatLonCoordinates() const
{
  FUNCTION_TRACE
  try
  {
    if (mGeometryDef)
      return mGeometryDef->getGridLatLonCoordinates();

    T::Coordinate_svec empty;
    return empty;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns. In this case we can find out the grid
    dimensions by using the 'getGridRowCount' and 'getGridColumnCount' methods.

        \return   The grid dimensions.
*/

T::Dimensions Message::getGridDimensions() const
{
  FUNCTION_TRACE
  try
  {
    if (mGeometryDef)
      return mGeometryDef->getGridDimensions();

    T::Dimensions empty(0,0);
    return empty;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





std::size_t Message::getGridRowCount() const
{
  FUNCTION_TRACE
  try
  {
    if (mGeometryDef)
      return mGeometryDef->getGridRowCount();

    return 0;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the number of columns used in the given original grid row.

        \param row    The grid row index (= j-position).
        \return       The number of columns in the given grid row.
*/

std::size_t Message::getGridColumnCount() const
{
  FUNCTION_TRACE
  try
  {
    if (mGeometryDef)
      return mGeometryDef->getGridColumnCount();

    return 0;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the number of original values defined in the original grid.

        \return   The number of the values in the original grid.
*/

std::size_t Message::getGridOriginalValueCount() const
{
  FUNCTION_TRACE
  try
  {
    return mColumns*mRows;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
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

int Message::getGridOriginalValueIndex(uint grid_i,uint grid_j) const
{
  FUNCTION_TRACE
  try
  {
    return 0;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns 'true' if the grid is global (i.e. goes around the globe).
    If the grid is global then we should be able to interpolate over the grid borders.

      \return   The method returns 'true' if the grid data is global. Otherwise
                it returns 'false'
*/

bool Message::isGridGlobal() const
{
  FUNCTION_TRACE
  try
  {
    if (!mGeometryDef)
      return false;

    return mGeometryDef->isGridGlobal();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::isRelativeUV() const
{
  FUNCTION_TRACE
  try
  {
    if (!mGeometryDef)
      return false;

    return mGeometryDef->isRelativeUV();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid geometry identifer.

        \return   The grid geometry identifier.
*/

T::GeometryId Message::getGridGeometryId() const
{
  try
  {
    if (mGeometryDef)
      return mGeometryDef->getGridGeometryId();

    return mGeometryId;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





void Message::getGridCellAverageSize(double& width,double& height) const
{
  FUNCTION_TRACE
  try
  {
    if (mGeometryDef)
      mGeometryDef->getGridCellAverageSize(width,height);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridMetricCellSize(double& width,double& height) const
{
  FUNCTION_TRACE
  try
  {
    if (!mGeometryDef)
      return false;

    return mGeometryDef->getGridMetricCellSize(width,height);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridMetricSize(double& width,double& height) const
{
  FUNCTION_TRACE
  try
  {
    if (!mGeometryDef)
      return false;

    return mGeometryDef->getGridMetricSize(width,height);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight)
{
  FUNCTION_TRACE
  try
  {
    if (!mGeometryDef)
      return false;

    return mGeometryDef->getGridMetricArea(topLeft,topRight,bottomLeft,bottomRight);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight)
{
  FUNCTION_TRACE
  try
  {
    if (!mGeometryDef)
      return false;

    return mGeometryDef->getGridLatLonArea(topLeft,topRight,bottomLeft,bottomRight);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}




/*! \brief The method returns the grid geometry string. This string can be used for comparing
    geometries in different grid files. For example, is is possible that a GRIB 1 message has
    the same geometry string as a GRIB 2 message, which means that they have same geometries.
    This comparison is more reliable than the hash comparison.

        \return   The grid geometry string.
*/

std::string Message::getGridGeometryString() const
{
  FUNCTION_TRACE
  try
  {
    if (mGeometryDef)
      return getGridGeometryString();

    return "";
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
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

void Message::setGridGeometryId(T::GeometryId geometryId)
{
  FUNCTION_TRACE
  try
  {
    mGeometryId = geometryId;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method is used for setting grid values. The basic assumption is that
    all necessary attributes/parameters (like dimensions, packing method, etc)
    are already initialized before calling this function.

        \param values  The vector of grid values.
*/

void Message::setGridValues(T::ParamValue_vec& values)
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the grid latlon coordinates in the given grid point (= integer coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return   The method return true if the latlon values were succesfully returned.
*/

bool Message::getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const
{
  FUNCTION_TRACE
  try
  {
    if (!mGeometryDef)
      return false;

    return mGeometryDef->getGridLatLonCoordinatesByGridPoint(grid_i,grid_j,lat,lon);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid latlon coordinates in the given grid position (= double coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return        The method return true if the latlon values were succesfully returned.
*/

bool Message::getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const
{
  FUNCTION_TRACE
  try
  {
    if (!mGeometryDef)
      return false;

    return mGeometryDef->getGridOriginalCoordinatesByGridPosition(grid_i,grid_j,lat,lon);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid latlon coordinates according the grid original (projection) coordinates.

        \param x       The x-coordinate in the original projection.
        \param y       The y-coordinate in the original projection.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return        The method return true if the latlon values were succesfully returned.
*/

bool Message::getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const
{
  FUNCTION_TRACE
  try
  {
    if (!mGeometryDef)
      return false;

    return mGeometryDef->getGridLatLonCoordinatesByOriginalCoordinates(x,y,lat,lon);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid original (projection) coordinates in the given grid point (= integer coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param x       The x-coordinate in the original projection is returned in this parameter.
        \param y       The y-coordinate in the original projection is returned in this parameter.
        \return        The method return true if the original coordinates were succesfully returned.
*/

bool Message::getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    if (!mGeometryDef)
      return false;

    return mGeometryDef->getGridOriginalCoordinatesByGridPoint(grid_i,grid_j,x,y);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid original (projection) coordinates in the given grid position (= double coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param x       The x-coordinate in the original projection is returned in this parameter.
        \param y       The y-coordinate in the original projection is returned in this parameter.
        \return        The method return true if the original coordinates were succesfully returned.
*/

bool Message::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    if (!mGeometryDef)
      return false;

    return mGeometryDef->getGridOriginalCoordinatesByGridPosition(grid_i,grid_j,x,y);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid original (projection) coordinates by the given latlon position.

        \param lat  The latitude value.
        \param lon  The longitude value.
        \param x    The x-coordinate in the original projection is returned in this parameter.
        \param y    The y-coordinate in the original projection is returned in this parameter.
        \return     The method return true if the original coordinates were succesfully returned.
*/

bool Message::getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    if (!mGeometryDef)
      return false;

    return mGeometryDef->getGridOriginalCoordinatesByLatLonCoordinates(lat,lon,x,y);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





void Message::getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const
{
  FUNCTION_TRACE
  try
  {
    if (!mGeometryDef)
      return;

    mGeometryDef->getGridPointListByLatLonCoordinates(latlon,points);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
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

bool Message::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j)  const
{
  FUNCTION_TRACE
  try
  {
    return getGridPointByLatLonCoordinatesNoCache(lat,lon,grid_i,grid_j);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j)  const
{
  FUNCTION_TRACE
  try
  {
    if (!mGeometryDef)
      return false;

    return mGeometryDef->getGridPointByLatLonCoordinatesNoCache(lat,lon,grid_i,grid_j);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
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

bool Message::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  FUNCTION_TRACE
  try
  {
    if (!mGeometryDef)
      return false;

    return mGeometryDef->getGridPointByOriginalCoordinates(x,y,grid_i,grid_j);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}






/*! \brief The method returns a list of grid projection attributes.

        \param prefix         The prefix that is added in the front of each attribute name.
        \param attributeList  The projection attributes are returned in this parameter.
*/

void Message::getGridProjectionAttributes(const std::string& prefix,T::AttributeList& attributeList) const
{
  //throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the parameter level.
    Sometime the parameter level is "included" in the parameter definition. I.e. there
    might be different parameterId for "temperature-2m" and "temperature-10m". On the other
    hand, there might be only one parameterId for "temperature" but several levels (2m, 10m, etc.).
    So, the same data can be defined in multiple ways.

         \return   The parameter level.
*/

T::ParamLevel Message::getGridParameterLevel() const
{
  FUNCTION_TRACE
  try
  {
    return mParameterLevel;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the parameter level id.

         \return   The parameter level type (= enum value).
*/


T::ParamLevelId Message::getGridParameterLevelId() const
{
  FUNCTION_TRACE
  try
  {
    return mFmiParameterLevelId;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the parameter level type string (define in Table 4.5).

        \return   The parameter level type (expressed in a string).
*/

/*
std::string Message::getGridParameterLevelIdString() const
{
  return std::string("");
  //throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}
*/




/*! \brief The method returns the grid value in the given (exact) point.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The parameter value of the given grid point.
*/

/*
T::ParamValue Message::getGridValueByGridPoint(uint grid_i,uint grid_j) const
{
  FUNCTION_TRACE
  try
  {
    return getGridValueByOriginalGridPoint(grid_i,grid_j);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}
*/




/*! \brief The method returns the grid value in the given grid point.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The parameter value of the given grid point.
*/

T::ParamValue Message::getGridValueByGridPoint(uint grid_i,uint grid_j) const
{
  FUNCTION_TRACE
  try
  {
    return mQueryDataFile->getGridValue(mParameterIndex,mLevelIndex,mTimeIndex,grid_i,grid_j);
#if 0
    //printf("  ** getGridValueByOriginalGridPoint %u,%u\n",grid_i,grid_j);

    if (grid_i >= mColumns)
      grid_i = grid_i % mColumns;

    if (grid_i >= mColumns || grid_j >= mRows)
      return ParamValueMissing;

    int typeSize[] = {0,1,1,2,4,4,8};

    ulonglong idx = (grid_j*mColumnMultiplier+grid_i*mRowMultiplier)*typeSize[mDataType];
    if (idx >= (mMessageSize + typeSize[mDataType]))
      return ParamValueMissing;

    switch (mDataType)
    {
      case 1:  // byte
      {
        uchar *v = (uchar*)(mDataStartPtr + idx);
        if ((T::ParamValue)(*v) == mMissingValue)
          return ParamValueMissing;

        return mScaleFactor*(T::ParamValue)(*v) + mBaseValue;
      }
      break;

      case 2:  // char
      {
        char *v = (char*)(mDataStartPtr + idx);
        if ((T::ParamValue)(*v) == mMissingValue)
          return ParamValueMissing;

        return mScaleFactor*(T::ParamValue)(*v) + mBaseValue;
      }
      break;

      case 3:  // short
      {
        short *v = (short*)(mDataStartPtr + idx);
        short val = ntohs(*v);
        if ((T::ParamValue)val == mMissingValue)
          return ParamValueMissing;

        return mScaleFactor*(T::ParamValue)val + mBaseValue;
      }
      break;

      case 4:  // int
      {
        int *v = (int*)(mDataStartPtr + idx);
        int val = ntohl(*v);
        if ((T::ParamValue)val == mMissingValue)
          return ParamValueMissing;

        return mScaleFactor*(T::ParamValue)val + mBaseValue;
      }
      break;

      case 5:  // float
      {
        int *v = (int*)(mDataStartPtr + idx);
        int vv = ntohl(*v);
        float *val = (float*)&vv;
        if ((T::ParamValue)(*val) == mMissingValue)
          return ParamValueMissing;

        return mScaleFactor*(T::ParamValue)(*val) + mBaseValue;
      }
      break;

      case 6:  // double
      {
        long long *v = (long long*)(mDataStartPtr + idx);
        long long vv = ntohll(*v);
        double *val = (double*)&vv;
        if ((T::ParamValue)(*val) == mMissingValue)
          return ParamValueMissing;

        return mScaleFactor*(T::ParamValue)(*val) + mBaseValue;
      }
      break;
    }
#endif
    return ParamValueMissing;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    exception.addParameter("Grid_i",Fmi::to_string(grid_i));
    exception.addParameter("Grid_j",Fmi::to_string(grid_j));
    throw exception;
  }
}





/*! \brief The method returns the minimum and maximum value used in the current grid.
    This functionality might help to visualize the grid data.

        \param minValue   The returned minimum parameter value in the grid.
        \param maxValue   The returned maximum parameter value in the grid.
*/

void Message::getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const
{
  try
  {
    minValue = 1000000000;
    maxValue = -1000000000;

    for (uint y=0; y<mRows; y++)
    {
      for (uint x=0; x<mColumns; x++)
      {
        T::ParamValue val = getGridValueByGridPoint(x,y);
        if (val != ParamValueMissing)
        {
          if (val < minValue)
            minValue = val;

          if (val > maxValue)
            maxValue = val;
        }
      }
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns all grid data values (also missing values) as the grid
    would be regular. In the case of an irregular grid, the grid rows are filled so that
    the grid looks like a regular grid.

        \param values   The returned grid values.
*/

void Message::getGridValueVector(T::ParamValue_vec& values) const
{
  try
  {
    getGridOriginalValueVector(values);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the original grid data values.
    If the grid is regular then the 'getGridValueVector()' method returns the same
    result as this method. However, if the grid is irregular then the grid rows
    might contain different number of columns. In this case the data should be
    processed row-by-row and the 'getGridColumnCount()' method should be
    used in order to find out the number of the columns used in each row. Also
    the 'getGridOriginalValueIndex()' method can be used in order to locate values
    in the returned vector.

        \param values   The returned grid values (original).
*/

void Message::getGridOriginalValueVector(T::ParamValue_vec& values) const
{
  try
  {
    for (uint y=0; y<mRows; y++)
    {
      for (uint x=0; x<mColumns; x++)
      {
        T::ParamValue val = getGridValueByGridPoint(x,y);
        values.push_back(val);
      }
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void Message::initSpatialReference()
{
  // throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the pointer to the spatial reference of the current grid.

        \return   The pointer to the spatial reference.
*/

T::SpatialRef* Message::getSpatialReference() const
{
  try
  {
    if (!mGeometryDef)
      return nullptr;

    return mGeometryDef->getSpatialReference();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the WKT (Well-Known-Text) of the current grid.

        \return   The WKT of the current grid.
*/

std::string Message::getWKT() const
{
  try
  {
    if (!mGeometryDef)
      return "";

    return mGeometryDef->getWKT();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





std::string Message::getProj4() const
{
  try
  {
    if (!mGeometryDef)
      return "";

    return mGeometryDef->getProj4();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns 'true' if the grid horizontal values are in the reverse order.

        \return   The method returns 'true' if the grid horizontal values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool Message::reverseXDirection() const
{
  try
  {
    if (!mGeometryDef)
      return false;

    return mGeometryDef->reverseXDirection();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns 'true' if the grid vertical values are in the reverse order.

        \return   The method returns 'true' if the grid vertical values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool Message::reverseYDirection() const
{
  try
  {
    if (!mGeometryDef)
      return false;

    return mGeometryDef->reverseYDirection();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the forecast type of the current grid.

        \return   The forecast type.
*/

short Message::getForecastType() const
{
  try
  {
    return mForecastType;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the forecast number of the current grid.

        \return   The forecast number.
*/

short Message::getForecastNumber() const
{
  try
  {
    return mForecastNumber;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





void Message::lockData()
{
  //throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





void Message::unlockData()
{
  //throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::isRead()
{
  try
  {
    return mIsRead;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





void Message::read()
{
  FUNCTION_TRACE
  try
  {
    /*
    if (mIsRead)
      return;

    if (mGridFilePtr == nullptr)
    {
      Fmi::Exception exception(BCP,"No pointer to the grib file!");
      throw exception;
    }

    long long s = mGridFilePtr->getSize();

    mDataStartPtr = (uchar*)mGridFilePtr->getMemoryPtr();
    mDataEndPtr = mDataStartPtr + s;

    MemoryReader memoryReader(mDataStartPtr,mDataEndPtr);
    memoryReader.setReadPosition(0);
    read(memoryReader);
    */
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Message read failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void Message::read(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    exception.addParameter("Message start position",uint64_toHex(memoryReader.getStartPtr()-memoryReader.getParentPtr()));
    throw exception;
  }
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

void Message::write(DataWriter& dataWriter)
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void Message::print(std::ostream& stream,uint level,uint optionFlags) const
{
  FUNCTION_TRACE
  try
  {
    stream << "\n" << space(level) << "########## MESSAGE [" << mMessageIndex << "] ##########\n\n";
    //stream << space(level) << "- filePosition           = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- fileType               = " << toString(mFileType) << "\n";
    //stream << space(level) << "- messageSize            = " << toString(mMessageSize) << " (" << uint64_toHex(mMessageSize) << ")\n";
    stream << space(level) << "- columns                = " << toString(mColumns) << "\n";
    stream << space(level) << "- rows                   = " << toString(mRows) << "\n";
    //stream << space(level) << "- dataType               = " << toString(mDataType) << "\n";
    //stream << space(level) << "- scaleFactor            = " << std::to_string(mScaleFactor) << "\n";
    stream << space(level) << "- gribParameterId        = " << toString(mGribParameterId) << "\n";
    stream << space(level) << "- gribParameterName      = " << getGribParameterName() << "\n";
    //stream << space(level) << "- gribParameterUnits     = " << getGribParameterUnits() << "\n";
    stream << space(level) << "- parameterLevel         = " << toString(getGridParameterLevel()) << "\n";
    stream << space(level) << "- fmiParameterLevelId    = " << toString(mFmiParameterLevelId) << "\n";
    //stream << space(level) << "- grib1ParameterLevelId  = " << toString(mGrib1ParameterLevelId) << "\n";
    //stream << space(level) << "- grib2ParameterLevelId  = " << toString(mGrib2ParameterLevelId) << "\n";
    stream << space(level) << "- fmiParameterId         = " << toString(mFmiParameterId) << "\n";
    stream << space(level) << "- fmiParameterName       = " << getFmiParameterName() << "\n";
    stream << space(level) << "- fmiParameterUnits      = " << getFmiParameterUnits() << "\n";
    stream << space(level) << "- newbaseParameterId     = " << mNewbaseParameterId << "\n";
    stream << space(level) << "- newbaseParameterName   = " << getNewbaseParameterName() << "\n";
    stream << space(level) << "- netCdfParameterName    = " << getNetCdfParameterName() << "\n";
    stream << space(level) << "- parameterLevel         = " << toString(mParameterLevel) << "\n";
    //stream << space(level) << "- parameterUnits         = " << mParameterUnits << "\n";
    stream << space(level) << "- forecastType           = " << toString(mForecastType) << "\n";
    stream << space(level) << "- forecastNumber         = " << toString(mForecastNumber) << "\n";
    stream << space(level) << "- forecastTime           = " << getForecastTime() << "\n";
    stream << space(level) << "- forecastTimeT          = " << toString(mForecastTimeT) << "\n";
    //stream << space(level) << "- missingValue           = " << toString(mMissingValue) << "\n";
    //stream << space(level) << "- referenceTime          = " << getReferenceTime() << "\n";
    stream << space(level) << "- gridGeometryId         = " << getGridGeometryId() << "\n";
    stream << space(level) << "- gridHash               = " << getGridHash() << "\n";
    stream << space(level) << "- gridProjection         = " << T::get_gridProjectionString(getGridProjection()) << "\n";
    //stream << space(level) << "- gridLayout             = " << T::get_gridLayoutString(getGridLayout()) << "\n";
    stream << space(level) << "- WKT                    = " << getWKT() << "\n";


    mGeometryDef->print(stream,level,optionFlags);

    if (optionFlags &  GRID::PrintFlag::data)
    {
      T::ParamValue_vec values;
      getGridValueVector(values);

      stream << space(level+1) << "- data (from the grid corners):\n";

      char st[1000];
      uint ny = getGridRowCount();
      uint nx = getGridColumnCount();
      uint c = 0;
      std::size_t sz = values.size();

      for (uint y=0; y < ny; y++)
      {
        for (uint x=0; x < nx; x++)
        {
          if ((y < 3  ||  y >= ny-3)  &&  (x < 3  ||  x >= nx-3))
          {
            if (c < sz)
            {
              auto val = getGridValueByGridPoint(x,y);
              double xx = 0;
              double yy = 0;
              getGridOriginalCoordinatesByGridPoint(x,y,xx,yy);
              double xxx = 0;
              double yyy = 0;
              getGridLatLonCoordinatesByGridPoint(x,y,xxx,yyy);
              //auto val = values[c];
              if (val != ParamValueMissing)
                sprintf(st,"[%u,%u] [%f,%f] [%f,%f] %f",y+1,x+1,xx,yy,xxx,yyy,val);
              else
                sprintf(st,"[%u,%u] [%f,%f] NA",y+1,x+1,xx,yy);
              stream << space(level+3) << st << "\n";
            }
          }
          c++;
        }
      }
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}




}
}
