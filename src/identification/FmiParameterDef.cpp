#include "FmiParameterDef.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{



FmiParameterDef::FmiParameterDef()
{
  try
  {
    mVersion = 0;
    mInterpolationMethod = T::InterpolationMethod::Unknown;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    mInterpolationMethod = parameterDef.mInterpolationMethod;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





FmiParameterDef::~FmiParameterDef()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void FmiParameterDef::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "FmiParameterDef\n";
    stream << space(level) << "- mFmiParameterId       = " << mFmiParameterId << "\n";
    stream << space(level) << "- mVersion              = " << mVersion << "\n";
    stream << space(level) << "- mParameterName        = " << mParameterName << "\n";
    stream << space(level) << "- mParameterUnits       = " << mParameterUnits << "\n";
    stream << space(level) << "- mParameterDescription = " << mParameterDescription << "\n";
    stream << space(level) << "- mInterpolationMethod  = " << (uint)mInterpolationMethod << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}
}

