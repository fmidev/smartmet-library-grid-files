#include "AttributeList.h"
#include "Exception.h"
#include "GeneralFunctions.h"


namespace SmartMet
{
namespace T
{


AttributeList::AttributeList()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




AttributeList::AttributeList(AttributeList& attributeList)
{
  try
  {
    uint size = attributeList.getLength();
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = attributeList.getAttributeByIndex(t);
      attributeVector.push_back(attr->duplicate());
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





AttributeList::~AttributeList()
{
  try
  {
    clear();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





void AttributeList::operator=(AttributeList& attributeList)
{
  try
  {
    if (&attributeList == this)
      return;

    clear();

    uint size = attributeList.getLength();
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = attributeList.getAttributeByIndex(t);
      attributeVector.push_back(attr->duplicate());
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




void  AttributeList::addAttribute(Attribute *attribute)
{
  try
  {
    attributeVector.push_back(attribute);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




void AttributeList::addAttribute(const char *name,std::string value)
{
  try
  {
    addAttribute(new Attribute(std::string(name),value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





void AttributeList::addAttribute(std::string name,std::string value)
{
  try
  {
    addAttribute(new Attribute(name,value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





void AttributeList::clear()
{
  try
  {
    uint size = getLength();
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = attributeVector.at(t);
      delete attr;
    }
    attributeVector.clear();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




unsigned int AttributeList::getLength()
{
  try
  {
    return (unsigned int)attributeVector.size();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





Attribute* AttributeList::getAttribute(const char *name)
{
  try
  {
    uint size = getLength();
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = attributeVector.at(t);
      if (attr->mName == name)
        return attr;
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




Attribute* AttributeList::getAttributeByIndex(unsigned int index)
{
  try
  {
    if (index < getLength())
    {
      Attribute *attr = attributeVector.at(index);
      return attr;
    }

    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




const char* AttributeList::getAttributeNameByIndex(unsigned int index)
{
  try
  {
    if (index < getLength())
    {
      Attribute *attr = attributeVector.at(index);
      return attr->mName.c_str();
    }

    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





const char* AttributeList::getAttributeValue(const char *name)
{
  try
  {
    uint size = getLength();
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = attributeVector.at(t);
      if (attr->mName == name)
        return attr->mValue.c_str();
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





const char* AttributeList::getAttributeValueByIndex(unsigned int index)
{
  try
  {
    if (index < getLength())
    {
      Attribute *attr = attributeVector.at(index);
      return attr->mValue.c_str();
    }

    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





void AttributeList::print(std::ostream& stream,uint level,uint optionFlags)
{
  try
  {
    uint size = getLength();
    stream << space(level) << "AttributeList\n";
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = attributeVector.at(t);
      stream << space(level) << "- " << attr->mName << " = " << attr->mValue << "\n";
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}


}
}
