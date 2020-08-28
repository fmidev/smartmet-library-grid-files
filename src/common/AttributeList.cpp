#include "AttributeList.h"
#include "Exception.h"
#include "GeneralFunctions.h"
#include <boost/functional/hash.hpp>


namespace SmartMet
{
namespace T
{


AttributeList::AttributeList()
{
  try
  {
    mCaseSensitive = true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





AttributeList::AttributeList(const AttributeList& attributeList)
{
  try
  {
    uint size = attributeList.getLength();
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = attributeList.getAttributeByIndex(t);
      mAttributeVector.push_back(attr->duplicate());
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





AttributeList::~AttributeList()
{
  try
  {
    uint size = getLength();
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = mAttributeVector.at(t);
      delete attr;
    }
    mAttributeVector.clear();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





AttributeList& AttributeList::operator=(const AttributeList& attributeList)
{
  try
  {
    if (&attributeList == this)
      return *this;

    clear();

    uint size = attributeList.getLength();
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = attributeList.getAttributeByIndex(t);
      mAttributeVector.push_back(attr->duplicate());
    }
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




void  AttributeList::addAttribute(Attribute *attribute)
{
  try
  {
    mAttributeVector.push_back(attribute);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void AttributeList::setAttribute(const char *name,std::string value)
{
  try
  {
    uint size = getLength();
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = mAttributeVector.at(t);
      if ((mCaseSensitive  &&  attr->mName == name) || (!mCaseSensitive  &&  strcasecmp(attr->mName.c_str(),name) == 0))
      {
        attr->mValue = value;
        return;
      }
    }

    addAttribute(new Attribute(std::string(name),value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void AttributeList::setAttribute(std::string name,std::string value)
{
  try
  {
    uint size = getLength();
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = mAttributeVector.at(t);
      if ((mCaseSensitive  &&  attr->mName == name) || (!mCaseSensitive  &&  strcasecmp(attr->mName.c_str(),name.c_str()) == 0))
      {
        attr->mValue = value;
        return;
      }
    }

    addAttribute(new Attribute(std::string(name),value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void AttributeList::setCaseSensitive(bool caseSensitive)
{
  try
  {
    mCaseSensitive = caseSensitive;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void AttributeList::clear()
{
  try
  {
    uint size = getLength();
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = mAttributeVector.at(t);
      delete attr;
    }
    mAttributeVector.clear();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





unsigned int AttributeList::getLength() const
{
  try
  {
    return (unsigned int)mAttributeVector.size();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





Attribute* AttributeList::getAttribute(const char *name) const
{
  try
  {
    uint size = getLength();
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = mAttributeVector.at(t);
      if ((mCaseSensitive  &&  attr->mName == name) || (!mCaseSensitive  &&  strcasecmp(attr->mName.c_str(),name) == 0))
        return attr;
    }
    return nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





Attribute* AttributeList::getAttributeByNameEnd(const char *nameEnd) const
{
  try
  {
    uint alen = strlen(nameEnd);
    uint size = getLength();
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = mAttributeVector.at(t);
      if (mCaseSensitive)
      {
        const char *p = strstr(attr->mName.c_str(),nameEnd);
        if (p != nullptr  &&  p[alen] == '\0')
          return attr;
      }
      else
      {
        const char *p = strcasestr(attr->mName.c_str(),nameEnd);
        if (p != nullptr  &&  p[alen] == '\0')
          return attr;
      }
    }
    return nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





size_t AttributeList::getAttributeValues(const char *name,std::vector<std::string>& values) const
{
  try
  {
    uint size = getLength();
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = mAttributeVector.at(t);
      if ((mCaseSensitive  &&  attr->mName == name) || (!mCaseSensitive  &&  strcasecmp(attr->mName.c_str(),name) == 0))
        values.push_back(attr->mValue);
    }
    return values.size();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





Attribute* AttributeList::getAttributeByIndex(unsigned int index) const
{
  try
  {
    if (index < getLength())
    {
      Attribute *attr = mAttributeVector.at(index);
      return attr;
    }

    return nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




const char* AttributeList::getAttributeNameByIndex(unsigned int index) const
{
  try
  {
    if (index < getLength())
    {
      Attribute *attr = mAttributeVector.at(index);
      return attr->mName.c_str();
    }

    return nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





const char* AttributeList::getAttributeValue(const char *name) const
{
  try
  {
    uint size = getLength();
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = mAttributeVector.at(t);
      if ((mCaseSensitive  &&  attr->mName == name) || (!mCaseSensitive  &&  strcasecmp(attr->mName.c_str(),name) == 0))
        return attr->mValue.c_str();
    }
    return nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





const char* AttributeList::getAttributeValueByIndex(unsigned int index) const
{
  try
  {
    if (index < getLength())
    {
      Attribute *attr = mAttributeVector.at(index);
      return attr->mValue.c_str();
    }

    return nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::size_t AttributeList::getHash()
{
  try
  {
    std::size_t hash = 0;
    for (auto it = mAttributeVector.begin(); it != mAttributeVector.end(); ++it)
      boost::hash_combine(hash,(*it)->getHash());

    return hash;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void AttributeList::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    uint size = getLength();
    stream << space(level) << "AttributeList\n";
    for (uint t=0; t<size; t++)
    {
      Attribute *attr = mAttributeVector.at(t);
      stream << space(level) << "- " << attr->mName << " = " << attr->mValue << "\n";
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}
}
