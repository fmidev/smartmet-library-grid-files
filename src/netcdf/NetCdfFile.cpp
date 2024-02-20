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

NetCdfFile::~NetCdfFile()
{
}









#if 0


bool NetCdfFile::getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    if (grid_i >= mXCoordinates.size() || grid_j >= mYCoordinates.size())
      return false;

    x = mXCoordinates[grid_i];
    y = mYCoordinates[grid_j];

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool NetCdfFile::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    if (grid_i < 0 || grid_j < 0 || grid_i >= (double)mXCoordinates.size() || grid_j >= (double)mYCoordinates.size() || mYCoordinates.size() <= 1 || mXCoordinates.size() <= 1)
      return false;

    double dy = mYCoordinates[1] - mYCoordinates[0];
    double dx = mXCoordinates[1] - mXCoordinates[0];

    y = mYCoordinates[0] + grid_j * dy;
    x = mXCoordinates[0] + grid_i * dx;

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




bool NetCdfFile::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    if (mYCoordinates.size() <= 1 || mXCoordinates.size() <= 1)
      return false;

    if (x < 0)
      x = x + 360;

    double dy = mYCoordinates[1] - mYCoordinates[0];
    double dx = mXCoordinates[1] - mXCoordinates[0];

    double diffX = x - mXCoordinates[0];
    double diffY = y - mYCoordinates[0];

    double i = diffX / dx;
    double j = diffY / dy;

    grid_i = i;
    grid_j = j;

    //printf("%f,%f => %f,%f\n",x,y,grid_i,grid_j);

    if (i < 0 ||  j < 0  ||  i >= C_DOUBLE(mXCoordinates.size()) ||  j >= C_DOUBLE(mYCoordinates.size()))
      return false;

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



#endif


void NetCdfFile::readAttribute(MemoryReader& memoryReader,std::string& attrName,std::vector<std::string>& attrValues)
{
  FUNCTION_TRACE
  try
  {
    uint nameLen = 0;
    memoryReader >> nameLen;
    if (nameLen > 0)
      nameLen = ((nameLen-1)/4 + 1) * 4;

    char name[nameLen+1];
    for (uint n = 0; n<nameLen; n++)
      name[n] = memoryReader.read_int8();

    name[nameLen] = '\0';
    attrName = name;


    uint attrType = 0;
    memoryReader >> attrType;

    uint attrCount = 0;
    memoryReader >> attrCount;

    memoryReader.setNetworkByteOrder(true);

    switch (attrType)
    {
      case 1:  // byte
      {
        uchar val = 0;
        uint rCount = attrCount;
        if (rCount > 0)
          rCount = ((rCount-1)/4 + 1) * 4;

        for (uint a=0; a<rCount; a++)
        {
          memoryReader >> val;
          if (a < rCount)
            attrValues.push_back(std::to_string((uint)val));
        }
      }
      break;

      case 2:  // char
      {
        std::int8_t val = 0;
        uint rCount = attrCount;
        if (rCount > 0)
          rCount = ((rCount-1)/4 + 1) * 4;

        char str[rCount+1];
        for (uint a=0; a<rCount; a++)
        {
          memoryReader >> val;
          if (a < attrCount)
            str[a] = val;
        }
        str[attrCount] = '\0';
        attrValues.push_back(std::string(str));
      }
      break;

      case 3:  // short
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
      break;

      case 4:  // int
      {
        int val = 0;
        for (uint a=0; a<attrCount; a++)
        {
          memoryReader >> val;
          attrValues.push_back(std::to_string(val));
        }
      }
      break;

      case 5:  // float
      {
        float val = 0;
        for (uint a=0; a<attrCount; a++)
        {
          memoryReader >> val;
          attrValues.push_back(std::to_string(val));
        }
      }
      break;

      case 6:  // double
      {
        double val = 0;
        for (uint a=0; a<attrCount; a++)
        {
          memoryReader >> val;
          attrValues.push_back(std::to_string(val));
        }
      }
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





void NetCdfFile::readValues(MemoryReader& memoryReader,uint items,ulonglong offset,std::vector<char>& values)
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




void NetCdfFile::readValues(MemoryReader& memoryReader,uint items,ulonglong offset,std::vector<uchar>& values)
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




void NetCdfFile::readValues(MemoryReader& memoryReader,uint items,ulonglong offset,std::vector<short>& values)
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




void NetCdfFile::readValues(MemoryReader& memoryReader,uint items,ulonglong offset,std::vector<int>& values)
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






void NetCdfFile::readValues(MemoryReader& memoryReader,uint items,ulonglong offset,std::vector<float>& values)
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




void NetCdfFile::readValues(MemoryReader& memoryReader,uint items,ulonglong offset,std::vector<double>& values)
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




void NetCdfFile::readValues(MemoryReader& memoryReader,uint type,uint items,ulonglong offset,float baseValue,float scaleFactor,std::vector<float>& values)
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
          values.push_back(scaleFactor*(float)val + baseValue);
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
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




void NetCdfFile::readValues(MemoryReader& memoryReader,uint type,uint items,ulonglong offset,double baseValue,double scaleFactor,std::vector<double>& values)
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
          values.push_back(scaleFactor*(double)val + baseValue);
        }
      }
      break;
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}





bool NetCdfFile::getProperty(std::string propertyName,uint index,std::string& propertyValue)
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




bool NetCdfFile::getProperty(std::string propertyName,uint index,int& propertyValue)
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




bool NetCdfFile::getProperty(std::string propertyName,uint index,uint& propertyValue)
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





bool NetCdfFile::getProperty(std::string propertyName,uint index,longlong& propertyValue)
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




bool NetCdfFile::getProperty(std::string propertyName,uint index,float& propertyValue)
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




bool NetCdfFile::getProperty(std::string propertyName,uint index,double& propertyValue)
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




void NetCdfFile::insertProperty(std::string propertyName,std::vector<std::string>& propertyValue)
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




void NetCdfFile::insertProperty(std::string propertyName,std::string propertyValue)
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




void NetCdfFile::insertProperty(std::string propertyName,int propertyValue)
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




void NetCdfFile::insertProperty(std::string propertyName,uint propertyValue)
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




void NetCdfFile::insertProperty(std::string propertyName,longlong propertyValue)
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




void NetCdfFile::insertProperty(std::string propertyName,double propertyValue)
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




void NetCdfFile::readPropertyList(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  try
  {
    int typeSize[] = {0,1,1,2,4,4,8};
    char tmp[1000];


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
      uint nameLen = 0;
      memoryReader >> nameLen;
      if (nameLen > 0)
        nameLen = ((nameLen-1)/4 + 1) * 4;

      char name[nameLen+1];
      for (uint n = 0; n<nameLen; n++)
        name[n] = memoryReader.read_int8();

      name[nameLen] = '\0';

      uint dimLen = 0;
      memoryReader >> dimLen;

      if (dimLen == 0)
        dimLen = recordCount;

      //printf("  [%s][%u]\n",name,dimLen);
      dimNames.push_back(std::string(name));
      dimLengths.push_back(std::to_string(dimLen));

      sprintf(tmp,"%s.dimension.length",name);
      insertProperty(tmp,dimLen);
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
      sprintf(tmp,"netcdf.attributes.%s",attrName.c_str());
      insertProperty(tmp,attrValues);
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
      uint nameLen = 0;
      memoryReader >> nameLen;
      if (nameLen > 0)
        nameLen = ((nameLen-1)/4 + 1) * 4;

      char varName[nameLen+1];
      for (uint n = 0; n<nameLen; n++)
        varName[n] = memoryReader.read_int8();

      varName[nameLen] = '\0';
      variables.push_back(std::string(varName));

      // Variable dimension indexes

      uint dimIndexCount = 0;
      memoryReader >> dimIndexCount;

      std::vector<std::string> dimList;
      std::vector<std::string> dimList2;
      for (uint d=0; d<dimIndexCount; d++)
      {
        uint dim = 0;
        memoryReader >> dim;
        dimList.push_back(std::to_string(dim));
        if (dim < dimNames.size() )
          dimList2.push_back(dimNames[dim]);
      }
      sprintf(tmp,"%s.dimension.indexes",varName);
      insertProperty(tmp,dimList);

      sprintf(tmp,"%s.dimension.names",varName);
      insertProperty(tmp,dimList2);

      // Variable attributes

      uint eType = 0;
      uint eCount = 0;

      memoryReader >> eType;
      memoryReader >> eCount;

      if (eCount > 0  &&  eType != 0x0C)
      {
        Fmi::Exception exception(BCP,"Expected attribute indicator (0x0C)!");
        exception.addParameter("Indicator",std::to_string(elemType));
        throw exception;
      }

      for (uint t=0; t<eCount; t++)
      {
        std::string attrName;
        std::vector<std::string> attrValues;
        readAttribute(memoryReader,attrName,attrValues);

        sprintf(tmp,"%s.%s",varName,attrName.c_str());
        insertProperty(tmp,attrValues);
      }

      // Variable value
      uint ncType = 0;
      memoryReader >> ncType;

      uint vSize = 0;
      memoryReader >> vSize;

      longlong offset = 0;

      if (version == 1)
        offset = memoryReader.read_uint32();
      else
        offset = memoryReader.read_uint64();

      uint items = vSize/typeSize[ncType];

      sprintf(tmp,"%s.type",varName);
      insertProperty(tmp,ncType);

      sprintf(tmp,"%s.items",varName);
      insertProperty(tmp,items);

      sprintf(tmp,"%s.offset",varName);
      insertProperty(tmp,offset);

      sprintf(tmp,"%s.size",varName);
      insertProperty(tmp,vSize);
    }

    insertProperty("netcdf.variables",variables);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}





void NetCdfFile::createMessageInfoList(MemoryReader& memoryReader,MessageInfoVec& messageInfoList)
{
  FUNCTION_TRACE
  try
  {
    int typeSize[] = {0,1,1,2,4,4,8};
    char tmp[1000];

    OGRSpatialReference latlonSp;
    latlonSp.importFromEPSG(4326);
    latlonSp.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

    auto d = mPropertyList.find("netcdf.variables");
    auto dn = mPropertyList.find("netcdf.dimension.names");
    auto dl = mPropertyList.find("netcdf.dimension.lengths");

    if (d != mPropertyList.end() && dn != mPropertyList.end() && dl != mPropertyList.end())
    {
      for (auto it = d->second.begin(); it != d->second.end(); ++it)
      {
        sprintf(tmp,"%s.dimension.indexes",it->c_str());
        auto dd = mPropertyList.find(tmp);
        if (dd != mPropertyList.end())
        {
          int timeCount = 0;
          int levelCount = 0;
          int xIndex = 0;
          int yIndex = 0;
          int yCount = 0;
          int xCount = 0;
          double xScale = 1.0;
          double yScale = 1.0;

          std::string timeName;
          std::string levelName;
          std::string xName;
          std::string yName;
          std::string xStandardName;
          std::string yStandardName;
          int projectionId = 0;
          int geometryId = 0;


          // printf("(%s[%ld])\n",it->c_str(),dd->second.size());
          if (dd->second.size() == 3 || dd->second.size() == 4)
          {
            // This is a grid variable

            int paramLevelId = 1;
            uint iii = 0;
            for (auto itm = dd->second.begin(); itm != dd->second.end(); ++itm)
            {
              int i = atoi(itm->c_str());
              int ii = atoi(dl->second[i].c_str());

              std::string standardName;
              sprintf(tmp,"%s.standard_name",dn->second[i].c_str());
              getProperty(tmp,0,standardName);

              std::string longName;
              sprintf(tmp,"%s.long_name",dn->second[i].c_str());
              getProperty(tmp,0,longName);

              std::string units;
              sprintf(tmp,"%s.units",dn->second[i].c_str());
              getProperty(tmp,0,units);

              std::string axis;
              sprintf(tmp,"%s.axis",dn->second[i].c_str());
              getProperty(tmp,0,axis);

              std::string positive;
              sprintf(tmp,"%s.positive",dn->second[i].c_str());
              getProperty(tmp,0,positive);

              if (strcasecmp(standardName.c_str(),"time") == 0 || strcasecmp(longName.c_str(),"time") == 0 || strcasecmp(axis.c_str(),"T") == 0 || strcasecmp(dn->second[i].c_str(),"time") == 0 || strcasecmp(dn->second[i].c_str(),"time_counter") == 0)
              {
                timeCount = ii;
                timeName = dn->second[i];
              }
              else
              if (strcasecmp(axis.c_str(),"Z") == 0 ||
                  strcasecmp(standardName.c_str(),"depth") == 0 || strcasecmp(standardName.c_str(),"height") == 0  || strcasecmp(standardName.c_str(),"level") == 0 ||
                  strcasecmp(longName.c_str(),"depth") == 0 || strcasecmp(longName.c_str(),"height") == 0 || strcasecmp(longName.c_str(),"level") == 0  ||
                  strcasecmp(dn->second[i].c_str(),"depth") == 0 || strcasecmp(dn->second[i].c_str(),"height") == 0 || strcasecmp(dn->second[i].c_str(),"level") == 0)
              {
                levelCount = ii;
                levelName = dn->second[i];

                if (strcasecmp(units.c_str(),"m") == 0 || strcasecmp(units.c_str(),"metre") == 0)
                {
                  if (strcasecmp(positive.c_str(),"down") == 0)
                    paramLevelId = 10;
                  else
                    paramLevelId = 1;
                }
                else
                if (strcasecmp(units.c_str(),"Pa") == 0 || strcasecmp(units.c_str(),"hPa") == 0)
                  paramLevelId = 2;
              }
              else
              if (strcasecmp(axis.c_str(),"Y") == 0 || strcasecmp(standardName.c_str(),"projection_y_coordinate") == 0 ||
                  strcasecmp(standardName.c_str(),"latitude") == 0 || strcasecmp(longName.c_str(),"latitude") == 0 ||
                  strcasecmp(dn->second[i].c_str(),"lat") == 0 || strcasecmp(dn->second[i].c_str(),"latitude") == 0)
              {
                yIndex = iii;
                yCount = ii;
                yName = dn->second[i];
                yStandardName = standardName;
              }
              else
              if (strcasecmp(axis.c_str(),"X") == 0 || strcasecmp(standardName.c_str(),"projection_x_coordinate") == 0 ||
                  strcasecmp(standardName.c_str(),"longitude") == 0 || strcasecmp(longName.c_str(),"longitude") == 0 ||
                  strcasecmp(dn->second[i].c_str(),"lon") == 0 || strcasecmp(dn->second[i].c_str(),"longitude") == 0)
              {
                xIndex = iii;
                xCount = ii;
                xName = dn->second[i];
                xStandardName = standardName;
              }

              //printf("  %s (%s,%d)\n",itm->c_str(),dn->second[i].c_str(),ii);
              iii++;
            }

            //printf("%s %s:%d,%s:%d,%s:%d,%s:%d\n",it->c_str(),timeName.c_str(),timeCount,levelName.c_str(),levelCount,yName.c_str(),yCount,yName.c_str(),xCount);


            longlong dataStartOffset = 0;
            sprintf(tmp,"%s.offset",it->c_str());
            getProperty(tmp,0,dataStartOffset);

            uint dataType = 0;
            sprintf(tmp,"%s.type",it->c_str());
            getProperty(tmp,0,dataType);

            double dataBaseValue = 0;
            sprintf(tmp,"%s.add_offset",it->c_str());
            getProperty(tmp,0,dataBaseValue);

            double dataScaleFactor = 1;
            sprintf(tmp,"%s.scale_factor",it->c_str());
            getProperty(tmp,0,dataScaleFactor);

            float missingValue = ParamValueMissing;
            sprintf(tmp,"%s.missing_value",it->c_str());
            if (!getProperty(tmp,0,missingValue))
            {
              sprintf(tmp,"%s._FillValue",it->c_str());
              getProperty(tmp,0,missingValue);
            }

            std::string xUnits;
            sprintf(tmp,"%s.units",xName.c_str());
            getProperty(tmp,0,xUnits);

            std::string yUnits;
            sprintf(tmp,"%s.units",yName.c_str());
            getProperty(tmp,0,yUnits);

            std::string dataUnits;
            sprintf(tmp,"%s.units",it->c_str());
            getProperty(tmp,0,dataUnits);

            std::string parameterStandardName;
            sprintf(tmp,"%s.standard_name",it->c_str());
            getProperty(tmp,0,parameterStandardName);

            std::string gridMapping;
            sprintf(tmp,"%s.grid_mapping",it->c_str());
            getProperty(tmp,0,gridMapping);

            uint dataSize = xCount * yCount * typeSize[dataType];


            if (!xUnits.empty())
            {
              double value = 0.0;
              std::string units;
              parseUnits(xUnits.c_str(),value,units);
              // printf("X-UNIT [%f][%s]\n",value,units.c_str());
              if (value == 0.0)
                value = 1.0;

              if (strcasecmp(units.c_str(),"km") == 0)
                xScale = value * 1000;
            }

            if (!yUnits.empty())
            {
              double value = 0.0;
              std::string units;
              parseUnits(yUnits.c_str(),value,units);
              // printf("Y-UNIT [%f][%s]\n",value,units.c_str());
              if (value == 0.0)
                value = 1.0;

              if (strcasecmp(units.c_str(),"km") == 0)
                yScale = value * 1000;
            }


            // ##### Time information ##############################################

            std::vector<time_t> timeList;
            int year = 0;
            int month = 0;
            int day = 0;
            int hour = 0;
            int minute = 0;
            int second = 0;
            time_t unitSize = 0;

            sprintf(tmp,"%s.units",timeName.c_str());
            std::string time_units;
            if (getProperty(tmp,0,time_units))
            {
              parseNetCdfTime(time_units,year,month,day,hour,minute,second,unitSize);
              // printf("TIME %04d%02d%02dT%02d%02d%02d  %ld\n",year,month,day,hour,minute,second,unitSize);
            }
            else
            {
              printf("*** TIME UNITS MISSING\n");
              // Time units missing
            }

            uint type = 0;
            uint size = 0;
            longlong offset = 0;
            uint itemCount = 0;
            double scaleFactor = 1;
            double baseValue = 0;

            sprintf(tmp,"%s.type",timeName.c_str());
            getProperty(tmp,0,type);

            sprintf(tmp,"%s.size",timeName.c_str());
            getProperty(tmp,0,size);

            sprintf(tmp,"%s.add_offset",timeName.c_str());
            getProperty(tmp,0,baseValue);

            sprintf(tmp,"%s.scale_factor",timeName.c_str());
            getProperty(tmp,0,scaleFactor);

            sprintf(tmp,"%s.offset",timeName.c_str());
            getProperty(tmp,0,offset);

            sprintf(tmp,"%s.items",timeName.c_str());
            getProperty(tmp,0,itemCount);

            std::vector<double> timeValues;
            //printf("READ TIME %f %f\n",baseValue,scaleFactor);
            readValues(memoryReader,type,itemCount,offset,baseValue,scaleFactor,timeValues);

            uint tc = timeCount;
            if (itemCount > 1)
              tc = 1;

            for (uint t=0; t<tc; t++)
            {
              for (auto v = timeValues.begin(); v != timeValues.end(); ++v)
              {
                time_t ttt = (time_t)(*v)*(time_t)unitSize+(time_t)t*(time_t)unitSize;
                //printf("TimeT %ld %f %ld\n",ttt,*v,unitSize);
                time_t tt = getGregorianTimeT(year,month,day,hour,minute,second,ttt);
                timeList.push_back(tt);

                //std::string tm = utcTimeFromTimeT(tt);
                //printf("  Time %f => %ld => %s\n",*v,tt,tm.c_str());
              }
            }

            // ##### Level information #############################################

            Identification::NetCdfParameterDef ncParamDef;
            if (Identification::gridDef.getNetCdfParameterDefByName(parameterStandardName,ncParamDef))
            {
              if (!ncParamDef.mFmiLevelId.empty())
                paramLevelId = atoi(ncParamDef.mFmiLevelId.c_str());
            }

            std::vector<double> levelList;
            if (levelCount > 0)
            {
              type = 0;
              size = 0;
              offset = 0;
              itemCount = 0;
              scaleFactor = 1;
              baseValue = 0;

              sprintf(tmp,"%s.type",levelName.c_str());
              getProperty(tmp,0,type);

              sprintf(tmp,"%s.size",levelName.c_str());
              getProperty(tmp,0,size);

              sprintf(tmp,"%s.add_offset",levelName.c_str());
              getProperty(tmp,0,baseValue);

              sprintf(tmp,"%s.scale_factor",levelName.c_str());
              getProperty(tmp,0,scaleFactor);

              sprintf(tmp,"%s.offset",levelName.c_str());
              getProperty(tmp,0,offset);

              sprintf(tmp,"%s.items",levelName.c_str());
              getProperty(tmp,0,itemCount);

              readValues(memoryReader,type,itemCount,offset,baseValue,scaleFactor,levelList);
            }
            else
            {
              levelList.push_back(0.0);
            }

            /*
            for (auto v = levelList.begin(); v != levelList.end(); ++v)
            {
              printf("  Level  %f\n",*v);
            }
            */


            // ##### X-coordinates #################################################

            if (mXCoordinates.size() == 0)
            {
              type = 0;
              size = 0;
              offset = 0;
              itemCount = 0;
              scaleFactor = 1;
              baseValue = 0;

              sprintf(tmp,"%s.type",xName.c_str());
              getProperty(tmp,0,type);

              sprintf(tmp,"%s.size",xName.c_str());
              getProperty(tmp,0,size);

              sprintf(tmp,"%s.offset",xName.c_str());
              getProperty(tmp,0,offset);

              sprintf(tmp,"%s.add_offset",xName.c_str());
              getProperty(tmp,0,baseValue);

              sprintf(tmp,"%s.scale_factor",xName.c_str());
              getProperty(tmp,0,scaleFactor);

              sprintf(tmp,"%s.items",xName.c_str());
              getProperty(tmp,0,itemCount);

              readValues(memoryReader,type,itemCount,offset,baseValue,scaleFactor*xScale,mXCoordinates);

              /*
              for (auto v = mXCoordinates.begin(); v != mXCoordinates.end(); ++v)
              {
                printf("  X-Coord  %f\n",*v);
              }
              */
            }

            // ##### Y-coordinates #################################################

            if (mYCoordinates.size() == 0)
            {
              type = 0;
              size = 0;
              offset = 0;
              itemCount = 0;
              scaleFactor = 1;
              baseValue = 0;

              sprintf(tmp,"%s.type",yName.c_str());
              getProperty(tmp,0,type);

              sprintf(tmp,"%s.size",yName.c_str());
              getProperty(tmp,0,size);

              sprintf(tmp,"%s.offset",yName.c_str());
              getProperty(tmp,0,offset);

              sprintf(tmp,"%s.add_offset",yName.c_str());
              getProperty(tmp,0,baseValue);

              sprintf(tmp,"%s.scale_factor",yName.c_str());
              getProperty(tmp,0,scaleFactor);

              sprintf(tmp,"%s.items",yName.c_str());
              getProperty(tmp,0,itemCount);

              readValues(memoryReader,type,itemCount,offset,baseValue,scaleFactor*yScale,mYCoordinates);

              /*
              for (auto v = mYCoordinates.begin(); v != mYCoordinates.end(); ++v)
              {
                printf("  Y-Coord  %f\n",*v);
              }
              */
            }

            // ##### Projection ####################################################

            std::string mappingName;
            sprintf(tmp,"%s.grid_mapping_name",gridMapping.c_str());
            getProperty(tmp,0,mappingName);

            double startx = mXCoordinates[0];
            double starty = mYCoordinates[0];

            uint xsz = mXCoordinates.size() - 1;
            uint ysz = mYCoordinates.size() - 1;
            double dx = (mXCoordinates[xsz] - mXCoordinates[0]) / (double)xsz;
            double dy = (mYCoordinates[ysz] - mYCoordinates[0]) / (double)ysz;

            char projectionString[300];
            projectionString[0] = '\0';
            char sm[100];
            char *p = sm;

            if (dx < 0)
              p += sprintf(p,"-x");
            else
              p += sprintf(p,"+x");

            if (dy < 0)
              p += sprintf(p,"-y");
            else
              p += sprintf(p,"+y");


            if (strcasecmp(mappingName.c_str(),"polar_stereographic") == 0 || strcasecmp(mappingName.c_str(),"stereographic") == 0)
            {
              // ***** PROJECTION: Polar stereograpic ***********************************************

              projectionId = T::GridProjectionValue::PolarStereographic;

              double longitude_of_projection_origin = 0.0;
              sprintf(tmp,"%s.longitude_of_projection_origin",gridMapping.c_str());
              getProperty(tmp,0,longitude_of_projection_origin);

              double latitude_of_projection_origin = 0.0;
              sprintf(tmp,"%s.latitude_of_projection_origin",gridMapping.c_str());
              getProperty(tmp,0,latitude_of_projection_origin);

              double scale_factor_at_projection_origin = 0.0;
              sprintf(tmp,"%s.scale_factor_at_projection_origin",gridMapping.c_str());
              getProperty(tmp,0,scale_factor_at_projection_origin);

              double straight_vertical_longitude_from_pole = 0.0;
              sprintf(tmp,"%s.straight_vertical_longitude_from_pole",gridMapping.c_str());
              getProperty(tmp,0,straight_vertical_longitude_from_pole);

              double false_easting = 0.0;
              sprintf(tmp,"%s.false_easting",gridMapping.c_str());
              getProperty(tmp,0,false_easting);

              double false_northing = 0.0;
              sprintf(tmp,"%s.false_northing",gridMapping.c_str());
              getProperty(tmp,0,false_northing);

              OGRSpatialReference sp;
              sp.SetPS(latitude_of_projection_origin,longitude_of_projection_origin,scale_factor_at_projection_origin,false_easting,false_northing);

              sp.SetTargetLinearUnits("PROJCS", SRS_UL_METER, 1.0);
              sp.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

              OGRCoordinateTransformation *transformation = OGRCreateCoordinateTransformation(&sp,&latlonSp);
              transformation->Transform(1,&startx,&starty);
              OCTDestroyCoordinateTransformation(transformation);

              sprintf(projectionString,"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;description",
                  T::GridProjectionValue::PolarStereographic,(int)mXCoordinates.size(),(int)mYCoordinates.size(),
                  startx,starty,fabs(dx),fabs(dy),sm,straight_vertical_longitude_from_pole,latitude_of_projection_origin);

              auto def = Identification::gridDef.getGrib2DefinitionByGeometryString(projectionString);
              if (def)
              {
                geometryId = def->getGridGeometryId();
              }
              else
              {
                std::cout << "#### Geometry not found ####\n";
                std::cout << "** Add the following line into the geometry definition file (=> fill id,name and description fields) :\n\n";
                std::cout << projectionString << "\n";
              }
            }
            else
            if (strcasecmp(mappingName.c_str(),"lambert_azimuthal_equal_area") == 0)
            {
              // ***** PROJECTION: Lambert Azimuthal Equal Area *************************************

              projectionId = T::GridProjectionValue::LambertAzimuthalEqualArea;

              dx = mXCoordinates[1] - mXCoordinates[0];
              dy = mYCoordinates[1] - mYCoordinates[0];

              double longitude_of_projection_origin = 0.0;
              sprintf(tmp,"%s.longitude_of_projection_origin",gridMapping.c_str());
              getProperty(tmp,0,longitude_of_projection_origin);

              double latitude_of_projection_origin = 0.0;
              sprintf(tmp,"%s.latitude_of_projection_origin",gridMapping.c_str());
              getProperty(tmp,0,latitude_of_projection_origin);

              double false_easting = 0.0;
              sprintf(tmp,"%s.false_easting",gridMapping.c_str());
              getProperty(tmp,0,false_easting);

              double false_northing = 0.0;
              sprintf(tmp,"%s.false_northing",gridMapping.c_str());
              getProperty(tmp,0,false_northing);

              OGRSpatialReference sp;
              sp.SetLAEA(latitude_of_projection_origin,longitude_of_projection_origin,false_easting,false_northing);
              sp.SetTargetLinearUnits("PROJCS", SRS_UL_METER, 1.0);
              sp.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

              OGRCoordinateTransformation *transformation = OGRCreateCoordinateTransformation(&sp,&latlonSp);
              transformation->Transform(1,&startx,&starty);
              OCTDestroyCoordinateTransformation(transformation);

              sprintf(projectionString,"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;description",
                  T::GridProjectionValue::LambertAzimuthalEqualArea,(int)mXCoordinates.size(),(int)mYCoordinates.size(),
                  startx,starty,fabs(dx),fabs(dy),sm,latitude_of_projection_origin,longitude_of_projection_origin);

              auto def = Identification::gridDef.getGrib2DefinitionByGeometryString(projectionString);
              if (def)
              {
                geometryId = def->getGridGeometryId();
              }
              else
              {
                char tmp[1000];
                sprintf(tmp,"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;0.000000;0.000000;description",
                    T::GridProjectionValue::LambertAzimuthalEqualArea,(int)mXCoordinates.size(),(int)mYCoordinates.size(),
                    startx,starty,fabs(dx),fabs(dy),sm,latitude_of_projection_origin,longitude_of_projection_origin);
                std::cout << "#### Geometry not found ####\n";
                std::cout << "** Add the following line into the geometry definition file (=> fill id,name and description fields) :\n\n";
                std::cout << tmp << "\n";
              }
            }
            else
            if (strcasecmp(mappingName.c_str(),"lambert_conformal_conic") == 0)
            {
              // ***** PROJECTION: Lambert Conformal *************************************

              projectionId = T::GridProjectionValue::LambertConformal;

              dx = (mXCoordinates[1] - mXCoordinates[0])*1000;
              dy = (mYCoordinates[1] - mYCoordinates[0])*1000;

              double standard_parallel = 0.0;
              sprintf(tmp,"%s.standard_parallel",gridMapping.c_str());
              getProperty(tmp,0,standard_parallel);

              double longitude_of_central_meridian = 0.0;
              sprintf(tmp,"%s.longitude_of_central_meridian",gridMapping.c_str());
              getProperty(tmp,0,longitude_of_central_meridian);


              double longitude_of_projection_origin = 0.0;
              sprintf(tmp,"%s.longitude_of_projection_origin",gridMapping.c_str());
              getProperty(tmp,0,longitude_of_projection_origin);

              double latitude_of_projection_origin = 0.0;
              sprintf(tmp,"%s.latitude_of_projection_origin",gridMapping.c_str());
              getProperty(tmp,0,latitude_of_projection_origin);

              double false_easting = 0.0;
              sprintf(tmp,"%s.false_easting",gridMapping.c_str());
              getProperty(tmp,0,false_easting);

              double false_northing = 0.0;
              sprintf(tmp,"%s.false_northing",gridMapping.c_str());
              getProperty(tmp,0,false_northing);

              double earth_radius = 6371229.0;
              sprintf(tmp,"%s.earth_radius",gridMapping.c_str());
              getProperty(tmp,0,earth_radius);

              OGRSpatialReference sp;
              sp.SetLCC(standard_parallel,longitude_of_central_meridian,latitude_of_projection_origin,longitude_of_projection_origin,false_easting,false_northing);
              sp.SetTargetLinearUnits("PROJCS", SRS_UL_METER, 1.0);
              sp.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

              OGRCoordinateTransformation *transformation = OGRCreateCoordinateTransformation(&sp,&latlonSp);
              transformation->Transform(1,&startx,&starty);
              OCTDestroyCoordinateTransformation(transformation);

              double sx = 0.0;
              double sy = -90.0;

              //# LAMBERT CONFORMAL : projection,id,name,ni,nj,first_lon,first_lat,di,dj,scanning_mode,orientation,latin1,latin2,south_pole_lon,south_pole_lat,LaD,earthSemiMajor,earthSemiMinor,description
              sprintf(projectionString,"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;%.6f;%.6f;%.6f;%.6f;description",
                T::GridProjectionValue::LambertConformal,(int)mXCoordinates.size(),(int)mYCoordinates.size(),startx,starty,fabs(dx),fabs(dy),
                sm,longitude_of_central_meridian,latitude_of_projection_origin,latitude_of_projection_origin,sx,sy,latitude_of_projection_origin);

              //auto def = Identification::gridDef.getGrib2DefinitionByGeometryId(1093);
              auto def = Identification::gridDef.getGrib2DefinitionByGeometryString(projectionString);
              if (def)
              {
                geometryId = def->getGridGeometryId();
              }
              else
              {
                char tmp[1000];
                sprintf(tmp,"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;%.6f;%.6f;%.6f;%.6f;description",
                  T::GridProjectionValue::LambertConformal,(int)mXCoordinates.size(),(int)mYCoordinates.size(),startx,starty,fabs(dx),fabs(dy),
                  sm,longitude_of_central_meridian,latitude_of_projection_origin,latitude_of_projection_origin,sx,sy,latitude_of_projection_origin);
                std::cout << "#### Geometry not found ####\n";
                std::cout << "** Add the following line into the geometry definition file (=> fill id,name and description fields) :\n\n";
                std::cout << tmp << "\n";
              }

            }
            else
            if (strcasecmp(mappingName.c_str(),"latitude_longitude") == 0 ||
                (mappingName.empty() &&  strcasecmp(xStandardName.c_str(),"longitude") == 0   &&  strcasecmp(yStandardName.c_str(),"latitude") == 0))
            {
              // ***** PROJECTION: Latlon ***********************************************************

              projectionId = T::GridProjectionValue::LatLon;

              sprintf(projectionString,"%d;id;name;%u;%u;%.6f;%.6f;%.6f;%.6f;%s;description",
                T::GridProjectionValue::LatLon,(int)mXCoordinates.size(),(int)mYCoordinates.size(),
                startx,starty,fabs(dx),fabs(dy),sm);

              auto def = Identification::gridDef.getGrib2DefinitionByGeometryString(projectionString);
              if (def)
              {
                geometryId = def->getGridGeometryId();
              }
              else
              {
                char tmp[1000];
                sprintf(tmp,"%d;id;name;%u;%u;%.6f;%.6f;%.6f;%.6f;%s;0.000000;0.000000;description",
                  T::GridProjectionValue::LatLon,(int)mXCoordinates.size(),(int)mYCoordinates.size(),
                  startx,starty,fabs(dx),fabs(dy),sm);
                std::cout << "#### Geometry not found ####\n";
                std::cout << "** Add the following line into the geometry definition file (=> fill id,name and description fields) :\n\n";
                std::cout << tmp << "\n";
              }
            }



            // ##### Creating message infos ########################################

            for (auto tIt = timeList.begin(); tIt != timeList.end(); tIt++)
            {
              for (auto lIt = levelList.begin(); lIt != levelList.end(); lIt++)
              {
                MessageInfo msg;
                msg.mProjectionId = projectionId;
                msg.mMessageType = T::FileTypeValue::NetCdf4;
                msg.mGeometryId = geometryId;
                msg.mFilePosition = dataStartOffset;
                msg.mMessageSize = dataSize;
                msg.mColumns = xCount;
                msg.mRows = yCount;
                if (xIndex > yIndex)
                {
                  msg.mColumnMultiplier = xCount;
                  msg.mRowMultiplier = 1;
                }
                else
                {
                  msg.mColumnMultiplier = 1;
                  msg.mRowMultiplier = yCount;
                }
                msg.mDataType = dataType;
                msg.mBaseValue = dataBaseValue;
                msg.mScaleFactor = dataScaleFactor;
                msg.mParameterName = *it;

                msg.mParameterStandardName = parameterStandardName;

                msg.mParameterUnits = dataUnits;
                msg.mParameterLevelId = paramLevelId;
                msg.mParameterLevel = *lIt;
                msg.mForecastType = 1;
                msg.mForecastNumber = 0;
                msg.mForecastTimeT = *tIt;
                msg.mMissingValue = missingValue;
                messageInfoList.push_back(msg);
                dataStartOffset += dataSize;
              }
              dataStartOffset += levelCount;
            }
          }
        }
      }
    }

  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
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




void NetCdfFile::getAttributeList(const char *variableName,const std::string& prefix,T::AttributeList& attributeList) const
{
  try
  {
    uint len = strlen(variableName);
    for (auto pr = mPropertyList.begin();pr != mPropertyList.end(); ++pr)
    {
      const char *s = pr->first.c_str();
      if (strncasecmp(s,variableName,len) == 0 &&  s[len] == '.')
      {
        char value[10000];
        char *p = value;
        *p = '\0';
        for (auto it = pr->second.begin(); it != pr->second.end(); ++it)
        {
          if (it != pr->second.begin())
            p += sprintf(p," ");

          p += sprintf(p,"%s",(*it).c_str());
        }

        char name[300];
        sprintf(name, "%s%s", prefix.c_str(),s);
        attributeList.addAttribute(name, value);
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

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void NetCdfFile::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "NetCdfFile\n";
    stream << space(level) << "- mPropertyList = \n";

    for (auto pr = mPropertyList.begin();pr != mPropertyList.end(); ++pr)
    {
      stream << space(level+2) <<  pr->first << " : ";
      for (auto it = pr->second.begin(); it != pr->second.end(); ++it)
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
