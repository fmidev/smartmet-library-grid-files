#include "DataFetcher_THREDDS.h"
#include "AutoThreadLock.h"
#include <macgyver/Exception.h>

namespace SmartMet
{

DataFetcher_THREDDS::DataFetcher_THREDDS()
{
}




DataFetcher_THREDDS::~DataFetcher_THREDDS()
{
}





int DataFetcher_THREDDS::getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr)
{
  try
  {
    // ToDo: This implementation should fetch data from THREDDS.

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




}  // namespace SmartMet
