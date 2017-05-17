#include "GribDef.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{

GribDef gribDef;



/*! \brief The constructor of the class. */

GribDef::GribDef()
{
  try
  {
    mInitialized = false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The destructor of the class. */

GribDef::~GribDef()
{
}





void GribDef::init(const char* configDir)
{
  try
  {
    if (mInitialized)
      return;

    mConfigDir = configDir;

    loadUnitDefinitions();
    loadTableValues();
    loadParameterDefinitions();
    loadParameterDefinitions_grib1();
    loadParameterDefinitions_grib2();
    loadLevelDefinitions_grib1();
    loadLevelDefinitions_grib2();
    loadTimeRangeDefinitions_grib1();
    loadTimeRangeDefinitions_grib2();

    mMessageIdentifier_fmi.init(configDir);

    mInitialized = true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string GribDef::getTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,std::string table,std::uint32_t number)
{
  try
  {
    std::size_t valueCount = mTableValues.size();
    for (std::size_t t = 0; t<valueCount; t++)
    {
      auto rec = mTableValues[t];
      if (rec.mGribVersion == gribVersion  &&  rec.mTableVersion == tableVersion  &&  rec.mTable == table  &&  rec.mNumber == number)
        return rec.mValue;
    }
    return std::to_string(number);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string GribDef::getTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,std::string table,T::UInt8_opt number)
{
  try
  {
    if (number)
      return getTableValue(gribVersion,tableVersion,table,*number);

    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string GribDef::getTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,std::string table,T::UInt16_opt number)
{
  try
  {
    if (number)
      return getTableValue(gribVersion,tableVersion,table,*number);

    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





Parameter_grib1_cptr GribDef::getParameterDefById_grib1(T::ParamId gribParamId)
{
  try
  {
    std::size_t sz = mParameters_grib1.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (strcasecmp(mParameters_grib1[t].mGribParameterId.c_str(),gribParamId.c_str()) == 0)
        return &mParameters_grib1[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





Parameter_grib1_cptr GribDef::getParameterDefByName_grib1(std::string gribParamName)
{
  try
  {
    std::size_t sz = mParameters_grib1.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (strcasecmp(mParameters_grib1[t].mParameterName.c_str(),gribParamName.c_str()) == 0)
        return &mParameters_grib1[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





Parameter_grib1_cptr GribDef::getParameterDef_grib1(uint tableVersion,uint indicatorOfParameter)
{
  try
  {
    std::size_t sz = mParameters_grib1.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (mParameters_grib1[t].mTable2Version == tableVersion  &&  mParameters_grib1[t].mIndicatorOfParameter == indicatorOfParameter)
        return &mParameters_grib1[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




Parameter_grib2_cptr GribDef::getParameterDefById_grib2(T::ParamId gribParamId)
{
  try
  {
    std::size_t sz = mParameters_grib2.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (strcasecmp(mParameters_grib2[t].mGribParameterId.c_str(),gribParamId.c_str()) == 0)
        return &mParameters_grib2[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





Parameter_grib2_cptr GribDef::getParameterDefByName_grib2(std::string gribParamName)
{
  try
  {
    std::size_t sz = mParameters_grib2.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (strcasecmp(mParameters_grib2[t].mParameterName.c_str(),gribParamName.c_str()) == 0)
        return &mParameters_grib2[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





void GribDef::loadTableValues()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/tables.csv",mConfigDir.c_str());

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

          if ((*p == ','  ||  *p == ';'  || *p == '\n') && !ind)
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
          TableValue rec;

          if (field[0][0] != '\0')
            rec.mGribVersion = (std::uint8_t)atoll(field[0]);

          if (field[1][0] != '\0')
            rec.mTableVersion = (std::uint8_t)atoll(field[1]);

          if (field[2][0] != '\0')
            rec.mTable = field[2];

          if (field[3][0] != '\0')
            rec.mNumber = (std::uint32_t)atoll(field[3]);

          if (field[4][0] != '\0')
            rec.mName = field[4];

          if (field[5][0] != '\0')
            rec.mValue = field[5];

          mTableValues.push_back(rec);
        }
      }

    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





void GribDef::loadParameterDefinitions()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/parameterDef.csv",mConfigDir.c_str());

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

          if ((*p == ','  ||  *p == ';'  || *p == '\n') && !ind)
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
          ParameterDefinition rec;
          rec.mGribParameterId = field[0];

          if (field[1][0] != '\0')
            rec.mDiscipline = (uint)atoll(field[1]);

          if (field[2][0] != '\0')
            rec.mParameterCategory = (uint)atoll(field[2]);

          if (field[3][0] != '\0')
            rec.mParameterNumber = (uint)atoll(field[3]);

          rec.mParameterName = field[4];
          rec.mParameterDescription = field[5];
          rec.mParameterUnits = field[6];

          mParameterDefs.push_back(rec);
        }
      }

    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}



ParameterDefinition_cptr GribDef::getGribParamDefById(T::ParamId gribParamId)
{
  try
  {
    std::size_t paramDefCount = mParameterDefs.size();
    for (std::size_t t=0; t<paramDefCount; t++)
    {
      if (strcasecmp(mParameterDefs[t].mGribParameterId.c_str(),gribParamId.c_str()) == 0)
        return &mParameterDefs[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





ParameterDefinition_cptr GribDef::getGribParamDefByName(std::string gribParamName)
{
  try
  {
    std::size_t paramDefCount = mParameterDefs.size();
    for (std::size_t t=0; t<paramDefCount; t++)
    {
      if (strcasecmp(mParameterDefs[t].mParameterName.c_str(),gribParamName.c_str()) == 0)
        return &mParameterDefs[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





ParameterDefinition_cptr GribDef::getGribParamDef(uint discipline,uint category,uint number)
{
  try
  {
    std::size_t paramDefCount = mParameterDefs.size();
    for (std::size_t t=0; t<paramDefCount; t++)
    {
      if (mParameterDefs[t].mDiscipline == discipline &&  mParameterDefs[t].mParameterCategory == category && mParameterDefs[t].mParameterNumber == number)
        return &mParameterDefs[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





LevelDef_cptr GribDef::getLevelDef_grib1(uint levelId)
{
  try
  {
    std::size_t sz = mLevelDefs_grib1.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (mLevelDefs_grib1[t].mLevelId == levelId)
        return &mLevelDefs_grib1[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





LevelDef_cptr GribDef::getLevelDef_grib2(uint levelId)
{
  try
  {
    std::size_t sz = mLevelDefs_grib2.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (mLevelDefs_grib2[t].mLevelId == levelId)
        return &mLevelDefs_grib1[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





TimeRangeDef_cptr GribDef::getTimeRangeDef_grib1(uint timeRangeId)
{
  try
  {
    std::size_t sz = mTimeRangeDefs_grib1.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (mTimeRangeDefs_grib1[t].mTimeRangeId == timeRangeId)
        return &mTimeRangeDefs_grib1[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




TimeRangeDef_cptr GribDef::getTimeRangeDef_grib2(uint timeRangeId)
{
  try
  {
    std::size_t sz = mTimeRangeDefs_grib2.size();
    for (std::size_t t=0; t<sz; t++)
    {
      if (mTimeRangeDefs_grib2[t].mTimeRangeId == timeRangeId)
        return &mTimeRangeDefs_grib2[t];
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




void GribDef::loadUnitDefinitions()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/units.csv",mConfigDir.c_str());

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

          if ((*p == ','  ||  *p == ';'  || *p == '\n') && !ind)
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

        if (c > 2)
        {
          UnitDefinition rec;
          rec.mOriginalUnits = field[0];
          rec.mPreferredUnits = field[1];
          rec.mPreferredInterpolationMethod = (T::InterpolationMethod)atoi(field[2]);

          mUnitDefs.push_back(rec);
        }
      }

    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




void GribDef::loadLevelDefinitions_grib1()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/levelDef_grib1.csv",mConfigDir.c_str());


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

          if ((*p == ','  ||  *p == ';'  || *p == '\n') && !ind)
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

        if (c > 2)
        {
          LevelDef rec;

          if (field[0][0] != '\0')
            rec.mLevelId = (uint)atoll(field[0]);

          if (field[1][0] != '\0')
            rec.mName = field[1];

          if (field[2][0] != '\0')
            rec.mDescription = field[2];

          mLevelDefs_grib1.push_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




void GribDef::loadLevelDefinitions_grib2()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/levelDef_grib2.csv",mConfigDir.c_str());


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

          if ((*p == ','  ||  *p == ';'  || *p == '\n') && !ind)
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

        if (c > 2)
        {
          LevelDef rec;

          if (field[0][0] != '\0')
            rec.mLevelId = (uint)atoll(field[0]);

          if (field[1][0] != '\0')
            rec.mName = field[1];

          if (field[2][0] != '\0')
            rec.mDescription = field[2];

          mLevelDefs_grib2.push_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




void GribDef::loadTimeRangeDefinitions_grib1()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/timeRangeDef_grib1.csv",mConfigDir.c_str());


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

          if ((*p == ','  ||  *p == ';'  || *p == '\n') && !ind)
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

        if (c > 2)
        {
          TimeRangeDef rec;

          if (field[0][0] != '\0')
            rec.mTimeRangeId = (uint)atoll(field[0]);

          if (field[1][0] != '\0')
            rec.mName = field[1];

          if (field[2][0] != '\0')
            rec.mDescription = field[2];

          mTimeRangeDefs_grib1.push_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





void GribDef::loadTimeRangeDefinitions_grib2()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/timeRangeDef_grib2.csv",mConfigDir.c_str());


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

          if ((*p == ','  ||  *p == ';'  || *p == '\n') && !ind)
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

        if (c > 2)
        {
          TimeRangeDef rec;

          if (field[0][0] != '\0')
            rec.mTimeRangeId = (uint)atoll(field[0]);

          if (field[1][0] != '\0')
            rec.mName = field[1];

          if (field[2][0] != '\0')
            rec.mDescription = field[2];

          mTimeRangeDefs_grib2.push_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





void GribDef::loadParameterDefinitions_grib1()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/parameterDef_grib1.csv",mConfigDir.c_str());


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

          if ((*p == ','  ||  *p == ';'  || *p == '\n') && !ind)
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

        if (c > 7)
        {
          Parameter_grib1 rec;

          if (field[0][0] != '\0')
            rec.mGribParameterId = field[0];

          if (field[1][0] != '\0')
            rec.mTable2Version = (std::uint8_t)atoll(field[1]);

          if (field[2][0] != '\0')
            rec.mCentre = (std::uint8_t)atoll(field[2]);

          if (field[3][0] != '\0')
            rec.mIndicatorOfParameter = (std::uint8_t)atoll(field[3]);

          if (field[4][0] != '\0')
            rec.mIndicatorOfTypeOfLevel = (std::uint8_t)atoll(field[4]);

          if (field[5][0] != '\0')
            rec.mParameterLevel = (std::uint16_t)atoll(field[5]);

          if (field[6][0] != '\0')
            rec.mParameterUnits = field[6];

          if (field[7][0] != '\0')
            rec.mParameterName = field[7];

          if (field[8][0] != '\0')
            rec.mParameterDescription = field[8];

          mParameters_grib1.push_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}






void GribDef::loadParameterDefinitions_grib2()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/parameterDef_grib2.csv",mConfigDir.c_str());

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

          if ((*p == ','  ||  *p == ';'  || *p == '\n') && !ind)
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

        if (c > 24)
        {
          Parameter_grib2 rec;

          if (field[0][0] != '\0')
            rec.mGribParameterId = field[0];

          if (field[1][0] != '\0')
            rec.mDiscipline = (std::uint8_t)atoll(field[1]);

          if (field[2][0] != '\0')
            rec.mCentre = (std::uint16_t)atoll(field[2]);

          if (field[3][0] != '\0')
            rec.mParameterCategory = (std::uint8_t)atoll(field[3]);

          if (field[4][0] != '\0')
            rec.mParameterNumber = (std::uint8_t)atoll(field[4]);

          if (field[5][0] != '\0')
            rec.mProbabilityType = (std::uint8_t)atoll(field[5]);

          if (field[6][0] != '\0')
            rec.mProductDefinitionTemplateNumber = (std::uint16_t)atoll(field[6]);

          if (field[7][0] != '\0')
            rec.mTypeOfFirstFixedSurface = (std::uint8_t)atoll(field[7]);

          if (field[8][0] != '\0')
            rec.mTypeOfSecondFixedSurface = (std::uint8_t)atoll(field[8]);

          if (field[9][0] != '\0')
            rec.mTypeOfStatisticalProcessing = (std::uint8_t)atoll(field[9]);

          if (field[10][0] != '\0')
            rec.mScaledValueOfLowerLimit = (std::uint8_t)atoll(field[10]);

          if (field[11][0] != '\0')
            rec.mScaledValueOfFirstFixedSurface = (std::uint32_t)atoll(field[11]);

          if (field[12][0] != '\0')
            rec.mScaledValueOfSecondFixedSurface =(std::uint32_t)atoll(field[12]);

          if (field[13][0] != '\0')
            rec.mScaleFactorOfLowerLimit = (std::uint8_t)atoll(field[13]);

          if (field[14][0] != '\0')
            rec.mScaleFactorOfFirstFixedSurface = (std::uint8_t)atoll(field[14]);

          if (field[15][0] != '\0')
            rec.mScaleFactorOfSecondFixedSurface = (std::int8_t)atoll(field[15]);

          if (field[16][0] != '\0')
            rec.mIs_tigge = (std::uint8_t)atoll(field[16]);

          if (field[17][0] != '\0')
            rec.mTypeOfGeneratingProcess = (std::uint8_t)atoll(field[17]);

          if (field[18][0] != '\0')
            rec.mConstituentType = (std::uint16_t)atoll(field[18]);

          if (field[19][0] != '\0')
            rec.mLengthOfTimeRange = (std::uint8_t)atoll(field[19]);

          if (field[20][0] != '\0')
            rec.mLocalTablesVersion = (std::uint8_t)atoll(field[20]);

          if (field[21][0] != '\0')
            rec.mAerosolType = (std::uint16_t)atoll(field[21]);

          if (field[22][0] != '\0')
            rec.mParameterUnits = field[22];

          if (field[23][0] != '\0')
            rec.mParameterName = field[23];

          if (field[24][0] != '\0')
            rec.mParameterDescription = field[24];

          //rec.print(std::cout,0,0);
          mParameters_grib2.push_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}



T::InterpolationMethod GribDef::getPreferredInterpolationMethodByUnits(std::string originalUnits)
{
  try
  {
    std::size_t unitCount = mUnitDefs.size();
    for (std::size_t t = 0; t<unitCount; t++)
    {
      if (mUnitDefs[t].mOriginalUnits == originalUnits)
        return mUnitDefs[t].mPreferredInterpolationMethod;
    }

    return T::InterpolationMethod::Linear;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string GribDef::getPreferredUnits(std::string originalUnits)
{
  try
  {
    std::size_t unitCount = mUnitDefs.size();
    for (std::size_t t = 0; t<unitCount; t++)
    {
      if (mUnitDefs[t].mOriginalUnits == originalUnits)
        return mUnitDefs[t].mPreferredUnits;
    }

    return originalUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}


}  // namespace GRIB2
}  // namespace SmartMet
