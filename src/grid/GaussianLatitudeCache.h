#pragma once

#include "Typedefs.h"
#include <macgyver/Exception.h>


namespace SmartMet
{
namespace GRID
{


#define GaussianLatitudeCacheSize 1000  //!< Maximum number of Gaussian latitude arrays cached


// ====================================================================================
/*! \brief Cache for pre-computed Gaussian latitude arrays, keyed by (nj, N).
 *
 *  Gaussian latitudes are expensive to compute; this cache stores the result for each
 *  unique (nj, N) combination so repeated lookups are O(1). */
// ====================================================================================

class GaussianLatitudeCache
{
  public:
              GaussianLatitudeCache();
    virtual   ~GaussianLatitudeCache();

    /*! \brief Return the array of nj Gaussian latitudes for the given N parameter.
     *  \param[in] nj  Number of latitude rows.
     *  \param[in] n   Gaussian N parameter (half the number of latitude circles).
     *  \return Pointer to the latitude array, or nullptr if (nj,n) is not cached. */
    double*   getLatitudes(uint nj,long n);

    /*! \brief Find the cached Gaussian latitudes bracketing a given latitude.
     *  \param[in]  nj       Number of latitude rows.
     *  \param[in]  n        Gaussian N parameter.
     *  \param[in]  lat      Target latitude in degrees.
     *  \param[out] latLow   Lower bracketing latitude.
     *  \param[out] latHigh  Upper bracketing latitude.
     *  \return Index of the lower bracket, or -1 if not found. */
    int       getClosestLatitudes(uint nj,long n,double lat,double& latLow,double& latHigh);

  protected:

    double*   mLatitudes[GaussianLatitudeCacheSize];      //!< Cached latitude arrays (nullptr = empty slot)
    long      mLatitudes_number[GaussianLatitudeCacheSize]; //!< Gaussian N parameter for each cached array
    uint      lastAccess;                                 //!< LRU eviction counter

};


extern GaussianLatitudeCache gaussianLatitudeCache;

}
}
