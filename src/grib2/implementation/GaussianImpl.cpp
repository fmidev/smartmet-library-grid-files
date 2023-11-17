#include "GaussianImpl.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralFunctions.h"
#include "../../common/Dimensions.h"
#include "../../grid/PrintOptions.h"
#include "../../grid/GaussianLatitudeCache.h"

#include <iostream>
#include <math.h>


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

GaussianImpl::GaussianImpl()
{
  mGridProjection = T::GridProjectionValue::Gaussian;
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





/*! \brief The method returns a duplicate of the current object. */

GridDefinition* GaussianImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new GaussianImpl(*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

         \return   The grid coordinates.
*/

T::Coordinate_svec GaussianImpl::getGridOriginalCoordinatesNoCache() const
{
  try
  {
    T::Coordinate_svec coordinateList(new T::Coordinate_vec());

    if (!mGaussian.getGrid()->getNi())
      throw Fmi::Exception(BCP,"i-coordinated does not exist!");

    if (!mGaussian.getGrid()->getNj())
      throw Fmi::Exception(BCP,"j-coordinated does not exist!");

    uint ni = (*mGaussian.getGrid()->getNi());
    uint nj = (*mGaussian.getGrid()->getNj());
    long n = (long)(*mGaussian.getN());

    double longitudeOfFirstGridPoint = C_DOUBLE(*mGaussian.getGrid()->getLongitudeOfFirstGridPoint());
    double longitudeOfLastGridPoint = C_DOUBLE(*mGaussian.getGrid()->getLongitudeOfLastGridPoint());
    //double iDirectionIncrement = C_DOUBLE(*mGaussian.iDirectionIncrement());
    double iDirectionIncrement = (longitudeOfLastGridPoint - longitudeOfFirstGridPoint) / C_DOUBLE(ni-1);

    unsigned char scanningMode = mGaussian.getScanningMode()->getScanningMode();

    if ((scanningMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;

    double *lats = GRID::gaussianLatitudeCache.getLatitudes(nj,n);

    coordinateList->reserve(ni*nj);

    for (uint j=0; j < nj; j++)
    {
      double y = lats[j];
      double x = longitudeOfFirstGridPoint;

      for (uint i=0; i < ni; i++)
      {
        double cx = x/1000000;
        double cy = y; ;
        T::Coordinate coord(cx,cy);
        coordinateList->emplace_back(coord);
        x += iDirectionIncrement;
      }
    }

    return coordinateList;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns.

        \return   The grid dimensions.
*/

T::Dimensions GaussianImpl::getGridDimensions() const
{
  try
  {
    if (!mGaussian.getGrid()->getNi() || !mGaussian.getGrid()->getNj())
      return T::Dimensions();

    return T::Dimensions(*mGaussian.getGrid()->getNi(),*mGaussian.getGrid()->getNi());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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

bool GaussianImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
{
  try
  {
    return getGridPointByOriginalCoordinates(lon,lat,grid_i,grid_j);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    if (!mGaussian.getGrid()->getNi() || !mGaussian.getGrid()->getNj())
      return false;

    uint ni = (*mGaussian.getGrid()->getNi());
    uint nj = (*mGaussian.getGrid()->getNj());
    long n = (long)(*mGaussian.getN());

    double longitudeOfFirstGridPoint = C_DOUBLE(*mGaussian.getGrid()->getLongitudeOfFirstGridPoint()) / 1000000;
    double longitudeOfLastGridPoint = C_DOUBLE(*mGaussian.getGrid()->getLongitudeOfLastGridPoint()) / 1000000;

    if (longitudeOfFirstGridPoint < 0)
      longitudeOfFirstGridPoint += 360;

    if (longitudeOfLastGridPoint < 0)
      longitudeOfLastGridPoint += 360;

    double iDirectionIncrement = (longitudeOfLastGridPoint - longitudeOfFirstGridPoint) / C_DOUBLE(ni-1);

    unsigned char scanningMode = mGaussian.getScanningMode()->getScanningMode();

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

    if (i < 0 || i >= C_DOUBLE(ni))
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

    grid_i = i;
    grid_j = j;

    if (j < 0  ||  j > C_DOUBLE(nj))
      return false;

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void GaussianImpl::initSpatialReference()
{
  try
  {
    // ### Set geographic coordinate system.

    const char *pszGeogName = "UNKNOWN";
    const char *pszDatumName = "UNKNOWN";
    const char *pszSpheroidName = "UNKNOWN";
    double dfSemiMajor = getMajorAxis(mEarthShape);
    double dfFlattening = getFlattening(mEarthShape);
    double dfInvFlattening = 0;
    if (dfFlattening != 0)
      dfInvFlattening = 1/dfFlattening;

    mSpatialReference.SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);
    mSpatialReference.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);


    // ### Validate the spatial reference.

    auto errorCode = mSpatialReference.Validate();
    if (errorCode != OGRERR_NONE)
    {
      Fmi::Exception exception(BCP,"The spatial reference is not valid!");
      exception.addParameter("ErrorCode",std::to_string(errorCode));
      throw exception;
    }


    // ### Test if the grid is global

    uint ni = (*mGaussian.getGrid()->getNi());
    double longitudeOfFirstGridPoint = C_DOUBLE(*mGaussian.getGrid()->getLongitudeOfFirstGridPoint()) / 1000000;
    double longitudeOfLastGridPoint = C_DOUBLE(*mGaussian.getGrid()->getLongitudeOfLastGridPoint()) / 1000000;

    if (longitudeOfFirstGridPoint < 0)
      longitudeOfFirstGridPoint += 360;

    if (longitudeOfLastGridPoint < 0)
      longitudeOfLastGridPoint += 360;

    double iDirectionIncrement = (longitudeOfLastGridPoint - longitudeOfFirstGridPoint) / C_DOUBLE(ni-1);

    if ((ni*iDirectionIncrement) >= 360)
      mGlobal = true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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

      T::Coordinate_svec coordinateList = getGridOriginalCoordinates();

      // ### Printing coordinates close to the grid corners.

      if (!mGaussian.getGrid()->getNi() || !mGaussian.getGrid()->getNj())
        return;

      int nx = C_INT(*mGaussian.getGrid()->getNi());
      int ny = C_INT(*mGaussian.getGrid()->getNj());

      char str[200];
      uint c = 0;
      for (int y=0; y < ny; y++)
      {
        for (int x=0; x < nx; x++)
        {
          if ((y < 3  ||  y >= ny-3)  &&  (x < 3  ||  x >= nx-3))
          {
            T::Coordinate coord = coordinateList->at(c);

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
}
