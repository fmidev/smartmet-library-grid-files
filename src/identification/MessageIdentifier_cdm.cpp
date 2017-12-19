#include "MessageIdentifier_cdm.h"
#include "GribDef.h"
#include "common/Exception.h"
#include "common/ShowFunction.h"


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{
namespace Identification
{



MessageIdentifier_cdm::MessageIdentifier_cdm()
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





MessageIdentifier_cdm::~MessageIdentifier_cdm()
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamId MessageIdentifier_cdm::getParamIdByName(std::string paramName)
{
  FUNCTION_TRACE
  try
  {
    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamLevelId MessageIdentifier_cdm::getParamLevelId(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    return message.getGridParameterLevelId();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamLevelId MessageIdentifier_cdm::getParamLevelId(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    return message.getGridParameterLevelId();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_cdm::getParamId(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    const GRIB1::ProductSection *productSection =  message.getProductSection();
    if (productSection == NULL)
      return std::string("");

    char tmp[200];
    char *p = (char*)tmp;


    p += sprintf(p,"VAR_%u-%u-%u-%u",
        productSection->getCentre(),
        productSection->getSubCentre(),
        productSection->getTableVersion(),
        productSection->getIndicatorOfParameter());

    if (productSection->getIndicatorOfTypeOfLevel() != 0xFF)
    {
      p += sprintf(p,"_L%u",productSection->getIndicatorOfTypeOfLevel());
      //p += sprintf(p,"_%u",productSection->getLevel());
    }

    TimeRangeDef timeRangeDef;
    if (gribDef.getGrib1TimeRangeDef(productSection->getUnitOfTimeRange(),timeRangeDef))
    {
      if (timeRangeDef.mName.length() > 0)
        p += sprintf(p,"_I%s",timeRangeDef.mName.c_str());
    }

    return std::string(tmp);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_cdm::getParamId(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    const GRIB2::ProductSection *productSection =  message.getProductSection();
    if (productSection == NULL)
      return std::string("");

    GRIB2::IndicatorSection_sptr indicatorSection = message.getIndicatorSection();
    if (!indicatorSection)
      return std::string("");

    char tmp[200];
    char *p = (char*)tmp;


    p += sprintf(p,"VAR_%u-%u-%u",
        indicatorSection->getDiscipline(),
        *productSection->getGribParameterCategory(),
        *productSection->getGribParameterNumber());

    LevelDef levelDef;
    if (gribDef.getGrib2LevelDef(message.getGridParameterLevelId(),levelDef))
    {
      p += sprintf(p,"_L%u",message.getGridParameterLevelId());
      // p += sprintf(p,"_%u",message.getGridParameterLevel());
    }


    GRIB2::ProductDefinition *productDef = productSection->getProductDefinition();
    if (productDef != NULL)
    {
      const GRIB2::StatisticalSettings *stat = productDef->getStatistical();
      if (stat != NULL)
      {
        TimeRangeDef timeRangeDef;
        if (gribDef.getGrib2TimeRangeDef(*stat->getIndicatorOfUnitForTimeRange(),timeRangeDef))
        {
          if (timeRangeDef.mName.length() > 0)
            p += sprintf(p,"_I%s",timeRangeDef.mName.c_str());
        }
      }
    }

    return std::string(tmp);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_cdm::getParamName(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    const GRIB1::ProductSection *productSection =  message.getProductSection();
    if (productSection == NULL)
      return std::string("");

    char tmp[200];
    tmp[0] = '\0';
    char *p = (char*)tmp;

    Parameter_grib1 param;
    if (gribDef.getGrib1ParameterDefByTable(productSection->getTableVersion(),productSection->getIndicatorOfParameter(),param))
    {
      if (productSection->getTableVersion() < 128  &&  param.mParameterName.length() > 0)
      {
        p += sprintf(p,"%s",param.mParameterName.c_str());
      }
      else
      {
        p += sprintf(p,"VAR_%u-%u-%u-%u",
                productSection->getCentre(),
                productSection->getSubCentre(),
                productSection->getTableVersion(),
                productSection->getIndicatorOfParameter());
      }

      LevelDef levelDef;
      if (gribDef.getGrib1LevelDef(productSection->getIndicatorOfTypeOfLevel(),levelDef))
      {
        if (levelDef.mName.length() > 0)
        {
          p += sprintf(p,"_%s",levelDef.mName.c_str());
          //p += sprintf(p,"_%u",productSection->getLevel());
        }
      }

      TimeRangeDef timeRangeDef;
      if (gribDef.getGrib1TimeRangeDef(productSection->getUnitOfTimeRange(),timeRangeDef))
      {
        if (timeRangeDef.mName.length() > 0)
          p += sprintf(p,"_%s",timeRangeDef.mName.c_str());
      }
    }

    return std::string(tmp);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_cdm::getParamName(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    const GRIB2::ProductSection *productSection =  message.getProductSection();
    if (productSection == NULL)
      return std::string("");

    GRIB2::IndicatorSection_sptr indicatorSection = message.getIndicatorSection();
    if (!indicatorSection)
      return std::string("");

    char tmp[200];
    tmp[0] = '\0';
    char *p = (char*)tmp;

    ParameterDefinition def;
    if (gribDef.getGribParamDef(indicatorSection->getDiscipline(),*productSection->getGribParameterCategory(),*productSection->getGribParameterNumber(),def)
      &&  def.mParameterName.length() > 0)
    {
      p += sprintf(p,"%s",def.mParameterName.c_str());
    }
    else
    {
      p += sprintf(p,"VAR_%u-%u-%u",
          indicatorSection->getDiscipline(),
          *productSection->getGribParameterCategory(),
          *productSection->getGribParameterNumber());
    }

    LevelDef levelDef;
    if (gribDef.getGrib2LevelDef(message.getGridParameterLevelId(),levelDef))
    {
      if (levelDef.mName.length() > 0)
      {
        p += sprintf(p,"_%s",levelDef.mName.c_str());
        //p += sprintf(p,"_%u",message.getGridParameterLevel());
      }
    }

    GRIB2::ProductDefinition *productDef = productSection->getProductDefinition();
    if (productDef != NULL)
    {
      const GRIB2::StatisticalSettings *stat = productDef->getStatistical();
      if (stat != NULL)
      {
        TimeRangeDef timeRangeDef;
        if (gribDef.getGrib2TimeRangeDef(*stat->getIndicatorOfUnitForTimeRange(),timeRangeDef))
        {
          if (timeRangeDef.mName.length() > 0)
            p += sprintf(p,"_I%s",timeRangeDef.mName.c_str());
        }
      }
    }

    return std::string(tmp);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_cdm::getParamDescription(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    T::ParamId paramId = message.getFmiParameterId();
    if (paramId.length())
      return gribDef.mMessageIdentifier_fmi.getParamDescription(message);

    paramId = message.getGribParameterId();
    if (paramId.length())
      return gribDef.mMessageIdentifier_grib1.getParamDescription(message);

    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_cdm::getParamDescription(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    T::ParamId paramId = message.getFmiParameterId();
    if (paramId.length())
      return gribDef.mMessageIdentifier_fmi.getParamDescription(message);

    paramId = message.getGribParameterId();
    if (paramId.length())
      return gribDef.mMessageIdentifier_grib2.getParamDescription(message);

    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_cdm::getParamUnits(GRIB1::Message& message)
{
  try
  {
    T::ParamId paramId = message.getFmiParameterId();
    if (paramId.length())
      return gribDef.mMessageIdentifier_fmi.getParamUnits(message);

    paramId = message.getGribParameterId();
    if (paramId.length())
      return gribDef.mMessageIdentifier_grib1.getParamUnits(message);

    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




std::string MessageIdentifier_cdm::getParamUnits(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    T::ParamId paramId = message.getFmiParameterId();
    if (paramId.length())
      return gribDef.mMessageIdentifier_fmi.getParamUnits(message);

    paramId = message.getGribParameterId();
    if (paramId.length())
      return gribDef.mMessageIdentifier_grib2.getParamUnits(message);

    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::InterpolationMethod MessageIdentifier_cdm::getParamInterpolationMethod(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    T::ParamId paramId = message.getFmiParameterId();
    if (paramId.length())
      return gribDef.mMessageIdentifier_fmi.getParamInterpolationMethod(message);

    paramId = message.getGribParameterId();
    if (paramId.length())
      return gribDef.mMessageIdentifier_grib1.getParamInterpolationMethod(message);

    return T::InterpolationMethod::Linear;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::InterpolationMethod MessageIdentifier_cdm::getParamInterpolationMethod(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    T::ParamId paramId = message.getFmiParameterId();
    if (paramId.length())
      return gribDef.mMessageIdentifier_fmi.getParamInterpolationMethod(message);

    paramId = message.getGribParameterId();
    if (paramId.length())
      return gribDef.mMessageIdentifier_grib2.getParamInterpolationMethod(message);

    return T::InterpolationMethod::Linear;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}

}
}
