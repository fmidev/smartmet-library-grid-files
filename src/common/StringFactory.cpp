#include "StringFactory.h"
#include "AutoWriteLock.h"
#include "AutoReadLock.h"
#include <macgyver/Exception.h>

namespace SmartMet
{

StringFactory stringFactory;



StringFactory::StringFactory()
{
  try
  {
    stringArraySize = 10000;
    stringArrayCount = 1000;
    stringTable = new StringArray[stringArrayCount];
    for (uint t=0; t<stringArrayCount; t++)
      stringTable[t] = nullptr;

    create("");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




StringFactory::~StringFactory()
{
  try
  {
    if (stringTable != nullptr)
    {
      for (uint t=0; t<stringArrayCount; t++)
      {
        if (stringTable[t] != nullptr)
        {
          for (uint a=0; a<stringArraySize;a++)
          {
            if (stringTable[t][a] != nullptr)
              delete[] stringTable[t][a];
          }
        }
        delete stringTable[t];
      }
      delete stringTable;
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





uint StringFactory::create(const char *str)
{
  try
  {
    if (str == nullptr)
      return 0;

    {
      AutoReadLock readLock(&modificationLock);
      auto res = stringIndex.find(str);
      if (res != stringIndex.end())
        return res->second;
    }

    AutoWriteLock writeLock(&modificationLock);
    uint idx = stringIndex.size();
    uint arrayNum = idx / stringArraySize;
    uint arrayIdx = idx % stringArraySize;

    if (stringTable[arrayNum] == nullptr)
    {
      stringTable[arrayNum] = new pchar[stringArraySize];
      for (uint t=0; t<stringArraySize; t++)
        stringTable[arrayNum][t] = nullptr;
    }

    uint len = strlen(str);
    stringTable[arrayNum][arrayIdx] = new char[len+1];
    strcpy(stringTable[arrayNum][arrayIdx],str);

    stringIndex.insert(std::pair<std::string,uint>(std::string(str),idx));
    return idx;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint StringFactory::create(std::string str)
{
  try
  {
    return create(str.c_str());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





pchar StringFactory::operator[](uint index)
{
  try
  {
    uint arrayNum = index / stringArraySize;
    uint arrayIdx = index % stringArraySize;

    if (arrayNum >= stringArrayCount ||  stringTable[arrayNum] == nullptr)
      return nullptr;

    return stringTable[arrayNum][arrayIdx];
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
