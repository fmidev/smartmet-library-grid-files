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
                    Attribute(Attribute& attribute);
                    Attribute(std::string name,std::string value);
     virtual        ~Attribute();

     void           operator=(Attribute& attribute);
     Attribute*     duplicate();
     void           print(std::ostream& stream,uint level,uint optionFlags);

     std::string    mName;
     std::string    mValue;
};


typedef Attribute* Attribute_ptr;


}
}
