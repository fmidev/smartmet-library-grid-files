#include "RotatedLatLonImpl.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralFunctions.h"
#include "../../common/CoordinateConversions.h"
#include "../../common/Dimensions.h"
#include "../../grid/PrintOptions.h"
#include <iostream>


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

RotatedLatLonImpl::RotatedLatLonImpl()
{
  try
  {
    mGridProjection = T::GridProjectionValue::RotatedLatLon;
    mNi = 0;
    mNj = 0;
    mStartY = 0;
    mStartX = 0;
    mDx = 0;
    mDy = 0;
    mSouthPoleLat = 0;
    mSouthPoleLon = 0;
    mInitialized = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

RotatedLatLonImpl::RotatedLatLonImpl(const RotatedLatLonImpl& other)
:RotatedLatLon(other)
{
  try
  {
    mGridProjection = T::GridProjectionValue::RotatedLatLon;
    mNi = other.mNi;
    mNj = other.mNj;
    mStartY = other.mStartY;
    mStartX = other.mStartX;
    mDx = other.mDx;
    mDy = other.mDy;
    mSouthPoleLat = other.mSouthPoleLat;
    mSouthPoleLon = other.mSouthPoleLon;
    mInitialized = other.mInitialized;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

RotatedLatLonImpl::~RotatedLatLonImpl()
{
  try
  {
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





void RotatedLatLonImpl::init() const
{
  try
  {
    if (mInitialized)
      return;

    mNi = (*mLatLon.getGrid()->getNi());
    mNj = (*mLatLon.getGrid()->getNj());
    mStartY = C_DOUBLE(*mLatLon.getGrid()->getLatitudeOfFirstGridPoint()) / 1000000;
    mStartX = getLongitude(C_DOUBLE(*mLatLon.getGrid()->getLongitudeOfFirstGridPoint()) / 1000000);

    double mEndY = C_DOUBLE(*mLatLon.getGrid()->getLatitudeOfLastGridPoint()) / 1000000;
    double mEndX = getLongitude(C_DOUBLE(*mLatLon.getGrid()->getLongitudeOfLastGridPoint()) / 1000000);

    double dx = C_DOUBLE(*mLatLon.getIDirectionIncrement()) / 1000000;
    double dy = C_DOUBLE(*mLatLon.getJDirectionIncrement()) / 1000000;

    ResolutionSettings *rs = mLatLon.getGrid()->getResolution();
    if (rs != nullptr)
    {
      std::uint8_t flags = rs->getResolutionAndComponentFlags();
      if ((flags & 0x20) == 0  &&  mLatLon.getGrid()->getLongitudeOfLastGridPoint())
      {
        // i direction increment not given
        dx = (mEndX-mStartX)/mNi;
      }

      if ((flags & 0x10) == 0  &&  mLatLon.getGrid()->getLatitudeOfLastGridPoint())
      {
        // j direction increment not given
        dy = (mEndY-mStartY)/mNj;
      }
    }

    mDx = dx;
    mDy = dy;

    mSouthPoleLat = C_DOUBLE(*mRotation.getLatitudeOfSouthernPole())/1000000;
    mSouthPoleLon = C_DOUBLE(*mRotation.getLongitudeOfSouthernPole())/1000000;

    unsigned char scanMode = mLatLon.getScanningMode()->getScanningMode();

    if ((scanMode & 0x80) != 0)
      mDx = -dx;

    if ((scanMode & 0x40) == 0)
      mDy = -dy;

    mInitialized = true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns a duplicate of the current object. */

GridDefinition* RotatedLatLonImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new RotatedLatLonImpl(*this);
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

void RotatedLatLonImpl::read(MemoryReader& memoryReader)
{
  try
  {
    RotatedLatLon::read(memoryReader);
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

T::Coordinate_svec RotatedLatLonImpl::getGridOriginalCoordinates() const
{
  try
  {
    T::Coordinate_svec coordinateList(new T::Coordinate_vec());

    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return coordinateList;

    if (mNi == 0 || mNj == 0)
      return coordinateList;

    coordinateList->reserve(mNi*mNj);

    double y = mStartY;
    for (uint j=0; j < mNj; j++)
    {
      double x = mStartX;
      for (uint i=0; i < mNi; i++)
      {
        T::Coordinate coord(x,y);
        coordinateList->emplace_back(T::Coordinate(x,y));
        x += mDx;
      }
      y += mDy;
    }

    return coordinateList;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






/*! \brief The method returns all grid coordinates as a latlon coordinate vector. If the grid
    original coordiantes were not latlon coordinates then the original coordinates are converted
    to the latlon coordinates.

        \return   The grid latlon coordinates.
*/

#if 0
T::Coordinate_svec RotatedLatLonImpl::getGridLatLonCoordinates() const
{
  try
  {
    T::Coordinate_svec coordinateList(new T::Coordinate_vec());

    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return coordinateList;

    if (!mInitialized)
      init();

    if (mNi == 0 || mNj == 0)
      return coordinateList;

    OGRSpatialReference sr_latlon;
    sr_latlon.importFromEPSG(4326);
    sr_latlon.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

    auto sr = mSpatialReference.Clone();
    auto tf = OGRCreateCoordinateTransformation(sr,&sr_latlon);
    if (tf == nullptr)
      throw Fmi::Exception(BCP,"Cannot create coordinate transformation!");

    coordinateList->reserve(mNi*mNj);

    double y = mStartY;
    for (uint j=0; j < mNj; j++)
    {
      double x = mStartX;

      for (uint i=0; i < mNi; i++)
      {
        double lat = y;
        double lon = x;

        tf->Transform(1,&lon,&lat);

        //rotatedLatlon_to_latlon(y,x,mSouthPoleLat,mSouthPoleLon,lat,lon);

        coordinateList->emplace_back(T::Coordinate(lon,lat));
        x += mDx;
      }
      y += mDy;
    }

    if (sr != nullptr)
      mSpatialReference.DestroySpatialReference(sr);

    if (tf != nullptr)
      OCTDestroyCoordinateTransformation(tf);

    return coordinateList;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}
#endif




void RotatedLatLonImpl:: getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const
{
  try
  {
    int sz = latlon.size();
    points.reserve(sz);

    double *x = new double[sz+1];
    double *y = new double[sz+1];

    std::shared_ptr<double> rx(x);
    std::shared_ptr<double> ry(y);

    for (int t=0; t<sz; t++)
    {
      auto cc = latlon[t];
      y[t] = cc.y();
      x[t] = cc.x();
    }

    convert(&mLatlonSpatialReference,&mSpatialReference,sz,x,y);

    for (int t=0; t<sz; t++)
    {
      double grid_i = 0;
      double grid_j = 0;
      if (getGridPointByOriginalCoordinates(x[t],y[t],grid_i,grid_j))
      {
        //printf("%f,%f => %f,%f\n",x[t],y[t],grid_i,grid_j);
        points.emplace_back(T::Coordinate(grid_i,grid_j));
      }
      else
      {
        //printf("INVALID %f,%f => %f,%f\n",x[t],y[t],grid_i,grid_j);
        points.emplace_back(T::Coordinate(ParamValueMissing,ParamValueMissing));
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief This method return the latlon coordinates of the give grid point.

        \param grid_i  The grid i-position.
        \param grid_j  The grid j-position.
        \param lat     The returned latitude value.
        \param lon     The returned longitude value.
*/

bool RotatedLatLonImpl::getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const
{
  try
  {
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return false;

    if (grid_i > mNi)
      return false;

    if (grid_j > mNj)
      return false;

    double rotated_lat = mStartY + grid_j * mDy;
    double rotated_lon = mStartX + grid_i * mDx;

    lat = rotated_lat;
    lon = rotated_lon;

    return convert(&mSpatialReference,&mLatlonSpatialReference,1,&lon,&lat);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid latlon coordinates in the given grid position (= double coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return        The method return true if the latlon values were succesfully returned.
*/

bool RotatedLatLonImpl::getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const
{
  try
  {
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return false;

    if (grid_i > C_DOUBLE(mNi))
      return false;

    if (grid_j > C_DOUBLE(mNj))
      return false;

    double rotated_lat = mStartY + grid_j * mDy;
    double rotated_lon = mStartX + grid_i * mDx;

    double lat = rotated_lat;
    double lon = rotated_lon;

    return convert(&mSpatialReference,&mLatlonSpatialReference,1,&lon,&lat);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid original (projection) coordinates in the given grid point (= integer coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param x       The x-coordinate in the original projection is returned in this parameter.
        \param y       The y-coordinate in the original projection is returned in this parameter.
        \return        The method return true if the original coordinates were succesfully returned.
*/

bool RotatedLatLonImpl::getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const
{
  try
  {
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return false;

    if (grid_i > mNi)
      return false;

    if (grid_j > mNj)
      return false;

    y = mStartY + grid_j * mDy;
    x = mStartX + grid_i * mDx;

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid original (projection) coordinates in the given grid position (= double coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param x       The x-coordinate in the original projection is returned in this parameter.
        \param y       The y-coordinate in the original projection is returned in this parameter.
        \return        The method return true if the original coordinates were succesfully returned.
*/

bool RotatedLatLonImpl::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  try
  {
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return false;

    if (grid_i > C_DOUBLE(mNi))
      return false;

    if (grid_j > C_DOUBLE(mNj))
      return false;

    y = mStartY + grid_j * mDy;
    x = mStartX + grid_i * mDx;

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid geometry string. This string can be used for comparing
    geometries in different grid files. For example, is is possible that a GRIB 1 message has
    the same geometry string as a GRIB 2 message, which means that they have same geometries.
    This comparison is more reliable than the hash comparison.

        \return   The grid geometry string.
*/

std::string RotatedLatLonImpl::getGridGeometryString() const
{
  try
  {
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return std::string("");

    char buf[1000];

    uint ni = (*mLatLon.getGrid()->getNi());
    uint nj = (*mLatLon.getGrid()->getNj());
    double y = C_DOUBLE(*mLatLon.getGrid()->getLatitudeOfFirstGridPoint()) / 1000000;
    double x = C_DOUBLE(*mLatLon.getGrid()->getLongitudeOfFirstGridPoint()) / 1000000;
    double dx = C_DOUBLE(*mLatLon.getIDirectionIncrement());
    double dy = C_DOUBLE(*mLatLon.getJDirectionIncrement());

    double sy = C_DOUBLE(*mRotation.getLatitudeOfSouthernPole())/1000000;
    double sx = C_DOUBLE(*mRotation.getLongitudeOfSouthernPole())/1000000;

    double angle = C_DOUBLE(mRotation.getAngleOfRotation());

    unsigned char scanningMode = mLatLon.getScanningMode()->getScanningMode();

    char sm[100];
    char *p = sm;
    if ((scanningMode & 0x80) != 0)
    {
      dx = -dx;
      p += sprintf(p,"-x");
    }
    else
    {
      p += sprintf(p,"+x");
    }

    if ((scanningMode & 0x40) == 0)
    {
      dy = -dy;
      p += sprintf(p,"-y");
    }
    else
    {
      p += sprintf(p,"+y");
    }

    sprintf(buf,"%d;id;name;%u;%u;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;%.6f;description",
        T::GridProjectionValue::RotatedLatLon,ni,nj,x,y,fabs(dx),fabs(dy),sm,sx,sy,angle);

    return std::string(buf);
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

T::Dimensions RotatedLatLonImpl::getGridDimensions() const
{
  try
  {
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return T::Dimensions();

    return T::Dimensions(*mLatLon.getGrid()->getNi(), *mLatLon.getGrid()->getNj());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




std::size_t RotatedLatLonImpl::getGridColumnCount() const
{
  try
  {
    return *mLatLon.getGrid()->getNi();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




std::size_t RotatedLatLonImpl::getGridRowCount() const
{
  try
  {
    return *mLatLon.getGrid()->getNj();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




bool RotatedLatLonImpl::getGridMetricCellSize(double& width,double& height) const
{
  try
  {
    width = C_DOUBLE(*mLatLon.getIDirectionIncrement()) / 1000000;
    height = C_DOUBLE(*mLatLon.getJDirectionIncrement()) / 1000000;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid original (projection) coordinates by the given latlon position.

        \param lat  The latitude value.
        \param lon  The longitude value.
        \param x    The x-coordinate in the original projection is returned in this parameter.
        \param y    The y-coordinate in the original projection is returned in this parameter.
        \return     The method return true if the original coordinates were succesfully returned.
*/

bool RotatedLatLonImpl::getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const
{
  try
  {
    y = lat;
    x = lon;

    return convert(&mLatlonSpatialReference,&mSpatialReference,1,&x,&y);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid latlon coordinates according the grid original (projection) coordinates.

        \param x       The x-coordinate in the original projection.
        \param y       The y-coordinate in the original projection.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return        The method return true if the latlon values were succesfully returned.
*/

bool RotatedLatLonImpl::getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const
{
  try
  {
    double lat = y;
    double lon = x;

    return convert(&mSpatialReference,&mLatlonSpatialReference,1,&lon,&lat);
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

bool RotatedLatLonImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    double aLon = getLongitude(x);
    if (aLon < mStartX)
      aLon += 360;

    double latDiff = (round(y*100) - round(mStartY*100)) / 100;
    double lonDiff = (round(aLon*100) - round(mStartX*100)) / 100;

    grid_i = lonDiff / mDx;
    grid_j = latDiff / mDy;

    if (grid_i < 0 ||  grid_j < 0  ||  grid_i >= C_DOUBLE(mNi) ||  grid_j >= C_DOUBLE(mNj))
      return false;

    return true;
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

bool RotatedLatLonImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
{
  try
  {
    double x = 0, y = 0;
    getGridOriginalCoordinatesByLatLonCoordinates(lat,lon,x,y);

    return getGridPointByOriginalCoordinates(x,y,grid_i,grid_j);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






/*! \brief The method returns 'true' if the grid horizontal values are in the reverse order.

        \return   The method returns 'true' if the grid horizontal values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool RotatedLatLonImpl::reverseXDirection() const
{
  try
  {
    unsigned char scanMode = mLatLon.getScanningMode()->getScanningMode();

    if ((scanMode & 0x80) != 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns 'true' if the grid vertical values are in the reverse order.

        \return   The method returns 'true' if the grid vertical values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool RotatedLatLonImpl::reverseYDirection() const
{
  try
  {
    unsigned char scanMode = mLatLon.getScanningMode()->getScanningMode();

    if ((scanMode & 0x40) == 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




std::string RotatedLatLonImpl::getWKT()
{
  try
  {
    return GridDefinition::getWKT();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




std::string RotatedLatLonImpl::getProj4()
{
  try
  {
    return mProj4;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void RotatedLatLonImpl::initSpatialReference()
{
  try
  {
    init();

    // ### Set geographic coordinate system.

    const char *pszGeogName = "UNKNOWN";
    const char *pszDatumName = "UNKNOWN";
    const char *pszSpheroidName = "UNKNOWN";
    double dfSemiMajor = getMajorAxis(mEarthShape);
    double dfInvFlattening = getFlattening(mEarthShape);
    double angle = C_DOUBLE(mRotation.getAngleOfRotation());

    mSpatialReference.SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);
    mSpatialReference.SetDerivedGeogCRSWithPoleRotationGRIBConvention("RotatedLatlon",mSouthPoleLat,mSouthPoleLon,angle);
    mSpatialReference.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);


#if 0
    double npole_lat = -mSouthPoleLat;
    double npole_lon = 0;
    double lon_0 = mSouthPoleLon;

    char proj[200];

    sprintf(proj,"+proj=ob_tran +o_proj=longlat +lon_0=%f +o_lon_p=%f +o_lat_p=%f +to_meter=.0174532925199433 +R=%f +wktext +over +towgs84=0,0,0 +no_defs",
        lon_0,npole_lon,npole_lat,dfSemiMajor);

    mProj4 = proj;

    OGRErr err = mSpatialReference.SetFromUserInput(proj);
    if (err != OGRERR_NONE)
      throw Fmi::Exception(BCP, "Invalid crs '" + std::string(proj) + "'!");
#endif


    char *out = nullptr;
    mSpatialReference.exportToProj4(&out);
    mProj4 = out;
    CPLFree(out);

    // ### Validate the spatial reference.

    auto errorCode = mSpatialReference.Validate();
    if (errorCode != OGRERR_NONE)
    {
      Fmi::Exception exception(BCP,"The spatial reference is not valid!");
      exception.addParameter("ErrorCode",std::to_string(errorCode));
      throw exception;
    }

    // ### Test if the grid is global

    uint ni = (*mLatLon.getGrid()->getNi());
    double iDirectionIncrement = C_DOUBLE(*mLatLon.getIDirectionIncrement()) / 1000000;
    double len = (ni+1)* iDirectionIncrement;

    if (len >= 360)
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

void RotatedLatLonImpl::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    RotatedLatLon::print(stream,level,optionFlags);

    stream << space(level+1) << "RotatedLatLonImpl\n";

    if (optionFlags & GRID::PrintFlag::coordinates)
    {
      stream << space(level+1) << "- Coordinates (of the grid corners):\n";

      T::Coordinate_svec coordinateList = getGridOriginalCoordinates();

      // ### Printing coordinates close to the grid corners.

      int nx = C_INT(*mLatLon.getGrid()->getNi());
      int ny = C_INT(*mLatLon.getGrid()->getNj());

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
