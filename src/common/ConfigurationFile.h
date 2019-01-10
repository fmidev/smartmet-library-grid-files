#pragma once

#include "Exception.h"
#include "Attribute.h"

#include <set>


namespace SmartMet
{


class ConfigurationFile
{
  public:
                  ConfigurationFile();
                  ConfigurationFile(const ConfigurationFile& configurationFile);
                  ConfigurationFile(std::string filename);
    virtual       ~ConfigurationFile();

    void          clear();
    void          readFile(std::string filename);

    void          addConfigurationFile(std::string filename);

    bool          getAttributeValue(const char *attributeName,bool& attributeValue);
    bool          getAttributeValue(const char *attributeName,float& attributeValue);
    bool          getAttributeValue(const char *attributeName,double& attributeValue);
    bool          getAttributeValue(const char *attributeName,char& attributeValue);
    bool          getAttributeValue(const char *attributeName,short& attributeValue);
    bool          getAttributeValue(const char *attributeName,int& attributeValue);
    bool          getAttributeValue(const char *attributeName,long& attributeValue);
    bool          getAttributeValue(const char *attributeName,long long& attributeValue);
    bool          getAttributeValue(const char *attributeName,unsigned char& attributeValue);
    bool          getAttributeValue(const char *attributeName,unsigned short& attributeValue);
    bool          getAttributeValue(const char *attributeName,unsigned int& attributeValue);
    bool          getAttributeValue(const char *attributeName,unsigned long& attributeValue);
    bool          getAttributeValue(const char *attributeName,unsigned long long& attributeValue);

    bool          getAttributeValue(const char *attributeName,std::string& attributeValue);
    bool          getAttributeValue(const char *attributeName,std::vector<std::string>& attributeValueVec);

    bool          getAttributeFields(const char *attributeName,std::set<std::string>& attributeFields);
    std::string   getFilename();

    void          setAttributeValue(const char *attributeName,std::string& attributeValue);

    bool          findAttribute(const char *attributeName);
    void          removeAttributes(const char *pattern);
    void          replaceAttributeNamesWithValues(std::string inputFilename,std::string outputFilename);

    void          print(std::ostream& stream,uint level,uint optionFlags);

  protected:

    std::string   parseValue(std::string value);
    std::string   parseConstValue(std::string value);

    void          removeComments(char *st,unsigned long long *positions,char *newst,unsigned long long *newpositions,int len);
    void          setPositions(char *st,unsigned long long *positions,int len);
    void          getWords(char *st,unsigned long long *positions,std::vector<std::string>& words,std::vector<unsigned long long>& wordPositions);
    int           readValue(std::vector<std::string>& words,std::vector<unsigned long long>& wordPositions,int len,int pos,std::string path);
    int           readAttribute(std::vector<std::string>& words,std::vector<unsigned long long>& wordPositions,int len,int pos,std::string path);

  public:

    std::vector<T::Attribute>  mAttributeList;
    std::string                mFilename;
    std::string                mCurrentFilename;

  private:
    std::set<std::string>      mIncludedConfigurationFiles;
};


}

