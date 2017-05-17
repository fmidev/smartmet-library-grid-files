#pragma once

#include <string>

namespace SmartMet
{


class ShowFunction
{
  public:
                 ShowFunction(const char *_file,uint _line,const char *_function);
    virtual      ~ShowFunction();


  protected:

    std::string   function;
    std::string   filename;
    uint          line;
};


#define FUNCTION_TRACE_ON  ShowFunction sfunc(__FILE__,__LINE__,__FUNCTION__);
#define FUNCTION_TRACE_OFF ;

}
