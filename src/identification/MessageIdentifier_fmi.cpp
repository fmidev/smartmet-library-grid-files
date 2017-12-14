#include "MessageIdentifier_fmi.h"
#include "common/Exception.h"


namespace SmartMet
{
namespace Identification
{




MessageIdentifier_fmi::MessageIdentifier_fmi()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





MessageIdentifier_fmi::~MessageIdentifier_fmi()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void MessageIdentifier_fmi::init(const char* configDir)
{
  try
  {
    mConfigDir = configDir;

    loadParameterDefinitions();
    loadExtendedParameterDefinitions();
    loadParameterDefinitions_grib1();
    loadParameterDefinitions_grib2();
    loadParameterDefinitions_newbase();
    loadLevelDefinitions_grib1();
    loadLevelDefinitions_grib2();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamId MessageIdentifier_fmi::getParamId(GRIB1::Message& message)
{
  try
  {
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
  try
  {
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
  try
  {
    /*
    T::ParamId fmiParamId = message.getFmiParameterId();

    Parameter_grib1_fmi_cptr p = getParameter_grib1(fmiParamId);
    if (p != NULL  &&  p->mFmiParameterLevelId)
    {
      return (T::ParamLevelId)(*p->mFmiParameterLevelId);
    }

    return 0;
    */

    const GRIB1::ProductSection *productSection =  message.getProductSection();
    if (productSection == NULL)
      return 0;

    uint sz = (uint)mLevelDefs_grib1.size();
    for (uint t=0; t<sz; t++)
    {
      LevelDef_fmi rec =  mLevelDefs_grib1[t];
      if (rec.mGeneratingProcessIdentifier == productSection->getGeneratingProcessIdentifier() &&
          rec.mCentre == productSection->getCentre() &&
          rec.mGribLevelId == productSection->getIndicatorOfTypeOfLevel())
      {
        return (T::ParamLevelId)rec.mFmiLevelId;
      }
    }
    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamId MessageIdentifier_fmi::getParamIdByName(std::string fmiParamName)
{
  try
  {
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
  try
  {
    /*
    T::ParamId fmiParamId = message.getFmiParameterId();

    Parameter_grib2_fmi_cptr p = getParameter_grib2(fmiParamId);
    if (p != NULL  &&  p->mFmiParameterLevelId)
    {
      return (T::ParamLevelId)(*p->mFmiParameterLevelId);
    }

    return 0;
    */

    GRIB2::ProductSection_cptr productSection = message.getProductSection();
    if (productSection == NULL)
      return 0;

    GRIB2::IdentificSection_sptr identificationSection =  message.getIdentificationSection();
    if (identificationSection == NULL)
      return 0;

    uint sz = (uint)mLevelDefs_grib2.size();
    for (uint t=0; t<sz; t++)
    {
      LevelDef_fmi rec =  mLevelDefs_grib2[t];
      if (rec.mGeneratingProcessIdentifier == *productSection->getGeneratingProcessIdentifier() &&
          rec.mCentre == identificationSection->getCentre() &&
          rec.mGribLevelId == message.getGridParameterLevelId())
      {
        return (T::ParamLevelId)rec.mFmiLevelId;
      }
    }
    return 0;

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string MessageIdentifier_fmi::getParamName(GRIB1::Message& message)
{
  try
  {
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
  try
  {
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
  try
  {
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
  try
  {
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
  try
  {
    const ParameterDefinition_fmi *p = getParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    Parameter_newbase_cptr n = getParameter_newbaseId(p->mNewbaseId);
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
  try
  {
    const ParameterDefinition_fmi *p = getParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    Parameter_newbase_cptr n = getParameter_newbaseId(p->mNewbaseId);
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
  try
  {
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
  try
  {
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
  try
  {
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
  try
  {
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
  try
  {
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
  try
  {
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





ParameterDefinition_fmi_cptr MessageIdentifier_fmi::getParameterDefById(T::ParamId fmiParamId)
{
  try
  {
    std::size_t sz = mParameterDefs.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (strcasecmp(mParameterDefs[t].mFmiParameterId.c_str(),fmiParamId.c_str()) == 0)
        return &mParameterDefs[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





ParameterDefinition_fmi_cptr MessageIdentifier_fmi::getParameterDefByName(std::string fmiParamName)
{
  try
  {
    std::size_t sz = mParameterDefs.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (strcasecmp(mParameterDefs[t].mParameterName.c_str(),fmiParamName.c_str()) == 0)
        return &mParameterDefs[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




ParameterDefinition_fmi_cptr MessageIdentifier_fmi::getParameterDefByNewbaseId(T::ParamId newbaseParamId)
{
  try
  {
    std::size_t sz = mParameterDefs.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (strcasecmp(mParameterDefs[t].mNewbaseId.c_str(),newbaseParamId.c_str()) == 0)
        return &mParameterDefs[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





ParameterDefinition_fmi_cptr MessageIdentifier_fmi::getParameterDefByNewbaseName(std::string newbaseParamName)
{
  try
  {
    Parameter_newbase_cptr p = getParameter_newbaseName(newbaseParamName);
    if (p == NULL)
      return NULL;

    std::size_t sz = mParameterDefs.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (strcasecmp(mParameterDefs[t].mNewbaseId.c_str(),p->mNewbaseParameterId.c_str()) == 0)
        return &mParameterDefs[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





Parameter_newbase_cptr MessageIdentifier_fmi::getParameter_newbaseId(T::ParamId newbaseParamId)
{
  try
  {
    std::size_t sz = mParameters_newbase.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (mParameters_newbase[t].mNewbaseParameterId == newbaseParamId)
        return &mParameters_newbase[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




Parameter_newbase_cptr MessageIdentifier_fmi::getParameter_newbaseName(std::string newbaseParamName)
{
  try
  {
    std::size_t sz = mParameters_newbase.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (strcasecmp(mParameters_newbase[t].mParameterName.c_str(),newbaseParamName.c_str()) == 0)
        return &mParameters_newbase[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





Parameter_grib1_fmi_cptr MessageIdentifier_fmi::getParameter_grib1(T::ParamId fmiParamId)
{
  try
  {
    std::size_t sz = mParameters_grib1.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (mParameters_grib1[t].mFmiParameterId == fmiParamId)
        return &mParameters_grib1[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





Parameter_grib2_fmi_cptr MessageIdentifier_fmi::getParameter_grib2(T::ParamId fmiParamId)
{
  try
  {
    std::size_t sz = mParameters_grib2.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (mParameters_grib2[t].mFmiParameterId == fmiParamId)
        return &mParameters_grib2[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void MessageIdentifier_fmi::loadParameterDefinitions_grib1()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/parameterDef_grib1_fmi.csv",mConfigDir.c_str());

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





void MessageIdentifier_fmi::loadParameterDefinitions_grib2()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/parameterDef_grib2_fmi.csv",mConfigDir.c_str());

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




void MessageIdentifier_fmi::loadParameterDefinitions()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/parameterDef_fmi.csv",mConfigDir.c_str());


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





void MessageIdentifier_fmi::loadExtendedParameterDefinitions()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/parameterDef_fmi_ext.csv",mConfigDir.c_str());


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





void MessageIdentifier_fmi::loadLevelDefinitions_grib1()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/levelDef_grib1_fmi.csv",mConfigDir.c_str());


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





void MessageIdentifier_fmi::loadLevelDefinitions_grib2()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/levelDef_grib2_fmi.csv",mConfigDir.c_str());


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



void MessageIdentifier_fmi::loadParameterDefinitions_newbase()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/parameterDef_newbase.csv",mConfigDir.c_str());


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




}
}
