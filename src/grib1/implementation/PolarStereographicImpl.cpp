#include "PolarStereographicImpl.h"
#include "../Properties.h"
#include "../../common/Exception.h"
#include "../../common/GeneralFunctions.h"
#include "../../common/GeneralDefinitions.h"
#include "../../grid/PrintOptions.h"
#include "../../grid/Typedefs.h"

namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class. */

PolarStereographicImpl::PolarStereographicImpl()
{
  try
  {
    mGridProjection = T::GridProjectionValue::PolarStereographic;
    mSr_polarSterographic = nullptr;
    mCt_latlon2pst = nullptr;
    mCt_pst2latlon = nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The copy constructor of the class. */

PolarStereographicImpl::PolarStereographicImpl(const PolarStereographicImpl& other)
:PolarStereographic(other)
{
  try
  {
    mSr_polarSterographic = nullptr;
    mCt_latlon2pst = nullptr;
    mCt_pst2latlon = nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The destructor of the class. */

PolarStereographicImpl::~PolarStereographicImpl()
{
  try
  {
    if (mSr_polarSterographic != nullptr)
      mSpatialReference.DestroySpatialReference(mSr_polarSterographic);

    if (mCt_latlon2pst != nullptr)
      OCTDestroyCoordinateTransformation(mCt_latlon2pst);

    if (mCt_pst2latlon != nullptr)
      OCTDestroyCoordinateTransformation(mCt_pst2latlon);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





/*! \brief The method returns a duplicate of the current object. */

GridDefinition* PolarStereographicImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new PolarStereographicImpl(*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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

void PolarStereographicImpl::read(MemoryReader& memoryReader)
{
  try
  {
    PolarStereographic::read(memoryReader);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

         \return   The grid coordinates.
*/

T::Coordinate_vec PolarStereographicImpl::getGridOriginalCoordinates() const
{
  try
  {
    T::Coordinate_vec coordinateList;

    uint nx = mNx;
    uint ny = mNy;


    double latitudeOfFirstGridPoint = C_DOUBLE(mLatitudeOfFirstGridPoint) / 1000;
    double longitudeOfFirstGridPoint = C_DOUBLE(mLongitudeOfFirstGridPoint) / 1000;

    double dx = C_DOUBLE(mDxInMetres);
    double dy = C_DOUBLE(mDyInMetres);


    unsigned char scanningMode = mScanningMode.getScanningMode();

    if ((scanningMode & 0x80) != 0)
      dx = -dx;

    if ((scanningMode & 0x40) == 0)
      dy = -dy;

    mCt_latlon2pst->Transform(1,&longitudeOfFirstGridPoint,&latitudeOfFirstGridPoint);

    coordinateList.reserve(nx*ny);

    double y = latitudeOfFirstGridPoint;
    for (uint j=0; j < ny; j++)
    {
      double x = longitudeOfFirstGridPoint;

      for (uint i=0; i < nx; i++)
      {
        T::Coordinate coord(x,y);
        coordinateList.push_back(coord);
        x += dx;
      }
      y += dy;
    }

    return coordinateList;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grid geometry string. This string can be used for comparing
    geometries in different grid files. For example, is is possible that a GRIB 1 message has
    the same geometry string as a GRIB 2 message, which means that they have same geometries.
    This comparison is more reliable than the hash comparison.

        \return   The grid geometry string.
*/

std::string PolarStereographicImpl::getGridGeometryString() const
{
  try
  {
    char buf[1000];

    double y = C_DOUBLE(mLatitudeOfFirstGridPoint) / 1000;
    double x = C_DOUBLE(mLongitudeOfFirstGridPoint) / 1000;
    double dx = C_DOUBLE(mDxInMetres);
    double dy = C_DOUBLE(mDyInMetres);
    double orientation = C_DOUBLE(mOrientationOfTheGrid)/1000;

    unsigned char scanningMode = mScanningMode.getScanningMode();

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

    sprintf(buf,"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;description",
        T::GridProjectionValue::PolarStereographic,mNx,mNy,x,y,fabs(dx),fabs(dy),sm,orientation,60.0);

    return std::string(buf);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns.

        \return   The grid dimensions.
*/

T::Dimensions PolarStereographicImpl::getGridDimensions() const
{
  try
  {
    return T::Dimensions(mNx,mNy);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool PolarStereographicImpl::getGridMetricCellSize(double& width,double& height) const
{
  try
  {
    width = C_DOUBLE(mDxInMetres) / 1000;
    height = C_DOUBLE(mDyInMetres) / 1000;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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

bool PolarStereographicImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    uint nx = mNx;
    uint ny = mNy;

    double latitudeOfFirstGridPoint = C_DOUBLE(mLatitudeOfFirstGridPoint) / 1000;
    double longitudeOfFirstGridPoint = C_DOUBLE(mLongitudeOfFirstGridPoint) / 1000;

    double dx = C_DOUBLE(mDxInMetres);
    double dy = C_DOUBLE(mDyInMetres);

    unsigned char scanningMode = mScanningMode.getScanningMode();

    if ((scanningMode & 0x80) != 0)
      dx = -dx;

    if ((scanningMode & 0x40) == 0)
      dy = -dy;

    double fX = longitudeOfFirstGridPoint;
    double fY = latitudeOfFirstGridPoint;

    mCt_latlon2pst->Transform(1,&fX,&fY);

    double xDiff = x - fX;
    double yDiff = y - fY;

    double i = xDiff / dx;
    double j = yDiff / dy;

    if (i < 0 ||  j < 0  ||  i >= C_DOUBLE(nx) ||  j > C_DOUBLE(ny))
      return false;

    grid_i = i;
    grid_j = j;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






/*! \brief The method returns 'true' if the grid horizontal values are in the reverse order.

        \return   The method returns 'true' if the grid horizontal values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool PolarStereographicImpl::reverseXDirection() const
{
  try
  {
    unsigned char scanMode = mScanningMode.getScanningMode();

    if ((scanMode & 0x80) != 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns 'true' if the grid vertical values are in the reverse order.

        \return   The method returns 'true' if the grid vertical values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool PolarStereographicImpl::reverseYDirection() const
{
  try
  {
    unsigned char scanMode = mScanningMode.getScanningMode();

    if ((scanMode & 0x40) == 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method is used for fetching a (long long ) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the requested property is returned in this parameter.
        \return            The method returns true if the value of the requested property was found.
*/

bool PolarStereographicImpl::getProperty(uint propertyId,long long& value)
{
  try
  {
    switch (propertyId)
    {
      case Property::GridSection::PolarStereographic::Nx:
        value = getNx();
        return true;

      case Property::GridSection::PolarStereographic::Ny:
        value = getNy();
        return true;

      case Property::GridSection::PolarStereographic::LatitudeOfFirstGridPoint:
        value = getLatitudeOfFirstGridPoint();
        return true;

      case Property::GridSection::PolarStereographic::LongitudeOfFirstGridPoint:
        value = getLongitudeOfFirstGridPoint();
        return true;

      case Property::GridSection::PolarStereographic::OrientationOfTheGrid:
        value = getOrientationOfTheGrid();
        return true;

      case Property::GridSection::PolarStereographic::DxInMetres:
        value = getDxInMetres();
        return true;

      case Property::GridSection::PolarStereographic::DyInMetres:
        value = getDyInMetres();
        return true;

      case Property::GridSection::PolarStereographic::ProjectionCentreFlag:
        value = getProjectionCentreFlag();
        return true;
    }

    return GridDefinition::getProperty(propertyId,value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






/*! \brief The method is used for setting a (long long) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool PolarStereographicImpl::setProperty(uint propertyId,long long value)
{
  try
  {
    switch (propertyId)
    {
      case Property::GridSection::PolarStereographic::Nx:
        setNx(value);
        return true;

      case Property::GridSection::PolarStereographic::Ny:
        setNy(value);
        return true;

      case Property::GridSection::PolarStereographic::LatitudeOfFirstGridPoint:
        setLatitudeOfFirstGridPoint(value);
        return true;

      case Property::GridSection::PolarStereographic::LongitudeOfFirstGridPoint:
        setLongitudeOfFirstGridPoint(value);
        return true;

      case Property::GridSection::PolarStereographic::OrientationOfTheGrid:
        setOrientationOfTheGrid(value);
        return true;

      case Property::GridSection::PolarStereographic::DxInMetres:
        setDxInMetres(value);
        return true;

      case Property::GridSection::PolarStereographic::DyInMetres:
        setDyInMetres(value);
        return true;

      case Property::GridSection::PolarStereographic::ProjectionCentreFlag:
        setProjectionCentreFlag(value);
        return true;
    }

    return GridDefinition::setProperty(propertyId,value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void PolarStereographicImpl::initSpatialReference()
{
  try
  {
    // ### Check that we have all necessary values needed by this method.

    double dfCenterLat = 60000;
    auto dfCenterLong = mOrientationOfTheGrid;

    // ### Set geographic coordinate system.

    const char *pszGeogName = "UNKNOWN";
    const char *pszDatumName = "UNKNOWN";
    const char *pszSpheroidName = "UNKNOWN";
    double dfSemiMajor =  6367470;
    double dfInvFlattening = 0.0;

    dfSemiMajor = getMajorAxis(mResolutionFlags.getResolutionAndComponentFlags());
    dfInvFlattening = getFlattening(mResolutionFlags.getResolutionAndComponentFlags());

    mSpatialReference.SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);


    // ### Set the projection and the linear units for the projection.

    double centerLat = C_DOUBLE(dfCenterLat) / 1000;
    double centerLon = C_DOUBLE(dfCenterLong) / 1000;
    double dfScale = 1.0;
    double dfFalseEasting = 0.0;
    double dfFalseNorthing = 0.0;

    mSpatialReference.SetPS(centerLat,centerLon,dfScale,dfFalseEasting,dfFalseNorthing);
    mSpatialReference.SetTargetLinearUnits("PROJCS", SRS_UL_METER, 1.0);


    // ### Validate the spatial reference.

    auto errorCode = mSpatialReference.Validate();
    if (errorCode != OGRERR_NONE)
    {
      SmartMet::Spine::Exception exception(BCP,"The spatial reference is not valid!");
      exception.addParameter("ErrorCode",std::to_string(errorCode));
      throw exception;
    }


    // ### Coordinate converters

    OGRSpatialReference sr_latlon;
    sr_latlon.importFromEPSG(4326);

    mSr_polarSterographic = mSpatialReference.Clone();

    mCt_latlon2pst = OGRCreateCoordinateTransformation(&sr_latlon,mSr_polarSterographic);
    if (mCt_latlon2pst == nullptr)
      throw SmartMet::Spine::Exception(BCP,"Cannot create coordinate transformation!");

    mCt_pst2latlon = OGRCreateCoordinateTransformation(mSr_polarSterographic,&sr_latlon);
    if (mCt_pst2latlon == nullptr)
      throw SmartMet::Spine::Exception(BCP,"Cannot create coordinate transformation!");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void PolarStereographicImpl::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    PolarStereographic::print(stream,level,optionFlags);
    stream << space(level+1) << "PolarStereographicImpl\n";

    if (optionFlags & GRID::PrintFlag::coordinates)
    {
      stream << space(level+1) << "- Coordinates (of the grid corners):\n";
      T::Coordinate_vec coordinateList = getGridOriginalCoordinates();

      int nx = C_INT(mNx);
      int ny = C_INT(mNy);

      char str[200];
      uint c = 0;
      for (int y=0; y < ny; y++)
      {
        for (int x=0; x < nx; x++)
        {
          if ((y < 3  ||  y >= ny-3)  &&  (x < 3  ||  x >= nx-3))
          {
            T::Coordinate coord = coordinateList.at(c);

            if (mCt_pst2latlon)
            {
              double lon = coord.x();
              double lat = coord.y();
              if (mCt_pst2latlon->Transform(1,&lon,&lat))
              {
                sprintf(str,"* [%03d,%03d] %f,%f => %f,%f",x,y,coord.x(),coord.y(),lon,lat);
                stream << space(level+2) << str << "\n";
              }
            }
          }
          c++;
        }
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}



}  // namespace GRIB1
}  // namespace SmartMet
