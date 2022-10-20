#pragma once

#include "MapInfo.h"

#include <string>
#include <vector>


namespace SmartMet
{


class Client
{
  public:
                  Client();
    virtual       ~Client();

    virtual int   getData(MapInfo& info,std::size_t filePosition,int dataSize,char *dataPtr);

    virtual bool  isActive();
    virtual void  setActive(bool active);

  protected:

    bool          mActive;
};

typedef Client* Client_ptr;
typedef std::vector<Client_ptr> Client_ptr_vec;

}
