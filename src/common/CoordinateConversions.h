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



