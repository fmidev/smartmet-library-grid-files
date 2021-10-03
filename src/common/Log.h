#pragma once

#include "ThreadLock.h"

#include <stdio.h>
#include <string>


namespace SmartMet
{

using uint = unsigned int;
using UInt64 = unsigned long long;

class Log
{
  public:
                        Log();
    virtual             ~Log();

    virtual void        init(bool _enabled,const char *_filename,uint _maxSize,uint _truncateSize);
    virtual void        open();
    virtual void        openForAppend();
    virtual void        close();
    virtual void        disable();
    virtual void        enable();
    virtual bool        isEnabled();

    virtual UInt64      getEventCounter();
    virtual FILE*       getFileHandle();
    virtual std::string getFileName();
    virtual uint        getMaxSize();
    virtual uint        getTruncateSize();
    virtual uint        getSize();

    virtual void        lock();
    virtual void        unlock();

    virtual void        print(const char *_event);
    virtual void        print(time_t _time,const char *_event);
    virtual void        print(time_t _time,const char *_filename,uint _line,const char *_function,const char *_event);
    virtual void        print(void *_data,uint _size);

    virtual void        truncate();

  protected:

    FILE*               file;
    bool                enabled;
    std::string         filename;
    uint                maxSize;
    ThreadLock          threadLock;
    uint                truncateSize;
    UInt64              eventCounter;
};

}



#define PRINT_EVENT(_xLog,_xfileName,_xLine,_xFunction,_xargs...) \
  if (_xLog != nullptr  &&  _xLog->isEnabled())\
  {\
    _xLog->lock();\
    FILE *file = _xLog->getFileHandle();\
    if (file != nullptr)\
    {\
      time_t x_time = time(nullptr);\
      struct tm x_tm;\
      localtime_r(&x_time,&x_tm);\
      fprintf(file,"[%04u-%02u-%02u/%02u:%02u:%02u][%llu][",x_tm.tm_year+1900,x_tm.tm_mon+1,x_tm.tm_mday,x_tm.tm_hour,x_tm.tm_min,x_tm.tm_sec,_xLog->getEventCounter());\
      fprintf(file,_xargs);\
      fprintf(file,"][%s:%u:%s()]\n",_xfileName,_xLine,_xFunction);\
      fflush(file); \
      _xLog->unlock();\
      _xLog->truncate();\
    }\
    else \
      _xLog->unlock();\
  }



#define PRINT_EVENT_LINE(_xLog,_xargs...) \
  if (_xLog != nullptr  &&  _xLog->isEnabled())\
  {\
    _xLog->lock();\
    FILE *file = _xLog->getFileHandle();\
    if (file != nullptr)\
    {\
      time_t x_time = time(nullptr);\
      struct tm x_tm;\
      localtime_r(&x_time,&x_tm);\
      fprintf(file,"[%04u-%02u-%02u/%02u:%02u:%02u][%llu][",x_tm.tm_year+1900,x_tm.tm_mon+1,x_tm.tm_mday,x_tm.tm_hour,x_tm.tm_min,x_tm.tm_sec,_xLog->getEventCounter());\
      fprintf(file,_xargs);\
      fprintf(file,"]\n");\
      fflush(file); \
      _xLog->unlock();\
      _xLog->truncate();\
    }\
    else \
      _xLog->unlock();\
  }



#define PRINT_DATA(_xLog,_xargs...) \
  if (_xLog != nullptr  &&  _xLog->isEnabled())\
  {\
    _xLog->lock();\
    FILE *file = _xLog->getFileHandle();\
    if (file != nullptr)\
    {\
      fprintf(file,_xargs);\
      fflush(file); \
      _xLog->unlock();\
      _xLog->truncate();\
    }\
    else \
      _xLog->unlock();\
  }


#define PRINT_FILE(_lFile,_xargs...) \
  if (_lFile != nullptr)\
  {\
      fprintf(_lFile,_xargs);\
      fflush(_lFile); \
  }



