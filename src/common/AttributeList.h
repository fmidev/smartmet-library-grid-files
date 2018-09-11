#pragma once

#include "Exception.h"
#include "Attribute.h"

namespace SmartMet
{
namespace T
{

class AttributeList
{
  public:
                    AttributeList();
                    AttributeList(AttributeList& attributeList);
    virtual         ~AttributeList();

    AttributeList&  operator=(AttributeList& attributeList);

    void            addAttribute(Attribute *attribute);
    void            addAttribute(const char *name,std::string value);
    void            addAttribute(std::string name,std::string value);
    void            clear();
    unsigned int    getLength();
    Attribute*      getAttribute(const char *name);
    Attribute*      getAttributeByIndex(unsigned int index);
    const char*     getAttributeNameByIndex(unsigned int index);
    const char*     getAttributeValue(const char *name);
    const char*     getAttributeValueByIndex(unsigned int index);
    void            print(std::ostream& stream,uint level,uint optionFlags);

 protected:

    std::vector<Attribute_ptr> attributeVector;
};


}
}
