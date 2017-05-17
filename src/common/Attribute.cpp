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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




Attribute::Attribute(Attribute& attribute)
{
  try
  {
    mName = attribute.mName;
    mValue = attribute.mValue;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





Attribute::~Attribute()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




void Attribute::operator=(Attribute& attribute)
{
  try
  {
    if (&attribute == this)
      return;

    mName = attribute.mName;
    mValue = attribute.mValue;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




}
}
