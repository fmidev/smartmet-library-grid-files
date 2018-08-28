#include "Grib2ParameterDef.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


Grib2ParameterDef::Grib2ParameterDef()
{
  try
  {
    mDiscipline = 0;
    mParameterCategory = 0;
    mParameterNumber = 0;
    mIs_tigge = false;
    mIs_replicate = false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





Grib2ParameterDef::Grib2ParameterDef(const Grib2ParameterDef& parameter)
{
  try
  {
    mGribParameterId = parameter.mGribParameterId;
    mParameterName = parameter.mParameterName;
    mParameterDescription = parameter.mParameterDescription;
    mParameterUnits = parameter.mParameterUnits;
    mDiscipline = parameter.mDiscipline;
    mCentre = parameter.mCentre;
    mParameterCategory = parameter.mParameterCategory;
    mParameterNumber = parameter.mParameterNumber;
    mTypeOfGeneratingProcess = parameter.mTypeOfGeneratingProcess;
    mConstituentType = parameter.mConstituentType;
    mLengthOfTimeRange = parameter.mLengthOfTimeRange;
    mLocalTablesVersion = parameter.mLocalTablesVersion;
    mAerosolType = parameter.mAerosolType;
    mProbabilityType = parameter.mProbabilityType;
    mProductDefinitionTemplateNumber = parameter.mProductDefinitionTemplateNumber;
    mTypeOfFirstFixedSurface = parameter.mTypeOfFirstFixedSurface;
    mTypeOfSecondFixedSurface = parameter.mTypeOfSecondFixedSurface;
    mTypeOfStatisticalProcessing = parameter.mTypeOfStatisticalProcessing;
    mScaledValueOfLowerLimit = parameter.mScaledValueOfLowerLimit;
    mScaledValueOfFirstFixedSurface = parameter.mScaledValueOfFirstFixedSurface;
    mScaledValueOfSecondFixedSurface = parameter.mScaledValueOfSecondFixedSurface;
    mScaleFactorOfLowerLimit = parameter.mScaleFactorOfLowerLimit;
    mScaleFactorOfFirstFixedSurface = parameter.mScaleFactorOfFirstFixedSurface;
    mScaleFactorOfSecondFixedSurface = parameter.mScaleFactorOfSecondFixedSurface;
    mIs_tigge = parameter.mIs_tigge;
    mIs_replicate = parameter.mIs_replicate;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





Grib2ParameterDef::~Grib2ParameterDef()
{
  try
  {
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
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
    stream << space(level) << "- mGribParameterId                 = " << mGribParameterId << "\n";
    stream << space(level) << "- mParameterName                   = " << mParameterName << "\n";
    stream << space(level) << "- mParameterDescription            = " << mParameterDescription << "\n";
    stream << space(level) << "- mParameterUnits                  = " << mParameterUnits << "\n";
    stream << space(level) << "- mDiscipline                      = " << toString(mDiscipline) << "\n";
    stream << space(level) << "- mCentre                          = " << toString(mCentre) << "\n";
    stream << space(level) << "- mParameterCategory               = " << toString(mParameterCategory) << "\n";
    stream << space(level) << "- mParameterNumber                 = " << toString(mParameterNumber) << "\n";
    stream << space(level) << "- mTypeOfGeneratingProcess         = " << toString(mTypeOfGeneratingProcess) << "\n";
    stream << space(level) << "- mConstituentType                 = " << toString(mConstituentType) << "\n";
    stream << space(level) << "- mLengthOfTimeRange               = " << toString(mLengthOfTimeRange) << "\n";
    stream << space(level) << "- mLocalTablesVersion              = " << toString(mLocalTablesVersion) << "\n";
    stream << space(level) << "- mAerosolType                     = " << toString(mAerosolType) << "\n";
    stream << space(level) << "- mProbabilityType                 = " << toString(mProbabilityType) << "\n";
    stream << space(level) << "- mProductDefinitionTemplateNumber = " << toString(mProductDefinitionTemplateNumber) << "\n";
    stream << space(level) << "- mTypeOfFirstFixedSurface         = " << toString(mTypeOfFirstFixedSurface) << "\n";
    stream << space(level) << "- mTypeOfSecondFixedSurface        = " << toString(mTypeOfSecondFixedSurface) << "\n";
    stream << space(level) << "- mTypeOfStatisticalProcessing     = " << toString(mTypeOfStatisticalProcessing) << "\n";
    stream << space(level) << "- mScaledValueOfLowerLimit         = " << toString(mScaledValueOfLowerLimit) << "\n";
    stream << space(level) << "- mScaledValueOfFirstFixedSurface  = " << toString(mScaledValueOfFirstFixedSurface) << "\n";
    stream << space(level) << "- mScaledValueOfSecondFixedSurface = " << toString(mScaledValueOfSecondFixedSurface) << "\n";
    stream << space(level) << "- mScaleFactorOfLowerLimit         = " << toString(mScaleFactorOfLowerLimit) << "\n";
    stream << space(level) << "- mScaleFactorOfFirstFixedSurface  = " << toString(mScaleFactorOfFirstFixedSurface) << "\n";
    stream << space(level) << "- mScaleFactorOfSecondFixedSurface = " << toString(mScaleFactorOfSecondFixedSurface) << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}

}  // namespace GRIB2
}  // namespace SmartMet
