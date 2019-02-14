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

     GridValueList&   operator=(const GridValueList& gridValueList);

     void             addGridValue(GridValue& gridValue);
     void             clear();
     GridValue*       getGridValuePtrByIndex(uint index) const;
     bool             getGridValueByIndex(uint index,GridValue& gridValue) const;
     bool             getGridValueByCoordinates(double x,double y,GridValue& gridValue) const;
     uint             getLength() const;
     T::ParamValue    getMaxValue() const;
     T::ParamValue    getMinValue() const;
     T::ParamValue    getAverageValue() const;
     uint             getNumOfValuesInValueRange(T::ParamValue minValue,T::ParamValue maxValue) const;
     void             print(std::ostream& stream,uint level,uint optionFlags) const;

  protected:

     std::vector<GridValue>  mList;
};

}
}
