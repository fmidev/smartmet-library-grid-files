#pragma once

#include "Message.h"
#include "Typedefs.h"
#include "GridPointValue.h"
#include "GridPointValueList.h"
#include "GridValueList.h"
#include "../common/AttributeList.h"
#include "../common/Coordinate.h"
#include "../common/Dimensions.h"
#include "../common/GraphFunctions.h"
#include "../common/ThreadLock.h"

#include <vector>
#include <string>
#include <memory>


namespace SmartMet
{
namespace GRID
{


class MessageProcessing
{
  public:

                 MessageProcessing();
    virtual      ~MessageProcessing();

    virtual void getGridIsobandsByLevel(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    virtual void getGridIsobandsByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    virtual void getGridIsobandsByLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours);
    virtual void getGridIsobandsByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    virtual void getGridIsobandsByTimeAndGrid(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours);
    virtual void getGridIsobandsByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    virtual void getGridIsobandsByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,int newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    virtual void getGridIsobandsByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,int newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    virtual void getGridIsobandsByTimeLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,int newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours) const;

    virtual void getGridIsolinesByLevel(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    virtual void getGridIsolinesByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    virtual void getGridIsolinesByLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours);
    virtual void getGridIsolinesByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    virtual void getGridIsolinesByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    virtual void getGridIsolinesByTimeAndGrid(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours);
    virtual void getGridIsolinesByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,int newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    virtual void getGridIsolinesByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,int newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    virtual void getGridIsolinesByTimeLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,int newLevel,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours) const;

    virtual void getGridValueByLevelAndPoint(const GRID::Message& message1,const GRID::Message& message2,int level1,int level2,int newLevel,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short levelInterpolationMethod,T::ParamValue& value) const;
    virtual void getGridValueByTimeAndPoint(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short timeInterpolationMethod,T::ParamValue& value) const;
    virtual void getGridValueByTimeLevelAndPoint(const GRID::Message& message1,int level1,const GRID::Message& message2,int level2,const GRID::Message& message3,int level3,const GRID::Message& message4,int level4,time_t newTime,int newLevel,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,T::ParamValue& value) const;

    virtual void getGridValueListByLevelAndCircle(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short levelInterpolationMethod,T::GridValueList& valueList) const;
    virtual void getGridValueListByLevelAndPointList(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const;
    virtual void getGridValueListByLevelAndPolygon(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short levelInterpolationMethod,T::GridValueList& valueList) const;
    virtual void getGridValueListByLevelAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short levelInterpolationMethod,T::GridValueList& valueList) const;
    virtual void getGridValueListByTimeAndCircle(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short timeInterpolationMethod,T::GridValueList& valueList) const;
    virtual void getGridValueListByTimeAndPointList(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short timeInterpolationMethod,T::GridValueList& valueList) const;
    virtual void getGridValueListByTimeAndPolygon(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short timeInterpolationMethod,T::GridValueList& valueList) const;
    virtual void getGridValueListByTimeAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short timeInterpolationMethod,T::GridValueList& valueList) const;
    virtual void getGridValueListByTimeLevelAndCircle(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,int newLevel,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const;
    virtual void getGridValueListByTimeLevelAndPointList(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,int newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const;
    virtual void getGridValueListByTimeLevelAndPolygon(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,int newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const;
    virtual void getGridValueListByTimeLevelAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,int newLevel,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const;

    virtual void getGridValueVectorByLevel(const GRID::Message& message1,const GRID::Message& message2,int newLevel,short levelInterpolationMethod,T::ParamValue_vec& values) const;
    virtual void getGridValueVectorByLevelAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,T::ParamValue_vec& values) const;
    virtual void getGridValueVectorByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::AttributeList& attributeList,T::ParamValue_vec& values) const;
    virtual void getGridValueVectorByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,short timeInterpolationMethod,T::ParamValue_vec& values) const;
    virtual void getGridValueVectorByTimeAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,T::ParamValue_vec& values) const;
    virtual void getGridValueVectorByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::AttributeList& attributeList,T::ParamValue_vec& values) const;
    virtual void getGridValueVectorByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,int newLevel,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,T::ParamValue_vec& values) const;
    virtual void getGridValueVectorByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,int newLevel,T::AttributeList& attributeList,T::ParamValue_vec& values) const;
    virtual void getGridValueVectorByTimeLevelAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,int newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,T::ParamValue_vec& values) const;
};



}  // namespace GRID
}  // namespace SmartMet

