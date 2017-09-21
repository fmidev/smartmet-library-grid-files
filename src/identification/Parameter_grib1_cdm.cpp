#include "Parameter_grib1_cdm.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


Parameter_grib1_cdm::Parameter_grib1_cdm()
{
  try
  {
    mParameterNumber = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





Parameter_grib1_cdm::Parameter_grib1_cdm(const Parameter_grib1_cdm& parameter)
{
  try
  {
    mParameterNumber = parameter.mParameterNumber;
    mParameterName = parameter.mParameterName;
    mParameterDescription = parameter.mParameterDescription;
    mParameterUnits = parameter.mParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





Parameter_grib1_cdm::~Parameter_grib1_cdm()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void Parameter_grib1_cdm::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "Parameter_grib1_cdm\n";
    stream << space(level) << "- mParameterNumber      = " << mParameterNumber << "\n";
    stream << space(level) << "- mParameterName        = " << mParameterName << "\n";
    stream << space(level) << "- mParameterDescription = " << mParameterDescription << "\n";
    stream << space(level) << "- mParameterUnits       = " << mParameterUnits << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}

}
}

