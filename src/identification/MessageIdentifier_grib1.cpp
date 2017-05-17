#include "MessageIdentifier_grib1.h"
#include "MessageIdentifier_grib2.h"
#include "common/Exception.h"
#include "GribDef.h"


namespace SmartMet
{
namespace Identification
{



MessageIdentifier_grib1::MessageIdentifier_grib1()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





MessageIdentifier_grib1::~MessageIdentifier_grib1()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::ParamId MessageIdentifier_grib1::getParamId(GRIB1::Message& message)
{
  try
  {
    const GRIB1::ProductSection *productSection =  message.getProductSection();
    if (productSection == NULL)
      return std::string("");

    uint maxPoints = 1;
    T::ParamId parameterId;
    std::size_t paramCount = gribDef.mParameters_grib1.size();
    for (std::size_t t=0; t<paramCount; t++)
    {
      uint requiredPoints = 0;
      uint points = 0;
      Parameter_grib1 p = gribDef.mParameters_grib1[t];

      if (p.mCentre)
      {
        requiredPoints++;
        if (p.mCentre == productSection->getCentre())
          points++;
      }

      if (p.mIndicatorOfParameter)
      {
        requiredPoints++;
        if (p.mIndicatorOfParameter == productSection->getIndicatorOfParameter())
          points++;
      }

      if (p.mIndicatorOfTypeOfLevel)
      {
        requiredPoints++;
        if (p.mIndicatorOfTypeOfLevel == productSection->getIndicatorOfTypeOfLevel())
          points++;
      }

      if (p.mTable2Version)
      {
        requiredPoints++;
        if (p.mTable2Version == productSection->getTableVersion())
          points++;
      }

      if (p.mParameterLevel)
      {
        if (p.mParameterLevel == productSection->getLevel())
          points++;
      }

      if (points >= requiredPoints  &&  points > maxPoints)
      {
         maxPoints = points;
         parameterId = p.mGribParameterId;
      }
    }
    return parameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::ParamId MessageIdentifier_grib1::getParamId(GRIB2::Message& message)
{
  try
  {
    return gribDef.mMessageIdentifier_grib2.getParamId(message);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::ParamLevelId MessageIdentifier_grib1::getParamLevelId(GRIB1::Message& message)
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





T::ParamLevelId MessageIdentifier_grib1::getParamLevelId(GRIB2::Message& message)
{
  try
  {
    // ToDo :: Convert GRIB 2 parameter level id to GRIB 1 parameter level id.
    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string MessageIdentifier_grib1::getParamName(GRIB1::Message& message)
{
  try
  {
    const Parameter_grib1 *p = gribDef.getParameterDefById_grib1(message.getGribParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string MessageIdentifier_grib1::getParamName(GRIB2::Message& message)
{
  try
  {
    const Parameter_grib1 *p = gribDef.getParameterDefById_grib1(message.getGribParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string MessageIdentifier_grib1::getParamDescription(GRIB1::Message& message)
{
  try
  {
    const Parameter_grib1 *p = gribDef.getParameterDefById_grib1(message.getGribParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string MessageIdentifier_grib1::getParamDescription(GRIB2::Message& message)
{
  try
  {
    const Parameter_grib1 *p = gribDef.getParameterDefById_grib1(message.getGribParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string MessageIdentifier_grib1::getParamUnits(GRIB1::Message& message)
{
  try
  {
    const Parameter_grib1 *p = gribDef.getParameterDefById_grib1(message.getGribParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string MessageIdentifier_grib1::getParamUnits(GRIB2::Message& message)
{
  try
  {
    const Parameter_grib1 *p = gribDef.getParameterDefById_grib1(message.getGribParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::ParamId MessageIdentifier_grib1::getParamIdByName(std::string gribParamName)
{
  try
  {
    const Parameter_grib1 *p = gribDef.getParameterDefByName_grib1(gribParamName);
    if (p == NULL)
      return std::string("");

    return p->mGribParameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::InterpolationMethod MessageIdentifier_grib1::getParamInterpolationMethod(GRIB1::Message& message)
{
  try
  {
    const Parameter_grib1 *p = gribDef.getParameterDefById_grib1(message.getGribParameterId());
    if (p != NULL)
      return gribDef.getPreferredInterpolationMethodByUnits(p->mParameterUnits);

    return T::InterpolationMethod::Linear;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::InterpolationMethod MessageIdentifier_grib1::getParamInterpolationMethod(GRIB2::Message& message)
{
  try
  {
    const Parameter_grib1 *p = gribDef.getParameterDefById_grib1(message.getGribParameterId());
    if (p != NULL)
      return gribDef.getPreferredInterpolationMethodByUnits(p->mParameterUnits);

    return T::InterpolationMethod::Linear;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}


}
}
