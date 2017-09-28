#pragma once

#include <vector>
#include "GridValue.h"


namespace SmartMet
{
namespace T
{


class GridValueList
{
  public:
                      GridValueList();
                      GridValueList(GridValueList& gridValueList);
     virtual          ~GridValueList();

     void             operator=(GridValueList& gridValueList);

     void             addGridValue(GridValue *gridValue);
     void             clear();
     GridValue*       getGridValueByIndex(uint index);
     uint             getLength();
     T::ParamValue    getMaxValue();
     T::ParamValue    getMinValue();
     T::ParamValue    getAverageValue();
     uint             getNumOfValuesInValueRange(T::ParamValue minValue,T::ParamValue maxValue);
     void             print(std::ostream& stream,uint level,uint optionFlags);

  protected:

     std::vector<GridValue*>  mList;
};


}
}
