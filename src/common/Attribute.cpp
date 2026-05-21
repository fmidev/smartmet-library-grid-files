#include "Attribute.h"
#include "GeneralFunctions.h"
#include <macgyver/Hash.h>
#include <macgyver/Exception.h>



namespace SmartMet
{
namespace T
{



/*! \brief Default constructor for Attribute. */

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




/*! \brief Copy constructor for Attribute. */

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




/*! \brief Constructs an Attribute with the given name and value. */

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





/*! \brief Destructor for Attribute. */

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




/*! \brief Assignment operator for Attribute. */

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




/*! \brief Returns a hash value computed from the attribute name and value. */

std::size_t Attribute::getHash()
{
  try
  {
    std::size_t hash = 0;
    Fmi::hash_merge(hash,mName);
    Fmi::hash_merge(hash,mValue);

    return hash;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Returns a heap-allocated copy of this attribute. */

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





/*! \brief Prints the attribute contents to the given stream. */

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
