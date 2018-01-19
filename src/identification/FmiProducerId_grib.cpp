#include "FmiProducerId_grib.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"


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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





FmiProducerId_grib::FmiProducerId_grib(const FmiProducerId_grib& producer)
{
  try
  {
    mProducerId = producer.mProducerId;
    mType = producer.mType;
    mCentre = producer.mCentre;
    mIdent = producer.mIdent;
    mProducerName = producer.mProducerName;
    mProducerDescription = producer.mProducerDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





FmiProducerId_grib::~FmiProducerId_grib()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}

}
}

