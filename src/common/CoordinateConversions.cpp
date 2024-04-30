#include "CoordinateConversions.h"
#include "CoordinateConverter.h"
#include "GeneralFunctions.h"
#include "GeneralDefinitions.h"
#include "AutoThreadLock.h"
#include "AutoWriteLock.h"
#include "AutoReadLock.h"

#include <macgyver/Exception.h>
#include <macgyver/Cache.h>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/make_shared.hpp>
#include <boost/functional/hash.hpp>
#include <ogr_geometry.h>
#include <ogr_spatialref.h>

#include <newbase/NFmiLocation.h>
#include <unordered_map>

Fmi::Cache::Cache<std::size_t,SmartMet::CoordinateConverter> coordinateConverterCache(1000000);



bool convert(const OGRSpatialReference *sr_from,const OGRSpatialReference *sr_to,int nCount,double *x,double *y)
{
  try
  {
    std::size_t hash = (std::size_t)sr_from;
    boost::hash_combine(hash, (std::size_t)sr_to);
    auto rec = coordinateConverterCache.find(hash);
    if (rec)
      return rec->convert(nCount,x,y);

    SmartMet::CoordinateConverter tr(sr_from,sr_to);
    coordinateConverterCache.insert(hash,tr);
    return tr.convert(nCount,x,y);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





double getValue(double theAngle)
{
  try
  {
    if (::fabs(theAngle - 180) < 0.0000001)
      return 180;
    else if (::fabs(theAngle + 180) < 0.0000001)
      return -180;
    else if (theAngle > 180)
      return getValue(theAngle - 360);
    else if (theAngle < -180)
      return getValue(theAngle + 360);

    return theAngle;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void latlon_to_rotatedLatlon(double lat,double lon,double southPoleLat,double southPoleLon,double& rotLat,double& rotLon)
{
  try
  {
    if (southPoleLat == -90)
    {
      rotLat = lat;
      rotLon = lon;
      return;
    }

    double SinYPole = sin((southPoleLat + 90) * kDegToRad);
    double CosYPole = cos((southPoleLat + 90) * kDegToRad);

    double SinXReg = sin((lon - southPoleLon) * kDegToRad);
    double CosXReg = cos((lon - southPoleLon) * kDegToRad);
    double SinYReg = sin(lat * kDegToRad);
    double CosYReg = cos(lat * kDegToRad);
    double SinYRot = CosYPole * SinYReg - SinYPole * CosYReg * CosXReg;
    SinYRot = std::min(std::max(SinYRot, -1.), 1.);
    double YRot = asin(SinYRot) * kOneRad;

    double CosYRot = cos(YRot * kDegToRad);
    double CosXRot = (CosYPole * CosYReg * CosXReg + SinYPole * SinYReg) / CosYRot;
    CosXRot = std::min(std::max(CosXRot, -1.), 1.);
    double SinXRot = CosYReg * SinXReg / CosYRot;
    double XRot = acos(CosXRot) * kOneRad;
    if (SinXRot < 0.)
      XRot = getValue(-XRot);
    else
      XRot = getValue(XRot);

    rotLon = XRot;
    rotLat = YRot;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void rotatedLatlon_to_latlon(double rotLat,double rotLon,double southPoleLat,double southPoleLon,double& lat,double& lon)
{
  try
  {
    if (southPoleLat == -90)
    {
      lat = rotLat;
      lon = rotLon;
      return;
    }

    double SinYPole = sin((southPoleLat + 90) * kDegToRad);
    double CosYPole = cos((southPoleLat + 90) * kDegToRad);

    double SinXRot = sin(rotLon * kDegToRad);
    double CosXRot = cos(rotLon * kDegToRad);
    double SinYRot = sin(rotLat * kDegToRad);
    double CosYRot = cos(rotLat * kDegToRad);
    double SinYReg = CosYPole * SinYRot + SinYPole * CosYRot * CosXRot;
    SinYReg = std::min(std::max(SinYReg, -1.0), 1.0);

    double YReg = asin(SinYReg) * kOneRad;

    double CosYReg = cos(YReg * kDegToRad);
    double CosXReg = (CosYPole * CosYRot * CosXRot - SinYPole * SinYRot) / CosYReg;
    CosXReg = std::min(std::max(CosXReg, -1.0), 1.0);
    double SinXReg = CosYRot * SinXRot / CosYReg;

    double XRegVal = acos(CosXReg) * kOneRad;
    if (SinXReg < 0.)
      XRegVal = -XRegVal;

    XRegVal = XRegVal + southPoleLon;
    double XReg = XRegVal;

    lat = YReg;
    lon = XReg;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




double latlon_distance(double lat1, double lon1, double lat2, double lon2)
{
  double p = 0.017453292519943295;    // Math.PI / 180
  double a = 0.5 - cos((lat2 - lat1) * p)/2 +
          cos(lat1 * p) * cos(lat2 * p) *
          (1 - cos((lon2 - lon1) * p))/2;

  return 12742 * asin(sqrt(a)); // 2 * R; R = 6371 km
}



double latlon_width(double lat, double longitudes)
{
  try
  {
    // Metric width of 1 degree
    double w = latlon_distance(lat,0,lat,1);
    return longitudes * w;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




double latlon_height(double lon, double latitudes)
{
  try
  {
    // Metric width of 1 degree
    double h = latlon_distance(0,lon,1,lon);
    return latitudes * h;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



std::pair<std::vector<SmartMet::T::Coordinate>, std::vector<double>> getIsocirclePoints(double lon1, double lat1, double lon2, double lat2, std::size_t steps)
{
  try
  {
    // Sanity checks
    if (lon1 == lon2 && lat1 == lat2)
      throw Fmi::Exception(BCP, "Ill-defined isocircle: start and end points are equal");

    if (std::abs(lon1 - lon2) == 180 && std::abs(lat1 - (90 - lat2)) == 90)
      throw Fmi::Exception(BCP, "Ill-defined isocircle: points at opposing ends of the earth");

    if (steps < 1 || steps > 10000)
      throw Fmi::Exception(BCP,"Number of points on isocircle must be 1-10000, not " + boost::lexical_cast<std::string>(steps));

    // Calculate bearing and distance to be travelled

    NFmiLocation startpoint(lon1, lat1);
    NFmiLocation endpoint(lon2, lat2);

    double bearing = startpoint.Direction(endpoint);
    double distance = startpoint.Distance(endpoint);

    std::vector<SmartMet::T::Coordinate> coordinates;
    auto cc = startpoint.GetLocation();
    coordinates.emplace_back(cc.X(),cc.Y());

    std::vector<double> distances;
    distances.emplace_back(0);

    for (std::size_t i = 1; i < steps; i++)
    {
      // Should this be fixed? Probably not - the coordinates should behave the same
      double dist = i * distance / steps;
      const bool pacific_view = false;
      auto loc = startpoint.GetLocation(bearing, dist, pacific_view);
      auto cc = loc.GetLocation();
      coordinates.emplace_back(cc.X(),cc.Y());
      distances.emplace_back(dist / 1000.0);
    }
    cc = endpoint.GetLocation();
    coordinates.emplace_back(cc.X(),cc.Y());
    distances.emplace_back(distance / 1000.0);

    return std::make_pair(coordinates, distances);
  }
  catch (...)
  {
    throw Fmi::Exception::Trace(BCP, "Operation failed!");
  }
}



void latLon_bboxByCenter(double centerX,double centerY,double metricWidth,double metricHeight,double& lon1,double& lat1,double& lon2,double& lat2)
{
  try
  {
    double dx = latlon_distance(centerY,centerX,centerY,centerX+0.00001)*100000000;
    double dy = latlon_distance(centerY,centerX,centerY+0.00001,centerX)*100000000;

    // Metric distance in degrees
    double ddx = 0.5*metricWidth/dx;
    double ddy = 0.5*metricHeight/dy;

    lon1 = centerX - ddx;
    lat1 = centerY - ddy;
    lon2 = centerX + ddx;
    lat2 = centerY + ddy;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void latLon_bboxByCenter(double centerX,double centerY,double metricDistanceLeft,double metricDistanceBottom,double metricDistanceRight,double metricDistanceTop,double& lon1,double& lat1,double& lon2,double& lat2)
{
  try
  {
    double dx = latlon_distance(centerY,centerX,centerY,centerX+0.00001)*100000000;
    double dy = latlon_distance(centerY,centerX,centerY+0.00001,centerX)*100000000;

    // Metric distance in degrees
    //double ddx = 0.5*metricWidth/dx;
    //double ddy = 0.5*metricHeight/dy;

    lon1 = centerX - metricDistanceLeft/dx;
    lat1 = centerY - metricDistanceBottom/dy;
    lon2 = centerX + metricDistanceRight/dx;
    lat2 = centerY + metricDistanceTop/dy;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


