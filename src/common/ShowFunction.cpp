#include "ShowFunction.h"
#include "GeneralFunctions.h"

namespace SmartMet
{


Log *globalTraceLog = nullptr;
int globalTraceLevel = 0;



ShowFunction::ShowFunction(const char *_file,uint _line,const char *_function)
{
  filename = _file;
  line = _line;
  function = _function;
  startTime = getTime();

  if (globalTraceLog != nullptr)
  {
    PRINT_DATA(globalTraceLog,"[%04u][        ] %sSTART %s [%s]\n",_line,space(globalTraceLevel).c_str(),_function,_file);
  }
  else
  {
    printf("[%04u][        ] %sSTART %s [%s]\n",_line,space(globalTraceLevel).c_str(),_function,_file);
    fflush(stdout);
  }
  globalTraceLevel++;
}




ShowFunction::~ShowFunction()
{
  unsigned long long endTime = getTime();
  globalTraceLevel--;

  if (globalTraceLog != nullptr)
  {
    PRINT_DATA(globalTraceLog,"[%04u][%.06f] %sEND\n",line,C_DOUBLE(endTime-startTime)/1000000,space(globalTraceLevel).c_str());
  }
  else
  {
    printf("[%04u][%.06f] %sEND\n",line,C_DOUBLE(endTime-startTime)/1000000,space(globalTraceLevel).c_str());
    fflush(stdout);
  }
}


}
