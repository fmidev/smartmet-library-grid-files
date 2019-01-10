#include "FmiParameterDef.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{



FmiParameterDef::FmiParameterDef()
{
  try
  {
    mVersion = 0;
    mAreaInterpolationMethod = T::AreaInterpolationMethod::Undefined;
    mTimeInterpolationMethod = T::TimeInterpolationMethod::Undefined;
    mLevelInterpolationMethod = T::LevelInterpolationMethod::Undefined;
    mDefaultPrecision = -1;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





FmiParameterDef::FmiParameterDef(const FmiParameterDef& parameterDef)
{
  try
  {
    mFmiParameterId = parameterDef.mFmiParameterId;
    mVersion = parameterDef.mVersion;
    mParameterName = parameterDef.mParameterName;
    mParameterUnits = parameterDef.mParameterUnits;
    mParameterDescription = parameterDef.mParameterDescription;
    mAreaInterpolationMethod = parameterDef.mAreaInterpolationMethod;
    mTimeInterpolationMethod = parameterDef.mTimeInterpolationMethod;
    mLevelInterpolationMethod = parameterDef.mLevelInterpolationMethod;
    mDefaultPrecision = parameterDef.mDefaultPrecision;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





FmiParameterDef::~FmiParameterDef()
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





void FmiParameterDef::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "FmiParameterDef\n";
    stream << space(level) << "- mFmiParameterId           = " << mFmiParameterId << "\n";
    stream << space(level) << "- mVersion                  = " << mVersion << "\n";
    stream << space(level) << "- mParameterName            = " << mParameterName << "\n";
    stream << space(level) << "- mParameterUnits           = " << mParameterUnits << "\n";
    stream << space(level) << "- mParameterDescription     = " << mParameterDescription << "\n";
    stream << space(level) << "- mAreaInterpolationMethod  = " << mAreaInterpolationMethod << "\n";
    stream << space(level) << "- mTimeInterpolationMethod  = " << mTimeInterpolationMethod << "\n";
    stream << space(level) << "- mLevelInterpolationMethod = " << mLevelInterpolationMethod << "\n";
    stream << space(level) << "- mDefaultPrecision         = " << mDefaultPrecision << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}
}

