#include "Grib2ParameterDef.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"
#include "../common/StringFactory.h"


namespace SmartMet
{
namespace Identification
{


Grib2ParameterDef::Grib2ParameterDef()
{
  try
  {
    mGribParameterId = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





Grib2ParameterDef::~Grib2ParameterDef()
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





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void Grib2ParameterDef::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "GribParameterDef2\n";
    stream << space(level) << "- mGribParameterId  = " << mGribParameterId << "\n";
    stream << space(level) << "- mParameterList    = \n";
    for (auto it = mParameterList.begin(); it != mParameterList.end(); ++it)
      stream << space(level+2) << stringFactory[it->first] << " : " << it->second << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}  // namespace GRIB2
}  // namespace SmartMet
