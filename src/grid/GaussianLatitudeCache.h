#pragma once

#include "Typedefs.h"
#include <macgyver/Exception.h>


namespace SmartMet
{
namespace GRID
{


#define GaussianLatitudeCacheSize 1000


class GaussianLatitudeCache
{
  public:
              GaussianLatitudeCache();
    virtual   ~GaussianLatitudeCache();

    double*   getLatitudes(uint nj,long n);
    int       getClosestLatitudes(uint nj,long n,double lat,double& latLow,double& latHigh);

  protected:

    double*   mLatitudes[GaussianLatitudeCacheSize];
    long      mLatitudes_number[GaussianLatitudeCacheSize];
    uint      lastAccess;

};


extern GaussianLatitudeCache gaussianLatitudeCache;

}
}
