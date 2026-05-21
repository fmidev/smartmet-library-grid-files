#include "GridValue.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace T
{


/*! \brief Default constructor that initializes coordinates and value to zero. */

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





/*! \brief Constructs a GridValue at the given coordinates with the given numeric value. */

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





/*! \brief Constructs a GridValue at the given coordinates with a string value. */

GridValue::GridValue(double x,double y, std::string& valueString)
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





/*! \brief Constructs a GridValue at the given coordinates with a C-string value. */

GridValue::GridValue(double x,double y, const char *valueString)
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





/*! \brief Constructs a GridValue with both numeric and string value representations. */

GridValue::GridValue(double x,double y, T::ParamValue value, std::string& valueString)
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





/*! \brief Constructs a GridValue with both numeric and C-string value representations. */

GridValue::GridValue(double x,double y, T::ParamValue value, const char *valueString)
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





/*! \brief The destructor of the class. */

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





/*! \brief Prints the contents of the grid value into the given stream. */

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
