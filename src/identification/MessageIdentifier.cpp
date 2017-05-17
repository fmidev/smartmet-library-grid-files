#include "MessageIdentifier.h"
#include "common/Exception.h"


namespace SmartMet
{
namespace Identification
{



MessageIdentifier::MessageIdentifier()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





MessageIdentifier::~MessageIdentifier()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::ParamId MessageIdentifier::getParamId(GRIB1::Message& message)
{
  try
  {
    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::ParamId MessageIdentifier::getParamId(GRIB2::Message& message)
{
  try
  {
    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::ParamId MessageIdentifier::getParamIdByName(std::string paramName)
{
  try
  {
    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::ParamLevelId MessageIdentifier::getParamLevelId(GRIB1::Message& message)
{
  try
  {
    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::ParamLevelId MessageIdentifier::getParamLevelId(GRIB2::Message& message)
{
  try
  {
    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string MessageIdentifier::getParamName(GRIB1::Message& message)
{
  try
  {
    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




std::string MessageIdentifier::getParamName(GRIB2::Message& message)
{
  try
  {
    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




std::string MessageIdentifier::getParamDescription(GRIB1::Message& message)
{
  try
  {
    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




std::string MessageIdentifier::getParamDescription(GRIB2::Message& message)
{
  try
  {
    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




std::string MessageIdentifier::getParamUnits(GRIB1::Message& message)
{
  try
  {
    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




std::string MessageIdentifier::getParamUnits(GRIB2::Message& message)
{
  try
  {
    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::InterpolationMethod MessageIdentifier::getParamInterpolationMethod(GRIB1::Message& message)
{
  try
  {
    return T::InterpolationMethod::Unknown;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::InterpolationMethod MessageIdentifier::getParamInterpolationMethod(GRIB2::Message& message)
{
  try
  {
    return T::InterpolationMethod::Unknown;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}


}
}
