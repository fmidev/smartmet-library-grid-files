#pragma once

#include "DataFetcher.h"

namespace SmartMet
{

class DataFetcher_THREDDS : public DataFetcher
{
  public:
                  DataFetcher_THREDDS();
    virtual       ~DataFetcher_THREDDS();

    virtual int   getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr);
};

}  // namespace SmartMet
