#include "FmiParameterId_grib.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


FmiParameterId_grib::FmiParameterId_grib()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





FmiParameterId_grib::FmiParameterId_grib(const FmiParameterId_grib& parameter)
{
  try
  {
    mFmiParameterId = parameter.mFmiParameterId;
    mGribParameterId = parameter.mGribParameterId;
    mConversionFunction = parameter.mConversionFunction;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





FmiParameterId_grib::~FmiParameterId_grib()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void FmiParameterId_grib::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "FmiParameterId_grib\n";
    stream << space(level) << "- mFmiParameterId      = " << mFmiParameterId << "\n";
    stream << space(level) << "- mGribParameterId  = " << mGribParameterId << "\n";
    stream << space(level) << "- mConversionFunction  = " << mConversionFunction << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}

}
}

