#include "GridDef.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/ShowFunction.h"

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


#define FUNCTION_TRACE FUNCTION_TRACE_OFF



namespace SmartMet
{
namespace Identification
{

// This is a global object that contains global configuration information.

GridDef gridDef;




/*! \brief The constructor of the class. */

GridDef::GridDef()
{
  FUNCTION_TRACE
  try
  {
    mInitialized = false;
    mLastCheckTime = 0;

    mGrib_parameterDef_modificationTime = 0;
    mGrib_tableDef_modificationTime = 0;
    mGrib_unitDef_modificationTime = 0;
    mGrib1_parameterDef_modificationTime = 0;
    mGrib1_levelDef_modificationTime = 0;
    mGrib1_timeRangeDef_modificationTime = 0;
    mGrib2_parameterDef_modificationTime = 0;
    mGrib2_levelDef_modificationTime = 0;
    mGrib2_timeRangeDef_modificationTime = 0;
    mFmi_parameterDef_modificationTime = 0;
    mFmi_levelDef_modificationTime = 0;
    mFmi_parametersFromGrib1_modificationTime = 0;
    mFmi_parametersFromGrib2_modificationTime = 0;
    mFmi_parametersFromNewbase_modificationTime = 0;
    mFmi_levelsFromGrib1_modificationTime = 0;
    mFmi_levelsFromGrib2_modificationTime = 0;
    mFmi_producersFromGrib_modificationTime = 0;
    mFmi_geometryDef_modificationTime = 0;
    mNewbase_parameterDef_modificationTime = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The destructor of the class. */

GridDef::~GridDef()
{
  FUNCTION_TRACE
  try
  {
    for (auto it=mGridDefinitions1.begin(); it!=mGridDefinitions1.end(); ++it)
    {
      delete (*it);
    }

    for (auto it=mGridDefinitions2.begin(); it!=mGridDefinitions2.end(); ++it)
    {
      delete (*it);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




void GridDef::init(const char* configFile)
{
  FUNCTION_TRACE
  try
  {
    const char *configAttribute[] =
    {
      "smartmet.library.grid-files.grib.parameterDef[]",
      "smartmet.library.grid-files.grib.tableDef[]",
      "smartmet.library.grid-files.grib.unitDef[]",
      "smartmet.library.grid-files.grib1.parameterDef[]",
      "smartmet.library.grid-files.grib1.levelDef[]",
      "smartmet.library.grid-files.grib1.timeRangeDef[]",
      "smartmet.library.grid-files.grib2.parameterDef[]",
      "smartmet.library.grid-files.grib2.levelDef[]",
      "smartmet.library.grid-files.grib2.timeRangeDef[]",
      "smartmet.library.grid-files.fmi.parameterDef[]",
      "smartmet.library.grid-files.fmi.levelDef[]",
      "smartmet.library.grid-files.fmi.geometryDef[]",
      "smartmet.library.grid-files.fmi.parametersFromGrib1[]",
      "smartmet.library.grid-files.fmi.parametersFromGrib2[]",
      "smartmet.library.grid-files.fmi.parametersFromNewbase[]",
      "smartmet.library.grid-files.fmi.levelsFromGrib1[]",
      "smartmet.library.grid-files.fmi.levelsFromGrib2[]",
      "smartmet.library.grid-files.fmi.producersFromGrib[]",
      "smartmet.library.grid-files.newbase.parameterDef[]",
       NULL
    };

    if (mInitialized)
      return;

    mConfigFileName = configFile;

    mConfigurationFile.readFile(configFile);
    //mConfigurationFile.print(std::cout,0,0);

    uint t=0;
    while (configAttribute[t] != NULL)
    {
      if (!mConfigurationFile.findAttribute(configAttribute[t]))
      {
        SmartMet::Spine::Exception exception(BCP, "Missing configuration attribute!");
        exception.addParameter("File",mConfigFileName);
        exception.addParameter("Attribute",configAttribute[t]);
        throw exception;
      }
      t++;
    }

    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.grib.parameterDef",mGrib_parameterDef_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.grib.tableDef",mGrib_tableDef_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.grib.unitDef",mGrib_unitDef_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.grib1.parameterDef",mGrib1_parameterDef_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.grib1.levelDef",mGrib1_levelDef_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.grib1.timeRangeDef",mGrib1_timeRangeDef_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.grib2.parameterDef",mGrib2_parameterDef_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.grib2.levelDef",mGrib2_levelDef_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.grib2.timeRangeDef",mGrib2_timeRangeDef_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.fmi.parameterDef",mFmi_parameterDef_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.fmi.levelDef",mFmi_levelDef_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.fmi.geometryDef",mFmi_geometryDef_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.fmi.parametersFromGrib1",mFmi_parametersFromGrib1_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.fmi.parametersFromGrib2",mFmi_parametersFromGrib2_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.fmi.parametersFromNewbase",mFmi_parametersFromNewbase_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.fmi.levelsFromGrib1",mFmi_levelsFromGrib1_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.fmi.levelsFromGrib2",mFmi_levelsFromGrib2_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.fmi.producersFromGrib",mFmi_producersFromGrib_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.newbase.parameterDef",mNewbase_parameterDef_files);

    mInitialized = true;

    updateCheck();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Initialization failed!",NULL);
    exception.addParameter("Configuration File",configFile);
    throw exception;
  }
}





void GridDef::updateCheck()
{
  FUNCTION_TRACE
  try
  {
    if (!mInitialized)
      throw SmartMet::Spine::Exception(BCP,"The 'GridDef' object is not initialized! Call init() first!");

    if ((mLastCheckTime + 30) < time(0))
    {
      AutoThreadLock lock(&mThreadLock);

      mLastCheckTime = time(0);

      updateGrib();
      updateGrib1();
      updateGrib2();
      updateFmi();
      updateNewbase();
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





time_t GridDef::getModificationTime(string_vec& files)
{
  FUNCTION_TRACE
  try
  {
    time_t t = 0;
    for (auto it = files.begin(); it != files.end(); ++it)
    {
      time_t tt = getFileModificationTime(it->c_str());
      if (tt > t)
        t = tt;
    }

    return t;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridDef::updateGrib()
{
  FUNCTION_TRACE
  try
  {
    time_t tt = getModificationTime(mGrib_parameterDef_files);
    if (tt != mGrib_parameterDef_modificationTime)
    {
      mGrib_parameterDef_records.clear();
      for (auto it = mGrib_parameterDef_files.begin(); it != mGrib_parameterDef_files.end(); ++it)
      {
        loadGribParameterDefinitions(it->c_str());
      }
      mGrib_parameterDef_modificationTime = tt;
    }

    tt = getModificationTime(mGrib_tableDef_files);
    if (tt != mGrib_tableDef_modificationTime)
    {
      mGrib_tableDef_records.clear();
      for (auto it = mGrib_parameterDef_files.begin(); it != mGrib_parameterDef_files.end(); ++it)
      {
        loadGribTableValues(it->c_str());
      }
      mGrib_tableDef_modificationTime = tt;
    }

    tt = getModificationTime(mGrib_unitDef_files);
    if (tt != mGrib_unitDef_modificationTime)
    {
      mGrib_unitDef_records.clear();
      for (auto it = mGrib_unitDef_files.begin(); it != mGrib_unitDef_files.end(); ++it)
      {
        loadGribUnitDefinitions(it->c_str());
      }
      mGrib_unitDef_modificationTime = tt;
    }

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridDef::updateGrib1()
{
  FUNCTION_TRACE
  try
  {
    time_t tt = getModificationTime(mGrib1_parameterDef_files);
    if (tt != mGrib1_parameterDef_modificationTime)
    {
      mGrib1_parameterDef_records.clear();
      for (auto it = mGrib1_parameterDef_files.begin(); it != mGrib1_parameterDef_files.end(); ++it)
      {
        loadGrib1ParameterDefs(it->c_str());
      }
      mGrib1_parameterDef_modificationTime = tt;
    }

    tt = getModificationTime(mGrib1_levelDef_files);
    if (tt != mGrib1_levelDef_modificationTime)
    {
      mGrib1_levelDef_records.clear();
      for (auto it = mGrib1_levelDef_files.begin(); it != mGrib1_levelDef_files.end(); ++it)
      {
        loadGrib1LevelDefinitions(it->c_str());
      }
      mGrib1_levelDef_modificationTime = tt;
    }

    tt = getModificationTime(mGrib1_timeRangeDef_files);
    if (tt != mGrib1_timeRangeDef_modificationTime)
    {
      mGrib1_timeRangeDef_records.clear();
      for (auto it = mGrib1_timeRangeDef_files.begin(); it != mGrib1_timeRangeDef_files.end(); ++it)
      {
        loadGrib1TimeRangeDefinitions(it->c_str());
      }
      mGrib1_timeRangeDef_modificationTime = tt;
    }

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridDef::updateGrib2()
{
  FUNCTION_TRACE
  try
  {
    time_t tt = getModificationTime(mGrib2_parameterDef_files);
    if (tt != mGrib2_parameterDef_modificationTime)
    {
      mGrib2_parameterDef_records.clear();
      for (auto it = mGrib2_parameterDef_files.begin(); it != mGrib2_parameterDef_files.end(); ++it)
      {
        loadGrib2ParameterDefs(it->c_str());
      }
      mGrib2_parameterDef_modificationTime = tt;
    }

    tt = getModificationTime(mGrib2_levelDef_files);
    if (tt != mGrib2_levelDef_modificationTime)
    {
      mGrib2_levelDef_records.clear();
      for (auto it = mGrib2_levelDef_files.begin(); it != mGrib2_levelDef_files.end(); ++it)
      {
        loadGrib2LevelDefinitions(it->c_str());
      }
      mGrib2_levelDef_modificationTime = tt;
    }

    tt = getModificationTime(mGrib2_timeRangeDef_files);
    if (tt != mGrib2_timeRangeDef_modificationTime)
    {
      mGrib2_timeRangeDef_records.clear();
      for (auto it = mGrib2_timeRangeDef_files.begin(); it != mGrib2_timeRangeDef_files.end(); ++it)
      {
        loadGrib2TimeRangeDefinitions(it->c_str());
      }
      mGrib2_timeRangeDef_modificationTime = tt;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridDef::updateFmi()
{
  FUNCTION_TRACE
  try
  {
    time_t tt = getModificationTime(mFmi_parameterDef_files);
    if (tt != mFmi_parameterDef_modificationTime)
    {
      mFmi_parameterDef_records.clear();
      for (auto it = mFmi_parameterDef_files.begin(); it != mFmi_parameterDef_files.end(); ++it)
      {
        loadFmiParameterDefinitions(it->c_str());
      }
      mFmi_parameterDef_modificationTime = tt;
    }

    tt = getModificationTime(mFmi_levelDef_files);
    if (tt != mFmi_levelDef_modificationTime)
    {
      mFmi_levelDef_records.clear();
      for (auto it = mFmi_levelDef_files.begin(); it != mFmi_levelDef_files.end(); ++it)
      {
        loadFmiLevelDefinitions(it->c_str());
      }
      mFmi_levelDef_modificationTime = tt;
    }

    tt = getModificationTime(mFmi_parametersFromGrib1_files);
    if (tt != mFmi_parametersFromGrib1_modificationTime)
    {
      mFmi_parametersFromGrib1_records.clear();
      for (auto it = mFmi_parametersFromGrib1_files.begin(); it != mFmi_parametersFromGrib1_files.end(); ++it)
      {
        loadFmiParameterId_grib1(it->c_str());
      }
      mFmi_parametersFromGrib1_modificationTime = tt;
    }

    tt = getModificationTime(mFmi_parametersFromGrib2_files);
    if (tt != mFmi_parametersFromGrib2_modificationTime)
    {
      mFmi_parametersFromGrib2_records.clear();
      for (auto it = mFmi_parametersFromGrib2_files.begin(); it != mFmi_parametersFromGrib2_files.end(); ++it)
      {
        loadFmiParameterId_grib2(it->c_str());
      }
      mFmi_parametersFromGrib2_modificationTime = tt;
    }

    tt = getModificationTime(mFmi_parametersFromNewbase_files);
    if (tt != mFmi_parametersFromNewbase_modificationTime)
    {
      mFmi_parametersFromNewbase_records.clear();
      for (auto it = mFmi_parametersFromNewbase_files.begin(); it != mFmi_parametersFromNewbase_files.end(); ++it)
      {
        loadFmiParameterId_newbase(it->c_str());
      }
      mFmi_parametersFromNewbase_modificationTime = tt;
    }

    tt = getModificationTime(mFmi_levelsFromGrib1_files);
    if (tt != mFmi_levelsFromGrib1_modificationTime)
    {
      mFmi_levelsFromGrib1_records.clear();
      for (auto it = mFmi_levelsFromGrib1_files.begin(); it != mFmi_levelsFromGrib1_files.end(); ++it)
      {
        loadFmiLevelId_grib1(it->c_str());
      }
      mFmi_levelsFromGrib1_modificationTime = tt;
    }

    tt = getModificationTime(mFmi_levelsFromGrib2_files);
    if (tt != mFmi_levelsFromGrib2_modificationTime)
    {
      mFmi_levelsFromGrib2_records.clear();
      for (auto it = mFmi_levelsFromGrib2_files.begin(); it != mFmi_levelsFromGrib2_files.end(); ++it)
      {
        loadFmiLevelId_grib2(it->c_str());
      }
      mFmi_levelsFromGrib2_modificationTime = tt;
    }

    tt = getModificationTime(mFmi_producersFromGrib_files);
    if (tt != mFmi_producersFromGrib_modificationTime)
    {
      mFmi_producersFromGrib_records.clear();
      for (auto it = mFmi_producersFromGrib_files.begin(); it != mFmi_producersFromGrib_files.end(); ++it)
      {
        loadFmiProducerId_grib(it->c_str());
      }
      mFmi_producersFromGrib_modificationTime = tt;
    }

    tt = getModificationTime(mFmi_geometryDef_files);
    if (tt != mFmi_geometryDef_modificationTime)
    {
      mGridDefinitions1.clear();
      mGridDefinitions2.clear();

      for (auto it = mFmi_geometryDef_files.begin(); it != mFmi_geometryDef_files.end(); ++it)
      {
        loadGeometryDefinitions(it->c_str());
      }
      mFmi_geometryDef_modificationTime = tt;
    }

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridDef::updateNewbase()
{
  FUNCTION_TRACE
  try
  {
    time_t tt = getModificationTime(mNewbase_parameterDef_files);
    if (tt != mNewbase_parameterDef_modificationTime)
    {
      mNewbase_parameterDef_records.clear();
      for (auto it = mNewbase_parameterDef_files.begin(); it != mNewbase_parameterDef_files.end(); ++it)
      {
        loadNewbaseParameterDefinitions(it->c_str());
      }
      mNewbase_parameterDef_modificationTime = tt;
    }

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getGribTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,std::string table,std::uint32_t number)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    for (auto it = mGrib_tableDef_records.begin(); it != mGrib_tableDef_records.end(); ++it)
    {
      if (it->mGribVersion == gribVersion  &&  it->mTableVersion == tableVersion  &&  it->mTable == table  &&  it->mNumber == number)
        return it->mValue;
    }
    return std::to_string(number);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getGribTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,std::string table,T::UInt8_opt number)
{
  FUNCTION_TRACE
  try
  {
    if (number)
      return getGribTableValue(gribVersion,tableVersion,table,*number);

    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getGribTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,std::string table,T::UInt16_opt number)
{
  FUNCTION_TRACE
  try
  {
    if (number)
      return getGribTableValue(gribVersion,tableVersion,table,*number);

    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint GridDef::getGrib1ParameterDefCount()
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    return (uint)mGrib1_parameterDef_records.size();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDef::getGrib1ParameterDefById(T::ParamId gribParamId,Grib1ParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getGrib1ParameterDefById(gribParamId);
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





bool GridDef::getGrib1ParameterDefByIndex(uint index,Grib1ParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    if (index >= (uint)mGrib1_parameterDef_records.size())
      return false;

    paramDef = mGrib1_parameterDef_records[index];
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDef::getGrib1ParameterDefByName(std::string gribParamName,Grib1ParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getGrib1ParameterDefByName(gribParamName);
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





bool GridDef::getGrib1ParameterDefByTable(uint tableVersion,uint indicatorOfParameter,Grib1ParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getGrib1ParameterDefByTable(tableVersion,indicatorOfParameter);
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





Grib1ParamDef_cptr GridDef::getGrib1ParameterDefById(T::ParamId gribParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGrib1_parameterDef_records.begin(); it != mGrib1_parameterDef_records.end(); ++it)
    {
      if (strcasecmp(it->mGribParameterId.c_str(),gribParamId.c_str()) == 0)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





Grib1ParamDef_cptr GridDef::getGrib1ParameterDefByName(std::string gribParamName)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGrib1_parameterDef_records.begin(); it != mGrib1_parameterDef_records.end(); ++it)
    {
      if (strcasecmp(it->mParameterName.c_str(),gribParamName.c_str()) == 0)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





Grib1ParamDef_cptr GridDef::getGrib1ParameterDefByTable(uint tableVersion,uint indicatorOfParameter)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGrib1_parameterDef_records.begin(); it != mGrib1_parameterDef_records.end(); ++it)
    {
      if (it->mTable2Version == tableVersion  &&  it->mIndicatorOfParameter == indicatorOfParameter)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint GridDef::getGrib2ParameterDefCount()
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    return (uint)mGrib2_parameterDef_records.size();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDef::getGrib2ParameterDefById(T::ParamId gribParamId,Grib2ParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getGrib2ParameterDefById(gribParamId);
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





bool GridDef::getGrib2ParameterDefByIndex(uint index,Grib2ParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    if (index >= (uint)mGrib2_parameterDef_records.size())
      return false;

    paramDef = mGrib2_parameterDef_records[index];
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDef::getGrib2ParameterDefByName(std::string gribParamName,Grib2ParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getGrib2ParameterDefByName(gribParamName);
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





Grib2ParamDef_cptr GridDef::getGrib2ParameterDefById(T::ParamId gribParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGrib2_parameterDef_records.begin(); it != mGrib2_parameterDef_records.end(); ++it)
    {
      if (strcasecmp(it->mGribParameterId.c_str(),gribParamId.c_str()) == 0)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





Grib2ParamDef_cptr GridDef::getGrib2ParameterDefByName(std::string gribParamName)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGrib2_parameterDef_records.begin(); it != mGrib2_parameterDef_records.end(); ++it)
    {
      if (strcasecmp(it->mParameterName.c_str(),gribParamName.c_str()) == 0)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridDef::loadGribTableValues(const char *filename)
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
          GribTableValue rec;

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

          mGrib_tableDef_records.push_back(rec);
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





void GridDef::loadGribParameterDefinitions(const char *filename)
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
          GribParameterDef rec;
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

          mGrib_parameterDef_records.push_back(rec);
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





bool GridDef::getGribParamDefById(T::ParamId gribParamId,GribParameterDef&  paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getGribParamDefById(gribParamId);
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





bool GridDef::getGribParamDefByName(std::string gribParamName,GribParameterDef&  paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getGribParamDefByName(gribParamName);
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





bool GridDef::getGribParamDef(uint discipline,uint category,uint number,GribParameterDef&  paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getGribParamDef(discipline,category,number);
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





GribParamDef_cptr GridDef::getGribParamDefById(T::ParamId gribParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGrib_parameterDef_records.begin(); it != mGrib_parameterDef_records.end(); ++it)
    {
      if (strcasecmp(it->mGribParameterId.c_str(),gribParamId.c_str()) == 0)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





GribParamDef_cptr GridDef::getGribParamDefByName(std::string gribParamName)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGrib_parameterDef_records.begin(); it != mGrib_parameterDef_records.end(); ++it)
    {
      if (strcasecmp(it->mParameterName.c_str(),gribParamName.c_str()) == 0)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





GribParamDef_cptr GridDef::getGribParamDef(uint discipline,uint category,uint number)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGrib_parameterDef_records.begin(); it != mGrib_parameterDef_records.end(); ++it)
    {
      if (it->mDiscipline == discipline &&  it->mParameterCategory == category && it->mParameterNumber == number)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDef::getFmiLevelDef(uint levelId,LevelDef& levelDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getFmiLevelDef(levelId);
    if (def == NULL)
      return false;

    levelDef = *def;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDef::getGrib1LevelDef(uint levelId,LevelDef& levelDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getGrib1LevelDef(levelId);
    if (def == NULL)
      return false;

    levelDef = *def;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDef::getGrib2LevelDef(uint levelId,LevelDef& levelDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getGrib2LevelDef(levelId);
    if (def == NULL)
      return false;

    levelDef = *def;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





LevelDef_cptr GridDef::getFmiLevelDef(uint levelId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_levelDef_records.begin(); it != mFmi_levelDef_records.end(); ++it)
    {
      if (it->mLevelId == levelId)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





LevelDef_cptr GridDef::getGrib1LevelDef(uint levelId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGrib1_levelDef_records.begin(); it != mGrib1_levelDef_records.end(); ++it)
    {
      if (it->mLevelId == levelId)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





LevelDef_cptr GridDef::getGrib2LevelDef(uint levelId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGrib2_levelDef_records.begin(); it != mGrib2_levelDef_records.end(); ++it)
    {
      if (it->mLevelId == levelId)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDef::getGrib1TimeRangeDef(uint timeRangeId,TimeRangeDef& timeRangeDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getGrib1TimeRangeDef(timeRangeId);
    if (def == NULL)
      return false;

    timeRangeDef = *def;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDef::getGrib2TimeRangeDef(uint timeRangeId,TimeRangeDef& timeRangeDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getGrib2TimeRangeDef(timeRangeId);
    if (def == NULL)
      return false;

    timeRangeDef = *def;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





TimeRangeDef_cptr GridDef::getGrib1TimeRangeDef(uint timeRangeId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGrib1_timeRangeDef_records.begin(); it != mGrib1_timeRangeDef_records.end(); ++it)
    {
      if (it->mTimeRangeId == timeRangeId)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





TimeRangeDef_cptr GridDef::getGrib2TimeRangeDef(uint timeRangeId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGrib2_timeRangeDef_records.begin(); it != mGrib2_timeRangeDef_records.end(); ++it)
    {
      if (it->mTimeRangeId == timeRangeId)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridDef::loadGribUnitDefinitions(const char *filename)
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

        if (c > 2)
        {
          UnitDefinition rec;
          rec.mOriginalUnits = field[0];
          rec.mPreferredUnits = field[1];
          rec.mPreferredAreaInterpolationMethod = (short)atoi(field[2]);

          mGrib_unitDef_records.push_back(rec);
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





void GridDef::loadGrib1LevelDefinitions(const char *filename)
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

        if (c > 2)
        {
          LevelDef rec;

          if (field[0][0] != '\0')
            rec.mLevelId = (uint)atoll(field[0]);

          if (field[1][0] != '\0')
            rec.mName = field[1];

          if (field[2][0] != '\0')
            rec.mDescription = field[2];

          mGrib1_levelDef_records.push_back(rec);
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





void GridDef::loadGrib2LevelDefinitions(const char *filename)
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

        if (c > 2)
        {
          LevelDef rec;

          if (field[0][0] != '\0')
            rec.mLevelId = (uint)atoll(field[0]);

          if (field[1][0] != '\0')
            rec.mName = field[1];

          if (field[2][0] != '\0')
            rec.mDescription = field[2];

          mGrib2_levelDef_records.push_back(rec);
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





void GridDef::loadGrib1TimeRangeDefinitions(const char *filename)
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

        if (c > 2)
        {
          TimeRangeDef rec;

          if (field[0][0] != '\0')
            rec.mTimeRangeId = (uint)atoll(field[0]);

          if (field[1][0] != '\0')
            rec.mName = field[1];

          if (field[2][0] != '\0')
            rec.mDescription = field[2];

          mGrib1_timeRangeDef_records.push_back(rec);
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





void GridDef::loadGrib2TimeRangeDefinitions(const char *filename)
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

        if (c > 2)
        {
          TimeRangeDef rec;

          if (field[0][0] != '\0')
            rec.mTimeRangeId = (uint)atoll(field[0]);

          if (field[1][0] != '\0')
            rec.mName = field[1];

          if (field[2][0] != '\0')
            rec.mDescription = field[2];

          mGrib2_timeRangeDef_records.push_back(rec);
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





void GridDef::loadGrib1ParameterDefs(const char *filename)
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

        if (c > 7)
        {
          Grib1ParameterDef rec;

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

          mGrib1_parameterDef_records.push_back(rec);
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






void GridDef::loadGrib2ParameterDefs(const char *filename)
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

        if (c > 24)
        {
          Grib2ParameterDef rec;

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
          mGrib2_parameterDef_records.push_back(rec);
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





void GridDef::loadFmiLevelDefinitions(const char *filename)
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

        if (c > 2)
        {
          LevelDef rec;

          if (field[0][0] != '\0')
            rec. mLevelId = (uint)atoll(field[0]);

          if (field[1][0] != '\0')
            rec.mName = field[1];

          if (field[2][0] != '\0')
            rec.mDescription = field[2];

          mFmi_levelDef_records.push_back(rec);
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





void GridDef::loadFmiParameterId_grib1(const char *filename)
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

        if (c > 8)
        {
          FmiParameterId_grib1 rec;

          if (field[0][0] != '\0')
            rec. mFmiParameterId = field[0];

          if (field[1][0] != '\0')
            rec.mFmiProducerId = (uint)atoll(field[1]);

          if (field[2][0] != '\0')
            rec.mGeneratingProcessIdentifier = (uint)atoll(field[2]);

          if (field[3][0] != '\0')
            rec.mCentre = (uint)atoll(field[3]);

          if (field[4][0] != '\0')
            rec.mGribTableVersion = (uint)atoll(field[4]);

          if (field[5][0] != '\0')
            rec.mGribParameterNumber = (uint)atoll(field[5]);

          if (field[6][0] != '\0')
            rec.mGribTimerangeIndicator = (uint)atoll(field[6]);

          if (field[7][0] != '\0')
            rec.mFmiParameterLevelId = (uint)atoll(field[7]);

          if (field[8][0] != '\0')
            rec.mGribParameterLevelId = (uint)atoll(field[8]);

          if (field[9][0] != '\0')
            rec.mParameterLevel = (uint)atoll(field[9]);

          mFmi_parametersFromGrib1_records.push_back(rec);
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





void GridDef::loadFmiParameterId_grib2(const char *filename)
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
          FmiParameterId_grib2 rec;

          if (field[0][0] != '\0')
            rec.mFmiParameterId = field[0];

          if (field[1][0] != '\0')
            rec.mFmiProducerId = (uint)atoll(field[1]);

          if (field[2][0] != '\0')
            rec.mGeneratingProcessIdentifier = (uint)atoll(field[2]);

          if (field[3][0] != '\0')
            rec.mCentre = (uint)atoll(field[3]);

          if (field[4][0] != '\0')
            rec.mDiscipline = (uint)atoll(field[4]);

          if (field[5][0] != '\0')
            rec.mParameterCategory = (uint)atoll(field[5]);

          if (field[6][0] != '\0')
            rec.mParameterNumber = (uint)atoll(field[6]);

          if (field[7][0] != '\0')
            rec.mFmiParameterLevelId = (uint)atoll(field[7]);

          if (field[8][0] != '\0')
            rec.mGribParameterLevelId = (uint)atoll(field[8]);

          if (field[9][0] != '\0')
            rec.mParameterLevel = (uint)atoll(field[9]);

          mFmi_parametersFromGrib2_records.push_back(rec);
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





void GridDef::loadFmiParameterId_newbase(const char *filename)
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

        if (c > 2)
        {
          FmiParameterId_newbase rec;

          if (field[0][0] != '\0')
            rec.mFmiParameterId = field[0];

          if (field[1][0] != '\0')
            rec.mNewbaseParameterId = field[1];

          if (field[2][0] != '\0')
            rec.mConversionFunction = field[2];

          mFmi_parametersFromNewbase_records.push_back(rec);
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





void GridDef::loadFmiParameterDefinitions(const char *filename)
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

        if (c > 7)
        {
          FmiParameterDef rec;

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
            rec.mAreaInterpolationMethod = (short)atoll(field[5]);

          if (field[6][0] != '\0')
            rec.mTimeInterpolationMethod = (short)atoll(field[6]);

          if (field[7][0] != '\0')
            rec.mLevelInterpolationMethod = (short)atoll(field[7]);

          mFmi_parameterDef_records.push_back(rec);
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





void GridDef::loadFmiLevelId_grib1(const char *filename)
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
          FmiLevelId_grib rec;

          if (field[0][0] != '\0')
            rec.mFmiLevelId = (uint)atoll(field[0]);

          if (field[1][0] != '\0')
            rec.mFmiProducerId = (uint)atoll(field[1]);

          if (field[2][0] != '\0')
            rec.mGeneratingProcessIdentifier = (uint)atoll(field[2]);

          if (field[3][0] != '\0')
            rec.mCentre = (uint)atoll(field[3]);

          if (field[4][0] != '\0')
            rec.mGribLevelId = (uint)atoll(field[4]);

          mFmi_levelsFromGrib1_records.push_back(rec);
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





void GridDef::loadFmiLevelId_grib2(const char *filename)
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
          FmiLevelId_grib rec;

          if (field[0][0] != '\0')
            rec.mFmiLevelId = (uint)atoll(field[0]);

          if (field[1][0] != '\0')
            rec.mFmiProducerId = (uint)atoll(field[1]);

          if (field[2][0] != '\0')
            rec.mGeneratingProcessIdentifier = (uint)atoll(field[2]);

          if (field[3][0] != '\0')
            rec.mCentre = (uint)atoll(field[3]);

          if (field[4][0] != '\0')
            rec.mGribLevelId = (uint)atoll(field[4]);

          mFmi_levelsFromGrib2_records.push_back(rec);
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





void GridDef::loadNewbaseParameterDefinitions(const char *filename)
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
          NewbaseParameterDef rec;

          if (field[0][0] != '\0')
            rec.mNewbaseParameterId = field[0];

          if (field[1][0] != '\0')
            rec.mParameterName = field[1];

          mNewbase_parameterDef_records.push_back(rec);
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





void GridDef::loadFmiProducerId_grib(const char *filename)
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
          FmiProducerId_grib rec;

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


          mFmi_producersFromGrib_records.push_back(rec);
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





bool GridDef::getGridCellAverageSizeByGeometryId(T::GeometryId geometryId,double& width,double& height)
{
  try
  {
    auto g2 = GridDef::getGrib2DefinitionByGeometryId(geometryId);
    if (g2 != NULL)
    {
      g2->getGridCellAverageSize(width,height);
      if (width != 0  &&  height != 0)
        return true;
    }

    auto g1 = GridDef::getGrib1DefinitionByGeometryId(geometryId);
    if (g1 != NULL)
    {
      g1->getGridCellAverageSize(width,height);
      if (width != 0  &&  height != 0)
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::Coordinate_vec GridDef::getGridCoordinatesByGeometryId(T::GeometryId  geometryId)
{
  try
  {
    auto g2 = GridDef::getGrib2DefinitionByGeometryId(geometryId);
    if (g2 != NULL)
      return g2->getGridCoordinates();

    auto g1 = GridDef::getGrib1DefinitionByGeometryId(geometryId);
    if (g1 != NULL)
      return g1->getGridCoordinates();

    T::Coordinate_vec empty;
    return empty;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::Coordinate_vec GridDef::getGridLatLonCoordinatesByGeometryId(T::GeometryId  geometryId)
{
  try
  {
    auto g2 = GridDef::getGrib2DefinitionByGeometryId(geometryId);
    if (g2 != NULL)
    {
      //g2->print(std::cout,0,2);
      return g2->getGridLatLonCoordinates();
    }

    auto g1 = GridDef::getGrib1DefinitionByGeometryId(geometryId);
    if (g1 != NULL)
    {
      //g1->print(std::cout,0,2);
      return g1->getGridLatLonCoordinates();
    }

    printf("*** Coordinates not found by the geometry %u\n",geometryId);
    T::Coordinate_vec empty;
    return empty;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





GRIB1::GridDef_ptr GridDef::getGrib1DefinitionByGeometryId(int geometryId)
{
  FUNCTION_TRACE
  try
  {
    /*
    std::map<uint,GRIB1::GridDef_ptr>::iterator it = mGridDefinitions1.find(geometryId);
    if (it != mGridDefinitions1.end())
      return it->second;
*/
    std::vector<GRIB1::GridDef_ptr>::iterator it;
    for (it=mGridDefinitions1.begin(); it!=mGridDefinitions1.end(); ++it)
    {
      if ((*it)->getGridGeometryId() == geometryId)
        return *it;
    }

    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





GRIB1::GridDef_ptr GridDef::getGrib1DefinitionByHash(T::Hash hash)
{
  FUNCTION_TRACE
  try
  {
    /*
    auto it = mHashAlternatives.find(hash);
    if (it != mHashAlternatives.end())
      hash = it->second;
*/
    for (auto it=mGridDefinitions1.begin(); it!=mGridDefinitions1.end(); ++it)
    {
      if ((*it)->getGridHash() == hash)
        return (*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





GRIB2::GridDef_ptr GridDef::getGrib2DefinitionByGeometryId(int geometryId)
{
  FUNCTION_TRACE
  try
  {
    /*
    std::map<uint,GRIB2::GridDef_ptr>::iterator it = mGridDefinitions2.find(geometryId);
    if (it != mGridDefinitions2.end())
      return it->second;
*/
    std::vector<GRIB2::GridDef_ptr>::iterator it;
    for (it=mGridDefinitions2.begin(); it!=mGridDefinitions2.end(); ++it)
    {
      if ((*it)->getGridGeometryId() == geometryId)
        return *it;
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





int GridDef::getGrib1GeometryIdByHash(T::Hash hash)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getGrib1DefinitionByHash(hash);
    if (def == NULL)
      return 0;

    return def->getGridGeometryId();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}






int GridDef::getGrib2GeometryIdByHash(T::Hash hash)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getGrib2DefinitionByHash(hash);
    if (def == NULL)
      return 0;

    return def->getGridGeometryId();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





GRIB2::GridDef_ptr GridDef::getGrib2DefinitionByHash(T::Hash hash)
{
  FUNCTION_TRACE
  try
  {
    /*
    auto it = mHashAlternatives.find(hash);
    if (it != mHashAlternatives.end())
      hash = it->second;
*/
    for (auto it=mGridDefinitions2.begin(); it!=mGridDefinitions2.end(); ++it)
    {
      if ((*it)->getGridHash() == hash)
        return *it;
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDef::getGeometryNameById(T::GeometryId geometryId,std::string& name)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto *def1 = getGrib1DefinitionByGeometryId(geometryId);
    if (def1)
    {
      name = def1->getGridGeometryName();
      return true;
    }

    auto *def2 = getGrib2DefinitionByGeometryId(geometryId);
    if (def2)
    {
      name = def2->getGridGeometryName();
      return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDef::getGridDirectionsByGeometryId(T::GeometryId  geometryId,bool& reverseXDirection,bool& reverseYDirection)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto *def1 = getGrib1DefinitionByGeometryId(geometryId);
    if (def1)
    {
      reverseXDirection = def1->reverseXDirection();
      reverseYDirection = def1->reverseYDirection();
      return true;
    }

    auto *def2 = getGrib2DefinitionByGeometryId(geometryId);
    if (def2)
    {
      reverseXDirection = def2->reverseXDirection();
      reverseYDirection = def2->reverseYDirection();
      return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::Coordinate_vec GridDef::getGridLatLonCoordinateLinePointsByGeometryId(T::GeometryId  geometryId)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    T::Coordinate_vec coordinates;
    auto *def1 = getGrib1DefinitionByGeometryId(geometryId);
    if (def1)
    {
      for (int lat=-90; lat < 90; lat = lat + 10)
      {
        for (int lon=-1800; lon < 1800; lon++)
        {
          double grid_i = 0;
          double grid_j = 0;
          if (def1->getGridPointByLatLonCoordinates((double)lat,((double)lon)/10,grid_i,grid_j))
          {
            coordinates.push_back(T::Coordinate(grid_i,grid_j));
          }
        }
      }

      for (int lon=-180; lon < 180; lon=lon+10)
      {
        for (int lat=-900; lat < 900; lat++)
        {
          double grid_i = 0;
          double grid_j = 0;
          if (def1->getGridPointByLatLonCoordinates(((double)lat)/10,(double)lon,grid_i,grid_j))
          {
            coordinates.push_back(T::Coordinate(grid_i,grid_j));
          }
        }
      }
      return coordinates;
    }

    auto *def2 = getGrib2DefinitionByGeometryId(geometryId);
    if (def2)
    {
      for (int lat=-90; lat < 90; lat = lat + 10)
      {
        for (int lon=-1800; lon < 1800; lon++)
        {
          double grid_i = 0;
          double grid_j = 0;
          if (def2->getGridPointByLatLonCoordinates((double)lat,((double)lon)/10,grid_i,grid_j))
          {
            coordinates.push_back(T::Coordinate(grid_i,grid_j));
          }
        }
      }

      for (int lon=-180; lon < 180; lon=lon+10)
      {
        for (int lat=-900; lat < 900; lat++)
        {
          double grid_i = 0;
          double grid_j = 0;
          if (def2->getGridPointByLatLonCoordinates(((double)lat)/10,(double)lon,grid_i,grid_j))
          {
            coordinates.push_back(T::Coordinate(grid_i,grid_j));
          }
        }
      }
    }

    return coordinates;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDef::getGridDimensionsByGeometryId(T::GeometryId  geometryId,uint& cols,uint& rows)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto *def1 = getGrib1DefinitionByGeometryId(geometryId);
    if (def1)
    {
      T::Dimensions_opt dim = def1->getGridDimensions();
      if (dim)
      {
        cols = dim->nx();
        rows = dim->ny();
        return true;
      }
    }

    auto *def2 = getGrib2DefinitionByGeometryId(geometryId);
    if (def2)
    {
      T::Dimensions_opt dim = def2->getGridDimensions();
      if (dim)
      {
        cols = dim->nx();
        rows = dim->ny();
        return true;
      }
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDef::getGridLatLonCoordinatesByGeometryId(T::GeometryId  geometryId,T::Coordinate_vec& coordinates)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto *def1 = getGrib1DefinitionByGeometryId(geometryId);
    if (def1)
    {
      coordinates = def1->getGridLatLonCoordinates();
      return true;
    }

    auto *def2 = getGrib2DefinitionByGeometryId(geometryId);
    if (def2)
    {
      coordinates = def2->getGridLatLonCoordinates();
      return true;
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridDef::getGeometryIdListByLatLon(double lat,double lon,std::set<T::GeometryId>& geometryIdList)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    for (auto it=mGridDefinitions1.begin(); it!=mGridDefinitions1.end(); ++it)
    {
      double grid_i = 0;
      double grid_j = 0;

      if ((*it)->getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j))
      {
        T::GeometryId geometryId = (*it)->getGridGeometryId();
        if (geometryIdList.find(geometryId) == geometryIdList.end())
          geometryIdList.insert(geometryId);
      }
    }

    for (auto it=mGridDefinitions2.begin(); it!=mGridDefinitions2.end(); ++it)
    {
      double grid_i = 0;
      double grid_j = 0;

      if ((*it)->getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j))
      {
        T::GeometryId geometryId = (*it)->getGridGeometryId();
        if (geometryIdList.find(geometryId) == geometryIdList.end())
          geometryIdList.insert(geometryId);
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridDef::loadGeometryDefinitions(const char *filename)
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
              int longitude = (int)round(atof(field[5])*1000000);
              int latitude = (int)round(atof(field[6])*1000000);
              int iInc = (int)round(atof(field[7]) * 1000000);
              int jInc = (int)round(atof(field[8]) * 1000000);
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
              def2->initSpatialReference();

              //def2->print(std::cout,0,0);
              //T::Hash hash = def2->countHash();
              //printf("HASH %llu\n",(unsigned long long)hash);
/*
              T::Hash hash1 = def2->countHash();

              if (longitude < 0 || lastLongitude < 0)
              {
                GRIB2::GridSettings gridx;

                gridx.setNi(T::UInt32_opt(ni));
                gridx.setNj(T::UInt32_opt(nj));

                if (longitude < 0)
                  gridx.setLongitudeOfFirstGridPoint(T::Int32_opt(longitude+360000000));
                else
                  gridx.setLongitudeOfFirstGridPoint(T::Int32_opt(longitude));

                gridx.setLatitudeOfFirstGridPoint(T::Int32_opt(latitude));
                gridx.setLongitudeOfLastGridPoint(T::Int32_opt(lastLongitude));

                if (lastLongitude < 0)
                  gridx.setLatitudeOfLastGridPoint(T::Int32_opt(lastLatitude+360000000));
                else
                  gridx.setLatitudeOfLastGridPoint(T::Int32_opt(lastLatitude));

                latLon.setGrid(gridx);
                def2->setLatLon(latLon);

                T::Hash hash2 = def2->countHash();
                def2->print(std::cout,0,0);
                printf("** ALT %llu => %llu\n",(unsigned long long)hash2,(unsigned long long)hash1);

                mHashAlternatives.insert(std::pair<T::Hash,T::Hash>(hash2,hash1));

                latLon.setGrid(grid);
                def2->setLatLon(latLon);
              }
*/
              mGridDefinitions2.push_back(def2);

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
              def1->initSpatialReference();

              //def1->print(std::cout,0,0);
              //T::Hash hash = def1->getGridHash();
              //printf("HASH %llu\n",(unsigned long long)hash);

              mGridDefinitions1.push_back(def1);
            }
            break;

            case T::GridProjection::RotatedLatLon:
            {
              uint geometryId = (uint)atoll(field[1]);
              char *geometryName = field[2];
              int ni = atoll(field[3]);
              int nj = atoll(field[4]);
              int longitude = (int)round(atof(field[5])*1000000);
              int latitude = (int)round(atof(field[6])*1000000);
              int iInc = (int)round(atof(field[7]) * 1000000);
              int jInc = (int)round(atof(field[8]) * 1000000);
              char *scanningMode = field[9];
              int longitudeOfSouthernPole = (int)round(atof(field[10])*1000000);
              int latitudeOfSouthernPole = (int)round(atof(field[11])*1000000);
              int lastLongitude = longitude + ni*iInc - iInc;
              int lastLatitude = latitude + nj*jInc - jInc;
              int angle = round(atof(field[12]));
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
              rotation2.setAngleOfRotation(angle);
              def2->setRotation(rotation2);

              def2->setGridGeometryId(geometryId);
              def2->setGridGeometryName(geometryName);
              def2->initSpatialReference();

              //def2->print(std::cout,0,0);
              //T::Hash hash = def2->getGridHash();
              //printf("HASH %llu\n",(unsigned long long)hash);

              mGridDefinitions2.push_back(def2);

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
              rotation1.setGeography_angleOfRotationInDegrees(angle);
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
              def1->initSpatialReference();

              // def1->print(std::cout,0,0);
              // T::Hash hash = def1->getGridHash();
              // printf("HASH %llu\n",(unsigned long long)hash);

              mGridDefinitions1.push_back(def1);
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
            {
              uint geometryId = (uint)atoll(field[1]);
              char *geometryName = field[2];
              int ni = atoll(field[3]);
              int nj = atoll(field[4]);
              int longitude = (int)round(atof(field[5])*1000000);
              int latitude = (int)round(atof(field[6])*1000000);
              int iInc = (int)round(atof(field[7]) * 1000);
              int jInc = (int)round(atof(field[8]) * 1000);
              char *scanningMode = field[9];
              int orientation = (int)round(atof(field[10])*1000000);
              int laD = (int)round(atof(field[11]) * 1000000);

              // ******* GRIB 2 ********
//#if 0
              GRIB2::PolarStereographicImpl *def2 = new GRIB2::PolarStereographicImpl();
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

              def2->setLaD(laD);
              def2->setOrientationOfTheGrid(orientation);
              def2->setDx(T::UInt32_opt(iInc));
              def2->setDy(T::UInt32_opt(jInc));
              //def2->setProjectionCentreFlag(std::uint8_t projectionCentreFlag);
              //def2->setLatin1(T::Int32_opt(latin1));
              //def2->setLatin2(T::Int32_opt(latin2));
              ////def2->setLatitudeOfSouthernPole(T::Int32_opt(latitudeOfSouthernPole));
              //def2->setLongitudeOfSouthernPole(T::UInt32_opt(longitudeOfSouthernPole));

              def2->setGridGeometryId(geometryId);
              def2->setGridGeometryName(geometryName);
              def2->initSpatialReference();

              //def2->print(std::cout,0,0);
              //T::Hash hash = def2->getGridHash();
              //printf("HASH %llu\n",(unsigned long long)hash);

              mGridDefinitions2.push_back(def2);
              //mGridDefinitions2.insert(std::pair<uint,GRIB2::GridDef_ptr>(geometryId,def2));
//#endif

              // ******* GRIB 1 ********

              GRIB1::PolarStereographicImpl *def1 = new GRIB1::PolarStereographicImpl();
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
              //def1->setLoV(orientation/1000);
              def1->setOrientationOfTheGrid(orientation/1000);
              def1->setDxInMetres((std::uint24_t)(iInc)/1000);
              def1->setDyInMetres((std::uint24_t)(jInc)/1000);
              //def1->setProjectionCentreFlag(std::uint8_t projectionCentreFlag);
              //def1->setLatin1((std::int24_t)latin1/1000);
              //def1->setLatin2((std::int24_t)latin2/1000);
              //def1->setLatitudeOfSouthernPole((std::int24_t)latitudeOfSouthernPole/1000);
              //def1->setLongitudeOfSouthernPole((std::int24_t)longitudeOfSouthernPole/1000);

              def1->setGridGeometryId(geometryId);
              def1->setGridGeometryName(geometryName);
              def1->initSpatialReference();

              //printf("*** GEOMETRY : %d\n",geometryId);
              //def1->print(std::cout,0,0);
              //std::size_t hash = def1->getGridHash();
              //printf("HASH %llu\n",(unsigned long long)hash);

              mGridDefinitions1.push_back(def1);
            }
            break;

            case T::GridProjection::LambertConformal:
            {
              uint geometryId = (uint)atoll(field[1]);
              char *geometryName = field[2];
              int ni = atoll(field[3]);
              int nj = atoll(field[4]);
              int longitude = (int)round(atof(field[5])*1000000);
              int latitude = (int)round(atof(field[6])*1000000);
              int iInc = (int)(atoll(field[7]));
              int jInc = (int)(atoll(field[8]));
              char *scanningMode = field[9];
              int orientation = (int)round(atof(field[10])*1000000);
              int latin1 = (int)round(atof(field[11])*1000000);
              int latin2 = (int)round(atof(field[12])*1000000);
              int longitudeOfSouthernPole = (int)round(atof(field[13])*1000000);
              int latitudeOfSouthernPole = (int)round(atof(field[14])*1000000);

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

              def2->setLaD(latin1);
              def2->setLoV(orientation);
              def2->setDx(T::UInt32_opt(iInc*1000));
              def2->setDy(T::UInt32_opt(jInc*1000));
              //def2->setProjectionCentreFlag(std::uint8_t projectionCentreFlag);
              def2->setLatin1(T::Int32_opt(latin1));
              def2->setLatin2(T::Int32_opt(latin2));
              def2->setLatitudeOfSouthernPole(T::Int32_opt(latitudeOfSouthernPole));
              def2->setLongitudeOfSouthernPole(T::UInt32_opt(longitudeOfSouthernPole));

              def2->setGridGeometryId(geometryId);
              def2->setGridGeometryName(geometryName);
              def2->initSpatialReference();

              //def2->print(std::cout,0,0);
              //T::Hash hash = def2->getGridHash();
              //printf("HASH %llu\n",(unsigned long long)hash);

              mGridDefinitions2.push_back(def2);

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
              def1->setLoV(orientation/1000);
              def1->setDxInMetres((std::uint24_t)iInc);
              def1->setDyInMetres((std::uint24_t)jInc);
              //def1->setProjectionCentreFlag(std::uint8_t projectionCentreFlag);
              def1->setLatin1((std::int24_t)latin1/1000);
              def1->setLatin2((std::int24_t)latin2/1000);
              def1->setLatitudeOfSouthernPole((std::int24_t)latitudeOfSouthernPole/1000);
              def1->setLongitudeOfSouthernPole((std::int24_t)longitudeOfSouthernPole/1000);

              def1->setGridGeometryId(geometryId);
              def1->setGridGeometryName(geometryName);
              def1->initSpatialReference();

              //def1->print(std::cout,0,0);
              //std::size_t hash = def1->getGridHash();
              //printf("HASH %llu\n",(unsigned long long)hash);

              mGridDefinitions1.push_back(def1);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





short GridDef::getPreferredInterpolationMethodByUnits(std::string originalUnits)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    for (auto it = mGrib_unitDef_records.begin(); it != mGrib_unitDef_records.end(); ++it)
    {
      if (it->mOriginalUnits == originalUnits)
        return it->mPreferredAreaInterpolationMethod;
    }

    return T::AreaInterpolationMethod::Linear;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getPreferredUnits(std::string originalUnits)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    for (auto it = mGrib_unitDef_records.begin(); it != mGrib_unitDef_records.end(); ++it)
    {
      if (it->mOriginalUnits == originalUnits)
        return it->mPreferredUnits;
    }

    return originalUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





GribParamDef_cptr GridDef::getGribParameterDefById(T::ParamId gribParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGrib_parameterDef_records.begin(); it != mGrib_parameterDef_records.end(); ++it)
    {
      if (strcasecmp(it->mGribParameterId.c_str(),gribParamId.c_str()) == 0)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamId GridDef::getGribParameterId(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    const GRIB1::ProductSection *productSection =  message.getProductSection();
    if (productSection == NULL)
      return std::string("");

    uint maxPoints = 1;
    T::ParamId parameterId;

    for (auto p = mGrib1_parameterDef_records.begin(); p != mGrib1_parameterDef_records.end(); ++p)
    {
      uint requiredPoints = 0;
      uint points = 0;

      if (p->mCentre)
      {
        requiredPoints++;
        if (p->mCentre == productSection->getCentre())
          points++;
      }

      if (p->mIndicatorOfParameter)
      {
        requiredPoints++;
        if (p->mIndicatorOfParameter == productSection->getIndicatorOfParameter())
          points++;
      }

      if (p->mIndicatorOfTypeOfLevel)
      {
        requiredPoints++;
        if (p->mIndicatorOfTypeOfLevel == productSection->getIndicatorOfTypeOfLevel())
          points++;
      }

      if (p->mTable2Version)
      {
        requiredPoints++;
        if (p->mTable2Version == productSection->getTableVersion())
          points++;
      }

      if (p->mParameterLevel)
      {
        if (p->mParameterLevel == productSection->getLevel())
          points++;
      }

      if (points >= requiredPoints  &&  points > maxPoints)
      {
         maxPoints = points;
         parameterId = p->mGribParameterId;
      }
    }
    return parameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamId GridDef::getGribParameterId(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    T::ParamId paramId;

    GRIB2::IndicatorSection_sptr indicatorSection = message.getIndicatorSection();
    if (!indicatorSection)
      return paramId;

    if (mGrib2_parameterDef_records.size() == 0)
      return paramId;

    // We have to go through all parameters and try to find the best match.

    uint maxMatchPoints = 0;

    for (auto p = mGrib2_parameterDef_records.begin(); p != mGrib2_parameterDef_records.end(); ++p)
    {
      if (p->mDiscipline == indicatorSection->getDiscipline())
      {
         uint matchPoints = countParameterMatchPoints(message,*p);
         if (matchPoints > maxMatchPoints)
         {
           maxMatchPoints = matchPoints;
           paramId = p->mGribParameterId;
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





T::ParamLevelId GridDef::getGrib1LevelId(GRIB1::Message& message)
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





T::ParamLevelId GridDef::getGrib2LevelId(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    T::ParamLevelId fmiLevelId = getFmiLevelId(message);
    if (fmiLevelId != 0)
    {
      for (auto it = mFmi_levelsFromGrib2_records.begin(); it != mFmi_levelsFromGrib2_records.end(); ++it)
      {
        if (it->mFmiLevelId == fmiLevelId)
        {
          return (T::ParamLevelId)it->mGribLevelId;
        }
      }
    }

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamLevelId GridDef::getGrib1LevelId(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    T::ParamLevelId fmiLevelId = getFmiLevelId(message);
    if (fmiLevelId != 0)
    {
      for (auto it = mFmi_levelsFromGrib1_records.begin(); it != mFmi_levelsFromGrib1_records.end(); ++it)
      {
        if (it->mFmiLevelId == fmiLevelId)
        {
          return (T::ParamLevelId)it->mGribLevelId;
        }
      }
    }

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamLevelId GridDef::getGrib2LevelId(GRIB2::Message& message)
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





std::string GridDef::getGribParameterName(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    auto p = getGribParameterDefById(message.getGribParameterId());
    if (p)
      return p->mParameterName;

    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getGribParameterName(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    auto p = getGribParameterDefById(message.getGribParameterId());
    if (p)
      return p->mParameterName;

    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getGribParameterDescription(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    auto p = getGribParameterDefById(message.getGribParameterId());
    if (p)
      return p->mParameterDescription;

    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getGribParameterDescription(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    auto p = getGribParameterDefById(message.getGribParameterId());
    if (p)
      return p->mParameterDescription;

    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getGribParameterUnits(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    auto p = getGribParameterDefById(message.getGribParameterId());
    if (p)
      return p->mParameterUnits;

    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getGribParameterUnits(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    auto p = getGribParameterDefById(message.getGribParameterId());
    if (p)
      return p->mParameterUnits;

    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint GridDef::countParameterMatchPoints(GRIB2::Message& message,const Grib2ParameterDef& p)
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





T::ParamId GridDef::getFmiParameterId(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const GRIB1::ProductSection *productSection =  message.getProductSection();
    if (productSection == NULL)
      return std::string("");

    uint maxPoints = 1;
    T::ParamId parameterId;

    for (auto p = mFmi_parametersFromGrib1_records.begin(); p != mFmi_parametersFromGrib1_records.end(); ++p)
    {
      uint requiredPoints = 0;
      uint points = 0;

      requiredPoints++;
      if (p->mGeneratingProcessIdentifier == productSection->getGeneratingProcessIdentifier())
        points++;

      requiredPoints++;
      if (p->mCentre == productSection->getCentre())
        points++;

      requiredPoints++;
      if (p->mGribTableVersion == productSection->getTableVersion())
        points++;

      requiredPoints++;
      if (p->mGribParameterNumber == productSection->getIndicatorOfParameter())
        points++;

      requiredPoints++;
      if (p->mGribTimerangeIndicator == productSection->getTimeRangeIndicator())
        points++;

      if (p->mGribParameterLevelId  &&  *p->mGribParameterLevelId != 0)
      {
        requiredPoints++;
        if (*p->mGribParameterLevelId == productSection->getIndicatorOfTypeOfLevel())
          points++;
      }

      if (p->mParameterLevel)
      {
        requiredPoints++;
        if (*p->mParameterLevel == productSection->getLevel())
          points++;
      }

       //p.print(std::cout,0,0);
       //printf("POINT %s %u %u\n",p.mFmiParameterId.c_str(),points,requiredPoints);

      if (points >= requiredPoints  &&  points > maxPoints)
      {
         maxPoints = points;
         parameterId = p->mFmiParameterId;
      }
    }

    return parameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamId GridDef::getFmiParameterId(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    GRIB2::IndicatorSection_sptr indicatorSection = message.getIndicatorSection();
    if (!indicatorSection)
      return std::string("");

    std::size_t parameterCount = mGrib2_parameterDef_records.size();
    if (parameterCount == 0)
      return std::string("");

    T::ParamId paramId;

    // We have to go through all parameters and try to find the best match.

    uint maxMatchPoints = 0;

    for (auto p = mFmi_parametersFromGrib2_records.begin(); p != mFmi_parametersFromGrib2_records.end(); ++p)
    {
      if (p->mDiscipline == indicatorSection->getDiscipline())
      {
         uint matchPoints = countParameterMatchPoints(message,*p);
         if (matchPoints > maxMatchPoints)
         {
           maxMatchPoints = matchPoints;
           paramId = p->mFmiParameterId;
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





uint GridDef::countParameterMatchPoints(GRIB2::Message& message,const FmiParameterId_grib2& p)
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
      //else
      //  return 0;
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





T::ParamLevelId GridDef::getFmiLevelId(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    const GRIB1::ProductSection *productSection =  message.getProductSection();
    if (productSection == NULL)
      return 0;

    for (auto it = mFmi_levelsFromGrib1_records.begin(); it != mFmi_levelsFromGrib1_records.end(); ++it)
    {
      if (it->mGeneratingProcessIdentifier == productSection->getGeneratingProcessIdentifier() &&
          it->mCentre == productSection->getCentre() &&
          it->mGribLevelId == productSection->getIndicatorOfTypeOfLevel())
      {
        return (T::ParamLevelId)it->mFmiLevelId;
      }
    }

    for (auto it = mFmi_levelsFromGrib1_records.begin(); it != mFmi_levelsFromGrib1_records.end(); ++it)
    {
      if (it->mGribLevelId == productSection->getIndicatorOfTypeOfLevel())
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





T::ParamLevelId GridDef::getFmiLevelId(GRIB2::Message& message)
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

    for (auto it = mFmi_levelsFromGrib2_records.begin(); it != mFmi_levelsFromGrib2_records.end(); ++it)
    {
      if (it->mGeneratingProcessIdentifier == *productSection->getGeneratingProcessIdentifier() &&
          it->mCentre == identificationSection->getCentre() &&
          it->mGribLevelId == message.getGridParameterLevelId())
      {
        return (T::ParamLevelId)it->mFmiLevelId;
      }
    }

    for (auto it = mFmi_levelsFromGrib2_records.begin(); it != mFmi_levelsFromGrib2_records.end(); ++it)
    {
      if (it->mGribLevelId == message.getGridParameterLevelId())
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





T::ParamId GridDef::getFmiParameterIdByFmiName(std::string fmiParamName)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getFmiParameterDefByName(fmiParamName);
    if (p != NULL)
      return p->mFmiParameterId;

    return std::string("");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





FmiParamDef_cptr GridDef::getFmiParameterDefById(T::ParamId fmiParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_parameterDef_records.begin(); it != mFmi_parameterDef_records.end(); ++it)
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






FmiParamId_newbase_cptr GridDef::getFmiParameterIdByNewbaseId(T::ParamId newbaseParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_parametersFromNewbase_records.begin(); it != mFmi_parametersFromNewbase_records.end(); ++it)
    {
      if (strcasecmp(it->mNewbaseParameterId.c_str(),newbaseParamId.c_str()) == 0)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}






FmiParamId_newbase_cptr GridDef::getNewbaseParameterIdByFmiId(T::ParamId fmiParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_parametersFromNewbase_records.begin(); it != mFmi_parametersFromNewbase_records.end(); ++it)
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





bool GridDef::getNewbaseParameterDefByFmiId(T::ParamId fmiParamId,NewbaseParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    auto p = getNewbaseParameterIdByFmiId(fmiParamId);
    if (p == NULL)
      return false;

    auto n = getNewbaseParameterDefById(p->mNewbaseParameterId);
    if (n == NULL)
      return false;

    paramDef = *n;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDef::getNewbaseParameterMappingByFmiId(T::ParamId fmiParamId,FmiParameterId_newbase& paramMapping)
{
  try
  {
    FmiParamId_newbase_cptr p = getNewbaseParameterIdByFmiId(fmiParamId);
    if (p != NULL)
    {
      paramMapping = *p;
      return true;
    }
    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDef::getNewbaseParameterDefById(T::ParamId newbaseParamId,NewbaseParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    auto n = getNewbaseParameterDefById(newbaseParamId);
    if (n == NULL)
      return false;

    paramDef = *n;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}






FmiParamDef_cptr GridDef::getFmiParameterDefByNewbaseId(T::ParamId newbaseParamId)
{
  FUNCTION_TRACE
  try
  {
    auto p = getFmiParameterIdByNewbaseId(newbaseParamId);
    if (p)
      return getFmiParameterDefById(p->mFmiParameterId);

    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





FmiParamDef_cptr GridDef::getFmiParameterDefByName(std::string fmiParamName)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_parameterDef_records.begin(); it != mFmi_parameterDef_records.end(); ++it)
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





bool GridDef::getFmiParameterDefById(T::ParamId fmiParamId,FmiParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getFmiParameterDefById(fmiParamId);
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





bool GridDef::getFmiParameterDefByNewbaseId(T::ParamId newbaseParamId,FmiParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getFmiParameterDefByNewbaseId(newbaseParamId);
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





bool GridDef::getFmiParameterDefByName(std::string fmiParamName,FmiParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto def = getFmiParameterDefByName(fmiParamName);
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





std::string GridDef::getFmiParameterName(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getFmiParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getFmiParameterName(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getFmiParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getFmiParameterDescription(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getFmiParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getFmiParameterDescription(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getFmiParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getFmiParameterUnits(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getFmiParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getFmiParameterUnits(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getFmiParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    return p->mParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





short GridDef::getFmiParameterInterpolationMethod(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getFmiParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return T::AreaInterpolationMethod::None;

    return p->mAreaInterpolationMethod;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





short GridDef::getFmiParameterInterpolationMethod(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getFmiParameterDefById(message.getFmiParameterId());
    if (p == NULL)
      return T::AreaInterpolationMethod::None;

    return p->mAreaInterpolationMethod;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





FmiProducerId_grib_cptr GridDef::getFmiProducerByName(std::string fmiProducerName)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_producersFromGrib_records.begin(); it != mFmi_producersFromGrib_records.end(); ++it)
    {
      if (strcasecmp(it->mProducerName.c_str(),fmiProducerName.c_str()) == 0)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDef::getFmiProducerByName(std::string fmiProducerName,FmiProducerId_grib& producer)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getFmiProducerByName(fmiProducerName);
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





NewbaseParamDef_cptr GridDef::getNewbaseParameterDefById(T::ParamId newbaseParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mNewbase_parameterDef_records.begin(); it != mNewbase_parameterDef_records.end(); ++it)
    {
      if (strcasecmp(it->mNewbaseParameterId.c_str(),newbaseParamId.c_str()) == 0)
        return &(*it);
    }
    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





NewbaseParamDef_cptr GridDef::getNewbaseParameterDefByName(std::string newbaseParamName)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mNewbase_parameterDef_records.begin(); it != mNewbase_parameterDef_records.end(); ++it)
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





T::ParamId GridDef::getNewbaseParameterId(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getNewbaseParameterIdByFmiId(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    return p->mNewbaseParameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamId GridDef::getNewbaseParameterId(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getNewbaseParameterIdByFmiId(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    return p->mNewbaseParameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getNewbaseParameterName(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getNewbaseParameterIdByFmiId(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    auto n = getNewbaseParameterDefById(p->mNewbaseParameterId);
    if (n == NULL)
      return std::string("");

    return n->mParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getNewbaseParameterName(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoThreadLock lock(&mThreadLock);

    auto p = getNewbaseParameterIdByFmiId(message.getFmiParameterId());
    if (p == NULL)
      return std::string("");

    auto n = getNewbaseParameterDefById(p->mNewbaseParameterId);
    if (n == NULL)
      return std::string("");

    return n->mParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string GridDef::getCdmParameterId(GRIB1::Message& message)
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
    if (getGrib1TimeRangeDef(productSection->getUnitOfTimeRange(),timeRangeDef))
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





std::string GridDef::getCdmParameterId(GRIB2::Message& message)
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
    if (getGrib2LevelDef(message.getGridParameterLevelId(),levelDef))
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
        if (getGrib2TimeRangeDef(*stat->getIndicatorOfUnitForTimeRange(),timeRangeDef))
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





std::string GridDef::getCdmParameterName(GRIB1::Message& message)
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

    Grib1ParameterDef param;
    if (getGrib1ParameterDefByTable(productSection->getTableVersion(),productSection->getIndicatorOfParameter(),param))
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
      if (getGrib1LevelDef(productSection->getIndicatorOfTypeOfLevel(),levelDef))
      {
        if (levelDef.mName.length() > 0)
        {
          p += sprintf(p,"_%s",levelDef.mName.c_str());
          //p += sprintf(p,"_%u",productSection->getLevel());
        }
      }

      TimeRangeDef timeRangeDef;
      if (getGrib1TimeRangeDef(productSection->getUnitOfTimeRange(),timeRangeDef))
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





std::string GridDef::getCdmParameterName(GRIB2::Message& message)
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

    GribParameterDef def;
    if (getGribParamDef(indicatorSection->getDiscipline(),*productSection->getGribParameterCategory(),*productSection->getGribParameterNumber(),def)
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
    if (getGrib2LevelDef(message.getGridParameterLevelId(),levelDef))
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
        if (getGrib2TimeRangeDef(*stat->getIndicatorOfUnitForTimeRange(),timeRangeDef))
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




}  // namespace GRIB2
}  // namespace SmartMet