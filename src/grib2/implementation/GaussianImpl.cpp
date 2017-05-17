#include "GaussianImpl.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "grid/PrintOptions.h"
#include "grid/Dimensions.h"
#include "grid/GaussianLatitudeCache.h"

#include <iostream>
#include <math.h>


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

GaussianImpl::GaussianImpl()
{
}





/*! \brief The copy constructor of the class. */

GaussianImpl::GaussianImpl(const GaussianImpl& other)
:Gaussian(other)
{
}





/*! \brief The destructor of the class. */

GaussianImpl::~GaussianImpl()
{
}





/*! \brief The method reads and initializes all data related to the current object.
    The purpose of this method is to get access to the read operation that takes place
    in the parent class (which is automatically generated). This means in practice that
    we first call the read operation in the parent class. After that we can ensure that
    the result of the read operation was correct (i.e. attribute values are valid, etc).
    We can also modify or update some attribute values if needed.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GaussianImpl::read(MemoryReader& memoryReader)
{
  try
  {
    Gaussian::read(memoryReader);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the first and the last latlon coordinates used in the grid.

        \param firstLat   The returned latitude of the top-left corner.
        \param firstLon   The returned longitude of the top-left corner.
        \param lastLat    The returned latitude of the bottom-right corner.
        \param lastLon    The returned longitude of the bottom-right corner.
*/

void GaussianImpl::getGridLatlonAreaCoordinates(double& firstLat,double& firstLon,double& lastLat,double& lastLon) const
{
  try
  {
    firstLat = (double)(*mGaussian.getGrid()->getLatitudeOfFirstGridPoint()) / 1000000;
    firstLon = (double)(*mGaussian.getGrid()->getLongitudeOfFirstGridPoint()) / 1000000;
    lastLat = (double)(*mGaussian.getGrid()->getLatitudeOfLastGridPoint()) / 1000000;
    lastLon = (double)(*mGaussian.getGrid()->getLongitudeOfLastGridPoint()) / 1000000;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

         \return   The grid coordinates.
*/

T::Coordinate_vec GaussianImpl::getGridCoordinates() const
{
  try
  {
    T::Coordinate_vec coordinateList;

    if (!mGaussian.getGrid()->getNi())
      throw SmartMet::Spine::Exception(BCP,"i-coordinated does not exist!");

    if (!mGaussian.getGrid()->getNj())
      throw SmartMet::Spine::Exception(BCP,"j-coordinated does not exist!");

    uint ni = (uint)(*mGaussian.getGrid()->getNi());
    uint nj = (uint)(*mGaussian.getGrid()->getNj());
    long n = (long)(*mGaussian.getN());

    double longitudeOfFirstGridPoint = (double)(*mGaussian.getGrid()->getLongitudeOfFirstGridPoint());
    double longitudeOfLastGridPoint = (double)(*mGaussian.getGrid()->getLongitudeOfLastGridPoint());
    //double iDirectionIncrement = (double)(*mGaussian.iDirectionIncrement());
    double iDirectionIncrement = (longitudeOfLastGridPoint - longitudeOfFirstGridPoint) / (double)(ni-1);

    unsigned char scanningMode = (unsigned char)(mGaussian.getScanningMode()->getScanningMode());

    if ((scanningMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;

    double *lats = GRID::gaussianLatitudeCache.getLatitudes(nj,n);

    for (uint j=0; j < nj; j++)
    {
      double y = lats[j];
      double x = longitudeOfFirstGridPoint;

      for (uint i=0; i < ni; i++)
      {
        double cx = x/1000000;
        double cy = y; ;
        T::Coordinate coord(cx,cy);
        coordinateList.push_back(coord);
        x += iDirectionIncrement;
      }
    }

    return coordinateList;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns.

        \return   The grid dimensions.
*/

T::Dimensions_opt GaussianImpl::getGridDimensions() const
{
  try
  {
    const auto defs = mGaussian.getGrid();
    uint nx = *defs->getNi();
    uint ny = *defs->getNj();
    return T::Dimensions{nx, ny};
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief This method calculates the estimated grid position by using the latlon coordinates.
    The estimated grid position is returned in the 'grid_i' and 'grid_j' parameters.

        \param lat     The latitude.
        \param lon     The longitude.
        \param grid_i  The returned grid i-position.
        \param grid_j  The returned grid j-position.
        \return        Returns 'false' if the given coordinates are outside of the grid.
*/

bool GaussianImpl::getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const
{
  try
  {
    return getGridPointByOriginalCoordinates(lon,lat,grid_i,grid_j);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief This method calculates the estimated grid position by using the original coordinates.
    The estimated grid position is returned in the 'grid_i' and 'grid_j' parameters.

      \param x       The original x-coordinate.
      \param y       The original y-coordinate.
      \param grid_i  The returned grid i-position.
      \param grid_j  The returned grid j-position.
      \return        Returns 'false' if the given coordinates are outside of the grid.
*/

bool GaussianImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    if (!mGaussian.getGrid()->getNi())
      throw SmartMet::Spine::Exception(BCP,"i-coordinated does not exist!");

    if (!mGaussian.getGrid()->getNj())
      throw SmartMet::Spine::Exception(BCP,"j-coordinated does not exist!");

    uint ni = (uint)(*mGaussian.getGrid()->getNi());
    uint nj = (uint)(*mGaussian.getGrid()->getNj());
    long n = (long)(*mGaussian.getN());

    double longitudeOfFirstGridPoint = (double)(*mGaussian.getGrid()->getLongitudeOfFirstGridPoint()) / 1000000;
    double longitudeOfLastGridPoint = (double)(*mGaussian.getGrid()->getLongitudeOfLastGridPoint()) / 1000000;

    if (longitudeOfFirstGridPoint < 0)
      longitudeOfFirstGridPoint += 360;

    if (longitudeOfLastGridPoint < 0)
      longitudeOfLastGridPoint += 360;

    double iDirectionIncrement = (longitudeOfLastGridPoint - longitudeOfFirstGridPoint) / (double)(ni-1);

    unsigned char scanningMode = (unsigned char)(mGaussian.getScanningMode()->getScanningMode());

    if ((scanningMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;


    double aLat = y + 90;
    double aLon = x;

    if (aLon < 0)
      aLon += 360;

    if (!mGlobal  &&  (aLon < longitudeOfFirstGridPoint || aLon > longitudeOfLastGridPoint))
      return false;

    double lonDiff = aLon - longitudeOfFirstGridPoint;
    double i = lonDiff / iDirectionIncrement;

    if (i < 0 || i >= (double)ni)
      return false;


    double latLow = 0;
    double latHigh = 0;

    int t = GRID::gaussianLatitudeCache.getClosestLatitudes(nj,n,y,latLow,latHigh);
    if (t < 0)
      return false;

    latLow += 90;
    latHigh += 90;

    double latDiff = aLat-latLow;
    double j = t + latDiff / (latHigh-latLow);

    if (j < 0  ||  j > (double)nj)
      return false;

    grid_i = i;
    grid_j = j;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




#if 0

bool GaussianImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    // ### TODO: This could be faster

    if (!mGaussian.getGrid().getNi())
      throw SmartMet::Spine::Exception(BCP,"i-coordinated does not exist!");

    if (!mGaussian.getGrid().getNj())
      throw SmartMet::Spine::Exception(BCP,"j-coordinated does not exist!");

    uint ni = (uint)(*mGaussian.getGrid().getNi());
    uint nj = (uint)(*mGaussian.getGrid().getNj());
    long n = (long)(*mGaussian.getN());

    double longitudeOfFirstGridPoint = (double)(*mGaussian.getGrid().getLongitudeOfFirstGridPoint()) / 1000000;
    double longitudeOfLastGridPoint = (double)(*mGaussian.getGrid().getLongitudeOfLastGridPoint()) / 1000000;

    if (longitudeOfFirstGridPoint < 0)
      longitudeOfFirstGridPoint += 360;

    if (longitudeOfLastGridPoint < 0)
      longitudeOfLastGridPoint += 360;

    double iDirectionIncrement = (longitudeOfLastGridPoint - longitudeOfFirstGridPoint) / (double)(ni-1);

    unsigned char scanningMode = (unsigned char)(mGaussian.getScanningMode().getScanningMode());

    if ((scanningMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;


    double *lats = GRID::gaussianLatitudeCache.getLatitudes(nj,n);
    double latitudeOfFirstGridPoint = lats[0] + 90;
    double latitudeOfLastGridPoint = lats[nj-1] + 90;

    double aLat = y + 90;
    double aLon = x;

    if (aLon < 0)
      aLon += 360;

    //printf("%f,%f => %f,%f (%f,%f) - (%f,%f)\n",y,x,aLat,aLon,latitudeOfFirstGridPoint,longitudeOfFirstGridPoint,latitudeOfLastGridPoint,longitudeOfLastGridPoint);


    if (latitudeOfFirstGridPoint < latitudeOfLastGridPoint && (aLat < latitudeOfFirstGridPoint || aLat > latitudeOfLastGridPoint))
      return false;

    if (latitudeOfFirstGridPoint > latitudeOfLastGridPoint && (aLat > latitudeOfFirstGridPoint || aLat < latitudeOfLastGridPoint))
      return false;

    if (!mGlobal  &&  (aLon < longitudeOfFirstGridPoint || aLon > longitudeOfLastGridPoint))
      return false;

    double lonDiff = aLon - longitudeOfFirstGridPoint;
    double i = lonDiff / iDirectionIncrement;

    if (i < 0 || i >= (double)ni)
      return false;

    double j = -1;
    for (uint t=0; t < nj-1; t++)
    {
      double y1 = lats[t] + 90;
      double y2 = lats[t+1] + 90;
      if (y1 < y2)
      {
        if (aLat >= y1  &&  aLat <= y2)
        {
          double latDiff = aLat-y1;
          j = (double)t + latDiff / (y2-y1);
          t = nj;
        }
      }
      else
      {
        if (aLat >= y2  &&  aLat <= y1)
        {
          double latDiff = aLat-y2;
          j = (double)t + 1 - latDiff / (y1-y2);
          t = nj;
        }
      }
    }

    if (j < 0  ||  j > (double)nj)
      return false;

    grid_i = i;
    grid_j = j;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}
#endif




/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void GaussianImpl::initSpatialReference()
{
  try
  {
    // ### Set geographic coordinate system.

    const char *pszGeogName = "UNKNOWN";
    const char *pszDatumName = "UNKNOWN";
    const char *pszSpheroidName = "UNKNOWN";
    double dfSemiMajor = 0.0;
    double dfInvFlattening = 0.0;

    auto radius = mEarthShape.getScaledValueOfRadiusOfSphericalEarth();

    if ((!radius) || (*radius == 0))
    {
      double majorAxis = *mEarthShape.getScaledValueOfEarthMajorAxis();
      double minorAxis = *mEarthShape.getScaledValueOfEarthMinorAxis();

      if (!(majorAxis && minorAxis && majorAxis > 0  && minorAxis > 0))
      {
        // TODO: Use code table 3.2 based values
        //
        dfSemiMajor = dfInvFlattening = 0.0;
        dfSemiMajor = 6371229;
      }
      else
      {
        dfSemiMajor = majorAxis;
        dfInvFlattening = 1.0 / (1.0 - (minorAxis / dfSemiMajor));
      }
    }
    else
    {
      dfSemiMajor = *radius;
      dfInvFlattening = 0.0;
    }

    mSpatialReference.SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);


    // ### Validate the spatial reference.

    auto errorCode = mSpatialReference.Validate();
    if (errorCode != OGRERR_NONE)
    {
      SmartMet::Spine::Exception exception(BCP,"The spatial reference is not valid!");
      exception.addParameter("ErrorCode",std::to_string(errorCode));
      throw exception;
    }


    // ### Test if the grid is global

    uint ni = (uint)(*mGaussian.getGrid()->getNi());
    double longitudeOfFirstGridPoint = (double)(*mGaussian.getGrid()->getLongitudeOfFirstGridPoint()) / 1000000;
    double longitudeOfLastGridPoint = (double)(*mGaussian.getGrid()->getLongitudeOfLastGridPoint()) / 1000000;

    if (longitudeOfFirstGridPoint < 0)
      longitudeOfFirstGridPoint += 360;

    if (longitudeOfLastGridPoint < 0)
      longitudeOfLastGridPoint += 360;

    double iDirectionIncrement = (longitudeOfLastGridPoint - longitudeOfFirstGridPoint) / (double)(ni-1);

    if ((ni*iDirectionIncrement) >= 360)
      mGlobal = true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void GaussianImpl::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    Gaussian::print(stream,level,optionFlags);

    stream << space(level+1) << "GaussianImpl\n";

    if (optionFlags & GRID::PrintFlag::coordinates)
    {
      stream << space(level+1) << "- Coordinates (of the grid corners):\n";

      T::Coordinate_vec coordinateList = getGridCoordinates();

      // ### Printing coordinates close to the grid corners.

      int nx = (int)(*mGaussian.getGrid()->getNi());
      int ny = (int)(*mGaussian.getGrid()->getNj());

      char str[200];
      uint c = 0;
      for (int y=0; y < ny; y++)
      {
        for (int x=0; x < nx; x++)
        {
          if ((y < 3  ||  y >= ny-3)  &&  (x < 3  ||  x >= nx-3))
          {
            T::Coordinate coord = coordinateList.at(c);

            sprintf(str,"* [%03d,%03d] %f,%f",x,y,coord.x(),coord.y());
            stream << space(level+2) << str << "\n";
          }
          c++;
        }
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}


}
}
