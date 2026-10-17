#include "NetCdfFile.h"
#include "../common/ShowFunction.h"
#include "../grid/GridFile.h"
#include "../grid/PrintOptions.h"
#include "../common/GeneralFunctions.h"
#include "../identification/GridDef.h"
#include <macgyver/StringConversion.h>
#include <macgyver/Exception.h>
#include <macgyver/FastMath.h>
#include <ogr_spatialref.h>
#include <vector>
#include <cmath>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{
namespace NetCDF
{

/*! \brief The constructor of the class. */

NetCdfFile::NetCdfFile()
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

NetCdfFile::~NetCdfFile() = default;





namespace
{
/*! \brief Reads the values of a byte attribute. */

void readByteAttribute(MemoryReader& memoryReader,uint attrCount,std::vector<std::string>& attrValues)
{
  uchar val = 0;
  uint rCount = attrCount;
  if (rCount > 0)
    rCount = ((rCount-1)/4 + 1) * 4;

  for (uint a=0; a<rCount; a++)
  {
    memoryReader >> val;
    // The padding bytes are not values
    if (a < attrCount)
      attrValues.push_back(std::to_string((uint)val));
  }
}



/*! \brief Reads the value of a char attribute. */

void readCharAttribute(MemoryReader& memoryReader,uint attrCount,std::vector<std::string>& attrValues)
{
  std::int8_t val = 0;
  uint rCount = attrCount;
  if (rCount > 0)
    rCount = ((rCount-1)/4 + 1) * 4;

  std::string str(attrCount, '\0');
  for (uint a=0; a<rCount; a++)
  {
    memoryReader >> val;
    if (a < attrCount)
      str[a] = val;
  }
  attrValues.push_back(str);
}



/*! \brief Reads the values of a short attribute. */

void readShortAttribute(MemoryReader& memoryReader,uint attrCount,std::vector<std::string>& attrValues)
{
  short val = 0;
  uint rCount = attrCount;
  if (rCount > 0)
    rCount = ((rCount-1)/2 + 1) * 2;

  for (uint a=0; a<rCount; a++)
  {
    memoryReader >> val;
    if (a < attrCount)
      attrValues.push_back(std::to_string(val));
  }
}



/*! \brief Reads the values of an int, float or double attribute. */

template <class ValueType>
void readNumericAttribute(MemoryReader& memoryReader,uint attrCount,std::vector<std::string>& attrValues)
{
  ValueType val = 0;
  for (uint a=0; a<attrCount; a++)
  {
    memoryReader >> val;
    attrValues.push_back(std::to_string(val));
  }
}
}  // namespace





/*! \brief Reads a single NetCDF attribute (name and typed values) from the memory reader. */

void NetCdfFile::readAttribute(MemoryReader& memoryReader,std::string& attrName,std::vector<std::string>& attrValues)
{
  FUNCTION_TRACE
  try
  {
    uint nameLen = 0;
    memoryReader >> nameLen;

    // The length comes from the file, it must fit in the remaining data
    const auto remaining = C_UINT64(memoryReader.getEndPtr() - memoryReader.getReadPtr());
    if (C_UINT64(nameLen) > remaining)
      throw Fmi::Exception(BCP,"Invalid NetCDF attribute name length!");

    if (nameLen > 0)
      nameLen = ((nameLen-1)/4 + 1) * 4;

    std::string name;
    name.reserve(nameLen);
    for (uint n = 0; n<nameLen; n++)
      name += static_cast<char>(memoryReader.read_int8());

    // NetCDF names may be NUL padded: keep the part before the first NUL
    attrName = name.substr(0, name.find('\0'));


    uint attrType = 0;
    memoryReader >> attrType;

    uint attrCount = 0;
    memoryReader >> attrCount;

    // Every element takes at least one byte of the remaining data
    if (C_UINT64(attrCount) > C_UINT64(memoryReader.getEndPtr() - memoryReader.getReadPtr()))
      throw Fmi::Exception(BCP,"Invalid NetCDF attribute value count!");

    memoryReader.setNetworkByteOrder(true);

    switch (attrType)
    {
      case 1:  // byte
        readByteAttribute(memoryReader,attrCount,attrValues);
        break;

      case 2:  // char
        readCharAttribute(memoryReader,attrCount,attrValues);
        break;

      case 3:  // short
        readShortAttribute(memoryReader,attrCount,attrValues);
        break;

      case 4:  // int
        readNumericAttribute<int>(memoryReader,attrCount,attrValues);
        break;

      case 5:  // float
        readNumericAttribute<float>(memoryReader,attrCount,attrValues);
        break;

      case 6:  // double
        readNumericAttribute<double>(memoryReader,attrCount,attrValues);
        break;
      default:
        break;
    }
    memoryReader.setNetworkByteOrder(false);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}





/*! \brief Reads the requested number of char values from the given file offset. */

void NetCdfFile::readValues(MemoryReader& memoryReader,uint items,UInt64 offset,std::vector<char>& values)
{
  try
  {
    memoryReader.setReadPosition(offset);

    char val = 0;
    for (uint i = 0; i < items; i++)
    {
      val = memoryReader.read_int8();
      values.push_back(val);
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Reads the requested number of unsigned byte values from the given file offset. */

void NetCdfFile::readValues(MemoryReader& memoryReader,uint items,UInt64 offset,std::vector<uchar>& values)
{
  try
  {
    memoryReader.setReadPosition(offset);

    uchar val = 0;
    for (uint i = 0; i < items; i++)
    {
      memoryReader >> val;
      values.push_back(val);
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Reads the requested number of short values from the given file offset. */

void NetCdfFile::readValues(MemoryReader& memoryReader,uint items,UInt64 offset,std::vector<short>& values)
{
  try
  {
    memoryReader.setReadPosition(offset);

    short val = 0;
    for (uint i = 0; i < items; i++)
    {
      memoryReader >> val;
      values.push_back(val);
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Reads the requested number of int values from the given file offset. */

void NetCdfFile::readValues(MemoryReader& memoryReader,uint items,UInt64 offset,std::vector<int>& values)
{
  try
  {
    memoryReader.setReadPosition(offset);

    int val = 0;
    for (uint i = 0; i < items; i++)
    {
      memoryReader >> val;
      values.push_back(val);
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}






/*! \brief Reads the requested number of float values from the given file offset. */

void NetCdfFile::readValues(MemoryReader& memoryReader,uint items,UInt64 offset,std::vector<float>& values)
{
  try
  {
    memoryReader.setReadPosition(offset);

    float val = 0;
    for (uint i = 0; i < items; i++)
    {
      memoryReader >> val;
      values.push_back(val);
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Reads the requested number of double values from the given file offset. */

void NetCdfFile::readValues(MemoryReader& memoryReader,uint items,UInt64 offset,std::vector<double>& values)
{
  try
  {
    memoryReader.setReadPosition(offset);

    double val = 0;
    for (uint i = 0; i < items; i++)
    {
      memoryReader >> val;
      values.push_back(val);
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Reads typed values from the file offset and converts them to scaled float values. */

void NetCdfFile::readValues(MemoryReader& memoryReader,uint type,uint items,UInt64 offset,float baseValue,float scaleFactor,std::vector<float>& values)
{
  try
  {
    memoryReader.setReadPosition(offset);

    switch (type)
    {
      case 1:  // byte
      {
        uchar val = 0;
        for (uint i = 0; i < items; i++)
        {
          memoryReader >> val;
          values.push_back(scaleFactor*(float)val + baseValue);
        }
      }
      break;

      case 2:  // char
      {
        std::int8_t val = 0;
        for (uint i = 0; i < items; i++)
        {
          memoryReader >> val;
          values.push_back(scaleFactor*(float)val + baseValue);
        }
      }
      break;

      case 3:  // short
      {
        short val = 0;
        for (uint i = 0; i < items; i++)
        {
          memoryReader >> val;
          values.push_back(scaleFactor*(float)val + baseValue);
        }
      }
      break;

      case 4:  // int
      {
        int val = 0;
        for (uint i = 0; i < items; i++)
        {
          memoryReader >> val;
          values.push_back(scaleFactor*(float)val + baseValue);
        }
      }
      break;

      case 5:  // float
      {
        float val = 0;
        for (uint i = 0; i < items; i++)
        {
          memoryReader >> val;
          values.push_back(scaleFactor*val + baseValue);
        }
      }
      break;

      case 6:  // double
      {
        double val = 0;
        for (uint i = 0; i < items; i++)
        {
          memoryReader >> val;
          values.push_back(scaleFactor*(float)val + baseValue);
        }
      }
      break;
      default:
        break;
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Reads typed values from the file offset and converts them to scaled double values. */

void NetCdfFile::readValues(MemoryReader& memoryReader,uint type,uint items,UInt64 offset,double baseValue,double scaleFactor,std::vector<double>& values)
{
  try
  {
    memoryReader.setReadPosition(offset);

    switch (type)
    {
      case 1:  // byte
      {
        uchar val = 0;
        for (uint i = 0; i < items; i++)
        {
          memoryReader >> val;
          values.push_back(scaleFactor*(double)val + baseValue);
        }
      }
      break;

      case 2:  // char
      {
        std::int8_t val = 0;
        for (uint i = 0; i < items; i++)
        {
          memoryReader >> val;
          values.push_back(scaleFactor*(double)val + baseValue);
        }
      }
      break;

      case 3:  // short
      {
        short val = 0;
        for (uint i = 0; i < items; i++)
        {
          memoryReader >> val;
          values.push_back(scaleFactor*(double)val + baseValue);
        }
      }
      break;

      case 4:  // int
      {
        int val = 0;
        for (uint i = 0; i < items; i++)
        {
          memoryReader >> val;
          values.push_back(scaleFactor*(double)val + baseValue);
        }
      }
      break;

      case 5:  // float
      {
        float val = 0;
        for (uint i = 0; i < items; i++)
        {
          memoryReader >> val;
          values.push_back(scaleFactor*(double)val + baseValue);
        }
      }
      break;

      case 6:  // double
      {
        double val = 0;
        for (uint i = 0; i < items; i++)
        {
          memoryReader >> val;
          values.push_back(scaleFactor*val + baseValue);
        }
      }
      break;
      default:
        break;
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}





/*! \brief Returns the indexed property value as a string and true if the property exists. */

bool NetCdfFile::getProperty(const std::string& propertyName,uint index,std::string& propertyValue)
{
  FUNCTION_TRACE
  try
  {
    auto prop = mPropertyList.find(propertyName);
    if (prop != mPropertyList.end())
    {
      if (prop->second.size() > index)
      {
        propertyValue = prop->second[0];
        //printf("  *** Property [%s][%s]\n",propertyName.c_str(),propertyValue.c_str());
        return true;
      }
    }
    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Returns the indexed property value as a signed int and true if the property exists. */

bool NetCdfFile::getProperty(const std::string& propertyName,uint index,int& propertyValue)
{
  FUNCTION_TRACE
  try
  {
    auto prop = mPropertyList.find(propertyName);
    if (prop != mPropertyList.end())
    {
      if (prop->second.size() > index)
      {
        propertyValue = toInt32(prop->second[index]);
        return true;
      }
    }
    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Returns the indexed property value as an unsigned int and true if the property exists. */

bool NetCdfFile::getProperty(const std::string& propertyName,uint index,uint& propertyValue)
{
  FUNCTION_TRACE
  try
  {
    auto prop = mPropertyList.find(propertyName);
    if (prop != mPropertyList.end())
    {
      if (prop->second.size() > index)
      {
        propertyValue = toUInt32(prop->second[index]);
        return true;
      }
    }
    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}





/*! \brief Returns the indexed property value as a 64-bit integer and true if the property exists. */

bool NetCdfFile::getProperty(const std::string& propertyName,uint index,Int64& propertyValue)
{
  FUNCTION_TRACE
  try
  {
    auto prop = mPropertyList.find(propertyName);
    if (prop != mPropertyList.end())
    {
      if (prop->second.size() > index)
      {
        propertyValue = toInt64(prop->second[index]);
        return true;
      }
    }
    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Returns the indexed property value as a float and true if the property exists. */

bool NetCdfFile::getProperty(const std::string& propertyName,uint index,float& propertyValue)
{
  FUNCTION_TRACE
  try
  {
    auto prop = mPropertyList.find(propertyName);
    if (prop != mPropertyList.end())
    {
      if (prop->second.size() > index)
      {
        propertyValue = toFloat(prop->second[index]);
        return true;
      }
    }
    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Returns the indexed property value as a double and true if the property exists. */

bool NetCdfFile::getProperty(const std::string& propertyName,uint index,double& propertyValue)
{
  FUNCTION_TRACE
  try
  {
    auto prop = mPropertyList.find(propertyName);
    if (prop != mPropertyList.end())
    {
      if (prop->second.size() > index)
      {
        propertyValue = toDouble(prop->second[index]);
        return true;
      }
    }
    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Inserts a property containing a vector of string values into the property list. */

void NetCdfFile::insertProperty(const std::string& propertyName,const std::vector<std::string>& propertyValue)
{
  FUNCTION_TRACE
  try
  {
    mPropertyList.insert(std::pair<std::string,std::vector<std::string>>(propertyName,propertyValue));
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Inserts a single string-valued property into the property list. */

void NetCdfFile::insertProperty(const std::string& propertyName,const std::string& propertyValue)
{
  FUNCTION_TRACE
  try
  {
    std::vector<std::string> valueVec;
    valueVec.push_back(propertyValue);
    mPropertyList.insert(std::pair<std::string,std::vector<std::string>>(propertyName,valueVec));
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Inserts a signed integer property into the property list. */

void NetCdfFile::insertProperty(const std::string& propertyName,int propertyValue)
{
  FUNCTION_TRACE
  try
  {
    std::vector<std::string> valueVec;
    valueVec.push_back(std::to_string(propertyValue));
    mPropertyList.insert(std::pair<std::string,std::vector<std::string>>(propertyName,valueVec));
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Inserts an unsigned integer property into the property list. */

void NetCdfFile::insertProperty(const std::string& propertyName,uint propertyValue)
{
  FUNCTION_TRACE
  try
  {
    std::vector<std::string> valueVec;
    valueVec.push_back(std::to_string(propertyValue));
    mPropertyList.insert(std::pair<std::string,std::vector<std::string>>(propertyName,valueVec));
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Inserts a 64-bit integer property into the property list. */

void NetCdfFile::insertProperty(const std::string& propertyName,Int64 propertyValue)
{
  FUNCTION_TRACE
  try
  {
    std::vector<std::string> valueVec;
    valueVec.push_back(std::to_string(propertyValue));
    mPropertyList.insert(std::pair<std::string,std::vector<std::string>>(propertyName,valueVec));
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Inserts a double-valued property into the property list. */

void NetCdfFile::insertProperty(const std::string& propertyName,double propertyValue)
{
  FUNCTION_TRACE
  try
  {
    std::vector<std::string> valueVec;
    valueVec.push_back(std::to_string(propertyValue));
    mPropertyList.insert(std::pair<std::string,std::vector<std::string>>(propertyName,valueVec));
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




namespace
{
/*! \brief Reads a name padded to a multiple of 4 bytes. */

std::string readPaddedName(MemoryReader& memoryReader)
{
  uint nameLen = 0;
  memoryReader >> nameLen;
  // The length comes from the file, it must fit in the remaining data
  if (C_UINT64(nameLen) > C_UINT64(memoryReader.getEndPtr() - memoryReader.getReadPtr()))
    throw Fmi::Exception(BCP,"Invalid NetCDF name length!");

  uint paddedLen = nameLen;
  if (nameLen > 0)
    paddedLen = ((nameLen-1)/4 + 1) * 4;

  std::string name(nameLen, '\0');
  for (uint n = 0; n<paddedLen; n++)
  {
    auto val = memoryReader.read_int8();
    if (n < nameLen)
      name[n] = val;
  }
  return name;
}



/*! \brief Reads the dimension indexes of a variable and the corresponding dimension names. */

void readDimensionIndexes(MemoryReader& memoryReader,uint dimIndexCount,const std::vector<std::string>& dimNames,std::vector<std::string>& dimList,std::vector<std::string>& dimList2)
{
  for (uint d=0; d<dimIndexCount; d++)
  {
    uint dim = 0;
    memoryReader >> dim;
    dimList.push_back(std::to_string(dim));
    if (dim < dimNames.size() )
      dimList2.push_back(dimNames[dim]);
  }
}
}  // namespace





/*! \brief Parses the NetCDF header (dimensions, attributes, variables) into the property list. */

void NetCdfFile::readPropertyList(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  try
  {
    int typeSize[] = {0,1,1,2,4,4,8};
    std::string tmp;


    uchar type[5] = {0};
    memoryReader.read_data(type,3);
    if (strcmp((char*)type,"CDF") != 0)
    {
      Fmi::Exception exception(BCP,"Not a NetCDF file!");
      throw exception;
    }

    uchar version = 0;
    memoryReader >> version;

    if (version == 0 || version > 2)
    {
      Fmi::Exception exception(BCP,"Invalid NetCDF version number!");
      exception.addParameter("Version",toString(version));
      throw exception;
    }

    insertProperty("netcdf.version",version);

    uint recordCount = 0;
    memoryReader >> recordCount;


    // ##### Dimensions ########################################################

    uint elemType = 0;
    memoryReader >> elemType;

    uint dimensionCount = 0;
    memoryReader >> dimensionCount;

    if (dimensionCount > 0  &&  elemType != 0x0A)
    {
      Fmi::Exception exception(BCP,"Expected dimension indicator (0x0A)!");
      exception.addParameter("Indicator",std::to_string(elemType));
      throw exception;
    }

    insertProperty("netcdf.dimension.count",dimensionCount);

    std::vector<std::string> dimNames;
    std::vector<std::string> dimLengths;

    //printf("dimensions:\n");
    for (uint t=0; t<dimensionCount; t++)
    {
      std::string name = readPaddedName(memoryReader);

      uint dimLen = 0;
      memoryReader >> dimLen;

      if (dimLen == 0)
        dimLen = recordCount;

      //printf("  [%s][%u]\n",name.c_str(),dimLen);
      dimNames.push_back(name);
      dimLengths.push_back(std::to_string(dimLen));

      insertProperty(name + ".dimension.length", dimLen);
    }

    insertProperty("netcdf.dimension.names",dimNames);
    insertProperty("netcdf.dimension.lengths",dimLengths);

    // ##### Global attributes #################################################

    uint attributeCount = 0;

    memoryReader >> elemType;
    memoryReader >> attributeCount;

    if (attributeCount > 0  &&  elemType != 0x0C)
    {
      Fmi::Exception exception(BCP,"Expected attribute indicator (0x0C)!");
      exception.addParameter("Indicator",std::to_string(elemType));
      throw exception;
    }

    for (uint t=0; t<attributeCount; t++)
    {
      std::string attrName;
      std::vector<std::string> attrValues;
      readAttribute(memoryReader,attrName,attrValues);
      insertProperty("netcdf.attributes." + attrName, attrValues);
    }


    // ##### Variables #########################################################

    std::vector<std::string> variables;
    uint variableCount = 0;

    memoryReader >> elemType;
    memoryReader >> variableCount;

    if (variableCount > 0  &&  elemType != 0x0B)
    {
      Fmi::Exception exception(BCP,"Expected variable indicator (0x0B)!");
      exception.addParameter("Indicator",std::to_string(elemType));
      throw exception;
    }

    for (uint t=0; t<variableCount; t++)
    {
      // Variable name
      std::string varName = readPaddedName(memoryReader);

      variables.push_back(varName);

      // Variable dimension indexes

      uint dimIndexCount = 0;
      memoryReader >> dimIndexCount;

      std::vector<std::string> dimList;
      std::vector<std::string> dimList2;
      readDimensionIndexes(memoryReader,dimIndexCount,dimNames,dimList,dimList2);
      insertProperty(varName + ".dimension.indexes", dimList);
      insertProperty(varName + ".dimension.names", dimList2);

      // Variable attributes

      uint eType = 0;
      uint eCount = 0;

      memoryReader >> eType;
      memoryReader >> eCount;

      if (eCount > 0  &&  eType != 0x0C)
      {
        Fmi::Exception exception(BCP,"Expected attribute indicator (0x0C)!");
        exception.addParameter("Indicator",std::to_string(eType));
        throw exception;
      }

      for (uint t=0; t<eCount; t++)
      {
        std::string attrName;
        std::vector<std::string> attrValues;
        readAttribute(memoryReader,attrName,attrValues);

        insertProperty(varName + "." + attrName, attrValues);
      }

      // Variable value
      uint ncType = 0;
      memoryReader >> ncType;

      uint vSize = 0;
      memoryReader >> vSize;

      Int64 offset = (version == 1 ? memoryReader.read_uint32() : memoryReader.read_uint64());

      if (ncType < 1 || ncType > 6)
        throw Fmi::Exception(BCP,"Invalid NetCDF variable type!");

      uint items = vSize/typeSize[ncType];

      insertProperty(varName + ".type", ncType);
      insertProperty(varName + ".items", items);
      insertProperty(varName + ".offset", offset);
      insertProperty(varName + ".size", vSize);
    }

    insertProperty("netcdf.variables",variables);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}





namespace
{
/*! \brief The dimensions of a grid variable. */

struct VariableDimensions
{
  int timeCount = 0;
  int levelCount = 0;
  int xIndex = 0;
  int yIndex = 0;
  int yCount = 0;
  int xCount = 0;

  std::string timeName;
  std::string levelName;
  std::string xName;
  std::string yName;
  std::string xStandardName;
  std::string yStandardName;
  int paramLevelId = 1;
};



/*! \brief The descriptive attributes of a dimension. */

struct DimensionAttributes
{
  std::string standardName;
  std::string longName;
  std::string units;
  std::string axis;
  std::string positive;
};



/*! \brief Checks if the dimension is the time dimension. */

bool isTimeDimension(const std::string& n,const DimensionAttributes& attr)
{
  return (strcasecmp(attr.standardName.c_str(),"time") == 0 || strcasecmp(attr.longName.c_str(),"time") == 0 || strcasecmp(attr.axis.c_str(),"T") == 0 || strcasecmp(n.c_str(),"time") == 0 || strcasecmp(n.c_str(),"time_counter") == 0);
}



/*! \brief Checks if the dimension is the level dimension. */

bool isLevelDimension(const std::string& n,const DimensionAttributes& attr)
{
  return (strcasecmp(attr.axis.c_str(),"Z") == 0 ||
      strcasecmp(attr.standardName.c_str(),"depth") == 0 || strcasecmp(attr.standardName.c_str(),"height") == 0  || strcasecmp(attr.standardName.c_str(),"level") == 0 ||
      strcasecmp(attr.longName.c_str(),"depth") == 0 || strcasecmp(attr.longName.c_str(),"height") == 0 || strcasecmp(attr.longName.c_str(),"level") == 0  ||
      strcasecmp(n.c_str(),"depth") == 0 || strcasecmp(n.c_str(),"height") == 0 || strcasecmp(n.c_str(),"level") == 0);
}



/*! \brief Checks if the dimension is the y-dimension. */

bool isYDimension(const std::string& n,const DimensionAttributes& attr)
{
  return (strcasecmp(attr.axis.c_str(),"Y") == 0 || strcasecmp(attr.standardName.c_str(),"projection_y_coordinate") == 0 ||
      strcasecmp(attr.standardName.c_str(),"latitude") == 0 || strcasecmp(attr.longName.c_str(),"latitude") == 0 ||
      strcasecmp(n.c_str(),"lat") == 0 || strcasecmp(n.c_str(),"latitude") == 0);
}



/*! \brief Checks if the dimension is the x-dimension. */

bool isXDimension(const std::string& n,const DimensionAttributes& attr)
{
  return (strcasecmp(attr.axis.c_str(),"X") == 0 || strcasecmp(attr.standardName.c_str(),"projection_x_coordinate") == 0 ||
      strcasecmp(attr.standardName.c_str(),"longitude") == 0 || strcasecmp(attr.longName.c_str(),"longitude") == 0 ||
      strcasecmp(n.c_str(),"lon") == 0 || strcasecmp(n.c_str(),"longitude") == 0);
}



/*! \brief The parameter level id of the level dimension. */

int levelDimensionLevelId(const DimensionAttributes& attr,int paramLevelId)
{
  if (strcasecmp(attr.units.c_str(),"m") == 0 || strcasecmp(attr.units.c_str(),"metre") == 0)
  {
    if (strcasecmp(attr.positive.c_str(),"down") == 0)
      return 10;

    return 1;
  }

  if (strcasecmp(attr.units.c_str(),"Pa") == 0 || strcasecmp(attr.units.c_str(),"hPa") == 0)
    return 2;

  return paramLevelId;
}



/*! \brief Classifies the dimension of the variable. */

void addVariableDimension(const std::string& n,const DimensionAttributes& attr,const std::string& dimName,int ii,int iii,VariableDimensions& vd)
{
  if (isTimeDimension(n,attr))
  {
    vd.timeCount = ii;
    vd.timeName = dimName;
  }
  else if (isLevelDimension(n,attr))
  {
    vd.levelCount = ii;
    vd.levelName = dimName;
    vd.paramLevelId = levelDimensionLevelId(attr,vd.paramLevelId);
  }
  else if (isYDimension(n,attr))
  {
    vd.yIndex = iii;
    vd.yCount = ii;
    vd.yName = n;
    vd.yStandardName = attr.standardName;
  }
  else if (isXDimension(n,attr))
  {
    vd.xIndex = iii;
    vd.xCount = ii;
    vd.xName = n;
    vd.xStandardName = attr.standardName;
  }
}



/*! \brief Reads the dimensions of a grid variable. */

void readVariableDimensions(NetCdfFile& file,const std::string& variable,const std::vector<std::string>& indexes,const std::vector<std::string>& dimNames,const std::vector<std::string>& dimLengths,VariableDimensions& vd)
{
  std::string coordStr;
  std::string tmp = variable + ".coordinates";
  if (file.getProperty(tmp,0,coordStr))
  {
    std::vector<std::string> coords;
    splitString(coordStr,' ',coords);
    //printf("--- coordinates size (%s) %lld\n",tmp,coords.size());
    if (coords.size() == 2)
    {
      vd.yName = coords[0];
      vd.xName = coords[1];
      //printf("XNAME [%s] YNAME[%s] [%s]\n",xName.c_str(),yName.c_str(),coordStr.c_str());
    }
  }

  uint iii = 0;
  for (auto itm = indexes.begin(); itm != indexes.end(); ++itm)
  {
    int i = toInt32(itm->c_str());
    // The dimension index comes from the file
    if (i < 0 || C_UINT64(i) >= dimLengths.size() || C_UINT64(i) >= dimNames.size())
      throw Fmi::Exception(BCP,"Invalid NetCDF dimension index!");
    int ii = toInt32(dimLengths[i].c_str());
    // the values may be NUL padded: keep the part before the first NUL
    std::string n = dimNames[i].substr(0, dimNames[i].find('\0'));
    //printf("DIM [%s][%s][%s]\n",itm->c_str(),dimLengths[i].c_str(),dimNames[i].c_str());

    if (strcasecmp(n.c_str(),"x") == 0  &&  !vd.xName.empty())
      n = vd.xName;

    if (strcasecmp(n.c_str(),"y") == 0  &&  !vd.yName.empty())
      n = vd.yName;

    DimensionAttributes attr;
    file.getProperty(n + ".standard_name", 0, attr.standardName);
    file.getProperty(n + ".long_name", 0, attr.longName);
    file.getProperty(n + ".units", 0, attr.units);
    file.getProperty(n + ".axis", 0, attr.axis);
    file.getProperty(n + ".positive", 0, attr.positive);

    addVariableDimension(n,attr,dimNames[i],ii,iii,vd);

    //printf("  %s (%s,%d)\n",itm->c_str(),dimNames[i].c_str(),ii);
    iii++;
  }
}



/*! \brief The scale of the coordinates in the given units (kilometres are converted into metres). */

double coordinateScale(const std::string& unitsStr)
{
  double scale = 1.0;
  if (!unitsStr.empty())
  {
    double value = 0.0;
    std::string units;
    parseUnits(unitsStr.c_str(),value,units);
    // printf("X-UNIT [%f][%s]\n",value,units.c_str());
    if (value == 0.0)
      value = 1.0;

    if (strcasecmp(units.c_str(),"km") == 0)
      scale = value * 1000;
  }
  return scale;
}



/*! \brief The data storage properties of a variable. */

struct VariableData
{
  uint type = 0;
  uint size = 0;
  Int64 offset = 0;
  uint itemCount = 0;
  double scaleFactor = 1;
  double baseValue = 0;
};



/*! \brief Reads the data storage properties of the variable. */

void readVariableData(NetCdfFile& file,const std::string& name,VariableData& data)
{
  file.getProperty(name + ".type", 0, data.type);
  file.getProperty(name + ".size", 0, data.size);
  file.getProperty(name + ".add_offset", 0, data.baseValue);
  file.getProperty(name + ".scale_factor", 0, data.scaleFactor);
  file.getProperty(name + ".offset", 0, data.offset);
  file.getProperty(name + ".items", 0, data.itemCount);
}



/*! \brief Reads the forecast times of the variable. */

void readTimeList(NetCdfFile& file,MemoryReader& memoryReader,const std::string& timeName,int timeCount,std::vector<time_t>& timeList)
{
  int year = 0;
  int month = 0;
  int day = 0;
  int hour = 0;
  int minute = 0;
  int second = 0;
  time_t unitSize = 0;

  std::string time_units;
  if (file.getProperty(timeName + ".units", 0, time_units))
  {
    parseNetCdfTime(time_units,year,month,day,hour,minute,second,unitSize);
    // printf("TIME %04d%02d%02dT%02d%02d%02d  %ld\n",year,month,day,hour,minute,second,unitSize);
  }
  else
  {
    printf("*** TIME UNITS MISSING\n");
    // Time units missing
  }

  VariableData data;
  readVariableData(file,timeName,data);

  std::vector<double> timeValues;
  //printf("READ TIME %f %f\n",baseValue,scaleFactor);
  file.readValues(memoryReader,data.type,data.itemCount,data.offset,data.baseValue,data.scaleFactor,timeValues);

  uint tc = timeCount;
  if (data.itemCount > 1)
    tc = 1;

  // Every time step needs data, so the step count cannot exceed the file size
  if (timeCount < 0 || C_UINT64(tc) * std::max<UInt64>(1, timeValues.size()) > memoryReader.getDataSize())
    throw Fmi::Exception(BCP,"Invalid NetCDF time dimension!");

  for (uint t=0; t<tc; t++)
  {
    for (double & timeValue : timeValues)
    {
      // The values come from the file, they must be convertible to time_t
      if (!std::isfinite(timeValue) || std::fabs(timeValue) > 1e12)
        throw Fmi::Exception(BCP,"Invalid NetCDF time value!");
      time_t ttt = (time_t)timeValue*unitSize+(time_t)t*unitSize;
      //printf("TimeT %ld %f %ld\n",ttt,*v,unitSize);
      time_t tt = getGregorianTimeT(year,month,day,hour,minute,second,ttt);
      timeList.push_back(tt);

      //std::string tm = utcTimeFromTimeT(tt);
      //printf("  Time %f => %ld => %s\n",*v,tt,tm.c_str());
    }
  }
}



/*! \brief Reads the levels of the variable. */

void readLevelList(NetCdfFile& file,MemoryReader& memoryReader,const std::string& levelName,int levelCount,std::vector<double>& levelList)
{
  if (levelCount <= 0)
  {
    levelList.push_back(0.0);
    return;
  }

  VariableData data;
  readVariableData(file,levelName,data);

  file.readValues(memoryReader,data.type,data.itemCount,data.offset,data.baseValue,data.scaleFactor,levelList);

  // The level values are stored as integers
  for (auto lv : levelList)
    if (!std::isfinite(lv) || std::fabs(lv) > 2e9)
      throw Fmi::Exception(BCP,"Invalid NetCDF level value!");
}



/*! \brief Reads the y-coordinates. The coordinates may be stored as a 2-dimensional array,
    in which case the values of the first column are used. */

void readYCoordinates(NetCdfFile& file,MemoryReader& memoryReader,const std::string& yName,int xCount,int yCount,double yScale,FloatVec& yCoordinates)
{
  VariableData data;
  readVariableData(file,yName,data);

  if ((int)data.itemCount == yCount)
  {
    file.readValues(memoryReader,data.type,data.itemCount,data.offset,data.baseValue,data.scaleFactor*yScale,yCoordinates);
  }
  else if (xCount > 0 && ((int)data.itemCount/xCount) == yCount)
  {
    FloatVec coordinates;
    file.readValues(memoryReader,data.type,data.itemCount,data.offset,data.baseValue,data.scaleFactor*yScale,coordinates);
    for (uint t=0; t<data.itemCount; t=t+xCount)
    {
      yCoordinates.push_back(coordinates[t]);
    }
  }
}



/*! \brief The coordinate step from the first and last coordinate, or from the first pair of
    non-missing coordinates. */

double coordinateStep(const FloatVec& coordinates,float missingValue)
{
  uint sz = coordinates.size() - 1;

  if (coordinates[sz] != missingValue  &&  coordinates[0] != missingValue)
    return (coordinates[sz] - coordinates[0]) / (double)sz;

  for (uint t=0; t<sz; t++)
  {
    if (coordinates[t] != missingValue  &&  coordinates[t+1] != missingValue)
      return (coordinates[t+1] - coordinates[t]);
  }
  return 0;
}



/*! \brief Transforms the start point from the projection into latlon. */

void transformToLatLon(OGRSpatialReference& sp,OGRSpatialReference& latlonSp,double& startx,double& starty)
{
  sp.SetTargetLinearUnits("PROJCS", SRS_UL_METER, 1.0);
  sp.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

  OGRCoordinateTransformation *transformation = OGRCreateCoordinateTransformation(&sp,&latlonSp);
  transformation->Transform(1,&startx,&starty);
  OCTDestroyCoordinateTransformation(transformation);
}



/*! \brief Finds the geometry id by the geometry string. If the geometry is not configured, the
    line to be added to the geometry definition file is printed. */

int findGeometryId(const char *projectionString,const char *configurationLine)
{
  auto def = Identification::gridDef.getGrib2DefinitionByGeometryString(projectionString);
  if (def)
    return def->getGridGeometryId();

  std::cout << "#### Geometry not found ####\n";
  std::cout << "** Add the following line into the geometry definition file (=> fill id,name and description fields) :\n\n";
  std::cout << configurationLine << "\n";
  return 0;
}



/*! \brief The grid geometry of the variable. */

struct GridGeometry
{
  NetCdfFile& file;
  const std::string& gridMapping;
  OGRSpatialReference& latlonSp;
  const FloatVec& xCoordinates;
  const FloatVec& yCoordinates;
  double startx;
  double starty;
  double dx;
  double dy;
  const char *sm;

  double property(const char *name,double defaultValue) const
  {
    double value = defaultValue;
    file.getProperty(gridMapping + name, 0, value);
    return value;
  }
};



/*! \brief PROJECTION: Polar stereograpic */

int polarStereographicGeometryId(GridGeometry g)
{
  double longitude_of_projection_origin = g.property(".longitude_of_projection_origin",0.0);
  double latitude_of_projection_origin = g.property(".latitude_of_projection_origin",0.0);
  double scale_factor_at_projection_origin = g.property(".scale_factor_at_projection_origin",0.0);
  double straight_vertical_longitude_from_pole = g.property(".straight_vertical_longitude_from_pole",0.0);
  double false_easting = g.property(".false_easting",0.0);
  double false_northing = g.property(".false_northing",0.0);

  OGRSpatialReference sp;
  sp.SetPS(latitude_of_projection_origin,longitude_of_projection_origin,scale_factor_at_projection_origin,false_easting,false_northing);
  transformToLatLon(sp,g.latlonSp,g.startx,g.starty);

  char projectionString[4000];
  snprintf(projectionString,sizeof(projectionString),"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;description",
      T::GridProjectionValue::PolarStereographic,(int)g.xCoordinates.size(),(int)g.yCoordinates.size(),
      g.startx,g.starty,fabs(g.dx),fabs(g.dy),g.sm,straight_vertical_longitude_from_pole,latitude_of_projection_origin);

  return findGeometryId(projectionString,projectionString);
}



/*! \brief PROJECTION: Lambert Azimuthal Equal Area */

int lambertAzimuthalEqualAreaGeometryId(GridGeometry g)
{
  g.dx = g.xCoordinates[1] - g.xCoordinates[0];
  g.dy = g.yCoordinates[1] - g.yCoordinates[0];

  double longitude_of_projection_origin = g.property(".longitude_of_projection_origin",0.0);
  double latitude_of_projection_origin = g.property(".latitude_of_projection_origin",0.0);
  double false_easting = g.property(".false_easting",0.0);
  double false_northing = g.property(".false_northing",0.0);

  OGRSpatialReference sp;
  sp.SetLAEA(latitude_of_projection_origin,longitude_of_projection_origin,false_easting,false_northing);
  transformToLatLon(sp,g.latlonSp,g.startx,g.starty);

  char projectionString[4000];
  snprintf(projectionString,sizeof(projectionString),"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;description",
      T::GridProjectionValue::LambertAzimuthalEqualArea,(int)g.xCoordinates.size(),(int)g.yCoordinates.size(),
      g.startx,g.starty,fabs(g.dx),fabs(g.dy),g.sm,latitude_of_projection_origin,longitude_of_projection_origin);

  char tmp[4000];
  snprintf(tmp,sizeof(tmp),"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;0.000000;0.000000;description",
      T::GridProjectionValue::LambertAzimuthalEqualArea,(int)g.xCoordinates.size(),(int)g.yCoordinates.size(),
      g.startx,g.starty,fabs(g.dx),fabs(g.dy),g.sm,latitude_of_projection_origin,longitude_of_projection_origin);

  return findGeometryId(projectionString,tmp);
}



/*! \brief PROJECTION: Lambert Conformal */

int lambertConformalGeometryId(GridGeometry g)
{
  g.dx = (g.xCoordinates[1] - g.xCoordinates[0])*1000;
  g.dy = (g.yCoordinates[1] - g.yCoordinates[0])*1000;

  double standard_parallel = g.property(".standard_parallel",0.0);
  double longitude_of_central_meridian = g.property(".longitude_of_central_meridian",0.0);
  double longitude_of_projection_origin = g.property(".longitude_of_projection_origin",0.0);
  double latitude_of_projection_origin = g.property(".latitude_of_projection_origin",0.0);
  double false_easting = g.property(".false_easting",0.0);
  double false_northing = g.property(".false_northing",0.0);
  double earth_radius = g.property(".earth_radius",6371229.0);
  (void)earth_radius;

  OGRSpatialReference sp;
  sp.SetLCC(standard_parallel,longitude_of_central_meridian,latitude_of_projection_origin,longitude_of_projection_origin,false_easting,false_northing);
  transformToLatLon(sp,g.latlonSp,g.startx,g.starty);

  double sx = 0.0;
  double sy = -90.0;

  //# LAMBERT CONFORMAL : projection,id,name,ni,nj,first_lon,first_lat,di,dj,scanning_mode,orientation,latin1,latin2,south_pole_lon,south_pole_lat,LaD,earthSemiMajor,earthSemiMinor,description
  char projectionString[4000];
  snprintf(projectionString,sizeof(projectionString),"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;%.6f;%.6f;%.6f;%.6f;description",
    T::GridProjectionValue::LambertConformal,(int)g.xCoordinates.size(),(int)g.yCoordinates.size(),g.startx,g.starty,fabs(g.dx),fabs(g.dy),
    g.sm,longitude_of_central_meridian,latitude_of_projection_origin,latitude_of_projection_origin,sx,sy,latitude_of_projection_origin);

  return findGeometryId(projectionString,projectionString);
}



/*! \brief PROJECTION: Latlon */

int latLonGeometryId(GridGeometry g)
{
  char projectionString[4000];
  snprintf(projectionString,sizeof(projectionString),"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;description",
    T::GridProjectionValue::LatLon,(int)g.xCoordinates.size(),(int)g.yCoordinates.size(),
    g.startx,g.starty,fabs(g.dx),fabs(g.dy),g.sm);

  char tmp[4000];
  snprintf(tmp,sizeof(tmp),"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;0.000000;0.000000;description",
    T::GridProjectionValue::LatLon,(int)g.xCoordinates.size(),(int)g.yCoordinates.size(),
    g.startx,g.starty,fabs(g.dx),fabs(g.dy),g.sm);

  return findGeometryId(projectionString,tmp);
}



/*! \brief Resolves the projection and the geometry of the variable. */

void resolveProjection(GridGeometry g,const VariableDimensions& vd,int& projectionId,int& geometryId)
{
  std::string mappingName;
  g.file.getProperty(g.gridMapping + ".grid_mapping_name", 0, mappingName);

  if (strcasecmp(mappingName.c_str(),"polar_stereographic") == 0 || strcasecmp(mappingName.c_str(),"stereographic") == 0)
  {
    projectionId = T::GridProjectionValue::PolarStereographic;
    geometryId = polarStereographicGeometryId(g);
  }
  else if (strcasecmp(mappingName.c_str(),"lambert_azimuthal_equal_area") == 0)
  {
    projectionId = T::GridProjectionValue::LambertAzimuthalEqualArea;
    geometryId = lambertAzimuthalEqualAreaGeometryId(g);
  }
  else if (strcasecmp(mappingName.c_str(),"lambert_conformal_conic") == 0)
  {
    projectionId = T::GridProjectionValue::LambertConformal;
    geometryId = lambertConformalGeometryId(g);
  }
  else if (strcasecmp(mappingName.c_str(),"latitude_longitude") == 0 ||
      (mappingName.empty() &&  strcasecmp(vd.xStandardName.c_str(),"longitude") == 0   &&  strcasecmp(vd.yStandardName.c_str(),"latitude") == 0))
  {
    projectionId = T::GridProjectionValue::LatLon;
    geometryId = latLonGeometryId(g);
  }
}



/*! \brief The scanning mode string of the coordinate steps. */

std::string scanningMode(double dx,double dy)
{
  char sm[100];
  char *p = sm;

  if (dx < 0)
    p += sprintf(p,"-x");
  else
    p += sprintf(p,"+x");

  if (dy < 0)
    sprintf(p,"-y");
  else
    sprintf(p,"+y");

  return sm;
}



/*! \brief Creates the message infos of the variable for each time and level. */

void addMessageInfos(MemoryReader& memoryReader,const MessageInfo& info,Int64 dataStartOffset,uint dataSize,int levelCount,const std::vector<time_t>& timeList,const std::vector<double>& levelList,MessageInfoVec& messageInfoList)
{
  for (auto tIt : timeList)
  {
    for (auto lIt : levelList)
    {
      if (C_UINT64(dataStartOffset) + dataSize > memoryReader.getDataSize())
        throw Fmi::Exception(BCP,"NetCDF data is outside of the file!");

      MessageInfo msg(info);
      msg.mFilePosition = dataStartOffset;
      msg.mParameterLevel = lIt;
      msg.mForecastTimeT = tIt;
      messageInfoList.push_back(msg);
      dataStartOffset += dataSize;
    }
    dataStartOffset += levelCount;
  }
}



/*! \brief Creates the message infos of a grid variable. */

void createVariableMessageInfos(NetCdfFile& file,MemoryReader& memoryReader,const std::string& variable,const std::vector<std::string>& indexes,const std::vector<std::string>& dimNames,const std::vector<std::string>& dimLengths,OGRSpatialReference& latlonSp,FloatVec& xCoordinates,FloatVec& yCoordinates,MessageInfoVec& messageInfoList)
{
  int typeSize[] = {0,1,1,2,4,4,8};

  VariableDimensions vd;
  readVariableDimensions(file,variable,indexes,dimNames,dimLengths,vd);

  //printf("%s %s:%d,%s:%d,%s:%d,%s:%d\n",it->c_str(),timeName.c_str(),timeCount,levelName.c_str(),levelCount,yName.c_str(),yCount,xName.c_str(),xCount);

  float xMissingValue = ParamValueMissing;
  float yMissingValue = ParamValueMissing;

  Int64 dataStartOffset = 0;
  file.getProperty(variable + ".offset", 0, dataStartOffset);

  uint dataType = 0;
  file.getProperty(variable + ".type", 0, dataType);

  double dataBaseValue = 0;
  file.getProperty(variable + ".add_offset", 0, dataBaseValue);

  double dataScaleFactor = 1;
  file.getProperty(variable + ".scale_factor", 0, dataScaleFactor);

  float missingValue = ParamValueMissing;
  if (!file.getProperty(variable + ".missing_value", 0, missingValue))
    file.getProperty(variable + "._FillValue", 0, missingValue);

  if (!file.getProperty(vd.xName + ".missing_value", 0, xMissingValue))
    file.getProperty(vd.xName + "._FillValue", 0, xMissingValue);

  if (!file.getProperty(vd.yName + ".missing_value", 0, yMissingValue))
    file.getProperty(vd.yName + "._FillValue", 0, yMissingValue);

  std::string xUnits;
  file.getProperty(vd.xName + ".units", 0, xUnits);

  std::string yUnits;
  file.getProperty(vd.yName + ".units", 0, yUnits);

  std::string dataUnits;
  file.getProperty(variable + ".units", 0, dataUnits);

  std::string parameterStandardName;
  file.getProperty(variable + ".standard_name", 0, parameterStandardName);

  std::string gridMapping;
  file.getProperty(variable + ".grid_mapping", 0, gridMapping);

  // The dimensions come from the file
  if (vd.xCount <= 0 || vd.yCount <= 0)
    throw Fmi::Exception(BCP,"Invalid NetCDF grid dimensions!");
  const UInt64 dataSize64 = C_UINT64(vd.xCount) * C_UINT64(vd.yCount) * C_UINT64(typeSize[dataType]);
  if (dataSize64 > 0xFFFFFFFFULL)
    throw Fmi::Exception(BCP,"NetCDF grid is too large!");
  uint dataSize = C_UINT(dataSize64);

  double xScale = coordinateScale(xUnits);
  double yScale = coordinateScale(yUnits);

  // ##### Time information ##############################################

  std::vector<time_t> timeList;
  readTimeList(file,memoryReader,vd.timeName,vd.timeCount,timeList);

  // ##### Level information #############################################

  Identification::NetCdfParameterDef ncParamDef;
  if (Identification::gridDef.getNetCdfParameterDefByName(parameterStandardName,ncParamDef)  &&  !ncParamDef.mFmiLevelId.empty())
    vd.paramLevelId = toInt32(ncParamDef.mFmiLevelId.c_str());

  std::vector<double> levelList;
  readLevelList(file,memoryReader,vd.levelName,vd.levelCount,levelList);

  // ##### X-coordinates #################################################

  if (xCoordinates.empty())
  {
    VariableData data;
    readVariableData(file,vd.xName,data);
    file.readValues(memoryReader,data.type,vd.xCount,data.offset,data.baseValue,data.scaleFactor*xScale,xCoordinates);
  }

  // ##### Y-coordinates #################################################

  if (yCoordinates.empty())
    readYCoordinates(file,memoryReader,vd.yName,vd.xCount,vd.yCount,yScale,yCoordinates);

  if (xCoordinates.empty() || yCoordinates.empty())
  {
    Fmi::Exception exception(BCP,"X- or Y-coordinates missing!");
    exception.addParameter("Number of X-coordinates",std::to_string(xCoordinates.size()));
    exception.addParameter("Number of Y-coordinates",std::to_string(yCoordinates.size()));
    throw exception;
  }

  // ##### Projection ####################################################

  double dx = coordinateStep(xCoordinates,xMissingValue);
  double dy = coordinateStep(yCoordinates,yMissingValue);
  std::string sm = scanningMode(dx,dy);

  int projectionId = 0;
  int geometryId = 0;

  GridGeometry geometry{file,gridMapping,latlonSp,xCoordinates,yCoordinates,xCoordinates[0],yCoordinates[0],dx,dy,sm.c_str()};
  resolveProjection(geometry,vd,projectionId,geometryId);

  // ##### Creating message infos ########################################

  MessageInfo info;
  info.mProjectionId = projectionId;
  info.mMessageType = T::FileTypeValue::NetCdf3;
  info.mGeometryId = geometryId;
  info.mMessageSize = dataSize;
  info.mColumns = vd.xCount;
  info.mRows = vd.yCount;
  if (vd.xIndex > vd.yIndex)
  {
    info.mColumnMultiplier = vd.xCount;
    info.mRowMultiplier = 1;
  }
  else
  {
    info.mColumnMultiplier = 1;
    info.mRowMultiplier = vd.yCount;
  }
  info.mDataType = dataType;
  info.mBaseValue = dataBaseValue;
  info.mScaleFactor = dataScaleFactor;
  info.mParameterName = variable;

  info.mParameterStandardName = parameterStandardName;

  info.mParameterUnits = dataUnits;
  info.mParameterLevelId = vd.paramLevelId;
  info.mForecastType = 1;
  info.mForecastNumber = 0;
  info.mMissingValue = missingValue;

  addMessageInfos(memoryReader,info,dataStartOffset,dataSize,vd.levelCount,timeList,levelList,messageInfoList);
}
}  // namespace





/*! \brief Builds MessageInfo entries for each grid variable, time step and level in the file. */

void NetCdfFile::createMessageInfoList(MemoryReader& memoryReader,MessageInfoVec& messageInfoList)
{
  FUNCTION_TRACE
  try
  {
    std::string tmp;

    OGRSpatialReference latlonSp;
    latlonSp.importFromEPSG(4326);
    latlonSp.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

    auto d = mPropertyList.find("netcdf.variables");
    auto dn = mPropertyList.find("netcdf.dimension.names");
    auto dl = mPropertyList.find("netcdf.dimension.lengths");

    if (d == mPropertyList.end() || dn == mPropertyList.end() || dl == mPropertyList.end())
      return;

    for (auto it = d->second.begin(); it != d->second.end(); ++it)
    {
      tmp = *it + ".dimension.indexes";
      auto dd = mPropertyList.find(tmp);
      //printf("INDEXES [%s] %ld\n",tmp,dd->second.size());
      // A grid variable has 3 or 4 dimensions
      if (dd != mPropertyList.end()  &&  (dd->second.size() == 3 || dd->second.size() == 4))
        createVariableMessageInfos(*this,memoryReader,*it,dd->second,dn->second,dl->second,latlonSp,mXCoordinates,mYCoordinates,messageInfoList);
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader    This object controls the access to the memory mapped file.
        \param messageInfoList Output list populated with one entry per parameter/level/time slice.
*/

void NetCdfFile::read(MemoryReader& memoryReader,MessageInfoVec& messageInfoList)
{
  try
  {
    readPropertyList(memoryReader);
    //print(std::cout,0,0);
    createMessageInfoList(memoryReader,messageInfoList);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief Collects all properties belonging to a NetCDF variable into the given attribute list. */

void NetCdfFile::getAttributeList(const char *variableName,const std::string& prefix,T::AttributeList& attributeList) const
{
  try
  {
    uint len = strlen(variableName);
    for (const auto& pr : mPropertyList)
    {
      const char *s = pr.first.c_str();
      if (strncasecmp(s,variableName,len) == 0 &&  s[len] == '.')
      {
        // The attribute names and values come from the file and may be long
        std::string value;
        for (auto it = pr.second.begin(); it != pr.second.end(); ++it)
        {
          if (it != pr.second.begin())
            value += " ";
          value += *it;
        }

        std::string name = prefix + s;
        attributeList.addAttribute(name.c_str(), value);
      }
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}



/*! \brief The method prints the content of the current object into the given stream.

        \param stream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void NetCdfFile::print(std::ostream& stream,uint level,uint /*optionFlags*/) const
{
  try
  {
    stream << space(level) << "NetCdfFile\n";
    stream << space(level) << "- mPropertyList = \n";

    for (const auto& pr : mPropertyList)
    {
      stream << space(level+2) <<  pr.first << " : ";
      for (auto it = pr.second.begin(); it != pr.second.end(); ++it)
      {
        stream << "[" << *it << "]";
      }
      stream << "\n";
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




}
}
