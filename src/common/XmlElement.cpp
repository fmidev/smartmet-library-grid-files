#include "XmlElement.h"
#include "GeneralFunctions.h"
#include <macgyver/Exception.h>

namespace SmartMet
{


XmlElement::XmlElement()
{
  try
  {
    parent = nullptr;
    filePosition = 0;
  }
  catch (Fmi::Exception& e)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




XmlElement::XmlElement(const char *data,int size)
{
  try
  {
    parent = nullptr;
    filePosition = 0;
    parseXml(data,size,*this);
  }
  catch (Fmi::Exception& e)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




XmlElement::~XmlElement()
{
  for (auto it=elementList.begin(); it!=elementList.end();++it)
  {
    delete (*it);
  }
}



void XmlElement::print(std::ostream& stream,uint level,uint optionFlags)
{
  try
  {
    stream << space(level) << "BEGIN " << tag << "\n";
    stream << space(level+1) << "FilePosition : " << filePosition << "\n";
    stream << space(level+1) << "Value        : " << value << "\n";
    stream << space(level+1) << "ElementList  : \n";

    for (auto it=elementList.begin(); it!=elementList.end();++it)
      (*it)->print(stream,level+2,0);

    stream << space(level) << "END " << tag << "\n";
  }
  catch (Fmi::Exception& e)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



int XmlElement::getTagNameAndType(const char *data,char *name,ParameterList& parameterList)
{
  try
  {
    // TODO: Add parameter parsing
    // TODO: Identify comment sections

    name[0] = '\0';
    int type = 0;
    int c = 0;
    int startName = -1;
    while (data[c] != '\0')
    {
      if (data[c] == '<')
      {
        c++;
        if (data[c] == '/')
        {
          type = 2;
          startName = c+1;
        }
        else
        if (data[c] == '?')
        {
          type = 4;
          startName = c+1;
        }
        else
        {
          type = 1;
          startName = c;
        }
      }
      if (startName >= 0  &&  (data[c] == '>' || data[c] == ' '))
      {
        int len = c - startName;
        if (data[c-1] == '/')
        {
          type = 3;
          len--;
        }
        strncpy(name,data + startName,len);
        name[len] = '\0';
        return type;
      }
      c++;
    }
    return type;
  }
  catch (Fmi::Exception& e)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void XmlElement::parseXml(const char *data,int size,XmlElement& xmlRoot)
{
  try
  {
    xmlRoot.tag = "xml";
    XmlElement *xe = &xmlRoot;

    int c = 0;
    int tagStart = -1;
    int valueStart = -1;
    char buf[size];

    while (c < size)
    {
      if (data[c] == '<')
      {
        if (valueStart >= 0)
        {
          int len = c - valueStart;
          strncpy(buf,data + valueStart,len);
          buf[len] = '\0';
          xe->value = buf;
          valueStart = -1;
        }
        tagStart = c;
      }

      if (tagStart >= 0  &&  data[c] == '>')
      {
        int len = c - tagStart + 1;
        strncpy(buf,data + tagStart,len);
        buf[len] = '\0';
        char tag[len];
        ParameterList parameterList;
        int type = getTagNameAndType(buf,tag,parameterList);

        if (type == 1)
        {
          XmlElement *e = new XmlElement;
          e->parent = xe;
          e->filePosition = tagStart;
          xe->elementList.push_back(e);
          e->tag = tag;
          e->parameters = parameterList;
          xe = e;
        }

        if (type == 3)
        {
          XmlElement *e = new XmlElement;
          e->parent = xe;
          e->filePosition = tagStart;
          xe->elementList.push_back(e);
          e->tag = tag;
        }

        if (type == 2)
        {
          if (xe->tag != tag)
          {
            printf("XML-ERROR: Wrong end tag (%s:%d), expected (%s:%d)!\n",tag,tagStart,xe->tag.c_str(),xe->filePosition);

            if (xe->parent && xe->parent->tag == tag)
              xe = xe->parent;
          }

          if (xe->parent)
            xe = xe->parent;
        }

        if (data[tagStart+1] != '/'  &&  data[c-1] != '/')
        {
          valueStart = c + 1;
        }

        tagStart = -1;
      }
      c++;
    }
  }
  catch (Fmi::Exception& e)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
