#pragma once

#include <boost/optional.hpp>
#include <gdal/ogr_spatialref.h>


/*! \brief  The function converts latlon coordinates to rotated latlon coordinates. */

void latlon_to_rotatedLatlon(
    double lat,
    double lon,
    double southPoleLat,
    double southPoleLon,
    double& rotLat,
    double& rotLon);



/*! \brief The function converts rotated latlon coordinates to regular latlon coordinates. */

void rotatedLatlon_to_latlon(
    double rotLat,
    double rotLon,
    double southPoleLat,
    double southPoleLon,
    double& lat,
    double& lon);



double latlon_distance(double lat1, double lon1, double lat2, double lon2);

void getBoundingBox(
    boost::optional<std::string> crs,
    boost::optional<std::string> bboxcrs,
    boost::optional<int> xsize,
    boost::optional<int> ysize,
    boost::optional<double> x1,
    boost::optional<double> y1,
    boost::optional<double> x2,
    boost::optional<double> y2,
    boost::optional<double> cx,
    boost::optional<double> cy,
    boost::optional<double> resolution,
    bool latlon_center,
    double& xx1,
    double& yy1,
    double& yy2,
    double& xx2);


inline double getLongitude(double lon)
{
  if (lon >= -180  &&  lon <= 180)
    return lon;

  lon = lon + 180;
  while (lon > 360)
    lon = lon-360;

  lon = lon - 180;
  return lon;
}

