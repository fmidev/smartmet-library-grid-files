#pragma once

#include <string>
#include <unordered_map>
#include "ModificationLock.h"

namespace SmartMet
{

typedef char* pchar;
typedef pchar* StringArray;
typedef std::unordered_map<std::string,uint> StringIndex;


class StringFactory
{
  public:
                  StringFactory();
                  ~StringFactory();

    uint          create(const char *str);
    uint          create(std::string str);
    pchar         operator[](uint index);

  protected:

    StringArray   *stringTable;
    StringIndex   stringIndex;
    uint          stringArraySize;
    uint          stringArrayCount;

    ModificationLock  modificationLock;
};


extern StringFactory stringFactory;

}
