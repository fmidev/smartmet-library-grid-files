#pragma once

#include "Typedefs.h"
#include "Log.h"

namespace SmartMet
{


// ====================================================================================
/*! \brief RAII function-entry/exit tracer for the global trace log.
 *
 *  When `FUNCTION_TRACE_ON` is placed at the top of a function, entry and exit
 *  (with elapsed time) are logged to `globalTraceLog` if non-null and enabled.
 *  Replace with `FUNCTION_TRACE_OFF` to silence tracing without changing call sites. */
// ====================================================================================

class ShowFunction
{
  public:
    /*! \brief Log function entry and start the elapsed timer.
     *  \param[in] _file      Source file name (__FILE__).
     *  \param[in] _line      Source line number (__LINE__).
     *  \param[in] _function  Function name (__FUNCTION__). */
                 ShowFunction(const char *_file,uint _line,const char *_function);
    virtual      ~ShowFunction(); //!< Log function exit with elapsed time

  protected:

    std::string   function;  //!< Function name
    std::string   filename;  //!< Source file name
    uint          line;      //!< Source line number
    UInt64        startTime; //!< Entry timestamp in microseconds

};


extern Log *globalTraceLog; //!< Global trace log; nullptr disables ShowFunction output


#define FUNCTION_TRACE_ON  ShowFunction sfunc(__FILE__,__LINE__,__FUNCTION__); //!< Enable function entry/exit tracing
#define FUNCTION_TRACE_OFF ; //!< Disable function tracing (no-op)

}
