#include "Attribute.h"
#include "GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <macgyver/Exception.h>



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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




Attribute::Attribute(const std::string& name,const std::string& value)
{
  try
  {
    mName = name;
    mValue = value;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





Attribute::~Attribute()
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




std::size_t Attribute::getHash()
{
  try
  {
    std::size_t hash = 0;
    boost::hash_combine(hash,mName);
    boost::hash_combine(hash,mValue);

    return hash;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




}
}
