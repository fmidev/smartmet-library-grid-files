#include "MessageProcessing.h"
#include "../common/InterpolationFunctions.h"
#include "../common/GeneralFunctions.h"
#include "../common/CoordinateConversions.h"
#include "../identification/GridDef.h"
#include "../common/ShowFunction.h"
#include <macgyver/StringConversion.h>

#define FUNCTION_TRACE FUNCTION_TRACE_OFF

namespace SmartMet
{
namespace GRID
{


MessageProcessing::MessageProcessing()
{
}




MessageProcessing::~MessageProcessing()
{
}





void MessageProcessing::getGridIsobandsByLevel(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    getGridIsobandsByLevel(message1,message2,newLevel,contourLowValues,contourHighValues,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsobandsByLevel(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    short levelInterpolationMethod = T::LevelInterpolationMethod::Linear;
    const char *levelInterpolationMethodStr = attributeList.getAttributeValue("grid.levelInterpolationMethod");
    if (levelInterpolationMethodStr != nullptr)
      levelInterpolationMethod = toInt16(levelInterpolationMethodStr);

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
    getGridValueVectorByLevel(message1,message2,newLevel,levelInterpolationMethod,modificationOperation,modificationParameters,gridValues);

    T::Dimensions d = message1.getGridDimensions();
    T::Coordinate_svec coordinates;
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = message1.getGridLatLonCoordinates();
        coordinatePtr = coordinates.get();
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = message1.getGridOriginalCoordinates();
        coordinatePtr = coordinates.get();
        break;
    }

    getIsobands(gridValues,coordinatePtr,d.nx(),d.ny(),contourLowValues,contourHighValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.proj4",message1.getProj4());
    attributeList.setAttribute("grid.original.width",Fmi::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",Fmi::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.levelInterpolationMethod",Fmi::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
    attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));

    double wm = 0;
    double hm = 0;
    if (message1.getGridMetricCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
    else
    {
      attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

      message1.getGridCellAverageSize(wm,hm);
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    getGridIsobandsByTime(message1,message2,newTime,contourLowValues,contourHighValues,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

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
    getGridValueVectorByTime(message1,message2,newTime,timeInterpolationMethod,modificationOperation,modificationParameters,gridValues);

    T::Dimensions d = message1.getGridDimensions();
    T::Coordinate_svec coordinates;
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = message1.getGridLatLonCoordinates();
        coordinatePtr = coordinates.get();
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = message1.getGridOriginalCoordinates();
        coordinatePtr = coordinates.get();
        break;
    }

    getIsobands(gridValues,coordinatePtr,d.nx(),d.ny(),contourLowValues,contourHighValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.timeInterpolationMethod",Fmi::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
    attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsobandsByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    getGridIsobandsByLevelAndGeometry(message1,message2,newLevel,contourLowValues,contourHighValues,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void MessageProcessing::getGridIsobandsByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const
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
        attributeList.setAttribute("grid.width",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridWidth())*m)));
        attributeList.setAttribute("grid.height",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
      const char *gridHeightStr = attributeList.getAttributeValue("grid.height");
      if ((gridWidthStr == nullptr || gridHeightStr == nullptr) &&  centerStr == nullptr)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(message1.getGridWidth()));
        attributeList.setAttribute("grid.height",Fmi::to_string(message1.getGridHeight()));
      }

      attributeList.setAttribute("grid.crs",message1.getWKT());
      attributeList.setAttribute("grid.proj4",message1.getProj4());
      T::Dimensions  d = message1.getGridDimensions();

      if (llboxStr == nullptr)
      {
        double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
        uint px1 = 0,py1 = 0,px2 = d.nx()-1,py2 = d.ny()-1;

        if (message1.reverseYDirection())
          px1 = 0,py1 = d.ny()-1,px2 = d.nx()-1,py2 = 0;

        char tmp[100];
        if (message1.getGridLatLonCoordinatesByGridPoint(px1,py1,y1,x1)  &&  message1.getGridLatLonCoordinatesByGridPoint(px2,py2,y2,x2))
        {
          if (x2 < x1  &&  x2 < 0)
            x2 += 360;

          if (x2 < x1  && x1 >= 180)
            x1 -= 360;

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          attributeList.setAttribute("grid.llbox",tmp);
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }

        if (message1.getGridOriginalCoordinatesByGridPoint(0,0,x1,y1)  &&  message1.getGridOriginalCoordinatesByGridPoint(d.nx()-1,d.ny()-1,x2,y2))
        {
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
          {
            if (x2 < x1  &&  x2 < 0)
              x2 += 360;

            if (x2 < x1  && x1 >= 180)
              x1 -= 360;
          }

          if (message1.reverseYDirection())
          {
            double tmp = y1;
            y1 = y2;
            y2 = tmp;
          }

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          if (message1.getGridProjection() != T::GridProjectionValue::LatLon)
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

      attributeList.setAttribute("grid.projectionType",Fmi::to_string(message1.getGridProjection()));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    if (geometryIdStr != nullptr  &&  message1.getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridIsobandsByLevel(message1,message2,newLevel,contourLowValues,contourHighValues,attributeList,modificationOperation,modificationParameters,contours);
      T::Dimensions  d = message1.getGridDimensions();
      attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
      attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
      return;
    }

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    uint width = 0;
    uint height = 0;
    T::Coordinate_svec coordinates;
    T::Coordinate_svec latLonCoordinates;

    Identification::gridDef.getGridOriginalCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (!latLonCoordinates || latLonCoordinates->size() == 0)
    {
      getGridIsobandsByLevel(message1,message2,newLevel,contourLowValues,contourHighValues,attributeList,modificationOperation,modificationParameters,contours);
      return;
    }

    T::ParamValue_vec gridValues;
    getGridValueVectorByLevelAndGeometry(message1,message2,newLevel,attributeList,modificationOperation,modificationParameters,gridValues);

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

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.proj4",message1.getProj4());
    attributeList.setAttribute("grid.original.width",Fmi::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",Fmi::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));
    attributeList.setAttribute("grid.width",Fmi::to_string(width));
    attributeList.setAttribute("grid.height",Fmi::to_string(height));

    double wm = 0;
    double hm = 0;
    if (message1.getGridMetricCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
    else
    {
      attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

      message1.getGridCellAverageSize(wm,hm);
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsobandsByLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    getGridIsobandsByLevelAndGrid(message1,message2,newLevel,contourLowValues,contourHighValues,gridWidth,gridHeight,gridLatLonCoordinates,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsobandsByLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    short levelInterpolationMethod = T::LevelInterpolationMethod::Linear;
    const char *li = attributeList.getAttributeValue("grid.levelInterpolationMethod");
    if (li != nullptr)
      levelInterpolationMethod = toInt16(li);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *s = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (s != nullptr)
      areaInterpolationMethod = toInt16(s);

    T::CoordinateType coordinateType = T::CoordinateTypeValue::GRID_COORDINATES;
    const char *c = attributeList.getAttributeValue("contour.coordinateType");
    if (c != nullptr)
      coordinateType = toUInt8(c);

    size_t smooth_size = 0;
    const char *ss = attributeList.getAttributeValue("contour.smooth.size");
    if (ss != nullptr)
      smooth_size = toSize_t(ss);

    size_t smooth_degree = 0;
    const char *sd = attributeList.getAttributeValue("contour.smooth.degree");
    if (sd != nullptr)
      smooth_degree = toSize_t(sd);

    T::ParamValue_vec gridValues;
    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    message1.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,values1);
    message2.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,values2);
    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,gridValues);

    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinatePtr = &gridLatLonCoordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        break;
    }

    attributeList.setAttribute("grid.levelInterpolationMethod",Fmi::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(gridWidth));
    attributeList.setAttribute("grid.height",Fmi::to_string(gridHeight));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));

    getIsobands(gridValues,coordinatePtr,gridWidth,gridHeight,contourLowValues,contourHighValues,areaInterpolationMethod,smooth_size,smooth_degree,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTimeAndGrid(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    getGridIsobandsByTimeAndGrid(message1,message2,newTime,contourLowValues,contourHighValues,gridWidth,gridHeight,gridLatLonCoordinates,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void MessageProcessing::getGridIsobandsByTimeAndGrid(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *ti = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (ti != nullptr)
      timeInterpolationMethod = toInt16(ti);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *s = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (s != nullptr)
      areaInterpolationMethod = toInt16(s);

    T::CoordinateType coordinateType = T::CoordinateTypeValue::GRID_COORDINATES;
    const char *c = attributeList.getAttributeValue("contour.coordinateType");
    if (c != nullptr)
      coordinateType = toUInt8(c);

    size_t smooth_size = 0;
    const char *ss = attributeList.getAttributeValue("contour.smooth.size");
    if (ss != nullptr)
      smooth_size = toSize_t(ss);

    size_t smooth_degree = 0;
    const char *sd = attributeList.getAttributeValue("contour.smooth.degree");
    if (sd != nullptr)
      smooth_degree = toSize_t(sd);

    T::ParamValue_vec gridValues;
    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    message1.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,values1);
    message2.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,values2);

    timeInterpolation(values1,values2,message1.getForecastTimeT(),message2.getForecastTimeT(),newTime,timeInterpolationMethod,gridValues);

    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinatePtr = &gridLatLonCoordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        break;
    }

    attributeList.setAttribute("grid.timeInterpolationMethod",Fmi::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(gridWidth));
    attributeList.setAttribute("grid.height",Fmi::to_string(gridHeight));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));

    getIsobands(gridValues,coordinatePtr,gridWidth,gridHeight,contourLowValues,contourHighValues,areaInterpolationMethod,smooth_size,smooth_degree,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    getGridIsobandsByTimeAndGeometry(message1,message2,newTime,contourLowValues,contourHighValues,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const
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
        attributeList.setAttribute("grid.width",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridWidth())*m)));
        attributeList.setAttribute("grid.height",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
      const char *gridHeightStr = attributeList.getAttributeValue("grid.height");
      if ((gridWidthStr == nullptr || gridHeightStr == nullptr) &&  centerStr == nullptr)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(message1.getGridWidth()));
        attributeList.setAttribute("grid.height",Fmi::to_string(message1.getGridHeight()));
      }

      attributeList.setAttribute("grid.crs",message1.getWKT());
      attributeList.setAttribute("grid.proj4",message1.getProj4());
      T::Dimensions  d = message1.getGridDimensions();

      if (llboxStr == nullptr)
      {
        double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
        uint px1 = 0,py1 = 0,px2 = d.nx()-1,py2 = d.ny()-1;

        if (message1.reverseYDirection())
          px1 = 0,py1 = d.ny()-1,px2 = d.nx()-1,py2 = 0;

        char tmp[100];
        if (message1.getGridLatLonCoordinatesByGridPoint(px1,py1,y1,x1)  &&  message1.getGridLatLonCoordinatesByGridPoint(px2,py2,y2,x2))
        {
          if (x2 < x1  &&  x2 < 0)
            x2 += 360;

          if (x2 < x1  && x1 >= 180)
            x1 -= 360;

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          attributeList.setAttribute("grid.llbox",tmp);
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }

        if (message1.getGridOriginalCoordinatesByGridPoint(0,0,x1,y1)  &&  message1.getGridOriginalCoordinatesByGridPoint(d.nx()-1,d.ny()-1,x2,y2))
        {
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
          {
            if (x2 < x1  &&  x2 < 0)
              x2 += 360;

            if (x2 < x1  && x1 >= 180)
              x1 -= 360;
          }

          if (message1.reverseYDirection())
          {
            double tmp = y1;
            y1 = y2;
            y2 = tmp;
          }

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          if (message1.getGridProjection() != T::GridProjectionValue::LatLon)
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

      attributeList.setAttribute("grid.projectionType",Fmi::to_string(message1.getGridProjection()));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    if (geometryIdStr != nullptr  &&  message1.getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridIsobandsByTime(message1,message2,newTime,contourLowValues,contourHighValues,attributeList,modificationOperation,modificationParameters,contours);
      T::Dimensions  d = message1.getGridDimensions();
      attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
      attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
      return;
    }

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    uint width = 0;
    uint height = 0;
    T::Coordinate_svec coordinates;
    T::Coordinate_svec latLonCoordinates;

    Identification::gridDef.getGridOriginalCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (!latLonCoordinates || latLonCoordinates->size() == 0)
    {
      getGridIsobandsByTime(message1,message2,newTime,contourLowValues,contourHighValues,attributeList,modificationOperation,modificationParameters,contours);
      return;
    }

    T::ParamValue_vec gridValues;
    getGridValueVectorByTimeAndGeometry(message1,message2,newTime,attributeList,modificationOperation,modificationParameters,gridValues);

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

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.proj4",message1.getProj4());
    attributeList.setAttribute("grid.original.width",Fmi::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",Fmi::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));
    attributeList.setAttribute("grid.width",Fmi::to_string(width));
    attributeList.setAttribute("grid.height",Fmi::to_string(height));

    double wm = 0;
    double hm = 0;
    if (message1.getGridMetricCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
    else
    {
      attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

      message1.getGridCellAverageSize(wm,hm);
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    getGridIsobandsByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,contourLowValues,contourHighValues,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

    short levelInterpolationMethod = T::LevelInterpolationMethod::Linear;
    const char *levelInterpolationMethodStr = attributeList.getAttributeValue("grid.levelInterpolationMethod");
    if (levelInterpolationMethodStr != nullptr)
      levelInterpolationMethod = toInt16(levelInterpolationMethodStr);

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
    getGridValueVectorByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,areaInterpolationMethod,timeInterpolationMethod,levelInterpolationMethod,modificationOperation,modificationParameters,gridValues);

    T::Dimensions d = message1.getGridDimensions();
    T::Coordinate_svec coordinates;
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = message1.getGridLatLonCoordinates();
        coordinatePtr = coordinates.get();
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = message1.getGridOriginalCoordinates();
        coordinatePtr = coordinates.get();
        break;
    }

    getIsobands(gridValues,coordinatePtr,d.nx(),d.ny(),contourLowValues,contourHighValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.timeInterpolationMethod",Fmi::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.levelInterpolationMethod",Fmi::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
    attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    getGridIsobandsByTimeLevelAndGeometry(message1,message2,message3,message4,newTime,newLevel,contourLowValues,contourHighValues,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const
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
        attributeList.setAttribute("grid.width",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridWidth())*m)));
        attributeList.setAttribute("grid.height",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
      const char *gridHeightStr = attributeList.getAttributeValue("grid.height");
      if ((gridWidthStr == nullptr || gridHeightStr == nullptr) &&  centerStr == nullptr)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(message1.getGridWidth()));
        attributeList.setAttribute("grid.height",Fmi::to_string(message1.getGridHeight()));
      }

      attributeList.setAttribute("grid.crs",message1.getWKT());
      attributeList.setAttribute("grid.proj4",message1.getProj4());
      T::Dimensions  d = message1.getGridDimensions();

      if (llboxStr == nullptr)
      {
        double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
        uint px1 = 0,py1 = 0,px2 = d.nx()-1,py2 = d.ny()-1;

        if (message1.reverseYDirection())
          px1 = 0,py1 = d.ny()-1,px2 = d.nx()-1,py2 = 0;

        char tmp[100];
        if (message1.getGridLatLonCoordinatesByGridPoint(px1,py1,y1,x1)  &&  message1.getGridLatLonCoordinatesByGridPoint(px2,py2,y2,x2))
        {
          if (x2 < x1  &&  x2 < 0)
            x2 += 360;

          if (x2 < x1  && x1 >= 180)
            x1 -= 360;

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          attributeList.setAttribute("grid.llbox",tmp);
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }

        if (message1.getGridOriginalCoordinatesByGridPoint(0,0,x1,y1)  &&  message1.getGridOriginalCoordinatesByGridPoint(d.nx()-1,d.ny()-1,x2,y2))
        {
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
          {
            if (x2 < x1  &&  x2 < 0)
              x2 += 360;

            if (x2 < x1  && x1 >= 180)
              x1 -= 360;
          }

          if (message1.reverseYDirection())
          {
            double tmp = y1;
            y1 = y2;
            y2 = tmp;
          }

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          if (message1.getGridProjection() != T::GridProjectionValue::LatLon)
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

      attributeList.setAttribute("grid.projectionType",Fmi::to_string(message1.getGridProjection()));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    if (geometryIdStr != nullptr  &&  message1.getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridIsobandsByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,contourLowValues,contourHighValues,attributeList,modificationOperation,modificationParameters,contours);
      T::Dimensions  d = message1.getGridDimensions();
      attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
      attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
      return;
    }

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    uint width = 0;
    uint height = 0;
    T::Coordinate_svec coordinates;
    T::Coordinate_svec latLonCoordinates;

    Identification::gridDef.getGridOriginalCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (!latLonCoordinates || latLonCoordinates->size() == 0)
    {
      getGridIsobandsByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,contourLowValues,contourHighValues,attributeList,modificationOperation,modificationParameters,contours);
      return;
    }

    T::ParamValue_vec gridValues;
    getGridValueVectorByTimeLevelAndGeometry(message1,message2,message3,message4,newTime,newLevel,attributeList,modificationOperation,modificationParameters,gridValues);

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

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.proj4",message1.getProj4());
    attributeList.setAttribute("grid.original.width",Fmi::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",Fmi::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.ogiginal.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));
    attributeList.setAttribute("grid.width",Fmi::to_string(width));
    attributeList.setAttribute("grid.height",Fmi::to_string(height));

    double wm = 0;
    double hm = 0;
    if (message1.getGridMetricCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
    else
    {
      attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

      message1.getGridCellAverageSize(wm,hm);
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTimeLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    getGridIsobandsByTimeLevelAndGrid(message1,message2,message3,message4,newTime,newLevel,contourLowValues,contourHighValues,gridWidth,gridHeight,gridLatLonCoordinates,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTimeLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    T::ParamValue_vec gridValues;
    getGridValueVectorByTimeLevelAndCoordinateList(message1,message2,message3,message4,newTime,newLevel,T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,attributeList,modificationOperation,modificationParameters,gridValues);

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

    getIsobands(gridValues,&gridLatLonCoordinates,gridWidth,gridHeight,contourLowValues,contourHighValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(gridWidth));
    attributeList.setAttribute("grid.height",Fmi::to_string(gridHeight));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    getGridIsolinesByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,contourValues,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

    short levelInterpolationMethod = T::LevelInterpolationMethod::Linear;
    const char *levelInterpolationMethodStr = attributeList.getAttributeValue("grid.levelInterpolationMethod");
    if (levelInterpolationMethodStr != nullptr)
      levelInterpolationMethod = toInt16(levelInterpolationMethodStr);

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
    getGridValueVectorByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,areaInterpolationMethod,timeInterpolationMethod,levelInterpolationMethod,modificationOperation,modificationParameters,gridValues);

    T::Dimensions d = message1.getGridDimensions();
    T::Coordinate_svec coordinates;
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = message1.getGridLatLonCoordinates();
        coordinatePtr = coordinates.get();
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = message1.getGridOriginalCoordinates();
        coordinatePtr = coordinates.get();
        break;
    }

    getIsolines(gridValues,coordinatePtr,d.nx(),d.ny(),contourValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.timeInterpolationMethod",Fmi::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.levelInterpolationMethod",Fmi::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
    attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    getGridIsolinesByTimeLevelAndGeometry(message1,message2,message3,message4,newTime,newLevel,contourValues,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const
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
        attributeList.setAttribute("grid.width",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridWidth())*m)));
        attributeList.setAttribute("grid.height",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
      const char *gridHeightStr = attributeList.getAttributeValue("grid.height");
      if ((gridWidthStr == nullptr || gridHeightStr == nullptr) &&  centerStr == nullptr)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(message1.getGridWidth()));
        attributeList.setAttribute("grid.height",Fmi::to_string(message1.getGridHeight()));
      }

      attributeList.setAttribute("grid.crs",message1.getWKT());
      attributeList.setAttribute("grid.proj4",message1.getProj4());
      T::Dimensions  d = message1.getGridDimensions();

      if (llboxStr == nullptr)
      {
        double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
        uint px1 = 0,py1 = 0,px2 = d.nx()-1,py2 = d.ny()-1;

        if (message1.reverseYDirection())
          px1 = 0,py1 = d.ny()-1,px2 = d.nx()-1,py2 = 0;

        char tmp[100];
        if (message1.getGridLatLonCoordinatesByGridPoint(px1,py1,y1,x1)  &&  message1.getGridLatLonCoordinatesByGridPoint(px2,py2,y2,x2))
        {
          if (x2 < x1  &&  x2 < 0)
            x2 += 360;

          if (x2 < x1  && x1 >= 180)
            x1 -= 360;

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          attributeList.setAttribute("grid.llbox",tmp);
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }

        if (message1.getGridOriginalCoordinatesByGridPoint(0,0,x1,y1)  &&  message1.getGridOriginalCoordinatesByGridPoint(d.nx()-1,d.ny()-1,x2,y2))
        {
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
          {
            if (x2 < x1  &&  x2 < 0)
              x2 += 360;

            if (x2 < x1  && x1 >= 180)
              x1 -= 360;
          }

          if (message1.reverseYDirection())
          {
            double tmp = y1;
            y1 = y2;
            y2 = tmp;
          }

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          if (message1.getGridProjection() != T::GridProjectionValue::LatLon)
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

      attributeList.setAttribute("grid.projectionType",Fmi::to_string(message1.getGridProjection()));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    if (geometryIdStr != nullptr  &&  message1.getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridIsolinesByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,contourValues,attributeList,modificationOperation,modificationParameters,contours);
      T::Dimensions  d = message1.getGridDimensions();
      attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
      attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
      return;
    }

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    uint width = 0;
    uint height = 0;
    T::Coordinate_svec coordinates;
    T::Coordinate_svec latLonCoordinates;

    Identification::gridDef.getGridOriginalCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (!latLonCoordinates || latLonCoordinates->size() == 0)
    {
      getGridIsolinesByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,contourValues,attributeList,modificationOperation,modificationParameters,contours);
      return;
    }

    T::ParamValue_vec gridValues;
    getGridValueVectorByTimeLevelAndGeometry(message1,message2,message3,message4,newTime,newLevel,attributeList,modificationOperation,modificationParameters,gridValues);

    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

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

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.proj4",message1.getProj4());
    attributeList.setAttribute("grid.original.width",Fmi::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",Fmi::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.timeInterpolationMethod",Fmi::to_string(timeInterpolationMethod));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));
    attributeList.setAttribute("grid.width",Fmi::to_string(width));
    attributeList.setAttribute("grid.height",Fmi::to_string(height));

    double wm = 0;
    double hm = 0;
    if (message1.getGridMetricCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
    else
    {
      attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

      message1.getGridCellAverageSize(wm,hm);
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByLevel(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    getGridIsolinesByLevel(message1,message2,newLevel,contourValues,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByLevel(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    short levelInterpolationMethod = T::LevelInterpolationMethod::Linear;
    const char *levelInterpolationMethodStr = attributeList.getAttributeValue("grid.levelInterpolationMethod");
    if (levelInterpolationMethodStr != nullptr)
      levelInterpolationMethod = toInt16(levelInterpolationMethodStr);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

    T::ParamValue_vec gridValues;
    getGridValueVectorByLevel(message1,message2,newLevel,levelInterpolationMethod,modificationOperation,modificationParameters,gridValues);

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

    T::Dimensions d = message1.getGridDimensions();
    T::Coordinate_svec coordinates;
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = message1.getGridLatLonCoordinates();
        coordinatePtr = coordinates.get();
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = message1.getGridOriginalCoordinates();
        coordinatePtr = coordinates.get();
        break;
    }

    getIsolines(gridValues,coordinatePtr,d.nx(),d.ny(),contourValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.levelInterpolationMethod",Fmi::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
    attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)message2.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    getGridIsolinesByTime(message1,message2,newTime,contourValues,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {

    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

    T::ParamValue_vec gridValues;
    getGridValueVectorByTime(message1,message2,newTime,timeInterpolationMethod,modificationOperation,modificationParameters,gridValues);

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

    T::Dimensions d = message1.getGridDimensions();
    T::Coordinate_svec coordinates;
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = message1.getGridLatLonCoordinates();
        coordinatePtr = coordinates.get();
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = message1.getGridOriginalCoordinates();
        coordinatePtr = coordinates.get();
        break;
    }

    getIsolines(gridValues,coordinatePtr,d.nx(),d.ny(),contourValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    //attributeList.setAttribute("grid.timeInterpolationMethod",Fmi::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
    attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)message2.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    getGridIsolinesByLevelAndGeometry(message1,message2,newLevel,contourValues,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const
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
        attributeList.setAttribute("grid.width",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridWidth())*m)));
        attributeList.setAttribute("grid.height",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
      const char *gridHeightStr = attributeList.getAttributeValue("grid.height");
      if ((gridWidthStr == nullptr || gridHeightStr == nullptr) &&  centerStr == nullptr)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(message1.getGridWidth()));
        attributeList.setAttribute("grid.height",Fmi::to_string(message1.getGridHeight()));
      }

      attributeList.setAttribute("grid.crs",message1.getWKT());
      attributeList.setAttribute("grid.proj4",message1.getProj4());
      T::Dimensions  d = message1.getGridDimensions();

      if (llboxStr == nullptr)
      {
        double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
        uint px1 = 0,py1 = 0,px2 = d.nx()-1,py2 = d.ny()-1;

        if (message1.reverseYDirection())
          px1 = 0,py1 = d.ny()-1,px2 = d.nx()-1,py2 = 0;

        char tmp[100];
        if (message1.getGridLatLonCoordinatesByGridPoint(px1,py1,y1,x1)  &&  message1.getGridLatLonCoordinatesByGridPoint(px2,py2,y2,x2))
        {
          if (x2 < x1  &&  x2 < 0)
            x2 += 360;

          if (x2 < x1  && x1 >= 180)
            x1 -= 360;

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          attributeList.setAttribute("grid.llbox",tmp);
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }

        if (message1.getGridOriginalCoordinatesByGridPoint(0,0,x1,y1)  &&  message1.getGridOriginalCoordinatesByGridPoint(d.nx()-1,d.ny()-1,x2,y2))
        {
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
          {
            if (x2 < x1  &&  x2 < 0)
              x2 += 360;

            if (x2 < x1  && x1 >= 180)
              x1 -= 360;
          }

          if (message1.reverseYDirection())
          {
            double tmp = y1;
            y1 = y2;
            y2 = tmp;
          }

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          if (message1.getGridProjection() != T::GridProjectionValue::LatLon)
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

      attributeList.setAttribute("grid.projectionType",Fmi::to_string(message1.getGridProjection()));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    if (geometryIdStr != nullptr  &&  message1.getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridIsolinesByLevel(message1,message2,newLevel,contourValues,attributeList,modificationOperation,modificationParameters,contours);
      T::Dimensions  d = message1.getGridDimensions();
      attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
      attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
      return;
    }

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    uint width = 0;
    uint height = 0;
    T::Coordinate_svec coordinates;
    T::Coordinate_svec latLonCoordinates;

    Identification::gridDef.getGridOriginalCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (!latLonCoordinates || latLonCoordinates->size() == 0)
    {
      getGridIsolinesByLevel(message1,message2,newLevel,contourValues,attributeList,modificationOperation,modificationParameters,contours);
      return;
    }

    T::ParamValue_vec gridValues;
    getGridValueVectorByLevelAndGeometry(message1,message2,newLevel,attributeList,modificationOperation,modificationParameters,gridValues);

    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

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

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.proj4",message1.getProj4());
    attributeList.setAttribute("grid.original.width",Fmi::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",Fmi::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.timeInterpolationMethod",Fmi::to_string(timeInterpolationMethod));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));
    attributeList.setAttribute("grid.width",Fmi::to_string(width));
    attributeList.setAttribute("grid.height",Fmi::to_string(height));

    double wm = 0;
    double hm = 0;
    if (message1.getGridMetricCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
    else
    {
      attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

      message1.getGridCellAverageSize(wm,hm);
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    getGridIsolinesByTimeAndGeometry(message1,message2,newTime,contourValues,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const
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
        attributeList.setAttribute("grid.width",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridWidth())*m)));
        attributeList.setAttribute("grid.height",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
      const char *gridHeightStr = attributeList.getAttributeValue("grid.height");
      if ((gridWidthStr == nullptr || gridHeightStr == nullptr) &&  centerStr == nullptr)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(message1.getGridWidth()));
        attributeList.setAttribute("grid.height",Fmi::to_string(message1.getGridHeight()));
      }

      attributeList.setAttribute("grid.crs",message1.getWKT());
      attributeList.setAttribute("grid.proj4",message1.getProj4());
      T::Dimensions  d = message1.getGridDimensions();

      if (llboxStr == nullptr)
      {
        double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
        uint px1 = 0,py1 = 0,px2 = d.nx()-1,py2 = d.ny()-1;

        if (message1.reverseYDirection())
          px1 = 0,py1 = d.ny()-1,px2 = d.nx()-1,py2 = 0;

        char tmp[100];
        if (message1.getGridLatLonCoordinatesByGridPoint(px1,py1,y1,x1)  &&  message1.getGridLatLonCoordinatesByGridPoint(px2,py2,y2,x2))
        {
          if (x2 < x1  &&  x2 < 0)
            x2 += 360;

          if (x2 < x1  && x1 >= 180)
            x1 -= 360;

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          attributeList.setAttribute("grid.llbox",tmp);
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }

        if (message1.getGridOriginalCoordinatesByGridPoint(0,0,x1,y1)  &&  message1.getGridOriginalCoordinatesByGridPoint(d.nx()-1,d.ny()-1,x2,y2))
        {
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
          {
            if (x2 < x1  &&  x2 < 0)
              x2 += 360;

            if (x2 < x1  && x1 >= 180)
              x1 -= 360;
          }

          if (message1.reverseYDirection())
          {
            double tmp = y1;
            y1 = y2;
            y2 = tmp;
          }

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          if (message1.getGridProjection() != T::GridProjectionValue::LatLon)
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

      attributeList.setAttribute("grid.projectionType",Fmi::to_string(message1.getGridProjection()));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    if (geometryIdStr != nullptr  &&  message1.getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridIsolinesByTime(message1,message2,newTime,contourValues,attributeList,modificationOperation,modificationParameters,contours);
      T::Dimensions  d = message1.getGridDimensions();
      attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
      attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
      return;
    }

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    uint width = 0;
    uint height = 0;
    T::Coordinate_svec coordinates;
    T::Coordinate_svec latLonCoordinates;

    Identification::gridDef.getGridOriginalCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (!latLonCoordinates || latLonCoordinates->size() == 0)
    {
      getGridIsolinesByTime(message1,message2,newTime,contourValues,attributeList,modificationOperation,modificationParameters,contours);
      return;
    }

    T::ParamValue_vec gridValues;
    getGridValueVectorByTimeAndGeometry(message1,message2,newTime,attributeList,modificationOperation,modificationParameters,gridValues);

    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

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

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.proj4",message1.getProj4());
    attributeList.setAttribute("grid.original.width",Fmi::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",Fmi::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.timeInterpolationMethod",Fmi::to_string(timeInterpolationMethod));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));
    attributeList.setAttribute("grid.width",Fmi::to_string(width));
    attributeList.setAttribute("grid.height",Fmi::to_string(height));

    double wm = 0;
    double hm = 0;
    if (message1.getGridMetricCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
    else
    {
      attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

      message1.getGridCellAverageSize(wm,hm);
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    getGridIsolinesByLevelAndGrid(message1,message2,newLevel,contourValues,gridWidth,gridHeight,gridLatLonCoordinates,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    short levelInterpolationMethod = T::LevelInterpolationMethod::Linear;
    const char *li = attributeList.getAttributeValue("grid.levelInterpolationMethod");
    if (li != nullptr)
      levelInterpolationMethod = toInt16(li);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *s = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (s != nullptr)
      areaInterpolationMethod = toInt16(s);

    T::CoordinateType coordinateType = T::CoordinateTypeValue::GRID_COORDINATES;
    const char *c = attributeList.getAttributeValue("contour.coordinateType");
    if (c != nullptr)
      coordinateType = toUInt8(c);

    size_t smooth_size = 0;
    const char *ss = attributeList.getAttributeValue("contour.smooth.size");
    if (ss != nullptr)
      smooth_size = toSize_t(ss);

    size_t smooth_degree = 0;
    const char *sd = attributeList.getAttributeValue("contour.smooth.degree");
    if (sd != nullptr)
      smooth_degree = toSize_t(sd);

    T::ParamValue_vec gridValues;
    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    message1.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,values1);
    message2.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,values2);
    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,gridValues);

    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinatePtr = &gridLatLonCoordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        break;
    }

    attributeList.setAttribute("grid.levelInterpolationMethod",Fmi::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(gridWidth));
    attributeList.setAttribute("grid.height",Fmi::to_string(gridHeight));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));

    getIsolines(gridValues,coordinatePtr,gridWidth,gridHeight,contourValues,areaInterpolationMethod,smooth_size,smooth_degree,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTimeAndGrid(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    getGridIsolinesByTimeAndGrid(message1,message2,newTime,contourValues,gridWidth,gridHeight,gridLatLonCoordinates,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTimeAndGrid(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours)
{
  FUNCTION_TRACE
  try
  {
    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *ti = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (ti != nullptr)
      timeInterpolationMethod = toInt16(ti);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *s = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (s != nullptr)
      areaInterpolationMethod = toInt16(s);

    T::CoordinateType coordinateType = T::CoordinateTypeValue::GRID_COORDINATES;
    const char *c = attributeList.getAttributeValue("contour.coordinateType");
    if (c != nullptr)
      coordinateType = toUInt8(c);

    size_t smooth_size = 0;
    const char *ss = attributeList.getAttributeValue("contour.smooth.size");
    if (ss != nullptr)
      smooth_size = toSize_t(ss);

    size_t smooth_degree = 0;
    const char *sd = attributeList.getAttributeValue("contour.smooth.degree");
    if (sd != nullptr)
      smooth_degree = toSize_t(sd);

    T::ParamValue_vec gridValues;
    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    message1.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,values1);
    message2.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,values2);

    timeInterpolation(values1,values2,message1.getForecastTimeT(),message2.getForecastTimeT(),newTime,timeInterpolationMethod,gridValues);

    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinatePtr = &gridLatLonCoordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        break;
    }

    attributeList.setAttribute("grid.timeInterpolationMethod",Fmi::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(gridWidth));
    attributeList.setAttribute("grid.height",Fmi::to_string(gridHeight));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",Fmi::to_string(coordinateType));

    getIsolines(gridValues,coordinatePtr,gridWidth,gridHeight,contourValues,areaInterpolationMethod,smooth_size,smooth_degree,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void MessageProcessing::getGridIsolinesByTimeLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    getGridIsolinesByTimeLevelAndGrid(message1,message2,message3,message4,newTime,newLevel,contourValues,gridWidth,gridHeight,gridLatLonCoordinates,attributeList,0,EMPTY_DOUBLE_VEC,contours);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTimeLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const
{
  FUNCTION_TRACE
  try
  {
    T::ParamValue_vec gridValues;
    getGridValueVectorByTimeLevelAndCoordinateList(message1,message2,message3,message4,newTime,newLevel,T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,attributeList,modificationOperation,modificationParameters,gridValues);

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

    getIsolines(gridValues,&gridLatLonCoordinates,gridWidth,gridHeight,contourValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(gridWidth));
    attributeList.setAttribute("grid.height",Fmi::to_string(gridHeight));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}
























void MessageProcessing::getGridStreamlinesByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::AttributeList& attributeList,T::ByteData_vec& streamlines) const
{
  FUNCTION_TRACE
  try
  {
    getGridStreamlinesByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,attributeList,0,EMPTY_DOUBLE_VEC,streamlines);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridStreamlinesByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines) const
{
  FUNCTION_TRACE
  try
  {
    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

    short levelInterpolationMethod = T::LevelInterpolationMethod::Linear;
    const char *levelInterpolationMethodStr = attributeList.getAttributeValue("grid.levelInterpolationMethod");
    if (levelInterpolationMethodStr != nullptr)
      levelInterpolationMethod = toInt16(levelInterpolationMethodStr);

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
    getGridValueVectorByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,areaInterpolationMethod,timeInterpolationMethod,levelInterpolationMethod,modificationOperation,modificationParameters,gridValues);

    T::Dimensions d = message1.getGridDimensions();
    T::Coordinate_svec coordinates;
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = message1.getGridLatLonCoordinates();
        coordinatePtr = coordinates.get();
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = message1.getGridOriginalCoordinates();
        coordinatePtr = coordinates.get();
        break;
    }

    getStreamlines(gridValues,coordinatePtr,d.nx(),d.ny(),minStreamLen, maxStreamLen,lineLen,xStep,yStep,streamlines);

    attributeList.setAttribute("grid.timeInterpolationMethod",Fmi::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.levelInterpolationMethod",Fmi::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
    attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("stream.coordinateType",Fmi::to_string(coordinateType));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridStreamlinesByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::AttributeList& attributeList,T::ByteData_vec& streamlines) const
{
  FUNCTION_TRACE
  try
  {
    getGridStreamlinesByTimeLevelAndGeometry(message1,message2,message3,message4,newTime,newLevel,attributeList,0,EMPTY_DOUBLE_VEC,streamlines);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridStreamlinesByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines) const
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
        attributeList.setAttribute("grid.width",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridWidth())*m)));
        attributeList.setAttribute("grid.height",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
      const char *gridHeightStr = attributeList.getAttributeValue("grid.height");
      if ((gridWidthStr == nullptr || gridHeightStr == nullptr) &&  centerStr == nullptr)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(message1.getGridWidth()));
        attributeList.setAttribute("grid.height",Fmi::to_string(message1.getGridHeight()));
      }

      attributeList.setAttribute("grid.crs",message1.getWKT());
      attributeList.setAttribute("grid.proj4",message1.getProj4());
      T::Dimensions  d = message1.getGridDimensions();

      if (llboxStr == nullptr)
      {
        double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
        uint px1 = 0,py1 = 0,px2 = d.nx()-1,py2 = d.ny()-1;

        if (message1.reverseYDirection())
          px1 = 0,py1 = d.ny()-1,px2 = d.nx()-1,py2 = 0;

        char tmp[100];
        if (message1.getGridLatLonCoordinatesByGridPoint(px1,py1,y1,x1)  &&  message1.getGridLatLonCoordinatesByGridPoint(px2,py2,y2,x2))
        {
          if (x2 < x1  &&  x2 < 0)
            x2 += 360;

          if (x2 < x1  && x1 >= 180)
            x1 -= 360;

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          attributeList.setAttribute("grid.llbox",tmp);
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }

        if (message1.getGridOriginalCoordinatesByGridPoint(0,0,x1,y1)  &&  message1.getGridOriginalCoordinatesByGridPoint(d.nx()-1,d.ny()-1,x2,y2))
        {
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
          {
            if (x2 < x1  &&  x2 < 0)
              x2 += 360;

            if (x2 < x1  && x1 >= 180)
              x1 -= 360;
          }

          if (message1.reverseYDirection())
          {
            double tmp = y1;
            y1 = y2;
            y2 = tmp;
          }

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          if (message1.getGridProjection() != T::GridProjectionValue::LatLon)
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

      attributeList.setAttribute("grid.projectionType",Fmi::to_string(message1.getGridProjection()));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    if (geometryIdStr != nullptr  &&  message1.getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridStreamlinesByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,attributeList,modificationOperation,modificationParameters,streamlines);
      T::Dimensions  d = message1.getGridDimensions();
      attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
      attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
      return;
    }

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

    uint width = 0;
    uint height = 0;
    T::Coordinate_svec coordinates;
    T::Coordinate_svec latLonCoordinates;

    Identification::gridDef.getGridOriginalCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (!latLonCoordinates || latLonCoordinates->size() == 0)
    {
      getGridStreamlinesByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,attributeList,modificationOperation,modificationParameters,streamlines);
      return;
    }

    T::ParamValue_vec gridValues;
    getGridValueVectorByTimeLevelAndGeometry(message1,message2,message3,message4,newTime,newLevel,attributeList,modificationOperation,modificationParameters,gridValues);

    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

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

    getStreamlines(gridValues,coordinatePtr,width,height,minStreamLen, maxStreamLen,lineLen,xStep,yStep,streamlines);

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.proj4",message1.getProj4());
    attributeList.setAttribute("grid.original.width",Fmi::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",Fmi::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.timeInterpolationMethod",Fmi::to_string(timeInterpolationMethod));
    attributeList.setAttribute("stream.coordinateType",Fmi::to_string(coordinateType));
    attributeList.setAttribute("grid.width",Fmi::to_string(width));
    attributeList.setAttribute("grid.height",Fmi::to_string(height));

    double wm = 0;
    double hm = 0;
    if (message1.getGridMetricCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
    else
    {
      attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

      message1.getGridCellAverageSize(wm,hm);
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridStreamlinesByLevel(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::AttributeList& attributeList,T::ByteData_vec& streamlines) const
{
  FUNCTION_TRACE
  try
  {
    getGridStreamlinesByLevel(message1,message2,newLevel,attributeList,0,EMPTY_DOUBLE_VEC,streamlines);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridStreamlinesByLevel(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines) const
{
  FUNCTION_TRACE
  try
  {
    short levelInterpolationMethod = T::LevelInterpolationMethod::Linear;
    const char *levelInterpolationMethodStr = attributeList.getAttributeValue("grid.levelInterpolationMethod");
    if (levelInterpolationMethodStr != nullptr)
      levelInterpolationMethod = toInt16(levelInterpolationMethodStr);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

    T::ParamValue_vec gridValues;
    getGridValueVectorByLevel(message1,message2,newLevel,levelInterpolationMethod,modificationOperation,modificationParameters,gridValues);

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

    T::Dimensions d = message1.getGridDimensions();
    T::Coordinate_svec coordinates;
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = message1.getGridLatLonCoordinates();
        coordinatePtr = coordinates.get();
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = message1.getGridOriginalCoordinates();
        coordinatePtr = coordinates.get();
        break;
    }

    getStreamlines(gridValues,coordinatePtr,d.nx(),d.ny(),minStreamLen, maxStreamLen,lineLen,xStep,yStep,streamlines);

    attributeList.setAttribute("grid.levelInterpolationMethod",Fmi::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
    attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)message2.reverseXDirection()));
    attributeList.setAttribute("stream.coordinateType",Fmi::to_string(coordinateType));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridStreamlinesByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::AttributeList& attributeList,T::ByteData_vec& streamlines) const
{
  FUNCTION_TRACE
  try
  {
    getGridStreamlinesByTime(message1,message2,newTime,attributeList,0,EMPTY_DOUBLE_VEC,streamlines);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridStreamlinesByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines) const
{
  FUNCTION_TRACE
  try
  {

    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

    T::ParamValue_vec gridValues;
    getGridValueVectorByTime(message1,message2,newTime,timeInterpolationMethod,modificationOperation,modificationParameters,gridValues);

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

    T::Dimensions d = message1.getGridDimensions();
    T::Coordinate_svec coordinates;
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = message1.getGridLatLonCoordinates();
        coordinatePtr = coordinates.get();
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = message1.getGridOriginalCoordinates();
        coordinatePtr = coordinates.get();
        break;
    }

    getStreamlines(gridValues,coordinatePtr,d.nx(),d.ny(),minStreamLen, maxStreamLen,lineLen,xStep,yStep,streamlines);

    //attributeList.setAttribute("grid.timeInterpolationMethod",Fmi::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
    attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)message2.reverseXDirection()));
    attributeList.setAttribute("stream.coordinateType",Fmi::to_string(coordinateType));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridStreamlinesByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::AttributeList& attributeList,T::ByteData_vec& streamlines) const
{
  FUNCTION_TRACE
  try
  {
    getGridStreamlinesByLevelAndGeometry(message1,message2,newLevel,attributeList,0,EMPTY_DOUBLE_VEC,streamlines);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridStreamlinesByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines) const
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
        attributeList.setAttribute("grid.width",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridWidth())*m)));
        attributeList.setAttribute("grid.height",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
      const char *gridHeightStr = attributeList.getAttributeValue("grid.height");
      if ((gridWidthStr == nullptr || gridHeightStr == nullptr) &&  centerStr == nullptr)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(message1.getGridWidth()));
        attributeList.setAttribute("grid.height",Fmi::to_string(message1.getGridHeight()));
      }

      attributeList.setAttribute("grid.crs",message1.getWKT());
      attributeList.setAttribute("grid.proj4",message1.getProj4());
      T::Dimensions  d = message1.getGridDimensions();

      if (llboxStr == nullptr)
      {
        double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
        uint px1 = 0,py1 = 0,px2 = d.nx()-1,py2 = d.ny()-1;

        if (message1.reverseYDirection())
          px1 = 0,py1 = d.ny()-1,px2 = d.nx()-1,py2 = 0;

        char tmp[100];
        if (message1.getGridLatLonCoordinatesByGridPoint(px1,py1,y1,x1)  &&  message1.getGridLatLonCoordinatesByGridPoint(px2,py2,y2,x2))
        {
          if (x2 < x1  &&  x2 < 0)
            x2 += 360;

          if (x2 < x1  && x1 >= 180)
            x1 -= 360;

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          attributeList.setAttribute("grid.llbox",tmp);
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }

        if (message1.getGridOriginalCoordinatesByGridPoint(0,0,x1,y1)  &&  message1.getGridOriginalCoordinatesByGridPoint(d.nx()-1,d.ny()-1,x2,y2))
        {
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
          {
            if (x2 < x1  &&  x2 < 0)
              x2 += 360;

            if (x2 < x1  && x1 >= 180)
              x1 -= 360;
          }

          if (message1.reverseYDirection())
          {
            double tmp = y1;
            y1 = y2;
            y2 = tmp;
          }

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          if (message1.getGridProjection() != T::GridProjectionValue::LatLon)
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

      attributeList.setAttribute("grid.projectionType",Fmi::to_string(message1.getGridProjection()));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    if (geometryIdStr != nullptr  &&  message1.getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridStreamlinesByLevel(message1,message2,newLevel,attributeList,modificationOperation,modificationParameters,streamlines);
      T::Dimensions  d = message1.getGridDimensions();
      attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
      attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
      return;
    }

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

    uint width = 0;
    uint height = 0;
    T::Coordinate_svec coordinates;
    T::Coordinate_svec latLonCoordinates;

    Identification::gridDef.getGridOriginalCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (!latLonCoordinates || latLonCoordinates->size() == 0)
    {
      getGridStreamlinesByLevel(message1,message2,newLevel,attributeList,modificationOperation,modificationParameters,streamlines);
      return;
    }

    T::ParamValue_vec gridValues;
    getGridValueVectorByLevelAndGeometry(message1,message2,newLevel,attributeList,modificationOperation,modificationParameters,gridValues);

    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

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

    getStreamlines(gridValues,coordinatePtr,width,height,minStreamLen, maxStreamLen,lineLen,xStep,yStep,streamlines);

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.proj4",message1.getProj4());
    attributeList.setAttribute("grid.original.width",Fmi::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",Fmi::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.timeInterpolationMethod",Fmi::to_string(timeInterpolationMethod));
    attributeList.setAttribute("stream.coordinateType",Fmi::to_string(coordinateType));
    attributeList.setAttribute("grid.width",Fmi::to_string(width));
    attributeList.setAttribute("grid.height",Fmi::to_string(height));

    double wm = 0;
    double hm = 0;
    if (message1.getGridMetricCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
    else
    {
      attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

      message1.getGridCellAverageSize(wm,hm);
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridStreamlinesByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::AttributeList& attributeList,T::ByteData_vec& streamlines) const
{
  FUNCTION_TRACE
  try
  {
    getGridStreamlinesByTimeAndGeometry(message1,message2,newTime,attributeList,0,EMPTY_DOUBLE_VEC,streamlines);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridStreamlinesByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines) const
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
        attributeList.setAttribute("grid.width",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridWidth())*m)));
        attributeList.setAttribute("grid.height",Fmi::to_string(C_INT(C_DOUBLE(message1.getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
      const char *gridHeightStr = attributeList.getAttributeValue("grid.height");
      if ((gridWidthStr == nullptr || gridHeightStr == nullptr) &&  centerStr == nullptr)
      {
        attributeList.setAttribute("grid.width",Fmi::to_string(message1.getGridWidth()));
        attributeList.setAttribute("grid.height",Fmi::to_string(message1.getGridHeight()));
      }

      attributeList.setAttribute("grid.crs",message1.getWKT());
      attributeList.setAttribute("grid.proj4",message1.getProj4());
      T::Dimensions  d = message1.getGridDimensions();

      if (llboxStr == nullptr)
      {
        double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
        uint px1 = 0,py1 = 0,px2 = d.nx()-1,py2 = d.ny()-1;

        if (message1.reverseYDirection())
          px1 = 0,py1 = d.ny()-1,px2 = d.nx()-1,py2 = 0;

        char tmp[100];
        if (message1.getGridLatLonCoordinatesByGridPoint(px1,py1,y1,x1)  &&  message1.getGridLatLonCoordinatesByGridPoint(px2,py2,y2,x2))
        {
          if (x2 < x1  &&  x2 < 0)
            x2 += 360;

          if (x2 < x1  && x1 >= 180)
            x1 -= 360;

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          attributeList.setAttribute("grid.llbox",tmp);
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
            attributeList.setAttribute("grid.bbox",tmp);
        }

        if (message1.getGridOriginalCoordinatesByGridPoint(0,0,x1,y1)  &&  message1.getGridOriginalCoordinatesByGridPoint(d.nx()-1,d.ny()-1,x2,y2))
        {
          if (message1.getGridProjection() == T::GridProjectionValue::LatLon)
          {
            if (x2 < x1  &&  x2 < 0)
              x2 += 360;

            if (x2 < x1  && x1 >= 180)
              x1 -= 360;
          }

          if (message1.reverseYDirection())
          {
            double tmp = y1;
            y1 = y2;
            y2 = tmp;
          }

          sprintf(tmp,"%f,%f,%f,%f",x1,y1,x2,y2);
          if (message1.getGridProjection() != T::GridProjectionValue::LatLon)
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

      attributeList.setAttribute("grid.projectionType",Fmi::to_string(message1.getGridProjection()));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    if (geometryIdStr != nullptr  &&  message1.getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridStreamlinesByTime(message1,message2,newTime,attributeList,modificationOperation,modificationParameters,streamlines);
      T::Dimensions  d = message1.getGridDimensions();
      attributeList.setAttribute("grid.width",Fmi::to_string(d.nx()));
      attributeList.setAttribute("grid.height",Fmi::to_string(d.ny()));
      return;
    }

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

    uint width = 0;
    uint height = 0;
    T::Coordinate_svec coordinates;
    T::Coordinate_svec latLonCoordinates;

    Identification::gridDef.getGridOriginalCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (!latLonCoordinates || latLonCoordinates->size() == 0)
    {
      getGridStreamlinesByTime(message1,message2,newTime,attributeList,modificationOperation,modificationParameters,streamlines);
      return;
    }

    T::ParamValue_vec gridValues;
    getGridValueVectorByTimeAndGeometry(message1,message2,newTime,attributeList,modificationOperation,modificationParameters,gridValues);

    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

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

    getStreamlines(gridValues,coordinatePtr,width,height,minStreamLen, maxStreamLen,lineLen,xStep,yStep,streamlines);

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.proj4",message1.getProj4());
    attributeList.setAttribute("grid.original.width",Fmi::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",Fmi::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.timeInterpolationMethod",Fmi::to_string(timeInterpolationMethod));
    attributeList.setAttribute("stream.coordinateType",Fmi::to_string(coordinateType));
    attributeList.setAttribute("grid.width",Fmi::to_string(width));
    attributeList.setAttribute("grid.height",Fmi::to_string(height));

    double wm = 0;
    double hm = 0;
    if (message1.getGridMetricCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
    else
    {
      attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

      message1.getGridCellAverageSize(wm,hm);
      attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridStreamlinesByLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,double newLevel,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& streamlines)
{
  FUNCTION_TRACE
  try
  {
    getGridStreamlinesByLevelAndGrid(message1,message2,newLevel,gridWidth,gridHeight,gridLatLonCoordinates,attributeList,0,EMPTY_DOUBLE_VEC,streamlines);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridStreamlinesByLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,double newLevel,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines)
{
  FUNCTION_TRACE
  try
  {
    short levelInterpolationMethod = T::LevelInterpolationMethod::Linear;
    const char *li = attributeList.getAttributeValue("grid.levelInterpolationMethod");
    if (li != nullptr)
      levelInterpolationMethod = toInt16(li);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *s = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (s != nullptr)
      areaInterpolationMethod = toInt16(s);

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
    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    message1.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,values1);
    message2.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,values2);
    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,gridValues);

    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinatePtr = &gridLatLonCoordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        break;
    }

    attributeList.setAttribute("grid.levelInterpolationMethod",Fmi::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(gridWidth));
    attributeList.setAttribute("grid.height",Fmi::to_string(gridHeight));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("stream.coordinateType",Fmi::to_string(coordinateType));

    getStreamlines(gridValues,coordinatePtr,gridWidth,gridHeight,minStreamLen, maxStreamLen,lineLen,xStep,yStep,streamlines);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridStreamlinesByTimeAndGrid(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& streamlines)
{
  FUNCTION_TRACE
  try
  {
    getGridStreamlinesByTimeAndGrid(message1,message2,newTime,gridWidth,gridHeight,gridLatLonCoordinates,attributeList,0,EMPTY_DOUBLE_VEC,streamlines);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridStreamlinesByTimeAndGrid(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines)
{
  FUNCTION_TRACE
  try
  {
    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *ti = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (ti != nullptr)
      timeInterpolationMethod = toInt16(ti);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *s = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (s != nullptr)
      areaInterpolationMethod = toInt16(s);

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
    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    message1.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,values1);
    message2.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,modificationOperation,modificationParameters,values2);

    timeInterpolation(values1,values2,message1.getForecastTimeT(),message2.getForecastTimeT(),newTime,timeInterpolationMethod,gridValues);

    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinatePtr = &gridLatLonCoordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        break;
    }

    attributeList.setAttribute("grid.timeInterpolationMethod",Fmi::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(gridWidth));
    attributeList.setAttribute("grid.height",Fmi::to_string(gridHeight));
    attributeList.setAttribute("grid.original.relativeUV",Fmi::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",Fmi::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("stream.coordinateType",Fmi::to_string(coordinateType));

    getStreamlines(gridValues,coordinatePtr,gridWidth,gridHeight,minStreamLen, maxStreamLen,lineLen,xStep,yStep,streamlines);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void MessageProcessing::getGridStreamlinesByTimeLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& streamlines) const
{
  FUNCTION_TRACE
  try
  {
    getGridStreamlinesByTimeLevelAndGrid(message1,message2,message3,message4,newTime,newLevel,gridWidth,gridHeight,gridLatLonCoordinates,attributeList,0,EMPTY_DOUBLE_VEC,streamlines);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridStreamlinesByTimeLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines) const
{
  FUNCTION_TRACE
  try
  {
    T::ParamValue_vec gridValues;
    getGridValueVectorByTimeLevelAndCoordinateList(message1,message2,message3,message4,newTime,newLevel,T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,attributeList,modificationOperation,modificationParameters,gridValues);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

    //T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    //const char *coordinateTypeStr = attributeList.getAttributeValue("stream.coordinateType");
    //if (coordinateTypeStr != nullptr)
    //  coordinateType = toUInt8(coordinateTypeStr);

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

    getStreamlines(gridValues,&gridLatLonCoordinates,gridWidth,gridHeight,minStreamLen, maxStreamLen,lineLen,xStep,yStep,streamlines);

    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",Fmi::to_string(gridWidth));
    attributeList.setAttribute("grid.height",Fmi::to_string(gridHeight));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}










void MessageProcessing::getGridValueByLevelAndPoint(const GRID::Message& message1,const GRID::Message& message2,int level1,int level2,double newLevel,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short levelInterpolationMethod,T::ParamValue& value) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueByLevelAndPoint(message1,message2,level1,level2,newLevel,coordinateType,x,y,areaInterpolationMethod,levelInterpolationMethod,0,EMPTY_DOUBLE_VEC,value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueByLevelAndPoint(const GRID::Message& message1,const GRID::Message& message2,int level1,int level2,double newLevel,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue& value) const
{
  FUNCTION_TRACE
  try
  {
    T::ParamValue value1 = ParamValueMissing;
    T::ParamValue value2 = ParamValueMissing;

    message1.getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,modificationOperation,modificationParameters,value1);
    message2.getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,modificationOperation,modificationParameters,value2);

    int l1 = level1;
    int l2 = level2;

    if (level1 < 0)
      l1 = message1.getGridParameterLevel();

    if (level2 < 0)
      l2 = message2.getGridParameterLevel();

    // If the levels are using different units (for example hPa and Pa), then we
    // try to tune levels so that : level1 < newLevel < level2

    if (level1 < 0 || level2 < 0)
      tuneLevels(l1,l2,newLevel);

    value = levelInterpolation(value1,value2,l1,l2,newLevel,levelInterpolationMethod);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueByTimeAndPoint(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short timeInterpolationMethod,T::ParamValue& value) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueByTimeAndPoint(message1,message2,newTime,coordinateType,x,y,areaInterpolationMethod,timeInterpolationMethod,0,EMPTY_DOUBLE_VEC,value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueByTimeAndPoint(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short timeInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue& value) const
{
  FUNCTION_TRACE
  try
  {
    T::ParamValue value1 = ParamValueMissing;
    T::ParamValue value2 = ParamValueMissing;

    message1.getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,modificationOperation,modificationParameters,value1);
    message2.getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,modificationOperation,modificationParameters,value2);

    value = timeInterpolation(value1,value2,message1.getForecastTimeT(),message2.getForecastTimeT(),newTime,timeInterpolationMethod);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueByTimeLevelAndPoint(const GRID::Message& message1,int level1,const GRID::Message& message2,int level2,const GRID::Message& message3,int level3,const GRID::Message& message4,int level4,time_t newTime,double newLevel,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,T::ParamValue& value) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueByTimeLevelAndPoint(message1,level1,message2,level2,message3,level3,message4,level4,newTime,newLevel,coordinateType,x,y,areaInterpolationMethod,timeInterpolationMethod,levelInterpolationMethod,0,EMPTY_DOUBLE_VEC,value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueByTimeLevelAndPoint(const GRID::Message& message1,int level1,const GRID::Message& message2,int level2,const GRID::Message& message3,int level3,const GRID::Message& message4,int level4,time_t newTime,double newLevel,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue& value) const
{
  FUNCTION_TRACE
  try
  {
    int prevTimeLevel1 = level1;
    if (level1 < 0)
      prevTimeLevel1 = message1.getGridParameterLevel();

    int prevTimeLevel2 = level2;
    if (level2 < 0)
      prevTimeLevel2 = message2.getGridParameterLevel();

    int nextTimeLevel1 = level3;
    if (level3 < 0)
      nextTimeLevel1 = message3.getGridParameterLevel();

    int nextTimeLevel2 = level4;
    if (level4 < 0)
      nextTimeLevel2 = message4.getGridParameterLevel();

    T::ParamValue prevTimePrevLevel = ParamValueMissing;
    T::ParamValue prevTimeNextLevel = ParamValueMissing;
    T::ParamValue prevValue = ParamValueMissing;

    T::ParamValue nextTimePrevLevel = ParamValueMissing;
    T::ParamValue nextTimeNextLevel = ParamValueMissing;
    T::ParamValue nextValue = ParamValueMissing;

    message1.getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,modificationOperation,modificationParameters,prevTimePrevLevel);
    message2.getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,modificationOperation,modificationParameters,prevTimeNextLevel);
    message3.getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,modificationOperation,modificationParameters,nextTimePrevLevel);
    message4.getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,modificationOperation,modificationParameters,nextTimeNextLevel);

    tuneLevels(prevTimeLevel1,prevTimeLevel2,newLevel);
    prevValue = levelInterpolation(prevTimePrevLevel,prevTimeNextLevel,prevTimeLevel1,prevTimeLevel2,newLevel,levelInterpolationMethod);

    tuneLevels(nextTimeLevel1,nextTimeLevel2,newLevel);
    nextValue = levelInterpolation(nextTimePrevLevel,nextTimeNextLevel,nextTimeLevel1,nextTimeLevel2,newLevel,levelInterpolationMethod);

    value = timeInterpolation(prevValue,nextValue,message1.getForecastTimeT(),message3.getForecastTimeT(),newTime,timeInterpolationMethod);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByLevelAndPointList(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByLevelAndPointList(message1,message2,newLevel,coordinateType,pointList,areaInterpolationMethod,levelInterpolationMethod,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByLevelAndPointList(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    message1.getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,modificationOperation,modificationParameters,values1);
    message2.getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,modificationOperation,modificationParameters,values2);

    int level1 = message1.getGridParameterLevel();
    int level2 = message2.getGridParameterLevel();

    // If the levels are using different units (for example hPa and Pa), then we
    // try to tune levels so that : level1 < newLevel < level2

    tuneLevels(level1,level2,newLevel);

    levelInterpolation(values1,values2,level1,level2,newLevel,levelInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByLevelAndCircle(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short levelInterpolationMethod,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByLevelAndCircle(message1,message2,newLevel,coordinateType,origoX,origoY,radius,levelInterpolationMethod,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByLevelAndCircle(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    message1.getGridValueListByCircle(coordinateType,origoX,origoY,radius,modificationOperation,modificationParameters,values1);
    message2.getGridValueListByCircle(coordinateType,origoX,origoY,radius,modificationOperation,modificationParameters,values2);

    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeAndCircle(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short timeInterpolationMethod,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByTimeAndCircle(message1,message2,newTime,coordinateType,origoX,origoY,radius,timeInterpolationMethod,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeAndCircle(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short timeInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    message1.getGridValueListByCircle(coordinateType,origoX,origoY,radius,modificationOperation,modificationParameters,values1);
    message2.getGridValueListByCircle(coordinateType,origoX,origoY,radius,modificationOperation,modificationParameters,values2);

    timeInterpolation(values1,values2,message1.getForecastTimeT(),message2.getForecastTimeT(),newTime,timeInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeLevelAndCircle(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByTimeLevelAndCircle(message1,message2,message3,message4,newTime,newLevel,coordinateType,origoX,origoY,radius,timeInterpolationMethod,levelInterpolationMethod,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void MessageProcessing::getGridValueListByTimeLevelAndCircle(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short timeInterpolationMethod,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    getGridValueListByTimeAndCircle(message1,message3,newTime,coordinateType,origoX,origoY,radius,timeInterpolationMethod,modificationOperation,modificationParameters,values1);
    getGridValueListByTimeAndCircle(message2,message4,newTime,coordinateType,origoX,origoY,radius,timeInterpolationMethod,modificationOperation,modificationParameters,values2);

    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void MessageProcessing::getGridValueListByTimeAndPointList(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short timeInterpolationMethod,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByTimeAndPointList(message1,message2,newTime,coordinateType,pointList,areaInterpolationMethod,timeInterpolationMethod,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeAndPointList(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short timeInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    message1.getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,modificationOperation,modificationParameters,values1);
    message2.getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,modificationOperation,modificationParameters,values2);

    timeInterpolation(values1,values2,message1.getForecastTimeT(),message2.getForecastTimeT(),newTime,timeInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByLevelAndPolygon(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short levelInterpolationMethod,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByLevelAndPolygon(message1,message2,newLevel,coordinateType,polygonPoints,levelInterpolationMethod,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByLevelAndPolygon(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    message1.getGridValueListByPolygon(coordinateType,polygonPoints,modificationOperation,modificationParameters,values1);
    message2.getGridValueListByPolygon(coordinateType,polygonPoints,modificationOperation,modificationParameters,values2);

    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeAndPolygon(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short timeInterpolationMethod,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByTimeAndPolygon(message1,message2,newTime,coordinateType,polygonPoints,timeInterpolationMethod,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeAndPolygon(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short timeInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    message1.getGridValueListByPolygon(coordinateType,polygonPoints,modificationOperation,modificationParameters,values1);
    message2.getGridValueListByPolygon(coordinateType,polygonPoints,modificationOperation,modificationParameters,values2);

    timeInterpolation(values1,values2,message1.getForecastTimeT(),message2.getForecastTimeT(),newTime,timeInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeLevelAndPolygon(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByTimeLevelAndPolygon(message1,message2,message3,message4,newTime,newLevel,coordinateType,polygonPoints,timeInterpolationMethod,levelInterpolationMethod,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeLevelAndPolygon(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short timeInterpolationMethod,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    getGridValueListByTimeAndPolygon(message1,message3,newTime,coordinateType,polygonPoints,timeInterpolationMethod,modificationOperation,modificationParameters,values1);
    getGridValueListByTimeAndPolygon(message2,message4,newTime,coordinateType,polygonPoints,timeInterpolationMethod,modificationOperation,modificationParameters,values2);

    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByLevelAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short levelInterpolationMethod,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByLevelAndPolygonPath(message1,message2,newLevel,coordinateType,polygonPath,levelInterpolationMethod,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByLevelAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    message1.getGridValueListByPolygonPath(coordinateType,polygonPath,modificationOperation,modificationParameters,values1);
    message2.getGridValueListByPolygonPath(coordinateType,polygonPath,modificationOperation,modificationParameters,values2);

    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short timeInterpolationMethod,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByTimeAndPolygonPath(message1,message2,newTime,coordinateType,polygonPath,timeInterpolationMethod,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short timeInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    message1.getGridValueListByPolygonPath(coordinateType,polygonPath,modificationOperation,modificationParameters,values1);
    message2.getGridValueListByPolygonPath(coordinateType,polygonPath,modificationOperation,modificationParameters,values2);

    timeInterpolation(values1,values2,message1.getForecastTimeT(),message2.getForecastTimeT(),newTime,timeInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeLevelAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByTimeLevelAndPolygonPath(message1,message2,message3,message4,newTime,newLevel,coordinateType,polygonPath,timeInterpolationMethod,levelInterpolationMethod,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeLevelAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short timeInterpolationMethod,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    getGridValueListByTimeAndPolygonPath(message1,message3,newTime,coordinateType,polygonPath,timeInterpolationMethod,modificationOperation,modificationParameters,values1);
    getGridValueListByTimeAndPolygonPath(message2,message4,newTime,coordinateType,polygonPath,timeInterpolationMethod,modificationOperation,modificationParameters,values2);

    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeLevelAndPointList(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueListByTimeLevelAndPointList(message1,message2,message3,message4,newTime,newLevel,coordinateType,pointList,areaInterpolationMethod,timeInterpolationMethod,levelInterpolationMethod,0,EMPTY_DOUBLE_VEC,valueList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeLevelAndPointList(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    int prevTimeLevel1 = message1.getGridParameterLevel();
    int prevTimeLevel2 = message2.getGridParameterLevel();

    int nextTimeLevel1 = message3.getGridParameterLevel();
    int nextTimeLevel2 = message4.getGridParameterLevel();

    T::GridValueList prevTimePrevLevel;
    T::GridValueList prevTimeNextLevel;
    T::GridValueList prevValues;

    T::GridValueList nextTimePrevLevel;
    T::GridValueList nextTimeNextLevel;
    T::GridValueList nextValues;

    message1.getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,modificationOperation,modificationParameters,prevTimePrevLevel);
    message2.getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,modificationOperation,modificationParameters,prevTimeNextLevel);
    message3.getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,modificationOperation,modificationParameters,nextTimePrevLevel);
    message4.getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,modificationOperation,modificationParameters,nextTimeNextLevel);

    if (prevTimeLevel1 == nextTimeLevel1  &&  prevTimeLevel2 == nextTimeLevel2)
    {
      timeInterpolation(prevTimePrevLevel,nextTimePrevLevel,message1.getForecastTimeT(),message3.getForecastTimeT(),newTime,timeInterpolationMethod,prevValues);
      timeInterpolation(prevTimeNextLevel,nextTimeNextLevel,message2.getForecastTimeT(),message4.getForecastTimeT(),newTime,timeInterpolationMethod,nextValues);

      tuneLevels(prevTimeLevel1,prevTimeLevel2,newLevel);
      levelInterpolation(prevValues,nextValues,prevTimeLevel1,prevTimeLevel2,newLevel,levelInterpolationMethod,valueList);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByLevel(const GRID::Message& message1,const GRID::Message& message2,double newLevel,short levelInterpolationMethod,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByLevel(message1,message2,newLevel,levelInterpolationMethod,0,EMPTY_DOUBLE_VEC,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByLevel(const GRID::Message& message1,const GRID::Message& message2,double newLevel,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    int level1 = message1.getGridParameterLevel();
    int level2 = message2.getGridParameterLevel();

    // If the levels are using different units (for example hPa and Pa), then we
    // try to tune levels so that : level1 < newLevel < level2

    tuneLevels(level1,level2,newLevel);

    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    message1.getGridValueVectorWithCaching(modificationOperation,modificationParameters,values1);
    message2.getGridValueVectorWithCaching(modificationOperation,modificationParameters,values2);

    levelInterpolation(values1,values2,level1,level2,newLevel,levelInterpolationMethod,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,short timeInterpolationMethod,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByTime(message1,message2,newTime,timeInterpolationMethod,0,EMPTY_DOUBLE_VEC,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,short timeInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    time_t tt = newTime;
    time_t t1 = message1.getForecastTimeT();
    time_t t2 = message2.getForecastTimeT();

    if (timeInterpolationMethod == T::TimeInterpolationMethod::Undefined  || timeInterpolationMethod == T::TimeInterpolationMethod::None ||
        (timeInterpolationMethod == T::TimeInterpolationMethod::Nearest  &&  (tt-t1) <= (t2-tt)) ||
        (timeInterpolationMethod == T::TimeInterpolationMethod::Linear  &&  tt == t1))
    {
      message1.getGridValueVectorWithCaching(modificationOperation,modificationParameters,values);
      return;
    }

    if ((timeInterpolationMethod == T::TimeInterpolationMethod::Nearest  &&  (tt-t1) > (t2-tt)) ||
        (timeInterpolationMethod == T::TimeInterpolationMethod::Linear  &&  tt == t2))
    {
      message2.getGridValueVectorWithCaching(modificationOperation,modificationParameters,values);
      return;
    }

    T::ParamValue_vec values1;
    T::ParamValue_vec values2;
    message1.getGridValueVectorWithCaching(modificationOperation,modificationParameters,values1);
    message2.getGridValueVectorWithCaching(modificationOperation,modificationParameters,values2);

    timeInterpolation(values1,values2,t1,t2,tt,timeInterpolationMethod,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByLevelAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByLevelAndCoordinateList(message1,message2,newLevel,coordinateType,coordinates,attributeList,0,EMPTY_DOUBLE_VEC,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByLevelAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    short levelInterpolationMethod = T::LevelInterpolationMethod::Linear;
    const char *levelInterpolationMethodStr = attributeList.getAttributeValue("grid.levelInterpolationMethod");
    if (levelInterpolationMethodStr != nullptr)
      levelInterpolationMethod = toInt16(levelInterpolationMethodStr);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.levelInterpolationMethod",Fmi::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.coordinateType",Fmi::to_string(coordinateType));

    if (coordinates.size() == 0)
      return;

    T::ParamValue_vec gridValues1;
    message1.getGridValueVectorByCoordinateList(coordinateType,coordinates,areaInterpolationMethod,modificationOperation,modificationParameters,gridValues1);

    T::ParamValue_vec gridValues2;
    message2.getGridValueVectorByCoordinateList(coordinateType,coordinates,areaInterpolationMethod,modificationOperation,modificationParameters,gridValues2);

    levelInterpolation(gridValues1,gridValues2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTimeAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByTimeAndCoordinateList(message1,message2,newTime,coordinateType,coordinates,attributeList,0,EMPTY_DOUBLE_VEC,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTimeAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

    short areaInterpolationMethod = T::AreaInterpolationMethod::Linear;
    const char *areaInterpolationMethodStr = attributeList.getAttributeValue("grid.areaInterpolationMethod");
    if (areaInterpolationMethodStr != nullptr)
      areaInterpolationMethod = toInt16(areaInterpolationMethodStr);

    attributeList.setAttribute("grid.areaInterpolationMethod",Fmi::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.timeInterpolationMethod",Fmi::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.coordinateType",Fmi::to_string(coordinateType));

    if (coordinates.size() == 0)
      return;

    T::ParamValue_vec gridValues1;
    message1.getGridValueVectorByCoordinateList(coordinateType,coordinates,areaInterpolationMethod,modificationOperation,modificationParameters,gridValues1);

    T::ParamValue_vec gridValues2;
    message2.getGridValueVectorByCoordinateList(coordinateType,coordinates,areaInterpolationMethod,modificationOperation,modificationParameters,gridValues2);

    timeInterpolation(gridValues1,gridValues2,message1.getForecastTimeT(),message2.getForecastTimeT(),newTime,timeInterpolationMethod,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::AttributeList& attributeList,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByLevelAndGeometry(message1,message2,newLevel,attributeList,0,EMPTY_DOUBLE_VEC,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    short levelInterpolationMethod = T::LevelInterpolationMethod::Linear;
    const char *levelInterpolationMethodStr = attributeList.getAttributeValue("grid.levelInterpolationMethod");
    if (levelInterpolationMethodStr != nullptr)
      levelInterpolationMethod = toInt16(levelInterpolationMethodStr);

    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    message1.getGridValueVectorByGeometry(attributeList,modificationOperation,modificationParameters,values1);
    message2.getGridValueVectorByGeometry(attributeList,modificationOperation,modificationParameters,values2);

    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::AttributeList& attributeList,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByTimeAndGeometry(message1,message2,newTime,attributeList,0,EMPTY_DOUBLE_VEC,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    message1.getGridValueVectorByGeometry(attributeList,modificationOperation,modificationParameters,values1);
    message2.getGridValueVectorByGeometry(attributeList,modificationOperation,modificationParameters,values2);

    timeInterpolation(values1,values2,message1.getForecastTimeT(),message2.getForecastTimeT(),newTime,timeInterpolationMethod,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,areaInterpolationMethod,timeInterpolationMethod,levelInterpolationMethod,0,EMPTY_DOUBLE_VEC,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    getGridValueVectorByLevel(message1,message2,newLevel,levelInterpolationMethod,modificationOperation,modificationParameters,values1);
    getGridValueVectorByLevel(message3,message4,newLevel,levelInterpolationMethod,modificationOperation,modificationParameters,values2);

    timeInterpolation(values1,values2,message1.getForecastTimeT(),message3.getForecastTimeT(),newTime,timeInterpolationMethod,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::AttributeList& attributeList,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByTimeLevelAndGeometry(message1,message2,message3,message4,newTime,newLevel,attributeList,0,EMPTY_DOUBLE_VEC,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    getGridValueVectorByLevelAndGeometry(message1,message2,newLevel,attributeList,modificationOperation,modificationParameters,values1);
    getGridValueVectorByLevelAndGeometry(message3,message4,newLevel,attributeList,modificationOperation,modificationParameters,values2);

    timeInterpolation(values1,values2,message1.getForecastTimeT(),message3.getForecastTimeT(),newTime,timeInterpolationMethod,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTimeLevelAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    getGridValueVectorByTimeLevelAndCoordinateList(message1,message2,message3,message4,newTime,newLevel,coordinateType,coordinates,attributeList,0,EMPTY_DOUBLE_VEC,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTimeLevelAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    getGridValueVectorByLevelAndCoordinateList(message1,message2,newLevel,coordinateType,coordinates,attributeList,modificationOperation,modificationParameters,values1);
    getGridValueVectorByLevelAndCoordinateList(message3,message4,newLevel,coordinateType,coordinates,attributeList,modificationOperation,modificationParameters,values2);

    timeInterpolation(values1,values2,message1.getForecastTimeT(),message3.getForecastTimeT(),newTime,timeInterpolationMethod,values);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}  // namespace GRID
}  // namespace SmartMet

