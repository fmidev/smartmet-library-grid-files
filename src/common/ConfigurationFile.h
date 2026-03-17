#pragma once

#include "Attribute.h"
#include "Typedefs.h"

#include <macgyver/Exception.h>
#include <set>


namespace SmartMet
{


class ConfigurationFile
{
  public:
                  ConfigurationFile();
                  //ConfigurationFile(const ConfigurationFile& configurationFile);
                  ConfigurationFile(const std::string& filename);
    virtual       ~ConfigurationFile();

    void          clear();
    void          readFile(const std::string& filename);

    void          addConfigurationFile(const std::string& filename);

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

    bool          getAttributeFields(const char *attributeName,std::set<std::string>& attributeFields);
    bool          getSubAttributes(const char *attributeName,std::vector<std::string>& attributeNames);
    std::string   getFilename();
    uint          getArraySize(const char *attributeName);

    void          setAttributeValue(const char *attributeName,std::string& attributeValue);

    bool          findAttribute(const char *attributeName);
    void          removeAttributes(const char *pattern);
    void          replaceAttributeNamesWithValues(const std::string& inputFilename,const std::string& outputFilename);

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

    std::vector<T::Attribute>  mAttributeList;
    std::string                mFilename;
    std::string                mCurrentFilename;

  private:
    std::set<std::string>      mIncludedConfigurationFiles;
};


}

