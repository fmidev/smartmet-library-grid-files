#include "GridValue.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"


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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





GridValue::GridValue(const GridValue& gridValue)
{
  try
  {
    mX = gridValue.mX;
    mY = gridValue.mY;
    mValue = gridValue.mValue;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





GridValue::~GridValue()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridValue::print(std::ostream& stream,uint level,uint optionFlags)
{
  try
  {
    stream << space(level) << "GridValue\n";
    stream << space(level) << "- mX     = " << mX << "\n";
    stream << space(level) << "- mY     = " << mY << "\n";
    stream << space(level) << "- mValue = " << mValue << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}
}  // namespace SmartMet
