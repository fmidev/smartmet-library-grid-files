#include "QueryDataFile.h"
#include "../common/ShowFunction.h"
#include "../grid/GridFile.h"
#include "../grid/PrintOptions.h"
#include "../common/GeneralFunctions.h"
#include "../identification/GridDef.h"
#include <macgyver/StringConversion.h>
#include <newbase/NFmiCmdLine.h>
#include <newbase/NFmiEnumConverter.h>
#include <newbase/NFmiEquidistArea.h>
#include <newbase/NFmiFastQueryInfo.h>
#include <newbase/NFmiFileString.h>
#include <newbase/NFmiFileSystem.h>
#include <newbase/NFmiGnomonicArea.h>
#include <newbase/NFmiGrid.h>
#include <newbase/NFmiKKJArea.h>
#include <newbase/NFmiLatLonArea.h>
#include <newbase/NFmiMercatorArea.h>
#include <newbase/NFmiPKJArea.h>
#include <newbase/NFmiRotatedLatLonArea.h>
#include <newbase/NFmiSettings.h>
#include <newbase/NFmiStereographicArea.h>
#include <newbase/NFmiStringList.h>
#include <newbase/NFmiYKJArea.h>
#include <newbase/NFmiStreamQueryData.h>

#include <algorithm>
#include <ctime>
#include <list>
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

  unsigned long classid = area->ClassId();
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
  int dx = 0;
  int dy = 0;
  char projectionString[200];
  projectionString[0] = '\0';

  if (grid)
  {
    cols = grid->XNumber();
    rows = grid->YNumber();
    dx = (area->WorldXYWidth() / (grid->XNumber()-1));
    dy = (area->WorldXYHeight() / (grid->YNumber()-1));
  }

  const char *sm = "+x+y";

  switch (classid)
  {
    case kNFmiEquiDistArea:
      break;

    case kNFmiGnomonicArea:
      break;

    case kNFmiStereographicArea:
    {
      sprintf(projectionString,"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;description",
          T::GridProjectionValue::PolarStereographic,
          cols,
          rows,
          area->BottomLeftLatLon().X(),
          area->BottomLeftLatLon().Y(),
          fabs(dx),
          fabs(dy),
          sm,
          part1[1],
          part1[3]);
    }
    break;

    case kNFmiLambertConformalConicArea:
    {
      if (part1.size() >= 4)
      {
        double spole_x = 0.0;
        double spole_y = -90.0;
        sprintf(projectionString,"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;%.6f;%.6f;%.6f;%.6f;description",
            T::GridProjectionValue::LambertConformal,
            cols,
            rows,
            area->BottomLeftLatLon().X(),
            area->BottomLeftLatLon().Y(),
            fabs(dx),
            fabs(dy),
            sm,
            part1[1],
            part1[2],
            part1[3],
            spole_x,
            spole_y,
            part1[2]);
      }
    }
    break;

    case kNFmiKKJArea:
      break;

    case kNFmiPKJArea:
      break;

    case kNFmiYKJArea:
      break;

    case kNFmiLatLonArea:
    {
      float dxx = (area->BottomRightLatLon().X() - area->BottomLeftLatLon().X()) / (float)(cols);
      float dyy = (area->TopLeftLatLon().Y() - area->BottomLeftLatLon().Y()) / (float)(rows-1);
      sprintf(projectionString,"%d;id;name;%u;%u;%.6f;%.6f;%.6f;%.6f;%s;description",
        T::GridProjectionValue::LatLon,
        cols,
        rows,
        area->BottomLeftLatLon().X(),
        area->BottomLeftLatLon().Y(),
        fabs(dxx),
        fabs(dyy),
        sm);
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

        //printf("AREA %f,%f %f,%f\n",rotLon1,rotLat1,rotLon2,rotLat2);

        const char *sm = "+x+y";
        float dxx = (rotLon2 - rotLon1) / (float)(cols);
        float dyy = (rotLat2 - rotLat1) / (float)(rows-1);
        float angle = 0;
        sprintf(projectionString,"%d;id;name;%u;%u;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;%.6f;description",
            T::GridProjectionValue::RotatedLatLon,
            cols,
            rows,
            rotLon1,
            rotLat1,
            fabs(dxx),
            fabs(dyy),
            sm,
            part1[2],
            part1[1],
            angle);
      }
    }
    break;

    case kNFmiMercatorArea:
      break;
  }


  if (projectionString[0] != '\0')
  {
    auto def = Identification::gridDef.getGrib2DefinitionByGeometryString(projectionString);
    if (def)
    {
      return def->getGridGeometryId();
    }
    else
    {
      std::cout << "** Add the following geometry into the geometry definition file (=> fill id,name and description fields) :\n\n";
      std::cout << "MISSING GEOMETRY: " << projectionString << "\n";
      return 0;
    }
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




void QueryDataFile::read(MessageInfoVec& messageInfoList)
{
  try
  {
    const NFmiGrid *grid = mFastQueryInfo->Grid();
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

        \param ostream      The output stream.
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
