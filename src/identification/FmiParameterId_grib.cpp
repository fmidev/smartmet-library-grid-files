#include "FmiParameterId_grib.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


FmiParameterId_grib::FmiParameterId_grib()
{
  try
  {
    mFmiParameterId = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




FmiParameterId_grib::~FmiParameterId_grib()
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





void FmiParameterId_grib::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "FmiParameterId_grib\n";
    stream << space(level) << "- mFmiParameterId             = " << mFmiParameterId << "\n";
    stream << space(level) << "- mGribParameterId            = " << mGribParameterId << "\n";
    stream << space(level) << "- mConversionFunction         = " << mConversionFunction << "\n";
    stream << space(level) << "- mReverseConversionFunction  = " << mReverseConversionFunction << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}
}

