#include "LatLonImpl.h"
#include "../../common/Exception.h"
#include "../../common/GeneralFunctions.h"
#include "../../common/GeneralDefinitions.h"
#include "../../grid/PrintOptions.h"

namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class. */

LatLonImpl::LatLonImpl()
{
  mGridProjection = T::GridProjection::LatLon;
}





/*! \brief The copy constructor of the class. */

LatLonImpl::LatLonImpl(const LatLonImpl& other)
:LatLon(other)
{
}





/*! \brief The destructor of the class. */

LatLonImpl::~LatLonImpl()
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

void LatLonImpl::read(MemoryReader& memoryReader)
{
  try
  {
    LatLon::read(memoryReader);

    if (mNi == 0xFFFF)
      mNi = 0; // ni missing

    if (mNj == 0xFFFF)
      mNj = 0; // nj missing

    if (mJDirectionIncrement == 0xFFFF)
      mJDirectionIncrement = 0;

    if (mIDirectionIncrement == 0xFFFF)
      mIDirectionIncrement = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

         \return   The grid coordinates.
*/

T::Coordinate_vec LatLonImpl::getGridCoordinates() const
{
  try
  {
    T::Coordinate_vec coordinateList;

    uint ni = (uint)mNi;
    uint nj = (uint)mNj;

    if (ni == 0)
      ni = (uint)getGridOriginalColumnCount();

    double latitudeOfFirstGridPoint = (double)mGridArea.getLatitudeOfFirstGridPoint();
    double longitudeOfFirstGridPoint = (double)mGridArea.getLongitudeOfFirstGridPoint();
    double latitudeOfLastGridPoint = (double)mGridArea.getLatitudeOfLastGridPoint();
    double longitudeOfLastGridPoint = (double)mGridArea.getLongitudeOfLastGridPoint();

    double iDirectionIncrement = (double)mIDirectionIncrement;
    double jDirectionIncrement = (double)mJDirectionIncrement;

    unsigned char scanMode = (unsigned char)mScanningMode.getScanningMode();

    if ((scanMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;

    if ((scanMode & 0x40) == 0)
      jDirectionIncrement = -jDirectionIncrement;


    if (iDirectionIncrement == 0  &&  (longitudeOfLastGridPoint-longitudeOfFirstGridPoint) != 0  && ni > 0)
      iDirectionIncrement = (longitudeOfLastGridPoint-longitudeOfFirstGridPoint)/ni;

    if (jDirectionIncrement == 0  &&  (latitudeOfLastGridPoint-latitudeOfFirstGridPoint) != 0  && ni > 0)
      jDirectionIncrement = (latitudeOfLastGridPoint-latitudeOfFirstGridPoint)/nj;

    coordinateList.reserve(ni*nj);

    double y = latitudeOfFirstGridPoint;
    for (uint j=0; j < nj; j++)
    {
      double x = longitudeOfFirstGridPoint;
      if (longitudeOfFirstGridPoint >= 180000)
        x = longitudeOfFirstGridPoint - 360000;

      for (uint i=0; i < ni; i++)
      {
        double cx = x/1000;
        double cy = y/1000;
        T::Coordinate coord(cx,cy);
        coordinateList.push_back(coord);
        x += iDirectionIncrement;
      }
      y += jDirectionIncrement;
    }

    return coordinateList;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::Coordinate_vec LatLonImpl::getGridLatLonCoordinates() const
{
  try
  {
    return getGridCoordinates();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string LatLonImpl::getGridGeometryString() const
{
  try
  {
    char buf[1000];

    double y = (double)mGridArea.getLatitudeOfFirstGridPoint() / 1000;
    double x = (double)mGridArea.getLongitudeOfFirstGridPoint() / 1000;
    double dx = (double)mIDirectionIncrement / 1000;
    double dy = (double)mJDirectionIncrement / 1000;

    unsigned char scanningMode = (unsigned char)(mScanningMode.getScanningMode());

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


    sprintf(buf,"%d;id;name;%d;%d;%f;%f;%f;%f;%s;description",
      (int)T::GridProjection::LatLon,mNi,mNj,x,y,fabs(dx),fabs(dy),sm);

    return std::string(buf);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns.

        \return   The grid dimensions.
*/

T::Dimensions_opt LatLonImpl::getGridDimensions() const
{
  try
  {
    return T::Dimensions{mNi,mNj};
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method converts the latlon coordinates to the original coordinates.
    The original coordinates are returned in the 'x' and 'y' parameters. In this
    case the latlon coordinates are the same as the original coordinates.

        \param lat     The latitude.
        \param lon     The longitude.
        \param x       The x-coordinate of the original coordinates.
        \param y       The y-coordinate of the original coordinates.
*/

bool LatLonImpl::getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const
{
  try
  {
    x = lon;
    y = lat;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method converts the original coordinates to the latlon coordinates.
    The latlon coordinates are returned in the 'lat' and 'lon' parameters. In this
    case the latlon coordinates are the same as the original coordinates.

        \param x       The original x-coordinate.
        \param y       The original y-coordinate.
        \param lat     The returned latitude value.
        \param lon     The returned longitude value.
*/

bool LatLonImpl::getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const
{
  try
  {
    lat = x;
    lon = y;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method return the latlon coordinates of the give grid point.

        \param grid_i  The grid i-position.
        \param grid_j  The grid j-position.
        \param lat     The returned latitude value.
        \param lon     The returned longitude value.
*/

bool LatLonImpl::getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const
{
  try
  {
    uint ni = (uint)mNi;
    uint nj = (uint)mNj;

    if (ni == 0)
      ni = (uint)getGridOriginalColumnCount();

    if ((double)grid_i > (double)ni)
      return false;

    if ((double)grid_j > (double)nj)
      return false;

    double latitudeOfFirstGridPoint = (double)mGridArea.getLatitudeOfFirstGridPoint();
    double longitudeOfFirstGridPoint = (double)mGridArea.getLongitudeOfFirstGridPoint();
    double latitudeOfLastGridPoint = (double)mGridArea.getLatitudeOfLastGridPoint();
    double longitudeOfLastGridPoint = (double)mGridArea.getLongitudeOfLastGridPoint();

    double iDirectionIncrement = (double)mIDirectionIncrement;
    double jDirectionIncrement = (double)mJDirectionIncrement;

    unsigned char scanMode = (unsigned char)mScanningMode.getScanningMode();

    if ((scanMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;

    if ((scanMode & 0x40) == 0)
      jDirectionIncrement = -jDirectionIncrement;

    if (iDirectionIncrement == 0  &&  (longitudeOfLastGridPoint-longitudeOfFirstGridPoint) != 0  && ni > 0)
      iDirectionIncrement = (longitudeOfLastGridPoint-longitudeOfFirstGridPoint)/ni;

    if (jDirectionIncrement == 0  &&  (latitudeOfLastGridPoint-latitudeOfFirstGridPoint) != 0  && ni > 0)
      jDirectionIncrement = (latitudeOfLastGridPoint-latitudeOfFirstGridPoint)/nj;

    double y = latitudeOfFirstGridPoint + grid_j * jDirectionIncrement;
    double x = longitudeOfFirstGridPoint + grid_i * iDirectionIncrement;

    if (longitudeOfFirstGridPoint >= 180000)
      x = longitudeOfFirstGridPoint - 360000 + grid_i * iDirectionIncrement;

    lon = x/1000;
    lat = y/1000;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}






/*! \brief This method return the latlon coordinates of the give grid point.

        \param grid_i  The grid i-position.
        \param grid_j  The grid j-position.
        \param lat     The returned latitude value.
        \param lon     The returned longitude value.
*/

bool LatLonImpl::getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const
{
  try
  {
    uint ni = (uint)mNi;
    uint nj = (uint)mNj;

    if (ni == 0)
      ni = (uint)getGridOriginalColumnCount();

    if ((double)grid_i > (double)ni)
      return false;

    if ((double)grid_j > (double)nj)
      return false;

    double latitudeOfFirstGridPoint = (double)mGridArea.getLatitudeOfFirstGridPoint();
    double longitudeOfFirstGridPoint = (double)mGridArea.getLongitudeOfFirstGridPoint();
    double latitudeOfLastGridPoint = (double)mGridArea.getLatitudeOfLastGridPoint();
    double longitudeOfLastGridPoint = (double)mGridArea.getLongitudeOfLastGridPoint();

    double iDirectionIncrement = (double)mIDirectionIncrement;
    double jDirectionIncrement = (double)mJDirectionIncrement;

    unsigned char scanMode = (unsigned char)mScanningMode.getScanningMode();

    if ((scanMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;

    if ((scanMode & 0x40) == 0)
      jDirectionIncrement = -jDirectionIncrement;

    if (iDirectionIncrement == 0  &&  (longitudeOfLastGridPoint-longitudeOfFirstGridPoint) != 0  && ni > 0)
      iDirectionIncrement = (longitudeOfLastGridPoint-longitudeOfFirstGridPoint)/ni;

    if (jDirectionIncrement == 0  &&  (latitudeOfLastGridPoint-latitudeOfFirstGridPoint) != 0  && ni > 0)
      jDirectionIncrement = (latitudeOfLastGridPoint-latitudeOfFirstGridPoint)/nj;

    double y = latitudeOfFirstGridPoint + grid_j * jDirectionIncrement;
    double x = longitudeOfFirstGridPoint + grid_i * iDirectionIncrement;

    if (longitudeOfFirstGridPoint >= 180000)
      x = longitudeOfFirstGridPoint - 360000 + grid_i * iDirectionIncrement;

    lon = x/1000;
    lat = y/1000;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}






bool LatLonImpl::getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const
{
  try
  {
    return getGridLatLonCoordinatesByGridPoint(grid_i,grid_j,y,x);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool LatLonImpl::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  try
  {
    return getGridLatLonCoordinatesByGridPosition(grid_i,grid_j,y,x);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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

bool LatLonImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
{
  try
  {
    return getGridPointByOriginalCoordinates(lon,lat,grid_i,grid_j);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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

bool LatLonImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    uint ni = (uint)mNi;
    uint nj = (uint)mNj;

    if (ni == 0)
      ni = (uint)getGridOriginalColumnCount();

    double latitudeOfFirstGridPoint = (double)mGridArea.getLatitudeOfFirstGridPoint() / 1000;
    double longitudeOfFirstGridPoint = (double)mGridArea.getLongitudeOfFirstGridPoint() / 1000;
    double latitudeOfLastGridPoint = (double)mGridArea.getLatitudeOfLastGridPoint() / 1000;
    double longitudeOfLastGridPoint = (double)mGridArea.getLongitudeOfLastGridPoint() / 1000;
    double iDirectionIncrement = (double)mIDirectionIncrement / 1000;
    double jDirectionIncrement = (double)mJDirectionIncrement / 1000;

    unsigned char scanMode = (unsigned char)mScanningMode.getScanningMode();

    if ((scanMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;

    if ((scanMode & 0x40) == 0)
      jDirectionIncrement = -jDirectionIncrement;

    if (longitudeOfFirstGridPoint >= 180)
      longitudeOfFirstGridPoint -= 360;


    if (iDirectionIncrement == 0  &&  (longitudeOfLastGridPoint-longitudeOfFirstGridPoint) != 0  && ni > 0)
      iDirectionIncrement = (longitudeOfLastGridPoint-longitudeOfFirstGridPoint)/ni;

    if (jDirectionIncrement == 0  &&  (latitudeOfLastGridPoint-latitudeOfFirstGridPoint) != 0  && ni > 0)
      jDirectionIncrement = (latitudeOfLastGridPoint-latitudeOfFirstGridPoint)/nj;

    double aLat = y;
    double aLon = x;

    if (aLon < longitudeOfFirstGridPoint)
      aLon += 360;

    double latDiff = aLat - latitudeOfFirstGridPoint;
    double lonDiff = aLon - longitudeOfFirstGridPoint;

    double i = lonDiff / iDirectionIncrement;
    double j = latDiff / jDirectionIncrement;

    if (i < 0 ||  j < 0  ||  i >= (double)ni ||  j >= (double)nj)
      return false;

    grid_i = i;
    grid_j = j;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool LatLonImpl::reverseXDirection() const
{
  try
  {
    unsigned char scanMode = (unsigned char)mScanningMode.getScanningMode();

    if ((scanMode & 0x80) != 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool LatLonImpl::reverseYDirection() const
{
  try
  {
    unsigned char scanMode = (unsigned char)mScanningMode.getScanningMode();

    if ((scanMode & 0x40) == 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void LatLonImpl::initSpatialReference()
{
  try
  {
    // ### Set geographic coordinate system.

    const char *pszGeogName = "UNKNOWN";
    const char *pszDatumName = "UNKNOWN";
    const char *pszSpheroidName = "UNKNOWN";
    double dfSemiMajor = 6371229;
    double dfInvFlattening = 0.0;

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

    uint ni = (uint)mNi;
    if (ni == 0)
      ni = (uint)getGridOriginalColumnCount();

    double iDirectionIncrement = (double)mIDirectionIncrement / 1000;
    if (iDirectionIncrement == 0)
    {
      double longitudeOfFirstGridPoint = (double)mGridArea.getLongitudeOfFirstGridPoint() / 1000;
      double longitudeOfLastGridPoint = (double)mGridArea.getLongitudeOfLastGridPoint() / 1000;
      iDirectionIncrement = (longitudeOfLastGridPoint-longitudeOfFirstGridPoint)/ni;
    }


    double len = (ni+1)* iDirectionIncrement;

    if (len >= 360)
      mGlobal = true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void LatLonImpl::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    LatLon::print(stream,level,optionFlags);

    stream << space(level+1) << "LatLonImpl\n";

    if (optionFlags & GRID::PrintFlag::coordinates)
    {
      stream << space(level+1) << "- Coordinates (of the grid corners):\n";

      T::Coordinate_vec coordinateList = getGridCoordinates();

      // ### Printing coordinates close to the grid corners.

      int nx = (int)mNi;
      int ny = (int)mNj;

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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}



}  // namespace GRIB1
}  // namespace SmartMet
