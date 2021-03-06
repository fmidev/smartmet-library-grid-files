#include "FmiProducerId_grib.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


FmiProducerId_grib::FmiProducerId_grib()
{
  try
  {
    mProducerId = 0;
    mType = 0;
    mCentre = 0;
    mIdent = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




FmiProducerId_grib::~FmiProducerId_grib()
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





void FmiProducerId_grib::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "FmiProducerId_grib\n";
    stream << space(level) << "- mProducerId          = " << mProducerId << "\n";
    stream << space(level) << "- mType                = " << mType << "\n";
    stream << space(level) << "- mCentre              = " << mCentre << "\n";
    stream << space(level) << "- mIdent               = " << mIdent << "\n";
    stream << space(level) << "- mProducerName        = " << mProducerName << "\n";
    stream << space(level) << "- mProducerDescription = " << mProducerDescription << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}
}

