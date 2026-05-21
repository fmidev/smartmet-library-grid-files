#pragma once

#include "ThreadLock.h"
#include "Typedefs.h"

#include <stdio.h>
#include <string>


namespace SmartMet
{

// ====================================================================================
/*! \brief Thread-safe file-based event logger with automatic size-based truncation.
 *
 *  Writes timestamped event lines to a stdio file.  When the file grows beyond
 *  `maxSize` bytes it is truncated to `truncateSize` bytes.  Each write is bracketed
 *  by `lock()`/`unlock()` calls; use the `PRINT_EVENT` macros for the full format. */
// ====================================================================================

class Log
{
  public:
                        Log();
    virtual             ~Log();

    /*! \brief Configure the logger.
     *  \param[in] _enabled       Start enabled if true.
     *  \param[in] _filename      Output file path.
     *  \param[in] _maxSize       Trigger truncation when file exceeds this size (bytes).
     *  \param[in] _truncateSize  Target size after truncation (bytes). */
    virtual void        init(bool _enabled,const char *_filename,uint _maxSize,uint _truncateSize);

    /*! \brief Open (or create) the log file for writing (overwrite mode). */
    virtual void        open();
    /*! \brief Open the log file in append mode. */
    virtual void        openForAppend();
    /*! \brief Truncate the log file to zero length. */
    virtual void        clear();
    /*! \brief Flush and close the log file. */
    virtual void        close();
    /*! \brief Disable logging without closing the file. */
    virtual void        disable();
    /*! \brief Re-enable logging. */
    virtual void        enable();
    /*! \brief Return true if logging is currently enabled. */
    virtual bool        isEnabled();

    /*! \brief Return the number of events written since open(). */
    virtual UInt64      getEventCounter();
    /*! \brief Return the raw FILE* handle (for use in PRINT_EVENT macros). */
    virtual FILE*       getFileHandle();
    /*! \brief Return the configured output file path. */
    virtual std::string getFileName();
    /*! \brief Return the configured maximum file size in bytes. */
    virtual uint        getMaxSize();
    /*! \brief Return the target size after truncation in bytes. */
    virtual uint        getTruncateSize();
    /*! \brief Return the current file size in bytes. */
    virtual uint        getSize();

    /*! \brief Acquire the log file mutex (used by PRINT_EVENT macros). */
    virtual void        lock();
    /*! \brief Release the log file mutex. */
    virtual void        unlock();

    /*! \brief Write a plain event string.
     *  \param[in] _event  Event text. */
    virtual void        print(const char *_event);

    /*! \brief Write a timestamped event string.
     *  \param[in] _time   Unix timestamp.
     *  \param[in] _event  Event text. */
    virtual void        print(time_t _time,const char *_event);

    /*! \brief Write an event with timestamp, source location, and text.
     *  \param[in] _time      Unix timestamp.
     *  \param[in] _filename  Source file name.
     *  \param[in] _line      Source line number.
     *  \param[in] _function  Function name.
     *  \param[in] _event     Event text. */
    virtual void        print(time_t _time,const char *_filename,uint _line,const char *_function,const char *_event);

    /*! \brief Write raw binary data as hex to the log.
     *  \param[in] _data  Source buffer.
     *  \param[in] _size  Number of bytes. */
    virtual void        print(void *_data,uint _size);

    /*! \brief Truncate the log file if it exceeds maxSize. */
    virtual void        truncate();

  protected:

    FILE*               file;         //!< Open file handle (nullptr when not open)
    bool                enabled;      //!< True when logging is active
    std::string         filename;     //!< Output file path
    uint                maxSize;      //!< Maximum file size before truncation (bytes)
    ThreadLock          threadLock;   //!< Mutex guarding concurrent writes
    uint                truncateSize; //!< File size to truncate to when maxSize is exceeded
    UInt64              eventCounter; //!< Total events written since open()
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



