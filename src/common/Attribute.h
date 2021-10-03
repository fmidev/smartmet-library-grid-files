#pragma once

#include <string>



namespace SmartMet
{
namespace T
{



class Attribute
{
  public:
                    Attribute();
                    Attribute(const Attribute& attribute);
                    Attribute(const std::string& name,const std::string& value);
     virtual        ~Attribute();

     std::size_t    getHash();
     Attribute&     operator=(const Attribute& attribute);
     Attribute*     duplicate();
     void           print(std::ostream& stream,uint level,uint optionFlags);

     std::string    mName;
     std::string    mValue;
};


using Attribute_ptr = Attribute *;


}
}
