#include "DataFetcher_S3.h"
#include "AutoThreadLock.h"
#include <macgyver/Exception.h>

namespace SmartMet
{

DataFetcher_S3::DataFetcher_S3()
{
}




DataFetcher_S3::~DataFetcher_S3()
{
}





int DataFetcher_S3::getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr)
{
  try
  {
    // ToDo: This implementation should fetch data from S3.

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




}  // namespace SmartMet
