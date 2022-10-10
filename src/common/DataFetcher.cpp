#include "DataFetcher_filesys.h"
#include <macgyver/Exception.h>

namespace SmartMet
{

DataFetcher::DataFetcher()
{
}




DataFetcher::~DataFetcher()
{
}





int DataFetcher::getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr)
{
  throw Fmi::Exception(BCP,"This method should be implemented in the child class!");
}




}  // namespace SmartMet
