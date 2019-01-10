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





void MessageProcessing::getGridIsobandsByTime(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::WkbData_vec& contours) const
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
    attributeList.setAttribute("grid.reverseYDirection",std::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.reverseXDirection",std::to_string((int)message1.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsobandsByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::WkbData_vec& contours) const
{
  try
  {
    const char *urnStr = attributeList.getAttributeValue("grid.urn");
    const char *bboxStr = attributeList.getAttributeValue("grid.bbox");
    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    const char *geometryStringStr = attributeList.getAttributeValue("grid.geometryString");
    const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
    const char *gridHeightStr = attributeList.getAttributeValue("grid.height");

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

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

    if ((geometryIdStr == nullptr  &&  geometryStringStr == nullptr  &&  urnStr == nullptr)  ||  (geometryIdStr != nullptr && message1.getGridGeometryId() == toInt32(geometryIdStr)))
    {
      T::Dimensions d = message1.getGridDimensions();
      getGridIsobandsByTime(message1,message2,newTime,contourLowValues,contourHighValues,attributeList,contours);
      return;
    }

    T::Coordinate_vec latLonCoordinates;
    T::Coordinate_vec coordinates;

    GRIB2::GridDef_ptr def = nullptr;
    if (geometryIdStr != nullptr)
    {
      def = Identification::gridDef.getGrib2DefinitionByGeometryId(toInt32(geometryIdStr));
      if (!def)
        return;

      latLonCoordinates = def->getGridLatLonCoordinates();
    }

    std::shared_ptr<GRIB2::GridDefinition> defPtr;
    if (geometryStringStr != nullptr)
    {
      def =  Identification::gridDef.createGrib2GridDefinition(geometryStringStr);
      if (!def)
        return;

      defPtr.reset(def);
      latLonCoordinates = def->getGridLatLonCoordinates();
    }

    uint width = 0;
    uint height = 0;

    if (def != nullptr)
    {
      T::Dimensions d = def->getGridDimensions();
      width = d.nx();
      height = d.ny();
      attributeList.setAttribute("grid.reverseYDirection",std::to_string((int)def->reverseYDirection()));
      attributeList.setAttribute("grid.reverseXDirection",std::to_string((int)def->reverseXDirection()));
    }

    if (urnStr != nullptr  &&  bboxStr != nullptr  &&  gridWidthStr != nullptr  &&  gridHeightStr != nullptr)
    {
      std::vector<double> cc;
      splitString(bboxStr,',',cc);

      if (cc.size() == 4)
      {
        OGRSpatialReference sr_latlon;
        sr_latlon.importFromEPSG(4326);

        OGRSpatialReference sr;
        std::string urn = urnStr;
        if (strncasecmp(urnStr,"urn:ogc:def:crs:",16) != 0)
          urn = std::string("urn:ogc:def:crs:") + urnStr;

        if (sr.importFromURN(urn.c_str()) != OGRERR_NONE)
          throw SmartMet::Spine::Exception(BCP, "Invalid crs!" + std::string(urnStr) + "'!");

        OGRCoordinateTransformation *tranformation = OGRCreateCoordinateTransformation(&sr,&sr_latlon);
        if (tranformation == nullptr)
          throw SmartMet::Spine::Exception(BCP,"Cannot create coordinate transformation!");

        width = toUInt32(gridWidthStr);
        height = toUInt32(gridHeightStr);

        double diffx = cc[2] - cc[0];
        double diffy = cc[3] - cc[1];

        double dx = diffx / C_DOUBLE(width);
        double dy = diffy / C_DOUBLE(height);

        uint sz = width*height;

        coordinates.reserve(sz);
        latLonCoordinates.reserve(sz);

        double yy = cc[1];
        for (uint y=0; y<height; y++)
        {
          double xx = cc[0];
          for (uint x=0; x<width; x++)
          {
            double lon = xx;
            double lat = yy;

            tranformation->Transform(1,&lon,&lat);
            latLonCoordinates.push_back(T::Coordinate(lon,lat));
            coordinates.push_back(T::Coordinate(xx,yy));

            xx = xx + dx;
          }
          yy = yy + dy;
        }
      }
    }

    if (latLonCoordinates.size() == 0)
      return;

    T::ParamValue_vec gridValues1;
    message1.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,latLonCoordinates,areaInterpolationMethod,gridValues1);

    T::ParamValue_vec gridValues2;
    message2.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,latLonCoordinates,areaInterpolationMethod,gridValues2);

    T::ParamValue_vec gridValues;
    timeInterpolation(gridValues1,gridValues2,message1.getForecastTime(),message2.getForecastTime(),newTime,timeInterpolationMethod,gridValues);

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
        coordinates = def->getGridCoordinates();
        coordinatePtr = &coordinates;
        break;
    }

    getIsobands(gridValues,coordinatePtr,width,height,contourLowValues,contourHighValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.timeInterpolationMethod",std::to_string(timeInterpolationMethod));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));
    attributeList.setAttribute("grid.width",std::to_string(width));
    attributeList.setAttribute("grid.height",std::to_string(height));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTime(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::WkbData_vec& contours) const
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

    attributeList.setAttribute("grid.timeInterpolationMethod",std::to_string(timeInterpolationMethod));
    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.width",std::to_string(d.nx()));
    attributeList.setAttribute("grid.height",std::to_string(d.ny()));
    attributeList.setAttribute("grid.reverseYDirection",std::to_string((int)message1.reverseYDirection()));
    attributeList.setAttribute("grid.reverseXDirection",std::to_string((int)message2.reverseXDirection()));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MessageProcessing::getGridIsolinesByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::WkbData_vec& contours) const
{
  try
  {
    const char *urnStr = attributeList.getAttributeValue("grid.urn");
    const char *bboxStr = attributeList.getAttributeValue("grid.bbox");
    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    const char *geometryStringStr = attributeList.getAttributeValue("grid.geometryString");
    const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
    const char *gridHeightStr = attributeList.getAttributeValue("grid.height");

    T::CoordinateType coordinateType = T::CoordinateTypeValue::LATLON_COORDINATES;
    const char *coordinateTypeStr = attributeList.getAttributeValue("contour.coordinateType");
    if (coordinateTypeStr != nullptr)
      coordinateType = toUInt8(coordinateTypeStr);

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

    if ((geometryIdStr == nullptr  &&  geometryStringStr == nullptr  &&  urnStr == nullptr)  ||  (geometryIdStr != nullptr && message1.getGridGeometryId() == toInt32(geometryIdStr)))
    {
      T::Dimensions d = message1.getGridDimensions();
      getGridIsolinesByTime(message1,message2,newTime,contourValues,attributeList,contours);
      return;
    }

    T::Coordinate_vec latLonCoordinates;
    T::Coordinate_vec coordinates;

    GRIB2::GridDef_ptr def = nullptr;
    if (geometryIdStr != nullptr)
    {
      def = Identification::gridDef.getGrib2DefinitionByGeometryId(toInt32(geometryIdStr));
      if (!def)
        return;

      latLonCoordinates = def->getGridLatLonCoordinates();
    }

    std::shared_ptr<GRIB2::GridDefinition> defPtr;
    if (geometryStringStr != nullptr)
    {
      def =  Identification::gridDef.createGrib2GridDefinition(geometryStringStr);
      if (!def)
        return;

      defPtr.reset(def);
      latLonCoordinates = def->getGridLatLonCoordinates();
    }

    uint width = 0;
    uint height = 0;

    if (def != nullptr)
    {
      T::Dimensions d = def->getGridDimensions();
      width = d.nx();
      height = d.ny();
      attributeList.setAttribute("grid.reverseYDirection",std::to_string((int)def->reverseYDirection()));
      attributeList.setAttribute("grid.reverseXDirection",std::to_string((int)def->reverseXDirection()));
    }

    if (urnStr != nullptr  &&  bboxStr != nullptr  &&  gridWidthStr != nullptr  &&  gridHeightStr != nullptr)
    {
      std::vector<double> cc;
      splitString(bboxStr,',',cc);

      if (cc.size() == 4)
      {
        OGRSpatialReference sr_latlon;
        sr_latlon.importFromEPSG(4326);

        OGRSpatialReference sr;
        std::string urn = urnStr;
        if (strncasecmp(urnStr,"urn:ogc:def:crs:",16) != 0)
          urn = std::string("urn:ogc:def:crs:") + urnStr;

        if (sr.importFromURN(urn.c_str()) != OGRERR_NONE)
          throw SmartMet::Spine::Exception(BCP, "Invalid crs!" + std::string(urnStr) + "'!");

        OGRCoordinateTransformation *tranformation = OGRCreateCoordinateTransformation(&sr,&sr_latlon);
        if (tranformation == nullptr)
          throw SmartMet::Spine::Exception(BCP,"Cannot create coordinate transformation!");

        width = toUInt32(gridWidthStr);
        height = toUInt32(gridHeightStr);

        double diffx = cc[2] - cc[0];
        double diffy = cc[3] - cc[1];

        double dx = diffx / C_DOUBLE(width);
        double dy = diffy / C_DOUBLE(height);

        uint sz = width*height;

        coordinates.reserve(sz);
        latLonCoordinates.reserve(sz);

        double yy = cc[1];
        for (uint y=0; y<height; y++)
        {
          double xx = cc[0];
          for (uint x=0; x<width; x++)
          {
            double lon = xx;
            double lat = yy;

            tranformation->Transform(1,&lon,&lat);
            latLonCoordinates.push_back(T::Coordinate(lon,lat));
            coordinates.push_back(T::Coordinate(xx,yy));

            xx = xx + dx;
          }
          yy = yy + dy;
        }
      }
    }

    if (latLonCoordinates.size() == 0)
      return;

    T::ParamValue_vec gridValues1;
    message1.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,latLonCoordinates,areaInterpolationMethod,gridValues1);

    T::ParamValue_vec gridValues2;
    message2.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,latLonCoordinates,areaInterpolationMethod,gridValues2);

    T::ParamValue_vec gridValues;
    timeInterpolation(gridValues1,gridValues2,message1.getForecastTime(),message2.getForecastTime(),newTime,timeInterpolationMethod,gridValues);

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
        coordinates = def->getGridCoordinates();
        coordinatePtr = &coordinates;
        break;
    }

    getIsolines(gridValues,coordinatePtr,width,height,contourValues,areaInterpolationMethod,smoothSize,smoothDegree,contours);

    attributeList.setAttribute("grid.areaInterpolationMethod",std::to_string(areaInterpolationMethod));
    attributeList.setAttribute("grid.timeInterpolationMethod",std::to_string(timeInterpolationMethod));
    attributeList.setAttribute("contour.coordinateType",std::to_string(coordinateType));
    attributeList.setAttribute("grid.width",std::to_string(width));
    attributeList.setAttribute("grid.height",std::to_string(height));
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





void MessageProcessing::getGridValueVectorByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::AttributeList& attributeList,T::ParamValue_vec& values) const
{
  try
  {
    const char *urnStr = attributeList.getAttributeValue("grid.urn");
    const char *bboxStr = attributeList.getAttributeValue("grid.bbox");
    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    const char *geometryStringStr = attributeList.getAttributeValue("grid.geometryString");
    const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
    const char *gridHeightStr = attributeList.getAttributeValue("grid.height");

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

    if ((geometryIdStr == nullptr  &&  geometryStringStr == nullptr  &&  urnStr == nullptr)  ||  (geometryIdStr != nullptr && message1.getGridGeometryId() == toInt32(geometryIdStr)))
    {
      T::Dimensions d = message1.getGridDimensions();
      attributeList.setAttribute("grid.width",std::to_string(d.nx()));
      attributeList.setAttribute("grid.height",std::to_string(d.ny()));
      attributeList.setAttribute("grid.reverseYDirection",std::to_string((int)message1.reverseYDirection()));
      attributeList.setAttribute("grid.reverseXDirection",std::to_string((int)message1.reverseXDirection()));

      getGridValueVectorByTime(message1,message2,newTime,timeInterpolationMethod,values);
      return;
    }

    T::Coordinate_vec latLonCoordinates;

    GRIB2::GridDef_ptr def = nullptr;
    if (geometryIdStr != nullptr)
    {
      def = Identification::gridDef.getGrib2DefinitionByGeometryId(toInt32(geometryIdStr));
      if (!def)
        return;

      latLonCoordinates = def->getGridLatLonCoordinates();
    }

    std::shared_ptr<GRIB2::GridDefinition> defPtr;
    if (geometryStringStr != nullptr)
    {
      def =  Identification::gridDef.createGrib2GridDefinition(geometryStringStr);
      if (!def)
        return;

      defPtr.reset(def);
      latLonCoordinates = def->getGridLatLonCoordinates();
    }

    if (def != nullptr)
    {
      T::Dimensions d = def->getGridDimensions();
      attributeList.setAttribute("grid.width",std::to_string(d.nx()));
      attributeList.setAttribute("grid.height",std::to_string(d.ny()));
      attributeList.setAttribute("grid.reverseYDirection",std::to_string((int)def->reverseYDirection()));
      attributeList.setAttribute("grid.reverseXDirection",std::to_string((int)def->reverseXDirection()));
    }

    if (urnStr != nullptr  &&  bboxStr != nullptr  &&  gridWidthStr != nullptr  &&  gridHeightStr != nullptr)
    {
      std::vector<double> cc;
      splitString(bboxStr,',',cc);

      if (cc.size() == 4)
      {
        OGRSpatialReference sr_latlon;
        sr_latlon.importFromEPSG(4326);

        OGRSpatialReference sr;
        std::string urn = urnStr;
        if (strncasecmp(urnStr,"urn:ogc:def:crs:",16) != 0)
          urn = std::string("urn:ogc:def:crs:") + urnStr;

        if (sr.importFromURN(urn.c_str()) != OGRERR_NONE)
          throw SmartMet::Spine::Exception(BCP, "Invalid crs!" + std::string(urnStr) + "'!");

        OGRCoordinateTransformation *tranformation = OGRCreateCoordinateTransformation(&sr,&sr_latlon);
        if (tranformation == nullptr)
          throw SmartMet::Spine::Exception(BCP,"Cannot create coordinate transformation!");

        uint width = toUInt32(gridWidthStr);
        uint height = toUInt32(gridHeightStr);

        double diffx = cc[2] - cc[0];
        double diffy = cc[3] - cc[1];

        double dx = diffx / C_DOUBLE(width);
        double dy = diffy / C_DOUBLE(height);

        uint sz = width*height;

        latLonCoordinates.reserve(sz);

        double yy = cc[1];
        for (uint y=0; y<height; y++)
        {
          double xx = cc[0];
          for (uint x=0; x<width; x++)
          {
            double lon = xx;
            double lat = yy;

            tranformation->Transform(1,&lon,&lat);
            latLonCoordinates.push_back(T::Coordinate(lon,lat));

            xx = xx + dx;
          }
          yy = yy + dy;
        }
      }
    }

    if (latLonCoordinates.size() == 0)
      return;

    T::ParamValue_vec gridValues1;
    message1.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,latLonCoordinates,areaInterpolationMethod,gridValues1);

    T::ParamValue_vec gridValues2;
    message2.getGridValueVectorByCoordinateList(T::CoordinateTypeValue::LATLON_COORDINATES,latLonCoordinates,areaInterpolationMethod,gridValues2);

    timeInterpolation(gridValues1,gridValues2,message1.getForecastTime(),message2.getForecastTime(),newTime,timeInterpolationMethod,values);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}



}  // namespace GRID
}  // namespace SmartMet

