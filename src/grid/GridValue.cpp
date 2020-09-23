#include "GridValue.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace T
{


GridValue::GridValue()
{
  try
  {
    mX = 0;
    mY = 0;
    mValue = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





GridValue::GridValue(const GridValue& gridValue)
{
  try
  {
    mX = gridValue.mX;
    mY = gridValue.mY;
    mValue = gridValue.mValue;
    mValueString = gridValue.mValueString;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





GridValue::GridValue(double x,double y, T::ParamValue value)
{
  try
  {
    mX = x;
    mY = y;
    mValue = value;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





GridValue::GridValue(double x,double y, std::string valueString)
{
  try
  {
    mX = x;
    mY = y;
    mValue = 0;
    mValueString = valueString;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





GridValue::GridValue(double x,double y, T::ParamValue value, std::string valueString)
{
  try
  {
    mX = x;
    mY = y;
    mValue = value;
    mValueString = valueString;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





GridValue::~GridValue()
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





void GridValue::print(std::ostream& stream,uint level,uint optionFlags)
{
  try
  {
    stream << space(level) << "GridValue\n";
    stream << space(level) << "- mX           = " << mX << "\n";
    stream << space(level) << "- mY           = " << mY << "\n";
    stream << space(level) << "- mValue       = " << mValue << "\n";
    stream << space(level) << "- mValueString = " << mValueString << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
}  // namespace SmartMet
