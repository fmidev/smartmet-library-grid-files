#include "ParameterDefinition_fmi.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{



ParameterDefinition_fmi::ParameterDefinition_fmi()
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





ParameterDefinition_fmi::ParameterDefinition_fmi(const ParameterDefinition_fmi& parameterDef)
{
  try
  {
    mFmiParameterId = parameterDef.mFmiParameterId;
    mVersion = parameterDef.mVersion;
    mParameterName = parameterDef.mParameterName;
    mParameterUnits = parameterDef.mParameterUnits;
    mParameterDescription = parameterDef.mParameterDescription;
    mInterpolationMethod = parameterDef.mInterpolationMethod;
    mNewbaseId = parameterDef.mNewbaseId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





ParameterDefinition_fmi::~ParameterDefinition_fmi()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void ParameterDefinition_fmi::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "ParameterDefinition_fmi\n";
    stream << space(level) << "- mFmiParameterId       = " << mFmiParameterId << "\n";
    stream << space(level) << "- mVersion              = " << mVersion << "\n";
    stream << space(level) << "- mParameterName        = " << mParameterName << "\n";
    stream << space(level) << "- mParameterUnits       = " << mParameterUnits << "\n";
    stream << space(level) << "- mParameterDescription = " << mParameterDescription << "\n";
    stream << space(level) << "- mInterpolationMethod  = " << (uint)mInterpolationMethod << "\n";
    stream << space(level) << "- mNewbaseId            = " << mNewbaseId << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}
}

