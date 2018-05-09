#include "GribTableValue.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


/*! \brief The constructor of the class. */

GribTableValue::GribTableValue()
{
  try
  {
    mGribVersion = 0;
    mTableVersion = 0;
    mNumber = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The copy constructor of the class. */

GribTableValue::GribTableValue(const GribTableValue& tableValue)
{
  try
  {
    mGribVersion = tableValue.mGribVersion;
    mTableVersion = tableValue.mTableVersion;
    mTable = tableValue.mTable;
    mNumber = tableValue.mNumber;
    mName = tableValue.mName;
    mValue = tableValue.mValue;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The destructor of the class. */

GribTableValue::~GribTableValue()
{
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void GribTableValue::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "GribTableValue\n";
    stream << space(level) << "- mGribVersion  = " << toString(mGribVersion) << "\n";
    stream << space(level) << "- mTableVersion = " << toString(mTableVersion) << "\n";
    stream << space(level) << "- mTable        = " << mTable << "\n";
    stream << space(level) << "- mNumber       = " << toString(mNumber) << "\n";
    stream << space(level) << "- mName         = " << mName << "\n";
    stream << space(level) << "- mValue        = " << mValue << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}

}  // namespace GRID
}  // namespace SmartMet
