#include "Parameter_grib2_fmi.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


Parameter_grib2_fmi::Parameter_grib2_fmi()
{
  try
  {
    mDbId = 0;
    mFmiProducerId = 0;
    mGeneratingProcessIdentifier = 0;
    mCentre = 0;
    mDiscipline = 0;
    mParameterCategory = 0;
    mParameterNumber = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





Parameter_grib2_fmi::Parameter_grib2_fmi(const Parameter_grib2_fmi& parameter)
{
  try
  {
    mDbId = parameter.mDbId;
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





Parameter_grib2_fmi::~Parameter_grib2_fmi()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





void Parameter_grib2_fmi::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "Parameter_grib2_fmi\n";
    stream << space(level) << "- mDbId                        = " << mDbId << "\n";
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}


}
}
