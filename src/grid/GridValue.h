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
                  //GridValue(const GridValue& gridValue);
                  GridValue(double x,double y, T::ParamValue value);
                  GridValue(double x,double y, const char *valueString);
                  GridValue(double x,double y, std::string& valueString);
                  GridValue(double x,double y, T::ParamValue value, std::string& valueString);
                  GridValue(double x,double y, T::ParamValue value, const char *valueString);
    virtual       ~GridValue();

    void          print(std::ostream& stream,uint level,uint optionFlags);

    double        mX;
    double        mY;
    T::ParamValue mValue;
    std::string   mValueString;
};



}
}  // namespace SmartMet
