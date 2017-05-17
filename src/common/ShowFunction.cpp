#include "ShowFunction.h"

namespace SmartMet
{

ShowFunction::ShowFunction(const char *_file,uint _line,const char *_function)
{
  filename = _file;
  line = _line;
  function = _function;
  printf("[%04u] START %s:%s\n",_line,_file,_function);
}




ShowFunction::~ShowFunction()
{
  printf("[%04u] END   %s:%s\n",line,filename.c_str(),function.c_str());
}


}
