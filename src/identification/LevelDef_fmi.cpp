#include "LevelDef_fmi.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


LevelDef_fmi::LevelDef_fmi()
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





LevelDef_fmi::LevelDef_fmi(const LevelDef_fmi& level)
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





LevelDef_fmi::~LevelDef_fmi()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





void LevelDef_fmi::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "LevelDef_fmi\n";
    stream << space(level) << "- mFmiProducerId               = " << mFmiProducerId << "\n";
    stream << space(level) << "- mGeneratingProcessIdentifier = " << mGeneratingProcessIdentifier << "\n";
    stream << space(level) << "- mCentre                      = " << mCentre << "\n";
    stream << space(level) << "- mGribLevelId                 = " << mGribLevelId << "\n";
    stream << space(level) << "- mFmiLevelId                  = " << mFmiLevelId << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}

}
}

