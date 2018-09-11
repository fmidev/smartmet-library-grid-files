#include "GaussianLatitudeCache.h"
#include "../common/Exception.h"
#include "../common/CoordinateConversions.h"

#include <string>
#include <vector>


namespace SmartMet
{
namespace GRID
{

GaussianLatitudeCache gaussianLatitudeCache;



// ########## Copied from grib_api-1.17 : grib_geography.c ############

#define NUMBER(x) (sizeof(x)/sizeof(x[0]))
#define MAXITER  10

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


static void gauss_first_guess(long N, double* vals)
{
  try
  {
    long i = 0, numVals;
    static double gvals[] =  {     2.4048255577E0,   5.5200781103E0,
        8.6537279129E0,   11.7915344391E0,  14.9309177086E0,
        18.0710639679E0,  21.2116366299E0,  24.3524715308E0,
        27.4934791320E0,  30.6346064684E0,  33.7758202136E0,
        36.9170983537E0,  40.0584257646E0,  43.1997917132E0,
        46.3411883717E0,  49.4826098974E0,  52.6240518411E0,
        55.7655107550E0,  58.9069839261E0,  62.0484691902E0,
        65.1899648002E0,  68.3314693299E0,  71.4729816036E0,
        74.6145006437E0,  77.7560256304E0,  80.8975558711E0,
        84.0390907769E0,  87.1806298436E0,  90.3221726372E0,
        93.4637187819E0,  96.6052679510E0,  99.7468198587E0,
        102.8883742542E0, 106.0299309165E0, 109.1714896498E0,
        112.3130502805E0, 115.4546126537E0, 118.5961766309E0,
        121.7377420880E0, 124.8793089132E0, 128.0208770059E0,
        131.1624462752E0, 134.3040166383E0, 137.4455880203E0,
        140.5871603528E0, 143.7287335737E0, 146.8703076258E0,
        150.0118824570E0, 153.1534580192E0, 156.2950342685E0 };

    numVals = NUMBER(gvals);
    for( i = 0; i < N; i++)
    {
      if(i < numVals)
        vals[i] = gvals[i];
      else
        vals[i] = vals[i-1] +  M_PI;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





int gaussian_getLatitudes(long N, double *lats)
{
  try
  {
    long jlat, iter, legi;
    double rad2deg, convval, root, legfonc = 0;
    double mem1, mem2, conv;
    double denom = 0.0;
    double precision = 1.0E-14;
    long  nlat = N*2;
    double dnlat = C_DOUBLE(nlat);

    rad2deg = 180.0/M_PI;

    convval   = (1.0 - ((2.0 / M_PI)*(2.0 / M_PI)) * 0.25);

    gauss_first_guess(N, lats);
    denom = sqrt( ((dnlat+0.5)*(dnlat+0.5)) + convval );

    for (jlat = 0; jlat < N; jlat++)
    {
      /*   First approximation for root      */
      root = cos( lats[jlat] / denom );

      /*   Perform loop of Newton iterations  */
      iter = 0;
      conv = 1;

      while (fabs(conv) >= precision )
      {
        mem2 = 1.0;
        mem1 = root;

        /*  Compute Legendre polynomial  */
        for (legi = 0; legi < nlat; legi++)
        {
          legfonc = ( (2.0 * (C_DOUBLE(legi)+1) - 1.0) * root * mem1 - C_DOUBLE(legi) * mem2) / ((C_DOUBLE(legi)+1));
          mem2 = mem1;
          mem1 = legfonc;
        }

        /*  Perform Newton iteration  */
        conv = legfonc / ((dnlat * (mem2 - root * legfonc) ) / (1.0 - (root *root)));
        root -= conv;

        /*  Routine fails if no convergence after MAXITER iterations  */
        if (iter++ > MAXITER)
        {
          return -1;
        }
      }

      /*   Set North and South values using symmetry */
      lats[jlat] = asin(root) * rad2deg;
      lats[nlat-1-jlat] = -lats[jlat];
    }

    if (nlat != (N*2))
      lats[N + 1] = 0.0;

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}

// ########## end of copy ##########





/*! \brief The constructor of the class. */

GaussianLatitudeCache::GaussianLatitudeCache()
{
  try
  {
    lastAccess = 0;
    for (uint t=0; t<GaussianLatitudeCacheSize; t++)
    {
      mLatitudes[t] = nullptr;
      mLatitudes_number[t] = 0;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The destructor of the class. */

GaussianLatitudeCache::~GaussianLatitudeCache()
{
  try
  {
    for (uint t=0; t<GaussianLatitudeCacheSize; t++)
    {
      if (mLatitudes[t] != nullptr)
        delete mLatitudes[t];
    }
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





double* GaussianLatitudeCache::getLatitudes(uint nj,long n)
{
  try
  {
    if (mLatitudes[lastAccess] != nullptr  &&  mLatitudes_number[lastAccess] == nj)
      return mLatitudes[lastAccess];

    uint c = 0;
    while (c < GaussianLatitudeCacheSize  &&  mLatitudes[c] != nullptr)
    {
      if (mLatitudes_number[c] == nj)
      {
        lastAccess = c;
        return mLatitudes[c];
      }
    }

    if (c == GaussianLatitudeCacheSize)
    {
      c = GaussianLatitudeCacheSize-1;
      delete mLatitudes[c];
    }

    mLatitudes[c] = new double[nj];
    mLatitudes_number[c] = nj;
    gaussian_getLatitudes(n,mLatitudes[c]);
    lastAccess = c;
    return mLatitudes[c];
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





int GaussianLatitudeCache::getClosestLatitudes(uint nj,long n,double lat,double& latLow,double& latHigh)
{
  try
  {
    if (nj == 0)
      return -1;

    double *lats = getLatitudes(nj,n);
    int endp = C_INT(nj-1);

    if (lat > lats[0] || lat < lats[endp])
      return -1;

    int low = endp;
    int high = 0;
    while (low > high)
    {
      int mid = (low + high) / 2;

      if (lats[mid] == lat)
      {
        latLow = lats[mid];
        latHigh = lats[mid];
        return mid;
      }

      if (lats[mid] < lat)
        low = mid - 1;
      else
        high = mid + 1;
    }

    if (high > endp  ||  low < 0)
      return -1;

    while (lats[low] < lat  &&  low > 0)
      low--;

    if (lats[low] >= lat  &&  lats[low+1] <= lat)
    {
      latLow = lats[low];
      latHigh = lats[low+1];
      return low;
    }

    return -1;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}

}
}
