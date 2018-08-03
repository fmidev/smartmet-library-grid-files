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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
      if (rec != NULL)
        mList.push_back(new GridValue(*rec));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridValueList::operator=(const GridValueList& gridValueList)
{
  try
  {
    clear();
    uint sz = gridValueList.getLength();
    for (uint t=0; t<sz; t++)
    {
      GridValue *rec = gridValueList.getGridValueByIndex(t);
      if (rec != NULL)
        mList.push_back(new GridValue(*rec));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridValueList::clear()
{
  try
  {
    uint sz = (uint)mList.size();
    for (uint t=0; t<sz; t++)
    {
      GridValue *rec = mList[t];
      if (rec != NULL)
        delete rec;
    }
    mList.clear();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





GridValue* GridValueList::getGridValueByIndex(uint index) const
{
  try
  {
    if (index >= (uint)mList.size())
      return NULL;

    return mList[index];
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint GridValueList::getLength() const
{
  try
  {
    return (uint)mList.size();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
      return (T::ParamValue)(total / (double)cnt);

    return ParamValueMissing;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridValueList::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "GridValueList\n";
    stream << space(level) << "- mList = \n";

    uint sz = (uint)mList.size();
    for (uint t=0; t<sz; t++)
    {
      GridValue *rec = mList[t];
      if (rec != NULL)
        rec->print(stream,level+2,optionFlags);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}
}
