#include "Parameter_grib1_fmi.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


Parameter_grib1_fmi::Parameter_grib1_fmi()
{
  try
  {
    mDbId = 0;
    mFmiProducerId = 0;
    mGeneratingProcessIdentifier = 0;
    mCentre = 0;
    mGribTableVersion = 0;
    mGribParameterNumber = 0;
    mGribTimerangeIndicator = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





Parameter_grib1_fmi::Parameter_grib1_fmi(const Parameter_grib1_fmi& parameter)
{
  try
  {
    mDbId = parameter.mDbId;
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





Parameter_grib1_fmi::~Parameter_grib1_fmi()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





void Parameter_grib1_fmi::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "Parameter_grib1_fmi\n";
    stream << space(level) << "- mDbId                        = " << mDbId << "\n";
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}

}
}

