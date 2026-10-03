#include "QueryDataFile.h"
#include "../common/ShowFunction.h"
#include "../grid/GridFile.h"
#include "../grid/PrintOptions.h"
#include "../common/GeneralFunctions.h"
#include "../identification/GridDef.h"
#include <macgyver/StringConversion.h>
#include <newbase/NFmiCmdLine.h>
#include <newbase/NFmiEnumConverter.h>
#include <newbase/NFmiFastQueryInfo.h>
#include <newbase/NFmiFileString.h>
#include <newbase/NFmiFileSystem.h>
#include <newbase/NFmiGrid.h>
#include <newbase/NFmiSettings.h>
#include <newbase/NFmiStringList.h>
#include <newbase/NFmiStreamQueryData.h>

#include <algorithm>
#include <ctime>
#include <cmath>
#include <list>
#include <mutex>
#include <set>
#include <string>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{
namespace QueryData
{

/*! \brief The constructor of the class. */

QueryDataFile::QueryDataFile(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    mFilename = filename;
    mQueryDataFile = new NFmiQueryData(mFilename,true);
    mFastQueryInfo = new NFmiFastQueryInfo(mQueryDataFile);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

QueryDataFile::~QueryDataFile()
{
  if (mFastQueryInfo != nullptr)
    delete mFastQueryInfo;

  if (mQueryDataFile != nullptr)
    delete mQueryDataFile;
}





/*! \brief Resolves the FMI grid geometry id from the QueryData area and grid. */

uint QueryDataFile::getGeometryId()
{
  if (mFastQueryInfo == nullptr)
    return 0;

  const NFmiArea *area = mFastQueryInfo->Area();
  const NFmiGrid *grid = mFastQueryInfo->Grid();

  if (area == nullptr)
  {
    std::cout << "ERROR: The querydata has no area!\n";
    return 0;
  }

  const auto &sr = *area->SpatialReference();

  OGRErr err = OGRERR_NONE;
  double false_eastening = sr.GetNormProjParm(SRS_PP_FALSE_EASTING,0,&err);
  double false_northing = sr.GetNormProjParm(SRS_PP_FALSE_NORTHING,0,&err);


  UInt64 classid = area->ClassId();
  const auto rect = area->WorldRect();

  std::vector<std::string> fmiArea;
  std::vector<float> part1;
  std::vector<float> part2;
  splitString(area->AreaStr(),':',fmiArea);
  if (fmiArea.size() == 2)
  {
    splitString(fmiArea[0],',',part1);
    splitString(fmiArea[1],',',part2);
  }

  int rows = 0;
  int cols = 0;
  double width = 0;   // metric width and height of the grid
  double height = 0;

  if (grid)
  {
    cols = grid->XNumber();
    rows = grid->YNumber();
    width = area->WorldXYWidth();
    height = area->WorldXYHeight();
  }

  if (cols < 2 || rows < 2)
    return 0;

  // The geometry is identified by its geometry string in the configuration. Two strings are
  // made: the exact one, with the grid step rounded only to the precision the configuration
  // stores, and the legacy one this method used to make (metric steps truncated to whole metres,
  // latlon steps divided by the number of columns instead of the number of intervals). Old
  // configuration lines made from the legacy string still match, but their coordinates drift
  // from the data, so a warning tells which line to replace.

  std::string exactString;
  std::string legacyString;
  bool earthInString = false;  // the transverse mercator string includes the earth axes
  const char *sm = "+x+y";
  char buf[4000];

  auto metricStrings = [&](const char *fmt, double precision, auto&&... params)
  {
    const double dxe = std::round(std::fabs(width / (cols-1)) * precision) / precision;
    const double dye = std::round(std::fabs(height / (rows-1)) * precision) / precision;
    const double dxl = static_cast<int>(width / (cols-1));
    const double dyl = static_cast<int>(height / (rows-1));
    snprintf(buf,sizeof(buf),fmt,cols,rows,area->BottomLeftLatLon().X(),area->BottomLeftLatLon().Y(),dxe,dye,sm,params...);
    exactString = buf;
    snprintf(buf,sizeof(buf),fmt,cols,rows,area->BottomLeftLatLon().X(),area->BottomLeftLatLon().Y(),std::fabs(dxl),std::fabs(dyl),sm,params...);
    legacyString = buf;
  };

  switch (classid)
  {
    case kNFmiEquiDistArea:
      break;

    case kNFmiGnomonicArea:
      break;

    case kNFmiYKJArea:
    case kNFmiGdalArea:
    {
      // The configuration stores the step in centimetres
      metricStrings("8;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;27.000000;0.000000;%.6f;%.6f;%.6f;%.6f;description",
          100.0,false_eastening,false_northing,sr.GetSemiMajor(),sr.GetSemiMinor());
      earthInString = true;
    }
    break;

    case kNFmiStereographicArea:
    {
      // The configuration stores the step in millimetres
      if (part1.size() >= 4)
        metricStrings("9;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;description",1000.0,part1[1],part1[3]);
    }
    break;

    case kNFmiLambertConformalConicArea:
    {
      if (part1.size() >= 4)
      {
        double spole_x = 0.0;
        double spole_y = -90.0;
        // The configuration stores the step in whole metres, so the legacy string is the exact one
        metricStrings("10;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;%.6f;%.6f;%.6f;%.6f;description",
            1.0,part1[1],part1[2],part1[3],spole_x,spole_y,part1[2]);
        exactString = legacyString;
      }
    }
    break;

    case kNFmiKKJArea:
      break;

    case kNFmiPKJArea:
      break;

    case kNFmiLatLonArea:
    {
      double w = area->BottomRightLatLon().X() - area->BottomLeftLatLon().X();
      if (w < 0)
        w += 360;
      const double h = area->TopLeftLatLon().Y() - area->BottomLeftLatLon().Y();
      snprintf(buf,sizeof(buf),"%d;id;name;%u;%u;%.6f;%.6f;%.6f;%.6f;%s;description",
        T::GridProjectionValue::LatLon,cols,rows,area->BottomLeftLatLon().X(),area->BottomLeftLatLon().Y(),
        std::fabs(w/(cols-1)),std::fabs(h/(rows-1)),sm);
      exactString = buf;

      float dxx = (area->BottomRightLatLon().X() - area->BottomLeftLatLon().X()) / (float)(cols);
      float dyy = (area->TopLeftLatLon().Y() - area->BottomLeftLatLon().Y()) / (float)(rows-1);
      snprintf(buf,sizeof(buf),"%d;id;name;%u;%u;%.6f;%.6f;%.6f;%.6f;%s;description",
        T::GridProjectionValue::LatLon,cols,rows,area->BottomLeftLatLon().X(),area->BottomLeftLatLon().Y(),
        fabs(dxx),fabs(dyy),sm);
      legacyString = buf;
    }
    break;

    case kNFmiRotatedLatLonArea:
    {
      if (part1.size() >= 3)
      {
        double rotLat1 = 0;
        double rotLon1 = 0;
        double rotLat2 = 0;
        double rotLon2 = 0;

        latlon_to_rotatedLatlon(area->BottomLeftLatLon().Y(),area->BottomLeftLatLon().X(),part1[1],part1[2],rotLat1,rotLon1);
        latlon_to_rotatedLatlon(area->TopRightLatLon().Y(),area->TopRightLatLon().X(),part1[1],part1[2],rotLat2,rotLon2);

        float angle = 0;
        snprintf(buf,sizeof(buf),"%d;id;name;%u;%u;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;%.6f;description",
            T::GridProjectionValue::RotatedLatLon,cols,rows,rotLon1,rotLat1,
            std::fabs((rotLon2 - rotLon1) / (cols-1)),std::fabs((rotLat2 - rotLat1) / (rows-1)),sm,part1[2],part1[1],angle);
        exactString = buf;

        float dxx = (rotLon2 - rotLon1) / (float)(cols);
        float dyy = (rotLat2 - rotLat1) / (float)(rows-1);
        snprintf(buf,sizeof(buf),"%d;id;name;%u;%u;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;%.6f;description",
            T::GridProjectionValue::RotatedLatLon,cols,rows,rotLon1,rotLat1,fabs(dxx),fabs(dyy),sm,part1[2],part1[1],angle);
        legacyString = buf;
      }
    }
    break;

    case kNFmiMercatorArea:
      break;
  }

  if (!exactString.empty())
  {
    // The configuration line for the exact geometry, including the earth axes of the data
    std::string configLine = exactString;
    if (!earthInString)
    {
      snprintf(buf,sizeof(buf),";%.10g;%.10g;description",sr.GetSemiMajor(),sr.GetSemiMinor());
      configLine = exactString.substr(0,exactString.rfind(";description")) + buf;
    }

    bool legacy = false;
    auto def = Identification::gridDef.getGrib2DefinitionByGeometryString(exactString);
    if (!def && legacyString != exactString)
    {
      def = Identification::gridDef.getGrib2DefinitionByGeometryString(legacyString);
      legacy = (def != nullptr);
    }

    if (!def)
    {
      std::cout << "** MISSING GEOMETRY **\n";
      std::cout << "Add the following geometry into the geometry definition\n";
      std::cout << "file (=> fill id,name and description fields) :\n\n";
      std::cout << configLine << "\n\n";
      return 0;
    }

    const auto geometryId = def->getGridGeometryId();

    // The configured earth axes must be those of the data, otherwise the coordinates drift.
    // A configuration line without them uses the GRIB default sphere.
    double semiMajor = def->getEarthSemiMajor();
    if (semiMajor == 0)
      semiMajor = 6367470;

    const bool earthMismatch = (!earthInString && std::fabs(semiMajor - sr.GetSemiMajor()) > 1);

    if (legacy || earthMismatch)
    {
      static std::mutex warnedMutex;
      static std::set<T::GeometryId> warned;
      std::lock_guard<std::mutex> lock(warnedMutex);
      if (warned.insert(geometryId).second)
      {
        std::string line = configLine;
        auto p = line.find(";id;name;");
        if (p != std::string::npos)
        {
          std::string name = "name";
          Identification::gridDef.getGeometryNameById(geometryId,name);
          line.replace(p,9,";" + std::to_string(geometryId) + ";" + name + ";");
        }
        std::cout << "** INEXACT GEOMETRY " << geometryId << " **\n";
        if (legacy)
          std::cout << "The configured grid step of the geometry is not exact (it was made by an older version).\n";
        if (earthMismatch)
          std::cout << "The configured earth radius of the geometry is " << semiMajor << ", the data uses " << sr.GetSemiMajor() << ".\n";
        std::cout << "The coordinates drift from those of the data. Replace the geometry definition with:\n\n";
        std::cout << line << "\n\n";
      }
    }

    return geometryId;
  }

  std::cout << "****************** PROJECTION NOT SUPPORTED *********************** \n\n";

  std::cout << "projection\t\t= " << area->ClassName() << "\n";
  std::cout << "top left lonlat\t\t= " << area->TopLeftLatLon().X() << ',' << area->TopLeftLatLon().Y() << "\n";
  std::cout << "top right lonlat\t= " << area->TopRightLatLon().X() << ',' << area->TopRightLatLon().Y() << "\n";
  std::cout << "bottom left lonlat\t= " << area->BottomLeftLatLon().X() << ',' << area->BottomLeftLatLon().Y() << "\n";
  std::cout << "bottom right lonlat\t= " << area->BottomRightLatLon().X() << ',' << area->BottomRightLatLon().Y() << "\n";
  std::cout << "center lonlat\t\t= " << area->CenterLatLon().X() << ',' << area->CenterLatLon().Y() << "\n";
  std::cout << std::setprecision(9) << "bbox\t\t\t= [" << rect.Left() << " " << rect.Right() << " "
            << std::min(rect.Bottom(), rect.Top()) << " " << std::max(rect.Bottom(), rect.Top()) << "]"
            << std::setprecision(6) << "\n\n";

  std::cout << "fmiarea\t= " << area->AreaStr() << "\n\n";

  std::cout << "top\t= " << area->Top() << "\n";
  std::cout << "left\t= " << area->Left() << "\n";
  std::cout << "right\t= " << area->Right() << "\n";
  std::cout << "bottom\t= " << area->Bottom() << "\n\n";

  std::cout << "xywidth\t\t= " << area->WorldXYWidth() / 1000.0 << " km\n";
  std::cout << "xyheight\t= " << area->WorldXYHeight() / 1000.0 << " km\n";
  std::cout << "aspectratio\t= " << area->WorldXYAspectRatio() << "\n\n";

  std::cout << "******************************************************************* \n\n";

  return 0;
}




/*
T::ParamValue QueryDataFile::getGridValue(uint paramIndex,uint levelIndex,uint timeIndex,uint grid_i,uint grid_j) const
{
  FUNCTION_TRACE
  try
  {
    if (mFastQueryInfo == nullptr)
      return ParamValueMissing;

    std::size_t locationIndex = mFastQueryInfo->PeekLocationIndex(grid_i,grid_j);
    std::size_t idx = mFastQueryInfo->Index(paramIndex,locationIndex,levelIndex,timeIndex);

    float val = mFastQueryInfo->PeekValue(idx);
    if (val == 32700.0)
      return ParamValueMissing;

    return val;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}
*/



/*! \brief Iterates all parameters, levels and times of the QueryData and produces MessageInfo entries. */

void QueryDataFile::read(MessageInfoVec& messageInfoList)
{
  try
  {
    const NFmiGrid *grid = mFastQueryInfo->Grid();
    if (!grid)
      return;

    int cols = grid->XNumber();
    int rows = grid->YNumber();
    int geometryId = getGeometryId();

    bool pInd = mFastQueryInfo->FirstParam(true);
    while (pInd)
    {
      int parameterId = mFastQueryInfo->Param().GetParamIdent();
      bool lInd = mFastQueryInfo->FirstLevel();
      while (lInd)
      {
        const NFmiLevel &lev = *mFastQueryInfo->Level();

        int levelId = Identification::gridDef.getFmiLevelIdByNewbaseLevelId(lev.LevelTypeId());
        int level = lev.LevelValue();
        if (level == 32700)
          level = 0;

        bool tInd = mFastQueryInfo->FirstTime();
        while (tInd)
        {
          NFmiMetTime mt = mFastQueryInfo->ValidTime();
          time_t utcTime = utcTimeToTimeT(mt.GetYear(),mt.GetMonth(),mt.GetDay(),mt.GetHour(),mt.GetMin(),mt.GetSec());

          MessageInfo info;
          info.mColumns = cols;
          info.mRows = rows;
          info.mParameterIndex = mFastQueryInfo->ParamIndex();
          info.mLevelIndex = mFastQueryInfo->LevelIndex();
          info.mTimeIndex = mFastQueryInfo->TimeIndex();
          info.mNewbaseId = parameterId;
          info.mParameterLevelId = levelId;
          info.mParameterLevel = level;
          info.mForecastTimeT = utcTime;
          info.mGeometryId = geometryId;
          messageInfoList.push_back(info);

          tInd = mFastQueryInfo->NextTime();
        }
        lInd = mFastQueryInfo->NextLevel();
      }
      pInd = mFastQueryInfo->NextParam(true);
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param stream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void QueryDataFile::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "QueryDataFile\n";
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




}
}
