#include "FmiLevelId_grib.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


FmiLevelId_grib::FmiLevelId_grib()
{
  try
  {
    mFmiProducerId = 0;
    mGeneratingProcessIdentifier = 0;
    mCentre = 0;
    mGribLevelId = 0;
    mFmiLevelId = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*
FmiLevelId_grib::FmiLevelId_grib(const FmiLevelId_grib& level)
{
  try
  {
    mFmiProducerId = level.mFmiProducerId;
    mGeneratingProcessIdentifier = level.mGeneratingProcessIdentifier;
    mCentre = level.mCentre;
    mGribLevelId = level.mGribLevelId;
    mFmiLevelId = level.mFmiLevelId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}
*/




FmiLevelId_grib::~FmiLevelId_grib()
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





void FmiLevelId_grib::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "FmiLevelId_grib\n";
    stream << space(level) << "- mFmiProducerId               = " << mFmiProducerId << "\n";
    stream << space(level) << "- mGeneratingProcessIdentifier = " << mGeneratingProcessIdentifier << "\n";
    stream << space(level) << "- mCentre                      = " << mCentre << "\n";
    stream << space(level) << "- mGribLevelId                 = " << mGribLevelId << "\n";
    stream << space(level) << "- mFmiLevelId                  = " << mFmiLevelId << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}
}

