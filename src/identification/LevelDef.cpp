#include "LevelDef.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"


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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




LevelDef::~LevelDef()
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}
}

