#include "LevelDef.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


LevelDef::LevelDef()
{
  try
  {
    mLevelId = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





LevelDef::LevelDef(const LevelDef& levelDef)
{
  try
  {
    mLevelId = levelDef.mLevelId;
    mName = levelDef.mName;
    mDescription = levelDef.mDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





LevelDef::~LevelDef()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





void LevelDef::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "LevelDef\n";
    stream << space(level) << "- mLevelId     = " << mLevelId << "\n";
    stream << space(level) << "- mName        = " << mName << "\n";
    stream << space(level) << "- mDescription = " << mDescription << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}

}
}

