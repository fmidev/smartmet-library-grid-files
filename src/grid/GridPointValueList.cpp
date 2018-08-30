#include "GridPointValueList.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"
#include "../common/AutoWriteLock.h"
#include "../common/AutoThreadLock.h"
#include "../common/AutoReadLock.h"


namespace SmartMet
{
namespace T
{


ThreadLock GridPointValueList_sortLock;

GridPointValue::ComparisonMethod gridPointValue_comparisonMethod = GridPointValue::ComparisonMethod::none;



int gridPointValue_compare(const void *_val1,const void *_val2)
{
  if (_val1 != nullptr  &&  _val2 != nullptr)
  {
    GridPointValuePtr *obj1 = const_cast<GridPointValuePtr*>(reinterpret_cast<const GridPointValuePtr *>(_val1));
    GridPointValuePtr *obj2 = const_cast<GridPointValuePtr*>(reinterpret_cast<const GridPointValuePtr *>(_val2));

    return (*obj1)->compare(gridPointValue_comparisonMethod,(*obj2));
  }
  return 0;
}




GridPointValueList::GridPointValueList()
{
  try
  {
    mComparisonMethod = GridPointValue::ComparisonMethod::none;
    mReleaseObjects = true;
    mSize = 100;
    mLength = 0;
    mArray = new GridPointValuePtr[100];

    for (uint t=0; t<100; t++)
    {
      mArray[t] = nullptr;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GridPointValueList::GridPointValueList(GridPointValueList& gridPointValueList)
{
  try
  {
    mReleaseObjects = true;
    mSize = gridPointValueList.mSize;
    mLength = gridPointValueList.mLength;
    mArray = new GridPointValuePtr[mSize];
    for (uint t=0; t<mSize; t++)
    {
      GridPointValue *info = gridPointValueList.mArray[t];
      if (info != nullptr)
        mArray[t] = info->duplicate();
      else
        mArray[t] = nullptr;
    }
    mComparisonMethod = gridPointValueList.mComparisonMethod;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GridPointValueList::GridPointValueList(const GridPointValueList& gridPointValueList)
{
  try
  {
    mReleaseObjects = true;
    mSize = gridPointValueList.mSize;
    mLength = gridPointValueList.mLength;
    mArray = new GridPointValuePtr[mSize];
    for (uint t=0; t<mSize; t++)
    {
      GridPointValue *info = gridPointValueList.mArray[t];
      if (info != nullptr)
        mArray[t] = info->duplicate();
      else
        mArray[t] = nullptr;
    }
    mComparisonMethod = gridPointValueList.mComparisonMethod;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GridPointValueList::~GridPointValueList()
{
  try
  {
    clear();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





void GridPointValueList::operator=(GridPointValueList& gridPointValueList)
{
  try
  {
    if (&gridPointValueList == this)
      return;

    clear();

    mSize = gridPointValueList.mSize;
    mLength = gridPointValueList.mLength;
    mArray = new GridPointValuePtr[mSize];
    for (uint t=0; t<mSize; t++)
    {
      GridPointValue *info = gridPointValueList.mArray[t];
      if (info != nullptr  &&  mReleaseObjects)
        mArray[t] = info->duplicate();
      else
        mArray[t] = info;
    }
    mComparisonMethod = gridPointValueList.mComparisonMethod;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridPointValueList::operator=(const GridPointValueList& gridPointValueList)
{
  try
  {
    if (&gridPointValueList == this)
      return;

    clear();

    mSize = gridPointValueList.mSize;
    mLength = gridPointValueList.mLength;
    mArray = new GridPointValuePtr[mSize];
    for (uint t=0; t<mSize; t++)
    {
      GridPointValue *info = gridPointValueList.mArray[t];
      if (info != nullptr  &&  mReleaseObjects)
        mArray[t] = info->duplicate();
      else
        mArray[t] = info;
    }
    mComparisonMethod = gridPointValueList.mComparisonMethod;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridPointValueList::addGridPointValue(GridPointValue *gridPointValue)
{
  try
  {
    if (mArray == nullptr  ||  mLength == mSize)
    {
      increaseSize(mSize + mSize/5 + 10);
    }

    if (mComparisonMethod == GridPointValue::ComparisonMethod::none)
    {
      mArray[mLength] = gridPointValue;
      mLength++;
      return;
    }

    int idx = getClosestIndex(mComparisonMethod,*gridPointValue);

    while (idx < (int)mLength  &&  mArray[idx] != nullptr  &&   mArray[idx]->compare(mComparisonMethod,gridPointValue) < 0)
    {
      idx++;
    }

    if (idx == (int)mLength)
    {
      mArray[mLength] = gridPointValue;
      mLength++;
      return;
    }

    if (idx < (int)mLength)
      memmove(&mArray[idx+1],&mArray[idx],sizeof(void*)*(mLength-idx));

    mArray[idx] = gridPointValue;
    mLength++;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridPointValueList::clear()
{
  try
  {
    if (mArray != nullptr)
    {
      for (uint t=0; t<mLength; t++)
      {
        if (mArray[t] != nullptr  &&  mReleaseObjects)
        {
          delete(mArray[t]);
          mArray[t] = nullptr;
        }
      }
      delete mArray;
    }

    mSize = 100;
    mLength = 0;
    mArray = new GridPointValuePtr[100];

    for (uint t=0; t<100; t++)
    {
      mArray[t] = nullptr;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




void GridPointValueList::increaseSize(uint newSize)
{
  try
  {
    if (mArray == nullptr)
    {
      mSize = newSize;
      mLength = 0;
      mArray = new GridPointValuePtr[mSize];

      for (uint t=0; t<mSize; t++)
      {
        mArray[t] = nullptr;
      }
      return;
    }

    GridPointValuePtr *newArray = new GridPointValuePtr[newSize];
    for (uint t=0; t<newSize; t++)
    {
      if (t < mSize)
      {
        newArray[t] = mArray[t];
      }
      else
      {
        newArray[t] = nullptr;
      }
    }

    delete mArray;
    mArray = newArray;
    mSize = newSize;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





int GridPointValueList::getClosestIndex(GridPointValue::ComparisonMethod comparisonMethod,GridPointValue& gridPointValue)
{
  try
  {
    if (mArray == nullptr  ||  mLength == 0)
          return 0;

    if (comparisonMethod != mComparisonMethod)
    {
      for (uint t=0; t<mLength; t++)
      {
        if (mArray[t] != nullptr)
        {
          int res = mArray[t]->compare(comparisonMethod,&gridPointValue);
          if (res == 0)
          {
            return t;
          }
        }
      }
      return 0;
    }

    int low = 0;
    int high = (int)mLength - 1;
    int mid = 0;

    while (low <= high)
    {
      mid = (low + high) / 2;
      int res = mArray[mid]->compare(comparisonMethod,&gridPointValue);

      if (res == 0)
      {
        while (mid > 0  &&  mArray[mid-1]->compare(comparisonMethod,&gridPointValue) == 0)
          mid--;

        return mid;
      }

      if (res < 0)
        low = mid + 1;
      else
        high = mid - 1;
    }

    if (mid >= 0  &&  mid < (int)mLength  &&  mArray[mid] != nullptr)
    {
      if (mArray[mid]->compare(comparisonMethod,&gridPointValue) < 0)
      {
        while (mid < (int)mSize  &&  mArray[mid] != nullptr  &&   mArray[mid]->compare(comparisonMethod,&gridPointValue) < 0)
          mid++;

        return mid-1;
      }
      else
      {
        while (mid > 0  &&  mArray[mid] != nullptr  &&   mArray[mid]->compare(comparisonMethod,&gridPointValue) > 0)
          mid--;

        return mid;
      }
    }
    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GridPointValue* GridPointValueList::getGridPointValueByIndex(uint index)
{
  try
  {
    if (index > mLength)
      return nullptr;

    return mArray[index];
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GridPointValue* GridPointValueList::getGridPointValueByIndexNoCheck(uint index)
{
  try
  {
    return mArray[index];
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GridPointValue* GridPointValueList::getGridPointValueByFileMessageAndPoint(uint fileId,uint messageIndex,double x,double y)
{
  try
  {
    for (uint t=0; t<mLength; t++)
    {
      if (mArray[t]->mX == x  &&  mArray[t]->mY == y  &&  mArray[t]->mFileId == fileId  &&  mArray[t]->mMessageIndex == messageIndex)
      {
        return mArray[t];
      }
    }
    return nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




GridPointValue* GridPointValueList::getGridPointValueByPointAndTime(double x,double y,T::ParamLevel level,T::TimeString time)
{
  try
  {
    for (uint t=0; t<mLength; t++)
    {
      if (mArray[t]->mX == x  &&  mArray[t]->mY == y  &&  mArray[t]->mLevel == level  &&  mArray[t]->mTime == time)
      {
        return mArray[t];
      }
    }
    return nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GridPointValue* GridPointValueList::getPreviousGridPointValueByPointAndTime(double x,double y,T::ParamLevel level,T::TimeString time)
{
  try
  {
    GridPointValue *point = nullptr;

    for (uint t=0; t<mLength; t++)
    {
      if (mArray[t]->mX == x  &&  mArray[t]->mY == y  &&  mArray[t]->mLevel == level  &&  mArray[t]->mTime < time)
      {
        if (point == nullptr  ||  mArray[t]->mTime > point->mTime)
          point = mArray[t];
      }
    }
    return point;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GridPointValue* GridPointValueList::getNextGridPointValueByPointAndTime(double x,double y,T::ParamLevel level,T::TimeString time)
{
  try
  {
    GridPointValue *point = nullptr;

    for (uint t=0; t<mLength; t++)
    {
      if (mArray[t]->mX == x  &&  mArray[t]->mY == y  &&  mArray[t]->mLevel == level  &&  mArray[t]->mTime > time)
      {
        if (point == nullptr  ||  mArray[t]->mTime < point->mTime)
          point = mArray[t];
      }
    }
    return point;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridPointValueList::getGridPointValueListByPoint(double x,double y,T::ParamLevel level,GridPointValueList& gridPointValueList)
{
  try
  {
    for (uint t=0; t<mLength; t++)
    {
      if (mArray[t]->mX == x  &&  mArray[t]->mY == y  &&  mArray[t]->mLevel == level)
      {
        gridPointValueList.addGridPointValue(mArray[t]->duplicate());
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridPointValueList::getGridPointValueListByArea(double minX,double minY,double maxX,double maxY,T::ParamLevel level,GridPointValueList& gridPointValueList)
{
  try
  {
    for (uint t=0; t<mLength; t++)
    {
      double x = mArray[t]->mX;
      double y = mArray[t]->mY;
      if (x >= minX  &&  x <= maxX  &&  y >= minY  &&  y <= maxY  &&  mArray[t]->mLevel == level)
      {
        gridPointValueList.addGridPointValue(mArray[t]->duplicate());
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridPointValueList::getGridPointValueListByTime(T::TimeString time,GridPointValueList& gridPointValueList)
{
  try
  {
    for (uint t=0; t<mLength; t++)
    {
      if (mArray[t]->mTime == time)
      {
        gridPointValueList.addGridPointValue(mArray[t]->duplicate());
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridPointValueList::getGridPointValueListByTimeRange(T::TimeString startTime,T::TimeString endTime,GridPointValueList& gridPointValueList)
{
  try
  {
    for (uint t=0; t<mLength; t++)
    {
      if (mArray[t]->mTime >= startTime  &&  mArray[t]->mTime <= endTime)
      {
        gridPointValueList.addGridPointValue(mArray[t]->duplicate());
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridPointValueList::getGridPointValueListByValueRange(T::ParamValue minValue,T::ParamValue maxValue,GridPointValueList& gridPointValueList)
{
  try
  {
    for (uint t=0; t<mLength; t++)
    {
      if (mArray[t]->mValue >= minValue  &&  mArray[t]->mValue < maxValue)
      {
        gridPointValueList.addGridPointValue(mArray[t]->duplicate());
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint GridPointValueList::getLength()
{
  try
  {
    return mLength;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool GridPointValueList::deleteGridPointValueByIndex(uint index)
{
  try
  {
    if (index >= mLength)
      return false;

    GridPointValue *info = mArray[index];

    for (uint t=index+1; t<mSize; t++)
    {
      mArray[t-1] = mArray[t];
      mArray[t] = nullptr;
    }

    if (mReleaseObjects)
      delete info;

    mLength--;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool GridPointValueList::getReleaseObjects()
{
  try
  {
    return mReleaseObjects;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




void GridPointValueList::setReleaseObjects(bool releaseObjects)
{
  try
  {
    mReleaseObjects = releaseObjects;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridPointValueList::setComparisonMethod(GridPointValue::ComparisonMethod comparisonMethod)
{
  try
  {
    mComparisonMethod = comparisonMethod;
    if (mLength == 0)
      return;

    gridPointValue_comparisonMethod = comparisonMethod;

    qsort(mArray,mLength,sizeof(GridPointValuePtr),gridPointValue_compare);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridPointValueList::sort(GridPointValue::ComparisonMethod comparisonMethod)
{
  try
  {
    mComparisonMethod = comparisonMethod;

    AutoThreadLock globalLock(&GridPointValueList_sortLock);

    gridPointValue_comparisonMethod = comparisonMethod;

    qsort(mArray,mLength,sizeof(GridPointValuePtr),gridPointValue_compare);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::ParamValue GridPointValueList::getMaxValue()
{
  try
  {
    if (mLength == 0)
      return 0;

    T::ParamValue maxValue = mArray[0]->mValue;

    for (uint t=1; t<mLength; t++)
    {
      if (mArray[t]->mValue > maxValue)
        maxValue = mArray[t]->mValue;
    }
    return maxValue;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::ParamValue GridPointValueList::getMaxValueByTime(T::TimeString time)
{
  try
  {
    if (mLength == 0)
      return 0;

    T::ParamValue maxValue = ParamValueMissing;

    for (uint t=0; t<mLength; t++)
    {
      if (mArray[t]->mTime == time  &&  (mArray[t]->mValue > maxValue || maxValue == ParamValueMissing))
        maxValue = mArray[t]->mValue;
    }

    if (maxValue != ParamValueMissing)
      return maxValue;

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::ParamValue GridPointValueList::getMinValue()
{
  try
  {
    if (mLength == 0)
      return 0;

    T::ParamValue minValue = mArray[0]->mValue;

    for (uint t=1; t<mLength; t++)
    {
      if (mArray[t]->mValue < minValue)
        minValue = mArray[t]->mValue;
    }
    return minValue;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::ParamValue GridPointValueList::getMinValueByTime(T::TimeString time)
{
  try
  {
    if (mLength == 0)
      return 0;

    T::ParamValue minValue = ParamValueMissing;

    for (uint t=0; t<mLength; t++)
    {
      if (mArray[t]->mTime == time  &&  (mArray[t]->mValue < minValue ||  minValue == ParamValueMissing))
        minValue = mArray[t]->mValue;
    }

    if (minValue != ParamValueMissing)
      return minValue;

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::ParamValue GridPointValueList::getAverageValue()
{
  try
  {
    if (mLength == 0)
      return 0;

    double total = 0;

    for (uint t=0; t<mLength; t++)
    {
      total = total + mArray[t]->mValue;
    }

    return (total / C_DOUBLE(mLength));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::ParamValue GridPointValueList::getAverageValueByTime(T::TimeString time)
{
  try
  {
    if (mLength == 0)
      return 0;

    double total = 0;
    uint count = 0;

    for (uint t=0; t<mLength; t++)
    {
      if (mArray[t]->mTime == time)
      {
        total = total + mArray[t]->mValue;
        count++;
      }
    }

    return (total / C_DOUBLE(count));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint GridPointValueList::getNumOfValuesInValueRange(T::ParamValue minValue,T::ParamValue maxValue)
{
  try
  {
    if (mLength == 0)
      return 0;

    uint count = 0;

    for (uint t=0; t<mLength; t++)
    {
      if (mArray[t]->mValue >= minValue  &&  mArray[t]->mValue < maxValue)
        count++;
    }

    return count;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::ParamValue GridPointValueList::getTimeInterpolatedValue(double x,double y,T::ParamLevel level,T::TimeString time)
{
  try
  {
    T::GridPointValue *point = getGridPointValueByPointAndTime(x,y,level,time);
    if (point != nullptr)
    {
      // Exact time match - no interpolation needed.
      return point->mValue;
    }

    T::GridPointValue *prevPoint = getPreviousGridPointValueByPointAndTime(x,y,level,time);
    if (prevPoint == nullptr)
    {
      // The current time is outside of the time range
      return ParamValueMissing;
    }

    T::GridPointValue *nextPoint = getNextGridPointValueByPointAndTime(x,y,level,time);
    if (nextPoint == nullptr)
    {
      // The current time is outside of the time range
      return ParamValueMissing;
    }

    boost::posix_time::ptime tt = toTimeStamp(time);
    boost::posix_time::ptime ttPrev = toTimeStamp(prevPoint->mTime);
    boost::posix_time::ptime ttNext = toTimeStamp(nextPoint->mTime);

    time_t diff = toTimeT(tt) - toTimeT(ttPrev);
    time_t ttDiff = toTimeT(ttNext) - toTimeT(ttPrev);

    T::ParamValue valueDiff = nextPoint->mValue - prevPoint->mValue;
    T::ParamValue valueStep = valueDiff / ttDiff;

    T::ParamValue value = prevPoint->mValue + diff * valueStep;

    //time_t toTimeT(boost::posix_time::ptime tim);
    return value;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridPointValueList::getGridPointValueListByTimeSteps(double x,double y,T::ParamLevel level,T::TimeString startTime,uint numberOfSteps,uint stepSizeInSeconds,GridPointValueList& gridPointValueList)
{
  try
  {
    boost::posix_time::ptime tt = toTimeStamp(startTime);
    for (uint t=0; t<numberOfSteps; t++)
    {
      T::TimeString tim = toString(tt);

      T::ParamValue val = getTimeInterpolatedValue(x,y,level,tim);
      gridPointValueList.addGridPointValue(new T::GridPointValue(0,0,x,y,level,tim,val));
      tt = tt + boost::posix_time::seconds(stepSizeInSeconds);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridPointValueList::print(std::ostream& stream,uint level,uint optionFlags)
{
  try
  {
    stream << space(level) << "GridPointValueList\n";
    for (uint t=0; t<mLength; t++)
      mArray[t]->print(stream,level+1,optionFlags);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




}
}
