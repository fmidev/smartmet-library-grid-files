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
                      GridValueList(const GridValueList& gridValueList);
     virtual          ~GridValueList();

     void             operator=(const GridValueList& gridValueList);

     void             addGridValue(GridValue *gridValue);
     void             clear();
     GridValue*       getGridValueByIndex(uint index) const;
     GridValue*       getGridValueByCoordinates(double x,double y) const;
     uint             getLength() const;
     T::ParamValue    getMaxValue() const;
     T::ParamValue    getMinValue() const;
     T::ParamValue    getAverageValue() const;
     uint             getNumOfValuesInValueRange(T::ParamValue minValue,T::ParamValue maxValue) const;
     void             print(std::ostream& stream,uint level,uint optionFlags) const;

  protected:

     std::vector<GridValue*>  mList;
};


}
}
