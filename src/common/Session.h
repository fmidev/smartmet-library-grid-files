// ======================================================================
/*! \brief SmartMet client session: a typed key/value attribute store.
 *
 *  Holds per-request or per-session parameters (coordinates, output format
 *  flags, authentication tokens, …) that plugins pass between layers without
 *  hardcoded function arguments. */
// ======================================================================

#pragma once

#include <map>
#include <vector>
#include <iostream>

#include "Typedefs.h"


namespace SmartMet
{


class Session
{
  public:

                Session();
    virtual     ~Session();

    /*! \brief Remove all stored attributes. */
    void        clearAttributes();

    /*! \brief Return true if an attribute with the given name exists.
     *  \param[in] name  Attribute name to look up. */
    bool        findAttribute(const char *name);

    /*! \brief Return true if an attribute matching prefix+name exists.
     *  \param[in] prefix  Name prefix.
     *  \param[in] name    Attribute name (appended to prefix). */
    bool        findAttribute(const char *prefix,const char *name);

    /*! \brief Parse a URL-encoded attribute string and store all key=value pairs.
     *  \param[in] attributes  URL-encoded parameter string. */
    void        setAttributes(std::string& attributes);

    /** @name Typed attribute setters
     *  Store a value under the given name (converts to string internally). @{ */
    void        setAttribute(const char *name,double value);
    void        setAttribute(const char *name,int value);
    void        setAttribute(const char *name,uint value);
    void        setAttribute(const char *name,Int64 value);
    void        setAttribute(const char *name,UInt64 value);
    void        setAttribute(const char *name,const char *value);
    void        setAttribute(const char *name,std::string& value);
    /** @} */

    /*! \brief Return the raw string value for \p name, or nullptr if not found.
     *  \param[in] name  Attribute name. */
    const char* getAttribute(const char *name);

    /** @name Typed attribute getters (return value directly)
     *  Return a default (0 / 0.0) when the attribute is absent or not convertible. @{ */
    double      getDoubleAttribute(const char *name);
    int         getIntAttribute(const char *name);
    uint        getUIntAttribute(const char *name);
    Int64       getInt64Attribute(const char *name);
    UInt64      getUInt64Attribute(const char *name);
    /** @} */

    /** @name Typed attribute getters (output parameter form)
     *  Return true and populate \p value if the attribute exists and converts. @{ */
    bool        getAttribute(const char *name,std::string& value);
    bool        getAttribute(const char *name,int& value);
    bool        getAttribute(const char *name,uint& value);
    bool        getAttribute(const char *name,Int64& value);
    bool        getAttribute(const char *name,UInt64& value);
    bool        getAttribute(const char *name,double& value);
    /** @} */

    /*! \brief Remove a single attribute by name.
     *  \param[in] name  Attribute to remove. */
    void        deleteAttribute(const char *name);

    /*! \brief Return all attributes formatted as a URL-encoded parameter string. */
    std::string getUrlParameter();

    /*! \brief Print all attributes to a stream.
     *  \param[in] stream      Output stream.
     *  \param[in] level       Indentation level.
     *  \param[in] optionFlags PrintFlag bit mask. */
    void        print(std::ostream& stream,uint level,uint optionFlags);

  protected:

    std::map<std::string,std::string> attributes; //!< Key/value store (all values as strings)
};

}

