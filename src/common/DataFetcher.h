#pragma once

#include "MapInfo.h"
#include <memory>
#include <map>

namespace SmartMet
{

class DataFetcher
{
  public:
                  DataFetcher();
    virtual       ~DataFetcher();

    virtual int   getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr);
};

typedef std::shared_ptr<DataFetcher> DataFetcher_sptr;
typedef std::map<uint,DataFetcher_sptr> DataFetcher_sptr_map;

}  // namespace SmartMet
