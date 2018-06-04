#include "FmiParameterId_grib1.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


FmiParameterId_grib1::FmiParameterId_grib1()
{
  try
  {
    mFmiProducerId = 0;
    mGeneratingProcessIdentifier = 0;
    mCentre = 0;
    mGribTableVersion = 0;
    mGribParameterNumber = 0;
    mGribTimerangeIndicator = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





FmiParameterId_grib1::FmiParameterId_grib1(const FmiParameterId_grib1& parameter)
{
  try
  {
    mFmiParameterId = parameter.mFmiParameterId;
    mFmiProducerId = parameter.mFmiProducerId;
    mGeneratingProcessIdentifier = parameter.mGeneratingProcessIdentifier;
    mCentre = parameter.mCentre;
    mGribTableVersion = parameter.mGribTableVersion;
    mGribParameterNumber = parameter.mGribParameterNumber;
    mGribTimerangeIndicator = parameter.mGribTimerangeIndicator;
    mFmiParameterLevelId = parameter.mFmiParameterLevelId;
    mGribParameterLevelId = parameter.mGribParameterLevelId;
    mParameterLevel = parameter.mParameterLevel;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





FmiParameterId_grib1::~FmiParameterId_grib1()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void FmiParameterId_grib1::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "FmiParameterId_grib1\n";
    stream << space(level) << "- mFmiParameterId              = " << mFmiParameterId << "\n";
    stream << space(level) << "- mFmiProducerId               = " << mFmiProducerId << "\n";
    stream << space(level) << "- mGeneratingProcessIdentifier = " << mGeneratingProcessIdentifier << "\n";
    stream << space(level) << "- mCentre                      = " << mCentre << "\n";
    stream << space(level) << "- mGribTableVersion            = " << mGribTableVersion << "\n";
    stream << space(level) << "- mGribParameterNumber         = " << mGribParameterNumber << "\n";
    stream << space(level) << "- mGribTimerangeIndicator      = " << mGribTimerangeIndicator << "\n";
    stream << space(level) << "- mFmiParameterLevelId         = " << toString(mFmiParameterLevelId) << "\n";
    stream << space(level) << "- mGribParameterLevelId        = " << toString(mGribParameterLevelId) << "\n";
    stream << space(level) << "- mParameterLevel              = " << toString(mParameterLevel) << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}

}
}

