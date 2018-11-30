#pragma once


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

