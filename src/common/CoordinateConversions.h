#pragma once

#include "Coordinate.h"

#include <vector>
#include <boost/optional.hpp>
#include <ogr_spatialref.h>

bool convert(const OGRSpatialReference *sr_from,const OGRSpatialReference *sr_to,int nCount,double *x,double *y);


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
double latlon_width(double lat, double longitudes);
double latlon_height(double lon, double latitudes);


void latLon_bboxByCenter(double centerX,double centerY,double metricWidth,double metricHeight,double& lon1,double& lat1,double& lon2,double& lat2);

std::pair<std::vector<SmartMet::T::Coordinate>, std::vector<double>> getIsocirclePoints(double lon1, double lat1, double lon2, double lat2, std::size_t steps);


inline double getLongitude(double lon)
{
  if (lon >= -180  &&  lon <= 180)
    return lon;

  // The longitude value is out the acceptable range.
  if (lon < -1000  ||  lon > 1000)
    return lon;

  lon = lon + 180;
  while (lon > 360)
    lon = lon-360;

  lon = lon - 180;
  return lon;
}

