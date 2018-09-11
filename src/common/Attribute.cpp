#include "Attribute.h"
#include "Exception.h"
#include "GeneralFunctions.h"



namespace SmartMet
{
namespace T
{



Attribute::Attribute()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




Attribute::Attribute(const Attribute& attribute)
{
  try
  {
    mName = attribute.mName;
    mValue = attribute.mValue;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




Attribute::Attribute(std::string name,std::string value)
{
  try
  {
    mName = name;
    mValue = value;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





Attribute::~Attribute()
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




Attribute& Attribute::operator=(const Attribute& attribute)
{
  try
  {
    if (&attribute == this)
      return *this;

    mName = attribute.mName;
    mValue = attribute.mValue;

    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




Attribute* Attribute::duplicate()
{
  try
  {
    return new Attribute(*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Attribute::print(std::ostream& stream,uint level,uint optionFlags)
{
  try
  {
    stream << space(level) << "Attribute\n";
    stream << space(level) << "- mName  = " << mName << "\n";
    stream << space(level) << "- mValue = " << mValue << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




}
}
