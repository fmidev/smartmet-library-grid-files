// ======================================================================
/*!
 * \brief SmartMet Session information
 */
// ======================================================================

#pragma once

#include <map>
#include <vector>
#include <iostream>


namespace SmartMet
{


class Session
{
  public:

                Session();
    virtual     ~Session();

    void        clearAttributes();
    bool        findAttribute(const char *name);
    bool        findAttribute(const char *prefix,const char *name);
    void        setAttributes(std::string& attributes);
    void        setAttribute(const char *name,double value);
    void        setAttribute(const char *name,int value);
    void        setAttribute(const char *name,uint value);
    void        setAttribute(const char *name,const char *value);
    void        setAttribute(const char *name,std::string& value);
    const char* getAttribute(const char *name);
    double      getDoubleAttribute(const char *name);
    int         getIntAttribute(const char *name);
    uint        getUIntAttribute(const char *name);
    bool        getAttribute(const char *name,std::string& value);
    bool        getAttribute(const char *name,int& value);
    bool        getAttribute(const char *name,uint& value);
    bool        getAttribute(const char *name,double& value);
    void        deleteAttribute(const char *name);
    std::string getUrlParameter();
    void        print(std::ostream& stream,uint level,uint optionFlags);

  protected:

    std::map<std::string,std::string> attributes;
};

}

