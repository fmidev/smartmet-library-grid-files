#include "Message.h"
#include "../common/CoordinateConversions.h"
#include "../common/GeneralFunctions.h"
#include "../common/GeneralDefinitions.h"
#include "../common/GraphFunctions.h"
#include "../common/Point.h"
#include "../common/InterpolationFunctions.h"
#include "../common/ShowFunction.h"
#include "../common/MemoryWriter.h"
#include "../identification/GridDef.h"
#include <macgyver/StringConversion.h>
#include <macgyver/Exception.h>
#include <macgyver/FastMath.h>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{
namespace GRID
{

typedef std::vector<float> AngleList;
typedef std::map<int,AngleList> AngleCache;

AngleCache gridAngleCache;

const uint tmpValueCacheSize = 200;
uint tmpValueCachePos = 0;

struct TmpValueCacheRec
{
    T::ParamValue_vec values;
    unsigned long long hash;
    uint fileId;
    uint messageIndex;
};

TmpValueCacheRec tmpValueCache[tmpValueCacheSize];
ThreadLock tmpCacheThreadLock;
std::vector<double> EMPTY_DOUBLE_VEC;
std::vector<Message*> EMPTY_MSG_VEC;



/*! \brief The constructor of the class. */

Message::Message()
{
  FUNCTION_TRACE
  try
  {
    mMessageIndex = 0;
    mMessageSize = 0;
    mGeometryId = 0;
    mGridFilePtr = nullptr;
    mFmiParameterLevelId = 0;
    mFmiParameterId = 0;
    mNewbaseParameterId = 0;
    mGribParameterId = 0;
    mParameterLevel = 0;
    mDefaultInterpolationMethod = T::AreaInterpolationMethod::Nearest;
    mFileType = 0;
    mVirtualFileId = 0;
    mRowCount = 0;
    mColumnCount = 0;
    mFmiParameterName = 0;
    mNetCdfParameterName = 0;
    mNewbaseParameterName = 0;
    mGribParameterName = 0;
    mFmiParameterUnits = 0;
    mGribParameterUnits = 0;
    mPremapped = false;
    mRequestCounter = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

Message::Message(const Message& message)
{
  FUNCTION_TRACE
  try
  {
    mGridFilePtr = message.mGridFilePtr;
    mMessageIndex = message.mMessageIndex;
    mMessageSize = message.mMessageSize;
    mGeometryId = message.mGeometryId;
    mGribParameterId = message.mGribParameterId;
    mParameterLevel = message.mParameterLevel;
    mGribParameterName = message.mGribParameterName;
    mGribParameterUnits = message.mGribParameterUnits;
    mFmiParameterId = message.mFmiParameterId;
    mFmiParameterLevelId = message.mFmiParameterLevelId;
    mFmiParameterName = message.mFmiParameterName;
    mFmiParameterUnits = message.mFmiParameterUnits;
    mNewbaseParameterId = message.mNewbaseParameterId;
    mNetCdfParameterName = message.mNetCdfParameterName;
    mNewbaseParameterName = message.mNewbaseParameterName;
    mVirtualFileId = message.mVirtualFileId;
    mDefaultInterpolationMethod = message.mDefaultInterpolationMethod;
    mFileType = message.mFileType;
    mRowCount = message.mRowCount;
    mColumnCount = message.mColumnCount;
    mPremapped = message.mPremapped;
    mRequestCounter = message.mRequestCounter;
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




void Message::premap() const
{
}



/*! \brief The method can be used for collecting all attributeList details related
    to the current message.
*/

void Message::getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::getAttributeValue(const char *attributeName, std::string& attributeValue) const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}




bool Message::hasAttributeValue(const char *attributeName, const char *attributeValue) const
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





uint Message::getMessageIndex() const
{
  FUNCTION_TRACE
  try
  {
    return mMessageIndex;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint Message::getMessageSize() const
{
  FUNCTION_TRACE
  try
  {
    return mMessageSize;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::setGridFilePtr(GridFile *gridFilePtr)
{
  FUNCTION_TRACE
  try
  {
    mGridFilePtr = gridFilePtr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::setMessageIndex(uint index)
{
  FUNCTION_TRACE
  try
  {
    mMessageIndex = index;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the reference time of the current grid. The forecast
    times are calculated from this.

        \return   The reference time of the current grid.
*/

T::TimeString Message::getReferenceTime() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





uint Message::getGribVersion() const
{
  return 0;
}





uint Message::getGribCentre() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





uint Message::getGribSubCentre() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





uint Message::getGribGeneratingProcessIdentifier() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





uint Message::getGribTableVersion() const
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





void Message::getGridIsobands(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    getGridIsobands(contourLowValues,contourHighValues,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridIsobands(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    size_t smoothSize = 0;
    const char *smoothSizeStr = attributeList.getAttributeValue("contour.smooth.size");
    if (smoothSizeStr != nullptr)
      smoothSize = static_cast<size_t>(toInt32(smoothSizeStr));

    size_t smoothDegree = 0;
    const char *smoothDegreeStr = attributeList.getAttributeValue("contour.smooth.degree");
    if (smoothDegreeStr != nullptr)
      smoothDegree = static_cast<size_t>(toInt32(smoothDegreeStr));

    T::ParamValue_vec gridValues;
    getGridValueVectorWithCaching(modificationOperation,modificationParameters,gridValues);

    T::Dimensions d = getGridDimensions();
    T::Coordinate_svec coordinates;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = getGridLatLonCoordinates();
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = getGridOriginalCoordinates();
        break;
    }

    getIsobands(gridValues,coordinates.get(),d.nx(),d.ny(),contourLowValues,contourHighValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
    attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridIsobandsByGeometry(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    getGridIsobandsByGeometry(contourLowValues,contourHighValues,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridIsobandsByGeometry(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    const char *crsStr = attributeList.getAttributeValue("grid.crs");
    const char *centerStr = attributeList.getAttributeValue("grid.center");
    const char *llboxStr = attributeList.getAttributeValue("grid.llbox");
    const char *gridSizeStr = attributeList.getAttributeValue("grid.size");

    if (gridSizeStr != nullptr)
    {
      double m = toDouble(gridSizeStr);
      if (m > 0)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(C_INT(C_DOUBLE(getGridWidth())*m)));
        attributeList.setAttribute("grid.height",Fmi::to_string(C_INT(C_DOUBLE(getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
      const char *gridHeightStr = attributeList.getAttributeValue("grid.height");
      if ((gridWidthStr == nullptr || gridHeightStr == nullptr) &&  centerStr == nullptr)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(getGridWidth()));
        attributeList.setAttribute("grid.height",Fmi::to_string(getGridHeight()));
      }

      attributeList.setAttribute("grid.crs",getWKT());
      attributeList.setAttribute("grid.proj4",getProj4());
      T::Dimensions  d = getGridDimensions();

      if (llboxStr == nullptr)
      {
        double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
        uint px1 = 0,py1 = 0,px2 = d.nx()-1,py2 = d.ny()-1;

        if (reverseYDirection())
          px1 = 0,py1 = d.ny()-1,px2 = d.nx()-1,py2 = 0;

        char tmp[100];
        if (getGridLatLonCoordinatesByGridPoint(px1,py1,y1,x1)  &&  getGridLatLonCoordinatesByGridPoint(px2,py2,y2,x2))
        {
          if (x2 < x1  &&  x2 < 0)
            x2 += 360;

          if (x2 < x1  && x1 >= 180)
            x1 -= 360;

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          attributeList.setAttribute("grid.llbox",tmp);
          if (getGridProjection() == T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }

        if (getGridOriginalCoordinatesByGridPoint(0,0,x1,y1)  &&  getGridOriginalCoordinatesByGridPoint(d.nx()-1,d.ny()-1,x2,y2))
        {
          if (getGridProjection() == T::GridProjectionValue::LatLon)
          {
            if (x2 < x1  &&  x2 < 0)
              x2 += 360;

            if (x2 < x1  && x1 >= 180)
              x1 -= 360;
          }

          if (reverseYDirection())
          {
            double tmp = y1;
            y1 = y2;
            y2 = tmp;
          }

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          if (getGridProjection() != T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }
      }

      if (llboxStr == nullptr &&  centerStr != nullptr)
      {
        // The crop area is defined by a rectangle and its latlon center coordinates.

        std::vector<double> a;
        splitString(centerStr,',',a);
        if (a.size() != 2)
          return;

        const char *metricWidthStr = attributeList.getAttributeValue("grid.metricWidth");
        const char *metricHeightStr = attributeList.getAttributeValue("grid.metricHeight");

        if (metricWidthStr != nullptr &&  metricHeightStr != nullptr)
        {
          double centerX = a[0];
          double centerY = a[1];

          double mWidth = toDouble(metricWidthStr) * 1000;   // km => m
          double mHeight = toDouble(metricHeightStr) * 1000; // km => m

          double lon1 = 0,lat1 = 0,lon2 = 0, lat2 =0;

          latLon_bboxByCenter(centerX,centerY,mWidth,mHeight,lon1,lat1,lon2,lat2);

          char tmp[200];
          sprintf(tmp,"%f,%f,%f,%f",lon1,lat1,lon2,lat2);
          attributeList.setAttribute("grid.llbox",tmp);
        }
      }

      attributeList.setAttribute("grid.projectionType",Fmi::to_string(getGridProjection()));
    }

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

    size_t smoothSize = 0;
    const char *smoothSizeStr = attributeList.getAttributeValue("contour.smooth.size");
    if (smoothSizeStr != nullptr)
      smoothSize = toSize_t(smoothSizeStr);

    size_t smoothDegree = 0;
    const char *smoothDegreeStr = attributeList.getAttributeValue("contour.smooth.degree");
    if (smoothDegreeStr != nullptr)
      smoothDegree = toSize_t(smoothDegreeStr);

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    attributeList.setAttribute("grid.original.crs",getWKT());
    attributeList.setAttribute("grid.original.proj4",getProj4());
    attributeList.setAttribute("grid.original.width",Fmi::to_string(getGridWidth()));
    attributeList.setAttribute("grid.original.height",Fmi::to_string(getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));

    double wm = 0;
    double hm = 0;
    if (getGridMetricCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
    else
    {
      attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

      getGridCellAverageSize(wm,hm);
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");

    if (geometryIdStr != nullptr  &&  getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridIsobands(contourLowValues,contourHighValues,attributeList,contours);

      T::Dimensions  d = getGridDimensions();
      attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
      attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
      return;
    }

    uint width = 0;
    uint height = 0;
    T::Coordinate_svec coordinates;
    T::Coordinate_svec latLonCoordinates;

    Identification::gridDef.getGridOriginalCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (!latLonCoordinates || latLonCoordinates->size() == 0)
    {
      getGridIsobands(contourLowValues,contourHighValues,attributeList,modificationOperation,modificationParameters,contours);
      return;
    }

    T::ParamValue_vec gridValues;
    getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,*latLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,gridValues);

    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinatePtr = latLonCoordinates.get();
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinatePtr = coordinates.get();
        break;
    }

    getIsobands(gridValues,coordinatePtr,width,height,contourLowValues,contourHighValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.width",Fmi::to_string(width));
    attributeList.setAttribute("grid.height",Fmi::to_string(height));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridIsobandsByGrid(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,std::vector<T::Coordinate>& projectionCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    getGridIsobandsByGrid(contourLowValues,contourHighValues,gridWidth,gridHeight,gridLatLonCoordinates,projectionCoordinates,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridIsobandsByGrid(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,std::vector<T::Coordinate>& projectionCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    if (gridLatLonCoordinates.size() == 0 ||  gridWidth == 0 || gridHeight == 0)
      return;

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

    T::CoordinateType coordinateType = T::CoordinateTypeValue::GRID_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    size_t smoothSize = 0;
    const char *smoothSizeStr = attributeList.getAttributeValue("contour.smooth.size");
    if (smoothSizeStr != nullptr)
      smoothSize = toSize_t(smoothSizeStr);

    size_t smoothDegree = 0;
    const char *smoothDegreeStr = attributeList.getAttributeValue("contour.smooth.degree");
    if (smoothDegreeStr != nullptr)
      smoothDegree = toSize_t(smoothDegreeStr);

    T::ParamValue_vec gridValues;
    getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,gridValues);
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinatePtr = &projectionCoordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        break;
    }

    getIsobands(gridValues,coordinatePtr,gridWidth,gridHeight,contourLowValues,contourHighValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(gridWidth));
    attributeList.setAttribute("grid.height",Fmi::to_string(gridHeight));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridIsolines(T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    getGridIsolines(contourValues,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridIsolines(T::ParamValue_vec& contourValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    size_t smoothSize = 0;
    const char *smoothSizeStr = attributeList.getAttributeValue("contour.smooth.size");
    if (smoothSizeStr != nullptr)
      smoothSize = toSize_t(smoothSizeStr);

    size_t smoothDegree = 0;
    const char *smoothDegreeStr = attributeList.getAttributeValue("contour.smooth.degree");
    if (smoothDegreeStr != nullptr)
      smoothDegree = toSize_t(smoothDegreeStr);

    T::ParamValue_vec gridValues;
    getGridValueVector(modificationOperation,modificationParameters,gridValues);

    T::Dimensions d = getGridDimensions();
    T::Coordinate_svec coordinates;
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = getGridLatLonCoordinates();
        coordinatePtr = coordinates.get();
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = getGridOriginalCoordinates();
        coordinatePtr = coordinates.get();
        break;
    }

    getIsolines(gridValues,coordinatePtr,d.nx(),d.ny(),contourValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
    attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));

  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridIsolinesByGeometry(T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    getGridIsolinesByGeometry(contourValues,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridIsolinesByGeometry(T::ParamValue_vec& contourValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    const char *crsStr = attributeList.getAttributeValue("grid.crs");
    const char *llboxStr = attributeList.getAttributeValue("grid.llbox");
    const char *centerStr = attributeList.getAttributeValue("grid.center");
    const char *gridSizeStr = attributeList.getAttributeValue("grid.size");

    if (gridSizeStr != nullptr)
    {
      double m = toDouble(gridSizeStr);
      if (m > 0)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(C_INT(C_DOUBLE(getGridWidth())*m)));
        attributeList.setAttribute("grid.height",Fmi::to_string(C_INT(C_DOUBLE(getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
      const char *gridHeightStr = attributeList.getAttributeValue("grid.height");
      if ((gridWidthStr == nullptr || gridHeightStr == nullptr) &&  centerStr == nullptr)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(getGridWidth()));
        attributeList.setAttribute("grid.height",Fmi::to_string(getGridHeight()));
      }

      attributeList.setAttribute("grid.crs",getWKT());
      attributeList.setAttribute("grid.proj4",getProj4());
      T::Dimensions  d = getGridDimensions();

      if (llboxStr == nullptr)
      {
        double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
        uint px1 = 0,py1 = 0,px2 = d.nx()-1,py2 = d.ny()-1;

        if (reverseYDirection())
          px1 = 0,py1 = d.ny()-1,px2 = d.nx()-1,py2 = 0;

        char tmp[100];
        if (getGridLatLonCoordinatesByGridPoint(px1,py1,y1,x1)  &&  getGridLatLonCoordinatesByGridPoint(px2,py2,y2,x2))
        {
          if (x2 < x1  &&  x2 < 0)
            x2 += 360;

          if (x2 < x1  && x1 >= 180)
            x1 -= 360;

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          attributeList.setAttribute("grid.llbox",tmp);
          if (getGridProjection() == T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }

        if (getGridOriginalCoordinatesByGridPoint(0,0,x1,y1)  &&  getGridOriginalCoordinatesByGridPoint(d.nx()-1,d.ny()-1,x2,y2))
        {
          if (getGridProjection() == T::GridProjectionValue::LatLon)
          {
            if (x2 < x1  &&  x2 < 0)
              x2 += 360;

            if (x2 < x1  && x1 >= 180)
              x1 -= 360;
          }

          if (reverseYDirection())
          {
            double tmp = y1;
            y1 = y2;
            y2 = tmp;
          }

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          if (getGridProjection() != T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }
      }

      if (llboxStr == nullptr &&  centerStr != nullptr)
      {
        // The crop area is defined by a rectangle and its latlon center coordinates.

        std::vector<double> a;
        splitString(centerStr,',',a);
        if (a.size() != 2)
          return;

        const char *metricWidthStr = attributeList.getAttributeValue("grid.metricWidth");
        const char *metricHeightStr = attributeList.getAttributeValue("grid.metricHeight");

        if (metricWidthStr != nullptr &&  metricHeightStr != nullptr)
        {
          double centerX = a[0];
          double centerY = a[1];

          double mWidth = toDouble(metricWidthStr) * 1000;   // km => m
          double mHeight = toDouble(metricHeightStr) * 1000; // km => m

          double lon1 = 0,lat1 = 0,lon2 = 0, lat2 =0;

          latLon_bboxByCenter(centerX,centerY,mWidth,mHeight,lon1,lat1,lon2,lat2);

          char tmp[200];
          sprintf(tmp,"%f,%f,%f,%f",lon1,lat1,lon2,lat2);
          attributeList.setAttribute("grid.llbox",tmp);
        }
      }

      attributeList.setAttribute("grid.projectionType",Fmi::to_string(getGridProjection()));
    }

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

    size_t smoothSize = 0;
    const char *smoothSizeStr = attributeList.getAttributeValue("contour.smooth.size");
    if (smoothSizeStr != nullptr)
      smoothSize = toSize_t(smoothSizeStr);

    size_t smoothDegree = 0;
    const char *smoothDegreeStr = attributeList.getAttributeValue("contour.smooth.degree");
    if (smoothDegreeStr != nullptr)
      smoothDegree = toSize_t(smoothDegreeStr);

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    attributeList.setAttribute("grid.original.crs",getWKT());
    attributeList.setAttribute("grid.original.proj4",getProj4());
    attributeList.setAttribute("grid.original.width",Fmi::to_string(getGridWidth()));
    attributeList.setAttribute("grid.original.height",Fmi::to_string(getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));

    double wm = 0;
    double hm = 0;
    if (getGridMetricCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
    else
    {
      attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

      getGridCellAverageSize(wm,hm);
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");

    if (geometryIdStr != nullptr  &&  getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridIsolines(contourValues,attributeList,contours);
      T::Dimensions  d = getGridDimensions();
      attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
      attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
      return;
    }

    uint width = 0;
    uint height = 0;
    T::Coordinate_svec coordinates;
    T::Coordinate_svec latLonCoordinates;

    Identification::gridDef.getGridOriginalCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (!latLonCoordinates || latLonCoordinates->size() == 0)
    {
      getGridIsolines(contourValues,attributeList,modificationOperation,modificationParameters,contours);
      return;
    }


    T::ParamValue_vec gridValues;
    getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,*latLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,gridValues);

    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinatePtr = latLonCoordinates.get();
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinatePtr = coordinates.get();
        break;
    }

    getIsolines(gridValues,coordinatePtr,width,height,contourValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.width",Fmi::to_string(width));
    attributeList.setAttribute("grid.height",Fmi::to_string(height));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridIsolinesByGrid(T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,std::vector<T::Coordinate>& projectionCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    getGridIsolinesByGrid(contourValues,gridWidth,gridHeight,gridLatLonCoordinates,projectionCoordinates,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridIsolinesByGrid(T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,std::vector<T::Coordinate>& projectionCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    if (gridLatLonCoordinates.size() == 0 ||  gridWidth == 0 || gridHeight == 0)
      return;

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    size_t smoothSize = 0;
    const char *smoothSizeStr = attributeList.getAttributeValue("contour.smooth.size");
    if (smoothSizeStr != nullptr)
      smoothSize = toSize_t(smoothSizeStr);

    size_t smoothDegree = 0;
    const char *smoothDegreeStr = attributeList.getAttributeValue("contour.smooth.degree");
    if (smoothDegreeStr != nullptr)
      smoothDegree = toSize_t(smoothDegreeStr);

    T::ParamValue_vec gridValues;
    getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,gridValues);

    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinatePtr = &projectionCoordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        break;
    }

    getIsolines(gridValues,coordinatePtr,gridWidth,gridHeight,contourValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(gridWidth));
    attributeList.setAttribute("grid.height",Fmi::to_string(gridHeight));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridStreamlines(T::AttributeList& attributeList,T::ByteData_vec& streamlines)
{
  FUNCTION_TRACE
  try
  {
    getGridStreamlines(attributeList,0,EMPTY_DOUBLE_VEC,streamlines);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridStreamlines(T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines)
{
  FUNCTION_TRACE
  try
  {
    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("stream.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    int maxStreamLen = 2048;
    const char *maxLengthStr = attributeList.getAttributeValue("stream.maxLength");
    if (maxLengthStr != nullptr)
      maxStreamLen = toInt32(maxLengthStr);

    int minStreamLen = 5;
    const char *minLengthStr = attributeList.getAttributeValue("stream.minLength");
    if (minLengthStr != nullptr)
      minStreamLen = toInt32(minLengthStr);

    int lineLen = 2048;
    const char *lineLengthStr = attributeList.getAttributeValue("stream.lineLength");
    if (lineLengthStr != nullptr)
      lineLen = toInt32(lineLengthStr);

    int xStep = 20;
    const char *xStepStr = attributeList.getAttributeValue("stream.xStep");
    if (xStepStr != nullptr)
      xStep = toInt32(xStepStr);

    int yStep = 20;
    const char *yStepStr = attributeList.getAttributeValue("stream.yStep");
    if (yStepStr != nullptr)
      yStep = toInt32(yStepStr);


    T::ParamValue_vec gridValues;
    getGridValueVector(modificationOperation,modificationParameters,gridValues);

    T::Coordinate_svec coordinates;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = getGridLatLonCoordinates();
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = getGridOriginalCoordinates();
        break;
    }

    int width = getGridWidth();
    int height = getGridHeight();

    getStreamlines(gridValues,coordinates.get(),width,height,minStreamLen, maxStreamLen,lineLen,xStep,yStep,streamlines);

    attributeList.setAttribute("grid.width",Fmi::to_string(width));
    attributeList.setAttribute("grid.height",Fmi::to_string(height));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)reverseXDirection()));
    attributeList.setAttribute("stream.coordinateType",Fmi::to_string(coordinateType));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridStreamlinesByGeometry(T::AttributeList& attributeList,T::ByteData_vec& streamlines)
{
  FUNCTION_TRACE
  try
  {
    getGridStreamlinesByGeometry(attributeList,0,EMPTY_DOUBLE_VEC,streamlines);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridStreamlinesByGeometry(T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines)
{
  FUNCTION_TRACE
  try
  {
    const char *crsStr = attributeList.getAttributeValue("grid.crs");
    const char *llboxStr = attributeList.getAttributeValue("grid.llbox");
    const char *centerStr = attributeList.getAttributeValue("grid.center");
    const char *gridSizeStr = attributeList.getAttributeValue("grid.size");

    if (gridSizeStr != nullptr)
    {
      double m = toDouble(gridSizeStr);
      if (m > 0)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(C_INT(C_DOUBLE(getGridWidth())*m)));
        attributeList.setAttribute("grid.height",Fmi::to_string(C_INT(C_DOUBLE(getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
      const char *gridHeightStr = attributeList.getAttributeValue("grid.height");
      if ((gridWidthStr == nullptr || gridHeightStr == nullptr) &&  centerStr == nullptr)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(getGridWidth()));
        attributeList.setAttribute("grid.height",Fmi::to_string(getGridHeight()));
      }

      attributeList.setAttribute("grid.crs",getWKT());
      attributeList.setAttribute("grid.proj4",getProj4());
      T::Dimensions  d = getGridDimensions();

      if (llboxStr == nullptr)
      {
        double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
        uint px1 = 0,py1 = 0,px2 = d.nx()-1,py2 = d.ny()-1;

        if (reverseYDirection())
          px1 = 0,py1 = d.ny()-1,px2 = d.nx()-1,py2 = 0;

        char tmp[100];
        if (getGridLatLonCoordinatesByGridPoint(px1,py1,y1,x1)  &&  getGridLatLonCoordinatesByGridPoint(px2,py2,y2,x2))
        {
          if (x2 < x1  &&  x2 < 0)
            x2 += 360;

          if (x2 < x1  && x1 >= 180)
            x1 -= 360;

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          attributeList.setAttribute("grid.llbox",tmp);
          if (getGridProjection() == T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }

        if (getGridOriginalCoordinatesByGridPoint(0,0,x1,y1)  &&  getGridOriginalCoordinatesByGridPoint(d.nx()-1,d.ny()-1,x2,y2))
        {
          if (getGridProjection() == T::GridProjectionValue::LatLon)
          {
            if (x2 < x1  &&  x2 < 0)
              x2 += 360;

            if (x2 < x1  && x1 >= 180)
              x1 -= 360;
          }

          if (reverseYDirection())
          {
            double tmp = y1;
            y1 = y2;
            y2 = tmp;
          }

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          if (getGridProjection() != T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }
      }

      if (llboxStr == nullptr &&  centerStr != nullptr)
      {
        // The crop area is defined by a rectangle and its latlon center coordinates.

        std::vector<double> a;
        splitString(centerStr,',',a);
        if (a.size() != 2)
          return;

        const char *metricWidthStr = attributeList.getAttributeValue("grid.metricWidth");
        const char *metricHeightStr = attributeList.getAttributeValue("grid.metricHeight");

        if (metricWidthStr != nullptr &&  metricHeightStr != nullptr)
        {
          double centerX = a[0];
          double centerY = a[1];

          double mWidth = toDouble(metricWidthStr) * 1000;   // km => m
          double mHeight = toDouble(metricHeightStr) * 1000; // km => m

          double lon1 = 0,lat1 = 0,lon2 = 0, lat2 =0;

          latLon_bboxByCenter(centerX,centerY,mWidth,mHeight,lon1,lat1,lon2,lat2);

          char tmp[200];
          sprintf(tmp,"%f,%f,%f,%f",lon1,lat1,lon2,lat2);
          attributeList.setAttribute("grid.llbox",tmp);
        }
      }

      attributeList.setAttribute("grid.projectionType",Fmi::to_string(getGridProjection()));
    }

    short areaInterpolationMethod = T::AreaInterpolationMethod::Nearest;

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("stream.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    attributeList.setAttribute("grid.original.crs",getWKT());
    attributeList.setAttribute("grid.original.proj4",getProj4());
    attributeList.setAttribute("grid.original.width",Fmi::to_string(getGridWidth()));
    attributeList.setAttribute("grid.original.height",Fmi::to_string(getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("stream.coordinateType",Fmi::to_string(coordinateType));

    double wm = 0;
    double hm = 0;
    if (getGridMetricCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
    else
    {
      attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

      getGridCellAverageSize(wm,hm);
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");

    if (geometryIdStr != nullptr  &&  getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridStreamlines(attributeList,streamlines);
      T::Dimensions  d = getGridDimensions();
      attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
      attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
      return;
    }

    uint gwidth = 0;
    uint gheight = 0;
    T::Coordinate_svec coordinates;
    T::Coordinate_svec latLonCoordinates;

    Identification::gridDef.getGridOriginalCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,gwidth,gheight);

    if (!latLonCoordinates || latLonCoordinates->size() == 0)
    {
      getGridStreamlines(attributeList,modificationOperation,modificationParameters,streamlines);
      return;
    }


    int maxStreamLen = 2048;
    const char *maxLengthStr = attributeList.getAttributeValue("stream.maxLength");
    if (maxLengthStr != nullptr)
      maxStreamLen = toInt32(maxLengthStr);

    int minStreamLen = 5;
    const char *minLengthStr = attributeList.getAttributeValue("stream.minLength");
    if (minLengthStr != nullptr)
      minStreamLen = toInt32(minLengthStr);

    int lineLen = 2048;
    const char *lineLengthStr = attributeList.getAttributeValue("stream.lineLength");
    if (lineLengthStr != nullptr)
      lineLen = toInt32(lineLengthStr);

    int xStep = 20;
    const char *xStepStr = attributeList.getAttributeValue("stream.xStep");
    if (xStepStr != nullptr)
      xStep = toInt32(xStepStr);

    int yStep = 20;
    const char *yStepStr = attributeList.getAttributeValue("stream.yStep");
    if (yStepStr != nullptr)
      yStep = toInt32(yStepStr);



    T::ParamValue_vec gridValues;
    getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,*latLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,gridValues);

    getStreamlines(gridValues,coordinates.get(),gwidth,gheight,minStreamLen, maxStreamLen,lineLen,xStep,yStep,streamlines);
    attributeList.setAttribute("grid.width",Fmi::to_string(gwidth));
    attributeList.setAttribute("grid.height",Fmi::to_string(gheight));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridStreamlinesByGrid(uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,std::vector<T::Coordinate>& projectionCoordinates,T::AttributeList& attributeList,T::ByteData_vec& streamlines)
{
  FUNCTION_TRACE
  try
  {
    getGridStreamlinesByGrid(gridWidth,gridHeight,gridLatLonCoordinates,projectionCoordinates,attributeList,0,EMPTY_DOUBLE_VEC,streamlines);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridStreamlinesByGrid(uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,std::vector<T::Coordinate>& projectionCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines)
{
  FUNCTION_TRACE
  try
  {
    if (gridLatLonCoordinates.size() == 0 ||  gridWidth == 0 || gridHeight == 0)
      return;

    short areaInterpolationMethod = T::AreaInterpolationMethod::Nearest;

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("stream.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    int maxStreamLen = 2048;
    const char *maxLengthStr = attributeList.getAttributeValue("stream.maxLength");
    if (maxLengthStr != nullptr)
      maxStreamLen = toInt32(maxLengthStr);

    int minStreamLen = 5;
    const char *minLengthStr = attributeList.getAttributeValue("stream.minLength");
    if (minLengthStr != nullptr)
      minStreamLen = toInt32(minLengthStr);

    int lineLen = 2048;
    const char *lineLengthStr = attributeList.getAttributeValue("stream.lineLength");
    if (lineLengthStr != nullptr)
      lineLen = toInt32(lineLengthStr);

    int xStep = 20;
    const char *xStepStr = attributeList.getAttributeValue("stream.xStep");
    if (xStepStr != nullptr)
      xStep = toInt32(xStepStr);

    int yStep = 20;
    const char *yStepStr = attributeList.getAttributeValue("stream.yStep");
    if (yStepStr != nullptr)
      yStep = toInt32(yStepStr);


    T::ParamValue_vec gridValues;
    getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,gridValues);

    getStreamlines(gridValues,&gridLatLonCoordinates,gridWidth,gridHeight,minStreamLen, maxStreamLen,lineLen,xStep,yStep,streamlines);

    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(gridWidth));
    attributeList.setAttribute("grid.height",Fmi::to_string(gridHeight));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)reverseXDirection()));
    attributeList.setAttribute("stream.coordinateType",Fmi::to_string(coordinateType));
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

T::Coordinate_svec Message::getGridLatLonCoordinates() const
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





uint Message::getGridWidth() const
{
  FUNCTION_TRACE
  try
  {
    return getGridColumnCount();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint Message::getGridHeight() const
{
  FUNCTION_TRACE
  try
  {
    return getGridRowCount();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
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




std::string Message::getGridGeometryLine() const
{
  FUNCTION_TRACE
  try
  {
    std::string str = getGridGeometryString();
    if (str.empty())
      return str;

    std::string s = ";description";
    str.replace(str.find(s),s.length(),";0.000000;0.000000;description");

    return str;
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





float Message::getGridPointAngle(T::CoordinateType coordinateType,double x,double y) const
{
  FUNCTION_TRACE
  try
  {
    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        return getGridPointAngleByLatLonCoordinates(y,x);

      case T::CoordinateTypeValue::GRID_COORDINATES:
      {
        double lat = 0, lon = 0;
        getGridLatLonCoordinatesByGridPosition(x,y,lat,lon);
        return getGridPointAngleByLatLonCoordinates(lat,lon);
      }
      break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
      {
        double lat = 0, lon = 0;
        getGridLatLonCoordinatesByOriginalCoordinates(x,y,lat,lon);
        return getGridPointAngleByLatLonCoordinates(lat,lon);
      }
      break;

      default:
      {
        Fmi::Exception exception(BCP,"Unknow coordinate type!",nullptr);
        exception.addParameter("Coordinate Type",Fmi::to_string(coordinateType));
        throw exception;
      }
    }
    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





float Message::getGridPointAngleByLatLonCoordinates(double lat,double lon)  const
{
  FUNCTION_TRACE
  try
  {
    double PI = 3.1415926536;
    T::Dimensions d = getGridDimensions();
    if (d.getDimensions() != 2)
      return 0;

    double grid_i1 = 0;
    double grid_j1 = 0;
    double grid_i2 = 0;
    double grid_j2 = 0;

    if (getGridPointByLatLonCoordinates(lat,lon,grid_i1,grid_j1)  &&  getGridPointByLatLonCoordinates(lat+0.0001,lon,grid_i2,grid_j2))
    {
      double di = grid_i2-grid_i1;
      double dj = grid_j2-grid_j1;
      double angle = 0;
      double a = atan(fabs(dj)/fabs(di));
/*
      if (reverseYDirection())
        dj = -dj;

      if (reverseXDirection())
        di = -di;
*/
      if (dj >= 0  &&  di >= 0)
      {
        angle = -(PI/2 - a);
      }

      if (dj >= 0  &&  di < 0)
      {
        angle = PI/2 - a;
      }

      if (dj < 0  &&  di >= 0)
      {
        angle = -(PI/2 - a) + PI;
      }

      if (dj < 0  &&  di < 0)
      {
        angle = PI/2 - a + PI;
      }

      return C_FLOAT(angle);
    }

    if (getGridPointByLatLonCoordinates(lat-0.0001,lon,grid_i1,grid_j1)  &&  getGridPointByLatLonCoordinates(lat,lon,grid_i2,grid_j2))
    {
      double di = grid_i2-grid_i1;
      double dj = grid_j2-grid_j1;
      double angle = 0;
      double a = atan(fabs(dj)/fabs(di));

      if (dj >= 0  &&  di >= 0)
      {
        angle = -(PI/2 - a);
      }

      if (dj >= 0  &&  di < 0)
      {
        angle = PI/2 - a;
      }

      if (dj < 0  &&  di >= 0)
      {
        angle = -(PI/2 - a) + PI;
      }

      if (dj < 0  &&  di < 0)
      {
        angle = PI/2 - a + PI;
      }

      return C_FLOAT(angle);
    }

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridPointAngles(std::vector<float>& angles) const
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions d = getGridDimensions();
    if (d.getDimensions() != 2)
      return;

    int geometryId = getGridGeometryId();
    if (geometryId > 0)
    {
      auto it = gridAngleCache.find(geometryId);
      if (it != gridAngleCache.end())
      {
        angles = it->second;
        return;
      }
    }

    angles.clear();
    angles.reserve(d.ny() * d.nx());
    for (uint y=0; y < d.ny(); y++)
    {
      for (uint x=0; x < d.nx(); x++)
      {
        float angle = getGridPointAngle(T::CoordinateTypeValue::GRID_COORDINATES,x,y);
        angles.emplace_back(angle);
      }
    }

    if (geometryId > 0)
      gridAngleCache.insert(std::pair<int,AngleList>(geometryId,angles));
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





T::GribParamId Message::getGribParameterId() const
{
  FUNCTION_TRACE
  try
  {
    return mGribParameterId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grib parameter name.

         \return   The grip parameter name.
*/

const char* Message::getGribParameterName() const
{
  FUNCTION_TRACE
  try
  {
    return stringFactory[mGribParameterName];
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the FMI parameter id.

         \return   The FMI parameter id.
*/

T::FmiParamId Message::getFmiParameterId() const
{
  FUNCTION_TRACE
  try
  {
    return mFmiParameterId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the FMI parameter level id.

         \return   The FMI parameter level id.
*/

T::ParamLevelId Message::getFmiParameterLevelId() const
{
  FUNCTION_TRACE
  try
  {
    return mFmiParameterLevelId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the FMI parameter name.

         \return   The FMI parameter name.
*/

const char* Message::getFmiParameterName() const
{
  FUNCTION_TRACE
  try
  {
    return stringFactory[mFmiParameterName];
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the FMI parameter units.

         \return   The FMI parameter units.
*/

const char* Message::getFmiParameterUnits() const
{
  FUNCTION_TRACE
  try
  {
    return stringFactory[mFmiParameterUnits];
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the newbase parameter id.

         \return   The newbase parameter id.
*/

T::NewbaseParamId Message::getNewbaseParameterId() const
{
  FUNCTION_TRACE
  try
  {
    return mNewbaseParameterId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the newbase parameter name.

         \return   The newbase parameter name.
*/

const char* Message::getNewbaseParameterName() const
{
  FUNCTION_TRACE
  try
  {
    return stringFactory[mNewbaseParameterName];
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the netcdf parameter name.

         \return   The netcdf parameter name.
*/

const char* Message::getNetCdfParameterName() const
{
  FUNCTION_TRACE
  try
  {
    return stringFactory[mNetCdfParameterName];
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the parameter level id.

         \return   The parameter level type (= enum value).
*/


T::ParamLevelId Message::getGridParameterLevelId() const
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





T::ParamValue Message::getGridValueByGridPoint(uint grid_i,uint grid_j,uint modificationOperation,double_vec& modificationParameters) const
{
  FUNCTION_TRACE
  try
  {
    auto value = getGridValueByGridPoint(grid_i,grid_j);

    uint sz = modificationParameters.size();
    if (value == ParamValueMissing || sz == 0)
      return value;

    switch (modificationOperation)
    {
      case Operation::NONE:
        return value;

      case Operation::GRID_ADD:
      {
        auto w = getGridWidth();
        auto h = getGridHeight();
        auto s = w*h;
        auto idx = grid_j * h + grid_i;

        if (sz == s && idx < sz)
        {
          auto val = modificationParameters[idx];
          if (val != ParamValueMissing)
            value = value + val;
        }
      }
      return value;

      case Operation::GRID_DEC:
      {
        auto w = getGridWidth();
        auto h = getGridHeight();
        auto s = w*h;
        auto idx = grid_j * h + grid_i;

        if (sz == s && idx < sz)
        {
          auto val = modificationParameters[idx];
          if (val != ParamValueMissing)
            value = value - val;
        }
      }
      return value;

      case Operation::GRID_MUL:
      {
        auto w = getGridWidth();
        auto h = getGridHeight();
        auto s = w*h;
        auto idx = grid_j * h + grid_i;

        if (sz == s && idx < sz)
        {
          auto val = modificationParameters[idx];
          if (val != ParamValueMissing)
            value = value * val;
        }
      }
      return value;

      case Operation::GRID_DIV:
      {
        auto w = getGridWidth();
        auto h = getGridHeight();
        auto s = w*h;
        auto idx = grid_j * h + grid_i;

        if (sz == s && idx < sz)
        {
          auto val = modificationParameters[idx];
          if (val != ParamValueMissing)
            value = value / val;
        }
      }
      return value;

      case Operation::GRID_HYPOT:
      {
        auto w = getGridWidth();
        auto h = getGridHeight();
        auto s = w*h;
        auto idx = grid_j * h + grid_i;

        if (sz == s && idx < sz)
        {
          auto val = modificationParameters[idx];
          if (val != ParamValueMissing)
            value = sqrt(value*value + val*val);
        }
      }
      return value;

      case Operation::ADD:
        if (sz > 0 && modificationParameters[0] != ParamValueMissing)
          return (value + modificationParameters[0]);
        else
          return value;

      case Operation::DEC:
        if (sz > 0 && modificationParameters[0] != ParamValueMissing)
          return (value - modificationParameters[0]);
        else
          return value;

      case Operation::MUL:
        if (sz > 0 && modificationParameters[0] != ParamValueMissing)
          return (value * modificationParameters[0]);
        else
          return value;

      case Operation::DIV:
        if (sz > 0 && modificationParameters[0] != ParamValueMissing)
          return (value / modificationParameters[0]);
        else
          return value;

      case Operation::ABS:
        if (value < 0)
          return -value;
        else
          return value;

      case Operation::NEG:
        return -value;

      case Operation::ROUND:
        return round(value);

      case Operation::FLOOR:
        return Fmi::floor(value);

      case Operation::CEIL:
        return (Fmi::floor(value) + 1.0);

      case Operation::K2C:
        return (value - 273.15);

      case Operation::C2K:
        return (value + 273.15);

      case Operation::F2C:
        return (5*(value - 32.0)/9.0);

      case Operation::C2F:
        return (value*1.8 + 32.0);

      case Operation::F2K:
        return ((5.0*(value - 32.0)/9.0) + 273.15);

      case Operation::K2F:
        return ((value - 273.15)*1.8 + 32.0);

      case Operation::RAD2DEG:
        return (360.0*value/(2*3.1415926535898));

      case Operation::DEG2RAD:
        return (2*3.1415926535898*value/360.0);
    }
    return value;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





T::ParamValue Message::countAverageValue() const
{
  FUNCTION_TRACE
  try
  {
    T::ParamValue_vec values;
    getGridValueVector(values);

    double sum = 0;
    double count = 0;
    double totalArea = 0;

    uint w = getGridWidth();
    uint h = getGridHeight();
    uint c = 0;
    for (uint y=0; y<h; y++)
    {
      double lat1,lon1,lat2,lon2,lat3,lon3,lat4,lon4;
      getGridLatLonCoordinatesByGridPoint(0,y,lat1,lon1);
      getGridLatLonCoordinatesByGridPoint(1,y,lat2,lon2);
      getGridLatLonCoordinatesByGridPoint(0,y+1,lat3,lon3);
      getGridLatLonCoordinatesByGridPoint(1,y+1,lat4,lon4);

      double ww = (latlon_distance(lat1,lon1,lat2,lon2) + latlon_distance(lat3,lon3,lat4,lon4))/2;
      double hh = latlon_distance(lat1,lon1+(lon2-lon1),lat3,lon3+(lon4-lon3));
      double area = ww*hh;

      for (uint x = 0; x<w; x++)
      {
        double val = values[c];
        if (val != ParamValueMissing)
        {
          sum = sum + val*area;
          totalArea = totalArea + area;
          count = count + 1;
        }
        c++;
      }
    }

    if (count > 0)
      return (sum / totalArea);

    return ParamValueMissing;
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
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





void Message::modifyGridValueVector(uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  try
  {
    uint vsz = values.size();
    if (vsz == 0)
      return;

    uint sz = modificationParameters.size();
    if (sz == 0)
      return;

    switch (modificationOperation)
    {
      case Operation::NONE:
        return;

      case Operation::GRID_ADD:
        if (sz == vsz)
        {
          for (uint v=0; v<vsz; v++)
          {
            if (modificationParameters[v] != ParamValueMissing  &&  values[v] != ParamValueMissing)
              values[v] = values[v] + modificationParameters[v];
          }
        }
        return;

      case Operation::GRID_DEC:
        if (sz == vsz)
        {
          for (uint v=0; v<vsz; v++)
          {
            if (modificationParameters[v] != ParamValueMissing  &&  values[v] != ParamValueMissing)
              values[v] = values[v] - modificationParameters[v];
          }
        }
        return;

      case Operation::GRID_MUL:
        if (sz == vsz)
        {
          for (uint v=0; v<vsz; v++)
          {
            if (modificationParameters[v] != ParamValueMissing  &&  values[v] != ParamValueMissing)
              values[v] = values[v] * modificationParameters[v];
          }
        }
        return;

      case Operation::GRID_DIV:
        if (sz == vsz)
        {
          for (uint v=0; v<vsz; v++)
          {
            if (modificationParameters[v] != ParamValueMissing  &&  values[v] != ParamValueMissing)
              values[v] = values[v] / modificationParameters[v];
          }
        }
        return;

      case Operation::GRID_HYPOT:
        if (sz == vsz)
        {
          for (uint v=0; v<vsz; v++)
          {
            if (modificationParameters[v] != ParamValueMissing  &&  values[v] != ParamValueMissing)
              values[v] = sqrt(values[v]*values[v] + modificationParameters[v]*modificationParameters[v]);
          }
        }
        return;

      case Operation::ADD:
        if (sz > 0 && modificationParameters[0] != ParamValueMissing)
        {
          auto val = modificationParameters[0];
          for (uint v=0; v<vsz; v++)
          {
            values[v] = values[v] + val;
          }
        }
        return;

      case Operation::DEC:
        if (sz > 0 && modificationParameters[0] != ParamValueMissing)
        {
          auto val = modificationParameters[0];
          for (uint v=0; v<vsz; v++)
          {
            values[v] = values[v] - val;
          }
        }
        return;

      case Operation::MUL:
        if (sz > 0 && modificationParameters[0] != ParamValueMissing)
        {
          auto val = modificationParameters[0];
          for (uint v=0; v<vsz; v++)
          {
            values[v] = values[v] * val;
          }
        }
        return;

      case Operation::DIV:
        if (sz > 0 && modificationParameters[0] != ParamValueMissing)
        {
          auto val = modificationParameters[0];
          for (uint v=0; v<vsz; v++)
          {
            values[v] = values[v] / val;
          }
        }
        return;

      case Operation::ABS:
        for (uint v=0; v<vsz; v++)
        {
          values[v] = fabs(values[v]);
        }
        return;

      case Operation::NEG:
        for (uint v=0; v<vsz; v++)
        {
          values[v] = -values[v];
        }
        return;

      case Operation::ROUND:
        for (uint v=0; v<vsz; v++)
        {
          values[v] = round(values[v]);
        }
        return;

      case Operation::FLOOR:
        for (uint v=0; v<vsz; v++)
        {
          values[v] = Fmi::floor(values[v]);
        }
        return;

      case Operation::CEIL:
        for (uint v=0; v<vsz; v++)
        {
          values[v] = Fmi::floor(values[v]) + 1.0;
        }
        return;

      case Operation::K2C:
        for (uint v=0; v<vsz; v++)
        {
          values[v] = values[v] - 273.15;
        }
        return;

      case Operation::C2K:
        for (uint v=0; v<vsz; v++)
        {
          values[v] = values[v] + 273.15;
        }
        return;

      case Operation::F2C:
        for (uint v=0; v<vsz; v++)
        {
          values[v] = (5*(values[v] - 32.0)/9.0);
        }
        return;

      case Operation::C2F:
        for (uint v=0; v<vsz; v++)
        {
          values[v] = (values[v]*1.8 + 32.0);
        }
        return;

      case Operation::F2K:
        for (uint v=0; v<vsz; v++)
        {
          values[v] = ((5.0*(values[v] - 32.0)/9.0) + 273.15);
        }
        return;

      case Operation::K2F:
        for (uint v=0; v<vsz; v++)
        {
          values[v] = ((values[v] - 273.15)*1.8 + 32.0);
        }
        return;

      case Operation::RAD2DEG:
      {
        double m = 360.0/(2*3.1415926535898);
        for (uint v=0; v<vsz; v++)
        {
          values[v] = (m*values[v]);
        }
      }
      return;

      case Operation::DEG2RAD:
      {
        double m = (2*3.1415926535898/360.0);
        for (uint v=0; v<vsz; v++)
        {
          values[v] = (m*values[v]);
        }
      }
      return;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void Message::getGridValueVector(uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  try
  {
    getGridValueVector(values);
    modifyGridValueVector(modificationOperation,modificationParameters,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns grid values according to the geometry defined by attributes.

        \param attributeList   The list of attributes that should contain geometry definitions.
        \param values          The returned grid values.
*/

void Message::getGridValueVectorByGeometry(T::AttributeList& attributeList,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByGeometry(attributeList,0,EMPTY_DOUBLE_VEC,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridValueVectorByGeometry(T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    const char *crsStr = attributeList.getAttributeValue("grid.crs");

    if (crsStr != nullptr &&  strcasecmp(crsStr,"crop") == 0)
    {
      getGridValueVectorByCrop(attributeList,modificationOperation,modificationParameters,values);
      return;
    }

    const char *llboxStr = attributeList.getAttributeValue("grid.llbox");
    const char *gridSizeStr = attributeList.getAttributeValue("grid.size");
    const char *centerStr = attributeList.getAttributeValue("grid.center");

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *s = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (s != nullptr)
      areaInterpolationMethod = toInt16(s);

    if (gridSizeStr != nullptr)
    {
      double m = toDouble(gridSizeStr);
      if (m > 0)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(C_INT(C_DOUBLE(getGridWidth())*m)));
        attributeList.setAttribute("grid.height",Fmi::to_string(C_INT(C_DOUBLE(getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
      const char *gridHeightStr = attributeList.getAttributeValue("grid.height");
      if ((gridWidthStr == nullptr || gridHeightStr == nullptr) &&  centerStr == nullptr)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(getGridWidth()));
        attributeList.setAttribute("grid.height",Fmi::to_string(getGridHeight()));
      }

      attributeList.setAttribute("grid.crs",getWKT());
      attributeList.setAttribute("grid.proj4",getProj4());
      T::Dimensions  d = getGridDimensions();

      if (llboxStr == nullptr  &&  centerStr == nullptr)
      {
        double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
        uint px1 = 0,py1 = 0,px2 = d.nx()-1,py2 = d.ny()-1;

        if (reverseYDirection())
          px1 = 0,py1 = d.ny()-1,px2 = d.nx()-1,py2 = 0;

        char tmp[100];
        if (getGridLatLonCoordinatesByGridPoint(px1,py1,y1,x1)  &&  getGridLatLonCoordinatesByGridPoint(px2,py2,y2,x2))
        {
          if (x2 < x1  &&  x2 < 0)
            x2 += 360;

          if (x2 < x1  && x1 >= 180)
            x1 -= 360;

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          attributeList.setAttribute("grid.llbox",tmp);
          if (getGridProjection() == T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }

        if (getGridOriginalCoordinatesByGridPoint(0,0,x1,y1)  &&  getGridOriginalCoordinatesByGridPoint(d.nx()-1,d.ny()-1,x2,y2))
        {
          if (getGridProjection() == T::GridProjectionValue::LatLon)
          {
            if (x2 < x1  &&  x2 < 0)
              x2 += 360;

            if (x2 < x1  && x1 >= 180)
              x1 -= 360;
          }

          if (reverseYDirection())
          {
            double tmp = y1;
            y1 = y2;
            y2 = tmp;
          }

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          if (getGridProjection() != T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }
      }

      if (llboxStr == nullptr &&  centerStr != nullptr)
      {
        // The crop area is defined by a rectangle and its latlon center coordinates.

        std::vector<double> a;
        splitString(centerStr,',',a);
        if (a.size() != 2)
          return;

        const char *metricWidthStr = attributeList.getAttributeValue("grid.metricWidth");
        const char *metricHeightStr = attributeList.getAttributeValue("grid.metricHeight");

        if (metricWidthStr != nullptr &&  metricHeightStr != nullptr)
        {
          double centerX = a[0];
          double centerY = a[1];

          double mWidth = toDouble(metricWidthStr) * 1000;   // km => m
          double mHeight = toDouble(metricHeightStr) * 1000; // km => m

          double lon1 = 0,lat1 = 0,lon2 = 0, lat2 =0;

          latLon_bboxByCenter(centerX,centerY,mWidth,mHeight,lon1,lat1,lon2,lat2);

          char tmp[200];
          sprintf(tmp,"%f,%f,%f,%f",lon1,lat1,lon2,lat2);
          attributeList.setAttribute("grid.llbox",tmp);
        }
      }

      attributeList.setAttribute("grid.projectionType",Fmi::to_string(getGridProjection()));
    }

    attributeList.setAttribute("grid.original.crs",getWKT());
    attributeList.setAttribute("grid.original.proj4",getProj4());
    attributeList.setAttribute("grid.original.width",Fmi::to_string(getGridWidth()));
    attributeList.setAttribute("grid.original.height",Fmi::to_string(getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)reverseXDirection()));
    attributeList.setAttribute("grid.original.projectionType",Fmi::to_string(getGridProjection()));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));

    double wm = 0;
    double hm = 0;
    if (getGridMetricCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
    else
    {
      attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

      getGridCellAverageSize(wm,hm);
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }


    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");

    if (geometryIdStr != nullptr  &&  getGridGeometryId() == toInt32(geometryIdStr))
    {
      // The geometryId is same as the original geometry.

      getGridValueVector(modificationOperation,modificationParameters,values);
      T::Dimensions  d = getGridDimensions();
      attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
      attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
      return;
    }

    uint width = 0;
    uint height = 0;
    T::Coordinate_svec latLonCoordinates;

    Identification::gridDef.getGridLatLonCoordinatesByGeometry(attributeList,latLonCoordinates,width,height);

    if (!latLonCoordinates || latLonCoordinates->size() == 0)
    {
      getGridValueVector(modificationOperation,modificationParameters,values);
      T::Dimensions  d = getGridDimensions();
      attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
      attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
      return;
    }


    //T::ParamValue_vec gridValues;
    getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,*latLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,values);

    attributeList.setAttribute("grid.width",Fmi::to_string(width));
    attributeList.setAttribute("grid.height",Fmi::to_string(height));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridValueVectorByCrop(T::AttributeList& attributeList,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByCrop(attributeList,0,EMPTY_DOUBLE_VEC,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridValueVectorByCrop(T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    double x1 = 0;
    double y1 = 0;
    double x2 = 0;
    double y2 = 0;

    const char *llboxStr = attributeList.getAttributeValue("grid.llbox");
    const char *centerStr = attributeList.getAttributeValue("grid.center");
    const char *borderStr = attributeList.getAttributeValue("grid.border");

    if (llboxStr != nullptr)
    {
      // The crop area is defined by a latlon bounding box.

      std::vector<double> a;
      splitString(llboxStr,',',a);

      if (a.size() != 4)
        return;

      getGridPointByLatLonCoordinates(a[1],a[0],x1,y1);
      getGridPointByLatLonCoordinates(a[3],a[2],x2,y2);
    }
    else
    if (centerStr != nullptr)
    {
      // The crop area is defined by a rectangle and its latlon center coordinates.

      std::vector<double> a;
      splitString(centerStr,',',a);
      if (a.size() != 2)
        return;

      const char *metricWidthStr = attributeList.getAttributeValue("grid.metricWidth");
      const char *metricHeightStr = attributeList.getAttributeValue("grid.metricHeight");

      if (metricWidthStr != nullptr &&  metricHeightStr != nullptr)
      {
        double centerX = a[0];
        double centerY = a[1];

        double mWidth = toDouble(metricWidthStr) * 1000;   // km => m
        double mHeight = toDouble(metricHeightStr) * 1000; // km => m

        double lon1 = 0,lat1 = 0,lon2 = 0, lat2 =0;

        latLon_bboxByCenter(centerX,centerY,mWidth,mHeight,lon1,lat1,lon2,lat2);

        // Converting latlon coordinates to grid points.

        getGridPointByLatLonCoordinates(lat1,lon1,x1,y1);
        getGridPointByLatLonCoordinates(lat2,lon2,x2,y2);

        char tmp[200];
        sprintf(tmp,"%f,%f,%f,%f",lon1,lat1,lon2,lat2);
        attributeList.setAttribute("grid.crop.llbox",tmp);
      }
    }
    else
      return;


    if (borderStr != nullptr &&  strcasecmp(borderStr,"outer") == 0)
    {
      x1 = C_DOUBLE(Fmi::floor(x1));
      y1 = C_DOUBLE(Fmi::floor(y1));
      x2 = C_DOUBLE(Fmi::ceil(x2));
      y2 = C_DOUBLE(Fmi::ceil(y2));
    }

    T::Dimensions d = getGridDimensions();
    double w = d.nx();
    double h = d.ny();

    if (x1 < 0)
      x1 = 0;

    if (y1 < 0)
      y1 = 0;

    if (x2 < 0)
      x2 = 0;

    if (y2 < 0)
      y2 = 0;

    if (x2 >= w)
      x2 = w-1;

    if (y2 >= h)
      y2 = h-1;

    // printf("Points %f,%f,%f,%f\n",x1,y1,x2,y2);

    bool gridRectangle = true;
    T::GridValueList valueList;

    // Picking grid points that are inside the rectangle.
    getGridValueListByRectangle(T::CoordinateTypeValue::GRID_COORDINATES,x1,y1,x2,y2,gridRectangle,modificationOperation,modificationParameters,valueList);

    double minX = 0;
    double minY = 0;
    double maxX = 0;
    double maxY = 0;
    valueList.getGridValueArea(minX,minY,maxX,maxY);

    // printf("ValueAREA %f,%f,%f,%f  %d\n",minX,minY,maxX,maxY,valueList.getLength());

    int width = C_INT(round(maxX-minX+1));
    int height = C_INT(round(maxY-minY+1));
    uint size = valueList.getLength();

    values.reserve(size);
    for (uint t=0; t<size; t++)
    {
      T::GridValue *val = valueList.getGridValuePtrByIndex(t);
      if (val != nullptr)
        values.emplace_back(val->mValue);
      else
        values.emplace_back(ParamValueMissing);
    }

    attributeList.setAttribute("grid.original.crs",getWKT());
    attributeList.setAttribute("grid.original.proj4",getProj4());
    attributeList.setAttribute("grid.original.width",Fmi::to_string(getGridWidth()));
    attributeList.setAttribute("grid.original.height",Fmi::to_string(getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)isGridGlobal()));
    attributeList.setAttribute("grid.original.projectionType",Fmi::to_string(getGridProjection()));
    attributeList.setAttribute("grid.projectionType",Fmi::to_string(getGridProjection()));
    attributeList.setAttribute("grid.width",Fmi::to_string(width));
    attributeList.setAttribute("grid.height",Fmi::to_string(height));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)reverseXDirection()));

    T::GridValue *first = valueList.getGridValuePtrByIndex(0);
    T::GridValue *last = valueList.getGridValuePtrByIndex(size-1);

    uint ww = C_UINT(w);
    if (first != nullptr && last != nullptr)
    {
      double lat1 = 0;
      double lon1 = 0;
      double lat2 = 0;
      double lon2 = 0;
      getGridLatLonCoordinatesByGridPoint(C_UINT(first->mX) % ww,C_UINT(first->mY),lat1,lon1);
      getGridLatLonCoordinatesByGridPoint(C_UINT(last->mX) % ww,C_UINT(last->mY),lat2,lon2);

      double xx1 = 0;
      double yy1 = 0;
      double xx2 = 0;
      double yy2 = 0;
      getGridOriginalCoordinatesByGridPoint(C_UINT(first->mX) % ww,C_UINT(first->mY),xx1,yy1);
      getGridOriginalCoordinatesByGridPoint(C_UINT(last->mX) % ww,C_UINT(last->mY),xx2,yy2);

      char tmp[200];
      sprintf(tmp,"%f,%f,%f,%f",lon1,lat1,lon2,lat2);
      attributeList.setAttribute("grid.crop.llbox",tmp);

      sprintf(tmp,"%f,%f,%f,%f",xx1,yy1,xx2,yy2);
      attributeList.setAttribute("grid.crop.bbox",tmp);
    }

    double wm = 0;
    double hm = 0;
    if (getGridMetricCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.cell.height",Fmi::to_string(hm));
    }
    else
    {
      attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

      getGridCellAverageSize(wm,hm);
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns all grid data values so that these values are cached.

        \param values   The returned grid values.
*/

void Message::getGridValueVectorWithCaching(T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    AutoThreadLock lock(&mThreadLock);

    uint fileId = getFileId();
    uint messageIndex = getMessageIndex();

    // ### Seaching data from the temporary cache
    if (fileId > 0)
    {
      AutoThreadLock lock(&tmpCacheThreadLock);
      for (uint t=0; t<tmpValueCacheSize; t++)
      {
        if (tmpValueCache[t].fileId ==  fileId  &&  tmpValueCache[t].messageIndex == messageIndex  &&  tmpValueCache[t].hash == 0)
        {
          values = tmpValueCache[t].values;
          return;
        }
      }
    }

    // ### Fetching data
    getGridValueVector(values);

    // ### Adding data into the temporary cache

    if (fileId > 0)
    {
      AutoThreadLock lock(&tmpCacheThreadLock);
      tmpValueCachePos++;
      uint idx = tmpValueCachePos % tmpValueCacheSize;
      tmpValueCache[idx].hash = 0;
      tmpValueCache[idx].values = values;
      tmpValueCache[idx].fileId = fileId;
      tmpValueCache[idx].messageIndex = messageIndex;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void Message::getGridValueVectorWithCaching(uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorWithCaching(values);
    modifyGridValueVector(modificationOperation,modificationParameters,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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




void Message::getSectionPositions(std::set<T::FilePosition>& positions)
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}




/*! \brief The method returns the default area interpolation method

        \return   The default area interpolation method.
*/

short Message::getDefaultInterpolationMethod() const
{
  FUNCTION_TRACE
  try
  {
    return mDefaultInterpolationMethod;
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





/*! \brief The method is used for setting a value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(uint propertyId,char value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyId,C_INT64(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(uint propertyId,short value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyId,C_INT64(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(uint propertyId,int value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyId,C_INT64(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(uint propertyId,long value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyId,C_INT64(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(uint propertyId,unsigned char value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyId,C_INT64(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(uint propertyId,unsigned short value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyId,C_INT64(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(uint propertyId,unsigned int value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyId,C_INT64(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(uint propertyId,unsigned long value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyId,C_INT64(value));
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

bool Message::setProperty(uint propertyId,long long value)
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method is used for setting a (double) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(uint propertyId,double value)
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method is used for fetching a (long long) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the requested property is returned in this parameter.
        \return            The method returns true if the value of the requested property was found.
*/

bool Message::getProperty(uint propertyId,long long& value)
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method is used for fetching a (long long) value for the property according to the property name.

        \param propertyName  The unique name of the requested property.
        \param value         The value of the requested property is returned in this parameter.
        \return              The method returns true if the value of the requested property was found.
*/

bool Message::getProperty(const char *propertyName,long long& value)
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method is used for setting a value for the property according to the property name.

        \param propertyName  The unique name of the requested property.
        \param value         The value of the property to be set.
        \return              The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(const char *propertyName,char value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyName,C_INT64(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a value for the property according to the property name.

        \param propertyName  The unique name of the requested property.
        \param value         The value of the property to be set.
        \return              The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(const char *propertyName,short value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyName,C_INT64(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a value for the property according to the property name.

        \param propertyName  The unique name of the requested property.
        \param value         The value of the property to be set.
        \return              The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(const char *propertyName,int value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyName,C_INT64(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a value for the property according to the property name.

        \param propertyName  The unique name of the requested property.
        \param value         The value of the property to be set.
        \return              The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(const char *propertyName,long value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyName,C_INT64(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a value for the property according to the property name.

        \param propertyName  The unique name of the requested property.
        \param value         The value of the property to be set.
        \return              The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(const char *propertyName,unsigned char value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyName,C_INT64(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a value for the property according to the property name.

        \param propertyName  The unique name of the requested property.
        \param value         The value of the property to be set.
        \return              The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(const char *propertyName,unsigned short value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyName,C_INT64(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a value for the property according to the property name.

        \param propertyName  The unique name of the requested property.
        \param value         The value of the property to be set.
        \return              The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(const char *propertyName,unsigned int value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyName,C_INT64(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a value for the property according to the property name.

        \param propertyName  The unique name of the requested property.
        \param value         The value of the property to be set.
        \return              The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(const char *propertyName,unsigned long value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyName,C_INT64(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a (long long) value for the property according to the property name.

        \param propertyName  The unique name of the requested property.
        \param value         The value of the property to be set.
        \return              The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(const char *propertyName,long long value)
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method is used for setting a (double) value for the property according to the property name.

        \param propertyName  The unique name of the requested property.
        \param value         The value of the property to be set.
        \return              The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(const char *propertyName,double value)
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method sets the value of the 'mFmiParameterId' member attribute.

        \param fmiParameterId   The new value for the member attribute.
*/

void Message::setFmiParameterId(T::FmiParamId fmiParameterId)
{
  FUNCTION_TRACE
  try
  {
    mFmiParameterId = fmiParameterId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the value of the 'mFmiParameterLevelId' member attribute.

        \param fmiParameterLevelId   The new value for the member attribute.
*/

void Message::setFmiParameterLevelId(T::ParamLevelId fmiParameterLevelId)
{
  FUNCTION_TRACE
  try
  {
    mFmiParameterLevelId = fmiParameterLevelId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the value of the 'mFmiParameterName' member attribute.

        \param fmiParameterName   The new value for the member attribute.
*/

void Message::setFmiParameterName(const char *fmiParameterName)
{
  FUNCTION_TRACE
  try
  {
    mFmiParameterName = stringFactory.create(fmiParameterName);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the value of the 'mFmiParameterUnits' member attribute.

        \param fmiParameterUnits   The new value for the member attribute.
*/

void Message::setFmiParameterUnits(const char *fmiParameterUnits)
{
  FUNCTION_TRACE
  try
  {
    mFmiParameterUnits = stringFactory.create(fmiParameterUnits);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the value of the 'mGribParameterId' member attribute.

        \param gribParameterId   The new value for the member attribute.
*/

void Message::setGribParameterId(T::GribParamId gribParameterId)
{
  FUNCTION_TRACE
  try
  {
    mGribParameterId = gribParameterId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the value of the 'mGribParameterName' member attribute.

        \param gribParameterName   The new value for the member attribute.
*/

void Message::setGribParameterName(const char *gribParameterName)
{
  FUNCTION_TRACE
  try
  {
    mGribParameterName = stringFactory.create(gribParameterName);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the value of the 'mGribParameterUnits' member attribute.

        \param gribParameterUnits   The new value for the member attribute.
*/

void Message::setGribParameterUnits(const char *gribParameterUnits)
{
  FUNCTION_TRACE
  try
  {
    mGribParameterUnits = stringFactory.create(gribParameterUnits);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the value of the 'mNewbaseParameterId' member attribute.

        \param newbaseParameterId   The new value for the member attribute.
*/

void Message::setNewbaseParameterId(T::NewbaseParamId newbaseParameterId)
{
  FUNCTION_TRACE
  try
  {
    mNewbaseParameterId = newbaseParameterId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the value of the 'mNewbaseParameterName' member attribute.

        \param newbaseParameterName   The new value for the member attribute.
*/

void Message::setNewbaseParameterName(const char *newbaseParameterName)
{
  FUNCTION_TRACE
  try
  {
    mNewbaseParameterName = stringFactory.create(newbaseParameterName);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the value of the 'mNetCdfParameterName' member attribute.

        \param netCdfParameterName   The new value for the member attribute.
*/

void Message::setNetCdfParameterName(const char *netCdfParameterName)
{
  FUNCTION_TRACE
  try
  {
    mNetCdfParameterName = stringFactory.create(netCdfParameterName);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the value of the given grid coordinates.

        \param coordinateType            The type of the used coordinates.
        \param x                         The x-coordinate (longitude when using latlon)
        \param y                         The y-coordinate (latitude when using latlon)
        \param areaInterpolationMethod   The area interpolation method.
        \param value                     The value of the grid point is returned in this parameter.
*/

void Message::getGridValueByPoint(T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,T::ParamValue& value) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,0,EMPTY_DOUBLE_VEC,value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridValueByPoint(T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue& value) const
{
  FUNCTION_TRACE
  try
  {
    value = ParamValueMissing;
    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        value = getGridValueByLatLonCoordinate(y,x,areaInterpolationMethod,modificationOperation,modificationParameters);
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        value = getGridValueByGridPoint_byInterpolation(x,y,areaInterpolationMethod,modificationOperation,modificationParameters);
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
         // TODO: Implementation required
         break;

      default:
      {
        Fmi::Exception exception(BCP,"Unknow coordinate type!",nullptr);
        exception.addParameter("Coordinate Type",Fmi::to_string(coordinateType));
        throw exception;
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



/*! \brief The method returns the value vector related to the given grid coordinates (for example grid corner values).

        \param coordinateType  The type of the used coordinates.
        \param x               The x-coordinate (longitude when using latlon)
        \param y               The y-coordinate (latitude when using latlon)
        \param vectorType      The type of the requested value vector.
        \param value           The value vector is returned in this parameter.
*/

void Message::getGridValueVectorByPoint(T::CoordinateType coordinateType,double x,double y,uint vectorType,double_vec& valueVector) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByPoint(coordinateType,x,y,vectorType,0,EMPTY_DOUBLE_VEC,valueVector);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridValueVectorByPoint(T::CoordinateType coordinateType,double x,double y,uint vectorType,uint modificationOperation,double_vec& modificationParameters,double_vec& valueVector) const
{
  FUNCTION_TRACE
  try
  {
    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        getGridValueVectorByLatLonCoordinate(y,x,vectorType,modificationOperation,modificationParameters,valueVector);
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        getGridValueVectorByGridPoint(x,y,vectorType,modificationOperation,modificationParameters,valueVector);
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
         // TODO: Implementation required
         break;

      default:
      {
        Fmi::Exception exception(BCP,"Unknow coordinate type!",nullptr);
        exception.addParameter("Coordinate Type",Fmi::to_string(coordinateType));
        throw exception;
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the value vector related to the given grid position (for example grid corner values).

        \param x               The x-coordinate (longitude when using latlon)
        \param y               The y-coordinate (latitude when using latlon)
        \param vectorType      The type of the requested value vector.
        \param value           The value vector is returned in this parameter.
*/

void Message::getGridValueVectorByGridPoint(double grid_i,double grid_j,uint vectorType,double_vec& valueVector) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByGridPoint(grid_i,grid_j,vectorType,0,EMPTY_DOUBLE_VEC,valueVector);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridValueVectorByGridPoint(double grid_i,double grid_j,uint vectorType,uint modificationOperation,double_vec& modificationParameters,double_vec& valueVector) const
{
  FUNCTION_TRACE
  try
  {
    double x = grid_i;
    double y = grid_j;

    uint x1 = C_UINT(Fmi::floor(x));
    uint y1 = C_UINT(Fmi::floor(y));
    uint x2 = x1+1;
    uint y2 = y1+1;

    switch (vectorType)
    {
      case T::AreaInterpolationMethod::None:
        valueVector.emplace_back(getGridValueByGridPoint(x1,y1,modificationOperation,modificationParameters));
        break;

      case T::AreaInterpolationMethod::Linear:
        valueVector.emplace_back(getGridValueByGridPoint_linearInterpolation(x,y,modificationOperation,modificationParameters));
        break;

      case T::AreaInterpolationMethod::Nearest:
        valueVector.emplace_back(getGridValueByGridPoint_nearest(x,y,modificationOperation,modificationParameters));
        break;

      case T::AreaInterpolationMethod::Min:
        valueVector.emplace_back(getGridValueByGridPoint_min(x,y,modificationOperation,modificationParameters));
        break;

      case T::AreaInterpolationMethod::Max:
        valueVector.emplace_back(getGridValueByGridPoint_max(x,y,modificationOperation,modificationParameters));
        break;

      case T::AreaInterpolationMethod::List:
        valueVector.emplace_back(2);
        valueVector.emplace_back(x-C_DOUBLE(x1));
        valueVector.emplace_back(y-C_DOUBLE(y1));
        valueVector.emplace_back(getGridValueByGridPoint(x1,y1,modificationOperation,modificationParameters));
        valueVector.emplace_back(getGridValueByGridPoint(x2,y1,modificationOperation,modificationParameters));
        valueVector.emplace_back(getGridValueByGridPoint(x2,y2,modificationOperation,modificationParameters));
        valueVector.emplace_back(getGridValueByGridPoint(x1,y2,modificationOperation,modificationParameters));
        break;

      case T::AreaInterpolationMethod::ListWithAngles:
        valueVector.emplace_back(7);
        valueVector.emplace_back(x-C_DOUBLE(x1));
        valueVector.emplace_back(y-C_DOUBLE(y1));
        valueVector.emplace_back(getGridPointAngle(T::CoordinateTypeValue::GRID_COORDINATES,grid_i,grid_j));
        valueVector.emplace_back(getGridPointAngle(T::CoordinateTypeValue::GRID_COORDINATES,C_DOUBLE(x1),C_DOUBLE(y1)));
        valueVector.emplace_back(getGridPointAngle(T::CoordinateTypeValue::GRID_COORDINATES,C_DOUBLE(x2),C_DOUBLE(y1)));
        valueVector.emplace_back(getGridPointAngle(T::CoordinateTypeValue::GRID_COORDINATES,C_DOUBLE(x2),C_DOUBLE(y2)));
        valueVector.emplace_back(getGridPointAngle(T::CoordinateTypeValue::GRID_COORDINATES,C_DOUBLE(x1),C_DOUBLE(y2)));
        valueVector.emplace_back(getGridValueByGridPoint(x1,y1,modificationOperation,modificationParameters));
        valueVector.emplace_back(getGridValueByGridPoint(x2,y1,modificationOperation,modificationParameters));
        valueVector.emplace_back(getGridValueByGridPoint(x2,y2,modificationOperation,modificationParameters));
        valueVector.emplace_back(getGridValueByGridPoint(x1,y2,modificationOperation,modificationParameters));
        break;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the value vector related to the given grid latlon coordinates.

        \param lat             The latitude of the coordinates
        \param lon             The longitude of the coordinates
        \param vectorType      The type of the requested value vector.
        \param value           The value vector is returned in this parameter.
*/

void Message::getGridValueVectorByLatLonCoordinate(double lat,double lon,uint vectorType,double_vec& valueVector) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByLatLonCoordinate(lat,lon,vectorType,0,EMPTY_DOUBLE_VEC,valueVector);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridValueVectorByLatLonCoordinate(double lat,double lon,uint vectorType,uint modificationOperation,double_vec& modificationParameters,double_vec& valueVector) const
{
  FUNCTION_TRACE
  try
  {
    double grid_i = 0;
    double grid_j = 0;

    if (getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j))
      getGridValueVectorByGridPoint(grid_i,grid_j,vectorType,modificationOperation,modificationParameters,valueVector);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns a list of grid point values that are inside the given circle.

        \param coordinateType    The type of the used coordinates.
        \param origoX            The x-coordinate (longitude when using latlon) of the origo
        \param origoY            The y-coordinate (latitude when using latlon) of the origo
        \param radius            The radius of the circle.
        \param valueList         The list of grid point values are returned in this parameter.
*/

void Message::getGridValueListByCircle(T::CoordinateType coordinateType,double origoX,double origoY,double radius,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByCircle(coordinateType,origoX,origoY,radius,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridValueListByCircle(T::CoordinateType coordinateType,double origoX,double origoY,double radius,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions d = getGridDimensions();
    uint cols = d.nx();
    uint rows = d.ny();

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
      {
        double x1 = origoX;
        double dist = 0;
        while (dist < radius)
        {
          dist = latlon_distance(origoY,origoX,origoY,x1);
          x1 = x1 - 0.01;
        }

        double x2 = origoX;
        dist = 0;
        while (dist < radius)
        {
          dist = latlon_distance(origoY,origoX,origoY,x2);
          x2 = x2 + 0.01;
        }

        double y1 = origoY;
        dist = 0;
        while (dist < radius)
        {
          dist = latlon_distance(origoY,origoX,y1,origoX);
          y1 = y1 - 0.01;
        }

        double y2 = origoY;
        dist = 0;
        while (dist < radius)
        {
          dist = latlon_distance(origoY,origoX,y2,origoX);
          y2 = y2 + 0.01;
        }

        std::vector<T::Coordinate> polygonPoints;
        polygonPoints.emplace_back(T::Coordinate(x1,y1));
        polygonPoints.emplace_back(T::Coordinate(x2,y1));
        polygonPoints.emplace_back(T::Coordinate(x2,y2));
        polygonPoints.emplace_back(T::Coordinate(x1,y2));

        T::GridValueList tmpValueList;
        getGridValueListByPolygon(coordinateType,polygonPoints,modificationOperation,modificationParameters,tmpValueList);

        uint len = tmpValueList.getLength();
        for (uint t=0; t<len; t++)
        {
          T::GridValue rec;
          if (tmpValueList.getGridValueByIndex(t,rec))
          {
            if (latlon_distance(origoY,origoX,rec.mY,rec.mX) <= radius)
              valueList.addGridValue(rec);
          }
        }
      }
      break;


      case T::CoordinateTypeValue::GRID_COORDINATES:
      {
        std::vector<T::Point> gridPoints;

        getPointsInsideCircle(cols,rows,origoX,origoY,radius,gridPoints);
        for (auto it=gridPoints.begin(); it != gridPoints.end(); ++it)
        {
          T::GridValue rec;

          rec.mX = it->x();
          rec.mY = it->y();
          rec.mValue = getGridValueByGridPoint(it->x(),it->y(),modificationOperation,modificationParameters);
          valueList.addGridValue(rec);
        }
      }
      break;


      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
      {
        double newOrigoX = 0;
        double newOrigoY = 0;

        getGridLatLonCoordinatesByOriginalCoordinates(origoX,origoY,newOrigoY,newOrigoX);

        double x1 = newOrigoX;
        double dist = 0;
        while (dist < radius)
        {
          dist = latlon_distance(newOrigoY,newOrigoX,newOrigoY,x1);
          x1 = x1 - 0.01;
        }

        double x2 = newOrigoX;
        dist = 0;
        while (dist < radius)
        {
          dist = latlon_distance(newOrigoY,newOrigoX,newOrigoY,x2);
          x2 = x2 + 0.01;
        }

        double y1 = newOrigoY;
        dist = 0;
        while (dist < radius)
        {
          dist = latlon_distance(newOrigoY,newOrigoX,y1,newOrigoX);
          y1 = y1 - 0.01;
        }

        double y2 = newOrigoY;
        dist = 0;
        while (dist < radius)
        {
          dist = latlon_distance(newOrigoY,newOrigoX,y2,newOrigoX);
          y2 = y2 + 0.01;
        }

        double xx1 = 0;
        double yy1 = 0;
        double xx2 = 0;
        double yy2 = 0;

        getGridOriginalCoordinatesByLatLonCoordinates(y1,x1,xx1,yy1);
        getGridOriginalCoordinatesByLatLonCoordinates(y2,x2,xx2,yy2);

        std::vector<T::Coordinate> polygonPoints;
        polygonPoints.emplace_back(T::Coordinate(xx1,yy1));
        polygonPoints.emplace_back(T::Coordinate(xx2,yy1));
        polygonPoints.emplace_back(T::Coordinate(xx2,yy2));
        polygonPoints.emplace_back(T::Coordinate(xx1,yy2));

        T::GridValueList tmpValueList;
        getGridValueListByPolygon(coordinateType,polygonPoints,modificationOperation,modificationParameters,tmpValueList);

        uint len = tmpValueList.getLength();
        for (uint t=0; t<len; t++)
        {
          T::GridValue rec;
          tmpValueList.getGridValueByIndex(t,rec);

          double lat = 0;
          double lon = 0;
          getGridLatLonCoordinatesByOriginalCoordinates(rec.mY,rec.mX,lat,lon);

          if (latlon_distance(origoY,origoX,lat,lon) <= radius)
            valueList.addGridValue(rec);
        }
      }
      break;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns the list of grid point values according to the given list of coordinates.

        \param coordinateType            The type of the used coordinates.
        \param pointList                 The list of coordinates
        \param areaInterpolationMethod   The area interpolation method.
        \param valueList                 The list of grid point values is returned in this parameter.
*/

void Message::getGridValueListByPointList(T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridValueListByPointList(T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    for (auto it = pointList.begin(); it != pointList.end(); ++it)
    {
      T::GridValue rec;
      rec.mX = it->x();
      rec.mY = it->y();
      getGridValueByPoint(coordinateType,it->x(),it->y(),areaInterpolationMethod,modificationOperation,modificationParameters,rec.mValue);
      valueList.addGridValue(rec);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns a list of grid point values that are inside the given polygon.

        \param coordinateType    The type of the used coordinates.
        \param polygonPoints     The polygon point coordinates
        \param valueList         The list of grid point values are returned in this parameter.
*/

void Message::getGridValueListByPolygon(T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByPolygon(coordinateType,polygonPoints,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






void Message::getGridValueListByPolygon(T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions d = getGridDimensions();
    uint cols = d.nx();
    uint rows = d.ny();

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
      {
        std::vector<T::Coordinate> newPolygonPoints;

        for (auto it = polygonPoints.begin(); it != polygonPoints.end(); ++it)
        {
          double grid_i = 0;
          double grid_j = 0;
          getGridPointByLatLonCoordinates(it->y(),it->x(),grid_i,grid_j);
          newPolygonPoints.emplace_back(T::Coordinate(grid_i,grid_j));
        }

        std::vector<T::Point> gridPoints;
        getPointsInsidePolygon(cols,rows,newPolygonPoints,gridPoints);

        for (auto it=gridPoints.begin(); it != gridPoints.end(); ++it)
        {
          T::GridValue rec;

          double lat = 0;
          double lon = 0;
          if (getGridLatLonCoordinatesByGridPoint(it->x(),it->y(),lat,lon))
          {
            rec.mX = lon;
            rec.mY = lat;
          }

          rec.mValue = getGridValueByGridPoint(it->x(),it->y(),modificationOperation,modificationParameters);
          valueList.addGridValue(rec);
        }
      }
      break;


      case T::CoordinateTypeValue::GRID_COORDINATES:
      {
        int k = 1;
        if (isGridGlobal())
          k = 2;

        std::vector<T::Point> gridPoints;
        getPointsInsidePolygon(k*cols,rows,polygonPoints,gridPoints);

        for (auto it=gridPoints.begin(); it != gridPoints.end(); ++it)
        {
          T::GridValue rec;

          rec.mX = it->x();
          rec.mY = it->y();
          rec.mValue = getGridValueByGridPoint(it->x() % cols,it->y(),modificationOperation,modificationParameters);
          valueList.addGridValue(rec);

          //double lat = 0,lon = 0;
          //getGridLatLonCoordinatesByGridPosition(it->x() % cols,it->y(),lat,lon);
        }
      }
      break;


      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
      {
        std::vector<T::Coordinate> newPolygonPoints;

        for (auto it = polygonPoints.begin(); it != polygonPoints.end(); ++it)
        {
          double grid_i = 0;
          double grid_j = 0;
          getGridPointByOriginalCoordinates(it->x(),it->y(),grid_i,grid_j);
          newPolygonPoints.emplace_back(T::Coordinate(grid_i,grid_j));
        }

        std::vector<T::Point> gridPoints;
        getPointsInsidePolygon(cols,rows,newPolygonPoints,gridPoints);

        for (auto it=gridPoints.begin(); it != gridPoints.end(); ++it)
        {
          T::GridValue rec;

          double x = 0;
          double y = 0;
          if (getGridOriginalCoordinatesByGridPoint(it->x(),it->y(),x,y))
          {
            rec.mX = x;
            rec.mY = y;
          }

          rec.mValue = getGridValueByGridPoint(it->x(),it->y(),modificationOperation,modificationParameters);
          valueList.addGridValue(rec);
        }
      }
      break;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






/*! \brief The method returns a list of grid point values that are inside the given polygon area. The polygon area
    can consists of multiple polygons. If a polygon is inside of another polygon then it is seen as a "hole" in
    the current area.

        \param coordinateType    The type of the used coordinates.
        \param polygonPath       The list of polygons (i.e. vectors of polygon points)
        \param valueList         The list of grid point values are returned in this parameter.
*/

void Message::getGridValueListByPolygonPath(T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByPolygonPath(coordinateType,polygonPath,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridValueListByPolygonPath(T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions d = getGridDimensions();
    uint cols = d.nx();
    uint rows = d.ny();

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
      {
        std::vector<std::vector<T::Coordinate>> newPolygonPath;

        for (auto polygonPoints = polygonPath.begin(); polygonPoints != polygonPath.end(); ++polygonPoints)
        {
          std::vector<T::Coordinate> newPolygonPoints;

          for (auto it = polygonPoints->begin(); it != polygonPoints->end(); ++it)
          {
            double grid_i = 0;
            double grid_j = 0;
            getGridPointByLatLonCoordinates(it->y(),it->x(),grid_i,grid_j);
            newPolygonPoints.emplace_back(T::Coordinate(grid_i,grid_j));
          }
          newPolygonPath.emplace_back(newPolygonPoints);
        }

        std::vector<T::Point> gridPoints;
        getPointsInsidePolygonPath(cols,rows,newPolygonPath,gridPoints);

        for (auto it=gridPoints.begin(); it != gridPoints.end(); ++it)
        {
          T::GridValue rec;

          double lat = 0;
          double lon = 0;
          if (getGridLatLonCoordinatesByGridPoint(it->x(),it->y(),lat,lon))
          {
            rec.mX = lon;
            rec.mY = lat;
          }

          rec.mValue = getGridValueByGridPoint(it->x(),it->y(),modificationOperation,modificationParameters);
          valueList.addGridValue(rec);
        }
      }
      break;


      case T::CoordinateTypeValue::GRID_COORDINATES:
      {
        std::vector<T::Point> gridPoints;
        getPointsInsidePolygonPath(cols,rows,polygonPath,gridPoints);

        for (auto it=gridPoints.begin(); it != gridPoints.end(); ++it)
        {
          T::GridValue rec;

          rec.mX = it->x();
          rec.mY = it->y();
          rec.mValue = getGridValueByGridPoint(it->x(),it->y(),modificationOperation,modificationParameters);
          valueList.addGridValue(rec);
        }
      }
      break;


      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
      {
        std::vector<std::vector<T::Coordinate>> newPolygonPath;

        for (auto polygonPoints = polygonPath.begin(); polygonPoints != polygonPath.end(); ++polygonPoints)
        {
          std::vector<T::Coordinate> newPolygonPoints;

          for (auto it = polygonPoints->begin(); it != polygonPoints->end(); ++it)
          {
            double grid_i = 0;
            double grid_j = 0;
            getGridPointByOriginalCoordinates(it->x(),it->y(),grid_i,grid_j);
            newPolygonPoints.emplace_back(T::Coordinate(grid_i,grid_j));
          }
          newPolygonPath.emplace_back(newPolygonPoints);
        }

        std::vector<T::Point> gridPoints;
        getPointsInsidePolygonPath(cols,rows,newPolygonPath,gridPoints);

        for (auto it=gridPoints.begin(); it != gridPoints.end(); ++it)
        {
          T::GridValue rec;

          double x = 0;
          double y = 0;
          if (getGridOriginalCoordinatesByGridPoint(it->x(),it->y(),x,y))
          {
            rec.mX = x;
            rec.mY = y;
          }

          rec.mValue = getGridValueByGridPoint(it->x(),it->y(),modificationOperation,modificationParameters);
          valueList.addGridValue(rec);
        }
      }
      break;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns a list of grid point values that are inside the given rectangle.

        \param coordinateType    The type of the used coordinates.
        \param x1                The x-parameter of the rectangles top-left corner.
        \param y1                The y-parameter of the rectangles top-left corner.
        \param x2                The x-parameter of the rectangles bottom-right corner.
        \param x2                The x-parameter of the rectangles bottom-right corner.
        \gridRectangle           The parameter defines if the given area is rectangular in the grid (or in the coordinate space).
        \param valueList         The list of grid point values are returned in this parameter.
*/

void Message::getGridValueListByRectangle(T::CoordinateType coordinateType,double x1,double y1,double x2,double y2,bool gridRectangle,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByRectangle(coordinateType,x1,y1,x2,y2,gridRectangle,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridValueListByRectangle(T::CoordinateType coordinateType,double x1,double y1,double x2,double y2,bool gridRectangle,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    if (!gridRectangle)
    {
      // We can count missing corners directly from the opposite corners. This means
      // that the requested coordinate rectangle is not necessary a rectangle in the current grid.

      std::vector<T::Coordinate> polygonPoints;
      polygonPoints.emplace_back(T::Coordinate(x1,y1));
      polygonPoints.emplace_back(T::Coordinate(x2,y1));
      polygonPoints.emplace_back(T::Coordinate(x2,y2));
      polygonPoints.emplace_back(T::Coordinate(x1,y2));
      polygonPoints.emplace_back(T::Coordinate(x1,y1));

      getGridValueListByPolygon(coordinateType,polygonPoints,valueList);
    }
    else
    {
      // We want to get values from the inside of the grid rectangle. This means that we have to
      // calculate the grid position of the opposite corners first and after that we can define
      // the missing corners.

      switch (coordinateType)
      {
        case T::CoordinateTypeValue::UNKNOWN:
        case T::CoordinateTypeValue::LATLON_COORDINATES:
        {
          double gx1 = 0;
          double gy1 = 0;
          double gx2 = 0;
          double gy2 = 0;
          std::vector<T::Coordinate> polygonPoints;
          getGridPointByLatLonCoordinates(y1,x1,gx1,gy1);
          getGridPointByLatLonCoordinates(y2,x2,gx2,gy2);

          polygonPoints.emplace_back(T::Coordinate(gx1,gy1));
          polygonPoints.emplace_back(T::Coordinate(gx1,gy2));
          polygonPoints.emplace_back(T::Coordinate(gx2,gy2));
          polygonPoints.emplace_back(T::Coordinate(gx2,gy1));
          polygonPoints.emplace_back(T::Coordinate(gx1,gy1));

          double lat1 = 0,lon1 = 0;
          double lat2 = 0,lon2 = 0;
          getGridLatLonCoordinatesByGridPosition(gx1,gy2,lat1,lon1);
          getGridLatLonCoordinatesByGridPosition(gx2,gy1,lat2,lon2);
          getGridValueListByPolygon(T::CoordinateTypeValue::GRID_COORDINATES,polygonPoints,modificationOperation,modificationParameters,valueList);
        }
        break;

        case T::CoordinateTypeValue::GRID_COORDINATES:
        {
          if (isGridGlobal() &&  x1 > x2)
          {
            T::Dimensions d = getGridDimensions();
            uint w = d.nx();

            double xx1 = x1;
            double xx2 = x2 + w;

            std::vector<T::Coordinate> polygonPoints;
            polygonPoints.emplace_back(T::Coordinate(xx1,y1));
            polygonPoints.emplace_back(T::Coordinate(xx1,y2));
            polygonPoints.emplace_back(T::Coordinate(xx2,y2));
            polygonPoints.emplace_back(T::Coordinate(xx2,y1));
            polygonPoints.emplace_back(T::Coordinate(xx1,y1));
            getGridValueListByPolygon(T::CoordinateTypeValue::GRID_COORDINATES,polygonPoints,modificationOperation,modificationParameters,valueList);
          }
          else
          {
            std::vector<T::Coordinate> polygonPoints;
            polygonPoints.emplace_back(T::Coordinate(x1,y1));
            polygonPoints.emplace_back(T::Coordinate(x1,y2));
            polygonPoints.emplace_back(T::Coordinate(x2,y2));
            polygonPoints.emplace_back(T::Coordinate(x2,y1));
            polygonPoints.emplace_back(T::Coordinate(x1,y1));
            getGridValueListByPolygon(T::CoordinateTypeValue::GRID_COORDINATES,polygonPoints,modificationOperation,modificationParameters,valueList);
          }
        }
        break;

        case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        {
          double gx1 = 0;
          double gy1 = 0;
          double gx2 = 0;
          double gy2 = 0;
          std::vector<T::Coordinate> polygonPoints;
          getGridPointByOriginalCoordinates(x1,y1,gx1,gy1);
          getGridPointByOriginalCoordinates(x2,y2,gx2,gy2);
          polygonPoints.emplace_back(T::Coordinate(gx1,gy1));
          polygonPoints.emplace_back(T::Coordinate(gx1,gy2));
          polygonPoints.emplace_back(T::Coordinate(gx2,gy2));
          polygonPoints.emplace_back(T::Coordinate(gx2,gy1));
          polygonPoints.emplace_back(T::Coordinate(gx1,gy1));
          getGridValueListByPolygon(T::CoordinateTypeValue::GRID_COORDINATES,polygonPoints,modificationOperation,modificationParameters,valueList);
        }
        break;

        default:
        {
          Fmi::Exception exception(BCP,"Unknow coordinate type!",nullptr);
          exception.addParameter("Coordinate Type",Fmi::to_string(coordinateType));
          throw exception;
        }
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns a vector of grid point values according the given coordinate vector.

        \param coordinateType            The type of the used coordinates.
        \param coordinates               The vector of coordinates.
        \param areaInterpolationMethod   The area interpolation method.
        \param values                    The vector of grid point values are returned in this parameter.
*/

void Message::getGridValueVectorByCoordinateList(T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByCoordinateList(coordinateType,coordinates,areaInterpolationMethod,0,EMPTY_DOUBLE_VEC,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridValueVectorByCoordinateList(T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    AutoThreadLock lock(&mThreadLock);

    // ### Counting a hash value for the coordinates

    unsigned long long hash = (C_UINT64(coordinateType) << 60) + (C_UINT64(areaInterpolationMethod) << 54);
    uint sz = coordinates.size();
    for (uint t=0; t<sz; t++)
      hash += C_UINT64(coordinates[t].x()*100000+t) + C_UINT64(coordinates[t].y()*100000+t);

    uint fileId = getFileId();
    uint messageIndex = getMessageIndex();

    // ### Seaching data from the temporary cache
    {
      AutoThreadLock lock(&tmpCacheThreadLock);
      for (uint t=0; t<tmpValueCacheSize; t++)
      {
        if (tmpValueCache[t].fileId ==  fileId  &&  tmpValueCache[t].messageIndex == messageIndex  &&  tmpValueCache[t].hash == hash)
        {
          values = tmpValueCache[t].values;
          return;
        }
      }
    }

    // ### Fetching data

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        getGridValueVectorByLatLonCoordinateList(coordinates,areaInterpolationMethod,modificationOperation,modificationParameters,values);
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        getGridValueVectorByGridPointList(coordinates,areaInterpolationMethod,modificationOperation,modificationParameters,values);
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
         // TODO: Implementation required
         break;

      default:
      {
        Fmi::Exception exception(BCP,"Unknow coordinate type!",nullptr);
        exception.addParameter("Coordinate Type",Fmi::to_string(coordinateType));
        throw exception;
      }
    }

    // ### Adding data into the temporary cache

    {
      AutoThreadLock lock(&tmpCacheThreadLock);
      tmpValueCachePos++;
      uint idx = tmpValueCachePos % tmpValueCacheSize;
      tmpValueCache[idx].hash = hash;
      tmpValueCache[idx].values = values;
      tmpValueCache[idx].fileId = fileId;
      tmpValueCache[idx].messageIndex = messageIndex;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns a vector of grid point values according the given latlon coordinate vector.

        \param coordinates               The vector of latlon coordinates.
        \param areaInterpolationMethod   The area interpolation method.
        \param values                    The vector of grid point values are returned in this parameter.
*/

void Message::getGridValueVectorByLatLonCoordinateList(std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByLatLonCoordinateList(coordinates,areaInterpolationMethod,0,EMPTY_DOUBLE_VEC,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






void Message::getGridValueVectorByLatLonCoordinateList(std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    T::Coordinate_vec points;
    getGridPointListByLatLonCoordinates(coordinates,points);

    values.reserve(coordinates.size());

    switch (areaInterpolationMethod)
    {
      case T::AreaInterpolationMethod::None:
        for (auto it = points.begin(); it != points.end(); ++it)
        {
          T::ParamValue value = getGridValueByGridPoint_noInterpolation(it->x(),it->y(),modificationOperation,modificationParameters);
          values.emplace_back(value);
        }
        break;

      case T::AreaInterpolationMethod::Nearest:
        for (auto it = points.begin(); it != points.end(); ++it)
        {
          T::ParamValue value = getGridValueByGridPoint_nearest(it->x(),it->y(),modificationOperation,modificationParameters);
          values.emplace_back(value);
        }
        break;

      case T::AreaInterpolationMethod::Linear:
        for (auto it = points.begin(); it != points.end(); ++it)
        {
          T::ParamValue value = getGridValueByGridPoint_linearInterpolation(it->x(),it->y(),modificationOperation,modificationParameters);
          values.emplace_back(value);
        }
        break;

      case T::AreaInterpolationMethod::Min:
        for (auto it = points.begin(); it != points.end(); ++it)
        {
          T::ParamValue value = getGridValueByGridPoint_min(it->x(),it->y(),modificationOperation,modificationParameters);
          values.emplace_back(value);
        }
        break;

      case T::AreaInterpolationMethod::Max:
        for (auto it = points.begin(); it != points.end(); ++it)
        {
          T::ParamValue value = getGridValueByGridPoint_max(it->x(),it->y(),modificationOperation,modificationParameters);
          values.emplace_back(value);
        }
        break;

      case T::AreaInterpolationMethod::External:
        for (auto it = points.begin(); it != points.end(); ++it)
        {
          T::ParamValue value = getGridValueByGridPoint_nearest(it->x(),it->y(),modificationOperation,modificationParameters);
          values.emplace_back(value);
        }
        break;

      default:
        for (auto it = points.begin(); it != points.end(); ++it)
        {
          T::ParamValue value = getGridValueByGridPoint_nearest(it->x(),it->y(),modificationOperation,modificationParameters);
          values.emplace_back(value);
        }
        break;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns a vector of grid point values according the given grid position coordinate vector.

        \param coordinates               The vector of grid position coordinates.
        \param areaInterpolationMethod   The area interpolation method.
        \param values                    The vector of grid point values are returned in this parameter.
*/

void Message::getGridValueVectorByGridPointList(std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByGridPointList(coordinates,areaInterpolationMethod,0,EMPTY_DOUBLE_VEC,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getGridValueVectorByGridPointList(std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    values.reserve(coordinates.size());

    switch (areaInterpolationMethod)
    {
      case T::AreaInterpolationMethod::None:
        for (auto it = coordinates.begin(); it != coordinates.end(); ++it)
        {
          T::ParamValue value = getGridValueByGridPoint_noInterpolation(it->x(),it->y(),modificationOperation,modificationParameters);
          values.emplace_back(value);
        }
        return;

      case T::AreaInterpolationMethod::Nearest:
        for (auto it = coordinates.begin(); it != coordinates.end(); ++it)
        {
          T::ParamValue value = getGridValueByGridPoint_nearest(it->x(),it->y(),modificationOperation,modificationParameters);
          values.emplace_back(value);
        }
        return;

      case T::AreaInterpolationMethod::Linear:
        for (auto it = coordinates.begin(); it != coordinates.end(); ++it)
        {
          T::ParamValue value = getGridValueByGridPoint_linearInterpolation(it->x(),it->y(),modificationOperation,modificationParameters);
          values.emplace_back(value);
        }
        return;

      case T::AreaInterpolationMethod::Min:
        for (auto it = coordinates.begin(); it != coordinates.end(); ++it)
        {
          T::ParamValue value = getGridValueByGridPoint_min(it->x(),it->y(),modificationOperation,modificationParameters);
          values.emplace_back(value);
        }
        return;

      case T::AreaInterpolationMethod::Max:
        for (auto it = coordinates.begin(); it != coordinates.end(); ++it)
        {
          T::ParamValue value = getGridValueByGridPoint_max(it->x(),it->y(),modificationOperation,modificationParameters);
          values.emplace_back(value);
        }
        return;

      case T::AreaInterpolationMethod::External:
        for (auto it = coordinates.begin(); it != coordinates.end(); ++it)
        {
          T::ParamValue value = getGridValueByGridPoint_nearest(it->x(),it->y(),modificationOperation,modificationParameters);
          values.emplace_back(value);
        }
        return;

      default:
        for (auto it = coordinates.begin(); it != coordinates.end(); ++it)
        {
          T::ParamValue value = getGridValueByGridPoint_nearest(it->x(),it->y(),modificationOperation,modificationParameters);
          values.emplace_back(value);
        }
        return;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the closest or the interpolated value in the given grid position.
    The basic idea is that the given position is inside the rectangular area which
    opposite corners are (floor(grid_i),floor(grid_j)) and (floor(grid_i)+1,floor(grid_j)+1).
    The 'areaInterpolationMethod' parameter indicates whether we should return the value of
    the closest grid point or calculate it by interpolating.

        \param grid_i                     The grid i-position.
        \param grid_j                     The grid j-position.
        \param areaInterpolationMethod    The interpolation method.
*/

T::ParamValue Message::getGridValueByGridPoint_byInterpolation(double grid_i,double grid_j,short areaInterpolationMethod) const
{
  FUNCTION_TRACE
  try
  {
    return getGridValueByGridPoint_byInterpolation(grid_i,grid_j,areaInterpolationMethod,0,EMPTY_DOUBLE_VEC);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






T::ParamValue Message::getGridValueByGridPoint_byInterpolation(double grid_i,double grid_j,short areaInterpolationMethod,uint modificationOperation,double_vec& modificationParameters) const
{
  FUNCTION_TRACE
  try
  {
    short ipm = areaInterpolationMethod;

    if (areaInterpolationMethod == T::AreaInterpolationMethod::Undefined)
      ipm = getDefaultInterpolationMethod();

    switch (ipm)
    {
      case T::AreaInterpolationMethod::None:
        return getGridValueByGridPoint_noInterpolation(grid_i,grid_j,modificationOperation,modificationParameters);

      case T::AreaInterpolationMethod::Nearest:
        return getGridValueByGridPoint_nearest(grid_i,grid_j,modificationOperation,modificationParameters);

      case T::AreaInterpolationMethod::Linear:
        return getGridValueByGridPoint_linearInterpolation(grid_i,grid_j,modificationOperation,modificationParameters);

      case T::AreaInterpolationMethod::Min:
        return getGridValueByGridPoint_min(grid_i,grid_j,modificationOperation,modificationParameters);

      case T::AreaInterpolationMethod::Max:
        return getGridValueByGridPoint_max(grid_i,grid_j,modificationOperation,modificationParameters);

      case T::AreaInterpolationMethod::External:
        return getGridValueByGridPoint_nearest(grid_i,grid_j,modificationOperation,modificationParameters);

      case 20:
        return countAverageValue();

      default:
        return getGridValueByGridPoint_nearest(grid_i,grid_j,modificationOperation,modificationParameters);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns the closest or the interpolated parameter value
    in the given latlon coordinates.

        \param lat                        The latitude.
        \param lon                        The longitude.
        \param areaInterpolationMethod    The interpolation method.
        \return                           The closest of the interpolated value
                                          in the given latlon coordinates.
*/

T::ParamValue Message::getGridValueByLatLonCoordinate(double lat,double lon,short areaInterpolationMethod) const
{
  FUNCTION_TRACE
  try
  {
    return getGridValueByLatLonCoordinate(lat,lon,areaInterpolationMethod,0,EMPTY_DOUBLE_VEC);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::ParamValue Message::getGridValueByLatLonCoordinate(double lat,double lon,short areaInterpolationMethod,uint modificationOperation,double_vec& modificationParameters) const
{
  FUNCTION_TRACE
  try
  {
    double grid_i = 0;
    double grid_j = 0;
    if (getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j))
    {
      return getGridValueByGridPoint_byInterpolation(grid_i,grid_j,areaInterpolationMethod,modificationOperation,modificationParameters);
    }

    return ParamValueMissing;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns grid point values in the given area (without any interpolation).

        \param grid_i_start  The start grid i-position.
        \param grid_j_start  The start grid j-position.
        \param grid_i_end    The end grid i-position.
        \param grid_j_end    The end grid j-position.
        \return              The parameter values in the given grid area.
*/

void Message::getGridValueVectorByRectangle(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,T::GridPointValue_vec& gridPointValues) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByRectangle(grid_i_start,grid_j_start,grid_i_end,grid_j_end,0,EMPTY_DOUBLE_VEC,gridPointValues);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






void Message::getGridValueVectorByRectangle(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,uint modificationOperation,double_vec& modificationParameters,T::GridPointValue_vec& gridPointValues) const
{
  FUNCTION_TRACE
  try
  {
    time_t tm = getForecastTimeT();

    for (uint j=grid_j_start; j<= grid_j_end; j++)
    {
      for (uint i=grid_i_start; i<= grid_i_end; i++)
      {
        auto val = getGridValueByGridPoint(i,j,modificationOperation,modificationParameters);
        gridPointValues.emplace_back(T::GridPointValue(getFileId(),getMessageIndex(),i,j,getGridParameterLevel(),tm,val));
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






/*! \brief The method returns grid point values in the given area (without any interpolation).

        \param grid_i_start  The start grid i-position.
        \param grid_j_start  The start grid j-position.
        \param grid_i_end    The end grid i-position.
        \param grid_j_end    The end grid j-position.
        \return              The parameter values in the given grid area.
*/

void Message::getParameterValuesByRectangle(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,T::GridPointValueList& gridPointValues) const
{
  FUNCTION_TRACE
  try
  {
    getParameterValuesByRectangle(grid_i_start,grid_j_start,grid_i_end,grid_j_end,0,EMPTY_DOUBLE_VEC,gridPointValues);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::getParameterValuesByRectangle(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,uint modificationOperation,double_vec& modificationParameters,T::GridPointValueList& gridPointValues) const
{
  FUNCTION_TRACE
  try
  {
    time_t tm = getForecastTimeT();

    for (uint j=grid_j_start; j<= grid_j_end; j++)
    {
      for (uint i=grid_i_start; i<= grid_i_end; i++)
      {
        T::ParamValue val = getGridValueByGridPoint(i,j);
        gridPointValues.addGridPointValue(new T::GridPointValue(getFileId(),getMessageIndex(),i,j,getGridParameterLevel(),tm,val));
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns the value of the rounded grid position.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The closest value of the given grid position.
*/

T::ParamValue Message::getGridValueByGridPoint_noInterpolation(double grid_i,double grid_j) const
{
  FUNCTION_TRACE
  try
  {
    return getGridValueByGridPoint_noInterpolation(grid_i,grid_j,0,EMPTY_DOUBLE_VEC);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::ParamValue Message::getGridValueByGridPoint_noInterpolation(double grid_i,double grid_j,uint modificationOperation,double_vec& modificationParameters) const
{
  FUNCTION_TRACE
  try
  {
    return getGridValueByGridPoint(Fmi::floor(grid_i),Fmi::floor(grid_j),modificationOperation,modificationParameters);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the closest value of the given grid position.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The closest value of the given grid position.
*/

T::ParamValue Message::getGridValueByGridPoint_nearest(double grid_i,double grid_j) const
{
  FUNCTION_TRACE
  try
  {
    return getGridValueByGridPoint_nearest(grid_i,grid_j,0,EMPTY_DOUBLE_VEC);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::ParamValue Message::getGridValueByGridPoint_nearest(double grid_i,double grid_j,uint modificationOperation,double_vec& modificationParameters) const
{
  FUNCTION_TRACE
  try
  {
    double x = grid_i;
    double y = grid_j;

    uint x1 = C_UINT(Fmi::floor(x));
    uint y1 = C_UINT(Fmi::floor(y));
    uint x2 = x1+1;
    uint y2 = y1+1;

    double dist_x1 = x - C_DOUBLE(x1);
    double dist_x2 = C_DOUBLE(x2) - x;
    double dist_y1 = y - C_DOUBLE(y1);
    double dist_y2 = C_DOUBLE(y2) - y;

    if (dist_x1 == 0  &&  dist_y1 == 0)
      return getGridValueByGridPoint(round(grid_i),round(grid_j),modificationOperation,modificationParameters);

    double dist_q11 = (dist_x1)*(dist_x1) + (dist_y1)*(dist_y1);
    double dist_q21 = (dist_x2)*(dist_x2) + (dist_y1)*(dist_y1);
    double dist_q12 = (dist_x1)*(dist_x1) + (dist_y2)*(dist_y2);
    double dist_q22 = (dist_x2)*(dist_x2) + (dist_y2)*(dist_y2);

    if (dist_q11 < dist_q21  &&  dist_q11 <= dist_q12 && dist_q11 <= dist_q22)
      return getGridValueByGridPoint(x1,y1,modificationOperation,modificationParameters);

    if (dist_q21 < dist_q11  &&  dist_q21 <= dist_q12 && dist_q21 <= dist_q22)
      return getGridValueByGridPoint(x2,y1,modificationOperation,modificationParameters);

    if (dist_q12 < dist_q11  &&  dist_q12 <= dist_q21   &&  dist_q12 <= dist_q22)
      return getGridValueByGridPoint(x1,y2,modificationOperation,modificationParameters);

    return getGridValueByGridPoint(x2,y2,modificationOperation,modificationParameters);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the min value of the closest (four) grid points.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The min value of the closest grid points.
*/

T::ParamValue Message::getGridValueByGridPoint_min(double grid_i,double grid_j) const
{
  FUNCTION_TRACE
  try
  {
    return getGridValueByGridPoint_min(grid_i,grid_j,0,EMPTY_DOUBLE_VEC);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::ParamValue Message::getGridValueByGridPoint_min(double grid_i,double grid_j,uint modificationOperation,double_vec& modificationParameters) const
{
  FUNCTION_TRACE
  try
  {
    double x = grid_i;
    double y = grid_j;

    uint x1 = C_UINT(Fmi::floor(x));
    uint y1 = C_UINT(Fmi::floor(y));
    uint x2 = C_UINT(x1+1);
    uint y2 = C_UINT(y1+1);

    std::set<T::ParamValue> values;
    values.insert(getGridValueByGridPoint(x1,y1,modificationOperation,modificationParameters));
    values.insert(getGridValueByGridPoint(x2,y1,modificationOperation,modificationParameters));
    values.insert(getGridValueByGridPoint(x1,y2,modificationOperation,modificationParameters));
    values.insert(getGridValueByGridPoint(x2,y2,modificationOperation,modificationParameters));

    return *values.begin();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the max value of the closest (four) grid points.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The max value of the closest grid points.
*/

T::ParamValue Message::getGridValueByGridPoint_max(double grid_i,double grid_j) const
{
  FUNCTION_TRACE
  try
  {
    return getGridValueByGridPoint_max(grid_i,grid_j,0,EMPTY_DOUBLE_VEC);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::ParamValue Message::getGridValueByGridPoint_max(double grid_i,double grid_j,uint modificationOperation,double_vec& modificationParameters) const
{
  FUNCTION_TRACE
  try
  {
    double x = grid_i;
    double y = grid_j;

    uint x1 = C_UINT(Fmi::floor(x));
    uint y1 = C_UINT(Fmi::floor(y));
    uint x2 = C_UINT(x1+1);
    uint y2 = C_UINT(y1+1);

    std::set<T::ParamValue> values;
    values.insert(getGridValueByGridPoint(x1,y1,modificationOperation,modificationParameters));
    values.insert(getGridValueByGridPoint(x2,y1,modificationOperation,modificationParameters));
    values.insert(getGridValueByGridPoint(x1,y2,modificationOperation,modificationParameters));
    values.insert(getGridValueByGridPoint(x2,y2,modificationOperation,modificationParameters));

    return *values.rbegin();

  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns an interpolated value of the given grid position.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The interpolated value of the given grid position.
*/

T::ParamValue Message::getGridValueByGridPoint_linearInterpolation(double grid_i,double grid_j) const
{
  FUNCTION_TRACE
  try
  {
    return getGridValueByGridPoint_linearInterpolation(grid_i,grid_j,0,EMPTY_DOUBLE_VEC);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::ParamValue Message::getGridValueByGridPoint_linearInterpolation(double grid_i,double grid_j,uint modificationOperation,double_vec& modificationParameters) const
{
  FUNCTION_TRACE
  try
  {
    // https://en.wikipedia.org/wiki/Bilinear_interpolation

    double x = grid_i;
    double y = grid_j;

    uint x1 = C_UINT(Fmi::floor(x));
    uint y1 = C_UINT(Fmi::floor(y));
    uint x2 = C_UINT(x1+1);
    uint y2 = C_UINT(y1+1);

    // Reading values of the corner grid points

    auto val_q11 = getGridValueByGridPoint(x1,y1,modificationOperation,modificationParameters);
    auto val_q21 = getGridValueByGridPoint(x2,y1,modificationOperation,modificationParameters);
    auto val_q12 = getGridValueByGridPoint(x1,y2,modificationOperation,modificationParameters);
    auto val_q22 = getGridValueByGridPoint(x2,y2,modificationOperation,modificationParameters);

    return linearInterpolation(x,y,x1,y1,x2,y2,val_q11,val_q21,val_q22,val_q12);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool Message::isRead()
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





void Message::read()
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void Message::read(MemoryReader& memoryReader)
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
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
