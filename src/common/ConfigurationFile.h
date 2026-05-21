#pragma once

#include "Attribute.h"
#include "Typedefs.h"

#include <macgyver/Exception.h>
#include <set>


namespace SmartMet
{


// ====================================================================================
/*! \brief Parser for the SmartMet libconfig-style configuration files.
 *
 *  Reads `.conf` files with `key = value;` syntax, supporting `@include`,
 *  `@ifdef` directives, and `$(VAR)` environment variable expansion.  Loaded
 *  attributes are stored as flat `key.sub.sub = value` strings and queried by
 *  typed `getAttributeValue()` overloads. */
// ====================================================================================

class ConfigurationFile
{
  public:
    /*! \brief Construct an empty configuration. */
                  ConfigurationFile();
                  //ConfigurationFile(const ConfigurationFile& configurationFile);

    /*! \brief Construct and immediately read a configuration file.
     *  \param[in] filename  Path to the configuration file. */
                  ConfigurationFile(const std::string& filename);
    virtual       ~ConfigurationFile();

    /*! \brief Remove all loaded attributes. */
    void          clear();

    /*! \brief Parse and load a configuration file, replacing current attributes.
     *  \param[in] filename  Path to the configuration file. */
    void          readFile(const std::string& filename);

    /*! \brief Load and merge an additional configuration file.
     *  \param[in] filename  Path to the file to merge in. */
    void          addConfigurationFile(const std::string& filename);

    /** @name Typed attribute getters
     *  Look up \p attributeName (dot-separated path) and convert its value.
     *  \param[in]  attributeName   Dot-separated attribute path.
     *  \param[out] attributeValue  Receives the converted value.
     *  \return True if the attribute was found and successfully converted. @{ */
    bool          getAttributeValue(const char *attributeName,bool& attributeValue);
    bool          getAttributeValue(const char *attributeName,float& attributeValue);
    bool          getAttributeValue(const char *attributeName,double& attributeValue);
    bool          getAttributeValue(const char *attributeName,char& attributeValue);
    bool          getAttributeValue(const char *attributeName,short& attributeValue);
    bool          getAttributeValue(const char *attributeName,int& attributeValue);
    bool          getAttributeValue(const char *attributeName,Int64& attributeValue);
    bool          getAttributeValue(const char *attributeName,unsigned char& attributeValue);
    bool          getAttributeValue(const char *attributeName,unsigned short& attributeValue);
    bool          getAttributeValue(const char *attributeName,unsigned int& attributeValue);
    bool          getAttributeValue(const char *attributeName,UInt64& attributeValue);
    bool          getAttributeValue(const char *attributeName,std::string& attributeValue);
    bool          getAttributeValue(const char *attributeName,std::vector<std::string>& attributeValueVec);
    /** @} */

    /*! \brief Return the distinct sub-keys of an array or group attribute.
     *  \param[in]  attributeName    Dot-separated path prefix.
     *  \param[out] attributeFields  Receives the sub-key names.
     *  \return True if at least one sub-key was found. */
    bool          getAttributeFields(const char *attributeName,std::set<std::string>& attributeFields);

    /*! \brief Return the names of all immediate children of a group attribute.
     *  \param[in]  attributeName   Parent path.
     *  \param[out] attributeNames  Receives child names.
     *  \return True if children were found. */
    bool          getSubAttributes(const char *attributeName,std::vector<std::string>& attributeNames);

    /*! \brief Return the path of the primary configuration file. */
    std::string   getFilename();

    /*! \brief Return the number of elements in an array attribute.
     *  \param[in] attributeName  Array path.
     *  \return Element count, or 0 if not found. */
    uint          getArraySize(const char *attributeName);

    /*! \brief Set or overwrite an attribute value at runtime.
     *  \param[in] attributeName   Dot-separated attribute path.
     *  \param[in] attributeValue  New value string. */
    void          setAttributeValue(const char *attributeName,std::string& attributeValue);

    /*! \brief Check whether an attribute exists without retrieving its value.
     *  \param[in] attributeName  Attribute path to test.
     *  \return True if the attribute exists. */
    bool          findAttribute(const char *attributeName);

    /*! \brief Remove all attributes whose names match \p pattern.
     *  \param[in] pattern  Glob pattern to match attribute names. */
    void          removeAttributes(const char *pattern);

    /*! \brief Expand attribute references in \p inputFilename and write to \p outputFilename.
     *  \param[in] inputFilename   Template file with `$(ATTR)` references.
     *  \param[in] outputFilename  Output path. */
    void          replaceAttributeNamesWithValues(const std::string& inputFilename,const std::string& outputFilename);

    /*! \brief Print all attributes to a stream.
     *  \param[in] stream      Output stream.
     *  \param[in] level       Indentation level.
     *  \param[in] optionFlags PrintFlag bit mask. */
    void          print(std::ostream& stream,uint level,uint optionFlags);

  protected:

    std::string   parseValue(const std::string& value);
    std::string   parseConstValue(const std::string& value);

    void          removeComments(char *st,UInt64 *positions,char *newst,UInt64 *newpositions,int len);
    void          setPositions(char *st,UInt64 *positions,int len);
    void          getWords(char *st,UInt64 *positions,std::vector<std::string>& words,std::vector<UInt64>& wordPositions);
    int           readValue(std::vector<std::string>& words,std::vector<UInt64>& wordPositions,int len,int pos,const std::string& path);
    int           readAttribute(std::vector<std::string>& words,std::vector<UInt64>& wordPositions,int len,int pos,const std::string& path,int index);

  public:

    std::vector<T::Attribute>  mAttributeList;         //!< Flat list of all loaded attributes
    std::string                mFilename;               //!< Primary configuration file path
    std::string                mCurrentFilename;        //!< File currently being parsed (for error messages)

  private:
    std::set<std::string>      mIncludedConfigurationFiles; //!< Tracks included files to prevent cycles
};


}

