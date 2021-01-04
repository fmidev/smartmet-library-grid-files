#include "ConfigurationFile.h"
#include "GeneralFunctions.h"
#include "ShowFunction.h"

#include <macgyver/Exception.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fnmatch.h>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


#define MAX_CONFIG_FILE_SIZE 100000

namespace SmartMet
{


ConfigurationFile::ConfigurationFile()
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed!",nullptr);
  }
}




/*
ConfigurationFile::ConfigurationFile(const ConfigurationFile& configurationFile)
{
  FUNCTION_TRACE
  try
  {
    mFilename = configurationFile.mFilename;
    mAttributeList = configurationFile.mAttributeList;
    mIncludedConfigurationFiles = configurationFile.mIncludedConfigurationFiles;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Copy constructor failed!",nullptr);
  }
}
*/




ConfigurationFile::ConfigurationFile(std::string filename)
{
  FUNCTION_TRACE
  try
  {
    readFile(filename);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Constructor failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





ConfigurationFile::~ConfigurationFile()
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}




// You can add extra configuration file that can be used in the actual
// configuration file. For example, you might use different additional
// configuration files for testing, development and production. These
// files might contain for example, database connection parameters
// required in different environments.

void ConfigurationFile::addConfigurationFile(std::string filename)
{
  FUNCTION_TRACE
  try
  {
    if (mIncludedConfigurationFiles.find(filename) != mIncludedConfigurationFiles.end())
      return; // Already loaded

    mIncludedConfigurationFiles.insert(filename);
    ConfigurationFile configFile(filename);
    for (auto it=configFile.mAttributeList.begin(); it!=configFile.mAttributeList.end();++it)
    {
      mAttributeList.push_back(*it);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Configuration file addition failed!",nullptr);
  }
}





void ConfigurationFile::clear()
{
  FUNCTION_TRACE
  try
  {
    mAttributeList.clear();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Clear operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





void ConfigurationFile::readFile(std::string filename)
{
  FUNCTION_TRACE
  try
  {
    if (mFilename.length() == 0)
      mFilename = filename;

    mCurrentFilename = filename;
    FILE *file = fopen(filename.c_str(),"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open the configuration file!");
      exception.addParameter("Configuration file",filename);
      throw exception;
    }

    char st[MAX_CONFIG_FILE_SIZE];
    char newst[MAX_CONFIG_FILE_SIZE];
    unsigned long long positions[MAX_CONFIG_FILE_SIZE];
    unsigned long long newpositions[MAX_CONFIG_FILE_SIZE];
    int n = fread(st,1,MAX_CONFIG_FILE_SIZE,file);
    fclose(file);

    if (n > 0)
    {
      st[n] = '\0';

      setPositions(st,positions,n);
      removeComments(st,positions,newst,newpositions,n);

      std::vector<std::string> wordList;
      std::vector<unsigned long long> wordPositions;

      getWords(newst,newpositions,wordList,wordPositions);
      int len = wordList.size();
      std::string path;
      int pos = 0;
      while (pos < len)
      {
        pos = readAttribute(wordList,wordPositions,len,pos,path,-1);
      }
    }

    mCurrentFilename = mFilename;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Configuration file reading failed!",nullptr);
    if (mFilename != filename)
      exception.addParameter("Main configuration file",mFilename);
    exception.addParameter("Configuration file",filename);
    throw exception;
  }
}





void ConfigurationFile::replaceAttributeNamesWithValues(std::string inputFilename,std::string outputFilename)
{
  FUNCTION_TRACE
  try
  {
    FILE *inFile = fopen(inputFilename.c_str(),"re");
    if (inFile == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open the input file!");
      exception.addParameter("Input file",inputFilename);
      throw exception;
    }

    FILE *outFile = fopen(outputFilename.c_str(),"we");
    if (outFile == nullptr)
    {
      fclose(inFile);
      Fmi::Exception exception(BCP,"Cannot open the output file!");
      exception.addParameter("Output file",outputFilename);
      throw exception;
    }

    char st[10000];
    while (!feof(inFile))
    {
      if (fgets(st,10000,inFile) != nullptr)
      {
        std::string newStr = parseValue(std::string(st));
        fprintf(outFile,"%s",newStr.c_str());
      }
    }

    fclose(inFile);
    fclose(outFile);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}





bool ConfigurationFile::getAttributeValue(const char *attributeName,bool& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    for (auto attr = mAttributeList.begin(); attr != mAttributeList.end(); ++attr)
    {
      if (strcasecmp(attr->mName.c_str(),attributeName) == 0)
      {
        std::string val = parseValue(attr->mValue);

        if (val.length() == 0)
        {
          Fmi::Exception exception(BCP,"The attribute value is empty (not a boolean as requested)!");
          exception.addParameter("AttributeName",attributeName);
          throw exception;
        }

        if (val[0] == '"')
        {
          Fmi::Exception exception(BCP,"The attribute value is a string (not a boolean as requested)!");
          exception.addParameter("AttributeName",attributeName);
          exception.addParameter("AttributeValue",val);
          throw exception;
        }

        if (strcasecmp(val.c_str(),"true") == 0  ||  strcasecmp(val.c_str(),"yes") == 0)
        {
          attributeValue = true;
          return true;
        }

        if (strcasecmp(val.c_str(),"false") == 0  ||  strcasecmp(val.c_str(),"no") == 0)
        {
          attributeValue = false;
          return true;
        }

        Fmi::Exception exception(BCP,"The attribute value is not a boolean!");
        exception.addParameter("AttributeName",attributeName);
        exception.addParameter("AttributeValue",val);
        throw exception;
      }
    }
    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





bool ConfigurationFile::getAttributeValue(const char *attributeName,double& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    for (auto attr = mAttributeList.begin(); attr != mAttributeList.end(); ++attr)
    {
      if (strcasecmp(attr->mName.c_str(),attributeName) == 0)
      {
        std::string val = parseValue(attr->mValue);

        if (val.length() == 0)
        {
          Fmi::Exception exception(BCP,"The attribute value is empty (not a float as requested)!");
          exception.addParameter("AttributeName",attributeName);
          throw exception;
        }

        if (val[0] == '"')
        {
          Fmi::Exception exception(BCP,"The attribute value is a string (not a float as requested)!");
          exception.addParameter("AttributeName",attributeName);
          exception.addParameter("AttributeValue",val);
          throw exception;
        }

        attributeValue = toDouble(val.c_str());
        return true;
      }
    }
    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





bool ConfigurationFile::getAttributeValue(const char *attributeName,char& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    long long val = 0;
    bool result = getAttributeValue(attributeName,val);
    attributeValue = C_CHAR(val);
    return result;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





bool ConfigurationFile::getAttributeValue(const char *attributeName,short& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    long long val = 0;
    bool result = getAttributeValue(attributeName,val);
    attributeValue = C_SHORT(val);
    return result;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





bool ConfigurationFile::getAttributeValue(const char *attributeName,int& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    long long val = 0;
    bool result = getAttributeValue(attributeName,val);
    attributeValue = C_INT(val);
    return result;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





bool ConfigurationFile::getAttributeValue(const char *attributeName,long& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    long long val = 0;
    bool result = getAttributeValue(attributeName,val);
    attributeValue = C_LONG(val);
    return result;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





bool ConfigurationFile::getAttributeValue(const char *attributeName,long long& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    for (auto attr = mAttributeList.begin(); attr != mAttributeList.end(); ++attr)
    {
      if (strcasecmp(attr->mName.c_str(),attributeName) == 0)
      {
        std::string val = parseValue(attr->mValue);

        if (val.length() == 0)
        {
          Fmi::Exception exception(BCP,"The attribute value is empty (not an integer as requested)!");
          exception.addParameter("AttributeName",attributeName);
          throw exception;
        }

        if (val[0] == '"')
        {
          Fmi::Exception exception(BCP,"The attribute value is a string (not an integer as requested)!");
          exception.addParameter("AttributeName",attributeName);
          exception.addParameter("AttributeValue",val);
          throw exception;
        }

        attributeValue = toInt64(val.c_str());
        return true;
      }
    }
    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





bool ConfigurationFile::getAttributeValue(const char *attributeName,unsigned char& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    unsigned long long val = 0;
    bool result = getAttributeValue(attributeName,val);
    attributeValue = C_UCHAR(val);
    return result;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





bool ConfigurationFile::getAttributeValue(const char *attributeName,unsigned short& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    unsigned long long val = 0;
    bool result = getAttributeValue(attributeName,val);
    attributeValue = C_USHORT(val);
    return result;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





bool ConfigurationFile::getAttributeValue(const char *attributeName,unsigned int& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    unsigned long long val = 0;
    bool result = getAttributeValue(attributeName,val);
    attributeValue = C_UINT(val);
    return result;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





bool ConfigurationFile::getAttributeValue(const char *attributeName,unsigned long& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    unsigned long long val = 0;
    bool result = getAttributeValue(attributeName,val);
    attributeValue = C_ULONG(val);
    return result;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





bool ConfigurationFile::getAttributeValue(const char *attributeName,unsigned long long& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    long long val = 0;
    bool result = getAttributeValue(attributeName,val);
    attributeValue = C_UINT64(val);
    return result;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





bool ConfigurationFile::getAttributeValue(const char *attributeName,std::string& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    for (auto attr = mAttributeList.begin(); attr != mAttributeList.end(); ++attr)
    {
      if (strcasecmp(attr->mName.c_str(),attributeName) == 0)
      {
        std::string val = parseValue(attr->mValue);

        auto len = val.length();

        if (len > 1  &&  val[0] == '"'  &&  val[len-1] == '"')
          attributeValue = val.substr(1,len-2);
        else
          attributeValue = val;

        return true;
      }
    }
    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





bool ConfigurationFile::getAttributeValue(const char *attributeName,std::vector<std::string>& attributeValueVec)
{
  FUNCTION_TRACE
  try
  {
    bool exists = false;
    uint len = strlen(attributeName);
    for (auto attr = mAttributeList.begin(); attr != mAttributeList.end(); ++attr)
    {
      if (strncasecmp(attr->mName.c_str(),attributeName,len) == 0)
      {
        if (attr->mName.length() == len)
        {
          // Attribute exists, but its value is not an array.
          Fmi::Exception exception(BCP,"The attribute value is not an array!");
          exception.addParameter("AttributeName",attributeName);
          throw exception;
        }

        if (attr->mName.length() >= (len+2)  &&  attr->mName[len] == '['  &&  attr->mName[len+1] == ']')
        {
          exists = true;
        }
        else
        if (attr->mName[len] == '.')
        {
          std::string itm;
          std::size_t p = attr->mName.find(".",len+1);

          if (p != std::string::npos)
          {
            Fmi::Exception exception(BCP,"The attribute value contains substructures!");
            exception.addParameter("AttributeName",attributeName);
            throw exception;
          }

          std::string val;
          if (getAttributeValue(attr->mName.c_str(),val))
            attributeValueVec.push_back(val);
        }
      }
    }

    if (attributeValueVec.size() > 0  ||  exists)
      return true;

    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





bool ConfigurationFile::getAttributeFields(const char *attributeName,std::set<std::string>& attributeFields)
{
  FUNCTION_TRACE
  try
  {
    uint len = strlen(attributeName);
    for (auto attr = mAttributeList.begin(); attr != mAttributeList.end(); ++attr)
    {
      if (strncasecmp(attr->mName.c_str(),attributeName,len) == 0)
      {
        if (attr->mName.length() == len)
        {
          // Attribute exists, but it does not have sub-attributes
          return true;
        }

        if (attr->mName[len] == '.')
        {
          std::string itm;
          std::size_t p = attr->mName.find(".",len+1);
          if (p != std::string::npos)
            itm = attr->mName.substr(len+1,p-len-1);
          else
            itm = attr->mName.substr(len+1);

          if (attributeFields.find(itm) == attributeFields.end())
            attributeFields.insert(itm);
        }
      }
    }

    if (attributeFields.size() > 0)
      return true;

    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





bool ConfigurationFile::getSubAttributes(const char *attributeName,std::vector<std::string>& attributeNames)
{
  FUNCTION_TRACE
  try
  {
    uint len = strlen(attributeName);
    for (auto attr = mAttributeList.begin(); attr != mAttributeList.end(); ++attr)
    {
      if (strncasecmp(attr->mName.c_str(),attributeName,len) == 0)
      {
        if (attr->mName.length() == len)
        {
          // Attribute exists, but it does not have sub-attributes
          return true;
        }

        if (attr->mName[len] == '.')
        {
          std::string itm = attr->mName.substr(len+1);

          attributeNames.push_back(itm);
        }
      }
    }

    if (attributeNames.size() > 0)
      return true;

    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





std::string ConfigurationFile::getFilename()
{
  try
  {
    return mFilename;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





bool ConfigurationFile::findAttribute(const char *attributeName)
{
  FUNCTION_TRACE
  try
  {
    uint len = strlen(attributeName);
    for (auto attr = mAttributeList.begin(); attr != mAttributeList.end(); ++attr)
    {
      if (strncasecmp(attr->mName.c_str(),attributeName,len) == 0)
      {
        if (attr->mName.length() == len  ||  attr->mName[len] == '.')
          return true;
      }
    }
    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





void ConfigurationFile::setAttributeValue(const char *attributeName,std::string& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    for (auto attr = mAttributeList.begin(); attr != mAttributeList.end(); ++attr)
    {
      if (strcasecmp(attr->mName.c_str(),attributeName) == 0)
      {
        attr->mValue = attributeValue;
        return;
      }
    }
    mAttributeList.push_back(T::Attribute(std::string(attributeName),attributeValue));
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





void ConfigurationFile::print(std::ostream& stream,uint level,uint optionFlags)
{
  FUNCTION_TRACE
  try
  {
    stream << space(level) << "ConfigurationFile\n";
    stream << space(level) << "- mFilename            = " << mFilename << "\n";
    stream << space(level) << "- mAttributeList       = \n";

    for (auto attr = mAttributeList.begin(); attr != mAttributeList.end(); ++attr)
    {
      if ((optionFlags & 0x0001) != 0)
        stream << space(level) << "    * ATTR " << attr->mName << " = " << parseValue(attr->mValue) << "\n";
      else
        stream << space(level) << "    * ATTR " << attr->mName << " = " << attr->mValue << "\n";
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string ConfigurationFile::parseValue(std::string value)
{
  FUNCTION_TRACE
  try
  {
    std::string val = value;

    std::size_t p1 = 0;
    while (p1 != std::string::npos)
    {
      p1 = val.find("$(");
      if (p1 != std::string::npos)
      {
        std::size_t p2 = val.find(")",p1+1);
        if (p2 != std::string::npos)
        {
          std::string var = val.substr(p1+2,p2-p1-2);
          std::string varValue;

          // Searching a value for the variable
          if (!getAttributeValue(var.c_str(),varValue))
          {
            // Variable not defined in the configuration file. Maybe it is an environmental variable.
            char *env = getenv(var.c_str());
            if (env == nullptr)
            {
              Fmi::Exception exception(BCP,"Unknown variable name!");
              exception.addParameter("VariableName",var);
              throw exception;
            }

            varValue = env;
          }

          std::string newVal = val.substr(0,p1) + varValue + val.substr(p2+1);
          val = newVal;
        }
        else
        {
          Fmi::Exception exception(BCP,"Expecting the character ')' at the end of the variable name!");
          exception.addParameter("Value",value);
          throw exception;
        }
      }
    }

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string ConfigurationFile::parseConstValue(std::string value)
{
  FUNCTION_TRACE
  try
  {
    std::string val = value;

    std::size_t p1 = 0;
    while (p1 != std::string::npos)
    {
      p1 = val.find("%(");
      if (p1 != std::string::npos)
      {
        std::size_t p2 = val.find(")",p1+1);
        if (p2 != std::string::npos)
        {
          std::string var = val.substr(p1+2,p2-p1-2);
          std::string varValue;

          if (var == "DIR")
          {
            varValue = getFileDir(mCurrentFilename);
          }
          else
          // Searching a value for the variable
          if (!getAttributeValue(var.c_str(),varValue))
          {
            // Variable not defined in the configuration file. Maybe it is an environmental variable.
            char *env = getenv(var.c_str());
            if (env == nullptr)
            {
              Fmi::Exception exception(BCP,"Unknown variable name!");
              exception.addParameter("VariableName",var);
              throw exception;
            }

            varValue = env;
          }

          std::string newVal = val.substr(0,p1) + varValue + val.substr(p2+1);
          val = newVal;
        }
        else
        {
          Fmi::Exception exception(BCP,"Expecting the character ')' at the end of the variable name!");
          exception.addParameter("Value",value);
          throw exception;
        }
      }
    }

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void ConfigurationFile::removeComments(char *st,unsigned long long *positions,char *newst,unsigned long long *newpositions,int len)
{
  FUNCTION_TRACE
  try
  {
    int a = 0;
    int b = 0;
    int stringStart = 0;

    bool ind = false;
    while (a < len)
    {
      if (st[a] == '"'  &&  st[a-1] != '\\')
      {
        ind = !ind;
        if (ind)
          stringStart = a;
      }

      if (ind  &&  st[a] == '\n')
      {
        Fmi::Exception exception(BCP,"The string does not have the end delimiter!");
        exception.addParameter("Row",std::to_string(positions[stringStart] >> 32));
        exception.addParameter("Column",std::to_string(positions[stringStart] & 0xFFFFFFFF));
        throw exception;
      }

      if (!ind)
      {
        if (st[a] == '#')
        {
          while (a < len  &&  st[a] != '\n')
            a++;
        }
        if (st[a] == '/'  &&  st[a+1] == '/')
        {
          while (a < len  &&  st[a] != '\n')
            a++;

          if (a < len)
            a++;
        }
        else
        if (st[a] == '/'  &&  st[a+1] == '*')
        {
          while (a < len  &&  !(st[a-1] == '*'  &&  st[a] == '/'))
            a++;

          if (a < len)
            a++;
        }
        else
        if (a < len)
        {
          newst[b] = st[a];
          newpositions[b] = positions[a];

          if (st[a] == ';')
          {
            newst[b] = ' ';
            newpositions[b] = positions[a];
          }

          if (st[a] == ',' || st[a] == ':' ||  st[a] == '=' ||  st[a] == '(' ||  st[a] == ')' ||  st[a] == '[' ||  st[a] == ']' ||  st[a] == '{' ||  st[a] == '}')
          {
            newst[b+1] = st[a];
            newst[b] = ' ';
            newst[b+2] = ' ';

            newpositions[b] = positions[a];
            newpositions[b+1] = positions[a];
            newpositions[b+2] = positions[a];

            b = b + 2;
          }

          b++;
          a++;
        }
      }
      else
      {
        newst[b] = st[a];
        newpositions[b] = positions[a];
        b++;
        a++;
      }
    }
    newst[b] = '\0';
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ConfigurationFile::setPositions(char *st,unsigned long long *positions,int len)
{
  FUNCTION_TRACE
  try
  {
    unsigned long long row = 1;
    unsigned long long col = 1;

    for (int t=0; t<len; t++)
    {
      positions[t] = (row << 32) + col;
      if (st[t] == '\n')
      {
        col = 0;
        row++;
      }
      col++;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ConfigurationFile::getWords(char *st,unsigned long long *positions,std::vector<std::string>& words,std::vector<unsigned long long>& wordPositions)
{
  FUNCTION_TRACE
  try
  {
    char buf[10000];
    uint a = 0;
    uint c = 0;
    bool ind = false;
    while (st[a] != '\0')
    {
      if (st[a] == '"')
        ind = !ind;

      if ((!ind  &&  st[a] <= ' '))
      {
        buf[c] = '\0';
        if (c > 0)
        {
          words.push_back(std::string(buf));
          wordPositions.push_back(positions[a-c]);
        }
        c = 0;
      }
      else
      {
        buf[c] = st[a];
        c++;
      }

      a++;
    }

    if (c > 0)
    {
      buf[c] = '\0';
      words.push_back(std::string(buf));
      wordPositions.push_back(positions[a-c]);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






int ConfigurationFile::readValue(std::vector<std::string>& words,std::vector<unsigned long long>& wordPositions,int len,int pos,std::string path)
{
  FUNCTION_TRACE
  try
  {
    if (pos >= len)
      return pos;

    if ((pos+3) < len &&  words[pos] == "$" &&  words[pos+1] == "("  &&  words[pos+3] == ")")
    {
      T::Attribute attr;
      attr.mName = path;
      attr.mValue = "$(" + words[pos+2] + ")";
      mAttributeList.push_back(attr);

      return pos + 4;
    }
    else
    if ((pos+3) < len &&  words[pos] == "%" &&  words[pos+1] == "("  &&  words[pos+3] == ")")
    {
      T::Attribute attr;
      attr.mName = path;
      std::string v = "%(" + words[pos+2] + ")";
      attr.mValue = parseConstValue(v);
      mAttributeList.push_back(attr);

      return pos + 4;
    }
    else
    if (words[pos] == "{" )
    {
      int startPos = pos;
      pos++;
      while (pos < len  &&  words[pos] != "}")
      {
        pos = readAttribute(words,wordPositions,len,pos,path,-1);
      }

      if (pos == len)
      {
        Fmi::Exception exception(BCP,"Cannot find the end char '}' for the structure!");
        exception.addParameter("Row",std::to_string(wordPositions[startPos] >> 32));
        exception.addParameter("Column",std::to_string(wordPositions[startPos] & 0xFFFFFFFF));
        throw exception;
      }

      return pos+1;
    }
    else
    if (words[pos] == "(")
    {
      T::Attribute attr;
      attr.mName = path + "()";
      attr.mValue = "";
      mAttributeList.push_back(attr);

      int startPos = pos;
      pos++;
      int index = 0;
      while (pos < len  &&  words[pos] != ")")
      {
        pos = readAttribute(words,wordPositions,len,pos,path,index);
        index++;

        if (words[pos] != ","  &&  words[pos] != ")")
        {
          Fmi::Exception exception(BCP,"Expected end char ')' for the list!");
          exception.addParameter("Row",std::to_string(wordPositions[startPos] >> 32));
          exception.addParameter("Column",std::to_string(wordPositions[startPos] & 0xFFFFFFFF));
          throw exception;
        }
        while (pos < len  &&  words[pos] == ",")
          pos++;
      }

      if (pos == len)
      {
        Fmi::Exception exception(BCP,"Cannot find the end char ')' for the list!");
        exception.addParameter("Row",std::to_string(wordPositions[startPos] >> 32));
        exception.addParameter("Column",std::to_string(wordPositions[startPos] & 0xFFFFFFFF));
        throw exception;
      }

      return pos+1;
    }
    else
    if (words[pos] == "[")
    {
      char tmp[1000];
      uint index = 0;
      T::Attribute attr;
      attr.mName = path + "[]";
      attr.mValue = "";
      if (!findAttribute(attr.mName.c_str()))
      {
        mAttributeList.push_back(attr);
      }
      else
      {
        // The array already exists. Let's try to find the first free index.
        bool idxFound = true;
        while (idxFound)
        {
          sprintf(tmp,"%s.%u",path.c_str(),index);
          if (findAttribute(tmp))
            index++;
          else
            idxFound = false;
        }
      }

      int startPos = pos;
      pos++;
      while (pos < len  &&  words[pos] != "]")
      {
        sprintf(tmp,"%s.%u",path.c_str(),index);
        std::string newPath = tmp;
        pos = readValue(words,wordPositions,len,pos,newPath);
        index++;
        if (words[pos] != ","  &&  words[pos] != "]")
        {
          Fmi::Exception exception(BCP,"Expected end char ']' for the array!");
          exception.addParameter("Row",std::to_string(wordPositions[startPos] >> 32));
          exception.addParameter("Column",std::to_string(wordPositions[startPos] & 0xFFFFFFFF));
          throw exception;
        }

        while (pos < len  &&  words[pos] == ",")
          pos++;
      }

      if (pos == len)
      {
        Fmi::Exception exception(BCP,"Cannot find the end char ']' for the array!");
        exception.addParameter("Row",std::to_string(wordPositions[startPos] >> 32));
        exception.addParameter("Column",std::to_string(wordPositions[startPos] & 0xFFFFFFFF));
        throw exception;
      }

      return pos+1;
    }
    else
    {
      std::string attributeValue = parseConstValue(words[pos]);
      setAttributeValue(path.c_str(),attributeValue);
      return pos + 1;
    }
    return pos;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void ConfigurationFile::removeAttributes(const char *pattern)
{
  try
  {
    std::vector<T::Attribute>  newAttributeList;

    for (auto attr = mAttributeList.begin(); attr != mAttributeList.end(); ++attr)
    {
      if (fnmatch(pattern,attr->mName.c_str(),0) != 0)
      {
        newAttributeList.push_back(*attr);
      }
    }
    if (newAttributeList.size() != mAttributeList.size())
      mAttributeList = newAttributeList;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





int ConfigurationFile::readAttribute(std::vector<std::string>& words,std::vector<unsigned long long>& wordPositions,int len,int pos,std::string path,int index)
{
  FUNCTION_TRACE
  try
  {
    if (pos >= len)
      return pos;

    if ((pos+1) < len  &&  words[pos] == "@include")
    {
      std::string fname = parseConstValue(words[pos+1]);
      fname = parseValue(fname);

      auto slen = fname.length();
      if (slen > 1  &&  fname[0] == '"'  &&  fname[slen-1] == '"')
        fname = fname.substr(1,slen-2);


      if (fname <= " ")
      {
        Fmi::Exception exception(BCP,"No include file defined!");
        exception.addParameter("Row",std::to_string(wordPositions[pos] >> 32));
        exception.addParameter("Column",std::to_string(wordPositions[pos] & 0xFFFFFFFF));
        throw exception;
      }

      if (fname[0] != '/')
      {
        // The file name does not contain path, so it should be relational
        // to the current path.

        std::string dir = getFileDir(mCurrentFilename);
        fname = dir + fname;
      }

      if (mIncludedConfigurationFiles.find(fname) == mIncludedConfigurationFiles.end())
      {
        std::string currentFilename = mCurrentFilename;
        mIncludedConfigurationFiles.insert(fname);
        readFile(fname);
        mCurrentFilename = currentFilename;
      }
      pos = pos + 1;
    }
    else
    if ((pos+1) < len  &&  words[pos] == "@remove")
    {
      std::string pattern = parseValue(words[pos+1]);

      auto slen = pattern.length();
      if (slen > 1  &&  pattern[0] == '"'  &&  pattern[slen-1] == '"')
        pattern = pattern.substr(1,slen-2);

      removeAttributes(pattern.c_str());

      pos = pos + 1;
    }
    else
    if ((pos+1) < len  &&  words[pos] == "@print")
    {
      std::string message = parseConstValue(words[pos+1]);
      message = parseValue(message);

      auto slen = message.length();
      if (slen > 1  &&  message[0] == '"'  &&  message[slen-1] == '"')
        message = message.substr(1,slen-2);

      printf("%s\n",message.c_str());
      pos = pos + 1;
    }
    else
    if ((pos+1) < len  &&  words[pos] == "@location")
    {
      printf("*** %s [%d:%d]\n",mCurrentFilename.c_str(),C_INT(wordPositions[pos] >> 32),C_INT(wordPositions[pos] & 0xFFFFFFFF));
    }
    else
    if ((pos+1) < len  &&  words[pos] == "@throw")
    {
      std::string message = parseConstValue(words[pos+1]);
      message = parseValue(message);

      Fmi::Exception exception(BCP,message);
      exception.addParameter("Row",std::to_string(wordPositions[pos] >> 32));
      exception.addParameter("Column",std::to_string(wordPositions[pos] & 0xFFFFFFFF));
      throw exception;
    }
    else
    if ((pos+1) < len  &&  words[pos] == "@ifdef")
    {
      int startPos = pos;
      std::string attrName = parseValue(words[pos+1]);
      pos = pos + 1;

      if (!findAttribute(attrName.c_str())  &&  getenv(attrName.c_str()) == nullptr)
      {
        // Attribute not defined. Ignoring the section.
        while (pos < len  &&  words[pos] != "@endif"  &&  words[pos] != "@else")
        {
          pos++;
        }

        if (words[pos] != "@endif"  &&  words[pos] != "@else")
        {
          Fmi::Exception exception(BCP,"Expected '@endif' or '@else' for '@ifdef'!");
          exception.addParameter("Row",std::to_string(wordPositions[startPos] >> 32));
          exception.addParameter("Column",std::to_string(wordPositions[startPos] & 0xFFFFFFFF));
          throw exception;
        }
      }
      else
      {
        // Attribute is defined. If there is 'else' section in this condition then we should
        // ignore it.

        int p = pos;
        while (p < len  &&  words[p] != "@endif"  &&  words[p] != "@else")
          p++;

        if (words[p] == "@else")
        {
          while (p < len  &&  words[p] != "@endif")
          {
            words[p] = "@ignore";
            p++;
          }
        }
      }
    }
    else
    if ((pos+1) < len  &&  words[pos] == "@ifndef")
    {
      int startPos = pos;
      std::string attrName = parseValue(words[pos+1]);
      pos = pos + 1;

      if (findAttribute(attrName.c_str())  ||  getenv(attrName.c_str()) != nullptr)
      {
        // Attribute defined. Ignoring the section.
        while (pos < len  &&  words[pos] != "@endif"  &&  words[pos] != "@else")
        {
          pos++;
        }
        if (words[pos] != "@endif"  &&  words[pos] != "@else")
        {
          Fmi::Exception exception(BCP,"Expected '@endif' or '@else' for '@ifndef'!");
          exception.addParameter("Row",std::to_string(wordPositions[startPos] >> 32));
          exception.addParameter("Column",std::to_string(wordPositions[startPos] & 0xFFFFFFFF));
          throw exception;
        }
      }
      else
      {
        // Attribute nit defined. If there is 'else' section in this condition then we should
        // ignore it.

        int p = pos;
        while (p < len  &&  words[p] != "@endif"  &&  words[p] != "@else")
          p++;

        if (words[p] == "@else")
        {
          while (p < len  &&  words[p] != "@endif")
          {
            words[p] = "@ignore";
            p++;
          }
        }
      }
    }
    else
    if (words[pos] == "@endif")
    {
      int p = pos-1;
      while (p > 0  &&  words[p] != "@endif"  &&  words[p] != "@else"  &&  words[p] != "@ifdef"  &&  words[p] != "@ifndef")
        p--;

      if (words[p] != "@ifdef"  &&  words[p] != "@ifndef"  &&  words[p] != "@else")
      {
        Fmi::Exception exception(BCP,"Unexpected '@endif' found!");
        exception.addParameter("Row",std::to_string(wordPositions[pos] >> 32));
        exception.addParameter("Column",std::to_string(wordPositions[pos] & 0xFFFFFFFF));
        throw exception;
      }
    }
    else
    if (words[pos] == "@else")
    {
      int p = pos-1;
      while (p > 0  &&  words[p] != "@endif"  &&  words[p] != "@else"  &&  words[p] != "@ifdef"  &&  words[p] != "@ifndef")
        p--;

      if (words[p] != "@ifdef"  &&  words[p] != "@ifndef")
      {
        Fmi::Exception exception(BCP,"Unexpected '@endif' found!");
        exception.addParameter("Row",std::to_string(wordPositions[pos] >> 32));
        exception.addParameter("Column",std::to_string(wordPositions[pos] & 0xFFFFFFFF));
        throw exception;
      }
    }
    else
    if (words[pos] == "@ignore")
    {
    }
    else
    if ((pos+1) < len  &&  (words[pos+1] == ":" || words[pos+1] == "="))
    {
      std::string attributeName = words[pos];
      std::string newPath = attributeName;
      if (path > " ")
        newPath = path + "." + attributeName;

      if (index >= 0)
        newPath = newPath + "." + std::to_string(index);

      pos = readValue(words,wordPositions,len,pos+2,newPath);
      return pos;
    }
    else
    {
      if ((pos+1) < len)
      {
        Fmi::Exception exception(BCP,"Expected ':'' or '=' character!");
        exception.addParameter("Row",std::to_string(wordPositions[pos+1] >> 32));
        exception.addParameter("Column",std::to_string(wordPositions[pos+1] & 0xFFFFFFFF));
        throw exception;
      }
      else
      {
        Fmi::Exception exception(BCP,"Invalid attribute definition!");
        exception.addParameter("Row",std::to_string(wordPositions[pos] >> 32));
        exception.addParameter("Column",std::to_string(wordPositions[pos] & 0xFFFFFFFF));
        throw exception;
      }
    }
    return pos+1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



}



