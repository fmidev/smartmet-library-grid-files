#include "Log.h"
#include "AutoThreadLock.h"
#include "GeneralFunctions.h"
#include <macgyver/Exception.h>
#include <macgyver/StringConversion.h>

#include <sys/types.h>
#include <unistd.h>


namespace SmartMet
{



/*! \brief Default constructor for Log. */

Log::Log()
{
  try
  {
    file = nullptr;
    enabled = false;
    maxSize = 0;
    truncateSize = 0;
    eventCounter = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Destructor that closes the log file if open. */

Log::~Log()
{
  try
  {
    if (file != nullptr)
    {
      AutoThreadLock tLock(&threadLock);
      fclose(file);
      file = nullptr;
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





/*! \brief Initialises the log with enable flag, filename, and size limits. */

void Log::init(bool _enabled,const char *_filename,uint _maxSize,uint _truncateSize)
{
  try
  {
    if (_filename == nullptr)
    {
      Fmi::Exception exception(BCP,"The '_filename' parameter points to nullptr!");
      throw exception;
    }

    if (_maxSize < _truncateSize)
    {
      Fmi::Exception exception(BCP,"The '_maxSize' parameter is smaller than the '_truncateSize' parameter!");
      exception.addParameter("maxSize",Fmi::to_string(_maxSize));
      exception.addParameter("truncateSize",Fmi::to_string(_truncateSize));
      throw exception;
    }

    filename = _filename;
    enabled = _enabled;
    maxSize = _maxSize;
    truncateSize = _truncateSize;

    if (enabled)
      open();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Opens the log file for writing, truncating any existing contents. */

void Log::open()
{
  try
  {
    if (filename.length() == 0)
      return;     // ### The log file name is empty.

    if (file != nullptr)
      return;    // ### The log file is already open.

    file = fopen(filename.c_str(),"we");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open the file for writing!");
      exception.addParameter("filename",filename);
      throw exception;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Opens the log file for appending. */

void Log::openForAppend()
{
  try
  {
    if (filename.length() == 0)
      return;     // ### The log file name is empty.

    if (file != nullptr)
      return;    // ### The log file is already open.

    file = fopen(filename.c_str(),"ae");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open the file for append!");
      exception.addParameter("filename",filename);
      throw exception;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Closes the currently open log file. */

void Log::close()
{
  try
  {
    if (file != nullptr)
    {
      AutoThreadLock tLock(&threadLock);
      fclose(file);
      file = nullptr;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Clears the log file by reopening it from scratch. */

void Log::clear()
{
  try
  {
    AutoThreadLock tLock(&threadLock);
    if (file != nullptr)
    {
      fclose(file);
      file = nullptr;
    }
    open();
    if (!enabled)
    {
      fclose(file);
      file = nullptr;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Disables logging and closes the log file. */

void Log::disable()
{
  try
  {
    enabled = false;
    close();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Enables logging and opens the log file for appending. */

void Log::enable()
{
  try
  {
    enabled = true;
    openForAppend();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns whether logging is currently enabled. */

bool Log::isEnabled()
{
  try
  {
    return enabled;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the underlying open file handle. */

FILE* Log::getFileHandle()
{
  try
  {
    return file;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the log file name. */

std::string Log::getFileName()
{
  try
  {
    return filename;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the configured maximum log file size. */

uint Log::getMaxSize()
{
  try
  {
    return maxSize;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the configured truncate size for the log file. */

uint Log::getTruncateSize()
{
  try
  {
    return truncateSize;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Increments and returns the next unique event counter value. */

UInt64 Log::getEventCounter()
{
  try
  {
    eventCounter++;
    return eventCounter;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Returns the current size of the log file in bytes. */

uint Log::getSize()
{
  try
  {
    Int64 size = getFileSize(filename.c_str());
    if (size > 0)
      return C_UINT(size);

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Acquires the log's thread lock. */

void  Log::lock()
{
  try
  {
    threadLock.lock();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Releases the log's thread lock. */

void  Log::unlock()
{
  try
  {
    threadLock.unlock();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes a plain event string to the log. */

void Log::print(const char *_event)
{
  try
  {
    if (!enabled  ||  file == nullptr  ||  _event == nullptr)
      return;

    AutoThreadLock tLock(&threadLock);
    fprintf(file,"%s",_event);
    fflush(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes a timestamped event string to the log. */

void Log::print(time_t _time,const char *_event)
{
  try
  {
    if (!enabled  ||  file == nullptr  ||  _event == nullptr)
      return;

    struct tm x_tm;
    localtime_r(&_time,&x_tm);
    AutoThreadLock tLock(&threadLock);
    fprintf(file,"[%04u-%02u-%02u/%02u:%02u:%02u] %s",x_tm.tm_year+1900,x_tm.tm_mon+1,x_tm.tm_mday,x_tm.tm_hour,x_tm.tm_min,x_tm.tm_sec,_event);
    fflush(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes a timestamped event with file, line, and function context. */

void Log::print(time_t _time,const char *_filename,uint _line,const char *_function,const char *_event)
{
  try
  {
    if (!enabled  ||  file == nullptr  ||  _event == nullptr  ||  _filename == nullptr  ||  _function == nullptr)
      return;

    struct tm x_tm;
    localtime_r(&_time,&x_tm);
    AutoThreadLock tLock(&threadLock);
    fprintf(file,"[%04u-%02u-%02u/%02u:%02u:%02u][%s:%u:%s()] %s",x_tm.tm_year+1900,x_tm.tm_mon+1,x_tm.tm_mday,x_tm.tm_hour,x_tm.tm_min,x_tm.tm_sec,_filename,_line,_function,_event);
    fflush(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes a block of raw bytes to the log. */

void Log::print(void *_data,uint _size)
{
  try
  {
    if (!enabled  ||  file == nullptr)
      return;

    AutoThreadLock tLock(&threadLock);
    fwrite(_data,1,_size,file);
    fflush(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Truncates the log file to the configured size when it exceeds the limit. */

void Log::truncate()
{
  try
  {
    if (!enabled  ||  file == nullptr)
      return;

    AutoThreadLock tLock(&threadLock);
    uint size = ftell(file);

    if (size < maxSize)
    {
      return;
    }

    int pos = size - truncateSize;

    if (pos <= 0)
    {
      return;
    }

    char st[10000];
    char tmpFilename[200];
    sprintf(tmpFilename,"%s.tmp.%d",filename.c_str(),getpid());

    // ### Closing and renaming the log file

    fclose(file);
    file = nullptr;
    rename(filename.c_str(),tmpFilename);

    // ### Opening a new log file

    open();

    // ### Copying log information into the new log file

    FILE *oldfile = fopen(tmpFilename,"re");
    if (oldfile == nullptr)
    {
      // ### ERROR
      return;
    }

    // ### Moving to the correct position and making sure that we start from the beginning of the line.

    fseek(oldfile,pos,SEEK_SET);
    if (fgets(st,10000,oldfile) != 0)
    {
      int n;
      while ((n = fread(st,1,10000,oldfile)) > 0)
      {
        fwrite(st,1,n,file);
      }
    }
    fclose(oldfile);
    remove(tmpFilename);
    fflush(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



}


