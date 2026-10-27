#include "GridPointValue.h"
#include "../common/GeneralFunctions.h"

namespace SmartMet
{
namespace T
{


/*! \brief The constructor of the class. */

GridPointValue::GridPointValue()
{
  try
  {
    mTime = 0;
    mFileId = 0;
    mMessageIndex = 0;
    mValue = 0;
    mX = 0;
    mY = 0;
    mLevel = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

GridPointValue::GridPointValue(const GridPointValue& gridPointValue)
{
  try
  {
    mFileId = gridPointValue.mFileId;
    mMessageIndex = gridPointValue.mMessageIndex;
    mX = gridPointValue.mX;
    mY = gridPointValue.mY;
    mLevel = gridPointValue.mLevel;
    mTime = gridPointValue.mTime;
    mValue = gridPointValue.mValue;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The constructor of the class.

        \param x            The grid X-coordinate
        \param y            The grid Y-coordinate
        \param valueTime    The timestamp of the parameter.
        \param level        The level of the parameter.
 */

GridPointValue::GridPointValue(T::FileId fileId,T::MessageIndex messageIndex,double x,double y,T::ParamLevel level,time_t valueTime,T::ParamValue value)
{
  try
  {
    mFileId = fileId;
    mMessageIndex = messageIndex;
    mX = x;
    mY = y;
    mLevel = level;
    mTime = valueTime;
    mValue = value;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

GridPointValue::~GridPointValue() = default;




/*! \brief Copy-assignment operator that copies fields from the given grid point value. */

GridPointValue& GridPointValue::operator=(const GridPointValue& gridPointValue)
{
  try
  {
    if (&gridPointValue == this)
      return *this;

    mFileId = gridPointValue.mFileId;
    mMessageIndex = gridPointValue.mMessageIndex;
    mX = gridPointValue.mX;
    mY = gridPointValue.mY;
    mLevel = gridPointValue.mLevel;
    mTime = gridPointValue.mTime;
    mValue = gridPointValue.mValue;

    return *this;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Compares this grid point value against another using the specified ordering scheme. */

namespace
{
/*! \brief Compares the grid point values in the time,x,y,level,value order. */

int compare_time_x_y_level_value(const GridPointValue& a,GridPointValue *b)
{
  int res = 0;
  res = time_compare(a.mTime,b->mTime);
  if (res != 0)
    return res;
  res = num_compare(a.mX,b->mX);
  if (res != 0)
    return res;
  res = num_compare(a.mY,b->mY);
  if (res != 0)
    return res;
  res = num_compare(a.mLevel,b->mLevel);
  if (res != 0)
    return res;
  return num_compare(a.mValue,b->mValue);
}




/*! \brief Compares the grid point values in the x,y,level,time,value order. */

int compare_x_y_level_time_value(const GridPointValue& a,GridPointValue *b)
{
  int res = 0;
  res = num_compare(a.mX,b->mX);
  if (res != 0)
    return res;
  res = num_compare(a.mY,b->mY);
  if (res != 0)
    return res;
  res = num_compare(a.mLevel,b->mLevel);
  if (res != 0)
    return res;
  res = time_compare(a.mTime,b->mTime);
  if (res != 0)
    return res;
  return num_compare(a.mValue,b->mValue);
}




/*! \brief Compares the grid point values in the y,x,level,time,value order. */

int compare_y_x_level_time_value(const GridPointValue& a,GridPointValue *b)
{
  int res = 0;
  res = num_compare(a.mY,b->mY);
  if (res != 0)
    return res;
  res = num_compare(a.mX,b->mX);
  if (res != 0)
    return res;
  res = num_compare(a.mLevel,b->mLevel);
  if (res != 0)
    return res;
  res = time_compare(a.mTime,b->mTime);
  if (res != 0)
    return res;
  return num_compare(a.mValue,b->mValue);
}




/*! \brief Compares the grid point values in the value,x,y,level,time order. */

int compare_value_x_y_level_time(const GridPointValue& a,GridPointValue *b)
{
  int res = 0;
  res = num_compare(a.mValue,b->mValue);
  if (res != 0)
    return res;
  res = time_compare(a.mTime,b->mTime);
  if (res != 0)
    return res;
  res = num_compare(a.mX,b->mX);
  if (res != 0)
    return res;
  res = num_compare(a.mY,b->mY);
  if (res != 0)
    return res;
  return num_compare(a.mLevel,b->mLevel);
}




/*! \brief Compares the grid point values in the file,message,x,y,level order. */

int compare_file_message_x_y_level(const GridPointValue& a,GridPointValue *b)
{
  int res = 0;
  res = num_compare(a.mFileId,b->mFileId);
  if (res != 0)
    return res;
  res = num_compare(a.mMessageIndex,b->mMessageIndex);
  if (res != 0)
    return res;
  res = num_compare(a.mX,b->mX);
  if (res != 0)
    return res;
  res = num_compare(a.mY,b->mY);
  if (res != 0)
    return res;
  return num_compare(a.mLevel,b->mLevel);
}
}  // namespace





int GridPointValue::compare(ComparisonMethod comparisonMethod,GridPointValue *gridPointValue) const
{
  try
  {
    switch (comparisonMethod)
    {
      case ComparisonMethod::none:
        return 0;

      case ComparisonMethod::time_x_y_level_value:
        return compare_time_x_y_level_value(*this,gridPointValue);

      case ComparisonMethod::x_y_level_time_value:
        return compare_x_y_level_time_value(*this,gridPointValue);

      case ComparisonMethod::y_x_level_time_value:
        return compare_y_x_level_time_value(*this,gridPointValue);

      case ComparisonMethod::value_x_y_level_time:
        return compare_value_x_y_level_time(*this,gridPointValue);

      case ComparisonMethod::file_message_x_y_level:
        return compare_file_message_x_y_level(*this,gridPointValue);

      default:
        return compare_time_x_y_level_value(*this,gridPointValue);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Creates a deep copy of this grid point value. */

GridPointValue* GridPointValue::duplicate()
{
  try
  {
    return new GridPointValue(*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param stream      The output stream.
        \param optionFlags  The printing options expressed in flag-bits.
*/

void GridPointValue::print(std::ostream& stream,uint level,uint /*optionFlags*/) const
{
  try
  {
    stream << space(level) << "GridPointValue\n";
    stream << space(level) << "- mFileId       = " << toString(mFileId) << "\n";
    stream << space(level) << "- mMessageIndex = " << toString(mMessageIndex) << "\n";
    stream << space(level) << "- mX            = " << toString(mX) << "\n";
    stream << space(level) << "- mY            = " << toString(mY) << "\n";
    stream << space(level) << "- mLevel        = " << toString(mLevel) << "\n";
    stream << space(level) << "- mTime         = " << utcTimeFromTimeT(mTime) << "\n";
    stream << space(level) << "- mValue        = " << toString(mValue) << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
}  // namespace SmartMet
