#include "FmiParameterId_grib2.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


FmiParameterId_grib2::FmiParameterId_grib2()
{
  try
  {
    mFmiProducerId = 0;
    mGeneratingProcessIdentifier = 0;
    mCentre = 0;
    mDiscipline = 0;
    mParameterCategory = 0;
    mParameterNumber = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





FmiParameterId_grib2::FmiParameterId_grib2(const FmiParameterId_grib2& parameter)
{
  try
  {
    mFmiParameterId = parameter.mFmiParameterId;
    mFmiProducerId = parameter.mFmiProducerId;
    mGeneratingProcessIdentifier = parameter.mGeneratingProcessIdentifier;
    mCentre = parameter.mCentre;
    mDiscipline = parameter.mDiscipline;
    mParameterCategory = parameter.mParameterCategory;
    mParameterNumber = parameter.mParameterNumber;
    mFmiParameterLevelId = parameter.mFmiParameterLevelId;
    mGribParameterLevelId = parameter.mGribParameterLevelId;
    mParameterLevel = parameter.mParameterLevel;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





FmiParameterId_grib2::~FmiParameterId_grib2()
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





void FmiParameterId_grib2::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "FmiParameterId_grib2\n";
    stream << space(level) << "- mFmiParameterId              = " << mFmiParameterId << "\n";
    stream << space(level) << "- mFmiProducerId               = " << mFmiProducerId << "\n";
    stream << space(level) << "- mGeneratingProcessIdentifier = " << mGeneratingProcessIdentifier << "\n";
    stream << space(level) << "- mCentre                      = " << mCentre << "\n";
    stream << space(level) << "- mDiscipline                  = " << mDiscipline << "\n";
    stream << space(level) << "- mParameterCategory           = " << mParameterCategory << "\n";
    stream << space(level) << "- mParameterNumber             = " << mParameterNumber << "\n";
    stream << space(level) << "- mFmiParameterLevelId         = " << toString(mFmiParameterLevelId) << "\n";
    stream << space(level) << "- mGribParameterLevelId        = " << toString(mGribParameterLevelId) << "\n";
    stream << space(level) << "- mParameterLevel              = " << toString(mParameterLevel) << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}
}
