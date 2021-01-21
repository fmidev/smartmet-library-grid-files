#include "CoordinateConversions.h"
#include "CoordinateConverter.h"
#include "GeneralFunctions.h"
#include "GeneralDefinitions.h"
#include "AutoThreadLock.h"
#include "AutoWriteLock.h"
#include "AutoReadLock.h"

#include <macgyver/Exception.h>
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




std::unordered_map<std::size_t,SmartMet::CoordinateConverter> *coordinateConverterCache = nullptr;
SmartMet::ModificationLock coordinateConverterCache_modificationLock;




bool convert(const OGRSpatialReference *sr_from,const OGRSpatialReference *sr_to,int nCount,double *x,double *y)
{
  try
  {
    if (coordinateConverterCache == nullptr)
    {
      SmartMet::AutoWriteLock writeLock(&coordinateConverterCache_modificationLock);
      if (coordinateConverterCache == nullptr)
        coordinateConverterCache = new std::unordered_map<std::size_t,SmartMet::CoordinateConverter>;
    }

    std::size_t hash = (std::size_t)sr_from;
    boost::hash_combine(hash, (std::size_t)sr_to);

    {
      SmartMet::AutoReadLock readLock(&coordinateConverterCache_modificationLock);
      auto rec = coordinateConverterCache->find(hash);
      if (rec != coordinateConverterCache->end())
        return rec->second.convert(nCount,x,y);
    }

    SmartMet::AutoWriteLock writeLock(&coordinateConverterCache_modificationLock);
    if (coordinateConverterCache->size() > 1000000)
      coordinateConverterCache->clear();

    SmartMet::CoordinateConverter tr(sr_from,sr_to);
    coordinateConverterCache->insert(std::pair<std::size_t,SmartMet::CoordinateConverter>(hash,tr));
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
    coordinates.emplace_back(SmartMet::T::Coordinate(cc.X(),cc.Y()));

    std::vector<double> distances;
    distances.emplace_back(0);

    for (std::size_t i = 1; i < steps; i++)
    {
      // Should this be fixed? Probably not - the coordinates should behave the same
      const bool pacific_view = false;
      double dist = i * distance / steps;
      auto loc = startpoint.GetLocation(bearing, dist, pacific_view);
      auto cc = loc.GetLocation();
      coordinates.emplace_back(SmartMet::T::Coordinate(cc.X(),cc.Y()));
      distances.emplace_back(dist / 1000.0);
    }
    cc = endpoint.GetLocation();
    coordinates.emplace_back(SmartMet::T::Coordinate(cc.X(),cc.Y()));
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
    OGRSpatialReference sr_latlon;
    sr_latlon.importFromEPSG(4326);
    sr_latlon.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

    OGRSpatialReference sr_wgs84_world_mercator;
    sr_wgs84_world_mercator.importFromEPSG(3395);
    sr_wgs84_world_mercator.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

    OGRCoordinateTransformation *transformation = OGRCreateCoordinateTransformation(&sr_latlon,&sr_wgs84_world_mercator);
    OGRCoordinateTransformation *reverseTransformation = OGRCreateCoordinateTransformation(&sr_wgs84_world_mercator,&sr_latlon);

    transformation->Transform(1,&centerX,&centerY);

    double xx1 = centerX - metricWidth/2;
    double yy1 = centerY - metricHeight/2;
    double xx2 = centerX + metricWidth/2;
    double yy2 = centerY + metricHeight/2;

    // Converting metric coordinates to latlon coordinates.

    reverseTransformation->Transform(1,&xx1,&yy1);
    reverseTransformation->Transform(1,&xx2,&yy2);

    if (transformation != nullptr)
      OCTDestroyCoordinateTransformation(transformation);

    if (reverseTransformation != nullptr)
      OCTDestroyCoordinateTransformation(reverseTransformation);

    lon1 = xx1;
    lat1 = yy1;
    lon2 = xx2;
    lat2 = yy2;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




