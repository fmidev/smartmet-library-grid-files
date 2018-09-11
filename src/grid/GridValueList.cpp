#include "GridValueList.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace T
{


GridValueList::GridValueList()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




GridValueList::GridValueList(const GridValueList& gridValueList)
{
  try
  {
    uint sz = gridValueList.getLength();
    for (uint t=0; t<sz; t++)
    {
      GridValue *rec = gridValueList.getGridValueByIndex(t);
      if (rec != nullptr)
        mList.push_back(new GridValue(*rec));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GridValueList::~GridValueList()
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





GridValueList& GridValueList::operator=(const GridValueList& gridValueList)
{
  try
  {
    if (&gridValueList == this)
      return *this;

    clear();
    uint sz = gridValueList.getLength();
    for (uint t=0; t<sz; t++)
    {
      GridValue *rec = gridValueList.getGridValueByIndex(t);
      if (rec != nullptr)
        mList.push_back(new GridValue(*rec));
    }
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridValueList::addGridValue(GridValue *gridValue)
{
  try
  {
    mList.push_back(gridValue);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridValueList::clear()
{
  try
  {
    uint sz = mList.size();
    for (uint t=0; t<sz; t++)
    {
      GridValue *rec = mList[t];
      if (rec != nullptr)
        delete rec;
    }
    mList.clear();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GridValue* GridValueList::getGridValueByIndex(uint index) const
{
  try
  {
    if (index >= mList.size())
      return nullptr;

    return mList[index];
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GridValue* GridValueList::getGridValueByCoordinates(double x,double y) const
{
  try
  {
    for (auto it=mList.begin(); it != mList.end(); ++it)
    {
      if ((*it)->mX == x  &&  (*it)->mY == y)
        return (*it);
    }
    return nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint GridValueList::getLength() const
{
  try
  {
    return mList.size();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::ParamValue GridValueList::getMaxValue() const
{
  try
  {
    T::ParamValue max = ParamValueMissing;

    for (auto it=mList.begin(); it != mList.end(); ++it)
    {
      if ((*it)->mValue != ParamValueMissing  &&  (max == ParamValueMissing || (*it)->mValue > max))
        max = (*it)->mValue;
    }
    return max;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::ParamValue GridValueList::getMinValue() const
{
  try
  {
    T::ParamValue min = ParamValueMissing;

    for (auto it=mList.begin(); it != mList.end(); ++it)
    {
      if ((*it)->mValue != ParamValueMissing  &&  (min == ParamValueMissing || (*it)->mValue < min))
        min = (*it)->mValue;
    }
    return min;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::ParamValue GridValueList::getAverageValue() const
{
  try
  {
    double total = 0;
    uint cnt = 0;

    for (auto it=mList.begin(); it != mList.end(); ++it)
    {
      if ((*it)->mValue != ParamValueMissing)
      {
        total = total + (*it)->mValue;
        cnt++;
      }
    }

    if (cnt != 0)
      return (total / C_DOUBLE(cnt));

    return ParamValueMissing;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint GridValueList::getNumOfValuesInValueRange(T::ParamValue minValue,T::ParamValue maxValue) const
{
  try
  {
    uint cnt = 0;
    for (auto it=mList.begin(); it != mList.end(); ++it)
    {
      if ((*it)->mValue >= minValue  &&  (*it)->mValue <= maxValue)
        cnt++;
    }
    return cnt;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridValueList::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "GridValueList\n";
    stream << space(level) << "- mList = \n";

    uint sz = mList.size();
    for (uint t=0; t<sz; t++)
    {
      GridValue *rec = mList[t];
      if (rec != nullptr)
        rec->print(stream,level+2,optionFlags);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}
}
