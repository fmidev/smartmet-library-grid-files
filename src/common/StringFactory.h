#pragma once

#include <unordered_map>
#include "ModificationLock.h"

namespace SmartMet
{

using pchar = char *;
using StringArray = pchar *;
using StringIndex = std::unordered_map<std::string, uint>;


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
