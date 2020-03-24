#include "Message.h"
#include "../common/Dimensions.h"
#include "../grid/PrintOptions.h"
#include "../common/Exception.h"
#include "../common/AutoThreadLock.h"
#include "../common/GeneralFunctions.h"
#include "../common/GeneralDefinitions.h"
#include "../common/BitArrayWriter.h"
#include "../identification/GridDef.h"
#include "../grid/ValueCache.h"
#include "../grid/IndexCache.h"
#include "../grid/GridFile.h"
#include "../common/ShowFunction.h"
#include <iostream>
#include <sys/mman.h>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF

namespace SmartMet
{
namespace FMIG1
{



/*! \brief The constructor of the class. */

Message::Message()
{
  FUNCTION_TRACE
  try
  {
    mMessageSize = 0;
    mWidth = 0;
    mHeight = 0;
    mPixelCount = 0;
    mGrib1ParameterLevelId = 0;
    mGrib2ParameterLevelId = 0;
    mFmiParameterLevelId = 0;
    mForecastType = 1;
    mForecastNumber = -1;
    mGeometryId = 0;
    mIsRead = false;
    mFileType = T::FileTypeValue::Fmig1;
    mDataPosition = 0;
    mPixelSize = 0;
    mDataSize = 0;
    mDataStartPtr = nullptr;
    mDataEndPtr = nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





Message::Message(GRID::GridFile *gridFile,uint messageIndex,GRID::MessageInfo& messageInfo)
{
  FUNCTION_TRACE
  try
  {
    mGridFilePtr = gridFile;
    mMessageIndex = messageIndex;
    mWidth = 0;
    mHeight = 0;
    mPixelCount = 0;
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
    mFileType = T::FileTypeValue::Fmig1;
    mDataPosition = 0;
    mPixelSize = 0;
    mDataSize = 0;
    mDataStartPtr = nullptr;
    mDataEndPtr = nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The copy-constructor of the class. */

Message::Message(const Message& other)
:GRID::Message(other)
{
  FUNCTION_TRACE
  try
  {
    mGridFilePtr = nullptr;
    mIsRead = true;
    mWidth = other.mWidth;
    mHeight = other.mHeight;
    mPixelCount = other.mPixelCount;
    mForecastType = 1;
    mForecastNumber = -1;
    mMessageIndex = other.mMessageIndex;
    mMessageSize = other.mMessageSize;
    mFileType = other.mFileType;
    mDataPosition = 0;
    mPixelSize = other.mPixelSize;
    mDataSize = other.mDataSize;
    mDataStartPtr = nullptr;
    mDataEndPtr = nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




/*! \brief The destructor of the class. */

Message::~Message()
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current message.
*/

void Message::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
  FUNCTION_TRACE
  try
  {
    char name[300];

    //const GRID::ParameterDefinition *paramDef = SmartMet::GRID::gridDef.getParameterDefById(getGribParameterId());

    sprintf(name,"%smessage[%u].fmiProducerName",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(mFmiProducerName));

    sprintf(name,"%smessage[%u].gribParameterId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGribParameterId()));

    sprintf(name,"%smessage[%u].grib1ParameterLevelId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGrib1ParameterLevelId()));

    sprintf(name,"%smessage[%u].grib2ParameterLevelId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGrib2ParameterLevelId()));

    sprintf(name,"%smessage[%u].gribParameterName",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,mGribParameterName);

    sprintf(name,"%smessage[%u].gribParameterUnits",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,mGribParameterUnits);

    sprintf(name,"%smessage[%u].fmiParameterId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(mFmiParameterId));

    sprintf(name,"%smessage[%u].fmiParameterLevelId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(mFmiParameterLevelId));

    sprintf(name,"%smessage[%u].fmiParameterName",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,mFmiParameterName);

    sprintf(name,"%smessage[%u].fmiParameterUnits",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,mFmiParameterUnits);

    sprintf(name,"%smessage[%u].newbaseParameterId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(mNewbaseParameterId));

    sprintf(name,"%smessage[%u].newbaseParameterName",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(mNewbaseParameterName));

    sprintf(name,"%smessage[%u].cdmParameterId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,mCdmParameterId);

    sprintf(name,"%smessage[%u].cdmParameterName",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,mCdmParameterName);

    sprintf(name,"%smessage[%u].parameterLevel",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridParameterLevel()));

    sprintf(name,"%smessage[%u].parameterLevelId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridParameterLevelId()));

    sprintf(name,"%smessage[%u].parameterLevelIdString",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,getGridParameterLevelIdString());

    sprintf(name,"%smessage[%u].foracastTime",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,getForecastTime());

    //sprintf(name,"%smessage[%u].referenceTime",prefix.c_str(),mMessageIndex);
    //attributeList.addAttribute(name,getReferenceTime());

    sprintf(name,"%smessage[%u].gridGeometryId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridGeometryId()));

    sprintf(name,"%smessage[%u].gridType",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridProjection()));

    sprintf(name,"%smessage[%u].gridTypeString",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,getGridProjectionString());

    sprintf(name,"%smessage[%u].gridLayout",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridLayout()));

    sprintf(name,"%smessage[%u].gridLayoutString",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,T::get_gridLayoutString(getGridLayout()));

    sprintf(name,"%smessage[%u].gridRows",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridOriginalRowCount()));

    sprintf(name,"%smessage[%u].gridColumns",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridOriginalColumnCount()));

    sprintf(name,"%smessage[%u].WKT",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,getWKT());
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint Message::getTimeStepCount()
{
  try
  {
    return mTimeStepCount;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}


bool Message::isRead()
{
  try
  {
    return mIsRead;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
      SmartMet::Spine::Exception exception(BCP,"No pointer to the grib file!");

    long long s = mGridFilePtr->getSize();

    mDataStartPtr = (uchar*)mGridFilePtr->getMemoryPtr();
    mDataEndPtr = mDataStartPtr + s;

    MemoryReader memoryReader(mDataStartPtr,mDataEndPtr);
    memoryReader.setReadPosition(0);
    read(memoryReader);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Message read failed!",nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method reads and initializes all data related to the current message object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void Message::read(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  try
  {
    AutoThreadLock lock(&mThreadLock);

    if (mIsRead)
      return;

    memoryReader.setReadPosition(0);

    mMessageSize = memoryReader.getDataSize();

    uchar type[5] = {0};
    memoryReader.read_data(type,4);
    if (strcmp((char*)type,"FMIG") != 0)
      SmartMet::Spine::Exception exception(BCP,"Not a FMIG file!");

    uchar version = 0;
    memoryReader >> version;

    if (version != 0)
      SmartMet::Spine::Exception exception(BCP,"Invalid FMIG version!");


    uchar format = 0;
    memoryReader >> format;

    uint headerLen = 0;
    memoryReader >> headerLen;

    uchar header[headerLen+1];
    memoryReader.read_data(header,headerLen);
    header[headerLen] = '\0';

    printf("%s\n",header);

    std::vector<std::string> partList;
    splitString((char*)header,'\t',partList);

    uint len = partList.size();
    printf("PARTLIST LEN %u\n",len);
    for (uint t=0; t<len; t=t+2)
    {
      printf("[%s][%s]\n",partList[t].c_str(),partList[t+1].c_str());
      if ((t+1) < len)
        mAttributeList.addAttribute(partList[t],partList[t+1]);
      else
        mAttributeList.addAttribute(partList[t],"");
    }

    mAttributeList.print(std::cout,0,0);

    memoryReader >> mWidth;
    memoryReader >> mHeight;

    mPixelCount = mWidth * mHeight;

    memoryReader >> mTimeStepCount;

    mPixelSize = 2*sizeof(float) + mTimeStepCount * sizeof(ushort);
    mDataSize = mPixelCount * mPixelSize;

    for (uint t=0; t<mTimeStepCount; t++)
    {
      short year = 0;
      uchar month = 0, day = 0, hour = 0, minute = 0, second = 0;

      memoryReader >> year;
      memoryReader >> month;
      memoryReader >> day;
      memoryReader >> hour;
      memoryReader >> minute;
      memoryReader >> second;

      char tm[50];
      sprintf(tm,"%04u%02u%02uT%02u%02u%02u",year,month,day,hour,minute,second);
      if (t == 0)
        mReferenceTime = tm;

      if (t == mMessageIndex)
        mForecastTime = tm;

//      mTimeSteps.push_back(std::string(tm));
    }

    mDataPosition = memoryReader.getGlobalReadPosition();


    const char *producerName = mAttributeList.getAttributeValue("producer.name");
    if (producerName != nullptr)
      mFmiProducerName = producerName;

    const char *fmiParameterId = mAttributeList.getAttributeValue("param.fmi.id");
    if (fmiParameterId != nullptr)
      mFmiParameterId = fmiParameterId;

    const char *fmiParameterName = mAttributeList.getAttributeValue("param.fmi.name");
    if (fmiParameterName != nullptr)
      mFmiParameterName = fmiParameterName;

    const char *fmiParameterUnits = mAttributeList.getAttributeValue("param.units");
    if (fmiParameterUnits != nullptr)
      mFmiParameterUnits = fmiParameterUnits;

    const char *fmiParameterLevelId = mAttributeList.getAttributeValue("param.level.fmi.id");
    if (fmiParameterLevelId != nullptr)
      mFmiParameterLevelId = toInt16(fmiParameterLevelId);

    const char *level = mAttributeList.getAttributeValue("param.level.value");
    if (level != nullptr)
      mParameterLevel = toInt32(level);

    const char *geometryId = mAttributeList.getAttributeValue("geometry.id");
    if (geometryId != nullptr)
      mGeometryId = toInt32(geometryId);

    mGeometryDef = Identification::gridDef.getGrib1DefinitionByGeometryId(mGeometryId);

    mIsRead = true;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    exception.addParameter("Message start position",uint64_toHex(memoryReader.getStartPtr()-memoryReader.getParentPtr()));
    throw exception;
  }
}





/*! \brief The method returns the forecast start time. This is calculated from the reference
    time and other time parameters (=> NormalProduct->parameter()).

        \return   The forecast start time of the current message.
*/

T::TimeString Message::getReferenceTime() const
{
  FUNCTION_TRACE
  try
  {
    return mReferenceTime;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





T::TimeString Message::getForecastTime() const
{
  FUNCTION_TRACE
  try
  {
    return mForecastTime;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





void Message::getGridProjectionAttributes(std::string prefix,T::AttributeList& attributeList) const
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}




/*! \brief The method returns the GRIB version number of the current message.

        \return   The GRIB version number.
*/

uint Message::getGribVersion() const
{
  FUNCTION_TRACE
  try
  {
    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the GRIB 1 centre identifer.

        \return   The GRIB 1 centre identifier.
*/

uint Message::getGribCentre() const
{
  FUNCTION_TRACE
  try
  {
    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the GRIB 1 sub-centre identifer.

        \return   The GRIB 1 sub-centre identifier.
*/

uint Message::getGribSubCentre() const
{
  FUNCTION_TRACE
  try
  {
    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the GRIB 1 processing identifer.

        \return   The GRIB 1 processing identifier.
*/

uint Message::getGribGeneratingProcessIdentifier() const
{
  FUNCTION_TRACE
  try
  {
    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the GRIB 1 table version.

        \return   The GRIB 1 table version.
*/

uint Message::getGribTableVersion() const
{
  FUNCTION_TRACE
  try
  {
    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grid hash value.

        \return   The grid hash value.
*/

T::Hash Message::getGridHash() const
{
  FUNCTION_TRACE
  try
  {
    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid geometry identifer.

        \return   The grid geometry identifier.
*/

T::GeometryId Message::getGridGeometryId() const
{
  FUNCTION_TRACE
  try
  {
    return mGeometryId;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}






bool Message::getGridMetricCellSize(double& width,double& height) const
{
  FUNCTION_TRACE
  try
  {
    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridMetricSize(double& width,double& height) const
{
  FUNCTION_TRACE
  try
  {
    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight)
{
  FUNCTION_TRACE
  try
  {
    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight)
{
  FUNCTION_TRACE
  try
  {
    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
    std::string str;
    return str;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief This method can be used for finding out the grid projection type (Mercator, LatLon, PolarStereographic, etc.).

        \return   The type of the grid projection (expressed as an enum value).
*/

T::GridProjection Message::getGridProjection() const
{
  FUNCTION_TRACE
  try
  {
    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the type of the grid layout.

        \return   The layout of the grid (expressed as an enum value).
*/

T::GridLayout Message::getGridLayout() const
{
  FUNCTION_TRACE
  try
  {
    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
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

T::Dimensions Message::getGridDimensions() const
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions d(mWidth,mHeight);
    return d;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid latlon coordinates in the given grid point (= integer coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return        The method return true if the latlon values were succesfully returned.
*/

bool Message::getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const
{
  FUNCTION_TRACE
  try
  {
    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns all grid coordinates as a coordinate vector (in original projection).
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

        \return   The grid coordinates.
*/

T::Coordinate_vec Message::getGridOriginalCoordinates() const
{
  FUNCTION_TRACE
  try
  {
    T::Coordinate_vec coordinates;
    return coordinates;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns all grid coordinates as a latlon coordinate vector. If the grid
    original coordiantes were not latlon coordinates then the original coordinates are converted
    to the latlon coordinates.

        \return   The grid latlon coordinates.
*/

T::Coordinate_vec Message::getGridLatLonCoordinates() const
{
  FUNCTION_TRACE
  try
  {
    T::Coordinate_vec coordinates;
    return coordinates;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the file identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \return  The grid file identifier.
*/

uint Message::getFileId() const
{
  {
    try
    {
      if (mGridFilePtr != nullptr)
        return mGridFilePtr->getFileId();

      return 0;
    }
    catch (...)
    {
      throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
    }
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
    if (mGridFilePtr != nullptr)
      return mGridFilePtr->getProducerId();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    if (mGridFilePtr != nullptr)
      return mGridFilePtr->getGenerationId();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method can be used in order to find out the message's start
    position in the grib file.

        \return  The messages's start position in the grib file.
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






/*! \brief The method returns the grid definition string (=> Projection name).

        \return   The projection used in the current grid (LatLon, Mercator, etc.)
*/

std::string Message::getGridProjectionString() const
{
  FUNCTION_TRACE
  try
  {
    std::string str;
    return str;
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

bool Message::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
{
  FUNCTION_TRACE
  try
  {
    GRIB1::GridDef_ptr  def = Identification::gridDef.getGrib1DefinitionByGeometryId(mGeometryId);
    if (!def)
      return false;

    def->getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j);

    return true;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief This method calculates the estimated grid position of the the given original
    coordinates. The estimated grid position is returned in the 'grid_i' and 'grid_j' parameters.

        \param x       The original x-coordinate.
        \param y       The original y-coordinate.
        \param grid_i  The returned grid i-position.
        \param grid_j  The returned grid j-position.
        \return        The method returns 'false' if the given coordinates are
                       outside of the grid.
*/

bool Message::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  FUNCTION_TRACE
  try
  {
    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the number of rows used in the original grid.

        \return   The number of the grid rows.
*/

std::size_t Message::getGridOriginalRowCount() const
{
  FUNCTION_TRACE
  try
  {
    return mHeight;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the number of columns used in the given original grid row.

        \param row    The grid row index (= j-position).
        \return       The number of columns in the given grid row.
*/

std::size_t Message::getGridOriginalColumnCount(std::size_t row) const
{
  FUNCTION_TRACE
  try
  {
    return mWidth;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the maximum number of the columns used in the original grid.
    If the grid is irregular, this method returns the length of the longest row.

        \return   The maximum number of the columns in the grid.
*/

std::size_t Message::getGridOriginalColumnCount() const
{
  FUNCTION_TRACE
  try
  {
    return mWidth;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
    return mWidth * mHeight;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
    return grid_i + (grid_j * mWidth);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
  FUNCTION_TRACE
  try
  {
    T::ParamValue_vec values;
    getGridValueVector(values);

    minValue = 1000000000;
    maxValue = -1000000000;

    for (auto it = values.begin(); it != values.end(); ++it)
    {
      if (*it != ParamValueMissing)
      {
        if (*it < minValue)
          minValue = *it;

        if (*it > maxValue)
          maxValue = *it;
      }
    }
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getValueByIndex(uint index,T::ParamValue& value) const
{
  FUNCTION_TRACE
  try
  {
    if (index >= mPixelCount)
      return false;

    if (mDataStartPtr == nullptr || mDataEndPtr == nullptr)
      return false;

    MemoryReader memoryReader(mDataStartPtr,mDataEndPtr);

    float minValue = 0;
    float maxValue = 0;

    uint pixelPos = mDataPosition + index * mPixelSize;
    memoryReader.setReadPosition(pixelPos);

    memoryReader >> minValue;
    memoryReader >> maxValue;

    float d = (maxValue-minValue)/65530;
    ushort val = 0;

    memoryReader.setReadPosition(pixelPos + 2*sizeof(float) + mMessageIndex * sizeof(ushort));
    memoryReader >> val;

    if (value == 0xFFFF)
      value = ParamValueMissing;
    else
      value = minValue + d*(double)val;
    //printf("%u: %f,%f %u x %f = %f\n",index,minValue,maxValue,val,d,value);
    return true;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid value in the given (exact) point.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The parameter value of the given grid point.
*/

T::ParamValue Message::getGridValueByGridPoint(uint grid_i,uint grid_j) const
{
  FUNCTION_TRACE
  try
  {
    int idx = 0; //getGridOriginalValueIndex(grid_i,grid_j);

    auto rows = getGridOriginalRowCount();
    auto cols = getGridOriginalColumnCount();

    if (grid_j >= rows)
      return ParamValueMissing;

    if (grid_i >= cols &&  !isGridGlobal())
      return ParamValueMissing;

    idx = C_INT((grid_j * cols) + (grid_i % cols));

    if (idx < 0)
      return ParamValueMissing;

    T::ParamValue value = 0;

    incRequestCounter(idx);

    if (getValueByIndex(idx,value))
      return value;

    return ParamValueMissing;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid value in the given original grid point.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The parameter value of the given grid point.
*/

T::ParamValue Message::getGridValueByOriginalGridPoint(uint grid_i,uint grid_j) const
{
  FUNCTION_TRACE
  try
  {
    return getGridValueByGridPoint(grid_i,grid_j);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns all grid data values (also missing values) as the grid
    would be regular. in the case of an irregular grid, the grid rows are filled so that
    the grid looks like a regular grid.

        \param values   The returned grid values.
*/

void Message::getGridValueVector(T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    values.clear();

    uint sz = mWidth * mHeight;
    if (sz == 0)
      return;

    values.reserve(sz);
    for (uint t=0; t<sz; t++)
    {
      T::ParamValue value = 0;

      if (getValueByIndex(t,value))
        values.push_back(value);
      else
        values.push_back(ParamValueMissing);
    }
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the original grid data values. If the grid
    is regular then the 'getGridValueVector()' method returns the same
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
  FUNCTION_TRACE
  try
  {
    getGridValueVector(values);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the type of the parameter level.

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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the parameter level type string (define in Table 4.5).

        \return   The parameter level type (expressed in a string).
*/

std::string Message::getGridParameterLevelIdString() const
{
  FUNCTION_TRACE
  try
  {
    std::string str = std::to_string(mFmiParameterLevelId);
    return str;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method intializes the grid's spatial reference that is used for coordinate conversions. */

void Message::initSpatialReference()
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the pointer to the spatial reference of the current grid.

        \return   The pointer to the spatial reference.
*/

T::SpatialRef* Message::getSpatialReference() const
{
  FUNCTION_TRACE
  try
  {
    return nullptr;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the WKT (Well-Known-Text) of the current grid.

        \return   The WKT of the current grid.
*/

std::string Message::getWKT() const
{
  FUNCTION_TRACE
  try
  {
    std::string wkt;
    T::SpatialRef *sr = getSpatialReference();
    if (sr != nullptr)
    {
      char *out = nullptr;
      sr->exportToWkt(&out);
      wkt = out;
      OGRFree(out);
    }
    return wkt;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the forecast type of the current grid.

        \return   The forecast type.
*/

short Message::getForecastType() const
{
  FUNCTION_TRACE
  try
  {
    return mForecastType;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the forecast number of the current grid.

        \return   The forecast number.
*/

short Message::getForecastNumber() const
{
  FUNCTION_TRACE
  try
  {
    return mForecastNumber;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::isRelativeUV() const
{
  FUNCTION_TRACE
  try
  {
    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns 'true' if the grid horizontal values are in the reverse order.

        \return   The method returns 'true' if the grid horizontal values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool Message::reverseXDirection() const
{
  FUNCTION_TRACE
  try
  {
    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns 'true' if the grid vertical values are in the reverse order.

        \return   The method returns 'true' if the grid vertical values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool Message::reverseYDirection() const
{
  FUNCTION_TRACE
  try
  {
    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
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
    stream << space(level) << "- fileType                = " << toString(mFileType) << "\n";
    stream << space(level) << "- gribParameterId         = " << toString(mGribParameterId) << "\n";
    stream << space(level) << "- gribParameterName       = " << mGribParameterName << "\n";
    stream << space(level) << "- gribParameterUnits      = " << mGribParameterUnits << "\n";
    stream << space(level) << "- parameterLevel          = " << toString(getGridParameterLevel()) << "\n";
    stream << space(level) << "- parameterLevelId        = " << toString(getGridParameterLevelId()) << "\n";
    stream << space(level) << "- parameterLevelIdString  = " << getGridParameterLevelIdString() << "\n";
    stream << space(level) << "- fmiProducerName         = " << mFmiProducerName << "\n";
    stream << space(level) << "- fmiParameterId          = " << toString(mFmiParameterId) << "\n";
    stream << space(level) << "- fmiParameterLevelId     = " << toString(mFmiParameterLevelId) << "\n";
    stream << space(level) << "- fmiParameterName        = " << mFmiParameterName << "\n";
    stream << space(level) << "- fmiParameterUnits       = " << mFmiParameterUnits << "\n";
    stream << space(level) << "- newbaseParameterId      = " << mNewbaseParameterId << "\n";
    stream << space(level) << "- newbaseParameterName    = " << mNewbaseParameterName << "\n";
    stream << space(level) << "- cdmParameterId          = " << mCdmParameterId << "\n";
    stream << space(level) << "- cdmParameterName        = " << mCdmParameterName << "\n";
    stream << space(level) << "- newbaseParameterId      = " << mNewbaseParameterId << "\n";
    stream << space(level) << "- newbaseParameterName    = " << mNewbaseParameterName << "\n";
    stream << space(level) << "- referenceTime           = " << getReferenceTime() << "\n";
    stream << space(level) << "- forecastTime            = " << getForecastTime() << "\n";
    stream << space(level) << "- gridGeometryId          = " << getGridGeometryId() << "\n";
    stream << space(level) << "- gridHash                = " << getGridHash() << "\n";
    stream << space(level) << "- gridProjection          = " << T::get_gridProjectionString(getGridProjection()) << "\n";
    stream << space(level) << "- gridLayout              = " << T::get_gridLayoutString(getGridLayout()) << "\n";
    stream << space(level) << "- gridOriginalRowCount    = " << toString(getGridOriginalRowCount()) << "\n";
    stream << space(level) << "- gridOriginalColumnCount = " << toString(getGridOriginalColumnCount()) << "\n";
    stream << space(level) << "- WKT                     = " << getWKT() << "\n";
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}


}  // namespace GRIB1
}  // namespace SmartMet
