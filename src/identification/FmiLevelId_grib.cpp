#include "FmiLevelId_grib.h"
#include "../common/Exception.h"
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





FmiLevelId_grib::~FmiLevelId_grib()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}

}
}

