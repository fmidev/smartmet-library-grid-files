#include "Client.h"
#include <macgyver/Exception.h>


namespace SmartMet
{


Client::Client()
{
  try
  {
    mActive = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




Client::~Client()
{
}




int Client::getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr)
{
  throw Fmi::Exception(BCP,"Should be implemented in the child class!");
}




bool Client::isActive()
{
  return mActive;
}




void Client::setActive(bool active)
{
  mActive = active;
}



}


