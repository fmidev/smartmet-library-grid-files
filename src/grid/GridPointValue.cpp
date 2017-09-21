#include "GridPointValue.h"
#include "common/GeneralFunctions.h"

namespace SmartMet
{
namespace T
{


/*! \brief The constructor of the class. */

GridPointValue::GridPointValue()
{
  try
  {
    mFileId = 0;
    mMessageIndex = 0;
    mValue = 0;
    mX = 0;
    mY = 0;
    mLevel = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The constructor of the class.

        \param x            The grid X-coordinate
        \param y            The grid Y-coordinate
        \param valueTime    The timestamp of the parameter.
        \param level        The level of the parameter.
 */

GridPointValue::GridPointValue(uint fileId,uint messageIndex,double x,double y,T::ParamLevel level,T::TimeString valueTime,T::ParamValue value)
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The destructor of the class. */

GridPointValue::~GridPointValue()
{
}




void GridPointValue::operator=(GridPointValue& gridPointValue)
{
  try
  {
    if (&gridPointValue == this)
      return;

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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





int GridPointValue::compare(ComparisonMethod comparisonMethod,GridPointValue *gridPointValue)
{
  try
  {
    int res = 0;
    switch (comparisonMethod)
    {
      case ComparisonMethod::none:
        return 0;

      case ComparisonMethod::time_x_y_level_value:
        res = strcmp(mTime.c_str(),gridPointValue->mTime.c_str());
        if (res != 0)
          return res;
        res = double_compare(mX,gridPointValue->mX);
        if (res != 0)
          return res;
        res = double_compare(mY,gridPointValue->mY);
        if (res != 0)
          return res;
        res = uint_compare((uint)mLevel,(uint)gridPointValue->mLevel);
        if (res != 0)
          return res;
        return double_compare(mValue,gridPointValue->mValue);

      case ComparisonMethod::x_y_level_time_value:
        res = double_compare(mX,gridPointValue->mX);
        if (res != 0)
          return res;
        res = double_compare(mY,gridPointValue->mY);
        if (res != 0)
          return res;
        res = uint_compare((uint)mLevel,(uint)gridPointValue->mLevel);
        if (res != 0)
          return res;
        res = strcmp(mTime.c_str(),gridPointValue->mTime.c_str());
        if (res != 0)
          return res;
        return double_compare(mValue,gridPointValue->mValue);

      case ComparisonMethod::y_x_level_time_value:
        res = double_compare(mY,gridPointValue->mY);
        if (res != 0)
          return res;
        res = double_compare(mX,gridPointValue->mX);
        if (res != 0)
          return res;
        res = uint_compare((uint)mLevel,(uint)gridPointValue->mLevel);
        if (res != 0)
          return res;
        res = strcmp(mTime.c_str(),gridPointValue->mTime.c_str());
        if (res != 0)
          return res;
        return double_compare(mValue,gridPointValue->mValue);

      case ComparisonMethod::value_x_y_level_time:
        res = double_compare(mValue,gridPointValue->mValue);
        if (res != 0)
          return res;
        res = strcmp(mTime.c_str(),gridPointValue->mTime.c_str());
        if (res != 0)
          return res;
        res = double_compare(mX,gridPointValue->mX);
        if (res != 0)
          return res;
        res = double_compare(mY,gridPointValue->mY);
        if (res != 0)
          return res;
        return uint_compare((uint)mLevel,(uint)gridPointValue->mLevel);

      case ComparisonMethod::file_message_x_y_level:
        res = uint_compare(mFileId,(uint)gridPointValue->mFileId);
        if (res != 0)
          return res;
        res = uint_compare(mMessageIndex,(uint)gridPointValue->mMessageIndex);
        if (res != 0)
          return res;
        res = double_compare(mX,gridPointValue->mX);
        if (res != 0)
          return res;
        res = double_compare(mY,gridPointValue->mY);
        if (res != 0)
          return res;
        return uint_compare((uint)mLevel,(uint)gridPointValue->mLevel);

      default:
        res = strcmp(mTime.c_str(),gridPointValue->mTime.c_str());
        if (res != 0)
          return res;
        res = double_compare(mX,gridPointValue->mX);
        if (res != 0)
          return res;
        res = double_compare(mY,gridPointValue->mY);
        if (res != 0)
          return res;
        res = uint_compare((uint)mLevel,(uint)gridPointValue->mLevel);
        if (res != 0)
          return res;
        return double_compare(mValue,gridPointValue->mValue);
    }
    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





GridPointValue* GridPointValue::duplicate()
{
  try
  {
    return new GridPointValue(*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param optionFlags  The printing options expressed in flag-bits.
*/

void GridPointValue::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "GridPointValue\n";
    stream << space(level) << "- mFileId       = " << toString(mFileId) << "\n";
    stream << space(level) << "- mMessageIndex = " << toString(mMessageIndex) << "\n";
    stream << space(level) << "- mX            = " << toString(mX) << "\n";
    stream << space(level) << "- mY            = " << toString(mY) << "\n";
    stream << space(level) << "- mLevel        = " << toString((uint)mLevel) << "\n";
    stream << space(level) << "- mTime         = " << toString(mTime) << "\n";
    stream << space(level) << "- mValue        = " << toString(mValue) << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}
}  // namespace SmartMet
