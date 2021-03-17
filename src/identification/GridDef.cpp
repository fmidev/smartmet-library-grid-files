#include "GridDef.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"
#include "../common/ShowFunction.h"
#include "../common/CoordinateConversions.h"

#include "../grib1/implementation/LatLonImpl.h"
#include "../grib1/implementation/MercatorImpl.h"
#include "../grib1/implementation/LambertConformalImpl.h"
#include "../grib1/implementation/GaussianImpl.h"
#include "../grib1/implementation/PolarStereographicImpl.h"
#include "../grib1/implementation/AlbersImpl.h"
#include "../grib1/implementation/RotatedLatLonImpl.h"
#include "../grib1/implementation/ObliqueLambertConformalImpl.h"
#include "../grib1/implementation/RotatedGaussianImpl.h"
#include "../grib1/implementation/StretchedLatLonImpl.h"
#include "../grib1/implementation/StretchedGaussianImpl.h"
#include "../grib1/implementation/StretchedRotatedLatLonImpl.h"
#include "../grib1/implementation/StretchedRotatedGaussianImpl.h"
#include "../grib1/implementation/SphericalHarmonicImpl.h"
#include "../grib1/implementation/RotatedSphericalHarmonicImpl.h"
#include "../grib1/implementation/StretchedSphericalHarmonicImpl.h"
#include "../grib1/implementation/StretchedRotatedSphericalHarmonicImpl.h"
#include "../grib1/implementation/SpaceViewImpl.h"

#include "../grib2/implementation/LatLonImpl.h"                             //  "3.0"
#include "../grib2/implementation/RotatedLatLonImpl.h"                      //  "3.1"
#include "../grib2/implementation/StretchedLatLonImpl.h"                    //  "3.2"
#include "../grib2/implementation/StretchedRotatedLatLonImpl.h"             //  "3.3"
#include "../grib2/implementation/VariableResolutionLatLonImpl.h"           //  "3.4"
#include "../grib2/implementation/VariableResolutionRotatedLatLonImpl.h"    //  "3.5"
#include "../grib2/implementation/MercatorImpl.h"                           //  "3.10"
#include "../grib2/implementation/TransverseMercatorImpl.h"                 //  "3.12"
#include "../grib2/implementation/PolarStereographicImpl.h"                 //  "3.20"
#include "../grib2/implementation/LambertConformalImpl.h"                   //  "3.30"
#include "../grib2/implementation/AlbersImpl.h"                             //  "3.31"
#include "../grib2/implementation/GaussianImpl.h"                           //  "3.40"
#include "../grib2/implementation/RotatedGaussianImpl.h"                    //  "3.41"
#include "../grib2/implementation/StretchedGaussianImpl.h"                  //  "3.42"
#include "../grib2/implementation/StretchedRotatedGaussianImpl.h"           //  "3.43"
#include "../grib2/implementation/SphericalHarmonicImpl.h"                  //  "3.50"
#include "../grib2/implementation/RotatedSphericalHarmonicImpl.h"           //  "3.51"
#include "../grib2/implementation/StretchedSphericalHarmonicImpl.h"         //  "3.52"
#include "../grib2/implementation/StretchedRotatedSphericalHarmonicImpl.h"  //  "3.53"
#include "../grib2/implementation/SpaceViewImpl.h"                          //  "3.90"
#include "../grib2/implementation/TriangularImpl.h"                         //  "3.100"
#include "../grib2/implementation/UnstructuredImpl.h"                       //  "3.101"
#include "../grib2/implementation/EquatorialAzimuthalEquidistantImpl.h"     //  "3.110"
#include "../grib2/implementation/AzimuthRangeImpl.h"                       //  "3.120"
#include "../grib2/implementation/IrregularLatLonImpl.h"                    //  "3.130"
#include "../grib2/implementation/LambertAzimuthalEqualAreaImpl.h"          //  "3.140"
#include "../grib2/implementation/CrossSectionImpl.h"                       //  "3.1000"
#include "../grib2/implementation/HovmollerImpl.h"                          //  "3.1100"
#include "../grib2/implementation/TimeSectionImpl.h"                        //  "3.1200"

#include <macgyver/StringConversion.h>

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
    mFmi_parametersFromGrib_modificationTime = 0;
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

GridDef::~GridDef()
{
  FUNCTION_TRACE
  try
  {
    /*
    for (auto it=mGridDefinitions1.begin(); it!=mGridDefinitions1.end(); ++it)
    {
      delete (it->second);
    }

    for (auto it=mGridDefinitions2.begin(); it!=mGridDefinitions2.end(); ++it)
    {
      delete (it->second);
    }
    */
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
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
      "smartmet.library.grid-files.fmi.forecastTypeDef[]",
      "smartmet.library.grid-files.fmi.geometryDef[]",
      "smartmet.library.grid-files.fmi.parametersFromGrib[]",
      "smartmet.library.grid-files.fmi.parametersFromGrib1[]",
      "smartmet.library.grid-files.fmi.parametersFromGrib2[]",
      "smartmet.library.grid-files.fmi.parametersFromNewbase[]",
      "smartmet.library.grid-files.fmi.levelsFromGrib1[]",
      "smartmet.library.grid-files.fmi.levelsFromGrib2[]",
      "smartmet.library.grid-files.fmi.producersFromGrib[]",
      "smartmet.library.grid-files.newbase.parameterDef[]",
       nullptr
    };

    if (mInitialized)
      return;

    mConfigFileName = configFile;
    mConfigurationFile.readFile(configFile);

    uint t=0;
    while (configAttribute[t] != nullptr)
    {
      if (!mConfigurationFile.findAttribute(configAttribute[t]))
      {
        Fmi::Exception exception(BCP, "Missing configuration attribute!");
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
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.fmi.forecastTypeDef",mFmi_forecastTypeDef_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.fmi.geometryDef",mFmi_geometryDef_files);
    mConfigurationFile.getAttributeValue("smartmet.library.grid-files.fmi.parametersFromGrib",mFmi_parametersFromGrib_files);
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
    Fmi::Exception exception(BCP,"Initialization failed!",nullptr);
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
      throw Fmi::Exception(BCP,"The 'GridDef' object is not initialized! Call init() first!");

    if ((mLastCheckTime + 60) < time(nullptr))
    {
      AutoWriteLock lock(&mModificationLock);
      if ((mLastCheckTime + 60) < time(nullptr))
      {
        mLastCheckTime = time(nullptr);
        updateGrib();
        updateGrib1();
        updateGrib2();
        updateFmi();
        updateNewbase();
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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

    tt = getModificationTime(mFmi_forecastTypeDef_files);
    if (tt != mFmi_forecastTypeDef_modificationTime)
    {
      mFmi_forecastTypeDef_records.clear();
      for (auto it = mFmi_forecastTypeDef_files.begin(); it != mFmi_forecastTypeDef_files.end(); ++it)
      {
        loadFmiForecastTypeDefinitions(it->c_str());
      }
      mFmi_forecastTypeDef_modificationTime = tt;
    }


    tt = getModificationTime(mFmi_parametersFromGrib_files);
    if (tt != mFmi_parametersFromGrib_modificationTime)
    {
      mFmi_parametersFromGrib_records.clear();
      for (auto it = mFmi_parametersFromGrib_files.begin(); it != mFmi_parametersFromGrib_files.end(); ++it)
      {
        loadFmiParameterId_grib(it->c_str());
      }
      mFmi_parametersFromGrib_modificationTime = tt;
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
      for (auto it = mGridDefinitions1.begin(); it != mGridDefinitions1.end(); ++it)
        delete (it->second);

      for (auto it = mGridDefinitions2.begin(); it != mGridDefinitions2.end(); ++it)
        delete (it->second);

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDef::getGribTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,const std::string& table,std::uint32_t number)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    for (auto it = mGrib_tableDef_records.begin(); it != mGrib_tableDef_records.end(); ++it)
    {
      if (it->mGribVersion == gribVersion  &&  it->mTableVersion == tableVersion  &&  it->mTable == table  &&  it->mNumber == number)
        return it->mValue;
    }
    return Fmi::to_string(number);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDef::getGribTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,const std::string& table,T::UInt8_opt number)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDef::getGribTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,const std::string& table,T::UInt16_opt number)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint GridDef::getGrib1ParameterDefCount()
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    return mGrib1_parameterDef_records.size();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGrib1ParameterDefById(T::ParamId gribParamId,Grib1ParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getGrib1ParameterDefById(gribParamId);
    if (def == nullptr)
      return false;

    paramDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGrib1ParameterDefByIndex(uint index,Grib1ParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    if (index >= C_UINT(mGrib1_parameterDef_records.size()))
      return false;

    paramDef = mGrib1_parameterDef_records[index];
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGrib1ParameterDefByName(const std::string& gribParamName,Grib1ParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getGrib1ParameterDefByName(gribParamName);
    if (def == nullptr)
      return false;

    paramDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGrib1ParameterDefByTable(uint tableVersion,uint indicatorOfParameter,Grib1ParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getGrib1ParameterDefByTable(tableVersion,indicatorOfParameter);
    if (def == nullptr)
      return false;

    paramDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGrib1DefByFmiId(T::ParamId fmiParamId,FmiParameterId_grib1& def)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto pdef =  getGrib1DefByFmiId(fmiParamId);
    if (pdef == nullptr)
      return false;

    def = *pdef;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





Grib1ParamDef_cptr GridDef::getGrib1ParameterDefByName(const std::string& gribParamName)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGrib1_parameterDef_records.begin(); it != mGrib1_parameterDef_records.end(); ++it)
    {
      if (strcasecmp(it->mParameterName.c_str(),gribParamName.c_str()) == 0)
        return &(*it);
    }
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint GridDef::getGrib2ParameterDefCount()
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    return mGrib2_parameterDef_records.size();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGrib2ParameterDefById(T::ParamId gribParamId,Grib2ParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getGrib2ParameterDefById(gribParamId);
    if (def == nullptr)
      return false;

    paramDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGribDefByFmiId(T::ParamId fmiParamId,FmiParameterId_grib& def)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto pdef =  getGribDefByFmiId(fmiParamId);
    if (pdef == nullptr)
      return false;

    def = *pdef;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGrib2DefByFmiId(T::ParamId fmiParamId,FmiParameterId_grib2& def)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto pdef =  getGrib2DefByFmiId(fmiParamId);
    if (pdef == nullptr)
      return false;

    def = *pdef;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGrib2ParameterDefByIndex(uint index,Grib2ParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    if (index >= C_UINT(mGrib2_parameterDef_records.size()))
      return false;

    paramDef = mGrib2_parameterDef_records[index];
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGrib2ParameterDefByName(const std::string& gribParamName,Grib2ParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getGrib2ParameterDefByName(gribParamName);
    if (def == nullptr)
      return false;

    paramDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





Grib2ParamDef_cptr GridDef::getGrib2ParameterDefByName(const std::string& gribParamName)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGrib2_parameterDef_records.begin(); it != mGrib2_parameterDef_records.end(); ++it)
    {
      if (strcasecmp(it->mParameterName.c_str(),gribParamName.c_str()) == 0)
        return &(*it);
    }
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadGribTableValues(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
            rec.mGribVersion = toUInt8(field[0]);

          if (field[1][0] != '\0')
            rec.mTableVersion = toUInt8(field[1]);

          if (field[2][0] != '\0')
            rec.mTable = field[2];

          if (field[3][0] != '\0')
            rec.mNumber = toUInt32(field[3]);

          if (field[4][0] != '\0')
            rec.mName = field[4];

          if (field[5][0] != '\0')
            rec.mValue = field[5];

          mGrib_tableDef_records.emplace_back(rec);
        }
      }

    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadGribParameterDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
            rec.mDiscipline = toUInt32(field[1]);

          if (field[2][0] != '\0')
            rec.mParameterCategory = toUInt32(field[2]);

          if (field[3][0] != '\0')
            rec.mParameterNumber = toUInt32(field[3]);

          rec.mParameterName = field[4];
          rec.mParameterDescription = field[5];
          rec.mParameterUnits = field[6];

          mGrib_parameterDef_records.emplace_back(rec);
        }
      }

    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGribParamDefById(T::ParamId gribParamId,GribParameterDef&  paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getGribParamDefById(gribParamId);
    if (def == nullptr)
      return false;

    paramDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGribParamDefByName(const std::string& gribParamName,GribParameterDef&  paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getGribParamDefByName(gribParamName);
    if (def == nullptr)
      return false;

    paramDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGribParamDef(uint discipline,uint category,uint number,GribParameterDef&  paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getGribParamDef(discipline,category,number);
    if (def == nullptr)
      return false;

    paramDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





GribParamDef_cptr GridDef::getGribParamDefByName(const std::string& gribParamName)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGrib_parameterDef_records.begin(); it != mGrib_parameterDef_records.end(); ++it)
    {
      if (strcasecmp(it->mParameterName.c_str(),gribParamName.c_str()) == 0)
        return &(*it);
    }
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getFmiLevelDef(uint levelId,LevelDef& levelDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getFmiLevelDef(levelId);
    if (def == nullptr)
      return false;

    levelDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getFmiForecastTypeDef(int forecastTypeId,ForecastTypeDef& forecastTypeDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getFmiForecastTypeDef(forecastTypeId);
    if (def == nullptr)
      return false;

    forecastTypeDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGrib1LevelDef(uint levelId,LevelDef& levelDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getGrib1LevelDef(levelId);
    if (def == nullptr)
      return false;

    levelDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGrib2LevelDef(uint levelId,LevelDef& levelDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getGrib2LevelDef(levelId);
    if (def == nullptr)
      return false;

    levelDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





ForecastTypeDef_cptr GridDef::getFmiForecastTypeDef(int forecastTypeId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_forecastTypeDef_records.begin(); it != mFmi_forecastTypeDef_records.end(); ++it)
    {
      if (it->mForecastTypeId == forecastTypeId)
        return &(*it);
    }
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGrib1TimeRangeDef(uint timeRangeId,TimeRangeDef& timeRangeDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getGrib1TimeRangeDef(timeRangeId);
    if (def == nullptr)
      return false;

    timeRangeDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGrib2TimeRangeDef(uint timeRangeId,TimeRangeDef& timeRangeDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getGrib2TimeRangeDef(timeRangeId);
    if (def == nullptr)
      return false;

    timeRangeDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadGribUnitDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
          rec.mPreferredAreaInterpolationMethod = toInt16(field[2]);

          mGrib_unitDef_records.emplace_back(rec);
        }
      }

    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadGrib1LevelDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
            rec.mLevelId = toUInt32(field[0]);

          if (field[1][0] != '\0')
            rec.mName = field[1];

          if (field[2][0] != '\0')
            rec.mDescription = field[2];

          mGrib1_levelDef_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadGrib2LevelDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
            rec.mLevelId = toUInt32(field[0]);

          if (field[1][0] != '\0')
            rec.mName = field[1];

          if (field[2][0] != '\0')
            rec.mDescription = field[2];

          mGrib2_levelDef_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadGrib1TimeRangeDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
            rec.mTimeRangeId = toUInt32(field[0]);

          if (field[1][0] != '\0')
            rec.mName = field[1];

          if (field[2][0] != '\0')
            rec.mDescription = field[2];

          mGrib1_timeRangeDef_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadGrib2TimeRangeDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
            rec.mTimeRangeId = toUInt32(field[0]);

          if (field[1][0] != '\0')
            rec.mName = field[1];

          if (field[2][0] != '\0')
            rec.mDescription = field[2];

          mGrib2_timeRangeDef_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadGrib1ParameterDefs(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
            rec.mTable2Version = toUInt32(field[1]);

          if (field[2][0] != '\0')
            rec.mCentre = toUInt32(field[2]);

          if (field[3][0] != '\0')
            rec.mIndicatorOfParameter = toUInt32(field[3]);

          if (field[4][0] != '\0')
            rec.mIndicatorOfTypeOfLevel = toUInt32(field[4]);

          if (field[5][0] != '\0')
            rec.mParameterLevel = toUInt32(field[5]);

          if (field[6][0] != '\0')
            rec.mParameterUnits = field[6];

          if (field[7][0] != '\0')
            rec.mParameterName = field[7];

          if (field[8][0] != '\0')
            rec.mParameterDescription = field[8];

          mGrib1_parameterDef_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






void GridDef::loadGrib2ParameterDefs(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
            rec.mDiscipline = toUInt8(field[1]);

          if (field[2][0] != '\0')
            rec.mCentre = toUInt16(field[2]);

          if (field[3][0] != '\0')
            rec.mParameterCategory = toUInt8(field[3]);

          if (field[4][0] != '\0')
            rec.mParameterNumber = toUInt8(field[4]);

          if (field[5][0] != '\0')
            rec.mProbabilityType = toUInt8(field[5]);

          if (field[6][0] != '\0')
            rec.mProductDefinitionTemplateNumber = toUInt16(field[6]);

          if (field[7][0] != '\0')
            rec.mTypeOfFirstFixedSurface = toUInt8(field[7]);

          if (field[8][0] != '\0')
            rec.mTypeOfSecondFixedSurface = toUInt8(field[8]);

          if (field[9][0] != '\0')
            rec.mTypeOfStatisticalProcessing = toUInt8(field[9]);

          if (field[10][0] != '\0')
            rec.mScaledValueOfLowerLimit = toUInt8(field[10]);

          if (field[11][0] != '\0')
            rec.mScaledValueOfFirstFixedSurface = toUInt32(field[11]);

          if (field[12][0] != '\0')
            rec.mScaledValueOfSecondFixedSurface = toUInt32(field[12]);

          if (field[13][0] != '\0')
            rec.mScaleFactorOfLowerLimit = toUInt8(field[13]);

          if (field[14][0] != '\0')
            rec.mScaleFactorOfFirstFixedSurface = toUInt8(field[14]);

          if (field[15][0] != '\0')
            rec.mScaleFactorOfSecondFixedSurface = toUInt8(field[15]);

          if (field[16][0] != '\0')
            rec.mIs_tigge = toUInt8(field[16]);

          if (field[17][0] != '\0')
            rec.mTypeOfGeneratingProcess = toUInt8(field[17]);

          if (field[18][0] != '\0')
            rec.mConstituentType = toUInt16(field[18]);

          if (field[19][0] != '\0')
            rec.mLengthOfTimeRange = toUInt8(field[19]);

          if (field[20][0] != '\0')
            rec.mLocalTablesVersion = toUInt8(field[20]);

          if (field[21][0] != '\0')
            rec.mAerosolType = toUInt16(field[21]);

          if (field[22][0] != '\0')
            rec.mParameterUnits = field[22];

          if (field[23][0] != '\0')
            rec.mParameterName = field[23];

          if (field[24][0] != '\0')
            rec.mParameterDescription = field[24];

          mGrib2_parameterDef_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadFmiLevelDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
            rec. mLevelId = toUInt32(field[0]);

          if (field[1][0] != '\0')
            rec.mName = field[1];

          if (field[2][0] != '\0')
            rec.mDescription = field[2];

          mFmi_levelDef_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadFmiForecastTypeDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
          ForecastTypeDef rec;

          if (field[0][0] != '\0')
            rec. mForecastTypeId = toInt32(field[0]);

          if (field[1][0] != '\0')
            rec.mName = field[1];

          if (field[2][0] != '\0')
            rec.mDescription = field[2];

          mFmi_forecastTypeDef_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadFmiParameterId_grib(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
          FmiParameterId_grib rec;

          if (field[0][0] != '\0')
            rec.mFmiParameterId = field[0];

          if (field[1][0] != '\0')
            rec.mGribParameterId = field[1];

          if (field[2][0] != '\0')
            rec.mConversionFunction = field[2];

          if (c > 3 && field[3][0] != '\0')
            rec.mReverseConversionFunction = field[3];

          mFmi_parametersFromGrib_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadFmiParameterId_grib1(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
            rec.mFmiProducerId = toUInt32(field[1]);

          if (field[2][0] != '\0')
            rec.mGeneratingProcessIdentifier = toUInt32(field[2]);

          if (field[3][0] != '\0')
            rec.mCentre = toUInt32(field[3]);

          if (field[4][0] != '\0')
            rec.mGribTableVersion = toUInt32(field[4]);

          if (field[5][0] != '\0')
            rec.mGribParameterNumber = toUInt32(field[5]);

          if (field[6][0] != '\0')
            rec.mGribTimerangeIndicator = toUInt32(field[6]);

          if (field[7][0] != '\0')
            rec.mFmiParameterLevelId = toUInt32(field[7]);

          if (field[8][0] != '\0')
            rec.mGribParameterLevelId = toUInt32(field[8]);

          if (field[9][0] != '\0')
            rec.mParameterLevel = toUInt32(field[9]);

          mFmi_parametersFromGrib1_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadFmiParameterId_grib2(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
            rec.mFmiProducerId = toUInt32(field[1]);

          if (field[2][0] != '\0')
            rec.mGeneratingProcessIdentifier = toUInt32(field[2]);

          if (field[3][0] != '\0')
            rec.mCentre = toUInt32(field[3]);

          if (field[4][0] != '\0')
            rec.mDiscipline = toUInt32(field[4]);

          if (field[5][0] != '\0')
            rec.mParameterCategory = toUInt32(field[5]);

          if (field[6][0] != '\0')
            rec.mParameterNumber = toUInt32(field[6]);

          if (field[7][0] != '\0')
            rec.mFmiParameterLevelId = toUInt32(field[7]);

          if (field[8][0] != '\0')
            rec.mGribParameterLevelId = toUInt32(field[8]);

          if (field[9][0] != '\0')
            rec.mParameterLevel = toUInt32(field[9]);

          mFmi_parametersFromGrib2_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadFmiParameterId_newbase(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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

          if (c > 3 && field[3][0] != '\0')
            rec.mReverseConversionFunction = field[3];

          mFmi_parametersFromNewbase_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadFmiParameterDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
            rec.mVersion = toUInt32(field[1]);

          if (field[2][0] != '\0')
            rec.mParameterName = field[2];

          if (field[3][0] != '\0')
            rec.mParameterUnits = field[3];

          if (field[4][0] != '\0')
            rec.mParameterDescription = field[4];

          if (field[5][0] != '\0')
            rec.mAreaInterpolationMethod = toInt16(field[5]);

          if (field[6][0] != '\0')
            rec.mTimeInterpolationMethod = toInt16(field[6]);

          if (field[7][0] != '\0')
            rec.mLevelInterpolationMethod = toInt16(field[7]);

          if (c > 8 &&  field[8][0] != '\0')
            rec.mDefaultPrecision = toInt16(field[8]);

          mFmi_parameterDef_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadFmiLevelId_grib1(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
            rec.mFmiLevelId = toUInt32(field[0]);

          if (field[1][0] != '\0')
            rec.mFmiProducerId = toUInt32(field[1]);

          if (field[2][0] != '\0')
            rec.mGeneratingProcessIdentifier = toUInt32(field[2]);

          if (field[3][0] != '\0')
            rec.mCentre = toUInt32(field[3]);

          if (field[4][0] != '\0')
            rec.mGribLevelId = toUInt32(field[4]);

          mFmi_levelsFromGrib1_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadFmiLevelId_grib2(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
            rec.mFmiLevelId = toUInt32(field[0]);

          if (field[1][0] != '\0')
            rec.mFmiProducerId = toUInt32(field[1]);

          if (field[2][0] != '\0')
            rec.mGeneratingProcessIdentifier = toUInt32(field[2]);

          if (field[3][0] != '\0')
            rec.mCentre = toUInt32(field[3]);

          if (field[4][0] != '\0')
            rec.mGribLevelId = toUInt32(field[4]);

          mFmi_levelsFromGrib2_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadNewbaseParameterDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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

          mNewbase_parameterDef_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadFmiProducerId_grib(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
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
            rec.mProducerId = toUInt32(field[0]);

          if (field[1][0] != '\0')
            rec.mType = toUInt32(field[1]);

          if (field[2][0] != '\0')
            rec.mCentre = toUInt32(field[2]);

          if (field[3][0] != '\0')
            rec.mIdent = toUInt32(field[3]);

          if (field[4][0] != '\0')
            rec.mProducerName = field[4];

          if (field[5][0] != '\0')
            rec.mProducerDescription = field[5];


          mFmi_producersFromGrib_records.emplace_back(rec);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGridLatLonAreaByGeometryId(T::GeometryId geometryId,T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight)
{
  FUNCTION_TRACE
  try
  {
    auto g2 = GridDef::getGrib2DefinitionByGeometryId(geometryId);
    if (g2 != nullptr)
    {
      return g2->getGridLatLonArea(topLeft,topRight,bottomLeft,bottomRight);
    }

    auto g1 = GridDef::getGrib1DefinitionByGeometryId(geometryId);
    if (g1 != nullptr)
    {
      return g1->getGridLatLonArea(topLeft,topRight,bottomLeft,bottomRight);
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGridCellAverageSizeByGeometryId(T::GeometryId geometryId,double& width,double& height)
{
  FUNCTION_TRACE
  try
  {
    auto g2 = GridDef::getGrib2DefinitionByGeometryId(geometryId);
    if (g2 != nullptr)
    {
      g2->getGridCellAverageSize(width,height);
      if (width != 0  &&  height != 0)
        return true;
    }

    auto g1 = GridDef::getGrib1DefinitionByGeometryId(geometryId);
    if (g1 != nullptr)
    {
      g1->getGridCellAverageSize(width,height);
      if (width != 0  &&  height != 0)
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::Coordinate_svec GridDef::getGridOriginalCoordinatesByGeometryId(T::GeometryId  geometryId)
{
  FUNCTION_TRACE
  try
  {
    auto g2 = GridDef::getGrib2DefinitionByGeometryId(geometryId);
    if (g2 != nullptr)
      return g2->getGridOriginalCoordinates();

    auto g1 = GridDef::getGrib1DefinitionByGeometryId(geometryId);
    if (g1 != nullptr)
      return g1->getGridOriginalCoordinates();

    T::Coordinate_svec empty(new T::Coordinate_vec());
    return empty;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::Coordinate_svec GridDef::getGridLatLonCoordinatesByGeometryId(T::GeometryId  geometryId)
{
  FUNCTION_TRACE
  try
  {
    auto g2 = GridDef::getGrib2DefinitionByGeometryId(geometryId);
    if (g2 != nullptr)
    {
      return g2->getGridLatLonCoordinates();
    }

    auto g1 = GridDef::getGrib1DefinitionByGeometryId(geometryId);
    if (g1 != nullptr)
    {
      return g1->getGridLatLonCoordinates();
    }

    // Coordinates not found by the geometry
    T::Coordinate_svec empty(new T::Coordinate_vec());
    return empty;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::getGridOriginalCoordinatesByGeometry(T::AttributeList& attributeList,T::Coordinate_svec& latLonCoordinates,T::CoordinateType coordinateType,T::Coordinate_svec& coordinates,uint& width,uint& height)
{
  FUNCTION_TRACE
  try
  {
    //attributeList.print(std::cout,0,0);
    const char *crsStr = attributeList.getAttributeValue("grid.crs");
    const char *proj4Str = attributeList.getAttributeValue("grid.proj4");
    const char *originalCrsStr = attributeList.getAttributeValue("grid.original.crs");
    const char *urnStr = attributeList.getAttributeValue("grid.urn");
    const char *bboxStr = attributeList.getAttributeValue("grid.bbox");
    const char *llboxStr = attributeList.getAttributeValue("grid.llbox");
    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    const char *geometryStringStr = attributeList.getAttributeValue("grid.geometryString");
    const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
    const char *gridHeightStr = attributeList.getAttributeValue("grid.height");

    if (geometryIdStr == nullptr  &&  geometryStringStr == nullptr  &&  urnStr == nullptr  &&  crsStr == nullptr)
      return;


    if (crsStr != nullptr  &&  strcasecmp(crsStr,"crop") == 0)
    {
      if (originalCrsStr == nullptr)
        return;

      crsStr = originalCrsStr;
    }

    // Checking if the geometry is defined by the geometryId

    GRIB2::GridDef_ptr def = nullptr;
    if (geometryIdStr != nullptr)
    {
      def = getGrib2DefinitionByGeometryId(toInt32(geometryIdStr));
      if (!def)
        return;

      latLonCoordinates = def->getGridLatLonCoordinates();
    }


    // Checking if the geometry is defigned by the geometry string

    std::shared_ptr<GRIB2::GridDefinition> defPtr;
    if (geometryStringStr != nullptr)
    {
      def =  Identification::gridDef.createGrib2GridDefinition(geometryStringStr);
      if (!def)
        return;

      defPtr.reset(def);
      latLonCoordinates = def->getGridLatLonCoordinates();
    }


    if (def != nullptr)
    {
      // If we have valid geometry definition then we know the grid width and the height.

      T::Dimensions d = def->getGridDimensions();
      width = d.nx();
      height = d.ny();
      attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)def->reverseYDirection()));
      attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)def->reverseXDirection()));

      double wm = 0;
      double hm = 0;
      if (def->getGridMetricCellSize(wm,hm))
      {
        attributeList.setAttribute("grid.cell.width",Fmi::to_string(wm));
        attributeList.setAttribute("grid.cell.height",Fmi::to_string(hm));
      }
      else
      {
        attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
        attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

        def->getGridCellAverageSize(wm,hm);
        attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
        attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
      }
    }


    if ((urnStr != nullptr  || crsStr != nullptr)  &&  (bboxStr != nullptr || llboxStr != nullptr)  &&  gridWidthStr != nullptr  &&  gridHeightStr != nullptr)
    {
      // If the geometry id defined by the URN / CRS then we need to the bounding box coordinates and preferred grid width and height.

      std::vector<double> aa;

      if (bboxStr != nullptr)
        splitString(bboxStr,',',aa);
      else
      if (llboxStr != nullptr)
      {
        splitString(llboxStr,',',aa);
      }

      if (aa.size() == 4)
      {
        std::vector<double> cc;

        OGRSpatialReference sr_latlon;
        sr_latlon.importFromEPSG(4326);
        sr_latlon.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

        OGRSpatialReference sr;

        if (urnStr != nullptr)
        {
          std::string urn = urnStr;
          if (strncasecmp(urnStr,"urn:ogc:def:crs:",16) != 0)
            urn = std::string("urn:ogc:def:crs:") + urnStr;

          if (sr.importFromURN(urn.c_str()) != OGRERR_NONE)
            throw Fmi::Exception(BCP, "Invalid urn '" + std::string(urnStr) + "'!");
        }
        else
        if (proj4Str != nullptr)
        {
          OGRErr err = sr.SetFromUserInput(proj4Str);
          if (err != OGRERR_NONE)
            throw Fmi::Exception(BCP, "Invalid proj4 '" + std::string(proj4Str) + "'!");
        }
        else
        if (crsStr != nullptr)
        {
          OGRErr err = sr.SetFromUserInput(crsStr);
          if (err != OGRERR_NONE)
            throw Fmi::Exception(BCP, "Invalid crs '" + std::string(crsStr) + "'!");
        }

        sr.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

        OGRCoordinateTransformation *transformation = OGRCreateCoordinateTransformation(&sr,&sr_latlon);
        if (transformation == nullptr)
          throw Fmi::Exception(BCP,"Cannot create coordinate transformation!");

        OGRCoordinateTransformation *reverseTransformation = nullptr;

        if (bboxStr != nullptr)
          cc = aa;
        else
        if (llboxStr != nullptr)
        {
          reverseTransformation = OGRCreateCoordinateTransformation(&sr_latlon,&sr);
          if (reverseTransformation == nullptr)
          {
            if (transformation != nullptr)
             OCTDestroyCoordinateTransformation(transformation);

            throw Fmi::Exception(BCP,"Cannot create coordinate transformation!");
          }

          double lon1 = aa[0];
          double lat1 = aa[1];
          double lon2 = aa[2];
          double lat2 = aa[3];

          reverseTransformation->Transform(1,&lon1,&lat1);
          reverseTransformation->Transform(1,&lon2,&lat2);

          cc.emplace_back(lon1);
          cc.emplace_back(lat1);
          cc.emplace_back(lon2);
          cc.emplace_back(lat2);
        }

        width = toUInt32(gridWidthStr);
        height = toUInt32(gridHeightStr);

        double diffx = cc[2] - cc[0];
        double diffy = cc[3] - cc[1];

        double dx = diffx / C_DOUBLE(width-1);
        double dy = diffy / C_DOUBLE(height-1);

        attributeList.setAttribute("grid.cell.width",Fmi::to_string(dx));
        attributeList.setAttribute("grid.cell.height",Fmi::to_string(dy));
        std::size_t hash = attributeList.getHash();

        {
          AutoReadLock lock(&mCoordinateCacheModificationLock);
          auto it = mCoordinateCache.find(hash);
          if (it != mCoordinateCache.end())
          {
            latLonCoordinates = it->second.latlonCoordinates;
            coordinates = it->second.originalCoordinates;
          }
        }

        if (!latLonCoordinates || latLonCoordinates->size() == 0)
        {
          uint sz = width*height;

          if (!latLonCoordinates)
            latLonCoordinates.reset(new T::Coordinate_vec());

          if (!coordinates)
            coordinates.reset(new T::Coordinate_vec());

          coordinates->reserve(sz);
          latLonCoordinates->reserve(sz);

          double *lon = new double[sz+1];
          double *lat = new double[sz+1];

          std::shared_ptr<double> rlat(lat);
          std::shared_ptr<double> rlon(lon);

          double yy = cc[1];
          int c = 0;
          for (uint y=0; y<height; y++)
          {
            double xx = cc[0];
            for (uint x=0; x<width; x++)
            {
              lon[c] = xx;
              lat[c] = yy;


              coordinates->emplace_back(T::Coordinate(xx,yy));

              xx = xx + dx;
              c++;
            }
            yy = yy + dy;
          }

          transformation->Transform(c,lon,lat);

          for (int t=0; t<c; t++)
          {
            latLonCoordinates->emplace_back(T::Coordinate(getLongitude(lon[t]),lat[t]));
          }

          if (transformation != nullptr)
            OCTDestroyCoordinateTransformation(transformation);

          if (reverseTransformation != nullptr)
            OCTDestroyCoordinateTransformation(reverseTransformation);


          CoordinateRec rec;
          rec.latlonCoordinates = latLonCoordinates;
          rec.originalCoordinates = coordinates;

          AutoWriteLock lock(&mCoordinateCacheModificationLock);
          mCoordinateCache.insert(std::pair<std::size_t,CoordinateRec>(hash,rec));
        }
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::getGridLatLonCoordinatesByGeometry(T::AttributeList& attributeList,T::Coordinate_svec& latLonCoordinates,uint& width,uint& height)
{
  FUNCTION_TRACE
  try
  {
    const char *crsStr = attributeList.getAttributeValue("grid.crs");
    const char *proj4Str = attributeList.getAttributeValue("grid.proj4Str");
    const char *originalCrsStr = attributeList.getAttributeValue("grid.original.crs");
    const char *urnStr = attributeList.getAttributeValue("grid.urn");
    const char *bboxStr = attributeList.getAttributeValue("grid.bbox");
    const char *crop_bboxStr = attributeList.getAttributeValue("grid.crop.bbox");
    const char *llboxStr = attributeList.getAttributeValue("grid.llbox");
    const char *crop_llboxStr = attributeList.getAttributeValue("grid.crop.llbox");
    const char *geometryIdStr = attributeList.getAttributeValue("grid.geometryId");
    const char *geometryStringStr = attributeList.getAttributeValue("grid.geometryString");
    const char *gridWidthStr = attributeList.getAttributeValue("grid.width");
    const char *gridHeightStr = attributeList.getAttributeValue("grid.height");
    const char *gridCellWidthStr = attributeList.getAttributeValue("grid.original.cell.width");
    const char *gridCellHeightStr = attributeList.getAttributeValue("grid.original.cell.height");
    const char *gridCellWidthDegrStr = attributeList.getAttributeValue("grid.original.cell.width.degrees");
    const char *gridCellHeightDegrStr = attributeList.getAttributeValue("grid.original.cell.height.degrees");
    const char *gridOriginalProjectionStr = attributeList.getAttributeValue("grid.original.projectionType");

    if (geometryIdStr == nullptr  &&  geometryStringStr == nullptr  &&  urnStr == nullptr  &&  crsStr == nullptr)
      return;

    if (crsStr != nullptr  &&  strcasecmp(crsStr,"crop") == 0)
    {
      if (originalCrsStr == nullptr)
        return;

      if (crop_bboxStr)
        bboxStr = crop_bboxStr;

      if (crop_llboxStr)
        llboxStr = crop_llboxStr;


      crsStr = originalCrsStr;
    }


    // Checking if the geometry is defined by the geometryId

    GRIB2::GridDef_ptr def = nullptr;
    if (geometryIdStr != nullptr)
    {
      def = getGrib2DefinitionByGeometryId(toInt32(geometryIdStr));
      if (!def)
        return;

      latLonCoordinates = def->getGridLatLonCoordinates();
    }


    // Checking if the geometry is defigned by the geometry string

    std::shared_ptr<GRIB2::GridDefinition> defPtr;
    if (geometryStringStr != nullptr)
    {
      def =  Identification::gridDef.createGrib2GridDefinition(geometryStringStr);
      if (!def)
        return;

      defPtr.reset(def);
      latLonCoordinates = def->getGridLatLonCoordinates();
    }


    if (def != nullptr)
    {
      // If we have valid geometry definition then we know the grid width and the height.

      T::Dimensions d = def->getGridDimensions();
      width = d.nx();
      height = d.ny();
      attributeList.setAttribute("grid.original.reverseYDirection",Fmi::to_string((int)def->reverseYDirection()));
      attributeList.setAttribute("grid.original.reverseXDirection",Fmi::to_string((int)def->reverseXDirection()));

      double wm = 0;
      double hm = 0;
      if (def->getGridMetricCellSize(wm,hm))
      {
        attributeList.setAttribute("grid.cell.width",Fmi::to_string(wm));
        attributeList.setAttribute("grid.cell.height",Fmi::to_string(hm));
      }
      else
      {
        attributeList.setAttribute("grid.original.cell.width.degrees",Fmi::to_string(wm));
        attributeList.setAttribute("grid.original.cell.height.degrees",Fmi::to_string(hm));

        def->getGridCellAverageSize(wm,hm);
        attributeList.setAttribute("grid.original.cell.width",Fmi::to_string(wm));
        attributeList.setAttribute("grid.original.cell.height",Fmi::to_string(hm));
      }
    }

    if ((urnStr != nullptr || crsStr != nullptr)  &&  (bboxStr != nullptr ||  llboxStr != nullptr) && ((gridWidthStr != nullptr  &&  gridHeightStr != nullptr) ||  (gridCellWidthStr != nullptr  &&  gridCellHeightStr != nullptr)))
    {
      // If the geometry id defined by the URN then we need to the bounding box coordinates and preferred grid width and height.

      std::vector<double> aa;

      if (bboxStr != nullptr)
        splitString(bboxStr,',',aa);
      else
      if (llboxStr != nullptr)
      {
        splitString(llboxStr,',',aa);
      }

      if (aa.size() == 4)
      {
        std::vector<double> cc;

        OGRSpatialReference sr_latlon;
        sr_latlon.importFromEPSG(4326);
        sr_latlon.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

        OGRSpatialReference sr;

        if (urnStr != nullptr)
        {
          std::string urn = urnStr;
          if (strncasecmp(urnStr,"urn:ogc:def:crs:",16) != 0)
            urn = std::string("urn:ogc:def:crs:") + urnStr;

          if (sr.importFromURN(urn.c_str()) != OGRERR_NONE)
            throw Fmi::Exception(BCP, "Invalid urn '" + std::string(urnStr) + "'!");
        }
        else
        if (proj4Str != nullptr)
        {
          OGRErr err = sr.SetFromUserInput(proj4Str);
          if (err != OGRERR_NONE)
            throw Fmi::Exception(BCP, "Invalid proj4 '" + std::string(proj4Str) + "'!");
        }
        else
        if (crsStr != nullptr)
        {
          if (sr.SetFromUserInput(crsStr) != OGRERR_NONE)
            throw Fmi::Exception(BCP, "Invalid crs '" + std::string(crsStr) + "'!");
        }
        sr.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

        OGRCoordinateTransformation *transformation = OGRCreateCoordinateTransformation(&sr,&sr_latlon);
        if (transformation == nullptr)
          throw Fmi::Exception(BCP,"Cannot create coordinate transformation!");

        OGRCoordinateTransformation *reverseTransformation = nullptr;

        bool targetIsLatlon = false;

        if (bboxStr != nullptr)
          cc = aa;
        else
        if (llboxStr != nullptr)
        {
          reverseTransformation = OGRCreateCoordinateTransformation(&sr_latlon,&sr);
          if (reverseTransformation == nullptr)
          {
            if (transformation != nullptr)
             OCTDestroyCoordinateTransformation(transformation);

            throw Fmi::Exception(BCP,"Cannot create coordinate transformation!");
          }

          double lon1 = aa[0];
          double lat1 = aa[1];
          double lon2 = aa[2];
          double lat2 = aa[3];

          reverseTransformation->Transform(1,&lon1,&lat1);
          reverseTransformation->Transform(1,&lon2,&lat2);

          cc.emplace_back(lon1);
          cc.emplace_back(lat1);
          cc.emplace_back(lon2);
          cc.emplace_back(lat2);

          if (lon1 == aa[0]  &&  lat1 == aa[1]  && lon2 == aa[2]  &&  lat2 == aa[3])
            targetIsLatlon = true;
        }

        double diffx = cc[2] - cc[0];
        double diffy = cc[3] - cc[1];


        double dx = 0;
        double dy = 0;

        if (gridWidthStr != nullptr  &&  gridHeightStr != nullptr)
        {
          width = toUInt32(gridWidthStr);
          height = toUInt32(gridHeightStr);

          dx = diffx / C_DOUBLE(width-1);
          dy = diffy / C_DOUBLE(height-1);
        }
        else
        {
          if (gridCellWidthStr != nullptr  &&  gridCellHeightStr != nullptr)
          {
            // Trying to define width and height for the new grid.

            // Size of the original grid cell (this might be metric or in degrees)
            double dxx = toDouble(gridCellWidthStr);
            double dyy = toDouble(gridCellHeightStr);

            int origProjectionType = 0;
            if (gridOriginalProjectionStr != NULL)
              origProjectionType = atoi(gridOriginalProjectionStr);

            if (targetIsLatlon)
            {
              // The target projection is latlon

              if (origProjectionType == T::GridProjectionValue::LatLon)
              {
                // The source projection is also latlon.

                if (gridCellWidthDegrStr != nullptr  &&  gridCellHeightDegrStr != nullptr)
                {
                  dxx = toDouble(gridCellWidthDegrStr);
                  dyy = toDouble(gridCellHeightDegrStr);
                }

                width = C_UINT(fabs(diffx) / dxx + 1);
                height = C_UINT(fabs(diffy) / dyy + 1);
              }
              else
              {
                // The source is metric

                // Counting metric width and height of the target projection

                double w1 = latlon_distance(cc[1], cc[0], cc[1],cc[2]);
                double w2 = latlon_distance(cc[3], cc[0], cc[3],cc[2]);
                double w = (w1+w2)/2;

                double h1 = latlon_distance(cc[1], cc[0], cc[3],cc[0]);
                double h2 = latlon_distance(cc[1], cc[2], cc[3],cc[2]);
                double h = (h1+h2)/2;

                // Width and height (in pixels) for the new grid

                width =  C_UINT(w/dxx);
                height = C_UINT(h/dyy);
              }
            }
            else
            {
              // The target projection is metric

              width = C_UINT(fabs(diffx) / dxx + 1);
              height = C_UINT(fabs(diffy) / dyy + 1);
            }

            dx = diffx / C_DOUBLE(width-1);
            dy = diffy / C_DOUBLE(height-1);
          }
        }

        if (width == 0 || height == 0)
        {
          Fmi::Exception exception(BCP,"Invalid grid size!");
          exception.addParameter("width",std::to_string(width));
          exception.addParameter("height",std::to_string(height));
          throw exception;
        }

        attributeList.setAttribute("grid.cell.width",Fmi::to_string(dx));
        attributeList.setAttribute("grid.cell.height",Fmi::to_string(dy));


        std::size_t hash = attributeList.getHash();
        {
          AutoReadLock lock(&mCoordinateCacheModificationLock);
          auto it = mCoordinateCache.find(hash);
          if (it != mCoordinateCache.end())
          {
            latLonCoordinates = it->second.latlonCoordinates;
          }
        }

        if (!latLonCoordinates || latLonCoordinates->size() == 0)
        {
          uint sz = width*height;

          if (!latLonCoordinates)
            latLonCoordinates.reset(new T::Coordinate_vec());

          latLonCoordinates->reserve(sz);

          double *lon = new double[sz+1];
          double *lat = new double[sz+1];

          std::shared_ptr<double> rlat(lat);
          std::shared_ptr<double> rlon(lon);

          int c = 0;
          double yy = cc[1];
          for (uint y=0; y<height; y++)
          {
            double xx = cc[0];
            for (uint x=0; x<width; x++)
            {
              lon[c] = xx;
              lat[c] = yy;

              xx = xx + dx;
              c++;
            }
            yy = yy + dy;
          }

          transformation->Transform(c,lon,lat);
          for (int t=0; t<c; t++)
          {
            latLonCoordinates->emplace_back(T::Coordinate(getLongitude(lon[t]),lat[t]));
          }

          if (transformation != nullptr)
            OCTDestroyCoordinateTransformation(transformation);

          if (reverseTransformation != nullptr)
            OCTDestroyCoordinateTransformation(reverseTransformation);

          CoordinateRec rec;
          rec.latlonCoordinates = latLonCoordinates;
          AutoWriteLock lock(&mCoordinateCacheModificationLock);
          mCoordinateCache.insert(std::pair<std::size_t,CoordinateRec>(hash,rec));
        }
      }
    }

    if (latLonCoordinates->size() > 0)
    {
      int last = latLonCoordinates->size() - 1;
      char tmp[100];
      sprintf(tmp,"%f,%f,%f,%f",(*latLonCoordinates)[0].x(),(*latLonCoordinates)[0].y(),(*latLonCoordinates)[last].x(),(*latLonCoordinates)[last].y());
      attributeList.setAttribute("grid.llbox",tmp);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





GRIB1::GridDef_ptr GridDef::getGrib1DefinitionByGeometryId(int geometryId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGridDefinitions1.begin(); it != mGridDefinitions1.end(); ++it)
    {
      if (it->second->getGridGeometryId() == geometryId)
        return it->second;
    }

    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





GRIB1::GridDef_ptr GridDef::getGrib1Definition(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    std::string geometryStr = message.getGridGeometryString();

    auto it = mGridDefinitions1.find(geometryStr);
    if (it != mGridDefinitions1.end())
      return it->second;

    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





GRIB2::GridDef_ptr GridDef::getGrib2Definition(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    std::string geometryStr = message.getGridGeometryString();

    auto it = mGridDefinitions2.find(geometryStr);
    if (it != mGridDefinitions2.end())
      return it->second;

    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





GRIB2::GridDef_ptr GridDef::getGrib2DefinitionByGeometryId(int geometryId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mGridDefinitions2.begin(); it != mGridDefinitions2.end(); ++it)
    {
      if (it->second->getGridGeometryId() == geometryId)
        return it->second;
    }
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




int GridDef::getGrib1GeometryId(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getGrib1Definition(message);
    if (def == nullptr)
      return 0;

    return def->getGridGeometryId();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





int GridDef::getGrib2GeometryId(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getGrib2Definition(message);
    if (def == nullptr)
      return 0;

    return def->getGridGeometryId();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGeometryNameById(T::GeometryId geometryId,std::string& name)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto *def2 = getGrib2DefinitionByGeometryId(geometryId);
    if (def2)
    {
      name = def2->getGridGeometryName();
      return true;
    }

    auto *def1 = getGrib1DefinitionByGeometryId(geometryId);
    if (def1)
    {
      name = def1->getGridGeometryName();
      return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGridDirectionsByGeometryId(T::GeometryId  geometryId,bool& reverseXDirection,bool& reverseYDirection)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto *def2 = getGrib2DefinitionByGeometryId(geometryId);
    if (def2)
    {
      reverseXDirection = def2->reverseXDirection();
      reverseYDirection = def2->reverseYDirection();
      return true;
    }

    auto *def1 = getGrib1DefinitionByGeometryId(geometryId);
    if (def1)
    {
      reverseXDirection = def1->reverseXDirection();
      reverseYDirection = def1->reverseYDirection();
      return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::Coordinate_svec GridDef::getGridLatLonCoordinateLinePointsByGeometryId(T::GeometryId  geometryId)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    T::Coordinate_svec coordinates(new T::Coordinate_vec());
    T::Coordinate_vec latlon;
    for (int lat=-90; lat < 90; lat = lat + 10)
    {
      for (int lon=-1800; lon < 1800; lon++)
      {
        latlon.emplace_back(T::Coordinate(C_DOUBLE(lon)/10,C_DOUBLE(lat)));
      }
    }

    for (int lon=-180; lon < 180; lon=lon+10)
    {
      for (int lat=-900; lat < 900; lat++)
      {
        latlon.emplace_back(T::Coordinate(C_DOUBLE(lon),C_DOUBLE(lat)/10));
      }
    }

    auto *def2 = getGrib2DefinitionByGeometryId(geometryId);
    if (def2)
    {
      def2->getGridPointListByLatLonCoordinates(latlon,*coordinates);
      return coordinates;
    }

    auto *def1 = getGrib1DefinitionByGeometryId(geometryId);
    if (def1)
    {
      def1->getGridPointListByLatLonCoordinates(latlon,*coordinates);
      return coordinates;
    }

    return coordinates;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGridDimensionsByGeometryId(T::GeometryId  geometryId,uint& cols,uint& rows)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto *def2 = getGrib2DefinitionByGeometryId(geometryId);
    if (def2)
    {
      T::Dimensions d = def2->getGridDimensions();
      if (d.getDimensions() == 2)
      {
        cols = d.nx();
        rows = d.ny();
        return true;
      }
    }

    auto *def1 = getGrib1DefinitionByGeometryId(geometryId);
    if (def1)
    {
      T::Dimensions d = def1->getGridDimensions();
      if (d.getDimensions() == 2)
      {
        cols = d.nx();
        rows = d.ny();
        return true;
      }
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGridPointByGeometryIdAndLatLonCoordinates(T::GeometryId  geometryId,double lat,double lon,double& grid_i,double& grid_j)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto *def2 = getGrib2DefinitionByGeometryId(geometryId);
    if (def2)
      return def2->getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j);

    auto *def1 = getGrib1DefinitionByGeometryId(geometryId);
    if (def1)
      return def1->getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j);

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGridLatLonCoordinatesByGeometryId(T::GeometryId  geometryId,T::Coordinate_svec& coordinates)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto *def2 = getGrib2DefinitionByGeometryId(geometryId);
    if (def2)
    {
      coordinates = def2->getGridLatLonCoordinates();
      return true;
    }

    auto *def1 = getGrib1DefinitionByGeometryId(geometryId);
    if (def1)
    {
      coordinates = def1->getGridLatLonCoordinates();
      return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::getGeometryIdList(std::set<T::GeometryId>& geometryIdList)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    for (auto it = mGridDefinitions2.begin(); it != mGridDefinitions2.end(); ++it)
    {
      T::GeometryId geometryId = it->second->getGridGeometryId();
      //if (geometryIdList.find(geometryId) == geometryIdList.end())
        geometryIdList.insert(geometryId);
    }

    for (auto it = mGridDefinitions1.begin(); it != mGridDefinitions1.end(); ++it)
    {
      T::GeometryId geometryId = it->second->getGridGeometryId();
      //if (geometryIdList.find(geometryId) == geometryIdList.end())
        geometryIdList.insert(geometryId);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::getGeometryIdListByLatLon(double lat,double lon,std::set<T::GeometryId>& geometryIdList)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    for (auto it = mGridDefinitions2.begin(); it != mGridDefinitions2.end(); ++it)
    {
      double grid_i = 0;
      double grid_j = 0;

      if (it->second->getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j))
      {
        T::GeometryId geometryId = it->second->getGridGeometryId();
        //if (geometryIdList.find(geometryId) == geometryIdList.end())
          geometryIdList.insert(geometryId);
      }
      else
      {
        //if ((*it)->getGridGeometryId() == 1078)
        //  printf("*** Not found %f,%f\n",lat,lon);
      }
    }

    for (auto it=mGridDefinitions1.begin(); it!=mGridDefinitions1.end(); ++it)
    {
      double grid_i = 0;
      double grid_j = 0;

      if (it->second->getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j))
      {
        T::GeometryId geometryId = it->second->getGridGeometryId();
        //if (geometryIdList.find(geometryId) == geometryIdList.end())
          geometryIdList.insert(geometryId);
      }
      else
      {
        //if ((*it)->getGridGeometryId() == 1078)
        //  printf("*** NOT FOUND %f,%f\n",lat,lon);
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDef::loadGeometryDefinitions(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    uint cnt = 0;
    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
      {
        cnt++;
        GRIB1::GridDefinition *def1 = createGrib1GridDefinition(st);
        if (def1 != nullptr)
        {
          std::string gstr = def1->getGridGeometryString();
          if (mGridDefinitions1.find(gstr) == mGridDefinitions1.end())
            mGridDefinitions1.insert(std::pair<std::string,GRIB1::GridDefinition*>(gstr,def1));
          else
            mGridDefinitions1.insert(std::pair<std::string,GRIB1::GridDefinition*>(gstr+Fmi::to_string(cnt),def1));
        }

        GRIB2::GridDefinition *def2 = createGrib2GridDefinition(st);
        if (def2 != nullptr)
        {
          std::string gstr = def2->getGridGeometryString();
          if (mGridDefinitions2.find(gstr) == mGridDefinitions2.end())
            mGridDefinitions2.insert(std::pair<std::string,GRIB2::GridDefinition*>(gstr,def2));
          else
            mGridDefinitions2.insert(std::pair<std::string,GRIB2::GridDefinition*>(gstr+Fmi::to_string(cnt),def2));
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





GRIB1::GridDefinition* GridDef::createGrib1GridDefinition(const char *str)
{
  FUNCTION_TRACE
  try
  {
    if (str[0] == '#')
      return nullptr;

    char st[1000];
    strcpy(st,str);

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
      ushort gridProjection = toUInt16(field[0]);
      switch (gridProjection)
      {
        case T::GridProjectionValue::Unknown:
          break;

        case T::GridProjectionValue::LatLon:
        {
          if (c < 10)
            return nullptr;

          uint geometryId = toInt32(field[1]);
          char *geometryName = field[2];
          int ni = toInt32(field[3]);
          int nj = toInt32(field[4]);
          int longitude = C_INT(round(toDouble(field[5])*1000));
          int latitude = C_INT(round(toDouble(field[6])*1000));
          int iInc = C_INT(round(toDouble(field[7]) * 1000));
          int jInc = C_INT(round(toDouble(field[8]) * 1000));
          char *scanningMode = field[9];
          int lastLongitude = longitude + ni*iInc - iInc;
          int lastLatitude = latitude + nj*jInc - jInc;

          if (lastLongitude > 360000)
            lastLongitude -= 360000;

          if (lastLatitude > 90000)
            lastLatitude = 180000 - lastLatitude;

          GRIB1::LatLonImpl *def1 = new GRIB1::LatLonImpl();
          GRIB1::GridAreaSettings gridArea;
          GRIB1::ScanningModeSettings scanningMode1;

          GRIB1::ResolutionFlagsSettings resolutionFlags;
          resolutionFlags.setResolutionAndComponentFlags(128);
          gridArea.setResolutionFlags(resolutionFlags);

          gridArea.setLatitudeOfFirstGridPoint(latitude);
          gridArea.setLongitudeOfFirstGridPoint(longitude);
          gridArea.setLatitudeOfLastGridPoint(lastLatitude);
          gridArea.setLongitudeOfLastGridPoint(lastLongitude);
          def1->setGridArea(gridArea);

          def1->setNi(ni);
          def1->setNj(nj);
          def1->setIDirectionIncrement(iInc);
          def1->setJDirectionIncrement(jInc);

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

          return def1;
        }
        break;

        case T::GridProjectionValue::RotatedLatLon:
        {
          if (c < 13)
            return nullptr;

          uint geometryId = toInt32(field[1]);
          char *geometryName = field[2];
          int ni = toInt32(field[3]);
          int nj = toInt32(field[4]);
          int longitude = C_INT(round(toDouble(field[5])*1000));
          int latitude = C_INT(round(toDouble(field[6])*1000));
          int iInc = C_INT(round(toDouble(field[7]) * 1000));
          int jInc = C_INT(round(toDouble(field[8]) * 1000));
          char *scanningMode = field[9];
          int longitudeOfSouthernPole = C_INT(round(toDouble(field[10])*1000));
          int latitudeOfSouthernPole = C_INT(round(toDouble(field[11])*1000));
          int lastLongitude = longitude + ni*iInc - iInc;
          int lastLatitude = latitude + nj*jInc - jInc;
          int angle = round(toDouble(field[12]));
          //std::uint8_t resolutionAndComponentFlags = 48;

          if (lastLongitude > 360000)
            lastLongitude -= 360000;

          if (lastLatitude > 90000)
            lastLatitude = 180000 - lastLatitude;

          GRIB1::RotatedLatLonImpl *def1 = new GRIB1::RotatedLatLonImpl();
          GRIB1::GridAreaSettings gridArea;
          GRIB1::RotationSettings rotation1;
          GRIB1::ScanningModeSettings scanningMode1;

          gridArea.setLatitudeOfFirstGridPoint(latitude);
          gridArea.setLongitudeOfFirstGridPoint(longitude);
          gridArea.setLatitudeOfLastGridPoint(lastLatitude);
          gridArea.setLongitudeOfLastGridPoint(lastLongitude);

          rotation1.setLatitudeOfSouthernPole(latitudeOfSouthernPole);
          rotation1.setLongitudeOfSouthernPole(longitudeOfSouthernPole);
          rotation1.setGeography_angleOfRotationInDegrees(angle);
          def1->setRotation(rotation1);

          def1->setNi(ni);
          def1->setNj(nj);
          def1->setGridArea(gridArea);
          def1->setIDirectionIncrement(iInc);
          def1->setJDirectionIncrement(jInc);

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

          return def1;
        }
        break;

        case T::GridProjectionValue::StretchedLatLon:
          break;

        case T::GridProjectionValue::StretchedRotatedLatLon:
          break;

        case T::GridProjectionValue::VariableResolutionLatLon:
          break;

        case T::GridProjectionValue::VariableResolutionRotatedLatLon:
          break;

        case T::GridProjectionValue::Mercator:
        {
          return nullptr;
          // ************* IMPLEMENTATION NOT TESTED *************

          if (c < 12)
            return nullptr;

          uint geometryId = toInt32(field[1]);
          char *geometryName = field[2];
          int ni = toInt32(field[3]);
          int nj = toInt32(field[4]);
          int longitude = C_INT(round(toDouble(field[5])*1000));
          int latitude = C_INT(round(toDouble(field[6])*1000));
          int iInc = C_INT(round(toDouble(field[7])));
          int jInc = C_INT(round(toDouble(field[8])));
          char *scanningMode = field[9];
          int latin = C_INT(round(toDouble(field[10])*1000));

          int lastLongitude = longitude + ni*iInc - iInc;
          int lastLatitude = latitude + nj*jInc - jInc;

          GRIB1::MercatorImpl *def1 = new GRIB1::MercatorImpl();
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

          def1->setNi(std::uint16_t(ni));
          def1->setNj(std::uint16_t(nj));

          GRIB1::GridAreaSettings gridArea;
          gridArea.setLatitudeOfFirstGridPoint(latitude);
          gridArea.setLongitudeOfFirstGridPoint(longitude);
          gridArea.setLatitudeOfLastGridPoint(lastLatitude);
          gridArea.setLongitudeOfLastGridPoint(lastLongitude);
          def1->setGridArea(gridArea);
          def1->setDiInMetres(iInc);
          def1->setDjInMetres(jInc);
          def1->setLatin((std::int24_t)latin);

          def1->setGridGeometryId(geometryId);
          def1->setGridGeometryName(geometryName);
          def1->initSpatialReference();

          return def1;
        }
        break;

        case T::GridProjectionValue::TransverseMercator:
          break;

        case T::GridProjectionValue::PolarStereographic:
        {
          if (c < 12)
            return nullptr;

          uint geometryId = toInt32(field[1]);
          char *geometryName = field[2];
          int ni = toInt32(field[3]);
          int nj = toInt32(field[4]);
          int longitude = C_INT(round(toDouble(field[5])*1000));
          int latitude = C_INT(round(toDouble(field[6])*1000));
          int iInc = C_INT(round(toDouble(field[7])));
          int jInc = C_INT(round(toDouble(field[8])));
          char *scanningMode = field[9];
          int orientation = C_INT(round(toDouble(field[10])*1000));
          //int laD = C_INT(round(toDouble(field[11]) * 1000000));

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
          def1->setLatitudeOfFirstGridPoint(latitude);
          def1->setLongitudeOfFirstGridPoint(longitude);
          //def1->setResolutionFlags(ResolutionFlagsSettings resolutionFlags);
          //def1->setLoV(orientation/1000);
          def1->setOrientationOfTheGrid(orientation);
          def1->setDxInMetres(iInc);
          def1->setDyInMetres(jInc);
          //def1->setProjectionCentreFlag(std::uint8_t projectionCentreFlag);
          //def1->setLatin1((std::int24_t)latin1/1000);
          //def1->setLatin2((std::int24_t)latin2/1000);
          //def1->setLatitudeOfSouthernPole((std::int24_t)latitudeOfSouthernPole/1000);
          //def1->setLongitudeOfSouthernPole((std::int24_t)longitudeOfSouthernPole/1000);

          def1->setGridGeometryId(geometryId);
          def1->setGridGeometryName(geometryName);
          def1->initSpatialReference();

          return def1;
        }
        break;

        case T::GridProjectionValue::LambertConformal:
        {
          if (c < 15)
            return nullptr;

          uint geometryId = toInt32(field[1]);
          char *geometryName = field[2];
          int ni = toInt32(field[3]);
          int nj = toInt32(field[4]);
          int longitude = C_INT(round(toDouble(field[5])*1000));
          int latitude = C_INT(round(toDouble(field[6])*1000));
          int iInc = toInt32(field[7]);
          int jInc = toInt32(field[8]);
          char *scanningMode = field[9];
          int orientation = C_INT(round(toDouble(field[10])*1000));
          int latin1 = C_INT(round(toDouble(field[11])*1000));
          int latin2 = C_INT(round(toDouble(field[12])*1000));
          int longitudeOfSouthernPole = C_INT(round(toDouble(field[13])*1000));
          int latitudeOfSouthernPole = C_INT(round(toDouble(field[14])*1000));

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
          def1->setLatitudeOfFirstGridPoint(latitude);
          def1->setLongitudeOfFirstGridPoint(longitude);
          //def1->setResolutionFlags(ResolutionFlagsSettings resolutionFlags);
          def1->setLoV(orientation);
          def1->setDxInMetres(iInc);
          def1->setDyInMetres(jInc);
          //def1->setProjectionCentreFlag(std::uint8_t projectionCentreFlag);
          def1->setLatin1(latin1);
          def1->setLatin2(latin2);
          def1->setLatitudeOfSouthernPole(latitudeOfSouthernPole);
          def1->setLongitudeOfSouthernPole(longitudeOfSouthernPole);

          def1->setGridGeometryId(geometryId);
          def1->setGridGeometryName(geometryName);
          def1->initSpatialReference();

          return def1;
        }
        break;

        case T::GridProjectionValue::ObliqueLambertConformal:
          break;

        case T::GridProjectionValue::Albers:
          break;

        case T::GridProjectionValue::Gaussian:
          break;

        case T::GridProjectionValue::RotatedGaussian:
          break;

        case T::GridProjectionValue::StretchedGaussian:
          break;

        case T::GridProjectionValue::StretchedRotatedGaussian:
          break;

        case T::GridProjectionValue::SphericalHarmonic:
          break;

        case T::GridProjectionValue::RotatedSphericalHarmonic:
          break;

        case T::GridProjectionValue::StretchedSphericalHarmonic:
          break;

        case T::GridProjectionValue::StretchedRotatedSphericalHarmonic:
          break;

        case T::GridProjectionValue::SpaceView:
          break;

        case T::GridProjectionValue::Triangular:
          break;

        case T::GridProjectionValue::Unstructured:
          break;

        case T::GridProjectionValue::EquatorialAzimuthalEquidistant:
          break;

        case T::GridProjectionValue::AzimuthRange:
          break;

        case T::GridProjectionValue::IrregularLatLon:
          break;

        case T::GridProjectionValue::LambertAzimuthalEqualArea:
          break;

        case T::GridProjectionValue::CrossSection:
          break;

        case T::GridProjectionValue::Hovmoller:
          break;

        case T::GridProjectionValue::TimeSection:
          break;

        case T::GridProjectionValue::GnomonicProjection:
          break;

        case T::GridProjectionValue::SimplePolyconicProjection:
          break;

        case T::GridProjectionValue::MillersCylindricalProjection:
          break;
      }
    }
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





GRIB2::GridDefinition* GridDef::createGrib2GridDefinition(const char *str)
{
  FUNCTION_TRACE
  try
  {
    if (str[0] == '#')
      return nullptr;

    char st[1000];
    strcpy(st,str);

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
      ushort gridProjection = toUInt16(field[0]);
      switch (gridProjection)
      {
        case T::GridProjectionValue::Unknown:
          break;

        case T::GridProjectionValue::LatLon:
        {
          if (c < 10)
            return nullptr;

          uint geometryId = toInt32(field[1]);
          char *geometryName = field[2];
          int ni = toInt32(field[3]);
          int nj = toInt32(field[4]);
          int longitude = C_INT(round(toDouble(field[5])*1000000));
          int latitude = C_INT(round(toDouble(field[6])*1000000));
          int iInc = C_INT(round(toDouble(field[7]) * 1000000));
          int jInc = C_INT(round(toDouble(field[8]) * 1000000));
          char *scanningMode = field[9];
          int lastLongitude = longitude + ni*iInc - iInc;
          int lastLatitude = latitude + nj*jInc - jInc;

          if (lastLongitude > 360000000)
            lastLongitude -= 360000000;

          if (lastLatitude > 90000000)
            lastLatitude = 180000000 - lastLatitude;

          GRIB2::LatLonImpl *def2 = new GRIB2::LatLonImpl();
          GRIB2::LatLonSettings latLon;
          GRIB2::ScanningModeSettings scanningMode2;
          GRIB2::GridSettings grid;

          GRIB2::ResolutionSettings resolution;
          resolution.setResolutionAndComponentFlags(48);
          grid.setResolution(resolution);

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

          return def2;
        }
        break;

        case T::GridProjectionValue::RotatedLatLon:
        {
          if (c < 13)
            return nullptr;

          uint geometryId = toInt32(field[1]);
          char *geometryName = field[2];
          int ni = toInt32(field[3]);
          int nj = toInt32(field[4]);
          int longitude = C_INT(round(toDouble(field[5])*1000000));
          int latitude = C_INT(round(toDouble(field[6])*1000000));
          int iInc = C_INT(round(toDouble(field[7]) * 1000000));
          int jInc = C_INT(round(toDouble(field[8]) * 1000000));
          char *scanningMode = field[9];
          int longitudeOfSouthernPole = C_INT(round(toDouble(field[10])*1000000));
          int latitudeOfSouthernPole = C_INT(round(toDouble(field[11])*1000000));
          int lastLongitude = longitude + ni*iInc - iInc;
          int lastLatitude = latitude + nj*jInc - jInc;
          int angle = round(toDouble(field[12]));
          //std::uint8_t resolutionAndComponentFlags = 48;

          if (lastLongitude > 360000000)
            lastLongitude -= 360000000;

          if (lastLatitude > 90000000)
            lastLatitude = 180000000 - lastLatitude;

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

          return def2;
        }
        break;

        case T::GridProjectionValue::StretchedLatLon:
          break;

        case T::GridProjectionValue::StretchedRotatedLatLon:
          break;

        case T::GridProjectionValue::VariableResolutionLatLon:
          break;

        case T::GridProjectionValue::VariableResolutionRotatedLatLon:
          break;

        case T::GridProjectionValue::Mercator:
          break;

        case T::GridProjectionValue::TransverseMercator:
          break;

        case T::GridProjectionValue::PolarStereographic:
        {
          if (c < 12)
            return nullptr;

          uint geometryId = toInt32(field[1]);
          char *geometryName = field[2];
          int ni = toInt32(field[3]);
          int nj = toInt32(field[4]);
          int longitude = C_INT(round(toDouble(field[5])*1000000));
          int latitude = C_INT(round(toDouble(field[6])*1000000));
          int iInc = C_INT(round(toDouble(field[7]) * 1000));
          int jInc = C_INT(round(toDouble(field[8]) * 1000));
          char *scanningMode = field[9];
          int orientation = C_INT(round(toDouble(field[10])*1000000));
          int laD = C_INT(round(toDouble(field[11]) * 1000000));

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

          def2->setResolutionAndComponentFlags(0x30);

          def2->setGridGeometryId(geometryId);
          def2->setGridGeometryName(geometryName);
          def2->initSpatialReference();

          return def2;
        }
        break;

        case T::GridProjectionValue::LambertConformal:
        {
          if (c < 15)
            return nullptr;

          uint geometryId = toInt32(field[1]);
          char *geometryName = field[2];
          int ni = toInt32(field[3]);
          int nj = toInt32(field[4]);
          int longitude = C_INT(round(toDouble(field[5])*1000000));
          int latitude = C_INT(round(toDouble(field[6])*1000000));
          int iInc = toInt32(field[7]);
          int jInc = toInt32(field[8]);
          char *scanningMode = field[9];
          int orientation = C_INT(round(toDouble(field[10])*1000000));
          int latin1 = C_INT(round(toDouble(field[11])*1000000));
          int latin2 = C_INT(round(toDouble(field[12])*1000000));
          int longitudeOfSouthernPole = C_INT(round(toDouble(field[13])*1000000));
          int latitudeOfSouthernPole = C_INT(round(toDouble(field[14])*1000000));
          int laD = 60000000;
          if (c >= 15)
            laD = C_INT(round(toDouble(field[15])*1000000));

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

          def2->setLaD(laD);
          def2->setLoV(orientation);
          def2->setDx(T::UInt32_opt(iInc*1000));
          def2->setDy(T::UInt32_opt(jInc*1000));
          //def2->setProjectionCentreFlag(std::uint8_t projectionCentreFlag);
          def2->setLatin1(T::Int32_opt(latin1));
          def2->setLatin2(T::Int32_opt(latin2));
          def2->setLatitudeOfSouthernPole(T::Int32_opt(latitudeOfSouthernPole));
          def2->setLongitudeOfSouthernPole(T::UInt32_opt(longitudeOfSouthernPole));

          GRIB2::ResolutionSettings resolution;
          resolution.setResolutionAndComponentFlags(0x30);
          def2->setResolution(resolution);

          def2->setGridGeometryId(geometryId);
          def2->setGridGeometryName(geometryName);
          def2->initSpatialReference();

          return def2;
        }
        break;

        case T::GridProjectionValue::ObliqueLambertConformal:
          break;

        case T::GridProjectionValue::Albers:
          break;

        case T::GridProjectionValue::Gaussian:
          break;

        case T::GridProjectionValue::RotatedGaussian:
          break;

        case T::GridProjectionValue::StretchedGaussian:
          break;

        case T::GridProjectionValue::StretchedRotatedGaussian:
          break;

        case T::GridProjectionValue::SphericalHarmonic:
          break;

        case T::GridProjectionValue::RotatedSphericalHarmonic:
          break;

        case T::GridProjectionValue::StretchedSphericalHarmonic:
          break;

        case T::GridProjectionValue::StretchedRotatedSphericalHarmonic:
          break;

        case T::GridProjectionValue::SpaceView:
          break;

        case T::GridProjectionValue::Triangular:
          break;

        case T::GridProjectionValue::Unstructured:
          break;

        case T::GridProjectionValue::EquatorialAzimuthalEquidistant:
          break;

        case T::GridProjectionValue::AzimuthRange:
          break;

        case T::GridProjectionValue::IrregularLatLon:
          break;

        case T::GridProjectionValue::LambertAzimuthalEqualArea:
        {
          if (c < 12)
            return nullptr;

          uint geometryId = toInt32(field[1]);
          char *geometryName = field[2];
          int ni = toInt32(field[3]);
          int nj = toInt32(field[4]);
          int longitude = C_INT(round(toDouble(field[5])*1000000));
          int latitude = C_INT(round(toDouble(field[6])*1000000));
          int iInc = toInt32(field[7]);
          int jInc = toInt32(field[8]);
          char *scanningMode = field[9];
          int standardParallel = C_INT(round(toDouble(field[10])*1000000));
          int centralLongitude = C_INT(round(toDouble(field[11])*1000000));

          GRIB2::LambertAzimuthalEqualAreaImpl *def2 = new GRIB2::LambertAzimuthalEqualAreaImpl();
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

          def2->setNumberOfPointsAlongXAxis(T::UInt32_opt(ni));
          def2->setNumberOfPointsAlongYAxis(T::UInt32_opt(nj));
          def2->setLatitudeOfFirstGridPoint(T::Int32_opt(latitude));
          def2->setLongitudeOfFirstGridPoint(T::Int32_opt(longitude));

          def2->setStandardParallelInMicrodegrees(T::Int32_opt(standardParallel));
          def2->setCentralLongitudeInMicrodegrees(T::Int32_opt(centralLongitude));
          def2->setXDirectionGridLengthInMillimetres(T::UInt32_opt(iInc*1000));
          def2->setYDirectionGridLengthInMillimetres(T::UInt32_opt(jInc*1000));

          def2->setResolutionAndComponentFlags(0x30);
          def2->setGridGeometryId(geometryId);
          def2->setGridGeometryName(geometryName);
          def2->initSpatialReference();

          return def2;
        }
        break;

        case T::GridProjectionValue::CrossSection:
          break;

        case T::GridProjectionValue::Hovmoller:
          break;

        case T::GridProjectionValue::TimeSection:
          break;

        case T::GridProjectionValue::GnomonicProjection:
          break;

        case T::GridProjectionValue::SimplePolyconicProjection:
          break;

        case T::GridProjectionValue::MillersCylindricalProjection:
          break;
      }
    }
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





short GridDef::getPreferredInterpolationMethodByUnits(const std::string& originalUnits)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    for (auto it = mGrib_unitDef_records.begin(); it != mGrib_unitDef_records.end(); ++it)
    {
      if (it->mOriginalUnits == originalUnits)
        return it->mPreferredAreaInterpolationMethod;
    }

    return T::AreaInterpolationMethod::Linear;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDef::getPreferredUnits(const std::string& originalUnits)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    for (auto it = mGrib_unitDef_records.begin(); it != mGrib_unitDef_records.end(); ++it)
    {
      if (it->mOriginalUnits == originalUnits)
        return it->mPreferredUnits;
    }

    return originalUnits;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





FmiParameterId_grib* GridDef::getGribDefByFmiId(T::ParamId fmiParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_parametersFromGrib_records.begin(); it != mFmi_parametersFromGrib_records.end(); ++it)
    {
      if (strcasecmp(it->mFmiParameterId.c_str(),fmiParamId.c_str()) == 0)
        return &(*it);
    }
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





FmiParameterId_grib1* GridDef::getGrib1DefByFmiId(T::ParamId fmiParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_parametersFromGrib1_records.begin(); it != mFmi_parametersFromGrib1_records.end(); ++it)
    {
      if (strcasecmp(it->mFmiParameterId.c_str(),fmiParamId.c_str()) == 0)
        return &(*it);
    }
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




FmiParameterId_grib2* GridDef::getGrib2DefByFmiId(T::ParamId fmiParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_parametersFromGrib2_records.begin(); it != mFmi_parametersFromGrib2_records.end(); ++it)
    {
      if (strcasecmp(it->mFmiParameterId.c_str(),fmiParamId.c_str()) == 0)
        return &(*it);
    }
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




T::ParamId GridDef::getGribParameterId(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    auto productSection =  message.getProductSection();
    if (productSection == nullptr)
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
        requiredPoints += 3;
        if (p->mIndicatorOfParameter == productSection->getIndicatorOfParameter())
          points += 3;
      }

      if (p->mIndicatorOfTypeOfLevel)
      {
        requiredPoints++;
        if (p->mIndicatorOfTypeOfLevel == productSection->getIndicatorOfTypeOfLevel())
          points++;
      }

      if (p->mTable2Version)
      {
        requiredPoints += 3;
        if (p->mTable2Version == productSection->getTableVersion())
          points += 3;
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::ParamId GridDef::getGribParameterId(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    T::ParamId paramId;

    GRIB2::IndicatorSect_sptr indicatorSection = message.getIndicatorSection();
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGrib1LevelDef(uint fmiLevelId,uint generatingProcessId,uint centre,FmiLevelId_grib& def)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_levelsFromGrib1_records.begin(); it != mFmi_levelsFromGrib1_records.end(); ++it)
    {
      if (it->mFmiLevelId == fmiLevelId  &&  it->mGeneratingProcessIdentifier == generatingProcessId  &&  it->mCentre == centre)
      {
        def = *it;
        return true;
      }
    }
    return false;

  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGrib1LevelDef(uint fmiLevelId,FmiLevelId_grib& def)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_levelsFromGrib1_records.begin(); it != mFmi_levelsFromGrib1_records.end(); ++it)
    {
      if (it->mFmiLevelId == fmiLevelId)
      {
        def = *it;
        return true;
      }
    }
    return false;

  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getGrib2LevelDef(uint fmiLevelId,FmiLevelId_grib& def)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_levelsFromGrib2_records.begin(); it != mFmi_levelsFromGrib2_records.end(); ++it)
    {
      if (it->mFmiLevelId == fmiLevelId)
      {
        def = *it;
        return true;
      }
    }
    return false;

  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
          return it->mGribLevelId;
        }
      }
    }

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
          return it->mGribLevelId;
        }
      }
    }

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint GridDef::countParameterMatchPoints(GRIB2::Message& message,const Grib2ParameterDef& p)
{
  FUNCTION_TRACE
  try
  {
    auto productSection = message.getProductSection();
    if (productSection == nullptr)
      return 0;

    GRIB2::ProductDefinition *productDefinition = productSection->getProductDefinition();
    if (productDefinition == nullptr)
      return 0;

    GRIB2::IdentifSect_sptr identificationSection =  message.getIdentificationSection();
    if (identificationSection == nullptr)
      return 0;

    const GRIB2::ParameterSettings *s = productDefinition->getParameter();
    const GRIB2::PostprocSettings *pp = productDefinition->getPostproc();
    const GRIB2::HorizontalSettings *h = productDefinition->getHorizontal();
    const GRIB2::StatisticalSettings *stat = productDefinition->getStatistical();

    uint matchPoints = 0;

    if (p.mCentre)
    {
      if (p.mCentre != identificationSection->getCentre())
        return 0;

      matchPoints++;
    }

    if (s != nullptr)
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

    if (pp != nullptr)
    {
      if (pp->getParameterCategory())
      {
        if (p.mParameterCategory != *pp->getParameterCategory())
          return 0;

        matchPoints++;
      }
      else
      {
        return 0;
      }

      if (pp->getParameterNumber())
      {
        if (p.mParameterNumber != *pp->getParameterNumber())
          return 0;

        matchPoints++;
      }
      else
      {
        return 0;
      }

      if (p.mTypeOfGeneratingProcess)
      {
        if (!pp->getTypeOfGeneratingProcess())
          return 0;

        if (p.mTypeOfGeneratingProcess != *pp->getTypeOfGeneratingProcess())
          return 0;

        matchPoints++;
      }
    }


    if (stat != nullptr)
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

    if (h != nullptr)
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
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





T::ParamId GridDef::getFmiParameterId(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    T::ParamId gribId = getGribParameterId(message);
    if (!gribId.empty())
    {
      auto r =  getFmiParameterIdByGribId(gribId);
      if (r != nullptr)
      {
        return r->mFmiParameterId;
      }
    }

    auto productSection =  message.getProductSection();
    if (productSection == nullptr)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::ParamId GridDef::getFmiParameterId(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    T::ParamId gribId = getGribParameterId(message);
    if (!gribId.empty())
    {
      auto r =  getFmiParameterIdByGribId(gribId);
      if (r != nullptr)
        return r->mFmiParameterId;
    }


    GRIB2::IndicatorSect_sptr indicatorSection = message.getIndicatorSection();
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
      if (p->mDiscipline == *(indicatorSection->getDiscipline()))
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint GridDef::countParameterMatchPoints(GRIB2::Message& message,const FmiParameterId_grib2& p)
{
  FUNCTION_TRACE
  try
  {
    auto productSection = message.getProductSection();
    if (productSection == nullptr)
      return 0;

    GRIB2::ProductDefinition *productDefinition = productSection->getProductDefinition();
    if (productDefinition == nullptr)
      return 0;

    GRIB2::IdentifSect_sptr identificationSection =  message.getIdentificationSection();
    if (identificationSection == nullptr)
      return 0;

    const GRIB2::ParameterSettings *s = productDefinition->getParameter();
    const GRIB2::HorizontalSettings *h = productDefinition->getHorizontal();

    uint matchPoints = 0;

    if (p.mGeneratingProcessIdentifier != 0)
    {
      if (p.mGeneratingProcessIdentifier == *productSection->getGeneratingProcessIdentifier())
        matchPoints++;
    }

    if (p.mCentre != 0)
    {
      if (p.mCentre == *identificationSection->getCentre())
        matchPoints++;
      else
        return 0;
    }

    if (s != nullptr)
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

    if (h != nullptr)
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
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





T::ParamLevelId GridDef::getFmiLevelId(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto productSection =  message.getProductSection();
    if (productSection == nullptr)
      return 0;

    for (auto it = mFmi_levelsFromGrib1_records.begin(); it != mFmi_levelsFromGrib1_records.end(); ++it)
    {
      if (it->mGeneratingProcessIdentifier == productSection->getGeneratingProcessIdentifier() &&
          it->mCentre == productSection->getCentre() &&
          it->mGribLevelId == productSection->getIndicatorOfTypeOfLevel())
      {
        return it->mFmiLevelId;
      }
    }

    for (auto it = mFmi_levelsFromGrib1_records.begin(); it != mFmi_levelsFromGrib1_records.end(); ++it)
    {
      if (it->mGribLevelId == productSection->getIndicatorOfTypeOfLevel())
      {
        return it->mFmiLevelId;
      }
    }
    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::ParamLevelId GridDef::getFmiLevelId(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto productSection = message.getProductSection();
    if (productSection == nullptr)
      return 0;

    GRIB2::IdentifSect_sptr identificationSection =  message.getIdentificationSection();
    if (identificationSection == nullptr)
      return 0;

    for (auto it = mFmi_levelsFromGrib2_records.begin(); it != mFmi_levelsFromGrib2_records.end(); ++it)
    {
      if (it->mGeneratingProcessIdentifier == *productSection->getGeneratingProcessIdentifier() &&
          it->mCentre == *identificationSection->getCentre() &&
          it->mGribLevelId == message.getGridParameterLevelId())
      {
        return it->mFmiLevelId;
      }
    }

    for (auto it = mFmi_levelsFromGrib2_records.begin(); it != mFmi_levelsFromGrib2_records.end(); ++it)
    {
      if (it->mGribLevelId == message.getGridParameterLevelId())
      {
        return it->mFmiLevelId;
      }
    }
    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::ParamId GridDef::getFmiParameterIdByFmiName(const std::string& fmiParamName)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto p = getFmiParameterDefByName(fmiParamName);
    if (p != nullptr)
      return p->mFmiParameterId;

    return std::string("");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





FmiParamId_grib_cptr GridDef::getFmiParameterIdByGribId(T::ParamId gribParamId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_parametersFromGrib_records.begin(); it != mFmi_parametersFromGrib_records.end(); ++it)
    {
      if (strcasecmp(it->mGribParameterId.c_str(),gribParamId.c_str()) == 0)
        return &(*it);
    }
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getNewbaseParameterDefByFmiId(T::ParamId fmiParamId,NewbaseParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    auto p = getNewbaseParameterIdByFmiId(fmiParamId);
    if (p == nullptr)
      return false;

    auto n = getNewbaseParameterDefById(p->mNewbaseParameterId);
    if (n == nullptr)
      return false;

    paramDef = *n;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getNewbaseParameterDefByName(const std::string& newbaseParamName,NewbaseParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    auto p = GridDef::getNewbaseParameterDefByName(newbaseParamName);
    if (p == nullptr)
      return false;

    paramDef = *p;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getNewbaseParameterMappingByFmiId(T::ParamId fmiParamId,FmiParameterId_newbase& paramMapping)
{
  try
  {
    FmiParamId_newbase_cptr p = getNewbaseParameterIdByFmiId(fmiParamId);
    if (p != nullptr)
    {
      paramMapping = *p;
      return true;
    }
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getNewbaseParameterDefById(T::ParamId newbaseParamId,NewbaseParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    auto n = getNewbaseParameterDefById(newbaseParamId);
    if (n == nullptr)
      return false;

    paramDef = *n;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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

    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





FmiParamDef_cptr GridDef::getFmiParameterDefByGribId(T::ParamId gribParamId)
{
  FUNCTION_TRACE
  try
  {
    auto p = getFmiParameterIdByGribId(gribParamId);
    if (p)
      return getFmiParameterDefById(p->mFmiParameterId);

    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





FmiParamDef_cptr GridDef::getFmiParameterDefByName(const std::string& fmiParamName)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_parameterDef_records.begin(); it != mFmi_parameterDef_records.end(); ++it)
    {
      if (strcasecmp(it->mParameterName.c_str(),fmiParamName.c_str()) == 0)
        return &(*it);
    }
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getFmiParameterDefById(T::ParamId fmiParamId,FmiParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getFmiParameterDefById(fmiParamId);
    if (def == nullptr)
      return false;

    paramDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getFmiParameterDefByNewbaseId(T::ParamId newbaseParamId,FmiParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getFmiParameterDefByNewbaseId(newbaseParamId);
    if (def == nullptr)
      return false;

    paramDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getFmiParameterDefByGribId(T::ParamId gribParamId,FmiParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getFmiParameterDefByGribId(gribParamId);
    if (def == nullptr)
      return false;

    paramDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getFmiParameterDefByName(const std::string& fmiParamName,FmiParameterDef& paramDef)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto def = getFmiParameterDefByName(fmiParamName);
    if (def == nullptr)
      return false;

    paramDef = *def;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDef::getFmiParameterName(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto p = getFmiParameterDefById(message.getFmiParameterId());
    if (p == nullptr)
      return std::string("");

    return p->mParameterName;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDef::getFmiParameterName(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto p = getFmiParameterDefById(message.getFmiParameterId());
    if (p == nullptr)
      return std::string("");

    return p->mParameterName;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDef::getFmiParameterDescription(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto p = getFmiParameterDefById(message.getFmiParameterId());
    if (p == nullptr)
      return std::string("");

    return p->mParameterDescription;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDef::getFmiParameterDescription(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto p = getFmiParameterDefById(message.getFmiParameterId());
    if (p == nullptr)
      return std::string("");

    return p->mParameterDescription;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDef::getFmiParameterUnits(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto p = getFmiParameterDefById(message.getFmiParameterId());
    if (p == nullptr)
      return std::string("");

    return p->mParameterUnits;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDef::getFmiParameterUnits(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto p = getFmiParameterDefById(message.getFmiParameterId());
    if (p == nullptr)
      return std::string("");

    return p->mParameterUnits;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





short GridDef::getFmiParameterInterpolationMethod(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto p = getFmiParameterDefById(message.getFmiParameterId());
    if (p == nullptr)
      return T::AreaInterpolationMethod::None;

    return p->mAreaInterpolationMethod;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





short GridDef::getFmiParameterInterpolationMethod(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto p = getFmiParameterDefById(message.getFmiParameterId());
    if (p == nullptr)
      return T::AreaInterpolationMethod::None;

    return p->mAreaInterpolationMethod;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





FmiProducerId_grib_cptr GridDef::getFmiProducerByName(const std::string& fmiProducerName)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_producersFromGrib_records.begin(); it != mFmi_producersFromGrib_records.end(); ++it)
    {
      if (strcasecmp(it->mProducerName.c_str(),fmiProducerName.c_str()) == 0)
        return &(*it);
    }
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





FmiProducerId_grib_cptr GridDef::getFmiProducerByFmiId(uint fmiProducerId)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mFmi_producersFromGrib_records.begin(); it != mFmi_producersFromGrib_records.end(); ++it)
    {
      if (it->mProducerId == fmiProducerId)
        return &(*it);
    }
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getFmiProducerByName(const std::string& fmiProducerName,FmiProducerId_grib& producer)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto p = getFmiProducerByName(fmiProducerName);
    if (p == nullptr)
      return false;

    producer = *p;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDef::getFmiProducerByFmiId(uint fmiProducerId,FmiProducerId_grib& producer)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto p = getFmiProducerByFmiId(fmiProducerId);
    if (p == nullptr)
      return false;

    producer = *p;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





NewbaseParamDef_cptr GridDef::getNewbaseParameterDefByName(const std::string& newbaseParamName)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mNewbase_parameterDef_records.begin(); it != mNewbase_parameterDef_records.end(); ++it)
    {
      if (strcasecmp(it->mParameterName.c_str(),newbaseParamName.c_str()) == 0)
        return &(*it);
    }
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::ParamId GridDef::getNewbaseParameterId(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto p = getNewbaseParameterIdByFmiId(message.getFmiParameterId());
    if (p == nullptr)
      return std::string("");

    return p->mNewbaseParameterId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::ParamId GridDef::getNewbaseParameterId(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto p = getNewbaseParameterIdByFmiId(message.getFmiParameterId());
    if (p == nullptr)
      return std::string("");

    return p->mNewbaseParameterId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDef::getNewbaseParameterName(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto p = getNewbaseParameterIdByFmiId(message.getFmiParameterId());
    if (p == nullptr)
      return std::string("");

    auto n = getNewbaseParameterDefById(p->mNewbaseParameterId);
    if (n == nullptr)
      return std::string("");

    return n->mParameterName;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDef::getNewbaseParameterName(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    updateCheck();
    AutoReadLock lock(&mModificationLock);

    auto p = getNewbaseParameterIdByFmiId(message.getFmiParameterId());
    if (p == nullptr)
      return std::string("");

    auto n = getNewbaseParameterDefById(p->mNewbaseParameterId);
    if (n == nullptr)
      return std::string("");

    return n->mParameterName;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDef::getCdmParameterId(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    auto productSection =  message.getProductSection();
    if (productSection == nullptr)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDef::getCdmParameterId(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    auto productSection =  message.getProductSection();
    if (productSection == nullptr)
      return std::string("");

    GRIB2::IndicatorSect_sptr indicatorSection = message.getIndicatorSection();
    if (!indicatorSection)
      return std::string("");

    char tmp[200];
    char *p = (char*)tmp;


    p += sprintf(p,"VAR_%u-%u-%u",
        *(indicatorSection->getDiscipline()),
        *(productSection->getGribParameterCategory()),
        *(productSection->getGribParameterNumber()));

    LevelDef levelDef;
    if (getGrib2LevelDef(message.getGridParameterLevelId(),levelDef))
    {
      p += sprintf(p,"_L%u",message.getGridParameterLevelId());
      // p += sprintf(p,"_%u",message.getGridParameterLevel());
    }


    GRIB2::ProductDefinition *productDef = productSection->getProductDefinition();
    if (productDef != nullptr)
    {
      const GRIB2::StatisticalSettings *stat = productDef->getStatistical();
      if (stat != nullptr)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDef::getCdmParameterName(GRIB1::Message& message)
{
  FUNCTION_TRACE
  try
  {
    auto productSection =  message.getProductSection();
    if (productSection == nullptr)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDef::getCdmParameterName(GRIB2::Message& message)
{
  FUNCTION_TRACE
  try
  {
    auto productSection =  message.getProductSection();
    if (productSection == nullptr)
      return std::string("");

    GRIB2::IndicatorSect_sptr indicatorSection = message.getIndicatorSection();
    if (!indicatorSection)
      return std::string("");

    char tmp[200];
    tmp[0] = '\0';
    char *p = (char*)tmp;

    GribParameterDef def;
    if (getGribParamDef(*(indicatorSection->getDiscipline()),*productSection->getGribParameterCategory(),*productSection->getGribParameterNumber(),def)
      &&  def.mParameterName.length() > 0)
    {
      p += sprintf(p,"%s",def.mParameterName.c_str());
    }
    else
    {
      p += sprintf(p,"VAR_%u-%u-%u",
          *(indicatorSection->getDiscipline()),
          *(productSection->getGribParameterCategory()),
          *(productSection->getGribParameterNumber()));
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
    if (productDef != nullptr)
    {
      const GRIB2::StatisticalSettings *stat = productDef->getStatistical();
      if (stat != nullptr)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




}  // namespace GRIB2
}  // namespace SmartMet
