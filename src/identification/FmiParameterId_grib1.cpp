#include "FmiParameterId_grib1.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


FmiParameterId_grib1::FmiParameterId_grib1()
{
  try
  {
    mFmiParameterId = 0;
    mFmiProducerId = 0;
    mGeneratingProcessIdentifier = 0;
    mCentre = 0;
    mGribTableVersion = 0;
    mGribParameterNumber = 0;
    mGribTimerangeIndicator = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





FmiParameterId_grib1::~FmiParameterId_grib1()
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}
}

