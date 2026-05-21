#include "LevelDef.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


/*! \brief The constructor of the class. */

LevelDef::LevelDef()
{
  try
  {
    mLevelId = 0;
    mType = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The destructor of the class. */

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





/*! \brief Prints the content of the object into the given stream. */

void LevelDef::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "LevelDef\n";
    stream << space(level) << "- mLevelId     = " << mLevelId << "\n";
    stream << space(level) << "- mName        = " << mName << "\n";
    stream << space(level) << "- mType        = " << (int)mType << "\n";
    stream << space(level) << "- mUnits       = " << mUnits << "\n";
    stream << space(level) << "- mDescription = " << mDescription << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}
}

