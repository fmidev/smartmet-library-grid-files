#include "ConfigurationFile.h"
#include "GeneralFunctions.h"
#include "ShowFunction.h"

#include <macgyver/Exception.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <fnmatch.h>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF



namespace SmartMet
{


/*! \brief Default constructor that creates an empty configuration. */

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




/*! \brief Constructs the configuration by reading attributes from the given file. */

ConfigurationFile::ConfigurationFile(const std::string& filename)
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





/*! \brief Destructor. */

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

/*! \brief Loads an additional configuration file and merges its attributes into this configuration. */

void ConfigurationFile::addConfigurationFile(const std::string& filename)
{
  FUNCTION_TRACE
  try
  {
    if (mIncludedConfigurationFiles.find(filename) != mIncludedConfigurationFiles.end())
      return; // Already loaded

    mIncludedConfigurationFiles.insert(filename);
    ConfigurationFile configFile(filename);
    for (auto& it : configFile.mAttributeList)
    {
      mAttributeList.emplace_back(it);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Configuration file addition failed!",nullptr);
  }
}





/*! \brief Clears all attributes from the configuration. */

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





/*! \brief Reads the given configuration file and parses its attributes into this configuration. */

void ConfigurationFile::readFile(const std::string& filename)
{
  FUNCTION_TRACE
  try
  {
    if (mFilename.empty())
      mFilename = filename;

    mCurrentFilename = filename;
    FILE *file = fopen(filename.c_str(),"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open the configuration file!");
      exception.addParameter("Configuration file",filename);
      throw exception;
    }

    // Read the whole file, the size is not limited
    if (fseek(file,0,SEEK_END) != 0)
      throw Fmi::Exception(BCP,"Failed to seek in the file");
    long fileSize = ftell(file);
    if (fseek(file,0,SEEK_SET) != 0)
      throw Fmi::Exception(BCP,"Failed to seek in the file");
    fileSize = std::max<long>(fileSize, 0);

    // Room for the terminating null character
    std::vector<char> stVec(fileSize + 1);
    // Separators are expanded to three characters when comments are removed
    std::vector<char> newstVec(3 * fileSize + 1);
    std::vector<UInt64> positionsVec(fileSize + 1);
    std::vector<UInt64> newpositionsVec(3 * fileSize + 1);
    char *st = stVec.data();
    char *newst = newstVec.data();
    UInt64 *positions = positionsVec.data();
    UInt64 *newpositions = newpositionsVec.data();

    int n = fread(st,1,fileSize,file);
    (void)fclose(file);

    if (n > 0)
    {
      // codechecker_false_positive [security.ArrayBound] n <= fileSize and the buffer has fileSize + 1 bytes
      st[n] = '\0';

      setPositions(st,positions,n);
      removeComments(st,positions,newst,newpositions,n);

      std::vector<std::string> wordList;
      std::vector<UInt64> wordPositions;

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





/*! \brief Copies the input file to the output file, expanding any attribute name references in its lines. */

void ConfigurationFile::replaceAttributeNamesWithValues(const std::string& inputFilename,const std::string& outputFilename)
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
      (void)fclose(inFile);
      Fmi::Exception exception(BCP,"Cannot open the output file!");
      exception.addParameter("Output file",outputFilename);
      throw exception;
    }

    char st[10000];
    while (fgets(st,10000,inFile) != nullptr)
    {
      std::string newStr = parseValue(std::string(st));
      fprintf(outFile,"%s",newStr.c_str());
    }

    (void)fclose(inFile);
    if (fclose(outFile) != 0)
      throw Fmi::Exception(BCP,"Failed to close the output file");
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}





/*! \brief Reads the named attribute as a boolean value. */

bool ConfigurationFile::getAttributeValue(const char *attributeName,bool& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    for (auto& attr : mAttributeList)
    {
      if (strcasecmp(attr.mName.c_str(),attributeName) == 0)
      {
        std::string val = parseValue(attr.mValue);

        if (val.empty())
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





/*! \brief Reads the named attribute as a double value. */

bool ConfigurationFile::getAttributeValue(const char *attributeName,double& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    for (auto& attr : mAttributeList)
    {
      if (strcasecmp(attr.mName.c_str(),attributeName) == 0)
      {
        std::string val = parseValue(attr.mValue);

        if (val.empty())
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





/*! \brief Reads the named attribute as a char value. */

bool ConfigurationFile::getAttributeValue(const char *attributeName,char& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    Int64 val = 0;
    bool result = getAttributeValue(attributeName,val);
    if (result)
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





/*! \brief Reads the named attribute as a short integer value. */

bool ConfigurationFile::getAttributeValue(const char *attributeName,short& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    Int64 val = 0;
    bool result = getAttributeValue(attributeName,val);
    if (result)
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





/*! \brief Reads the named attribute as an int value. */

bool ConfigurationFile::getAttributeValue(const char *attributeName,int& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    Int64 val = 0;
    bool result = getAttributeValue(attributeName,val);
    if (result)
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





/*! \brief Reads the named attribute as a 64-bit signed integer value. */

bool ConfigurationFile::getAttributeValue(const char *attributeName,Int64& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    for (auto& attr : mAttributeList)
    {
      if (strcasecmp(attr.mName.c_str(),attributeName) == 0)
      {
        std::string val = parseValue(attr.mValue);

        if (val.empty())
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





/*! \brief Reads the named attribute as an unsigned char value. */

bool ConfigurationFile::getAttributeValue(const char *attributeName,unsigned char& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    UInt64 val = 0;
    bool result = getAttributeValue(attributeName,val);
    if (result)
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





/*! \brief Reads the named attribute as an unsigned short value. */

bool ConfigurationFile::getAttributeValue(const char *attributeName,unsigned short& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    UInt64 val = 0;
    bool result = getAttributeValue(attributeName,val);
    if (result)
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





/*! \brief Reads the named attribute as an unsigned int value. */

bool ConfigurationFile::getAttributeValue(const char *attributeName,unsigned int& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    UInt64 val = 0;
    bool result = getAttributeValue(attributeName,val);
    if (result)
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





/*! \brief Reads the named attribute as a 64-bit unsigned integer value. */

bool ConfigurationFile::getAttributeValue(const char *attributeName,UInt64& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    Int64 val = 0;
    bool result = getAttributeValue(attributeName,val);
    if (result)
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





/*! \brief Reads the named attribute as a string value, stripping surrounding quotes. */

bool ConfigurationFile::getAttributeValue(const char *attributeName,std::string& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    for (auto& attr : mAttributeList)
    {
      if (strcasecmp(attr.mName.c_str(),attributeName) == 0)
      {
        std::string val = parseValue(attr.mValue);

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





/*! \brief Reads the named array attribute, populating the vector with all of its string values. */

bool ConfigurationFile::getAttributeValue(const char *attributeName,std::vector<std::string>& attributeValueVec)
{
  FUNCTION_TRACE
  try
  {
    bool exists = false;
    uint len = strlen(attributeName);
    for (auto& attr : mAttributeList)
    {
      if (strncasecmp(attr.mName.c_str(),attributeName,len) == 0)
      {
        if (attr.mName.length() == len)
        {
          // Attribute exists, but its value is not an array.
          Fmi::Exception exception(BCP,"The attribute value is not an array!");
          exception.addParameter("AttributeName",attributeName);
          throw exception;
        }

        if (attr.mName.length() >= (len+2)  &&  attr.mName[len] == '['  &&  attr.mName[len+1] == ']')
        {
          exists = true;
        }
        else
        if (attr.mName[len] == '.')
        {
          std::string itm;
          std::size_t p = attr.mName.find('.',len+1);

          if (p != std::string::npos)
          {
            Fmi::Exception exception(BCP,"The attribute value contains substructures!");
            exception.addParameter("AttributeName",attributeName);
            throw exception;
          }

          std::string val;
          if (getAttributeValue(attr.mName.c_str(),val))
            attributeValueVec.emplace_back(val);
        }
      }
    }

    return !attributeValueVec.empty()  ||  exists;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





/*! \brief Returns the number of elements in the named array attribute. */

uint ConfigurationFile::getArraySize(const char *attributeName)
{
  FUNCTION_TRACE
  try
  {
    int idx = -1;
    bool exists = false;
    uint len = strlen(attributeName);
    for (auto& attr : mAttributeList)
    {
      if (strncasecmp(attr.mName.c_str(),attributeName,len) == 0)
      {
        if (attr.mName.length() == len)
        {
          // Attribute exists, but its value is not an array.
          return 0;
        }

        if (attr.mName.length() >= (len+2)  &&  attr.mName[len] == '['  &&  attr.mName[len+1] == ']')
        {
          exists = true;
        }
        else
        if (attr.mName[len] == '.')
        {
          std::string itm;

          std::size_t p = attr.mName.find('.',len+1);
          if (p != std::string::npos)
            itm = attr.mName.substr(len+1,p-len-1);
          else
            itm = attr.mName.substr(len+1);

          int i = toInt32(itm.c_str());
          idx = std::max(i, idx);
        }
      }
    }

    if (exists)
      return idx+1;

    return 0;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}




/*! \brief Collects the names of immediate sub-fields under the given attribute. */

bool ConfigurationFile::getAttributeFields(const char *attributeName,std::set<std::string>& attributeFields)
{
  FUNCTION_TRACE
  try
  {
    uint len = strlen(attributeName);
    for (auto& attr : mAttributeList)
    {
      if (strncasecmp(attr.mName.c_str(),attributeName,len) == 0)
      {
        if (attr.mName.length() == len)
        {
          // Attribute exists, but it does not have sub-attributes
          return true;
        }

        if (attr.mName[len] == '.')
        {
          std::string itm;
          std::size_t p = attr.mName.find('.',len+1);
          if (p != std::string::npos)
            itm = attr.mName.substr(len+1,p-len-1);
          else
            itm = attr.mName.substr(len+1);

          attributeFields.insert(itm);
        }
      }
    }

    return !attributeFields.empty();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





/*! \brief Collects the full sub-attribute names under the given attribute. */

bool ConfigurationFile::getSubAttributes(const char *attributeName,std::vector<std::string>& attributeNames)
{
  FUNCTION_TRACE
  try
  {
    uint len = strlen(attributeName);
    for (auto& attr : mAttributeList)
    {
      if (strncasecmp(attr.mName.c_str(),attributeName,len) == 0)
      {
        if (attr.mName.length() == len)
        {
          // Attribute exists, but it does not have sub-attributes
          return true;
        }

        if (attr.mName[len] == '.')
        {
          std::string itm = attr.mName.substr(len+1);

          attributeNames.emplace_back(itm);
        }
      }
    }

    return !attributeNames.empty();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





/*! \brief Returns the name of the main configuration file. */

std::string ConfigurationFile::getFilename() const
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





/*! \brief Returns true if an attribute matching the given name (or its prefix path) exists. */

bool ConfigurationFile::findAttribute(const char *attributeName)
{
  FUNCTION_TRACE
  try
  {
    uint len = strlen(attributeName);
    for (auto& attr : mAttributeList)
    {
      if (strncasecmp(attr.mName.c_str(),attributeName,len) == 0)
      {
        if (attr.mName.length() == len  ||  attr.mName[len] == '.' || attr.mName[len] == '[')
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





/*! \brief Sets or updates the value of the named attribute. */

void ConfigurationFile::setAttributeValue(const char *attributeName,const std::string& attributeValue)
{
  FUNCTION_TRACE
  try
  {
    for (auto& attr : mAttributeList)
    {
      if (strcasecmp(attr.mName.c_str(),attributeName) == 0)
      {
        attr.mValue = attributeValue;
        return;
      }
    }
    mAttributeList.emplace_back(attributeName,attributeValue);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Configuration file",mFilename);
    throw exception;
  }
}





/*! \brief Prints the configuration filename and all its attributes to the given stream. */

void ConfigurationFile::print(std::ostream& stream,uint level,uint optionFlags)
{
  FUNCTION_TRACE
  try
  {
    stream << space(level) << "ConfigurationFile\n";
    stream << space(level) << "- mFilename            = " << mFilename << "\n";
    stream << space(level) << "- mAttributeList       = \n";

    for (auto& attr : mAttributeList)
    {
      if ((optionFlags & 0x0001) != 0)
        stream << space(level) << "    * ATTR " << attr.mName << " = " << parseValue(attr.mValue) << "\n";
      else
        stream << space(level) << "    * ATTR " << attr.mName << " = " << attr.mValue << "\n";
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Expands $(NAME) references in the given value using attributes or environment variables. */

std::string ConfigurationFile::parseValue(const std::string& value)
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
        std::size_t p2 = val.find(')',p1+1);
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





/*! \brief Expands %(NAME) references in the given value using attributes, environment variables, or special tokens like DIR. */

std::string ConfigurationFile::parseConstValue(const std::string& value)
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
        std::size_t p2 = val.find(')',p1+1);
        if (p2 != std::string::npos)
        {
          std::string var = val.substr(p1+2,p2-p1-2);
          std::string varValue;

          if (var == "DIR")
          {
            varValue = getFileDir(mCurrentFilename);
          }
          // Searching a value for the variable
          else if (!getAttributeValue(var.c_str(),varValue))
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




namespace
{
/*! \brief Copies the character into the new string. Semicolons are replaced by spaces and
    separators are surrounded by spaces. Returns the next position in the new string. */

int copyCharacter(const char *st,const UInt64 *positions,char *newst,UInt64 *newpositions,int a,int b)
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
  return b;
}



/*! \brief Processes the character outside of a string: skips the comments and copies the
    other characters. */

void processCharacter(const char *st,const UInt64 *positions,char *newst,UInt64 *newpositions,int len,int& a,int& b)
{
  if (st[a] == '#')
  {
    while (a < len  &&  st[a] != '\n')
      a++;
  }
  if ((a+1) < len  &&  st[a] == '/'  &&  st[a+1] == '/')
  {
    while (a < len  &&  st[a] != '\n')
      a++;

    if (a < len)
      a++;
  }
  else
  if ((a+1) < len  &&  st[a] == '/'  &&  st[a+1] == '*')
  {
    while (a < len  &&  (a <= 0 ||  st[a-1] != '*'  ||  st[a] != '/'))
      a++;

    if (a < len)
      a++;
  }
  else
  if (a < len)
  {
    b = copyCharacter(st,positions,newst,newpositions,a,b);
    a++;
  }
}
}  // namespace





/*! \brief Strips comments from the input buffer and pads delimiters with spaces in the output buffer. */

void ConfigurationFile::removeComments(const char *st,const UInt64 *positions,char *newst,UInt64 *newpositions,int len)
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
      if (st[a] == '"'  &&  (a == 0 || st[a-1] != '\\'))
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
        processCharacter(st,positions,newst,newpositions,len,a,b);
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





/*! \brief Builds row/column position information for each character in the input buffer. */

void ConfigurationFile::setPositions(const char *st,UInt64 *positions,int len)
{
  FUNCTION_TRACE
  try
  {
    UInt64 row = 1;
    UInt64 col = 1;

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





/*! \brief Tokenises the input buffer into whitespace-separated words with their source positions. */

void ConfigurationFile::getWords(char *st,UInt64 *positions,std::vector<std::string>& words,std::vector<UInt64>& wordPositions)
{
  FUNCTION_TRACE
  try
  {
    std::string buf;
    uint a = 0;
    uint c = 0;
    bool ind = false;
    while (st[a] != '\0')
    {
      if (st[a] == '"')
        ind = !ind;

      if ((!ind  &&  st[a] <= ' '))
      {
        if (c > 0)
        {
          words.emplace_back(buf);
          wordPositions.emplace_back(positions[a-c]);
        }
        buf.clear();
        c = 0;
      }
      else
      {
        buf += st[a];
        c++;
      }

      a++;
    }

    if (c > 0)
    {
      words.emplace_back(buf);
      wordPositions.emplace_back(positions[a-c]);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






/*! \brief Reads a structure value { ... }. */

int ConfigurationFile::readStructure(std::vector<std::string>& words,std::vector<UInt64>& wordPositions,int len,int pos,const std::string& path)
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





/*! \brief Reads a list value ( ... ). */

int ConfigurationFile::readList(std::vector<std::string>& words,std::vector<UInt64>& wordPositions,int len,int pos,const std::string& path)
{
  T::Attribute attr;
  attr.mName = path + "()";
  attr.mValue = "";
  mAttributeList.emplace_back(attr);

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





/*! \brief Returns the first free index of an existing array. */

uint ConfigurationFile::firstFreeArrayIndex(const std::string& path)
{
  uint index = 0;
  bool idxFound = true;
  while (idxFound)
  {
    std::string tmp = path + "." + std::to_string(index);
    if (findAttribute(tmp.c_str()))
      index++;
    else
      idxFound = false;
  }
  return index;
}





/*! \brief Reads an array value [ ... ]. */

int ConfigurationFile::readArray(std::vector<std::string>& words,std::vector<UInt64>& wordPositions,int len,int pos,const std::string& path)
{
  std::string tmp;
  uint index = 0;
  T::Attribute attr;
  attr.mName = path + "[]";
  attr.mValue = "";
  if (!findAttribute(attr.mName.c_str()))
  {
    mAttributeList.emplace_back(attr);
  }
  else
  {
    // The array already exists. Let's try to find the first free index.
    index = firstFreeArrayIndex(path);
  }

  int startPos = pos;
  pos++;
  while (pos < len  &&  words[pos] != "]")
  {
    tmp = path + "." + std::to_string(index);
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





/*! \brief Parses an attribute value (scalar, structure, list, or array) starting at the given word position. */

int ConfigurationFile::readValue(std::vector<std::string>& words,std::vector<UInt64>& wordPositions,int len,int pos,const std::string& path)
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
      mAttributeList.emplace_back(attr);

      return pos + 4;
    }
    if ((pos+3) < len &&  words[pos] == "%" &&  words[pos+1] == "("  &&  words[pos+3] == ")")
    {
      T::Attribute attr;
      attr.mName = path;
      std::string v = "%(" + words[pos+2] + ")";
      attr.mValue = parseConstValue(v);
      mAttributeList.emplace_back(attr);

      return pos + 4;
    }
    if (words[pos] == "{" )
      return readStructure(words,wordPositions,len,pos,path);

    if (words[pos] == "(")
      return readList(words,wordPositions,len,pos,path);

    if (words[pos] == "[")
      return readArray(words,wordPositions,len,pos,path);

    std::string attributeValue = parseConstValue(words[pos]);
    setAttributeValue(path.c_str(),attributeValue);
    return pos + 1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Removes every attribute whose name matches the given fnmatch pattern. */

void ConfigurationFile::removeAttributes(const char *pattern)
{
  try
  {
    std::vector<T::Attribute>  newAttributeList;

    for (auto& attr : mAttributeList)
    {
      if (fnmatch(pattern,attr.mName.c_str(),0) != 0)
      {
        newAttributeList.emplace_back(attr);
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





namespace
{
/*! \brief Removes the surrounding quotes from the string. */

std::string unquote(const std::string& str)
{
  auto slen = str.length();
  if (slen > 1  &&  str[0] == '"'  &&  str[slen-1] == '"')
    return str.substr(1,slen-2);
  return str;
}



/*! \brief Marks the else section of a condition to be ignored. */

void ignoreElseSection(std::vector<std::string>& words,int len,int pos)
{
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



/*! \brief Checks that the '@endif' or '@else' directive has a matching start of the condition. */

void checkConditionalStart(std::vector<std::string>& words,std::vector<UInt64>& wordPositions,int pos,bool isEndif)
{
  int p = pos-1;
  while (p > 0  &&  words[p] != "@endif"  &&  words[p] != "@else"  &&  words[p] != "@ifdef"  &&  words[p] != "@ifndef")
    p--;

  if (words[p] != "@ifdef"  &&  words[p] != "@ifndef"  &&  (!isEndif  ||  words[p] != "@else"))
  {
    Fmi::Exception exception(BCP,"Unexpected '@endif' found!");
    exception.addParameter("Row",std::to_string(wordPositions[pos] >> 32));
    exception.addParameter("Column",std::to_string(wordPositions[pos] & 0xFFFFFFFF));
    throw exception;
  }
}



/*! \brief The path of the attribute. */

std::string attributePath(const std::string& path,const std::string& attributeName,int index)
{
  std::string newPath = attributeName;
  if (path > " ")
    newPath = path + "." + attributeName;

  if (index >= 0)
    newPath = newPath + "." + std::to_string(index);

  return newPath;
}



/*! \brief Throws an exception about an invalid attribute definition. */

[[noreturn]] void throwInvalidAttribute(std::vector<UInt64>& wordPositions,int len,int pos)
{
  if ((pos+1) < len)
  {
    Fmi::Exception exception(BCP,"Expected ':'' or '=' character!");
    exception.addParameter("Row",std::to_string(wordPositions[pos+1] >> 32));
    exception.addParameter("Column",std::to_string(wordPositions[pos+1] & 0xFFFFFFFF));
    throw exception;
  }
  Fmi::Exception exception(BCP,"Invalid attribute definition!");
  exception.addParameter("Row",std::to_string(wordPositions[pos] >> 32));
  exception.addParameter("Column",std::to_string(wordPositions[pos] & 0xFFFFFFFF));
  throw exception;
}
}  // namespace





/*! \brief Includes the configuration file given after the '@include' directive. */

void ConfigurationFile::includeConfigurationFile(std::vector<std::string>& words,std::vector<UInt64>& wordPositions,int pos)
{
  std::string fname = parseConstValue(words[pos+1]);
  fname = parseValue(fname);

  fname = unquote(fname);


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
    fname = dir + "/" + fname;
  }

  if (mIncludedConfigurationFiles.find(fname) == mIncludedConfigurationFiles.end())
  {
    std::string currentFilename = mCurrentFilename;
    mIncludedConfigurationFiles.insert(fname);
    readFile(fname);
    mCurrentFilename = currentFilename;
  }
}





/*! \brief Processes the '@ifdef' (ifdef=true) or '@ifndef' directive. Returns the position of the
    last processed word. */

int ConfigurationFile::readConditional(std::vector<std::string>& words,std::vector<UInt64>& wordPositions,int len,int pos,bool ifndef)
{
  int startPos = pos;
  std::string attrName = parseValue(words[pos+1]);
  pos = pos + 1;

  bool defined = (findAttribute(attrName.c_str())  ||  getenv(attrName.c_str()) != nullptr);

  if (defined == ifndef)
  {
    // The section should be ignored.
    while (pos < len  &&  words[pos] != "@endif"  &&  words[pos] != "@else")
    {
      pos++;
    }

    if (words[pos] != "@endif"  &&  words[pos] != "@else")
    {
      Fmi::Exception exception(BCP,ifndef ? "Expected '@endif' or '@else' for '@ifndef'!" : "Expected '@endif' or '@else' for '@ifdef'!");
      exception.addParameter("Row",std::to_string(wordPositions[startPos] >> 32));
      exception.addParameter("Column",std::to_string(wordPositions[startPos] & 0xFFFFFFFF));
      throw exception;
    }
  }
  else
  {
    // The section is used. If there is 'else' section in this condition then we should
    // ignore it.

    ignoreElseSection(words,len,pos);
  }
  return pos;
}





/*! \brief Parses one attribute definition or directive (\@include, \@ifdef, etc.) from the word stream. */

int ConfigurationFile::readAttribute(std::vector<std::string>& words,std::vector<UInt64>& wordPositions,int len,int pos,const std::string& path,int index)
{
  FUNCTION_TRACE
  try
  {
    if (pos >= len)
      return pos;

    if ((pos+1) < len  &&  words[pos] == "@include")
    {
      includeConfigurationFile(words,wordPositions,pos);
      pos = pos + 1;
    }
    else if ((pos+1) < len  &&  words[pos] == "@remove")
    {
      std::string pattern = parseValue(words[pos+1]);

      pattern = unquote(pattern);
      removeAttributes(pattern.c_str());

      pos = pos + 1;
    }
    else if ((pos+1) < len  &&  words[pos] == "@print")
    {
      std::string message = parseConstValue(words[pos+1]);
      message = parseValue(message);

      message = unquote(message);
      printf("%s\n",message.c_str());
      pos = pos + 1;
    }
    else if ((pos+1) < len  &&  words[pos] == "@location")
    {
      printf("*** %s [%d:%d]\n",mCurrentFilename.c_str(),C_INT(wordPositions[pos] >> 32),C_INT(wordPositions[pos] & 0xFFFFFFFF));
    }
    else if ((pos+1) < len  &&  words[pos] == "@throw")
    {
      std::string message = parseConstValue(words[pos+1]);
      message = parseValue(message);

      Fmi::Exception exception(BCP,message);
      exception.addParameter("Row",std::to_string(wordPositions[pos] >> 32));
      exception.addParameter("Column",std::to_string(wordPositions[pos] & 0xFFFFFFFF));
      throw exception;
    }
    else if ((pos+1) < len  &&  words[pos] == "@ifdef")
    {
      pos = readConditional(words,wordPositions,len,pos,false);
    }
    else if ((pos+1) < len  &&  words[pos] == "@ifndef")
    {
      pos = readConditional(words,wordPositions,len,pos,true);
    }
    else if (words[pos] == "@endif")
    {
      checkConditionalStart(words,wordPositions,pos,true);
    }
    else if (words[pos] == "@else")
    {
      checkConditionalStart(words,wordPositions,pos,false);
    }
    else if (words[pos] == "@ignore")
    {
    }
    else if ((pos+1) < len  &&  (words[pos+1] == ":" || words[pos+1] == "="))
    {
      std::string newPath = attributePath(path,words[pos],index);

      pos = readValue(words,wordPositions,len,pos+2,newPath);
      return pos;
    }
    else
    {
      throwInvalidAttribute(wordPositions,len,pos);
    }
    return pos+1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



}



