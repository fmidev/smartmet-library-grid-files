#pragma once

#include "GridPointValue.h"


namespace SmartMet
{
namespace T
{


class GridPointValueList
{
  public:
                          GridPointValueList();
                          GridPointValueList(GridPointValueList& gridPointValueList);
                          GridPointValueList(const GridPointValueList& gridPointValueList);
     virtual              ~GridPointValueList();

     GridPointValueList&  operator=(GridPointValueList& gridPointValueList);
     GridPointValueList&  operator=(const GridPointValueList& gridPointValueList);

     void                 addGridPointValue(GridPointValue *gridPointValue);
     void                 clear();
     bool                 deleteGridPointValueByIndex(uint index);
     int                  getClosestIndex(GridPointValue::ComparisonMethod comparisonMethod,GridPointValue& gridPointValue);
     void                 getGridPointValueArea(double& minX,double& minY,double& maxX,double& maxY);
     GridPointValue*      getGridPointValueByIndex(uint index);
     GridPointValue*      getGridPointValueByIndexNoCheck(uint index);
     GridPointValue*      getGridPointValueByPointAndTime(double x,double y,T::ParamLevel level,time_t time);
     GridPointValue*      getGridPointValueByFileMessageAndPoint(uint fileId,uint messageIndex,double x,double y);
     GridPointValue*      getPreviousGridPointValueByPointAndTime(double x,double y,T::ParamLevel level,time_t time);
     GridPointValue*      getNextGridPointValueByPointAndTime(double x,double y,T::ParamLevel level,time_t time);
     void                 getGridPointValueListByPoint(double x,double y,T::ParamLevel level,GridPointValueList& gridPointValueList);
     void                 getGridPointValueListByArea(double minX,double minY,double maxX,double maxY,T::ParamLevel level,GridPointValueList& gridPointValueList);
     void                 getGridPointValueListByTime(time_t time,GridPointValueList& gridPointValueList);
     void                 getGridPointValueListByTimeRange(time_t startTime,time_t endTime,GridPointValueList& gridPointValueList);
     void                 getGridPointValueListByValueRange(T::ParamValue minValue,T::ParamValue maxValue,GridPointValueList& gridPointValueList);
     void                 getGridPointValueListByTimeSteps(double x,double y,T::ParamLevel level,time_t startTime,uint numberOfSteps,uint stepSizeInSeconds,GridPointValueList& gridPointValueList);

     uint                 getLength();
     bool                 getReleaseObjects();
     void                 increaseSize(uint newSize);
     void                 setComparisonMethod(GridPointValue::ComparisonMethod comparisonMethod);
     void                 setReleaseObjects(bool releaseObjects);
     void                 sort(GridPointValue::ComparisonMethod comparisonMethod);

     T::ParamValue        getMaxValue();
     T::ParamValue        getMaxValueByTime(time_t time);
     T::ParamValue        getMinValue();
     T::ParamValue        getMinValueByTime(time_t time);
     T::ParamValue        getAverageValue();
     T::ParamValue        getAverageValueByTime(time_t time);
     uint                 getNumOfValuesInValueRange(T::ParamValue minValue,T::ParamValue maxValue);

     T::ParamValue        getTimeInterpolatedValue(double x,double y,T::ParamLevel level,time_t time);

     void                 print(std::ostream& stream,uint level,uint optionFlags);

  protected:

     GridPointValuePtr    *mArray;
     uint                 mSize;
     uint                 mLength;
     bool                 mReleaseObjects;

     GridPointValue::ComparisonMethod mComparisonMethod;
};



}
}
