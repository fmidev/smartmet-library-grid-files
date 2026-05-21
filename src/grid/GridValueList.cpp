#include "GridValueList.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace T
{


/*! \brief The constructor of the class. */

GridValueList::GridValueList()
{
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Copy constructor that copies the underlying list of grid values. */

GridValueList::GridValueList(const GridValueList& gridValueList)
{
  try
  {
    mList = gridValueList.mList;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

GridValueList::~GridValueList()
{
  try
  {
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





/*! \brief Assignment operator that replaces this list with a copy of the source list. */

GridValueList& GridValueList::operator=(const GridValueList& gridValueList)
{
  try
  {
    if (&gridValueList == this)
      return *this;

    mList = gridValueList.mList;
    return *this;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Appends a grid value to the end of the list. */

void GridValueList::addGridValue(GridValue& gridValue)
{
  try
  {
    mList.emplace_back(gridValue);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Removes all grid values from the list. */

void GridValueList::clear()
{
  try
  {
    mList.clear();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns a pointer to the grid value at the given index, or nullptr if out of range. */

GridValue* GridValueList::getGridValuePtrByIndex(uint index) const
{
  try
  {
    if (index >= mList.size())
      return nullptr;

    return (GridValue*)&mList[index];
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Copies the grid value at the given index into the output parameter. */

bool GridValueList::getGridValueByIndex(uint index,GridValue& gridValue) const
{
  try
  {
    if (index >= mList.size())
      return false;

    gridValue = mList[index];
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Replaces the grid value at the given index with the supplied value. */

bool GridValueList::setGridValueByIndex(uint index,GridValue& gridValue)
{
  try
  {
    if (index >= mList.size())
      return false;

    mList[index] = gridValue;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



/*! \brief Finds the grid value matching the given coordinates. */

bool GridValueList::getGridValueByCoordinates(double x,double y,GridValue& gridValue) const
{
  try
  {
    for (auto it=mList.begin(); it != mList.end(); ++it)
    {
      if (it->mX == x  &&  it->mY == y)
      {
        gridValue = *it;
        return true;
      }
    }
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Computes the bounding rectangle of all grid values in the list. */

void GridValueList::getGridValueArea(double& minX,double& minY,double& maxX,double& maxY)
{
  try
  {
    minX = 1000000000;
    minY = 1000000000;
    maxX = -1000000000;
    maxY = -1000000000;

    uint len = mList.size();
    for (uint t=0; t<len; t++)
    {
      if (mList[t].mX < minX)
        minX = mList[t].mX;

      if (mList[t].mX > maxX)
        maxX = mList[t].mX;

      if (mList[t].mY < minY)
        minY = mList[t].mY;

      if (mList[t].mY > maxY)
        maxY = mList[t].mY;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the number of grid values currently stored in the list. */

uint GridValueList::getLength() const
{
  try
  {
    return mList.size();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the maximum value among all grid values in the list, ignoring missing values. */

T::ParamValue GridValueList::getMaxValue() const
{
  try
  {
    T::ParamValue max = ParamValueMissing;

    for (auto it=mList.begin(); it != mList.end(); ++it)
    {
      if (it->mValue != ParamValueMissing  &&  (max == ParamValueMissing || it->mValue > max))
        max = it->mValue;
    }
    return max;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the minimum value among all grid values in the list, ignoring missing values. */

T::ParamValue GridValueList::getMinValue() const
{
  try
  {
    T::ParamValue min = ParamValueMissing;

    for (auto it=mList.begin(); it != mList.end(); ++it)
    {
      if (it->mValue != ParamValueMissing  &&  (min == ParamValueMissing || it->mValue < min))
        min = it->mValue;
    }
    return min;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the arithmetic mean of grid values in the list, ignoring missing values. */

T::ParamValue GridValueList::getAverageValue() const
{
  try
  {
    double total = 0;
    uint cnt = 0;

    for (auto it=mList.begin(); it != mList.end(); ++it)
    {
      if (it->mValue != ParamValueMissing)
      {
        total = total + it->mValue;
        cnt++;
      }
    }

    if (cnt != 0)
      return (total / C_DOUBLE(cnt));

    return ParamValueMissing;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Counts grid values whose values fall in the given inclusive range. */

uint GridValueList::getNumOfValuesInValueRange(T::ParamValue minValue,T::ParamValue maxValue) const
{
  try
  {
    uint cnt = 0;
    for (auto it=mList.begin(); it != mList.end(); ++it)
    {
      if (it->mValue >= minValue  &&  it->mValue <= maxValue)
        cnt++;
    }
    return cnt;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Prints the contents of the grid value list into the given stream. */

void GridValueList::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "GridValueList\n";
    stream << space(level) << "- mList = \n";

    uint sz = mList.size();
    for (uint t=0; t<sz; t++)
    {
      auto it = mList[t];
      it.print(stream,level+2,optionFlags);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




}
}
