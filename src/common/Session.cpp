// ======================================================================
/*!
 * \brief SmartMet Grid Gui plugin implementation
 */
// ======================================================================

#include "Session.h"

#include "GeneralFunctions.h"
#include "ShowFunction.h"
#include <spine/SmartMet.h>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{

static const char *emptyStr = "\0";



Session::Session()
{
}



Session::~Session()
{
}



void Session::clearAttributes()
{
  try
  {
    attributes.clear();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void Session::setAttributes(std::string& attributes)
{
  try
  {
    std::vector<std::string> list;
    splitString(attributes,';',list);
    for (auto it=list.begin(); it != list.end(); it++)
    {
      std::vector<std::string> attr;
      splitString(it->c_str(),'=',attr);
      if (attr.size() == 1)
      {
        setAttribute(attr[0].c_str(),"");
      }
      else
      if (attr.size() == 2)
      {
        setAttribute(attr[0].c_str(),attr[1].c_str());
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void Session::setAttribute(const char *name,double value)
{
  try
  {
    // printf("SETATTR [%s][%f]\n",name,value);
    auto attr = attributes.find(name);
    if (attr != attributes.end())
    {
      attr->second = std::to_string(value);
      return;
    }
    attributes.insert(std::pair<std::string,std::string>(std::string(name),std::to_string(value)));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void Session::setAttribute(const char *name,int value)
{
  try
  {
    // printf("SETATTR [%s][%d]\n",name,value);
    auto attr = attributes.find(name);
    if (attr != attributes.end())
    {
      attr->second = std::to_string(value);
      return;
    }
    attributes.insert(std::pair<std::string,std::string>(std::string(name),std::to_string(value)));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void Session::setAttribute(const char *name,uint value)
{
  try
  {
    // printf("SETATTR [%s][%u]\n",name,value);
    auto attr = attributes.find(name);
    if (attr != attributes.end())
    {
      attr->second = std::to_string(value);
      return;
    }
    attributes.insert(std::pair<std::string,std::string>(std::string(name),std::to_string(value)));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void Session::setAttribute(const char *name,std::string& value)
{
  try
  {
    // printf("SETATTR [%s][%s]\n",name,value.c_str();
    auto attr = attributes.find(name);
    if (attr != attributes.end())
    {
      attr->second = value;
      return;
    }
    attributes.insert(std::pair<std::string,std::string>(std::string(name),std::string(value)));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void Session::setAttribute(const char *name,const char *value)
{
  try
  {
    // printf("SETATTR [%s][%s]\n",name,value);
    auto attr = attributes.find(name);
    if (attr != attributes.end())
    {
      attr->second = value;
      return;
    }
    attributes.insert(std::pair<std::string,std::string>(std::string(name),std::string(value)));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



const char* Session::getAttribute(const char *name)
{
  try
  {
    auto attr = attributes.find(name);
    if (attr != attributes.end())
      return attr->second.c_str();

    return emptyStr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



bool Session::getAttribute(const char *name,std::string& value)
{
  try
  {
    auto attr = attributes.find(name);
    if (attr != attributes.end())
    {
      value = attr->second;
      return true;
    }
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



bool Session::findAttribute(const char *name)
{
  try
  {
    auto attr = attributes.find(name);
    if (attr != attributes.end())
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




bool Session::findAttribute(const char *prefix,const char *name)
{
  try
  {
    char newName[200];
    sprintf(newName,"%s%s",prefix,name);
    auto attr = attributes.find(newName);
    if (attr != attributes.end())
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




int Session::getIntAttribute(const char *name)
{
  try
  {
    auto attr = attributes.find(name);
    if (attr != attributes.end())
      return toInt32(attr->second);

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



uint Session::getUIntAttribute(const char *name)
{
  try
  {
    auto attr = attributes.find(name);
    if (attr != attributes.end())
      return toUInt32(attr->second);

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



double Session::getDoubleAttribute(const char *name)
{
  try
  {
    auto attr = attributes.find(name);
    if (attr != attributes.end())
      return toDouble(attr->second);

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



bool Session::getAttribute(const char *name,int& value)
{
  try
  {
    auto attr = attributes.find(name);
    if (attr != attributes.end())
    {
      value = toInt32(attr->second);
      return true;
    }
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



bool Session::getAttribute(const char *name,uint& value)
{
  try
  {
    auto attr = attributes.find(name);
    if (attr != attributes.end())
    {
      value = toUInt32(attr->second);
      return true;
    }
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



bool Session::getAttribute(const char *name,double& value)
{
  try
  {
    auto attr = attributes.find(name);
    if (attr != attributes.end())
    {
      value = toDouble(attr->second);
      return true;
    }
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void Session::deleteAttribute(const char *name)
{
  try
  {
    auto attr = attributes.find(name);
    if (attr != attributes.end())
      attributes.erase(attr);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



std::string Session::getUrlParameter()
{
  try
  {
    std::ostringstream output;
    for (auto it = attributes.begin(); it != attributes.end(); ++it)
    {
      if (it->first.substr(0,1) != "#")
        output << it->first << "=" << it->second << ";";
    }
    return output.str();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void Session::print(std::ostream& stream,uint level,uint optionFlags)
{
  try
  {
    stream << "SESSION:\n";
    for (auto it = attributes.begin(); it != attributes.end(); ++it)
    {
      stream << "  - " << it->first << "=" << it->second << "\n";
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}



