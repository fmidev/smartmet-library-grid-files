#pragma once

#include "DataFetcher.h"

namespace SmartMet
{

class DataFetcher_S3 : public DataFetcher
{
  public:
                  DataFetcher_S3();
    virtual       ~DataFetcher_S3();

    virtual int   getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr);
};

}  // namespace SmartMet
