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
                    AttributeList(const AttributeList& attributeList);
    virtual         ~AttributeList();

    AttributeList&  operator=(const AttributeList& attributeList);

    void            addAttribute(Attribute *attribute);
    void            addAttribute(const char *name,std::string value);
    void            addAttribute(std::string name,std::string value);
    void            setAttribute(const char *name,std::string value);
    void            setAttribute(std::string name,std::string value);
    void            setCaseSensitive(bool caseSensitive);
    void            clear();
    unsigned int    getLength() const;
    Attribute*      getAttribute(const char *name) const;
    Attribute*      getAttributeByIndex(unsigned int index) const;
    const char*     getAttributeNameByIndex(unsigned int index) const;
    const char*     getAttributeValue(const char *name) const;
    size_t          getAttributeValues(const char *name,std::vector<std::string>& values) const;
    const char*     getAttributeValueByIndex(unsigned int index) const;
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

 protected:

    std::vector<Attribute_ptr>  mAttributeVector;
    bool                        mCaseSensitive;
};


}
}
