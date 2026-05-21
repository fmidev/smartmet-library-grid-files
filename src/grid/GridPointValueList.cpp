#include "GridPointValueList.h"
#include <macgyver/Exception.h>
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



/*! \brief qsort comparator that compares two GridPointValue pointers using the current method. */

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




/*! \brief The constructor of the class. */

GridPointValueList::GridPointValueList()
{
  try
  {
    mComparisonMethod = GridPointValue::ComparisonMethod::none;
    mReleaseObjects = true;
    mSize = 0;
    mLength = 0;
    mArray = nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Copy constructor that deep-copies the contents of the source list. */

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Const copy constructor that deep-copies the contents of the source list. */

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

GridPointValueList::~GridPointValueList()
{
  try
  {
    if (mArray == nullptr)
      return;

    if (mReleaseObjects && mLength > 0)
    {
      for (uint t=0; t<mLength; t++)
      {
        if (mArray[t] != nullptr)
          delete(mArray[t]);
      }
    }
    delete[] mArray;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





/*! \brief Assignment operator that replaces this list with a copy of the source list. */

GridPointValueList& GridPointValueList::operator=(GridPointValueList& gridPointValueList)
{
  try
  {
    if (&gridPointValueList == this)
      return *this;

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

    return *this;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Const assignment operator that replaces this list with a copy of the source list. */

GridPointValueList& GridPointValueList::operator=(const GridPointValueList& gridPointValueList)
{
  try
  {
    if (&gridPointValueList == this)
      return *this;

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
    return *this;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Adds a grid point value to the list, preserving the configured sort order. */

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

    int len = C_INT(mLength);

    while (idx < len  &&  mArray[idx] != nullptr  &&   mArray[idx]->compare(mComparisonMethod,gridPointValue) < 0)
    {
      idx++;
    }

    if (idx == len)
    {
      mArray[mLength] = gridPointValue;
      mLength++;
      return;
    }

    if (idx < len)
      memmove(&mArray[idx+1],&mArray[idx],sizeof(void*)*(mLength-idx));

    mArray[idx] = gridPointValue;
    mLength++;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Empties the list, optionally releasing the owned grid point value objects. */

void GridPointValueList::clear()
{
  try
  {
    if (mArray == nullptr)
      return;

    if (mReleaseObjects  && mLength > 0)
    {
      for (uint t=0; t<mLength; t++)
      {
        if (mArray[t] != nullptr)
          delete(mArray[t]);
      }
    }
    delete[] mArray;
    mArray = nullptr;
    mSize = 0;
    mLength = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Grows the internal storage array to the given capacity. */

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

    delete[] mArray;
    mArray = newArray;
    mSize = newSize;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the index of the entry that is closest to the given value under the comparison method. */

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
    int len = C_INT(mLength);
    int sz = C_INT(mSize);
    int high = len - 1;
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

    if (mid >= 0  &&  mid < len  &&  mArray[mid] != nullptr)
    {
      if (mArray[mid]->compare(comparisonMethod,&gridPointValue) < 0)
      {
        while (mid < sz  &&  mArray[mid] != nullptr  &&   mArray[mid]->compare(comparisonMethod,&gridPointValue) < 0)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the grid point value at the given index, or nullptr if the index is out of range. */

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the grid point value at the given index without bounds checking. */

GridPointValue* GridPointValueList::getGridPointValueByIndexNoCheck(uint index)
{
  try
  {
    return mArray[index];
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Finds the grid point value matching the given file, message and coordinates. */

GridPointValue* GridPointValueList::getGridPointValueByFileMessageAndPoint(T::FileId fileId,T::MessageIndex messageIndex,double x,double y)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Finds the grid point value matching the given coordinates, level and time. */

GridPointValue* GridPointValueList::getGridPointValueByPointAndTime(double x,double y,T::ParamLevel level,time_t time)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the most recent grid point value at the given point and level strictly before the given time. */

GridPointValue* GridPointValueList::getPreviousGridPointValueByPointAndTime(double x,double y,T::ParamLevel level,time_t time)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the earliest grid point value at the given point and level strictly after the given time. */

GridPointValue* GridPointValueList::getNextGridPointValueByPointAndTime(double x,double y,T::ParamLevel level,time_t time)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Computes the bounding rectangle of all grid point coordinates in the list. */

void GridPointValueList::getGridPointValueArea(double& minX,double& minY,double& maxX,double& maxY)
{
  try
  {
    minX = 1000000000;
    minY = 1000000000;
    maxX = -1000000000;
    maxY = -1000000000;

    for (uint t=0; t<mLength; t++)
    {
      if (mArray[t]->mX < minX)
        minX = mArray[t]->mX;

      if (mArray[t]->mX > maxX)
        maxX = mArray[t]->mX;

      if (mArray[t]->mY < minY)
        minY = mArray[t]->mY;

      if (mArray[t]->mY > maxY)
        maxY = mArray[t]->mY;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Copies all grid point values matching the given point and level into the target list. */

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Copies all grid point values located inside the given rectangle and level into the target list. */

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Copies all grid point values matching the given time into the target list. */

void GridPointValueList::getGridPointValueListByTime(time_t time,GridPointValueList& gridPointValueList)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Copies all grid point values whose timestamps fall in the given range into the target list. */

void GridPointValueList::getGridPointValueListByTimeRange(time_t startTime,time_t endTime,GridPointValueList& gridPointValueList)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Copies all grid point values whose values fall in the given range into the target list. */

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the number of grid point values currently stored in the list. */

uint GridPointValueList::getLength()
{
  try
  {
    return mLength;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Removes the grid point value at the given index from the list. */

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns whether the list owns and releases its grid point value objects. */

bool GridPointValueList::getReleaseObjects()
{
  try
  {
    return mReleaseObjects;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Sets whether the list owns and releases its grid point value objects. */

void GridPointValueList::setReleaseObjects(bool releaseObjects)
{
  try
  {
    mReleaseObjects = releaseObjects;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Sets the comparison method and re-sorts the list accordingly. */

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Sorts the list using the specified comparison method. */

void GridPointValueList::sort(GridPointValue::ComparisonMethod comparisonMethod)
{
  try
  {
    if (mArray == nullptr || mLength == 0)
      return;

    mComparisonMethod = comparisonMethod;

    AutoThreadLock globalLock(&GridPointValueList_sortLock);

    gridPointValue_comparisonMethod = comparisonMethod;

    qsort(mArray,mLength,sizeof(GridPointValuePtr),gridPointValue_compare);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the maximum value among all grid point values in the list. */

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the maximum value among grid point values matching the given time. */

T::ParamValue GridPointValueList::getMaxValueByTime(time_t time)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the minimum value among all grid point values in the list. */

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the minimum value among grid point values matching the given time. */

T::ParamValue GridPointValueList::getMinValueByTime(time_t time)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the arithmetic mean of all grid point values in the list. */

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the arithmetic mean of grid point values matching the given time. */

T::ParamValue GridPointValueList::getAverageValueByTime(time_t time)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Counts grid point values whose values fall in the given range. */

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Linearly interpolates the value at the given point and level for the requested time. */

T::ParamValue GridPointValueList::getTimeInterpolatedValue(double x,double y,T::ParamLevel level,time_t time)
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

    time_t diff = time - prevPoint->mTime;
    time_t ttDiff = nextPoint->mTime - prevPoint->mTime;

    T::ParamValue valueDiff = nextPoint->mValue - prevPoint->mValue;
    T::ParamValue valueStep = valueDiff / ttDiff;

    T::ParamValue value = prevPoint->mValue + diff * valueStep;

    //time_t toTimeT(Fmi::DateTime tim);
    return value;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Generates a time series of interpolated values at the given point and level. */

void GridPointValueList::getGridPointValueListByTimeSteps(double x,double y,T::ParamLevel level,time_t startTime,uint numberOfSteps,uint stepSizeInSeconds,GridPointValueList& gridPointValueList)
{
  try
  {
    time_t tt = startTime;
    for (uint t=0; t<numberOfSteps; t++)
    {
      T::ParamValue val = getTimeInterpolatedValue(x,y,level,tt);
      gridPointValueList.addGridPointValue(new T::GridPointValue(0,0,x,y,level,tt,val));
      tt = tt + stepSizeInSeconds;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Prints the contents of the list into the given stream. */

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




}
}
