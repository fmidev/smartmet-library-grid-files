#pragma once

#include <memory>
#include <string>
#include <vector>



namespace SmartMet
{
namespace T
{



class AttributeNode
{
  public:
                    AttributeNode();
                    AttributeNode(const AttributeNode& attributeNode);
                    AttributeNode(const char *name,std::string value);
                    AttributeNode(const char *name,const char *value);
                    AttributeNode(const char *name);
     virtual        ~AttributeNode();

     std::shared_ptr<AttributeNode> addAttribute(const char *name);
     std::shared_ptr<AttributeNode> addAttribute(const char *name,std::string value);
     std::shared_ptr<AttributeNode> addAttribute(const char *name,const char *value);
     std::shared_ptr<AttributeNode> addAttribute(const char *name,int value);

     void           print(std::ostream& stream,uint level,uint optionFlags);

     std::string    mName;
     std::string    mValue;

     std::vector<std::shared_ptr<AttributeNode>> mSubAttributes;
};



}
}
