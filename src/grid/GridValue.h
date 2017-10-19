#pragma once

#include "Typedefs.h"

namespace SmartMet
{
namespace T
{


class GridValue
{
  public:
                  GridValue();
                  GridValue(const GridValue& gridValue);
                  GridValue(double x,double y, T::ParamValue value);
    virtual       ~GridValue();

    void          print(std::ostream& stream,uint level,uint optionFlags);

    double        mX;
    double        mY;
    T::ParamValue mValue;
};



}
}  // namespace SmartMet
