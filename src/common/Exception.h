#pragma once


#include <spine/Exception.h>


//#define CDP  __FILE__,__LINE__,__PRETTY_FUNCTION__

#define CODE_LOCATION std::string(__FILE__) + ":" + std::to_string(__LINE__) + ":" + std::string(__PRETTY_FUNCTION__)

extern const char *exception_implementation_required;
extern const char *exception_operation_failed;




#if 0
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace SmartMet
{

typedef boost::posix_time::ptime TimeStamp;
typedef std::vector<std::pair<std::string,std::string>> ParameterVector;
typedef std::vector<std::string> DetailVector;
typedef std::list<std::string> DetailList;


class Exception
{
 public:
                  Exception();
                  Exception(const Exception& _exception);

                  // Use the following constructor when there is no previous exception in place

                  Exception(const char *_filename,int _line,const char *_function,std::string _message);

                  // Use the following constructor when there is previous exception in place
                  // (i.e when you are in a "catch" block. If '_prevExeption' parameter is nullptr then
                  // the constructor automatically detects the content of the previous exception.

                  Exception(const char *_filename,int _line,const char *_function,std::string _message,Exception *_prevException);

                  // Destructor
  virtual         ~Exception();

                  // The following methods can be used for adding some additional information
                  // related to the current exception.

  void            addDetail(std::string _detailStr);
  void            addDetails(const DetailList& _detailList);

                  // This method can be used for adding named parameters into the exception.
                  // The parameters can be "incorrect" values that caused the exception. They
                  // can be also used for delivering additional information to the exception
                  // catchers ("preferred HTTP status code",etc.).

  void            addParameter(const char *_name,std::string _value);

  std::string     getFilename();
  int             getLine();
  std::string     getFunction();
  std::string     getMessage();
  Exception*      getFirstException();
  Exception*      getExceptionByIndex(unsigned int _index);
  Exception*      getExceptionByParameterName(const char *_paramName);
  unsigned int    getExceptionCount();
  const char*     getDetailByIndex(unsigned int _index);
  unsigned int    getDetailCount();
  unsigned int    getParameterCount();
  const char*     getParameterNameByIndex(unsigned int _index);
  const char*     getParameterValue(const char *_name);
  const char*     getParameterValueByIndex(unsigned int _index);
  Exception*      getPrevException();
  TimeStamp       getTimeStamp();
  void            setTimeStamp(TimeStamp _timestamp);
  std::string     what();

  friend std::ostream& operator<<(std::ostream&,Exception&);

 protected:
  TimeStamp       timestamp;
  std::string     filename;
  int             line;
  std::string     function;
  std::string     message;
  Exception*      prevException;
  ParameterVector parameterVector;
  DetailVector    detailVector;
};



}
#endif
