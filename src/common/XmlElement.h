#pragma once

#include <map>
#include <vector>

namespace SmartMet
{


typedef std::map<std::string,std::string> ParameterList;


// This is very simple XML-parser that can be used if there is no need
// for more complex operations. The point is that the xml libraries like
// xerces are quite huge and getting them to work in different environment
// takes usually some time.


class XmlElement
{
  public:

                  XmlElement();
                  XmlElement(const char *data,int size);
    virtual       ~XmlElement();

    static void   parseXml(const char *data,int size,XmlElement& xmlRoot);
    void          print(std::ostream& stream,uint level,uint optionFlags);

    int           filePosition;
    XmlElement    *parent;
    std::string   tag;
    ParameterList parameters;
    std::string   value;

    std::vector<XmlElement*> elementList;

  protected:

    static int    getTagNameAndType(const char *data,char *name,ParameterList& parameterList);
};


}
