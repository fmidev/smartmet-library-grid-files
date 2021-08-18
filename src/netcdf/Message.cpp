#include "Message.h"
#include "../common/ShowFunction.h"
#include "../grid/GridFile.h"
#include "../common/GeneralFunctions.h"
#include <macgyver/StringConversion.h>
#include <macgyver/Exception.h>
#include <macgyver/FastMath.h>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{
namespace NetCDF
{

/*! \brief The constructor of the class. */

Message::Message()
{
  FUNCTION_TRACE
  try
  {
    mFileMessageCount = 0;
    mFileVersion = 0;
    mFileRecordCount = 0;
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
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





Message::Message(GRID::GridFile *gridFile,uint messageIndex,GRID::MessageInfo& messageInfo)
{
  FUNCTION_TRACE
  try
  {
    FUNCTION_TRACE
    try
    {
      mGridFilePtr = gridFile;
      mMessageIndex = messageIndex;
      mFileMessageCount = 0;
      mFileVersion = 0;
      mFileRecordCount = 0;
      mTimeStepCount = 0;
      mLevelCount = 0;
      mWidth = 0;
      mHeight = 0;
      mMessageSize = messageInfo.mMessageSize;
      mFmiParameterId = messageInfo.mFmiParameterId;
      mFmiParameterName = messageInfo.mFmiParameterName;
      mFmiParameterLevelId = messageInfo.mFmiParameterLevelId;
      mParameterLevel = messageInfo.mParameterLevel;
      mForecastType = messageInfo.mForecastType;
      mForecastNumber = messageInfo.mForecastNumber;
      mGeometryId = messageInfo.mGeometryId;
      mGrib1ParameterLevelId = 0;
      mGrib2ParameterLevelId = 0;
      mIsRead = false;
      mFileType = T::FileTypeValue::NetCDF;
      mDataPosition = 0;
      mDataSize = 0;
      mDataStartPtr = nullptr;
      mDataEndPtr = nullptr;
      mForecastTimeT = 0;
    }
    catch (...)
    {
      throw Fmi::Exception(BCP,"Operation failed!",nullptr);
    }
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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the file identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \return  The grid file identifier.
*/

uint Message::getFileId() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the producer identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \return  The grid producer identifier.
*/

uint Message::getProducerId() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the generation identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \return  The grid generation identifier.
*/

uint Message::getGenerationId() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method can be used in order to find out the message's start
    position in the grib file.

        \return  The message's start position in the grib file.
*/

T::FilePosition Message::getFilePosition() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the reference time of the current grid. The forecast
    times are calculated from this.

        \return   The reference time of the current grid.
*/

T::TimeString Message::getReferenceTime() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the forecast start time. This is calculated from the reference
    time and other time parameters (=> NormalProduct->parameter()).

        \return   The forecast start time of the current message.
*/

T::TimeString Message::getForecastTime() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the forecast start time. This is calculated from the reference
    time and other time parameters (=> NormalProduct->parameter()).

        \return   The forecast start time of the current message.
*/

time_t Message::getForecastTimeT() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





uint Message::getFileMessageCount()
{
  return mFileMessageCount;
}




/*! \brief The method returns the hash of the grid.

        \return   The hash of the grid.
*/

T::Hash Message::getGridHash() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief This method can be used for finding out the grid projection type (Mercator, LatLon, PolarStereographic, etc.).

        \return   The type of the grid projection (expressed as an enum value).
*/

T::GridProjection Message::getGridProjection() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the type of the grid layout.

        \return   The layout of the grid (expressed as an enum value).
*/

T::GridLayout Message::getGridLayout() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the grid definition string (=> Projection name).

        \return   The projection used in the current grid (LatLon, Mercator, etc.)
*/

std::string Message::getGridProjectionString() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

         \return   The grid coordinates.
*/

T::Coordinate_svec Message::getGridOriginalCoordinates() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns all grid coordinates as a latlon coordinate vector. If the grid
    original coordiantes were not latlon coordinates then the original coordinates are converted
    to the latlon coordinates.

        \return   The grid latlon coordinates.
*/

T::Coordinate_svec Message::getGridLatLonCoordinates() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns. In this case we can find out the grid
    dimensions by using the 'getGridOriginalRowCount' and 'getGridOriginalColumnCount' methods.

        \return   The grid dimensions.
*/

T::Dimensions Message::getGridDimensions() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





std::size_t Message::getGridRowCount() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the number of columns used in the given original grid row.

        \param row    The grid row index (= j-position).
        \return       The number of columns in the given grid row.
*/

std::size_t Message::getGridColumnCount() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}




/*! \brief The method returns the number of rows used in the original grid.

       \return   The number of the grid rows.
*/

std::size_t Message::getGridOriginalRowCount() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the number of columns used in the given original grid row.

        \param row    The grid row index (= j-position).
        \return       The number of columns in the given grid row.
*/

std::size_t Message::getGridOriginalColumnCount(std::size_t row) const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the maximum number of the columns used in the original grid
    If the grid is irregular, this method returns the length of the longest row.

         \return   The maximum number of the columns in the grid.
*/

std::size_t Message::getGridOriginalColumnCount() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the number of original values defined in the original grid.

        \return   The number of the values in the original grid.
*/

std::size_t Message::getGridOriginalValueCount() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns 'true' if the grid is global (i.e. goes around the globe).
    If the grid is global then we should be able to interpolate over the grid borders.

      \return   The method returns 'true' if the grid data is global. Otherwise
                it returns 'false'
*/

bool Message::isGridGlobal() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::isRelativeUV() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the grid geometry identifer.

        \return   The grid geometry identifier.
*/

T::GeometryId Message::getGridGeometryId() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





void Message::getGridCellAverageSize(double& width,double& height) const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::getGridMetricCellSize(double& width,double& height) const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::getGridMetricSize(double& width,double& height) const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight)
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight)
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}




/*! \brief The method returns the grid geometry string. This string can be used for comparing
    geometries in different grid files. For example, is is possible that a GRIB 1 message has
    the same geometry string as a GRIB 2 message, which means that they have same geometries.
    This comparison is more reliable than the hash comparison.

        \return   The grid geometry string.
*/

std::string Message::getGridGeometryString() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





void Message::getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j)  const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}






/*! \brief The method returns a list of grid projection attributes.

        \param prefix         The prefix that is added in the front of each attribute name.
        \param attributeList  The projection attributes are returned in this parameter.
*/

void Message::getGridProjectionAttributes(const std::string& prefix,T::AttributeList& attributeList) const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the parameter level id.

         \return   The parameter level type (= enum value).
*/


T::ParamLevelId Message::getGridParameterLevelId() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the parameter level type string (define in Table 4.5).

        \return   The parameter level type (expressed in a string).
*/

std::string Message::getGridParameterLevelIdString() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the grid value in the given (exact) point.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The parameter value of the given grid point.
*/

T::ParamValue Message::getGridValueByGridPoint(uint grid_i,uint grid_j) const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the grid value in the given original grid point.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The parameter value of the given grid point.
*/

T::ParamValue Message::getGridValueByOriginalGridPoint(uint grid_i,uint grid_j) const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the minimum and maximum value used in the current grid.
    This functionality might help to visualize the grid data.

        \param minValue   The returned minimum parameter value in the grid.
        \param maxValue   The returned maximum parameter value in the grid.
*/

void Message::getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns all grid data values (also missing values) as the grid
    would be regular. In the case of an irregular grid, the grid rows are filled so that
    the grid looks like a regular grid.

        \param values   The returned grid values.
*/

void Message::getGridValueVector(T::ParamValue_vec& values) const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the original grid data values.
    If the grid is regular then the 'getGridValueVector()' method returns the same
    result as this method. However, if the grid is irregular then the grid rows
    might contain different number of columns. In this case the data should be
    processed row-by-row and the 'getGridOriginalColumnCount()' method should be
    used in order to find out the number of the columns used in each row. Also
    the 'getGridOriginalValueIndex()' method can be used in order to locate values
    in the returned vector.

        \param values   The returned grid values (original).
*/

void Message::getGridOriginalValueVector(T::ParamValue_vec& values) const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void Message::initSpatialReference()
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the pointer to the spatial reference of the current grid.

        \return   The pointer to the spatial reference.
*/

T::SpatialRef* Message::getSpatialReference() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the WKT (Well-Known-Text) of the current grid.

        \return   The WKT of the current grid.
*/

std::string Message::getWKT() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





std::string Message::getProj4() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns 'true' if the grid horizontal values are in the reverse order.

        \return   The method returns 'true' if the grid horizontal values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool Message::reverseXDirection() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns 'true' if the grid vertical values are in the reverse order.

        \return   The method returns 'true' if the grid vertical values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool Message::reverseYDirection() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the forecast type of the current grid.

        \return   The forecast type.
*/

short Message::getForecastType() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the forecast number of the current grid.

        \return   The forecast number.
*/

short Message::getForecastNumber() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





void Message::lockData()
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





void Message::unlockData()
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
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
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Message read failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





std::string utcTimeFromTimeTx(time_t t)
{
  try
  {
    struct tm tt;
    gmtime_r(&t, &tt);

    char buf[200];
    sprintf(buf,
            "%04d%02d%02dT%02d%02d%02d",
            tt.tm_year + 1900,
            tt.tm_mon + 1,
            tt.tm_mday,
            tt.tm_hour,
            tt.tm_min,
            tt.tm_sec);
    std::string str = buf;
    return str;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}


//731 217 pv
// -62135596800
// 719162



time_t utcTimeToTimeTx(const std::string& utcTime)
{
  try
  {
    if (utcTime.length() != 15)
      throw Fmi::Exception(BCP, "Invalid timestamp format (expected YYYYMMDDTHHMMSS)!");

    const char *str = utcTime.c_str();

    struct tm tt;
    tt.tm_year = getInt(str, 0, 4) - 1900; /* Year - 1900 */
    tt.tm_mon = getInt(str, 4, 2) - 1;     /* Month (0-11) */
    tt.tm_mday = getInt(str, 6, 2);        /* Day of the month (1-31) */
    tt.tm_hour = getInt(str, 9, 2);
    ; /* Hours (0-23) */
    tt.tm_min = getInt(str, 11, 2);
    ; /* Minutes (0-59) */
    tt.tm_sec = getInt(str, 13, 2);
    ;                 /* Seconds (0-60) */
    tt.tm_isdst = -1; /* Daylight saving time */

    return timegm(&tt);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP, "Operation failed!", nullptr);
    exception.addParameter("utcTime",utcTime);
    throw exception;
  }
}













void readAttribute(MemoryReader& memoryReader,std::string& attrName,std::vector<std::string>& attrValues)
{
  FUNCTION_TRACE
  try
  {
    uint nameLen = 0;
    memoryReader >> nameLen;
    if (nameLen > 0)
      nameLen = ((nameLen-1)/4 + 1) * 4;

    char name[nameLen+1];
    for (uint n = 0; n<nameLen; n++)
      name[n] = memoryReader.read_int8();

    name[nameLen] = '\0';
    attrName = name;


    uint attrType = 0;
    memoryReader >> attrType;

    uint attrCount = 0;
    memoryReader >> attrCount;


    switch (attrType)
    {
      case 1:  // byte
      {
        uchar val = 0;
        uint rCount = attrCount;
        if (rCount > 0)
          rCount = ((rCount-1)/4 + 1) * 4;

        for (uint a=0; a<rCount; a++)
        {
          memoryReader >> val;
          if (a < rCount)
            attrValues.push_back(std::to_string((uint)val));
        }
      }
      break;

      case 2:  // char
      {
        std::int8_t val = 0;
        uint rCount = attrCount;
        if (rCount > 0)
          rCount = ((rCount-1)/4 + 1) * 4;

        char str[rCount+1];
        for (uint a=0; a<rCount; a++)
        {
          memoryReader >> val;
          if (a < attrCount)
            str[a] = val;
        }
        str[attrCount] = '\0';
        attrValues.push_back(std::string(str));
      }
      break;

      case 3:  // short
      {
        short val = 0;
        uint rCount = attrCount;
        if (rCount > 0)
          rCount = ((rCount-1)/2 + 1) * 2;

        for (uint a=0; a<rCount; a++)
        {
          memoryReader >> val;
          if (a < attrCount)
            attrValues.push_back(std::to_string(val));
        }
      }
      break;

      case 4:  // int
      {
        int val = 0;
        for (uint a=0; a<attrCount; a++)
        {
          memoryReader >> val;
          attrValues.push_back(std::to_string(val));
        }
      }
      break;

      case 5:  // float
      {
        float val = 0;
        for (uint a=0; a<attrCount; a++)
        {
          memoryReader >> val;
          attrValues.push_back(std::to_string(val));
        }
      }
      break;

      case 6:  // double
      {
        double val = 0;
        for (uint a=0; a<attrCount; a++)
        {
          memoryReader >> val;
          attrValues.push_back(std::to_string(val));
        }
      }
      break;
    }
    //printf("  [%s][%0X][%u][%s]\n",name,attrType,attrCount,attrValue);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    //exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    //exception.addParameter("Message start position",uint64_toHex(memoryReader.getStartPtr()-memoryReader.getParentPtr()));
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
    int typeSize[] = {0,1,1,2,4,4,8};
    AutoThreadLock lock(&mThreadLock);

    if (mIsRead)
      return;

    std::map<std::string,std::vector<std::string>> propertyList;
    char tmp[1000];


    time_t startTime = utcTimeToTimeTx(std::string("00010101T000000"));
    time_t expectedTime = utcTimeToTimeTx(std::string("20030101T000000"));
    time_t tt = 63220420819;// 1041552000;
    auto st = utcTimeFromTimeTx(tt);
    auto st2 = utcTimeFromTimeTx(1073001600);

    printf("START %ld %ld %ld %s %s\n",startTime,expectedTime,expectedTime-startTime,st.c_str(),st2.c_str());


    time_t gt = getGregorianTimeT(1,1,1,0,0,0,17549208LL*3600LL);
    std::string ts = utcTimeFromTimeT(gt);
    printf("NEW TIME %s\n",ts.c_str());


    memoryReader.setReadPosition(0);

    mMessageSize = memoryReader.getDataSize();

    uchar type[5] = {0};
    memoryReader.read_data(type,3);
    if (strcmp((char*)type,"CDF") != 0)
    {
      Fmi::Exception exception(BCP,"Not a NetCDF file!");
      throw exception;
    }

    memoryReader >> mFileVersion;

    if (mFileVersion == 0 || mFileVersion > 2)
    {
      Fmi::Exception exception(BCP,"Invalid NetCDF version number!");
      exception.addParameter("Version",std::to_string(mFileVersion));
      throw exception;
    }

    // numrecs
    memoryReader >> mFileRecordCount;

    uint elemType = 0;
    uint elemCount = 0;

    // dim_list
    memoryReader >> elemType;
    memoryReader >> elemCount;

    if (elemCount > 0  &&  elemType != 0x0A)
    {
      Fmi::Exception exception(BCP,"Expected dimension indicator (0x0A)!");
      exception.addParameter("Indicator",std::to_string(elemType));
      throw exception;
    }

    //std::vector<std::pair<std::string,uint>> mDimensions;


    std::vector<std::string> dimNames;
    std::vector<std::string> dimLengths;

    printf("dimensions:\n");
    for (uint t=0; t<elemCount; t++)
    {
      uint nameLen = 0;
      memoryReader >> nameLen;
      if (nameLen > 0)
        nameLen = ((nameLen-1)/4 + 1) * 4;

      char name[nameLen+1];
      for (uint n = 0; n<nameLen; n++)
        name[n] = memoryReader.read_int8();

      name[nameLen] = '\0';

      // dim_length
      uint dimLen = 0;
      memoryReader >> dimLen;

      if (dimLen == 0)
        dimLen = mFileRecordCount;

      printf("  [%s][%u]\n",name,dimLen);
      dimNames.push_back(std::string(name));
      dimLengths.push_back(std::to_string(dimLen));

      std::vector<std::string> dimL;
      dimL.push_back(std::to_string(dimLen));
      sprintf(tmp,"%s.dimension.length",name);
      propertyList.insert(std::pair<std::string,std::vector<std::string>>(std::string(tmp),dimL));

      //mDimensions.push_back(std::pair<std::string,uint>(std::string((char*)name),dimLen));
    }

    propertyList.insert(std::pair<std::string,std::vector<std::string>>(std::string("dimension.name"),dimNames));


    propertyList.insert(std::pair<std::string,std::vector<std::string>>(std::string("dimension.length"),dimLengths));

    // attr_list
    memoryReader >> elemType;
    memoryReader >> elemCount;

    if (elemCount > 0  &&  elemType != 0x0C)
    {
      Fmi::Exception exception(BCP,"Expected attribute indicator (0x0C)!");
      exception.addParameter("Indicator",std::to_string(elemType));
      throw exception;
    }

    printf("attributes:\n");
    for (uint t=0; t<elemCount; t++)
    {
      std::string attrName;
      std::vector<std::string> attrValues;
      readAttribute(memoryReader,attrName,attrValues);

      printf("  [%s]",attrName.c_str());
      for (auto it = attrValues.begin(); it != attrValues.end(); ++it)
      {
        printf("[%s]",it->c_str());
      }
      printf("\n");
    }


    // var_list

    std::vector<std::string> variables;

    memoryReader >> elemType;
    memoryReader >> elemCount;

    if (elemCount > 0  &&  elemType != 0x0B)
    {
      Fmi::Exception exception(BCP,"Expected variable indicator (0x0B)!");
      exception.addParameter("Indicator",std::to_string(elemType));
      throw exception;
    }

    printf("variables:\n");
    for (uint t=0; t<elemCount; t++)
    {
      // dim[t]

      // name
      uint nameLen = 0;
      memoryReader >> nameLen;
      if (nameLen > 0)
        nameLen = ((nameLen-1)/4 + 1) * 4;

      char varName[nameLen+1];
      for (uint n = 0; n<nameLen; n++)
        varName[n] = memoryReader.read_int8();

      varName[nameLen] = '\0';

      variables.push_back(std::string(varName));

      uint dimCount = 0;
      memoryReader >> dimCount;

      printf(" VAR(%u) [%s][%u]\n",t,varName,dimCount);

      sprintf(tmp,"%s.dimension.index",varName);
      std::vector<std::string> dimList;

      //uint dimItems = 1;
      for (uint d=0; d<dimCount; d++)
      {
        uint dim = 0;
        memoryReader >> dim;
        dimList.push_back(std::to_string(dim));

        printf("  dimension [%u][%u]\n",d,dim);
/*
        if (dim < mDimensions.size())
          dimItems = dimItems * mDimensions[dim].second;
*/
      }
      propertyList.insert(std::pair<std::string,std::vector<std::string>>(std::string(tmp),dimList));


      // attr_list

      uint eType = 0;
      uint eCount = 0;

      memoryReader >> eType;
      memoryReader >> eCount;

      if (eCount > 0  &&  eType != 0x0C)
      {
        Fmi::Exception exception(BCP,"Expected attribute indicator (0x0C)!");
        exception.addParameter("Indicator",std::to_string(elemType));
        throw exception;
      }

      printf("** attributes:\n");
      for (uint t=0; t<eCount; t++)
      {
        std::string attrName;
        std::vector<std::string> attrValues;
        readAttribute(memoryReader,attrName,attrValues);


        sprintf(tmp,"%s.%s",varName,attrName.c_str());
        propertyList.insert(std::pair<std::string,std::vector<std::string>>(std::string(tmp),attrValues));


        printf("  [%s]",attrName.c_str());
        for (auto it = attrValues.begin(); it != attrValues.end(); ++it)
        {
          printf("[%s]",it->c_str());
        }
        printf("\n");
      }


      uint ncType = 0;
      memoryReader >> ncType;

      uint vSize = 0;
      memoryReader >> vSize;

      ulonglong offset = 0;

      if (mFileVersion == 1)
        offset = memoryReader.read_uint32();
      else
        offset = memoryReader.read_uint64();

      uint items = vSize/typeSize[ncType];

      printf("type   : %u\n",ncType);
      printf("size   : %u\n",vSize);
      printf("offset : %llu\n",offset);
      printf("items  : %u\n",items);

      std::vector<std::string> details;
      details.push_back(std::to_string(ncType));
      details.push_back(std::to_string(items));
      details.push_back(std::to_string(offset));
      details.push_back(std::to_string(vSize));

      sprintf(tmp,"%s.details",varName);
      propertyList.insert(std::pair<std::string,std::vector<std::string>>(std::string(tmp),details));


      auto readPos = memoryReader.getReadPosition();
      memoryReader.setReadPosition(offset);

      switch (ncType)
      {
        case 1:  // byte
        {
          uchar val = 0;
          for (uint i = 0; i < items; i++)
          {
            memoryReader >> val;
            if (i < items)
            {
              if (i != 0)
                printf(",%d",val);
              else
                printf("%d",val);
            }
          }
        }
        break;

        case 2:  // char
        {
          std::int8_t val = 0;
          for (uint i = 0; i < items; i++)
          {
            memoryReader >> val;
            if (i < items)
            {
              if (i != 0)
                printf(",%d",val);
              else
                printf("%d",val);
            }
          }
        }
        break;

        case 3:  // short
        {
          short val = 0;
          for (uint i = 0; i < items; i++)
          {
            memoryReader >> val;
            if (i < items)
            {
              if (i != 0)
                printf(",%d",val);
              else
                printf("%d",val);
            }
          }
        }
        break;

        case 4:  // int
        {
          int val = 0;
          for (uint i = 0; i < items; i++)
          {
            memoryReader >> val;
            if (i < items)
            {
              if (i != 0)
                printf(",%d",val);
              else
                printf("%d",val);
            }
          }
        }
        break;

        case 5:  // float
        {
          float val = 0;
          for (uint i = 0; i < items; i++)
          {
            memoryReader >> val;
            if (i < items)
            {
              if (i != 0)
                printf(",%f",val);
              else
                printf("%f",val);
            }
          }
        }
        break;

        case 6:  // double
        {
          double val = 0;
          for (uint i = 0; i < items; i++)
          {
            memoryReader >> val;
            if (i < items)
            {
              if (i != 0)
                printf(",%f",val);
              else
                printf("%f",val);
            }
          }
        }
        break;
      }
      printf("\n");

      memoryReader.setReadPosition(readPos);
    }

    propertyList.insert(std::pair<std::string,std::vector<std::string>>(std::string("variables"),variables));


    printf("READPOS %llu\n",memoryReader.getReadPosition());

    mIsRead = true;


    printf("PROPERTIES\n");
    for (auto pr = propertyList.begin();pr != propertyList.end(); ++pr)
    {
      printf("  [%s]",pr->first.c_str());
      for (auto it = pr->second.begin(); it != pr->second.end(); ++it)
      {
        printf("[%s]",it->c_str());
      }
      printf("\n");
    }

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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}




}
}
