#include "MessageIdentifier_cdm.h"
#include "common/Exception.h"
#include "GribDef.h"


namespace SmartMet
{
namespace Identification
{



MessageIdentifier_cdm::MessageIdentifier_cdm()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





MessageIdentifier_cdm::~MessageIdentifier_cdm()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




T::ParamId MessageIdentifier_cdm::getParamIdByName(std::string paramName)
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





T::ParamLevelId MessageIdentifier_cdm::getParamLevelId(GRIB1::Message& message)
{
  try
  {
    return message.getParameterLevelId();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::ParamLevelId MessageIdentifier_cdm::getParamLevelId(GRIB2::Message& message)
{
  try
  {
    return message.getParameterLevelId();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string MessageIdentifier_cdm::getParamId(GRIB1::Message& message)
{
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

    TimeRangeDef_cptr timeRangeDef = gribDef.getTimeRangeDef_grib1(productSection->getUnitOfTimeRange());
    if (timeRangeDef != NULL  &&  timeRangeDef->mName.length() > 0)
      p += sprintf(p,"_I%s",timeRangeDef->mName.c_str());

    return std::string(tmp);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string MessageIdentifier_cdm::getParamId(GRIB2::Message& message)
{
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

    LevelDef_cptr levelDef = gribDef.getLevelDef_grib2(message.getParameterLevelId());
    if (levelDef != NULL /* &&  levelDef->mName.length() > 0*/)
    {
      p += sprintf(p,"_L%u",message.getParameterLevelId());
      // p += sprintf(p,"_%u",message.getParameterLevel());
    }


    GRIB2::ProductDefinition *productDef = productSection->getProductDefinition();
    if (productDef != NULL)
    {
      const GRIB2::StatisticalSettings *stat = productDef->getStatistical();
      if (stat != NULL)
      {
        TimeRangeDef_cptr timeRangeDef = gribDef.getTimeRangeDef_grib2(*stat->getIndicatorOfUnitForTimeRange());
        if (timeRangeDef != NULL  &&  timeRangeDef->mName.length() > 0)
          p += sprintf(p,"_I%s",timeRangeDef->mName.c_str());
      }
    }

    return std::string(tmp);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string MessageIdentifier_cdm::getParamName(GRIB1::Message& message)
{
  try
  {
    const GRIB1::ProductSection *productSection =  message.getProductSection();
    if (productSection == NULL)
      return std::string("");

    char tmp[200];
    tmp[0] = '\0';
    char *p = (char*)tmp;

    Parameter_grib1_cptr param = gribDef.getParameterDef_grib1(productSection->getTableVersion(),productSection->getIndicatorOfParameter());

    if (productSection->getTableVersion() < 128  &&  (param != NULL  &&  param->mParameterName.length() > 0))
    {
      p += sprintf(p,"%s",param->mParameterName.c_str());
    }
    else
    {
      p += sprintf(p,"VAR_%u-%u-%u-%u",
              productSection->getCentre(),
              productSection->getSubCentre(),
              productSection->getTableVersion(),
              productSection->getIndicatorOfParameter());
    }

    LevelDef_cptr levelDef = gribDef.getLevelDef_grib1(productSection->getIndicatorOfTypeOfLevel());
    if (levelDef != NULL  &&  levelDef->mName.length() > 0)
    {
      p += sprintf(p,"_%s",levelDef->mName.c_str());
      //p += sprintf(p,"_%u",productSection->getLevel());
    }

    TimeRangeDef_cptr timeRangeDef = gribDef.getTimeRangeDef_grib1(productSection->getUnitOfTimeRange());
    if (timeRangeDef != NULL  &&  timeRangeDef->mName.length() > 0)
      p += sprintf(p,"_%s",timeRangeDef->mName.c_str());

    return std::string(tmp);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string MessageIdentifier_cdm::getParamName(GRIB2::Message& message)
{
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

    ParameterDefinition_cptr def = gribDef.getGribParamDef(indicatorSection->getDiscipline(),*productSection->getGribParameterCategory(),*productSection->getGribParameterNumber());

    if (def != NULL  &&  def->mParameterName.length() > 0)
    {
      p += sprintf(p,"%s",def->mParameterName.c_str());
    }
    else
    {
      p += sprintf(p,"VAR_%u-%u-%u",
          indicatorSection->getDiscipline(),
          *productSection->getGribParameterCategory(),
          *productSection->getGribParameterNumber());
    }

    LevelDef_cptr levelDef = gribDef.getLevelDef_grib2(message.getParameterLevelId());
    if (levelDef != NULL  &&  levelDef->mName.length() > 0)
    {
      p += sprintf(p,"_%s",levelDef->mName.c_str());
      //p += sprintf(p,"_%u",message.getParameterLevel());
    }

    GRIB2::ProductDefinition *productDef = productSection->getProductDefinition();
    if (productDef != NULL)
    {
      const GRIB2::StatisticalSettings *stat = productDef->getStatistical();
      if (stat != NULL)
      {
        TimeRangeDef_cptr timeRangeDef = gribDef.getTimeRangeDef_grib2(*stat->getIndicatorOfUnitForTimeRange());
        if (timeRangeDef != NULL  &&  timeRangeDef->mName.length() > 0)
          p += sprintf(p,"_I%s",timeRangeDef->mName.c_str());
      }
    }

    return std::string(tmp);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string MessageIdentifier_cdm::getParamDescription(GRIB1::Message& message)
{
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string MessageIdentifier_cdm::getParamDescription(GRIB2::Message& message)
{
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




std::string MessageIdentifier_cdm::getParamUnits(GRIB2::Message& message)
{
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




T::InterpolationMethod MessageIdentifier_cdm::getParamInterpolationMethod(GRIB1::Message& message)
{
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




T::InterpolationMethod MessageIdentifier_cdm::getParamInterpolationMethod(GRIB2::Message& message)
{
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}

}
}
