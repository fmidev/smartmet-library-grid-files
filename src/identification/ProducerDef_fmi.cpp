#include "ProducerDef_fmi.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


ProducerDef_fmi::ProducerDef_fmi()
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





ProducerDef_fmi::ProducerDef_fmi(const ProducerDef_fmi& producer)
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





ProducerDef_fmi::~ProducerDef_fmi()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void ProducerDef_fmi::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "ProducerDef_fmi\n";
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

