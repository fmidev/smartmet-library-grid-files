#include "ShowFunction.h"
#include "GeneralFunctions.h"

namespace SmartMet
{

ShowFunction::ShowFunction(const char *_file,uint _line,const char *_function)
{
  filename = _file;
  line = _line;
  function = _function;
  startTime = getTime();

  printf("[%04u][        ] START %s:%s\n",_line,_file,_function);
  fflush(stdout);
}




ShowFunction::~ShowFunction()
{
  unsigned long long endTime = getTime();
  printf("[%04u][%.06f] END   %s:%s\n",line,(double)(endTime-startTime)/1000000,filename.c_str(),function.c_str());
  fflush(stdout);
}


}
