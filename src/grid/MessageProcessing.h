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

    virtual void getGridIsobandsByTime(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::WkbData_vec& contours) const;
    virtual void getGridIsobandsByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::WkbData_vec& contours) const;
    virtual void getGridIsolinesByTime(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::WkbData_vec& contours) const;
    virtual void getGridIsolinesByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::WkbData_vec& contours) const;

    virtual void getGridValueByLevelAndPoint(const GRID::Message& message1,const GRID::Message& message2,int level1,int level2,int newLevel,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short levelInterpolationMethod,T::ParamValue& value) const;
    virtual void getGridValueByTimeAndPoint(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short timeInterpolationMethod,T::ParamValue& value) const;
    virtual void getGridValueByTimeLevelAndPoint(const GRID::Message& message1,int level1,const GRID::Message& message2,int level2,const GRID::Message& message3,int level3,const GRID::Message& message4,int level4,std::string newTime,int newLevel,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,T::ParamValue& value) const;

    virtual void getGridValueListByLevelAndPointList(const GRID::Message& message1,const GRID::Message& message2,int newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const;
    virtual void getGridValueListByTimeAndCircle(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short timeInterpolationMethod,T::GridValueList& valueList) const;
    virtual void getGridValueListByTimeAndPointList(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short timeInterpolationMethod,T::GridValueList& valueList) const;
    virtual void getGridValueListByTimeAndPolygon(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short timeInterpolationMethod,T::GridValueList& valueList) const;
    virtual void getGridValueListByTimeAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short timeInterpolationMethod,T::GridValueList& valueList) const;
    virtual void getGridValueListByTimeLevelAndPointList(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,std::string newTime,int newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const;

    virtual void getGridValueVectorByTime(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,short timeInterpolationMethod,T::ParamValue_vec& values) const;
    virtual void getGridValueVectorByTimeAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,T::ParamValue_vec& values) const;
    virtual void getGridValueVectorByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,std::string newTime,T::AttributeList& attributeList,T::ParamValue_vec& values) const;
};



}  // namespace GRID
}  // namespace SmartMet

