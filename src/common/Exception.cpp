#include "Exception.h"

#if 0

#include "GeneralFunctions.h"
#include "AnsiEscapeCodes.h"
#include <iostream>
#include <sstream>

namespace SmartMet
{


/*! \brief The constructor of the class. */

Exception::Exception()
{
  timestamp = boost::posix_time::second_clock::local_time();
  line = 0;
  prevException = NULL;
}





/*! \brief The copy constructor of the class. */

Exception::Exception(const Exception& _exception)
{
  timestamp = _exception.timestamp;
  filename = _exception.filename;
  line = _exception.line;
  function = _exception.function;
  message = _exception.message;
  detailVector = _exception.detailVector;
  parameterVector = _exception.parameterVector;
  prevException = NULL;
  if (_exception.prevException != NULL)
    prevException = new Exception(*_exception.prevException);
}





/*! \brief The constructor of the class. */

Exception::Exception(const char *_filename,int _line,const char *_function,std::string _message,Exception *_prevException)
{
  // printf("EXCEPTION %s:%d:%s\n",_filename,_line,_function);
  timestamp = boost::posix_time::second_clock::local_time();
  filename = _filename;
  line = _line;
  function = _function;
  message = _message;
  prevException = NULL;
  if (_prevException != NULL)
  {
    prevException = new Exception(*_prevException);
  }
  else
  {
    try
    {
      throw;
    }
    catch (Exception& e)
    {
      prevException = new Exception(e);
    }
    catch (std::out_of_range& e)
    {
      prevException = new Exception(_filename,_line,_function,
          std::string("[Out of range] ") + e.what());
    }
    catch (std::invalid_argument& e)
    {
      prevException = new Exception(_filename,_line,_function,
          std::string("[Invalid argument] ") + e.what());
    }
    catch (std::length_error& e)
    {
      prevException = new Exception(_filename,_line,_function,
          std::string("[Length error] ") + e.what());
    }
    catch (std::domain_error& e)
    {
      prevException = new Exception(_filename,_line,_function,
          std::string("[Domain error] ") + e.what());
    }
    catch (std::range_error& e)
    {
      prevException = new Exception(_filename,_line,_function,
          std::string("[Range error] ") + e.what());
    }
    catch (std::overflow_error& e)
    {
      prevException = new Exception(_filename,_line,_function,
          std::string("[Overflow error] ") + e.what());
    }
    catch (std::underflow_error& e)
    {
      prevException = new Exception(_filename,_line,_function,
          std::string("[Underflow error] ") + e.what());
    }
    catch (std::runtime_error& e)
    {
      prevException = new Exception(_filename,_line,_function,
          std::string("[Runtime error] ") + e.what());
    }
    catch (std::logic_error& e)
    {
      prevException = new Exception(_filename,_line,_function,
          std::string("[Logic error] ") + e.what());
    }
    catch (std::exception& e)
    {
      prevException = new Exception(_filename,_line,_function,
          std::string("[Exception] ") + e.what());
    }
    catch (...)
    {
      prevException = new Exception(_filename,_line,_function,"Unknown exception");
    }
  }
}





/*! \brief The constructor of the class. */

Exception::Exception(const char *_filename,int _line,const char *_function,std::string _message)
{
  // printf("EXCEPTION %s:%d:%s\n",_filename,_line,_function);
  timestamp = boost::posix_time::second_clock::local_time();
  filename = _filename;
  line = _line;
  function = _function;
  message = _message;
  prevException = NULL;
}





/*! \brief The destructor of the class. */

Exception::~Exception()
{
  if (prevException != NULL)
    delete prevException;
}





std::string Exception::getFilename()
{
  return filename;
}





int Exception::getLine()
{
  return line;
}





std::string Exception::getFunction()
{
  return function;
}





std::string Exception::getMessage()
{
  return message;
}





Exception* Exception::getPrevException()
{
  return prevException;
}





Exception* Exception::getFirstException()
{
  if (prevException != NULL)
    return prevException->getFirstException();

  return this;
}





TimeStamp Exception::getTimeStamp()
{
  return timestamp;
}





unsigned int Exception::getExceptionCount()
{
  unsigned int count = 0;
  Exception *e = this;
  while (e != NULL)
  {
    count++;
    e = e->getPrevException();
  }
  return count;
}





Exception* Exception::getExceptionByIndex(unsigned int _index)
{
  unsigned int count = 0;
  Exception *e = this;
  while (e != NULL)
  {
    if (count == _index)
      return e;

    count++;
    e = e->getPrevException();
  }
  return NULL;
}





void Exception::setTimeStamp(TimeStamp _timestamp)
{
  timestamp = _timestamp;
}





void Exception::addDetail(std::string _detailStr)
{
  detailVector.push_back(_detailStr);
}





void Exception::addDetails(const DetailList& _detailList)
{
  auto begin = _detailList.begin();
  auto end = _detailList.end();

  while (begin != end)
    addDetail(*begin++);
}





void Exception::addParameter(const char *_name,std::string _value)
{
  parameterVector.push_back(std::make_pair(std::string(_name),_value));
}





const char* Exception::getDetailByIndex(unsigned int _index)
{
  if (_index < getDetailCount())
    return detailVector.at(_index).c_str();

  return NULL;
}





const char* Exception::getParameterNameByIndex(unsigned int _index)
{
  if (_index < getParameterCount())
  {
    auto p = parameterVector.at(_index);
    return p.first.c_str();
  }

  return NULL;
}





const char* Exception::getParameterValue(const char *_name)
{
  size_t size = parameterVector.size();
  if (size > 0)
  {
    for (size_t t=0; t<size; t++)
    {
      auto p = parameterVector.at(t);
      if (p.first == _name)
        return p.second.c_str();
    }
  }
  return NULL;
}





const char* Exception::getParameterValueByIndex(unsigned int _index)
{
  if (_index < getParameterCount())
  {
    auto p = parameterVector.at(_index);
    return p.second.c_str();
  }

  return NULL;
}





Exception* Exception::getExceptionByParameterName(const char *_paramName)
{
  if (getParameterValue(_paramName) != NULL)
    return this;

  if (prevException == NULL)
    return NULL;

  return prevException->getExceptionByParameterName(_paramName);
}





unsigned int Exception::getDetailCount()
{
  return static_cast<unsigned int>(detailVector.size());
}





unsigned int Exception::getParameterCount()
{
  return static_cast<unsigned int>(parameterVector.size());
}





std::string Exception::what()
{
  std::stringbuf buffer;
  std::ostream stream(&buffer);

  stream << *this;

  return buffer.str();
}





std::ostream& operator<<(std::ostream& _ostream,Exception& _exception)
{
  _ostream << "\n";
  _ostream << ANSI_BG_RED << ANSI_FG_WHITE << ANSI_BOLD_ON << " ##### " << _exception.timestamp << " ##### " << ANSI_BOLD_OFF << ANSI_FG_DEFAULT << ANSI_BG_DEFAULT;
  _ostream << "\n\n";

  Exception *e = &_exception;
  while (e != NULL)
  {
    _ostream << ANSI_FG_RED << ANSI_BOLD_ON << "EXCEPTION "  << ANSI_BOLD_OFF << e->message  << ANSI_FG_DEFAULT << "\n";

    //_ostream << ANSI_BOLD_ON << " * Time       : " << ANSI_BOLD_OFF << e->timestamp << "\n";
    _ostream << ANSI_BOLD_ON << " * Function   : " << ANSI_BOLD_OFF << e->function << "\n";
    _ostream << ANSI_BOLD_ON << " * Location   : " << ANSI_BOLD_OFF << e->filename << ":" << e->line << "\n";

    size_t size = e->detailVector.size();
    if (size > 0)
    {
      _ostream << ANSI_BOLD_ON << " * Details    :\n" << ANSI_BOLD_OFF;
      for (size_t t=0; t<size; t++)
      {
        _ostream << "   - " << e->detailVector.at(t) << "\n";
      }
    }

    size = e->parameterVector.size();
    if (size > 0)
    {
      _ostream << ANSI_BOLD_ON << " * Parameters :\n" << ANSI_BOLD_OFF;
        for (size_t t=0; t<size; t++)
      {
        auto p = e->parameterVector.at(t);
        _ostream << "   - " << p.first << " = " << p.second << "\n";
      }
    }
    _ostream << "\n";

    e = e->prevException;
  }

  return _ostream;
}

} // namespace BrainStorm

#endif
