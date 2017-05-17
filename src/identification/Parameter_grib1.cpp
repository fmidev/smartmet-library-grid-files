#include "Parameter_grib1.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


Parameter_grib1::Parameter_grib1()
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





Parameter_grib1::Parameter_grib1(const Parameter_grib1& parameter)
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




Parameter_grib1::~Parameter_grib1()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void Parameter_grib1::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "ParameterDefinition_grib1\n";
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}


}  // namespace Identification
}  // namespace SmartMet
