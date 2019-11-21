#include "MessageProcessing.h"
#include "../common/InterpolationFunctions.h"
#include "../common/GeneralFunctions.h"
#include "../identification/GridDef.h"

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





void MessageProcessing::getGridIsobandsByLevel(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
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
    getGridValueVectorByLevel(message1,message2,newLevel,levelInterpolationMethod,gridValues);

    T::Dimensions d = message1.getGridDimensions();
    T::Coordinate_vec coordinates;
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = message1.getGridLatLonCoordinates();
        coordinatePtr = &coordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = message1.getGridCoordinates();
        coordinatePtr = &coordinates;
        break;
    }

    getIsobands(gridValues,coordinatePtr,d.nx(),d.ny(),contourLowValues,contourHighValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.width",std::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",std::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.levelInterpolationMethod",std::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",std::to_string(d.nx()));
    attributeList.setAttribute("grid.height",std::to_string(d.ny()));
    attributeList.setAttribute("grid.relativeUV",std::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.global",std::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.reverseYDirection",std::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.reverseXDirection",std::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));

    double wm = 0;
    double hm = 0;
    if (message1.getGridCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",std::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",std::to_string(hm));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTime(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
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
    getGridValueVectorByTime(message1,message2,newTime,timeInterpolationMethod,gridValues);

    T::Dimensions d = message1.getGridDimensions();
    T::Coordinate_vec coordinates;
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = message1.getGridLatLonCoordinates();
        coordinatePtr = &coordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = message1.getGridCoordinates();
        coordinatePtr = &coordinates;
        break;
    }

    getIsobands(gridValues,coordinatePtr,d.nx(),d.ny(),contourLowValues,contourHighValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.timeInterpolationMethod",std::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",std::to_string(d.nx()));
    attributeList.setAttribute("grid.height",std::to_string(d.ny()));
    attributeList.setAttribute("grid.relativeUV",std::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.global",std::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.reverseYDirection",std::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.reverseXDirection",std::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsobandsByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  try
  {
    const char *crsStr = attributeList.getAttributeValue("grid.crs");
    const char *llboxStr = attributeList.getAttributeValue("grid.llbox");
    const char *gridSizeStr = attributeList.getAttributeValue("grid.size");

    if (gridSizeStr != nullptr)
    {
      double m = toDouble(gridSizeStr);
      if (m > 0)
      {
        attributeList.setAttribute("grid.width",std::to_string(C_INT(C_DOUBLE(message1.getGridWidth())*m)));
        attributeList.setAttribute("grid.height",std::to_string(C_INT(C_DOUBLE(message1.getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      attributeList.setAttribute("grid.crs",message1.getWKT());
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

      attributeList.setAttribute("grid.projectionType",std::to_string(message1.getGridProjection()));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    if (geometryIdStr != nullptr  &&  message1.getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridIsobandsByLevel(message1,message2,newLevel,contourLowValues,contourHighValues,attributeList,contours);
      T::Dimensions  d = message1.getGridDimensions();
      attributeList.setAttribute("grid.width",std::to_string(d.nx()));
      attributeList.setAttribute("grid.height",std::to_string(d.ny()));
      return;
    }

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    uint width = 0;
    uint height = 0;
    T::Coordinate_vec coordinates;
    T::Coordinate_vec latLonCoordinates;

    Identification::gridDef.getGridCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (latLonCoordinates.size() == 0)
    {
      getGridIsobandsByLevel(message1,message2,newLevel,contourLowValues,contourHighValues,attributeList,contours);
      return;
    }

    T::ParamValue_vec gridValues;
    getGridValueVectorByLevelAndGeometry(message1,message2,newLevel,attributeList,gridValues);

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
        coordinatePtr = &latLonCoordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinatePtr = &coordinates;
        break;
    }

    getIsobands(gridValues,coordinatePtr,width,height,contourLowValues,contourHighValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.width",std::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",std::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",std::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",std::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));
    attributeList.setAttribute("grid.width",std::to_string(width));
    attributeList.setAttribute("grid.height",std::to_string(height));

    double wm = 0;
    double hm = 0;
    if (message1.getGridCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",std::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",std::to_string(hm));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




void MessageProcessing::getGridIsobandsByLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours)
{
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

    message1.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,values1);
    message2.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,values2);
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

    attributeList.setAttribute("grid.levelInterpolationMethod",std::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",std::to_string(gridWidth));
    attributeList.setAttribute("grid.height",std::to_string(gridHeight));
    attributeList.setAttribute("grid.original.relativeUV",std::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",std::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.reverseYDirection",std::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.reverseXDirection",std::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));

    getIsobands(gridValues,coordinatePtr,gridWidth,gridHeight,contourLowValues,contourHighValues,areaInterpolationMethod,smooth_size,smooth_degree,contours);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTimeAndGrid(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours)
{
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

    message1.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,values1);
    message2.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,values2);
    timeInterpolation(values1,values2,message1.getForecastTime(),message2.getForecastTime(),newTime,timeInterpolationMethod,gridValues);

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

    attributeList.setAttribute("grid.timeInterpolationMethod",std::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",std::to_string(gridWidth));
    attributeList.setAttribute("grid.height",std::to_string(gridHeight));
    attributeList.setAttribute("grid.relativeUV",std::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.global",std::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.reverseYDirection",std::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.reverseXDirection",std::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));

    getIsobands(gridValues,coordinatePtr,gridWidth,gridHeight,contourLowValues,contourHighValues,areaInterpolationMethod,smooth_size,smooth_degree,contours);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




void MessageProcessing::getGridIsobandsByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  try
  {
    const char *crsStr = attributeList.getAttributeValue("grid.crs");
    const char *llboxStr = attributeList.getAttributeValue("grid.llbox");
    const char *gridSizeStr = attributeList.getAttributeValue("grid.size");

    if (gridSizeStr != nullptr)
    {
      double m = toDouble(gridSizeStr);
      if (m > 0)
      {
        attributeList.setAttribute("grid.width",std::to_string(C_INT(C_DOUBLE(message1.getGridWidth())*m)));
        attributeList.setAttribute("grid.height",std::to_string(C_INT(C_DOUBLE(message1.getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      attributeList.setAttribute("grid.crs",message1.getWKT());
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

      attributeList.setAttribute("grid.projectionType",std::to_string(message1.getGridProjection()));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    if (geometryIdStr != nullptr  &&  message1.getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridIsobandsByTime(message1,message2,newTime,contourLowValues,contourHighValues,attributeList,contours);
      T::Dimensions  d = message1.getGridDimensions();
      attributeList.setAttribute("grid.width",std::to_string(d.nx()));
      attributeList.setAttribute("grid.height",std::to_string(d.ny()));
      return;
    }

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    uint width = 0;
    uint height = 0;
    T::Coordinate_vec coordinates;
    T::Coordinate_vec latLonCoordinates;

    Identification::gridDef.getGridCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (latLonCoordinates.size() == 0)
    {
      getGridIsobandsByTime(message1,message2,newTime,contourLowValues,contourHighValues,attributeList,contours);
      return;
    }

    T::ParamValue_vec gridValues;
    getGridValueVectorByTimeAndGeometry(message1,message2,newTime,attributeList,gridValues);

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
        coordinatePtr = &latLonCoordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinatePtr = &coordinates;
        break;
    }

    getIsobands(gridValues,coordinatePtr,width,height,contourLowValues,contourHighValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.width",std::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",std::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",std::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",std::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));
    attributeList.setAttribute("grid.width",std::to_string(width));
    attributeList.setAttribute("grid.height",std::to_string(height));

    double wm = 0;
    double hm = 0;
    if (message1.getGridCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",std::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",std::to_string(hm));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,std::string newTime,int newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
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
    getGridValueVectorByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,areaInterpolationMethod,timeInterpolationMethod,levelInterpolationMethod,gridValues);

    T::Dimensions d = message1.getGridDimensions();
    T::Coordinate_vec coordinates;
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = message1.getGridLatLonCoordinates();
        coordinatePtr = &coordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = message1.getGridCoordinates();
        coordinatePtr = &coordinates;
        break;
    }

    getIsobands(gridValues,coordinatePtr,d.nx(),d.ny(),contourLowValues,contourHighValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.timeInterpolationMethod",std::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.levelInterpolationMethod",std::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.width",std::to_string(d.nx()));
    attributeList.setAttribute("grid.height",std::to_string(d.ny()));
    attributeList.setAttribute("grid.relativeUV",std::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.global",std::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.reverseYDirection",std::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.reverseXDirection",std::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,std::string newTime,int newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  try
  {
    const char *crsStr = attributeList.getAttributeValue("grid.crs");
    const char *llboxStr = attributeList.getAttributeValue("grid.llbox");
    const char *gridSizeStr = attributeList.getAttributeValue("grid.size");

    if (gridSizeStr != nullptr)
    {
      double m = toDouble(gridSizeStr);
      if (m > 0)
      {
        attributeList.setAttribute("grid.width",std::to_string(C_INT(C_DOUBLE(message1.getGridWidth())*m)));
        attributeList.setAttribute("grid.height",std::to_string(C_INT(C_DOUBLE(message1.getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      attributeList.setAttribute("grid.crs",message1.getWKT());
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

      attributeList.setAttribute("grid.projectionType",std::to_string(message1.getGridProjection()));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    if (geometryIdStr != nullptr  &&  message1.getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridIsobandsByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,contourLowValues,contourHighValues,attributeList,contours);
      T::Dimensions  d = message1.getGridDimensions();
      attributeList.setAttribute("grid.width",std::to_string(d.nx()));
      attributeList.setAttribute("grid.height",std::to_string(d.ny()));
      return;
    }

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    uint width = 0;
    uint height = 0;
    T::Coordinate_vec coordinates;
    T::Coordinate_vec latLonCoordinates;

    Identification::gridDef.getGridCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (latLonCoordinates.size() == 0)
    {
      getGridIsobandsByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,contourLowValues,contourHighValues,attributeList,contours);
      return;
    }

    T::ParamValue_vec gridValues;
    getGridValueVectorByTimeLevelAndGeometry(message1,message2,message3,message4,newTime,newLevel,attributeList,gridValues);

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
        coordinatePtr = &latLonCoordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinatePtr = &coordinates;
        break;
    }

    getIsobands(gridValues,coordinatePtr,width,height,contourLowValues,contourHighValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.width",std::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",std::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.ogiginal.relativeUV",std::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",std::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));
    attributeList.setAttribute("grid.width",std::to_string(width));
    attributeList.setAttribute("grid.height",std::to_string(height));

    double wm = 0;
    double hm = 0;
    if (message1.getGridCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",std::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",std::to_string(hm));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTimeLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,std::string newTime,int newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  try
  {
    T::ParamValue_vec gridValues;
    getGridValueVectorByTimeLevelAndCoordinateList(message1,message2,message3,message4,newTime,newLevel,T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,attributeList,gridValues);

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

    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",std::to_string(gridWidth));
    attributeList.setAttribute("grid.height",std::to_string(gridHeight));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,std::string newTime,int newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
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
    getGridValueVectorByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,areaInterpolationMethod,timeInterpolationMethod,levelInterpolationMethod,gridValues);

    T::Dimensions d = message1.getGridDimensions();
    T::Coordinate_vec coordinates;
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = message1.getGridLatLonCoordinates();
        coordinatePtr = &coordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = message1.getGridCoordinates();
        coordinatePtr = &coordinates;
        break;
    }

    getIsolines(gridValues,coordinatePtr,d.nx(),d.ny(),contourValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.timeInterpolationMethod",std::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.levelInterpolationMethod",std::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.width",std::to_string(d.nx()));
    attributeList.setAttribute("grid.height",std::to_string(d.ny()));
    attributeList.setAttribute("grid.relativeUV",std::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.global",std::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.reverseYDirection",std::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.reverseXDirection",std::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,std::string newTime,int newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  try
  {
    const char *crsStr = attributeList.getAttributeValue("grid.crs");
    const char *llboxStr = attributeList.getAttributeValue("grid.llbox");
    const char *gridSizeStr = attributeList.getAttributeValue("grid.size");

    if (gridSizeStr != nullptr)
    {
      double m = toDouble(gridSizeStr);
      if (m > 0)
      {
        attributeList.setAttribute("grid.width",std::to_string(C_INT(C_DOUBLE(message1.getGridWidth())*m)));
        attributeList.setAttribute("grid.height",std::to_string(C_INT(C_DOUBLE(message1.getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      attributeList.setAttribute("grid.crs",message1.getWKT());
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

      attributeList.setAttribute("grid.projectionType",std::to_string(message1.getGridProjection()));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    if (geometryIdStr != nullptr  &&  message1.getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridIsolinesByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,contourValues,attributeList,contours);
      T::Dimensions  d = message1.getGridDimensions();
      attributeList.setAttribute("grid.width",std::to_string(d.nx()));
      attributeList.setAttribute("grid.height",std::to_string(d.ny()));
      return;
    }

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    uint width = 0;
    uint height = 0;
    T::Coordinate_vec coordinates;
    T::Coordinate_vec latLonCoordinates;

    Identification::gridDef.getGridCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (latLonCoordinates.size() == 0)
    {
      getGridIsolinesByTimeAndLevel(message1,message2,message3,message4,newTime,newLevel,contourValues,attributeList,contours);
      return;
    }

    T::ParamValue_vec gridValues;
    getGridValueVectorByTimeLevelAndGeometry(message1,message2,message3,message4,newTime,newLevel,attributeList,gridValues);

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
        coordinatePtr = &latLonCoordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinatePtr = &coordinates;
        break;
    }

    getIsolines(gridValues,coordinatePtr,width,height,contourValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.width",std::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",std::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",std::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",std::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.timeInterpolationMethod",std::to_string(timeInterpolationMethod));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));
    attributeList.setAttribute("grid.width",std::to_string(width));
    attributeList.setAttribute("grid.height",std::to_string(height));

    double wm = 0;
    double hm = 0;
    if (message1.getGridCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",std::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",std::to_string(hm));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsolinesByLevel(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
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
    getGridValueVectorByLevel(message1,message2,newLevel,levelInterpolationMethod,gridValues);

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
    T::Coordinate_vec coordinates;
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = message1.getGridLatLonCoordinates();
        coordinatePtr = &coordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = message1.getGridCoordinates();
        coordinatePtr = &coordinates;
        break;
    }

    getIsolines(gridValues,coordinatePtr,d.nx(),d.ny(),contourValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.levelInterpolationMethod",std::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",std::to_string(d.nx()));
    attributeList.setAttribute("grid.height",std::to_string(d.ny()));
    attributeList.setAttribute("grid.relativeUV",std::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.global",std::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.reverseYDirection",std::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.reverseXDirection",std::to_string((int)message2.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTime(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
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
    getGridValueVectorByTime(message1,message2,newTime,timeInterpolationMethod,gridValues);

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
    T::Coordinate_vec coordinates;
    T::Coordinate_vec *coordinatePtr = nullptr;

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        coordinates = message1.getGridLatLonCoordinates();
        coordinatePtr = &coordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinates = message1.getGridCoordinates();
        coordinatePtr = &coordinates;
        break;
    }

    getIsolines(gridValues,coordinatePtr,d.nx(),d.ny(),contourValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    //attributeList.setAttribute("grid.timeInterpolationMethod",std::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",std::to_string(d.nx()));
    attributeList.setAttribute("grid.height",std::to_string(d.ny()));
    attributeList.setAttribute("grid.relativeUV",std::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.global",std::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.reverseYDirection",std::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.reverseXDirection",std::to_string((int)message2.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsolinesByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  try
  {
    const char *crsStr = attributeList.getAttributeValue("grid.crs");
    const char *llboxStr = attributeList.getAttributeValue("grid.llbox");
    const char *gridSizeStr = attributeList.getAttributeValue("grid.size");

    if (gridSizeStr != nullptr)
    {
      double m = toDouble(gridSizeStr);
      if (m > 0)
      {
        attributeList.setAttribute("grid.width",std::to_string(C_INT(C_DOUBLE(message1.getGridWidth())*m)));
        attributeList.setAttribute("grid.height",std::to_string(C_INT(C_DOUBLE(message1.getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      attributeList.setAttribute("grid.crs",message1.getWKT());
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

      attributeList.setAttribute("grid.projectionType",std::to_string(message1.getGridProjection()));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    if (geometryIdStr != nullptr  &&  message1.getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridIsolinesByLevel(message1,message2,newLevel,contourValues,attributeList,contours);
      T::Dimensions  d = message1.getGridDimensions();
      attributeList.setAttribute("grid.width",std::to_string(d.nx()));
      attributeList.setAttribute("grid.height",std::to_string(d.ny()));
      return;
    }

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    uint width = 0;
    uint height = 0;
    T::Coordinate_vec coordinates;
    T::Coordinate_vec latLonCoordinates;

    Identification::gridDef.getGridCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (latLonCoordinates.size() == 0)
    {
      getGridIsolinesByLevel(message1,message2,newLevel,contourValues,attributeList,contours);
      return;
    }

    T::ParamValue_vec gridValues;
    getGridValueVectorByLevelAndGeometry(message1,message2,newLevel,attributeList,gridValues);

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
        coordinatePtr = &latLonCoordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinatePtr = &coordinates;
        break;
    }

    getIsolines(gridValues,coordinatePtr,width,height,contourValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.width",std::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",std::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",std::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",std::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.timeInterpolationMethod",std::to_string(timeInterpolationMethod));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));
    attributeList.setAttribute("grid.width",std::to_string(width));
    attributeList.setAttribute("grid.height",std::to_string(height));

    double wm = 0;
    double hm = 0;
    if (message1.getGridCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",std::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",std::to_string(hm));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  try
  {
    const char *crsStr = attributeList.getAttributeValue("grid.crs");
    const char *llboxStr = attributeList.getAttributeValue("grid.llbox");
    const char *gridSizeStr = attributeList.getAttributeValue("grid.size");

    if (gridSizeStr != nullptr)
    {
      double m = toDouble(gridSizeStr);
      if (m > 0)
      {
        attributeList.setAttribute("grid.width",std::to_string(C_INT(C_DOUBLE(message1.getGridWidth())*m)));
        attributeList.setAttribute("grid.height",std::to_string(C_INT(C_DOUBLE(message1.getGridHeight())*m)));
      }
    }

    if (crsStr != nullptr &&  strcasecmp(crsStr,"data") == 0)
    {
      attributeList.setAttribute("grid.crs",message1.getWKT());
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

      attributeList.setAttribute("grid.projectionType",std::to_string(message1.getGridProjection()));
    }

    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    if (geometryIdStr != nullptr  &&  message1.getGridGeometryId() == toInt32(geometryIdStr))
    {
      getGridIsolinesByTime(message1,message2,newTime,contourValues,attributeList,contours);
      T::Dimensions  d = message1.getGridDimensions();
      attributeList.setAttribute("grid.width",std::to_string(d.nx()));
      attributeList.setAttribute("grid.height",std::to_string(d.ny()));
      return;
    }

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

    uint width = 0;
    uint height = 0;
    T::Coordinate_vec coordinates;
    T::Coordinate_vec latLonCoordinates;

    Identification::gridDef.getGridCoordinatesByGeometry(attributeList,latLonCoordinates,coordinateType,coordinates,width,height);

    if (latLonCoordinates.size() == 0)
    {
      getGridIsolinesByTime(message1,message2,newTime,contourValues,attributeList,contours);
      return;
    }

    T::ParamValue_vec gridValues;
    getGridValueVectorByTimeAndGeometry(message1,message2,newTime,attributeList,gridValues);

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
        coordinatePtr = &latLonCoordinates;
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        coordinatePtr = &coordinates;
        break;
    }

    getIsolines(gridValues,coordinatePtr,width,height,contourValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.original.crs",message1.getWKT());
    attributeList.setAttribute("grid.original.width",std::to_string(message1.getGridWidth()));
    attributeList.setAttribute("grid.original.height",std::to_string(message1.getGridHeight()));
    attributeList.setAttribute("grid.original.relativeUV",std::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.original.global",std::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.timeInterpolationMethod",std::to_string(timeInterpolationMethod));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));
    attributeList.setAttribute("grid.width",std::to_string(width));
    attributeList.setAttribute("grid.height",std::to_string(height));

    double wm = 0;
    double hm = 0;
    if (message1.getGridCellSize(wm,hm))
    {
      attributeList.setAttribute("grid.original.cell.width",std::to_string(wm));
      attributeList.setAttribute("grid.original.cell.height",std::to_string(hm));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsolinesByLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours)
{
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

    message1.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,values1);
    message2.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,values2);
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

    attributeList.setAttribute("grid.levelInterpolationMethod",std::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",std::to_string(gridWidth));
    attributeList.setAttribute("grid.height",std::to_string(gridHeight));
    attributeList.setAttribute("grid.relativeUV",std::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.global",std::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.reverseYDirection",std::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.reverseXDirection",std::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));

    getIsolines(gridValues,coordinatePtr,gridWidth,gridHeight,contourValues,areaInterpolationMethod,smooth_size,smooth_degree,contours);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTimeAndGrid(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours)
{
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

    message1.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,values1);
    message2.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,areaInterpolationMethod,values2);
    timeInterpolation(values1,values2,message1.getForecastTime(),message2.getForecastTime(),newTime,timeInterpolationMethod,gridValues);

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

    attributeList.setAttribute("grid.timeInterpolationMethod",std::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",std::to_string(gridWidth));
    attributeList.setAttribute("grid.height",std::to_string(gridHeight));
    attributeList.setAttribute("grid.relativeUV",std::to_string((int)message1.isRelativeUV()));
    attributeList.setAttribute("grid.global",std::to_string((int)message1.isGridGlobal()));
    attributeList.setAttribute("grid.reverseYDirection",std::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.reverseXDirection",std::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));

    getIsolines(gridValues,coordinatePtr,gridWidth,gridHeight,contourValues,areaInterpolationMethod,smooth_size,smooth_degree,contours);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




void MessageProcessing::getGridIsolinesByTimeLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,std::string newTime,int newLevel,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours) const
{
  try
  {
    T::ParamValue_vec gridValues;
    getGridValueVectorByTimeLevelAndCoordinateList(message1,message2,message3,message4,newTime,newLevel,T::CoordinateTypeValue::LATLON_COORDINATES,gridLatLonCoordinates,attributeList,gridValues);

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

    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",std::to_string(gridWidth));
    attributeList.setAttribute("grid.height",std::to_string(gridHeight));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueByLevelAndPoint(const GRID::Message& message1,const GRID::Message& message2,int level1,int level2,int newLevel,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short levelInterpolationMethod,T::ParamValue& value) const
{
  try
  {
    T::ParamValue value1 = ParamValueMissing;
    T::ParamValue value2 = ParamValueMissing;

    message1.getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,value1);
    message2.getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,value2);

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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueByTimeAndPoint(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short timeInterpolationMethod,T::ParamValue& value) const
{
  try
  {
    T::ParamValue value1 = ParamValueMissing;
    T::ParamValue value2 = ParamValueMissing;

    message1.getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,value1);
    message2.getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,value2);

    value = timeInterpolation(value1,value2,message1.getForecastTime(),message2.getForecastTime(),newTime,timeInterpolationMethod);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueByTimeLevelAndPoint(const GRID::Message& message1,int level1,const GRID::Message& message2,int level2,const GRID::Message& message3,int level3,const GRID::Message& message4,int level4,std::string newTime,int newLevel,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,T::ParamValue& value) const
{
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

    T::ParamValue prevTimePrevLevel;
    T::ParamValue prevTimeNextLevel;
    T::ParamValue prevValue;

    T::ParamValue nextTimePrevLevel;
    T::ParamValue nextTimeNextLevel;
    T::ParamValue nextValue;

    message1.getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,prevTimePrevLevel);
    message2.getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,prevTimeNextLevel);
    message3.getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,nextTimePrevLevel);
    message4.getGridValueByPoint(coordinateType,x,y,areaInterpolationMethod,nextTimeNextLevel);

    //printf("LEVELS %d %d %d %d\n",prevTimeLevel1,prevTimeLevel2,nextTimeLevel1,nextTimeLevel2);

    //printf("VALUES %f  %f  %f  %f\n",prevTimePrevLevel,prevTimeNextLevel,nextTimePrevLevel,nextTimeNextLevel);

    tuneLevels(prevTimeLevel1,prevTimeLevel2,newLevel);
    prevValue = levelInterpolation(prevTimePrevLevel,prevTimeNextLevel,prevTimeLevel1,prevTimeLevel2,newLevel,levelInterpolationMethod);

    tuneLevels(nextTimeLevel1,nextTimeLevel2,newLevel);
    nextValue = levelInterpolation(nextTimePrevLevel,nextTimeNextLevel,nextTimeLevel1,nextTimeLevel2,newLevel,levelInterpolationMethod);

    value = timeInterpolation(prevValue,nextValue,message1.getForecastTime(),message3.getForecastTime(),newTime,timeInterpolationMethod);

    //printf("VALUE %f  %d\n",value,newLevel);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueListByLevelAndPointList(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const
{
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    message1.getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,values1);
    message2.getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,values2);

    int level1 = message1.getGridParameterLevel();
    int level2 = message2.getGridParameterLevel();

    // If the levels are using different units (for example hPa and Pa), then we
    // try to tune levels so that : level1 < newLevel < level2

    tuneLevels(level1,level2,newLevel);

    levelInterpolation(values1,values2,level1,level2,newLevel,levelInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueListByLevelAndCircle(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short levelInterpolationMethod,T::GridValueList& valueList) const
{
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    message1.getGridValueListByCircle(coordinateType,origoX,origoY,radius,values1);
    message2.getGridValueListByCircle(coordinateType,origoX,origoY,radius,values2);

    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeAndCircle(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short timeInterpolationMethod,T::GridValueList& valueList) const
{
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    message1.getGridValueListByCircle(coordinateType,origoX,origoY,radius,values1);
    message2.getGridValueListByCircle(coordinateType,origoX,origoY,radius,values2);

    timeInterpolation(values1,values2,message1.getForecastTime(),message2.getForecastTime(),newTime,timeInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeLevelAndCircle(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,std::string newTime,int newLevel,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const
{
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    getGridValueListByTimeAndCircle(message1,message3,newTime,coordinateType,origoX,origoY,radius,timeInterpolationMethod,values1);
    getGridValueListByTimeAndCircle(message2,message4,newTime,coordinateType,origoX,origoY,radius,timeInterpolationMethod,values2);

    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




void MessageProcessing::getGridValueListByTimeAndPointList(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short timeInterpolationMethod,T::GridValueList& valueList) const
{
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    message1.getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,values1);
    message2.getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,values2);

    timeInterpolation(values1,values2,message1.getForecastTime(),message2.getForecastTime(),newTime,timeInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueListByLevelAndPolygon(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short levelInterpolationMethod,T::GridValueList& valueList) const
{
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    message1.getGridValueListByPolygon(coordinateType,polygonPoints,values1);
    message2.getGridValueListByPolygon(coordinateType,polygonPoints,values2);

    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeAndPolygon(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short timeInterpolationMethod,T::GridValueList& valueList) const
{
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    message1.getGridValueListByPolygon(coordinateType,polygonPoints,values1);
    message2.getGridValueListByPolygon(coordinateType,polygonPoints,values2);

    timeInterpolation(values1,values2,message1.getForecastTime(),message2.getForecastTime(),newTime,timeInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeLevelAndPolygon(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,std::string newTime,int newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const
{
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    getGridValueListByTimeAndPolygon(message1,message3,newTime,coordinateType,polygonPoints,timeInterpolationMethod,values1);
    getGridValueListByTimeAndPolygon(message2,message4,newTime,coordinateType,polygonPoints,timeInterpolationMethod,values2);

    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueListByLevelAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short levelInterpolationMethod,T::GridValueList& valueList) const
{
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    message1.getGridValueListByPolygonPath(coordinateType,polygonPath,values1);
    message2.getGridValueListByPolygonPath(coordinateType,polygonPath,values2);

    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short timeInterpolationMethod,T::GridValueList& valueList) const
{
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    message1.getGridValueListByPolygonPath(coordinateType,polygonPath,values1);
    message2.getGridValueListByPolygonPath(coordinateType,polygonPath,values2);

    timeInterpolation(values1,values2,message1.getForecastTime(),message2.getForecastTime(),newTime,timeInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeLevelAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,std::string newTime,int newLevel,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const
{
  try
  {
    T::GridValueList values1;
    T::GridValueList values2;

    getGridValueListByTimeAndPolygonPath(message1,message3,newTime,coordinateType,polygonPath,timeInterpolationMethod,values1);
    getGridValueListByTimeAndPolygonPath(message2,message4,newTime,coordinateType,polygonPath,timeInterpolationMethod,values2);

    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,valueList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueListByTimeLevelAndPointList(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,std::string newTime,int newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const
{
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

    message1.getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,prevTimePrevLevel);
    message2.getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,prevTimeNextLevel);
    message3.getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,nextTimePrevLevel);
    message4.getGridValueListByPointList(coordinateType,pointList,areaInterpolationMethod,nextTimeNextLevel);

    //prevTimePrevLevel.print(std::cout,0,0);
    //prevTimeNextLevel.print(std::cout,0,0);
    //nextTimePrevLevel.print(std::cout,0,0);
    //nextTimeNextLevel.print(std::cout,0,0);

    if (prevTimeLevel1 == nextTimeLevel1  &&  prevTimeLevel2 == nextTimeLevel2)
    {
      timeInterpolation(prevTimePrevLevel,nextTimePrevLevel,message1.getForecastTime(),message3.getForecastTime(),newTime,timeInterpolationMethod,prevValues);
      timeInterpolation(prevTimeNextLevel,nextTimeNextLevel,message2.getForecastTime(),message4.getForecastTime(),newTime,timeInterpolationMethod,nextValues);

      tuneLevels(prevTimeLevel1,prevTimeLevel2,newLevel);

      //prevValues.print(std::cout,0,0);
      //nextValues.print(std::cout,0,0);
      levelInterpolation(prevValues,nextValues,prevTimeLevel1,prevTimeLevel2,newLevel,levelInterpolationMethod,valueList);
      //valueList.print(std::cout,0,0);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueVectorByLevel(const GRID::Message& message1,const GRID::Message& message2,int newLevel,short levelInterpolationMethod,T::ParamValue_vec& values) const
{
  try
  {
    int level1 = message1.getGridParameterLevel();
    int level2 = message2.getGridParameterLevel();

    // If the levels are using different units (for example hPa and Pa), then we
    // try to tune levels so that : level1 < newLevel < level2

    tuneLevels(level1,level2,newLevel);

    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    message1.getGridValueVectorWithCaching(values1);
    message2.getGridValueVectorWithCaching(values2);

    levelInterpolation(values1,values2,level1,level2,newLevel,levelInterpolationMethod,values);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTime(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,short timeInterpolationMethod,T::ParamValue_vec& values) const
{
  try
  {
    time_t tt = utcTimeToTimeT(newTime);
    time_t t1 = utcTimeToTimeT(message1.getForecastTime());
    time_t t2 = utcTimeToTimeT(message2.getForecastTime());

    if (timeInterpolationMethod == T::TimeInterpolationMethod::Undefined  || timeInterpolationMethod == T::TimeInterpolationMethod::None ||
        (timeInterpolationMethod == T::TimeInterpolationMethod::Nearest  &&  (tt-t1) <= (t2-tt)) ||
        (timeInterpolationMethod == T::TimeInterpolationMethod::Linear  &&  tt == t1))
    {
      message1.getGridValueVectorWithCaching(values);
      return;
    }

    if ((timeInterpolationMethod == T::TimeInterpolationMethod::Nearest  &&  (tt-t1) > (t2-tt)) ||
        (timeInterpolationMethod == T::TimeInterpolationMethod::Linear  &&  tt == t2))
    {
      message2.getGridValueVectorWithCaching(values);
      return;
    }

    T::ParamValue_vec values1;
    T::ParamValue_vec values2;
    message1.getGridValueVectorWithCaching(values1);
    message2.getGridValueVectorWithCaching(values2);

    timeInterpolation(values1,values2,message1.getForecastTime(),message2.getForecastTime(),newTime,timeInterpolationMethod,values);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueVectorByLevelAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,T::ParamValue_vec& values) const
{
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

    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.levelInterpolationMethod",std::to_string(levelInterpolationMethod));
    attributeList.setAttribute("grid.coordinateType",std::to_string(coordinateType));

    if (coordinates.size() == 0)
      return;

    T::ParamValue_vec gridValues1;
    message1.getGridValueVectorByCoordinateList(coordinateType,coordinates,areaInterpolationMethod,gridValues1);

    T::ParamValue_vec gridValues2;
    message2.getGridValueVectorByCoordinateList(coordinateType,coordinates,areaInterpolationMethod,gridValues2);

    levelInterpolation(gridValues1,gridValues2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,values);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTimeAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,T::ParamValue_vec& values) const
{
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

    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.timeInterpolationMethod",std::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.coordinateType",std::to_string(coordinateType));

    if (coordinates.size() == 0)
      return;

    T::ParamValue_vec gridValues1;
    message1.getGridValueVectorByCoordinateList(coordinateType,coordinates,areaInterpolationMethod,gridValues1);

    T::ParamValue_vec gridValues2;
    message2.getGridValueVectorByCoordinateList(coordinateType,coordinates,areaInterpolationMethod,gridValues2);

    timeInterpolation(gridValues1,gridValues2,message1.getForecastTime(),message2.getForecastTime(),newTime,timeInterpolationMethod,values);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueVectorByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::AttributeList& attributeList,T::ParamValue_vec& values) const
{
  try
  {
    short levelInterpolationMethod = T::LevelInterpolationMethod::Linear;
    const char *levelInterpolationMethodStr = attributeList.getAttributeValue("grid.levelInterpolationMethod");
    if (levelInterpolationMethodStr != nullptr)
      levelInterpolationMethod = toInt16(levelInterpolationMethodStr);


    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    message1.getGridValueVectorByGeometry(attributeList,values1);
    message2.getGridValueVectorByGeometry(attributeList,values2);

    levelInterpolation(values1,values2,message1.getGridParameterLevel(),message2.getGridParameterLevel(),newLevel,levelInterpolationMethod,values);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::AttributeList& attributeList,T::ParamValue_vec& values) const
{
  try
  {
    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    message1.getGridValueVectorByGeometry(attributeList,values1);
    message2.getGridValueVectorByGeometry(attributeList,values2);

    timeInterpolation(values1,values2,message1.getForecastTime(),message2.getForecastTime(),newTime,timeInterpolationMethod,values);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,std::string newTime,int newLevel,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,T::ParamValue_vec& values) const
{
  try
  {
    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    getGridValueVectorByLevel(message1,message2,newLevel,levelInterpolationMethod,values1);
    getGridValueVectorByLevel(message3,message4,newLevel,levelInterpolationMethod,values2);

    timeInterpolation(values1,values2,message1.getForecastTime(),message3.getForecastTime(),newTime,timeInterpolationMethod,values);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,std::string newTime,int newLevel,T::AttributeList& attributeList,T::ParamValue_vec& values) const
{
  try
  {
    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    getGridValueVectorByLevelAndGeometry(message1,message2,newLevel,attributeList,values1);
    getGridValueVectorByLevelAndGeometry(message3,message4,newLevel,attributeList,values2);

    timeInterpolation(values1,values2,message1.getForecastTime(),message3.getForecastTime(),newTime,timeInterpolationMethod,values);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridValueVectorByTimeLevelAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,std::string newTime,int newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,T::ParamValue_vec& values) const
{
  try
  {
    short timeInterpolationMethod = T::TimeInterpolationMethod::Linear;
    const char *timeInterpolationMethodStr = attributeList.getAttributeValue("grid.timeInterpolationMethod");
    if (timeInterpolationMethodStr != nullptr)
      timeInterpolationMethod = toInt16(timeInterpolationMethodStr);

    T::ParamValue_vec values1;
    T::ParamValue_vec values2;

    getGridValueVectorByLevelAndCoordinateList(message1,message2,newLevel,coordinateType,coordinates,attributeList,values1);
    getGridValueVectorByLevelAndCoordinateList(message3,message4,newLevel,coordinateType,coordinates,attributeList,values2);

    timeInterpolation(values1,values2,message1.getForecastTime(),message3.getForecastTime(),newTime,timeInterpolationMethod,values);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





}  // namespace GRID
}  // namespace SmartMet

