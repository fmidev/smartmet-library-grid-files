#include "AttributeNode.h"
#include "GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <macgyver/Exception.h>



namespace SmartMet
{
namespace T
{



AttributeNode::AttributeNode()
{
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




AttributeNode::AttributeNode(const AttributeNode& attributeNode)
{
  try
  {
    mName = attributeNode.mName;
    mValue = attributeNode.mValue;
    mSubAttributes = attributeNode.mSubAttributes;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




AttributeNode::AttributeNode(const char *name,std::string value)
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





AttributeNode::AttributeNode(const char *name,const char *value)
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





AttributeNode::AttributeNode(const char *name)
{
  try
  {
    mName = name;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::shared_ptr<AttributeNode> AttributeNode::addAttribute(const char *name,const char *value)
{
  try
  {
    std::shared_ptr<AttributeNode> rec(new AttributeNode(name,value));
    mSubAttributes.push_back(rec);
    return rec;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::shared_ptr<AttributeNode> AttributeNode::addAttribute(const char *name,std::string value)
{
  try
  {
    std::shared_ptr<AttributeNode> rec(new AttributeNode(name,value));
    mSubAttributes.push_back(rec);
    return rec;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::shared_ptr<AttributeNode> AttributeNode::addAttribute(const char *name,int value)
{
  try
  {
    char val[20];
    sprintf(val,"%d",value);
    std::shared_ptr<AttributeNode> rec(new AttributeNode(name,val));
    mSubAttributes.push_back(rec);
    return rec;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::shared_ptr<AttributeNode> AttributeNode::addAttribute(const char *name)
{
  try
  {
    std::shared_ptr<AttributeNode> rec(new AttributeNode(name));
    mSubAttributes.push_back(rec);
    return rec;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





AttributeNode::~AttributeNode()
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




void AttributeNode::print(std::ostream& stream,uint level,uint optionFlags)
{
  try
  {
    if (mSubAttributes.size() > 0)
    {
      stream << space(level) << "* " << mName << " :\n";
      for (auto it = mSubAttributes.begin(); it != mSubAttributes.end(); ++it)
      {
        (*it)->print(stream,level+1,optionFlags);
      }
    }
    else
    {
      stream << space(level) << "- " << mName << " : " << mValue << "\n";
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




}
}
