#include "FmiParameterId_netCdf.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


FmiParameterId_netCdf::FmiParameterId_netCdf()
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




FmiParameterId_netCdf::~FmiParameterId_netCdf()
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





void FmiParameterId_netCdf::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "FmiParameterId_netCdf\n";
    stream << space(level) << "- mFmiParameterId             = " << mFmiParameterId << "\n";
    stream << space(level) << "- mNetCdfParameterName        = " << mNetCdfParameterName << "\n";
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

