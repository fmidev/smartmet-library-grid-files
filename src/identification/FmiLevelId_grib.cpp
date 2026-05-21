#include "FmiLevelId_grib.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"
#include "../common/StringFactory.h"


namespace SmartMet
{
namespace Identification
{


/*! \brief The constructor of the class. */

FmiLevelId_grib::FmiLevelId_grib()
{
  try
  {
    mFmiLevelId = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The destructor of the class. */

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





/*! \brief Prints the content of the object into the given stream. */

void FmiLevelId_grib::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "FmiLevelId_grib\n";
    stream << space(level) << "- mFmiLevelId       = " << mFmiLevelId << "\n";
    stream << space(level) << "- mParameterList    = \n";
    for (auto it = mParameterList.begin(); it != mParameterList.end(); ++it)
      stream << space(level+2) << stringFactory[it->first] << " : " << it->second << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}
}

