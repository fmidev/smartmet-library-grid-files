#pragma once

#include "../grid/Message.h"
#include "Message.h"


namespace SmartMet
{
namespace NetCDF
{


using PropertyVec = std::map<std::string, std::vector<std::string>>;
using FloatVec = std::vector<float>;


class NetCdfFile
{
  public:

                NetCdfFile();
    virtual     ~NetCdfFile();

    void        getAttributeList(const char *variableName,const std::string& prefix,T::AttributeList& attributeList) const;
    void        read(MemoryReader& memoryReader,MessageInfoVec& messageInfoList);
    void        print(std::ostream& stream,uint level,uint optionFlags) const;

    void        createMessageInfoList(MemoryReader& memoryReader,MessageInfoVec& messageInfoList);
    void        insertProperty(std::string propertyName,std::vector<std::string>& propertyValue);
    void        insertProperty(std::string propertyName,std::string propertyValue);
    void        insertProperty(std::string propertyName,int propertyValue);
    void        insertProperty(std::string propertyName,uint propertyValue);
    void        insertProperty(std::string propertyName,longlong propertyValue);
    void        insertProperty(std::string propertyName,double propertyValue);
    void        readAttribute(MemoryReader& memoryReader,std::string& attrName,std::vector<std::string>& attrValues);
    void        readPropertyList(MemoryReader& memoryReader);
    void        readValues(MemoryReader& memoryReader,uint items,ulonglong offset,std::vector<char>& values);
    void        readValues(MemoryReader& memoryReader,uint items,ulonglong offset,std::vector<uchar>& values);
    void        readValues(MemoryReader& memoryReader,uint items,ulonglong offset,std::vector<short>& values);
    void        readValues(MemoryReader& memoryReader,uint items,ulonglong offset,std::vector<int>& values);
    void        readValues(MemoryReader& memoryReader,uint items,ulonglong offset,std::vector<float>& values);
    void        readValues(MemoryReader& memoryReader,uint items,ulonglong offset,std::vector<double>& values);
    void        readValues(MemoryReader& memoryReader,uint type,uint items,ulonglong offset,float baseValue,float scaleFactor,std::vector<float>& values);
    void        readValues(MemoryReader& memoryReader,uint type,uint items,ulonglong offset,double baseValue,double scaleFactor,std::vector<double>& values);
/*
    bool        getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    bool        getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool        getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
*/

    bool        getProperty(std::string propertyName,uint index,std::string& propertyValue);
    bool        getProperty(std::string propertyName,uint index,int& propertyValue);
    bool        getProperty(std::string propertyName,uint index,uint& propertyValue);
    bool        getProperty(std::string propertyName,uint index,longlong& propertyValue);
    bool        getProperty(std::string propertyName,uint index,float& propertyValue);
    bool        getProperty(std::string propertyName,uint index,double& propertyValue);

  protected:

    PropertyVec mPropertyList;
    FloatVec    mXCoordinates;
    FloatVec    mYCoordinates;
};



using NetCdfFilePtr = NetCdfFile *;


}  // namespace NetCDF
}  // namespace SmartMet

