#include "FmiParameterId_grib2.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


FmiParameterId_grib2::FmiParameterId_grib2()
{
  try
  {
    mFmiParameterId = 0;
    mFmiProducerId = 0;
    mGeneratingProcessIdentifier = 0;
    mCentre = 0;
    mDiscipline = 0;
    mParameterCategory = 0;
    mParameterNumber = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





FmiParameterId_grib2::~FmiParameterId_grib2()
{
  try
  {
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
}
