#include "MessageIdentifier_fmi.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/ShowFunction.h"


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{
namespace Identification
{




MessageIdentifier_fmi::MessageIdentifier_fmi()
{
  FUNCTION_TRACE
  try
  {
    mInitialized = false;
    mLastCheckTime = 0;
    mParameterDefs_modificationTime = 0;
    mParameterDefsExt_modificationTime = 0;
    mParameters_newbase_modificationTime = 0;
    mParameters_grib1_modificationTime = 0;
    mParameters_grib2_modificationTime = 0;
    mLevelDefs_grib1_modificationTime = 0;
    mLevelDefs_grib2_modificationTime = 0;
    mProducerDefs_modificationTime = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





MessageIdentifier_fmi::~MessageIdentifier_fmi()
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





void MessageIdentifier_fmi::init(const char *configDir)
{
  FUNCTION_TRACE
  try
  {
    if (mInitialized)
      return;

    mInitialized = true;
    mConfigDir = configDir;
    updateCheck();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void MessageIdentifier_fmi::updateCheck()
{
  FUNCTION_TRACE
  try
  {
    if (!mInitialized)
      throw SmartMet::Spine::Exception(BCP,"The 'MessageIdentifier_fmi' object is not initialized! Call init() first!");

    if ((mLastCheckTime + 30) < time(0))
    {
      AutoThreadLock lock(&mThreadLock);

      mLastCheckTime = time(0);

      char filename[200];
      char filename2[200];

      sprintf(filename,"%s/parameterDef_fmi.csv",mConfigDir.c_str());
      sprintf(filename2,"%s/parameterDef_fmi_ext.csv",mConfigDir.c_str());

      time_t tt = getFileModificationTime(filename);
      time_t tt2 = getFileModificationTime(filename2);

      if (mParameterDefs_modificationTime != tt  ||  mParameterDefsExt_modificationTime != tt2)
      {
        mParameterDefs.clear();
        loadParameterDefinitions(filename);
        loadParameterDefinitions(filename2);
        mParameterDefs_modificationTime = tt;
        mParameterDefsExt_modificationTime = tt2;
      }

      sprintf(filename,"%s/parameterDef_grib1_fmi.csv",mConfigDir.c_str());
      tt = getFileModificationTime(filename);
      if (mParameters_grib1_modificationTime != tt)
      {
        mParameters_grib1.clear();
        loadGrib1ParameterDefinitions(filename);
        mParameters_grib1_modificationTime = tt;
      }

      sprintf(filename,"%s/parameterDef_grib2_fmi.csv",mConfigDir.c_str());
      tt = getFileModificationTime(filename);
      if (mParameters_grib2_modificationTime != tt)
      {
        mParameters_grib2.clear();
        loadGrib2ParameterDefinitions(filename);
        mParameters_grib2_modificationTime = tt;
      }

      sprintf(filename,"%s/parameterDef_newbase.csv",mConfigDir.c_str());
      tt = getFileModificationTime(filename);
      if (mParameters_newbase_modificationTime != tt)
      {
        mParameters_newbase.clear();
        loadParameterDefinitions_newbase(filename);
        mParameters_newbase_modificationTime = tt;
      }

      sprintf(filename,"%s/levelDef_grib1_fmi.csv",mConfigDir.c_str());
      tt = getFileModificationTime(filename);
      if (mLevelDefs_grib1_modificationTime != tt)
      {
        mLevelDefs_grib1.clear();
        loadGrib1LevelDefinitions(filename);
        mLevelDefs_grib1_modificationTime = tt;
      }

      sprintf(filename,"%s/levelDef_grib2_fmi.csv",mConfigDir.c_str());
      tt = getFileModificationTime(filename);
      if (mLevelDefs_grib2_modificationTime != tt)
      {
        mLevelDefs_grib1.clear();
        loadGrib2LevelDefinitions(filename);
        mLevelDefs_grib2_modificationTime = tt;
      }

      sprintf(filename,"%s/producerDef_grib_fmi.csv",mConfigDir.c_str());
      tt = getFileModificationTime(filename);
      if (mProducerDefs_modificationTime != tt)
      {
        mProducerDefs.clear();
        loadProducerDefinitions(filename);
        mProducerDefs_modificationTime = tt;
      }

    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamId MessageIdentifier_fmi::getParamId(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const GRIB1::ProductSection *productSection =  message.getProductSection();
    if (productSection == NULL)
      return std::string("");

    //uint dbId = 0;
    uint maxPoints = 1;
    T::ParamId parameterId;
    std::size_t paramCount = mParameters_grib1.size();
    for (std::size_t t=0; t<paramCount; t++)
    {
      uint requiredPoints = 0;
      uint points = 0;
      Parameter_grib1_fmi p = mParameters_grib1[t];

      requiredPoints++;
      if (p.mGeneratingProcessIdentifier == productSection->getGeneratingProcessIdentifier())
        points++;

      requiredPoints++;
      if (p.mCentre == productSection->getCentre())
        points++;

      requiredPoints++;
      if (p.mGribTableVersion == productSection->getTableVersion())
        points++;

      requiredPoints++;
      if (p.mGribParameterNumber == productSection->getIndicatorOfParameter())
        points++;

      requiredPoints++;
      if (p.mGribTimerangeIndicator == productSection->getTimeRangeIndicator())
        points++;

      if (p.mGribParameterLevelId  &&  *p.mGribParameterLevelId != 0)
      {
        requiredPoints++;
        if (*p.mGribParameterLevelId == productSection->getIndicatorOfTypeOfLevel())
          points++;
      }

      if (p.mParameterLevel)
      {
        requiredPoints++;
        if (*p.mParameterLevel == productSection->getLevel())
          points++;
      }

       //p.print(std::cout,0,0);
       //printf("POINT %s %u %u\n",p.mFmiParameterId.c_str(),points,requiredPoints);

      if (points >= requiredPoints  &&  points > maxPoints)
      {
         maxPoints = points;
         parameterId = p.mFmiParameterId;
         //dbId = p.mDbId;
      }
    }
    //printf("**** DB ID = %u\n",dbId);
    return parameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamId MessageIdentifier_fmi::getParamId(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    GRIB2::IndicatorSection_sptr indicatorSection = message.getIndicatorSection();
    if (!indicatorSection)
      return std::string("");

    std::size_t parameterCount = mParameters_grib2.size();
    if (parameterCount == 0)
      return std::string("");

    T::ParamId paramId;
    //uint dbId = 0;

    // We have to go through all parameters and try to find the best match.

    uint maxMatchPoints = 0;

    for (std::size_t t=0; t<parameterCount; t++)
    {
      Parameter_grib2_fmi p = mParameters_grib2[t];
      if (p.mDiscipline == indicatorSection->getDiscipline())
      {
         uint matchPoints = countParameterMatchPoints(message,p);
         if (matchPoints > maxMatchPoints)
         {
           maxMatchPoints = matchPoints;
           paramId = p.mFmiParameterId;
           //dbId = p.mDbId;
         }
      }
    }

    //printf("**** DB ID = %u\n",dbId);
    return paramId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint MessageIdentifier_fmi::countParameterMatchPoints(GRIB2::Message& message,const Parameter_grib2_fmi& p)
{
  FUNCTION_TRACE
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

    uint matchPoints = 0;

    if (p.mGeneratingProcessIdentifier != 0)
    {
      if (p.mGeneratingProcessIdentifier == *productSection->getGeneratingProcessIdentifier())
        matchPoints++;
      else
        return 0;
    }

    if (p.mCentre != 0)
    {
      if (p.mCentre == identificationSection->getCentre())
        matchPoints++;
      else
        return 0;
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
    }

    if (h != NULL)
    {
      if (p.mGribParameterLevelId)
      {
        if (!h->getTypeOfFirstFixedSurface())
          return 0;

        if (*p.mGribParameterLevelId != *h->getTypeOfFirstFixedSurface())
          return 0;

        matchPoints++;
      }

      if (p.mParameterLevel)
      {
        if (!h->getScaledValueOfFirstFixedSurface())
          return 0;

        if (*p.mParameterLevel != *h->getScaledValueOfFirstFixedSurface())
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




T::ParamLevelId MessageIdentifier_fmi::getParamLevelId(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const GRIB1::ProductSection *productSection =  message.getProductSection();
    if (productSection == NULL)
      return 0;

    for (auto it = mLevelDefs_grib1.begin(); it != mLevelDefs_grib1.end(); ++it)
    {
      if (it->mGeneratingProcessIdentifier == productSection->getGeneratingProcessIdentifier() &&
          it->mCentre == productSection->getCentre() &&
          it->mGribLevelId == productSection->getIndicatorOfTypeOfLevel())
      {
        return (T::ParamLevelId)it->mFmiLevelId;
      }
    }
    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_fmi::getProducerName(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const GRIB1::ProductSection *productSection =  message.getProductSection();
    if (productSection == NULL)
      return std::string("");

    uint producerType = 1;
    short ft = message.getForecastType();
    if (ft > 1)
      producerType = 3;

    auto p = getProducer(productSection->getCentre(),productSection->getGeneratingProcessIdentifier(),producerType);
    if (p == NULL)
      return std::string("");

    return p->mProducerName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamId MessageIdentifier_fmi::getParamIdByName(std::string fmiParamName)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const ParameterDefinition_fmi *p = getParameterDefByName(fmiParamName);
    if (p != NULL)
      return p->mFmiParameterId;

    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamLevelId MessageIdentifier_fmi::getParamLevelId(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    GRIB2::ProductSection_cptr productSection = message.getProductSection();
    if (productSection == NULL)
      return 0;

    GRIB2::IdentificSection_sptr identificationSection =  message.getIdentificationSection();
    if (identificationSection == NULL)
      return 0;

    for (auto it = mLevelDefs_grib2.begin(); it != mLevelDefs_grib2.end(); ++it)
    {
      if (it->mGeneratingProcessIdentifier == *productSection->getGeneratingProcessIdentifier() &&
          it->mCentre == identificationSection->getCentre() &&
          it->mGribLevelId == message.getGridParameterLevelId())
      {
        return (T::ParamLevelId)it->mFmiLevelId;
      }
    }
    return 0;

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_fmi::getProducerName(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    GRIB2::ProductSection_cptr productSection = message.getProductSection();
    if (productSection == NULL)
      return std::string("");

    GRIB2::IdentificSection_sptr identificationSection =  message.getIdentificationSection();
    if (identificationSection == NULL)
      return std::string("");

    uint producerType = 1;
    short ft = message.getForecastType();
    if (ft > 1)
      producerType = 3;

    auto p = getProducer(identificationSection->getCentre(),*productSection->getGeneratingProcessIdentifier(),producerType);
    if (p == NULL)
      return std::string("");

    return p->mProducerName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_fmi::getParamName(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const ParameterDefinition_fmi *p = getParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_fmi::getParamName(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const ParameterDefinition_fmi *p = getParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamId MessageIdentifier_fmi::getNewbaseParamId(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const ParameterDefinition_fmi *p = getParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    return p->mNewbaseId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamId MessageIdentifier_fmi::getNewbaseParamId(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const ParameterDefinition_fmi *p = getParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    return p->mNewbaseId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_fmi::getNewbaseParamName(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const ParameterDefinition_fmi *p = getParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    Param_newbase_cptr n = getParameter_newbaseId(p->mNewbaseId);
    if (n == NULL)
      return std::string("");

    return n->mParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_fmi::getNewbaseParamName(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const ParameterDefinition_fmi *p = getParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    Param_newbase_cptr n = getParameter_newbaseId(p->mNewbaseId);
    if (n == NULL)
      return std::string("");

    return n->mParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_fmi::getParamDescription(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const ParameterDefinition_fmi *p = getParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_fmi::getParamDescription(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const ParameterDefinition_fmi *p = getParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_fmi::getParamUnits(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const ParameterDefinition_fmi *p = getParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




std::string MessageIdentifier_fmi::getParamUnits(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const ParameterDefinition_fmi *p = getParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::InterpolationMethod MessageIdentifier_fmi::getParamInterpolationMethod(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const ParameterDefinition_fmi *p = getParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return T::InterpolationMethod::Unknown;

    return p->mInterpolationMethod;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::InterpolationMethod MessageIdentifier_fmi::getParamInterpolationMethod(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const ParameterDefinition_fmi *p = getParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return T::InterpolationMethod::Unknown;

    return p->mInterpolationMethod;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool MessageIdentifier_fmi::getParameterDefById(T::ParamId fmiParamId,ParameterDefinition_fmi& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getParameterDefById(fmiParamId);
    if (def == NULL)
      return false;

    paramDef = *def;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool MessageIdentifier_fmi::getParameterDefByName(std::string fmiParamName,ParameterDefinition_fmi& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getParameterDefByName(fmiParamName);
    if (def == NULL)
      return false;

    paramDef = *def;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool MessageIdentifier_fmi::getParameterDefByNewbaseId(T::ParamId newbaseParamId,ParameterDefinition_fmi& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getParameterDefByNewbaseId(newbaseParamId);
    if (def == NULL)
      return false;

    paramDef = *def;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool MessageIdentifier_fmi::getParameterDefByNewbaseName(std::string newbaseParamName,ParameterDefinition_fmi& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getParameterDefByNewbaseName(newbaseParamName);
    if (def == NULL)
      return false;

    paramDef = *def;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}






bool MessageIdentifier_fmi::getProducer(uint centre,uint ident,uint type,ProducerDef_fmi& producer)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getProducer(centre,ident,type);
    if (p == NULL)
      return false;

    producer = *p;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





ParamDef_fmi_cptr MessageIdentifier_fmi::getParameterDefById(T::ParamId fmiParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mParameterDefs.begin(); it != mParameterDefs.end(); ++it)
    {
      if (strcasecmp(it->mFmiParameterId.c_str(),fmiParamId.c_str()) == 0)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





ParamDef_fmi_cptr MessageIdentifier_fmi::getParameterDefByName(std::string fmiParamName)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mParameterDefs.begin(); it != mParameterDefs.end(); ++it)
    {
      if (strcasecmp(it->mParameterName.c_str(),fmiParamName.c_str()) == 0)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





ParamDef_fmi_cptr MessageIdentifier_fmi::getParameterDefByNewbaseId(T::ParamId newbaseParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mParameterDefs.begin(); it != mParameterDefs.end(); ++it)
    {
      if (strcasecmp(it->mNewbaseId.c_str(),newbaseParamId.c_str()) == 0)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





ParamDef_fmi_cptr MessageIdentifier_fmi::getParameterDefByNewbaseName(std::string newbaseParamName)
{
  FUNCTION_TRACE
  try
  {
    Param_newbase_cptr p = getParameter_newbaseName(newbaseParamName);
    if (p == NULL)
      return NULL;

    for (auto it = mParameterDefs.begin(); it != mParameterDefs.end(); ++it)
    {
      if (strcasecmp(it->mNewbaseId.c_str(),p->mNewbaseParameterId.c_str()) == 0)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool MessageIdentifier_fmi::getParameter_grib1(T::ParamId fmiParamId,Parameter_grib1_fmi& param)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getParameter_grib1(fmiParamId);
    if (p == NULL)
      return false;

    param = *p;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool MessageIdentifier_fmi::getParameter_grib2(T::ParamId fmiParamId,Parameter_grib2_fmi& param)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getParameter_grib2(fmiParamId);
    if (p == NULL)
      return false;

    param = *p;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool MessageIdentifier_fmi::getParameter_newbaseId(T::ParamId newbaseParamId,Parameter_newbase& param)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getParameter_newbaseId(newbaseParamId);
    if (p == NULL)
      return false;

    param = *p;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool MessageIdentifier_fmi::getParameter_newbaseName(std::string newbaseParamName,Parameter_newbase& param)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getParameter_newbaseName(newbaseParamName);
    if (p == NULL)
      return false;

    param = *p;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





Param_newbase_cptr MessageIdentifier_fmi::getParameter_newbaseId(T::ParamId newbaseParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mParameters_newbase.begin(); it != mParameters_newbase.end(); ++it)
    {
      if (it->mNewbaseParameterId == newbaseParamId)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





Param_newbase_cptr MessageIdentifier_fmi::getParameter_newbaseName(std::string newbaseParamName)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mParameters_newbase.begin(); it != mParameters_newbase.end(); ++it)
    {
      if (strcasecmp(it->mParameterName.c_str(),newbaseParamName.c_str()) == 0)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





Param_grib1_fmi_cptr MessageIdentifier_fmi::getParameter_grib1(T::ParamId fmiParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mParameters_grib1.begin(); it != mParameters_grib1.end(); ++it)
    {
      if (it->mFmiParameterId == fmiParamId)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





Param_grib2_fmi_cptr MessageIdentifier_fmi::getParameter_grib2(T::ParamId fmiParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mParameters_grib2.begin(); it != mParameters_grib2.end(); ++it)
    {
      if (it->mFmiParameterId == fmiParamId)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





ProducerDef_fmi_cptr MessageIdentifier_fmi::getProducer(uint centre,uint ident,uint type)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mProducerDefs.begin(); it != mProducerDefs.end(); ++it)
    {
      if (it->mCentre == centre  &&  it->mIdent == ident   &&  it->mType == type)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void MessageIdentifier_fmi::loadGrib1ParameterDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"r");
    if (file == NULL)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != NULL  &&  st[0] != '#')
      {
        bool ind = false;
        char *field[100];
        uint c = 1;
        field[0] = st;
        char *p = st;
        while (*p != '\0'  &&  c < 100)
        {
          if (*p == '"')
            ind = !ind;

          if ((*p == ';'  || *p == '\n') && !ind)
          {
            *p = '\0';
            p++;
            field[c] = p;
            c++;
          }
          else
          {
            p++;
          }
        }

        if (c > 9)
        {
          Parameter_grib1_fmi rec;

          if (field[0][0] != '\0')
            rec. mDbId = (uint)atoll(field[0]);

          if (field[1][0] != '\0')
            rec. mFmiParameterId = field[1];

          if (field[2][0] != '\0')
            rec.mFmiProducerId = (uint)atoll(field[2]);

          if (field[3][0] != '\0')
            rec.mGeneratingProcessIdentifier = (uint)atoll(field[3]);

          if (field[4][0] != '\0')
            rec.mCentre = (uint)atoll(field[4]);

          if (field[5][0] != '\0')
            rec.mGribTableVersion = (uint)atoll(field[5]);

          if (field[6][0] != '\0')
            rec.mGribParameterNumber = (uint)atoll(field[6]);

          if (field[7][0] != '\0')
            rec.mGribTimerangeIndicator = (uint)atoll(field[7]);

          if (field[8][0] != '\0')
            rec.mFmiParameterLevelId = (uint)atoll(field[8]);

          if (field[9][0] != '\0')
            rec.mGribParameterLevelId = (uint)atoll(field[9]);

          if (field[10][0] != '\0')
            rec.mParameterLevel = (uint)atoll(field[10]);

          mParameters_grib1.push_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void MessageIdentifier_fmi::loadGrib2ParameterDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"r");
    if (file == NULL)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != NULL  &&  st[0] != '#')
      {
        bool ind = false;
        char *field[100];
        uint c = 1;
        field[0] = st;
        char *p = st;
        while (*p != '\0'  &&  c < 100)
        {
          if (*p == '"')
            ind = !ind;

          if ((*p == ';'  || *p == '\n') && !ind)
          {
            *p = '\0';
            p++;
            field[c] = p;
            c++;
          }
          else
          {
            p++;
          }
        }

        if (c > 10)
        {
          Parameter_grib2_fmi rec;

          if (field[0][0] != '\0')
            rec. mDbId = (uint)atoll(field[0]);

          if (field[1][0] != '\0')
            rec.mFmiParameterId = field[1];

          if (field[2][0] != '\0')
            rec.mFmiProducerId = (uint)atoll(field[2]);

          if (field[3][0] != '\0')
            rec.mGeneratingProcessIdentifier = (uint)atoll(field[3]);

          if (field[4][0] != '\0')
            rec.mCentre = (uint)atoll(field[4]);

          if (field[5][0] != '\0')
            rec.mDiscipline = (uint)atoll(field[5]);

          if (field[6][0] != '\0')
            rec.mParameterCategory = (uint)atoll(field[6]);

          if (field[7][0] != '\0')
            rec.mParameterNumber = (uint)atoll(field[7]);

          if (field[8][0] != '\0')
            rec.mFmiParameterLevelId = (uint)atoll(field[8]);

          if (field[9][0] != '\0')
            rec.mGribParameterLevelId = (uint)atoll(field[9]);

          if (field[10][0] != '\0')
            rec.mParameterLevel = (uint)atoll(field[10]);

          mParameters_grib2.push_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void MessageIdentifier_fmi::loadParameterDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"r");
    if (file == NULL)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != NULL  &&  st[0] != '#')
      {
        bool ind = false;
        char *field[100];
        uint c = 1;
        field[0] = st;
        char *p = st;
        while (*p != '\0'  &&  c < 100)
        {
          if (*p == '"')
            ind = !ind;

          if ((*p == ';'  || *p == '\n') && !ind)
          {
            *p = '\0';
            p++;
            field[c] = p;
            c++;
          }
          else
          {
            p++;
          }
        }

        if (c > 6)
        {
          ParameterDefinition_fmi rec;

          if (field[0][0] != '\0')
            rec.mFmiParameterId = field[0];

          if (field[1][0] != '\0')
            rec.mVersion = (uint)atoll(field[1]);

          if (field[2][0] != '\0')
            rec.mParameterName = field[2];

          if (field[3][0] != '\0')
            rec.mParameterUnits = field[3];

          if (field[4][0] != '\0')
            rec.mParameterDescription = field[4];

          if (field[5][0] != '\0')
            rec.mInterpolationMethod = (T::InterpolationMethod)atoll(field[5]);

          if (field[6][0] != '\0')
            rec.mNewbaseId = field[6];

          mParameterDefs.push_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void MessageIdentifier_fmi::loadGrib1LevelDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"r");
    if (file == NULL)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != NULL  &&  st[0] != '#')
      {
        bool ind = false;
        char *field[100];
        uint c = 1;
        field[0] = st;
        char *p = st;
        while (*p != '\0'  &&  c < 100)
        {
          if (*p == '"')
            ind = !ind;

          if ((*p == ';'  || *p == '\n') && !ind)
          {
            *p = '\0';
            p++;
            field[c] = p;
            c++;
          }
          else
          {
            p++;
          }
        }

        if (c > 4)
        {
          LevelDef_fmi rec;

          if (field[0][0] != '\0')
            rec.mFmiProducerId = (uint)atoll(field[0]);

          if (field[1][0] != '\0')
            rec.mGeneratingProcessIdentifier = (uint)atoll(field[1]);

          if (field[2][0] != '\0')
            rec.mCentre = (uint)atoll(field[2]);

          if (field[3][0] != '\0')
            rec.mGribLevelId = (uint)atoll(field[3]);

          if (field[4][0] != '\0')
            rec.mFmiLevelId = (uint)atoll(field[4]);

          mLevelDefs_grib1.push_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void MessageIdentifier_fmi::loadGrib2LevelDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"r");
    if (file == NULL)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != NULL  &&  st[0] != '#')
      {
        bool ind = false;
        char *field[100];
        uint c = 1;
        field[0] = st;
        char *p = st;
        while (*p != '\0'  &&  c < 100)
        {
          if (*p == '"')
            ind = !ind;

          if ((*p == ';'  || *p == '\n') && !ind)
          {
            *p = '\0';
            p++;
            field[c] = p;
            c++;
          }
          else
          {
            p++;
          }
        }

        if (c > 4)
        {
          LevelDef_fmi rec;

          if (field[0][0] != '\0')
            rec.mFmiProducerId = (uint)atoll(field[0]);

          if (field[1][0] != '\0')
            rec.mGeneratingProcessIdentifier = (uint)atoll(field[1]);

          if (field[2][0] != '\0')
            rec.mCentre = (uint)atoll(field[2]);

          if (field[3][0] != '\0')
            rec.mGribLevelId = (uint)atoll(field[3]);

          if (field[4][0] != '\0')
            rec.mFmiLevelId = (uint)atoll(field[4]);

          mLevelDefs_grib2.push_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void MessageIdentifier_fmi::loadParameterDefinitions_newbase(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"r");
    if (file == NULL)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != NULL  &&  st[0] != '#')
      {
        bool ind = false;
        char *field[100];
        uint c = 1;
        field[0] = st;
        char *p = st;
        while (*p != '\0'  &&  c < 100)
        {
          if (*p == '"')
            ind = !ind;

          if ((*p == ';'  || *p == '\n') && !ind)
          {
            *p = '\0';
            p++;
            field[c] = p;
            c++;
          }
          else
          {
            p++;
          }
        }

        if (c > 1)
        {
          Parameter_newbase rec;

          if (field[0][0] != '\0')
            rec.mNewbaseParameterId = field[0];

          if (field[1][0] != '\0')
            rec.mParameterName = field[1];

          mParameters_newbase.push_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void MessageIdentifier_fmi::loadProducerDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"r");
    if (file == NULL)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != NULL  &&  st[0] != '#')
      {
        bool ind = false;
        char *field[100];
        uint c = 1;
        field[0] = st;
        char *p = st;
        while (*p != '\0'  &&  c < 100)
        {
          if (*p == '"')
            ind = !ind;

          if ((*p == ';'  || *p == '\n') && !ind)
          {
            *p = '\0';
            p++;
            field[c] = p;
            c++;
          }
          else
          {
            p++;
          }
        }

        if (c > 5)
        {
          ProducerDef_fmi rec;

          if (field[0][0] != '\0')
            rec.mProducerId = (uint)atoll(field[0]);

          if (field[1][0] != '\0')
            rec.mType = (uint)atoll(field[1]);

          if (field[2][0] != '\0')
            rec.mCentre = (uint)atoll(field[2]);

          if (field[3][0] != '\0')
            rec.mIdent = (uint)atoll(field[3]);

          if (field[4][0] != '\0')
            rec.mProducerName = field[4];

          if (field[5][0] != '\0')
            rec.mProducerDescription = field[5];


          mProducerDefs.push_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}






}
}
