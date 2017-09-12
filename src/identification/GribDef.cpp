#include "GribDef.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"

#include "grib1/implementation/LatLonImpl.h"
#include "grib1/implementation/MercatorImpl.h"
#include "grib1/implementation/LambertConformalImpl.h"
#include "grib1/implementation/GaussianImpl.h"
#include "grib1/implementation/PolarStereographicImpl.h"
#include "grib1/implementation/AlbersImpl.h"
#include "grib1/implementation/RotatedLatLonImpl.h"
#include "grib1/implementation/ObliqueLambertConformalImpl.h"
#include "grib1/implementation/RotatedGaussianImpl.h"
#include "grib1/implementation/StretchedLatLonImpl.h"
#include "grib1/implementation/StretchedGaussianImpl.h"
#include "grib1/implementation/StretchedRotatedLatLonImpl.h"
#include "grib1/implementation/StretchedRotatedGaussianImpl.h"
#include "grib1/implementation/SphericalHarmonicImpl.h"
#include "grib1/implementation/RotatedSphericalHarmonicImpl.h"
#include "grib1/implementation/StretchedSphericalHarmonicImpl.h"
#include "grib1/implementation/StretchedRotatedSphericalHarmonicImpl.h"
#include "grib1/implementation/SpaceViewImpl.h"

#include "grib2/implementation/LatLonImpl.h"                             //  "3.0"
#include "grib2/implementation/RotatedLatLonImpl.h"                      //  "3.1"
#include "grib2/implementation/StretchedLatLonImpl.h"                    //  "3.2"
#include "grib2/implementation/StretchedRotatedLatLonImpl.h"             //  "3.3"
#include "grib2/implementation/VariableResolutionLatLonImpl.h"           //  "3.4"
#include "grib2/implementation/VariableResolutionRotatedLatLonImpl.h"    //  "3.5"
#include "grib2/implementation/MercatorImpl.h"                           //  "3.10"
#include "grib2/implementation/TransverseMercatorImpl.h"                 //  "3.12"
#include "grib2/implementation/PolarStereographicImpl.h"                 //  "3.20"
#include "grib2/implementation/LambertConformalImpl.h"                   //  "3.30"
#include "grib2/implementation/AlbersImpl.h"                             //  "3.31"
#include "grib2/implementation/GaussianImpl.h"                           //  "3.40"
#include "grib2/implementation/RotatedGaussianImpl.h"                    //  "3.41"
#include "grib2/implementation/StretchedGaussianImpl.h"                  //  "3.42"
#include "grib2/implementation/StretchedRotatedGaussianImpl.h"           //  "3.43"
#include "grib2/implementation/SphericalHarmonicImpl.h"                  //  "3.50"
#include "grib2/implementation/RotatedSphericalHarmonicImpl.h"           //  "3.51"
#include "grib2/implementation/StretchedSphericalHarmonicImpl.h"         //  "3.52"
#include "grib2/implementation/StretchedRotatedSphericalHarmonicImpl.h"  //  "3.53"
#include "grib2/implementation/SpaceViewImpl.h"                          //  "3.90"
#include "grib2/implementation/TriangularImpl.h"                         //  "3.100"
#include "grib2/implementation/UnstructuredImpl.h"                       //  "3.101"
#include "grib2/implementation/EquatorialAzimuthalEquidistantImpl.h"     //  "3.110"
#include "grib2/implementation/AzimuthRangeImpl.h"                       //  "3.120"
#include "grib2/implementation/IrregularLatLonImpl.h"                    //  "3.130"
#include "grib2/implementation/LambertAzimuthalEqualAreaImpl.h"          //  "3.140"
#include "grib2/implementation/CrossSectionImpl.h"                       //  "3.1000"
#include "grib2/implementation/HovmollerImpl.h"                          //  "3.1100"
#include "grib2/implementation/TimeSectionImpl.h"                        //  "3.1200"


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
  try
  {
    for (auto it=mGridDefinitions1.begin(); it!=mGridDefinitions1.end(); ++it)
    {
      delete (it->second);
    }

    for (auto it=mGridDefinitions2.begin(); it!=mGridDefinitions2.end(); ++it)
    {
      delete (it->second);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
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
    loadGeometryDefinitions();

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





GRIB1::GridDefinition_ptr GribDef::getGridDefinition1ByGeometryId(uint geometryId)
{
  try
  {
    std::map<uint,GRIB1::GridDefinition_ptr>::iterator it = mGridDefinitions1.find(geometryId);
    if (it != mGridDefinitions1.end())
      return it->second;
/*
    std::vector<GRIB1::GridDefinition_ptr>::iterator it;
    for (it=mGridDefinitions1.begin(); it!=mGridDefinitions1.end(); ++it)
    {
      if ((*it)->getGridGeometryId() == geometryId)
        return *it;
    }
  */
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





GRIB1::GridDefinition_ptr GribDef::getGridDefinition1ByHash(T::Hash hash)
{
  try
  {
    for (auto it=mGridDefinitions1.begin(); it!=mGridDefinitions1.end(); ++it)
    {
      if (it->second->getGridHash() == hash)
        return it->second;
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





GRIB2::GridDefinition_ptr GribDef::getGridDefinition2ByGeometryId(uint geometryId)
{
  try
  {
    std::map<uint,GRIB2::GridDefinition_ptr>::iterator it = mGridDefinitions2.find(geometryId);
    if (it != mGridDefinitions2.end())
      return it->second;
/*
    std::vector<GRIB2::GridDefinition_ptr>::iterator it;
    for (it=mGridDefinitions2.begin(); it!=mGridDefinitions2.end(); ++it)
    {
      if ((*it)->getGridGeometryId() == geometryId)
        return *it;
    }
    */
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





GRIB2::GridDefinition_ptr GribDef::getGridDefinition2ByHash(T::Hash hash)
{
  try
  {
    for (auto it=mGridDefinitions2.begin(); it!=mGridDefinitions2.end(); ++it)
    {
      if (it->second->getGridHash() == hash)
        return it->second;
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





void GribDef::loadGeometryDefinitions()
{
  try
  {
    char filename[200];
    sprintf(filename,"%s/geometryDef.csv",mConfigDir.c_str());

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

        if (c > 1)
        {
          T::GridProjection gridProjection = (T::GridProjection)atoll(field[0]);
          switch (gridProjection)
          {
            case T::GridProjection::Unknown:
              break;

            case T::GridProjection::LatLon:
            {
              uint geometryId = (uint)atoll(field[1]);
              char *geometryName = field[2];
              int ni = atoll(field[3]);
              int nj = atoll(field[4]);
              int longitude = (int)(atof(field[5])*1000000);
              int latitude = (int)(atof(field[6])*1000000);
              int iInc = (int)(atof(field[7]) * 1000000);
              int jInc = (int)(atof(field[8]) * 1000000);
              char *scanningMode = field[9];
              int lastLongitude = longitude + ni*iInc - iInc;
              int lastLatitude = latitude + nj*jInc - jInc;

              if (lastLongitude > 360000000)
                lastLongitude -= 360000000;

              if (lastLatitude > 90000000)
                lastLatitude = 180000000 - lastLatitude;

              // ******* GRIB 2 ********

              GRIB2::LatLonImpl *def2 = new GRIB2::LatLonImpl();
              GRIB2::LatLonSettings latLon;
              GRIB2::ScanningModeSettings scanningMode2;
              GRIB2::GridSettings grid;

              grid.setNi(T::UInt32_opt(ni));
              grid.setNj(T::UInt32_opt(nj));
              grid.setLongitudeOfFirstGridPoint(T::Int32_opt(longitude));
              grid.setLatitudeOfFirstGridPoint(T::Int32_opt(latitude));
              grid.setLongitudeOfLastGridPoint(T::Int32_opt(lastLongitude));
              grid.setLatitudeOfLastGridPoint(T::Int32_opt(lastLatitude));
              latLon.setGrid(grid);

              latLon.setIDirectionIncrement(T::UInt32_opt(iInc));
              latLon.setJDirectionIncrement(T::UInt32_opt(jInc));

              if (strcasecmp(scanningMode,"+x+y") == 0)
                scanningMode2.setScanningMode(0x40);
              else
              if (strcasecmp(scanningMode,"-x+y") == 0)
              {
                lastLongitude = longitude - (ni*iInc - iInc);
                scanningMode2.setScanningMode(0x80+0x40);
              }
              else
              if (strcasecmp(scanningMode,"+x-y") == 0)
              {
                lastLatitude = latitude - (nj*jInc - jInc);
                scanningMode2.setScanningMode(0);
              }
              else
              if (strcasecmp(scanningMode,"-x-y") == 0)
              {
                lastLongitude = longitude - (ni*iInc - iInc);
                lastLatitude = latitude - (nj*jInc - jInc);
                scanningMode2.setScanningMode(0x80);
              }

              latLon.setScanningMode(scanningMode2);
              def2->setLatLon(latLon);

              def2->setGridGeometryId(geometryId);
              def2->setGridGeometryName(geometryName);

              //def2->print(std::cout,0,0);
              //T::Hash hash = def2->getGridHash();
              //printf("HASH %llu\n",(unsigned long long)hash);

              mGridDefinitions2.insert(std::pair<uint,GRIB2::GridDefinition_ptr>(geometryId,def2));

              // ******* GRIB 1 ********

              GRIB1::LatLonImpl *def1 = new GRIB1::LatLonImpl();
              GRIB1::GridAreaSettings gridArea;
              //GRIB1::ResolutionFlagsSettings resolutionFlags;
              GRIB1::ScanningModeSettings scanningMode1;

              //resolutionFlags.setResolutionAndComponentFlags(128);
              //gridArea.setResolutionFlags(resolutionFlags);

              gridArea.setLatitudeOfFirstGridPoint((std::int24_t)(latitude/1000));
              gridArea.setLongitudeOfFirstGridPoint((std::int24_t)(longitude/1000));
              gridArea.setLatitudeOfLastGridPoint((std::int24_t)(lastLatitude/1000));
              gridArea.setLongitudeOfLastGridPoint((std::int24_t)(lastLongitude/1000));
              def1->setGridArea(gridArea);

              def1->setNi((std::uint16_t)ni);
              def1->setNj((std::uint16_t)nj);
              def1->setIDirectionIncrement((std::uint16_t)(iInc/1000));
              def1->setJDirectionIncrement((std::uint16_t)(jInc/1000));

              if (strcasecmp(scanningMode,"+x+y") == 0)
                scanningMode1.setScanningMode(0x40);
              else
              if (strcasecmp(scanningMode,"-x+y") == 0)
                scanningMode1.setScanningMode(0x80+0x40);
              else
              if (strcasecmp(scanningMode,"+x-y") == 0)
                scanningMode1.setScanningMode(0);
              else
              if (strcasecmp(scanningMode,"-x-y") == 0)
                scanningMode1.setScanningMode(0x80);

              def1->setScanningMode(scanningMode1);

              def1->setGridGeometryId(geometryId);
              def1->setGridGeometryName(geometryName);

              //def1->print(std::cout,0,0);
              //T::Hash hash = def1->getGridHash();
              //printf("HASH %llu\n",(unsigned long long)hash);

              mGridDefinitions1.insert(std::pair<uint,GRIB1::GridDefinition_ptr>(geometryId,def1));
            }
            break;

            case T::GridProjection::RotatedLatLon:
            {
              uint geometryId = (uint)atoll(field[1]);
              char *geometryName = field[2];
              int ni = atoll(field[3]);
              int nj = atoll(field[4]);
              int longitude = (int)(atof(field[5])*1000000);
              int latitude = (int)(atof(field[6])*1000000);
              int iInc = (int)(atof(field[7]) * 1000000);
              int jInc = (int)(atof(field[8]) * 1000000);
              char *scanningMode = field[9];
              int longitudeOfSouthernPole = (int)(atof(field[10])*1000000);
              int latitudeOfSouthernPole = (int)(atof(field[11])*1000000);
              int lastLongitude = longitude + ni*iInc - iInc;
              int lastLatitude = latitude + nj*jInc - jInc;
              //std::uint8_t resolutionAndComponentFlags = 48;

              if (lastLongitude > 360000000)
                lastLongitude -= 360000000;

              if (lastLatitude > 90000000)
                lastLatitude = 180000000 - lastLatitude;

              // ******* GRIB 2 ********

              GRIB2::RotatedLatLonImpl *def2 = new GRIB2::RotatedLatLonImpl();
              GRIB2::LatLonSettings latLon;
              GRIB2::ScanningModeSettings scanningMode2;
              GRIB2::GridSettings grid;
              GRIB2::RotationSettings rotation2;

              grid.setNi(T::UInt32_opt(ni));
              grid.setNj(T::UInt32_opt(nj));
              grid.setLongitudeOfFirstGridPoint(T::Int32_opt(longitude));
              grid.setLatitudeOfFirstGridPoint(T::Int32_opt(latitude));
              grid.setLongitudeOfLastGridPoint(T::Int32_opt(lastLongitude));
              grid.setLatitudeOfLastGridPoint(T::Int32_opt(lastLatitude));
              latLon.setGrid(grid);

              latLon.setIDirectionIncrement(T::UInt32_opt(iInc));
              latLon.setJDirectionIncrement(T::UInt32_opt(jInc));

              if (strcasecmp(scanningMode,"+x+y") == 0)
                scanningMode2.setScanningMode(0x40);
              else
              if (strcasecmp(scanningMode,"-x+y") == 0)
              {
                lastLongitude = longitude - (ni*iInc - iInc);
                scanningMode2.setScanningMode(0x80+0x40);
              }
              else
              if (strcasecmp(scanningMode,"+x-y") == 0)
              {
                lastLatitude = latitude - (nj*jInc - jInc);
                scanningMode2.setScanningMode(0);
              }
              else
              if (strcasecmp(scanningMode,"-x-y") == 0)
              {
                lastLongitude = longitude - (ni*iInc - iInc);
                lastLatitude = latitude - (nj*jInc - jInc);
                scanningMode2.setScanningMode(0x80);
              }

              latLon.setScanningMode(scanningMode2);
              def2->setLatLon(latLon);

              rotation2.setLongitudeOfSouthernPole(T::UInt32_opt(longitudeOfSouthernPole));
              rotation2.setLatitudeOfSouthernPole(T::Int32_opt(latitudeOfSouthernPole));
              rotation2.setAngleOfRotation(0);
              def2->setRotation(rotation2);

              def2->setGridGeometryId(geometryId);
              def2->setGridGeometryName(geometryName);

              //def2->print(std::cout,0,0);
              //T::Hash hash = def2->getGridHash();
              //printf("HASH %llu\n",(unsigned long long)hash);

              mGridDefinitions2.insert(std::pair<uint,GRIB2::GridDefinition_ptr>(geometryId,def2));

              // ******* GRIB 1 ********

              GRIB1::RotatedLatLonImpl *def1 = new GRIB1::RotatedLatLonImpl();
              GRIB1::GridAreaSettings gridArea;
              GRIB1::RotationSettings rotation1;
              GRIB1::ScanningModeSettings scanningMode1;

              gridArea.setLatitudeOfFirstGridPoint((std::int24_t)(latitude/1000));
              gridArea.setLongitudeOfFirstGridPoint((std::int24_t)(longitude/1000));
              gridArea.setLatitudeOfLastGridPoint((std::int24_t)(lastLatitude/1000));
              gridArea.setLongitudeOfLastGridPoint((std::int24_t)(lastLongitude/1000));

              rotation1.setLatitudeOfSouthernPole((std::int24_t)(latitudeOfSouthernPole/1000));
              rotation1.setLongitudeOfSouthernPole((std::int24_t)(longitudeOfSouthernPole/1000));
              rotation1.setGeography_angleOfRotationInDegrees(0);
              def1->setRotation(rotation1);

              def1->setNi((std::uint16_t)ni);
              def1->setNj((std::uint16_t)nj);
              def1->setGridArea(gridArea);
              def1->setIDirectionIncrement((std::uint16_t)(iInc/1000));
              def1->setJDirectionIncrement((std::uint16_t)(jInc/1000));

              if (strcasecmp(scanningMode,"+x+y") == 0)
                scanningMode1.setScanningMode(0x40);
              else
              if (strcasecmp(scanningMode,"-x+y") == 0)
                scanningMode1.setScanningMode(0x80+0x40);
              else
              if (strcasecmp(scanningMode,"+x-y") == 0)
                scanningMode1.setScanningMode(0);
              else
              if (strcasecmp(scanningMode,"-x-y") == 0)
                scanningMode1.setScanningMode(0x80);

              def1->setScanningMode(scanningMode1);

              def1->setGridGeometryId(geometryId);
              def1->setGridGeometryName(geometryName);

              // def1->print(std::cout,0,0);
              // T::Hash hash = def1->getGridHash();
              // printf("HASH %llu\n",(unsigned long long)hash);

              mGridDefinitions1.insert(std::pair<uint,GRIB1::GridDefinition_ptr>(geometryId,def1));
            }
            break;

            case T::GridProjection::StretchedLatLon:
              break;

            case T::GridProjection::StretchedRotatedLatLon:
              break;

            case T::GridProjection::VariableResolutionLatLon:
              break;

            case T::GridProjection::VariableResolutionRotatedLatLon:
              break;

            case T::GridProjection::Mercator:
              break;

            case T::GridProjection::TransverseMercator:
              break;

            case T::GridProjection::PolarStereographic:
              break;

            case T::GridProjection::LambertConformal:
            {
              uint geometryId = (uint)atoll(field[1]);
              char *geometryName = field[2];
              int ni = atoll(field[3]);
              int nj = atoll(field[4]);
              int longitude = (int)(atof(field[5])*1000000);
              int latitude = (int)(atof(field[6])*1000000);
              int iInc = (int)(atof(field[7]) * 1000000);
              int jInc = (int)(atof(field[8]) * 1000000);
              char *scanningMode = field[9];
              //int orientation = (int)atoll(field[10]);
              int latin1 = (int)(atof(field[11])*1000000);
              int latin2 = (int)(atof(field[12])*1000000);
              int longitudeOfSouthernPole = (int)(atof(field[13])*1000000);
              int latitudeOfSouthernPole = (int)(atof(field[14])*1000000);

              // ******* GRIB 2 ********

              GRIB2::LambertConformalImpl *def2 = new GRIB2::LambertConformalImpl();
              GRIB2::ScanningModeSettings scanningMode2;

              if (strcasecmp(scanningMode,"+x+y") == 0)
                scanningMode2.setScanningMode(0x40);
              else
              if (strcasecmp(scanningMode,"-x+y") == 0)
                scanningMode2.setScanningMode(0x80+0x40);
              else
              if (strcasecmp(scanningMode,"+x-y") == 0)
                scanningMode2.setScanningMode(0);
              else
              if (strcasecmp(scanningMode,"-x-y") == 0)
                scanningMode2.setScanningMode(0x80);

              def2->setScanningMode(scanningMode2);

              def2->setNx(T::UInt32_opt(ni));
              def2->setNy(T::UInt32_opt(nj));
              def2->setLatitudeOfFirstGridPoint(T::Int32_opt(latitude));
              def2->setLongitudeOfFirstGridPoint(T::UInt32_opt(longitude));

              //def2->setLaD(T::Int32_opt laD);
              //def2->setLoV(T::UInt32_opt loV);
              def2->setDx(T::UInt32_opt(iInc));
              def2->setDy(T::UInt32_opt(jInc));
              //def2->setProjectionCentreFlag(std::uint8_t projectionCentreFlag);
              def2->setLatin1(T::Int32_opt(latin1));
              def2->setLatin2(T::Int32_opt(latin2));
              def2->setLatitudeOfSouthernPole(T::Int32_opt(latitudeOfSouthernPole));
              def2->setLongitudeOfSouthernPole(T::UInt32_opt(longitudeOfSouthernPole));

              def2->setGridGeometryId(geometryId);
              def2->setGridGeometryName(geometryName);

              //def2->print(std::cout,0,0);
              //T::Hash hash = def2->getGridHash();
              //printf("HASH %llu\n",(unsigned long long)hash);

              mGridDefinitions2.insert(std::pair<uint,GRIB2::GridDefinition_ptr>(geometryId,def2));

              // ******* GRIB 1 ********

              GRIB1::LambertConformalImpl *def1 = new GRIB1::LambertConformalImpl();
              GRIB1::ScanningModeSettings scanningMode1;

              if (strcasecmp(scanningMode,"+x+y") == 0)
                scanningMode1.setScanningMode(0x40);
              else
              if (strcasecmp(scanningMode,"-x+y") == 0)
                scanningMode1.setScanningMode(0x80+0x40);
              else
              if (strcasecmp(scanningMode,"+x-y") == 0)
                scanningMode1.setScanningMode(0);
              else
              if (strcasecmp(scanningMode,"-x-y") == 0)
                scanningMode1.setScanningMode(0x80);

              def1->setScanningMode(scanningMode1);

              def1->setNx(std::uint16_t(ni));
              def1->setNy(std::uint16_t(nj));
              def1->setLatitudeOfFirstGridPoint((std::int24_t)(latitude/1000));
              def1->setLongitudeOfFirstGridPoint((std::int24_t)(longitude/1000));
              //def1->setResolutionFlags(ResolutionFlagsSettings resolutionFlags);
              //def1->setLoV(std::int24_t loV);
              def1->setDxInMetres((std::uint24_t)iInc);
              def1->setDyInMetres((std::uint24_t)jInc);
              //def1->setProjectionCentreFlag(std::uint8_t projectionCentreFlag);
              def1->setLatin1((std::int24_t)latin1);
              def1->setLatin2((std::int24_t)latin2);
              def1->setLatitudeOfSouthernPole((std::int24_t)latitudeOfSouthernPole);
              def1->setLongitudeOfSouthernPole((std::int24_t)longitudeOfSouthernPole);

              def1->setGridGeometryId(geometryId);
              def1->setGridGeometryName(geometryName);

              //def1->print(std::cout,0,0);
              //hash = def1->getGridHash();
              //printf("HASH %llu\n",(unsigned long long)hash);

              mGridDefinitions2.insert(std::pair<uint,GRIB2::GridDefinition_ptr>(geometryId,def2));

            }
            break;

            case T::GridProjection::ObliqueLambertConformal:
              break;

            case T::GridProjection::Albers:
              break;

            case T::GridProjection::Gaussian:
              break;

            case T::GridProjection::RotatedGaussian:
              break;

            case T::GridProjection::StretchedGaussian:
              break;

            case T::GridProjection::StretchedRotatedGaussian:
              break;

            case T::GridProjection::SphericalHarmonic:
              break;

            case T::GridProjection::RotatedSphericalHarmonic:
              break;

            case T::GridProjection::StretchedSphericalHarmonic:
              break;

            case T::GridProjection::StretchedRotatedSphericalHarmonic:
              break;

            case T::GridProjection::SpaceView:
              break;

            case T::GridProjection::Triangular:
              break;

            case T::GridProjection::Unstructured:
              break;

            case T::GridProjection::EquatorialAzimuthalEquidistant:
              break;

            case T::GridProjection::AzimuthRange:
              break;

            case T::GridProjection::IrregularLatLon:
              break;

            case T::GridProjection::LambertAzimuthalEqualArea:
              break;

            case T::GridProjection::CrossSection:
              break;

            case T::GridProjection::Hovmoller:
              break;

            case T::GridProjection::TimeSection:
              break;

            case T::GridProjection::GnomonicProjection:
              break;

            case T::GridProjection::SimplePolyconicProjection:
              break;

            case T::GridProjection::MillersCylindricalProjection:
              break;
          };
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
