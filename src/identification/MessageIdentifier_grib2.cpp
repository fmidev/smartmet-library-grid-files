#include "MessageIdentifier_grib2.h"
#include "MessageIdentifier_grib1.h"
#include "GribDef.h"
#include "common/Exception.h"


namespace SmartMet
{
namespace Identification
{


MessageIdentifier_grib2::MessageIdentifier_grib2()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





MessageIdentifier_grib2::~MessageIdentifier_grib2()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamId MessageIdentifier_grib2::getParamId(GRIB1::Message& message)
{
  try
  {
    return gribDef.mMessageIdentifier_grib1.getParamId(message);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamId MessageIdentifier_grib2::getParamId(GRIB2::Message& message)
{
  try
  {
    T::ParamId paramId;

    GRIB2::IndicatorSection_sptr indicatorSection = message.getIndicatorSection();
    if (!indicatorSection)
      return paramId;

    std::size_t parameterCount = gribDef.mParameters_grib2.size();
    if (parameterCount == 0)
      return paramId;


    // We have to go through all parameters and try to find the best match.

    uint maxMatchPoints = 0;

    for (std::size_t t=0; t<parameterCount; t++)
    {
      Parameter_grib2 p = gribDef.mParameters_grib2[t];
      if (p.mDiscipline == indicatorSection->getDiscipline())
      {
         uint matchPoints = countParameterMatchPoints(message,p);
         if (matchPoints > maxMatchPoints)
         {
           maxMatchPoints = matchPoints;
           paramId = p.mGribParameterId;
         }
      }
    }

    return paramId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamId MessageIdentifier_grib2::getParamIdByName(std::string gribParamName)
{
  try
  {
    const Parameter_grib2 *p = gribDef.getParameterDefByName_grib2(gribParamName);
    if (p == NULL)
      return std::string("");

    return p->mGribParameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamLevelId MessageIdentifier_grib2::getParamLevelId(GRIB1::Message& message)
{
  try
  {
    // ToDo: Convert GRIB 1 parameter levels to GRIB 2 parameter levels.
    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamLevelId MessageIdentifier_grib2::getParamLevelId(GRIB2::Message& message)
{
  try
  {
    return message.getParameterLevelId();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint MessageIdentifier_grib2::countParameterMatchPoints(GRIB2::Message& message,const Parameter_grib2& p)
{
  try
  {
    GRIB2::ProductSection_cptr productSection = message.getProductSection();
    if (productSection == NULL)
      return 0;

    GRIB2::ProductDefinition *productDefinition = productSection->getProductDefinition();
    if (productDefinition == NULL)
      return 0;

    GRIB2::IdentificSection_sptr identificationSection =  message.getIdentificationSection();
    if (identificationSection == NULL)
      return 0;

    const GRIB2::ParameterSettings *s = productDefinition->getParameter();
    const GRIB2::HorizontalSettings *h = productDefinition->getHorizontal();
    const GRIB2::StatisticalSettings *stat = productDefinition->getStatistical();

    uint matchPoints = 0;

    if (p.mCentre)
    {
      if (p.mCentre != identificationSection->getCentre())
        return 0;

      matchPoints++;
    }

    if (s != NULL)
    {
      if (s->getParameterCategory())
      {
        if (p.mParameterCategory != *s->getParameterCategory())
          return 0;

        matchPoints++;
      }
      else
      {
        return 0;
      }

      if (s->getParameterNumber())
      {
        if (p.mParameterNumber != *s->getParameterNumber())
          return 0;

        matchPoints++;
      }
      else
      {
        return 0;
      }

      if (p.mTypeOfGeneratingProcess)
      {
        if (!s->getTypeOfGeneratingProcess())
          return 0;

        if (p.mTypeOfGeneratingProcess != *s->getTypeOfGeneratingProcess())
          return 0;

        matchPoints++;
      }
    }

    if (stat != NULL)
    {
      if (p.mTypeOfStatisticalProcessing)
      {
        if (!stat->getTypeOfStatisticalProcessing())
          return 0;

        if (p.mTypeOfStatisticalProcessing != *stat->getTypeOfStatisticalProcessing())
          return 0;

        matchPoints++;
      }
    }

    if (h != NULL)
    {
      if (p.mTypeOfSecondFixedSurface)
      {
        if (!h->getTypeOfSecondFixedSurface())
          return 0;

        if (p.mTypeOfSecondFixedSurface != *h->getTypeOfSecondFixedSurface())
          return 0;

        matchPoints++;
      }

      if (p.mTypeOfFirstFixedSurface)
      {
        if (!h->getTypeOfFirstFixedSurface())
          return 0;

        if (p.mTypeOfFirstFixedSurface != *h->getTypeOfFirstFixedSurface())
          return 0;

        matchPoints++;
      }

      if (p.mScaleFactorOfFirstFixedSurface)
      {
        if (!h->getScaleFactorOfFirstFixedSurface())
          return 0;

        if (p.mScaleFactorOfFirstFixedSurface != *h->getScaleFactorOfFirstFixedSurface())
          return 0;

        matchPoints++;
      }

      if (p.mScaledValueOfFirstFixedSurface)
      {
        if (!h->getScaledValueOfFirstFixedSurface())
          return 0;

        if (p.mScaledValueOfFirstFixedSurface != *h->getScaledValueOfFirstFixedSurface())
          return 0;

        matchPoints++;
      }

      if (p.mScaledValueOfSecondFixedSurface)
      {
        if (!h->getScaledValueOfSecondFixedSurface())
          return 0;

        if (p.mScaledValueOfSecondFixedSurface != *h->getScaledValueOfSecondFixedSurface())
          return 0;

        matchPoints++;
      }

      if (p.mScaleFactorOfSecondFixedSurface)
      {
        if (!h->getScaleFactorOfSecondFixedSurface())
          return 0;

        if (p.mScaleFactorOfSecondFixedSurface != *h->getScaleFactorOfSecondFixedSurface())
          return 0;

        matchPoints++;
      }

      if (p.mTypeOfFirstFixedSurface)
      {
        if (!h->getTypeOfFirstFixedSurface())
          return 0;

        if (p.mTypeOfFirstFixedSurface != *h->getTypeOfFirstFixedSurface())
          return 0;

        matchPoints++;
      }
    }

    return matchPoints;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}




std::string MessageIdentifier_grib2::getParamName(GRIB1::Message& message)
{
  try
  {
    const Parameter_grib2 *p = gribDef.getParameterDefById_grib2(message.getGribParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_grib2::getParamName(GRIB2::Message& message)
{
  try
  {
    const Parameter_grib2 *p = gribDef.getParameterDefById_grib2(message.getGribParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_grib2::getParamDescription(GRIB1::Message& message)
{
  try
  {
    const Parameter_grib2 *p = gribDef.getParameterDefById_grib2(message.getGribParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_grib2::getParamDescription(GRIB2::Message& message)
{
  try
  {
    const Parameter_grib2 *p = gribDef.getParameterDefById_grib2(message.getGribParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_grib2::getParamUnits(GRIB1::Message& message)
{
  try
  {
    const Parameter_grib2 *p = gribDef.getParameterDefById_grib2(message.getGribParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_grib2::getParamUnits(GRIB2::Message& message)
{
  try
  {
    const Parameter_grib2 *p = gribDef.getParameterDefById_grib2(message.getGribParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::InterpolationMethod MessageIdentifier_grib2::getParamInterpolationMethod(GRIB1::Message& message)
{
  try
  {
    const Parameter_grib2 *p = gribDef.getParameterDefById_grib2(message.getGribParameterId());
    if (p != NULL)
      return gribDef.getPreferredInterpolationMethodByUnits(p->mParameterUnits);

    return T::InterpolationMethod::Linear;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




T::InterpolationMethod MessageIdentifier_grib2::getParamInterpolationMethod(GRIB2::Message& message)
{
  try
  {
    const Parameter_grib2 *p = gribDef.getParameterDefById_grib2(message.getGribParameterId());
    if (p != NULL)
      return gribDef.getPreferredInterpolationMethodByUnits(p->mParameterUnits);

    return T::InterpolationMethod::Linear;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}

}
}
