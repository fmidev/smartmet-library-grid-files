#include "PolarStereographicImpl.h"
#include "../Properties.h"
#include <macgyver/Exception.h>
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
    mDxx = 0;
    mDyy = 0;
    mStartX = 0;
    mStartY = 0;
    mInitialized = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

PolarStereographicImpl::PolarStereographicImpl(const PolarStereographicImpl& other)
:PolarStereographic(other)
{
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

PolarStereographicImpl::~PolarStereographicImpl()
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





/*! \brief The method returns a duplicate of the current object. */

GridDefinition* PolarStereographicImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new PolarStereographicImpl(*this);
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

void PolarStereographicImpl::read(MemoryReader& memoryReader)
{
  try
  {
    PolarStereographic::read(memoryReader);
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

T::Coordinate_svec PolarStereographicImpl::getGridOriginalCoordinatesNoCache() const
{
  try
  {
    T::Coordinate_svec coordinateList(new T::Coordinate_vec());

    uint nx = mNx;
    uint ny = mNy;

    coordinateList->reserve(nx*ny);

    double y = mStartY;
    for (uint j=0; j < ny; j++)
    {
      double x = mStartX;

      for (uint i=0; i < nx; i++)
      {
        T::Coordinate coord(x,y);
        coordinateList->emplace_back(coord);
        x += mDxx;
      }
      y += mDyy;
    }

    return coordinateList;
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

bool PolarStereographicImpl::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  try
  {
    if (grid_i < 0 ||  grid_i >= C_DOUBLE(mNx))
      return false;

    if (grid_j < 0 ||  grid_j >= C_DOUBLE(mNy))
      return false;

    x = mStartX + grid_i * mDxx;
    y = mStartY + grid_j * mDyy;

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

std::string PolarStereographicImpl::getGridGeometryString() const
{
  try
  {
    char buf[1000];

    double y = C_DOUBLE(mLatitudeOfFirstGridPoint) / 1000;
    double x = getLongitude(C_DOUBLE(mLongitudeOfFirstGridPoint) / 1000);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::size_t PolarStereographicImpl::getGridColumnCount() const
{
  try
  {
    return mNx;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::size_t PolarStereographicImpl::getGridRowCount() const
{
  try
  {
    return mNy;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void PolarStereographicImpl::init() const
{
  try
  {
    if (mInitialized)
      return;

    double dxx = C_DOUBLE(mDxInMetres);
    double dyy = C_DOUBLE(mDyInMetres);

    unsigned char scanningMode = mScanningMode.getScanningMode();

    mDxx = dxx;
    mDyy = dyy;

    if ((scanningMode & 0x80) != 0)
      mDxx = -dxx;

    if ((scanningMode & 0x40) == 0)
      mDyy = -dyy;

    double lon = C_DOUBLE(mLongitudeOfFirstGridPoint) / 1000;
    double lat = C_DOUBLE(mLatitudeOfFirstGridPoint) / 1000;

    double startX = lon;
    double startY = lat;

    convert(latlonSpatialReference,mSpatialReference,1,&startX,&startY);

    mStartX = startX;
    mStartY = startY;

    mInitialized = true;
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

bool PolarStereographicImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    double xDiff = x - mStartX;
    double yDiff = y - mStartY;

    double i = xDiff / mDxx;
    double j = yDiff / mDyy;

    grid_i = i;
    grid_j = j;

    if (i < 0 ||  j < 0  ||  i >= C_DOUBLE(mNx) ||  j > C_DOUBLE(mNy))
      return false;

    return true;
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void PolarStereographicImpl::getProperties(T::PropertySettingVec& properties)
{
  try
  {
    GridDefinition::getProperties(properties);

    properties.emplace_back((uint)Property::GridSection::PolarStereographic::Nx,getNx());
    properties.emplace_back((uint)Property::GridSection::PolarStereographic::Ny,getNy());
    properties.emplace_back((uint)Property::GridSection::PolarStereographic::LatitudeOfFirstGridPoint,getLatitudeOfFirstGridPoint());
    properties.emplace_back((uint)Property::GridSection::PolarStereographic::LongitudeOfFirstGridPoint,getLongitudeOfFirstGridPoint());
    properties.emplace_back((uint)Property::GridSection::PolarStereographic::OrientationOfTheGrid,getOrientationOfTheGrid());
    properties.emplace_back((uint)Property::GridSection::PolarStereographic::DxInMetres,getDxInMetres());
    properties.emplace_back((uint)Property::GridSection::PolarStereographic::DyInMetres,getDyInMetres());
    properties.emplace_back((uint)Property::GridSection::PolarStereographic::ProjectionCentreFlag,getProjectionCentreFlag());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
        if (value >= 0)
          setLongitudeOfFirstGridPoint(value);
        else
          setLongitudeOfFirstGridPoint(value + 360000);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void PolarStereographicImpl::initSpatialReference()
{
  try
  {
    mSpatialReference = getSpatialReference();
    if (!mSpatialReference)
    {
      mSpatialReference.reset(new T::SpatialRef());
      addSpatialReference(mSpatialReference);

      // ### Check that we have all necessary values needed by this method.

      double dfCenterLat = 60000;
      auto dfCenterLong = mOrientationOfTheGrid;

      // ### Set geographic coordinate system.

      const char *pszGeogName = "UNKNOWN";
      const char *pszDatumName = "UNKNOWN";
      const char *pszSpheroidName = "UNKNOWN";
      double dfSemiMajor = getMajorAxis(mResolutionFlags.getResolutionAndComponentFlags());
      double dfFlattening = getFlattening(mResolutionFlags.getResolutionAndComponentFlags());
      double dfInvFlattening = 0.0;
      if (dfFlattening != 0)
        dfInvFlattening = 1/dfFlattening;

      mSpatialReference->SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);


      // ### Set the projection and the linear units for the projection.

      double centerLat = C_DOUBLE(dfCenterLat) / 1000;
      double centerLon = C_DOUBLE(dfCenterLong) / 1000;
      double dfScale = 1.0;
      double dfFalseEasting = 0.0;
      double dfFalseNorthing = 0.0;

      mSpatialReference->SetPS(centerLat,centerLon,dfScale,dfFalseEasting,dfFalseNorthing);
      mSpatialReference->SetTargetLinearUnits("PROJCS", SRS_UL_METER, 1.0);
      mSpatialReference->SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);


      // ### Validate the spatial reference.

      auto errorCode = mSpatialReference->Validate();
      if (errorCode != OGRERR_NONE)
      {
        Fmi::Exception exception(BCP,"The spatial reference is not valid!");
        exception.addParameter("ErrorCode",std::to_string(errorCode));
        throw exception;
      }
    }

    init();
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

void PolarStereographicImpl::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    PolarStereographic::print(stream,level,optionFlags);
    stream << space(level+1) << "PolarStereographicImpl (Grib1)\n";

    if (optionFlags & GRID::PrintFlag::coordinates)
    {
      stream << space(level+1) << "- Coordinates (of the grid corners):\n";
      T::Coordinate_svec coordinateList = getGridOriginalCoordinatesNoCache();

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
            T::Coordinate coord = coordinateList->at(c);

            double lon = coord.x();
            double lat = coord.y();
            if (convert(latlonSpatialReference,mSpatialReference,1,&lon,&lat))
            {
              sprintf(str,"* [%03d,%03d] %f,%f => %f,%f",x,y,coord.x(),coord.y(),lon,lat);
              stream << space(level+2) << str << "\n";
            }
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



}  // namespace GRIB1
}  // namespace SmartMet
