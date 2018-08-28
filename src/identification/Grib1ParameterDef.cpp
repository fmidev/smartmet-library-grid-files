#include "Grib1ParameterDef.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


Grib1ParameterDef::Grib1ParameterDef()
{
  try
  {
    mTable2Version = 0;
    mCentre = 0;
    mIndicatorOfParameter = 0;
    mIndicatorOfTypeOfLevel = 0;
    mParameterLevel = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





Grib1ParameterDef::Grib1ParameterDef(const Grib1ParameterDef& parameter)
{
  try
  {
    mGribParameterId = parameter.mGribParameterId;
    mTable2Version = parameter.mTable2Version;
    mCentre = parameter.mCentre;
    mIndicatorOfParameter = parameter.mIndicatorOfParameter;
    mIndicatorOfTypeOfLevel = parameter.mIndicatorOfTypeOfLevel;
    mParameterLevel = parameter.mParameterLevel;
    mParameterUnits = parameter.mParameterUnits;
    mParameterName = parameter.mParameterName;
    mParameterDescription = parameter.mParameterDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




Grib1ParameterDef::~Grib1ParameterDef()
{
  try
  {
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}




/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void Grib1ParameterDef::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "GribParameterDef1\n";
    stream << space(level) << "- mGribParameterId        = " << mGribParameterId << "\n";
    stream << space(level) << "- mTable2Version          = " << toString(mTable2Version) << "\n";
    stream << space(level) << "- mCentre                 = " << toString(mCentre) << "\n";
    stream << space(level) << "- mIndicatorOfParameter   = " << toString(mIndicatorOfParameter) << "\n";
    stream << space(level) << "- mIndicatorOfTypeOfLevel = " << toString(mIndicatorOfTypeOfLevel) << "\n";
    stream << space(level) << "- mParameterLevel         = " << toString(mParameterLevel) << "\n";
    stream << space(level) << "- mParameterUnits         = " << mParameterUnits << "\n";
    stream << space(level) << "- mParameterName          = " << mParameterName << "\n";
    stream << space(level) << "- mParameterDescription   = " << mParameterDescription << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}  // namespace Identification
}  // namespace SmartMet
