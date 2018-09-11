#include "Message.h"
#include "../common/CoordinateConversions.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"
#include "../common/GeneralDefinitions.h"
#include "../common/GraphFunctions.h"
#include "../common/Point.h"
#include "../common/InterpolationFunctions.h"
#include "../common/ShowFunction.h"
#include "../identification/GridDef.h"


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{
namespace GRID
{

typedef std::vector<float> AngleList;
typedef std::map<int,AngleList> AngleCache;

AngleCache gridAngleCache;



/*! \brief The constructor of the class. */

Message::Message()
{
  FUNCTION_TRACE
  try
  {
    mMessageIndex = 0;
    mGrib1ParameterLevelId = 0;
    mGrib2ParameterLevelId = 0;
    mFmiParameterLevelId = 0;
    mDefaultInterpolationMethod = T::AreaInterpolationMethod::Nearest;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The copy constructor of the class. */

Message::Message(const Message& message)
{
  FUNCTION_TRACE
  try
  {
    mMessageIndex = message.mMessageIndex;
    mGribParameterId = message.mGribParameterId;
    mGrib1ParameterLevelId = message.mGrib1ParameterLevelId;
    mGrib2ParameterLevelId = message.mGrib2ParameterLevelId;
    mGribParameterName = message.mGribParameterName;
    mGribParameterDescription = message.mGribParameterDescription;
    mGribParameterUnits = message.mGribParameterUnits;
    mFmiProducerName = message.mFmiProducerName;
    mFmiParameterId = message.mFmiParameterId;
    mFmiParameterLevelId = message.mFmiParameterLevelId;
    mFmiParameterName = message.mFmiParameterName;
    mFmiParameterDescription = message.mFmiParameterDescription;
    mFmiParameterUnits = message.mFmiParameterUnits;
    mCdmParameterId = message.mCdmParameterId;
    mCdmParameterName = message.mCdmParameterName;
    mNewbaseParameterId = message.mNewbaseParameterId;
    mNewbaseParameterName = message.mNewbaseParameterName;
    mVirtualFileId = message.mVirtualFileId;
    mDefaultInterpolationMethod = message.mDefaultInterpolationMethod;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The destructor of the class. */

Message::~Message()
{
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current message.
*/

void Message::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method can be used in order to find the file id of the current file.

        \return  The file id of  the grib file.
*/

uint Message::getFileId() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method can be used in order to find out the message's start
    position in the grib file.

        \return  The message's start position in the grib file.
*/

T::FilePosition Message::getFilePosition() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





uint Message::getMessageIndex() const
{
  FUNCTION_TRACE
  try
  {
    return mMessageIndex;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::setMessageIndex(uint index)
{
  FUNCTION_TRACE
  try
  {
    mMessageIndex = index;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the reference time of the current message. The forecast
    times are calculated from this.

        \return   The reference time of the current message.
*/

T::TimeString Message::getReferenceTime() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





uint Message::getGribCentre() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





uint Message::getGribSubCentre() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the forecast start time. This is calculated from the reference
    time and other time parameters (=> NormalProduct->parameter()).

        \return   The forecast start time of the current message.
*/

T::TimeString Message::getForecastTime() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the hash of the grid.

        \return   The hash of the grid.
*/

T::Hash Message::getGridHash() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the type of the grid.

        \return   The type of the grid (expressed as an enum value).
*/

T::GridProjection Message::getGridProjection() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the type of the grid layout.

        \return   The layout of the grid (expressed as an enum value).
*/

T::GridLayout Message::getGridLayout() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the grid definition string (=> Projection name).

        \return   The projection used in the current grid (LatLon, Mercator, etc.)
*/

std::string Message::getGridProjectionString() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

         \return   The grid coordinates.
*/

T::Coordinate_vec Message::getGridCoordinates() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





T::Coordinate_vec Message::getGridLatLonCoordinates() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns. In this case we can find out the grid
    dimensions by using the 'getGridOriginalRowCount' and 'getGridOriginalColumnCount' methods.

        \return   The grid dimensions.
*/

T::Dimensions Message::getGridDimensions() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the number of rows used in the original grid.

       \return   The number of the grid rows.
*/

std::size_t Message::getGridOriginalRowCount() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the number of columns used in the given original grid row.

        \param row    The grid row index (= j-position).
        \return       The number of columns in the given grid row.
*/

std::size_t Message::getGridOriginalColumnCount(std::size_t row) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the maximum number of the columns used in the original grid
    If the grid is irregular, this method returns the length of the longest row.

         \return   The maximum number of the columns in the grid.
*/

std::size_t Message::getGridOriginalColumnCount() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the number of original values defined in the original grid.

        \return   The number of the values in the original grid.
*/

std::size_t Message::getGridOriginalValueCount() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the index of given grid position in the original grid data.
    In the case of irregular grid the grid rows might contain different number of
    columns. If the given grid position is outside of the grid data then the method
    returns -1. This is the case when the grid column (grid_i) is bigger than
    the length of the given grid row (grid_j), or if the given grid row (grid_j)
    is bigger than the actual number of grid rows.

        \param grid_i    The grid i-position.
        \param grid_j    The grid j-position.
        \return          The index of the original data position. If the position
                         is outside of the grid data then the method return -1.
*/

int Message::getGridOriginalValueIndex(uint grid_i,uint grid_j) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns 'true' if the grid is global (i.e. goes around the globe).
    If the grid is global then we should be able to interpolate over the grid borders.

      \return   The method returns 'true' if the grid data is global. Otherwise
                it returns 'false'
*/

bool Message::isGridGlobal() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





T::GeometryId Message::getGridGeometryId() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





std::string Message::getGridGeometryString() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





void Message::setGridGeometryId(T::GeometryId geometryId)
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





void Message::setGridValues(T::ParamValue_vec& values)
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief This method calculates the estimated grid position by using the latlon coordinates.
    The estimated grid position is returned in the 'grid_i' and 'grid_j' parameters.

        \param lat     The latitude.
        \param lon     The longitude.
        \param grid_i  The returned grid i-position.
        \param grid_j  The returned grid j-position.
        \return        Returns 'false' if the given coordinates are outside of the grid.
*/

bool Message::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j)  const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





float Message::getGridPointAngle(T::CoordinateType coordinateType,double x,double y) const
{
  FUNCTION_TRACE
  try
  {
    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        return getGridPointAngleByLatLonCoordinates(y,x);

      case T::CoordinateTypeValue::GRID_COORDINATES:
      {
        double lat = 0, lon = 0;
        getGridLatLonCoordinatesByGridPosition(x,y,lat,lon);
        return getGridPointAngleByLatLonCoordinates(lat,lon);
      }
      break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
      {
        double lat = 0, lon = 0;
        getGridLatLonCoordinatesByOriginalCoordinates(x,y,lat,lon);
        return getGridPointAngleByLatLonCoordinates(lat,lon);
      }
      break;

      default:
      {
        SmartMet::Spine::Exception exception(BCP,"Unknow coordinate type!",nullptr);
        exception.addParameter("Coordinate Type",std::to_string(coordinateType));
        throw exception;
      }
    }
    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





float Message::getGridPointAngleByLatLonCoordinates(double lat,double lon)  const
{
  FUNCTION_TRACE
  try
  {
    double PI = 3.1415926536;
    T::Dimensions d = getGridDimensions();
    if (d.getDimensions() != 2)
      return 0;

    double grid_i1 = 0;
    double grid_j1 = 0;
    double grid_i2 = 0;
    double grid_j2 = 0;

    if (getGridPointByLatLonCoordinates(lat,lon,grid_i1,grid_j1)  &&  getGridPointByLatLonCoordinates(lat+0.0001,lon,grid_i2,grid_j2))
    {
      double di = grid_i2-grid_i1;
      double dj = grid_j2-grid_j1;
      double angle = 0;
      double a = atan(fabs(dj)/fabs(di));
/*
      if (reverseYDirection())
        dj = -dj;

      if (reverseXDirection())
        di = -di;
*/
      if (dj >= 0  &&  di >= 0)
      {
        angle = -(PI/2 - a);
      }

      if (dj >= 0  &&  di < 0)
      {
        angle = PI/2 - a;
      }

      if (dj < 0  &&  di >= 0)
      {
        angle = -(PI/2 - a) + PI;
      }

      if (dj < 0  &&  di < 0)
      {
        angle = PI/2 - a + PI;
      }

      //printf("%f,%f ANGLE %f\n",di,dj,angle);
      return angle;
    }

    if (getGridPointByLatLonCoordinates(lat-0.0001,lon,grid_i1,grid_j1)  &&  getGridPointByLatLonCoordinates(lat,lon,grid_i2,grid_j2))
    {
      double di = grid_i2-grid_i1;
      double dj = grid_j2-grid_j1;
      double angle = 0;
      double a = atan(fabs(dj)/fabs(di));
/*
      if (reverseYDirection())
        dj = -dj;

      if (reverseXDirection())
        di = -di;
*/
      if (dj >= 0  &&  di >= 0)
      {
        angle = -(PI/2 - a);
      }

      if (dj >= 0  &&  di < 0)
      {
        angle = PI/2 - a;
      }

      if (dj < 0  &&  di >= 0)
      {
        angle = -(PI/2 - a) + PI;
      }

      if (dj < 0  &&  di < 0)
      {
        angle = PI/2 - a + PI;
      }

      //printf("* ANGLE %f\n",angle);
      return angle;
    }

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::getGridPointAngles(std::vector<float>& angles) const
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions d = getGridDimensions();
    if (d.getDimensions() != 2)
      return;

    int geometryId = getGridGeometryId();
    if (geometryId > 0)
    {
      auto it = gridAngleCache.find(geometryId);
      if (it != gridAngleCache.end())
      {
        angles = it->second;
        return;
      }
    }

    angles.clear();
    angles.reserve(d.ny() * d.nx());
    for (uint y=0; y < d.ny(); y++)
    {
      for (uint x=0; x < d.nx(); x++)
      {
        float angle = getGridPointAngle(T::CoordinateTypeValue::GRID_COORDINATES,x,y);
        angles.push_back(angle);
      }
    }

    if (geometryId > 0)
      gridAngleCache.insert(std::pair<int,AngleList>(geometryId,angles));
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


bool Message::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}






void Message::getGridProjectionAttributes(std::string prefix,T::AttributeList& attributeList) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the parameterId of the grid data. If the data cannot be recognized
     then the method return 0.

    Notice that the messages do not contain any exact parameter identifiers. In the GRIB_API attributeList
    files unique parameter identifiers are defined as a combination of multiple attributes.

    For example "temperature 2m" (parameterId = 167) is defined as follows:

      '167' = {
         discipline = 0 ;
         parameterCategory = 0 ;
         parameterNumber = 0 ;
         typeOfFirstFixedSurface = 103 ;
         scaleFactorOfFirstFixedSurface = 0 ;
         scaledValueOfFirstFixedSurface = 2 ;
      }

    So, in order to find an unique parameterId, we should compare several attribute values
    to the parameterId definition. After that we should select the closest match. The task
    is not easy, because some parameterId definition are overlapping. For example "temperature"
    (parameterId = 130) is defined as follows:

      '130' = {
         discipline = 0 ;
         parameterCategory = 0 ;
         parameterNumber = 0 ;
      }

    As can be seen, the definition looks similar to the "temperature 2m" definition. The difference is
    that there are no requirements for "scaleFactorOfFirstFixedSurface" and "scaledValueOfFirstFixedSurface"
    attributes. Let's assume that the "scaledValueOfFirstFixedSurface" attribute have value "5". In this case
    the parameter definition do not match "temperature 2m" definition, but it matches "temperature" definition.

    The point is that this kind of parameter identification is very confusing. In my opinion, there should
    be just one parameterId for the temperature and the level definition should not be part of the parameter
    definition.
*/

T::ParamId Message::getGribParameterId() const
{
  FUNCTION_TRACE
  try
  {
    return mGribParameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string Message::getGribParameterName() const
{
  FUNCTION_TRACE
  try
  {
    return mGribParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string Message::getGribParameterDescription() const
{
  FUNCTION_TRACE
  try
  {
    return mGribParameterDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string Message::getGribParameterUnits() const
{
  FUNCTION_TRACE
  try
  {
    return mGribParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




/*! \brief The method returns the grib 1 parameter level id.

         \return   The parameter level type (= enum value).
*/


T::ParamLevelId Message::getGrib1ParameterLevelId() const
{
  FUNCTION_TRACE
  try
  {
    return mGrib1ParameterLevelId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grib 2 parameter level id.

         \return   The parameter level type (= enum value).
*/


T::ParamLevelId Message::getGrib2ParameterLevelId() const
{
  FUNCTION_TRACE
  try
  {
    return mGrib2ParameterLevelId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string Message::getFmiProducerName() const
{
  FUNCTION_TRACE
  try
  {
    return mFmiProducerName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::ParamId Message::getFmiParameterId() const
{
  FUNCTION_TRACE
  try
  {
    return mFmiParameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::ParamLevelId Message::getFmiParameterLevelId() const
{
  FUNCTION_TRACE
  try
  {
    return mFmiParameterLevelId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string Message::getFmiParameterName() const
{
  FUNCTION_TRACE
  try
  {
    return mFmiParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string Message::getFmiParameterDescription() const
{
  FUNCTION_TRACE
  try
  {
    return mFmiParameterDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string Message::getFmiParameterUnits() const
{
  FUNCTION_TRACE
  try
  {
    return mFmiParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string Message::getCdmParameterId() const
{
  FUNCTION_TRACE
  try
  {
    return mCdmParameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string Message::getCdmParameterName() const
{
  FUNCTION_TRACE
  try
  {
    return mCdmParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string Message::getNewbaseParameterId() const
{
  FUNCTION_TRACE
  try
  {
    return mNewbaseParameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string Message::getNewbaseParameterName() const
{
  FUNCTION_TRACE
  try
  {
    return mNewbaseParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the parameter level.
    Sometime the parameter level is "included" in the parameter definition. I.e. there
    might be different parameterId for "temperature-2m" and "temperature-10m". On the other
    hand, there might be only one parameterId for "temperature" but several levels (2m, 10m, etc.).
    So, the same data can be defined in multiple ways.

         \return   The parameter level.
*/

T::ParamLevel Message::getGridParameterLevel() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the parameter level id.

         \return   The parameter level type (= enum value).
*/


T::ParamLevelId Message::getGridParameterLevelId() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the parameter level type string (define in Table 4.5).

        \return   The parameter level type (expressed in a string).
*/

std::string Message::getGridParameterLevelIdString() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the grid value in the given (exact) point.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.

        \return         The parameter value of the given grid point.
*/

T::ParamValue Message::getGridValueByGridPoint(uint grid_i,uint grid_j) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the grid value in the given original grid point.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.

        \return         The parameter value of the given grid point.
*/

T::ParamValue Message::getGridValueByOriginalGridPoint(uint grid_i,uint grid_j) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the minimum and maximum value used in the current grid.
    This functionality might help to visualize the grid data.

        \param minValue   The returned minimum parameter value in the grid.
        \param maxValue   The returned maximum parameter value in the grid.
*/

void Message::getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}



/*! \brief The method returns all grid data values (also missing values) as the grid
    would be regular. In the case of an irregular grid, the grid rows are filled so that
    the grid looks like a regular grid.

        \param values   The returned grid values.
*/

void Message::getGridValueVector(T::ParamValue_vec& values) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the original grid data values.
    If the grid is regular then the 'getGridValueVector()' method returns the same
    result as this method. However, if the grid is irregular then the grid rows
    might contain different number of columns. In this case the data should be
    processed row-by-row and the 'getGridOriginalColumnCount()' method should be
    used in order to find out the number of the columns used in each row. Also
    the 'getGridOriginalValueIndex()' method can be used in order to locate values
    in the returned vector.

        \param values   The returned grid values (original).
*/

void Message::getGridOriginalValueVector(T::ParamValue_vec& values) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





T::SpatialRef* Message::getSpatialReference() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the WKT (Well-Known-Text) of the current grid.

        \return   The WKT of the current grid.
*/

std::string Message::getWKT() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





short Message::getDefaultInterpolationMethod() const
{
  FUNCTION_TRACE
  try
  {
    return mDefaultInterpolationMethod;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool Message::reverseXDirection() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::reverseYDirection() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





short Message::getForecastType() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





short Message::getForecastNumber() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::setProperty(uint propertyId,long long value)
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





void Message::setFmiParameterId(T::ParamId fmiParameterId)
{
  FUNCTION_TRACE
  try
  {
    mFmiParameterId = fmiParameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::setFmiParameterLevelId(T::ParamLevelId fmiParameterLevelId)
{
  FUNCTION_TRACE
  try
  {
    mFmiParameterLevelId = fmiParameterLevelId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::setFmiParameterName(std::string fmiParameterName)
{
  FUNCTION_TRACE
  try
  {
    mFmiParameterName = fmiParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::setFmiParameterDescription(std::string fmiParameterDescr)
{
  FUNCTION_TRACE
  try
  {
    mFmiParameterDescription = fmiParameterDescr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::setFmiParameterUnits(std::string fmiParameterUnits)
{
  FUNCTION_TRACE
  try
  {
    mFmiParameterUnits = fmiParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::setGribParameterId(T::ParamId gribParameterId)
{
  FUNCTION_TRACE
  try
  {
    mGribParameterId = gribParameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::setGribParameterName(std::string gribParameterName)
{
  FUNCTION_TRACE
  try
  {
    mGribParameterName = gribParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::setGribParameterDescription(std::string gribParameterDescr)
{
  FUNCTION_TRACE
  try
  {
    mGribParameterDescription = gribParameterDescr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::setGribParameterUnits(std::string gribParameterUnits)
{
  FUNCTION_TRACE
  try
  {
    mGribParameterUnits = gribParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::setGrib1ParameterLevelId(T::ParamLevelId grib1ParameterLevelId)
{
  FUNCTION_TRACE
  try
  {
    mGrib1ParameterLevelId = grib1ParameterLevelId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::setGrib2ParameterLevelId(T::ParamLevelId grib2ParameterLevelId)
{
  FUNCTION_TRACE
  try
  {
    mGrib2ParameterLevelId = grib2ParameterLevelId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::setCdmParameterId(std::string cdmParameterId)
{
  FUNCTION_TRACE
  try
  {
    mCdmParameterId = cdmParameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::setCdmParameterName(std::string cdmParameterName)
{
  FUNCTION_TRACE
  try
  {
    mCdmParameterName = cdmParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::setNewbaseParameterId(std::string newbaseParameterId)
{
  FUNCTION_TRACE
  try
  {
    mNewbaseParameterId = newbaseParameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::setNewbaseParameterName(std::string newbaseParameterName)
{
  FUNCTION_TRACE
  try
  {
    mNewbaseParameterName = newbaseParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::getGridValueByPoint(T::CoordinateType coordinateType,double x,double y,short interpolationMethod,T::ParamValue& value) const
{
  FUNCTION_TRACE
  try
  {
    value = ParamValueMissing;
    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        value = getGridValueByLatLonCoordinate(y,x,interpolationMethod);
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        value = getGridValueByGridPoint(x,y,interpolationMethod);
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
         // TODO: Implementation required
         break;

      default:
      {
        SmartMet::Spine::Exception exception(BCP,"Unknow coordinate type!",nullptr);
        exception.addParameter("Coordinate Type",std::to_string(coordinateType));
        throw exception;
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::getGridValueVectorByPoint(T::CoordinateType coordinateType,double x,double y,uint vectorType,double_vec& valueVector) const
{
  FUNCTION_TRACE
  try
  {
    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
        getGridValueVectorByLatLonCoordinate(y,x,vectorType,valueVector);
        break;

      case T::CoordinateTypeValue::GRID_COORDINATES:
        getGridValueVectorByGridPoint(x,y,vectorType,valueVector);
        break;

      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
         // TODO: Implementation required
         break;

      default:
      {
        SmartMet::Spine::Exception exception(BCP,"Unknow coordinate type!",nullptr);
        exception.addParameter("Coordinate Type",std::to_string(coordinateType));
        throw exception;
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




void Message::getGridValueVectorByGridPoint(double grid_i,double grid_j,uint vectorType,double_vec& valueVector) const
{
  FUNCTION_TRACE
  try
  {
    double x = grid_i;
    double y = grid_j;

    uint x1 = C_UINT(floor(x));
    uint y1 = C_UINT(floor(y));
    uint x2 = x1+1;
    uint y2 = y1+1;

    switch (vectorType)
    {
      case T::AreaInterpolationMethod::None:
        valueVector.push_back(getGridValueByGridPoint(x1,y1));
        break;

      case T::AreaInterpolationMethod::Linear:
        valueVector.push_back(getGridValueByGridPoint_linearInterpolation(x,y));
        break;

      case T::AreaInterpolationMethod::Nearest:
        valueVector.push_back(getGridValueByGridPoint_nearest(x,y));
        break;

      case T::AreaInterpolationMethod::Min:
        valueVector.push_back(getGridValueByGridPoint_min(x,y));
        break;

      case T::AreaInterpolationMethod::Max:
        valueVector.push_back(getGridValueByGridPoint_max(x,y));
        break;

      case T::AreaInterpolationMethod::List:
        valueVector.push_back(2);
        valueVector.push_back(x-C_DOUBLE(x1));
        valueVector.push_back(y-C_DOUBLE(y1));
        valueVector.push_back(getGridValueByGridPoint(x1,y1));
        valueVector.push_back(getGridValueByGridPoint(x2,y1));
        valueVector.push_back(getGridValueByGridPoint(x2,y2));
        valueVector.push_back(getGridValueByGridPoint(x1,y2));
        break;

      case T::AreaInterpolationMethod::ListWithAngles:
        valueVector.push_back(7);
        valueVector.push_back(x-C_DOUBLE(x1));
        valueVector.push_back(y-C_DOUBLE(y1));
        valueVector.push_back(getGridPointAngle(T::CoordinateTypeValue::GRID_COORDINATES,grid_i,grid_j));
        valueVector.push_back(getGridPointAngle(T::CoordinateTypeValue::GRID_COORDINATES,C_DOUBLE(x1),C_DOUBLE(y1)));
        valueVector.push_back(getGridPointAngle(T::CoordinateTypeValue::GRID_COORDINATES,C_DOUBLE(x2),C_DOUBLE(y1)));
        valueVector.push_back(getGridPointAngle(T::CoordinateTypeValue::GRID_COORDINATES,C_DOUBLE(x2),C_DOUBLE(y2)));
        valueVector.push_back(getGridPointAngle(T::CoordinateTypeValue::GRID_COORDINATES,C_DOUBLE(x1),C_DOUBLE(y2)));
        valueVector.push_back(getGridValueByGridPoint(x1,y1));
        valueVector.push_back(getGridValueByGridPoint(x2,y1));
        valueVector.push_back(getGridValueByGridPoint(x2,y2));
        valueVector.push_back(getGridValueByGridPoint(x1,y2));
        break;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::getGridValueVectorByLatLonCoordinate(double lat,double lon,uint vectorType,double_vec& valueVector) const
{
  FUNCTION_TRACE
  try
  {
    double grid_i = 0;
    double grid_j = 0;

    if (getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j))
      getGridValueVectorByGridPoint(grid_i,grid_j,vectorType,valueVector);
/*
    printf("getGridValueVectorByLatLonCoordinate %f,%f => %f,%f\n",lat,lon,grid_i,grid_j);
    for (auto it = valueVector.begin(); it != valueVector.end(); ++it)
      std::cout << *it << "\n";
*/
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::getGridValueListByCircle(T::CoordinateType coordinateType,double origoX,double origoY,double radius,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions d = getGridDimensions();
    uint cols = d.nx();
    uint rows = d.ny();

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
      {
        double x1 = origoX;
        double dist = 0;
        while (dist < radius)
        {
          dist = latlon_distance(origoY,origoX,origoY,x1);
          x1 = x1 - 0.01;
        }

        double x2 = origoX;
        dist = 0;
        while (dist < radius)
        {
          dist = latlon_distance(origoY,origoX,origoY,x2);
          x2 = x2 + 0.01;
        }

        double y1 = origoY;
        dist = 0;
        while (dist < radius)
        {
          dist = latlon_distance(origoY,origoX,y1,origoX);
          y1 = y1 - 0.01;
        }

        double y2 = origoY;
        dist = 0;
        while (dist < radius)
        {
          dist = latlon_distance(origoY,origoX,y2,origoX);
          y2 = y2 + 0.01;
        }

        //printf("%f,%f  ...  %f,%f\n",x1,y1,x2,y2);
        std::vector<T::Coordinate> polygonPoints;
        polygonPoints.push_back(T::Coordinate(x1,y1));
        polygonPoints.push_back(T::Coordinate(x2,y1));
        polygonPoints.push_back(T::Coordinate(x2,y2));
        polygonPoints.push_back(T::Coordinate(x1,y2));

        T::GridValueList tmpValueList;
        getGridValueListByPolygon(coordinateType,polygonPoints,tmpValueList);

        uint len = tmpValueList.getLength();
        for (uint t=0; t<len; t++)
        {
          T::GridValue *rec = tmpValueList.getGridValueByIndex(t);
          if (latlon_distance(origoY,origoX,rec->mY,rec->mX) <= radius)
            valueList.addGridValue(new T::GridValue(*rec));
        }
      }
      return;


      case T::CoordinateTypeValue::GRID_COORDINATES:
      {
        std::vector<T::Point> gridPoints;

        getPointsInsideCircle(cols,rows,origoX,origoY,radius,gridPoints);
        for (auto it=gridPoints.begin(); it != gridPoints.end(); ++it)
        {
          T::GridValue *rec = new T::GridValue();

          rec->mX = it->x();
          rec->mY = it->y();
          rec->mValue = getGridValueByGridPoint(it->x(),it->y());
          valueList.addGridValue(rec);
        }
      }
      return;


      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
      {
        double newOrigoX = 0;
        double newOrigoY = 0;

        getGridLatLonCoordinatesByOriginalCoordinates(origoX,origoY,newOrigoY,newOrigoX);

        double x1 = newOrigoX;
        double dist = 0;
        while (dist < radius)
        {
          dist = latlon_distance(newOrigoY,newOrigoX,newOrigoY,x1);
          x1 = x1 - 0.01;
        }

        double x2 = newOrigoX;
        dist = 0;
        while (dist < radius)
        {
          dist = latlon_distance(newOrigoY,newOrigoX,newOrigoY,x2);
          x2 = x2 + 0.01;
        }

        double y1 = newOrigoY;
        dist = 0;
        while (dist < radius)
        {
          dist = latlon_distance(newOrigoY,newOrigoX,y1,newOrigoX);
          y1 = y1 - 0.01;
        }

        double y2 = newOrigoY;
        dist = 0;
        while (dist < radius)
        {
          dist = latlon_distance(newOrigoY,newOrigoX,y2,newOrigoX);
          y2 = y2 + 0.01;
        }

        double xx1 = 0;
        double yy1 = 0;
        double xx2 = 0;
        double yy2 = 0;

        getGridOriginalCoordinatesByLatLonCoordinates(y1,x1,xx1,yy1);
        getGridOriginalCoordinatesByLatLonCoordinates(y2,x2,xx2,yy2);

        //printf("%f,%f  ...  %f,%f\n",x1,y1,x2,y2);
        std::vector<T::Coordinate> polygonPoints;
        polygonPoints.push_back(T::Coordinate(xx1,yy1));
        polygonPoints.push_back(T::Coordinate(xx2,yy1));
        polygonPoints.push_back(T::Coordinate(xx2,yy2));
        polygonPoints.push_back(T::Coordinate(xx1,yy2));

        T::GridValueList tmpValueList;
        getGridValueListByPolygon(coordinateType,polygonPoints,tmpValueList);

        uint len = tmpValueList.getLength();
        for (uint t=0; t<len; t++)
        {
          T::GridValue *rec = tmpValueList.getGridValueByIndex(t);

          double lat = 0;
          double lon = 0;
          getGridLatLonCoordinatesByOriginalCoordinates(rec->mY,rec->mX,lat,lon);

          if (latlon_distance(origoY,origoX,lat,lon) <= radius)
            valueList.addGridValue(new T::GridValue(*rec));
        }
      }
      return;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::getGridValueListByPointList(T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short interpolationMethod,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    for (auto it = pointList.begin(); it != pointList.end(); ++it)
    {
      T::GridValue *rec = new T::GridValue();
      rec->mX = it->x();
      rec->mY = it->y();
      getGridValueByPoint(coordinateType,it->x(),it->y(),interpolationMethod,rec->mValue);
      valueList.addGridValue(rec);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::getGridValueListByPolygon(T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions d = getGridDimensions();
    uint cols = d.nx();
    uint rows = d.ny();

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
      {
        std::vector<T::Coordinate> newPolygonPoints;

        for (auto it = polygonPoints.begin(); it != polygonPoints.end(); ++it)
        {
          double grid_i = 0;
          double grid_j = 0;
          getGridPointByLatLonCoordinates(it->y(),it->x(),grid_i,grid_j);
          newPolygonPoints.push_back(T::Coordinate(grid_i,grid_j));
        }

        std::vector<T::Point> gridPoints;
        getPointsInsidePolygon(cols,rows,newPolygonPoints,gridPoints);

        for (auto it=gridPoints.begin(); it != gridPoints.end(); ++it)
        {
          T::GridValue *rec = new T::GridValue();

          double lat = 0;
          double lon = 0;
          if (getGridLatLonCoordinatesByGridPoint(it->x(),it->y(),lat,lon))
          {
            rec->mX = lon;
            rec->mY = lat;
              //printf("%d,%d => %f,%f => %f,%f\n",it->x(),it->y(),rec->mX,rec->mY,lon,lat);
          }

          rec->mValue = getGridValueByGridPoint(it->x(),it->y());
          valueList.addGridValue(rec);
        }
      }
      return;


      case T::CoordinateTypeValue::GRID_COORDINATES:
      {
        std::vector<T::Point> gridPoints;
        getPointsInsidePolygon(cols,rows,polygonPoints,gridPoints);

        for (auto it=gridPoints.begin(); it != gridPoints.end(); ++it)
        {
          T::GridValue *rec = new T::GridValue();

          rec->mX = it->x();
          rec->mY = it->y();
          rec->mValue = getGridValueByGridPoint(it->x(),it->y());
          valueList.addGridValue(rec);

          double lat = 0,lon = 0;
          getGridLatLonCoordinatesByGridPosition(it->x(),it->y(),lat,lon);
          //printf("%d,%d => %f,%f\n",it->x(),it->y(),lat,lon);

        }
      }
      return;


      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
      {
        std::vector<T::Coordinate> newPolygonPoints;

        for (auto it = polygonPoints.begin(); it != polygonPoints.end(); ++it)
        {
          double grid_i = 0;
          double grid_j = 0;
          getGridPointByOriginalCoordinates(it->x(),it->y(),grid_i,grid_j);
          newPolygonPoints.push_back(T::Coordinate(grid_i,grid_j));
        }

        std::vector<T::Point> gridPoints;
        getPointsInsidePolygon(cols,rows,newPolygonPoints,gridPoints);

        for (auto it=gridPoints.begin(); it != gridPoints.end(); ++it)
        {
          T::GridValue *rec = new T::GridValue();

          double x = 0;
          double y = 0;
          if (getGridOriginalCoordinatesByGridPoint(it->x(),it->y(),x,y))
          {
            rec->mX = x;
            rec->mY = y;
              //printf("%d,%d => %f,%f => %f,%f\n",it->x(),it->y(),rec->mX,rec->mY,lon,lat);
          }

          rec->mValue = getGridValueByGridPoint(it->x(),it->y());
          valueList.addGridValue(rec);
        }
      }
      return;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






void Message::getGridValueListByPolygonPath(T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions d = getGridDimensions();
    uint cols = d.nx();
    uint rows = d.ny();

    switch (coordinateType)
    {
      case T::CoordinateTypeValue::UNKNOWN:
      case T::CoordinateTypeValue::LATLON_COORDINATES:
      {
        std::vector<std::vector<T::Coordinate>> newPolygonPath;

        for (auto polygonPoints = polygonPath.begin(); polygonPoints != polygonPath.end(); ++polygonPoints)
        {
          std::vector<T::Coordinate> newPolygonPoints;

          for (auto it = polygonPoints->begin(); it != polygonPoints->end(); ++it)
          {
            double grid_i = 0;
            double grid_j = 0;
            getGridPointByLatLonCoordinates(it->y(),it->x(),grid_i,grid_j);
            newPolygonPoints.push_back(T::Coordinate(grid_i,grid_j));
          }
          newPolygonPath.push_back(newPolygonPoints);
        }

        std::vector<T::Point> gridPoints;
        getPointsInsidePolygonPath(cols,rows,newPolygonPath,gridPoints);

        for (auto it=gridPoints.begin(); it != gridPoints.end(); ++it)
        {
          T::GridValue *rec = new T::GridValue();

          double lat = 0;
          double lon = 0;
          if (getGridLatLonCoordinatesByGridPoint(it->x(),it->y(),lat,lon))
          {
            rec->mX = lon;
            rec->mY = lat;
            //printf("%d,%d => %f,%f => %f,%f\n",it->x(),it->y(),rec->mX,rec->mY,lon,lat);
          }

          rec->mValue = getGridValueByGridPoint(it->x(),it->y());
          valueList.addGridValue(rec);
        }
      }
      return;


      case T::CoordinateTypeValue::GRID_COORDINATES:
      {
        std::vector<T::Point> gridPoints;
        getPointsInsidePolygonPath(cols,rows,polygonPath,gridPoints);

        for (auto it=gridPoints.begin(); it != gridPoints.end(); ++it)
        {
          T::GridValue *rec = new T::GridValue();

          rec->mX = it->x();
          rec->mY = it->y();
          rec->mValue = getGridValueByGridPoint(it->x(),it->y());
          valueList.addGridValue(rec);
        }
      }
      return;


      case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
      {
        std::vector<std::vector<T::Coordinate>> newPolygonPath;

        for (auto polygonPoints = polygonPath.begin(); polygonPoints != polygonPath.end(); ++polygonPoints)
        {
          std::vector<T::Coordinate> newPolygonPoints;

          for (auto it = polygonPoints->begin(); it != polygonPoints->end(); ++it)
          {
            double grid_i = 0;
            double grid_j = 0;
            getGridPointByOriginalCoordinates(it->x(),it->y(),grid_i,grid_j);
            newPolygonPoints.push_back(T::Coordinate(grid_i,grid_j));
          }
          newPolygonPath.push_back(newPolygonPoints);
        }

        std::vector<T::Point> gridPoints;
        getPointsInsidePolygonPath(cols,rows,newPolygonPath,gridPoints);

        for (auto it=gridPoints.begin(); it != gridPoints.end(); ++it)
        {
          T::GridValue *rec = new T::GridValue();

          double x = 0;
          double y = 0;
          if (getGridOriginalCoordinatesByGridPoint(it->x(),it->y(),x,y))
          {
            rec->mX = x;
            rec->mY = y;
              //printf("%d,%d => %f,%f => %f,%f\n",it->x(),it->y(),rec->mX,rec->mY,lon,lat);
          }

          rec->mValue = getGridValueByGridPoint(it->x(),it->y());
          valueList.addGridValue(rec);
        }
      }
      return;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::getGridValueListByRectangle(T::CoordinateType coordinateType,double x1,double y1,double x2,double y2,bool gridRectangle,T::GridValueList& valueList) const
{
  FUNCTION_TRACE
  try
  {
    if (!gridRectangle)
    {
      // We can count missing corners directly from the opposite corners. This means
      // that the requested coordinate rectangle is not necessary a rectangle in the current grid.

      std::vector<T::Coordinate> polygonPoints;
      polygonPoints.push_back(T::Coordinate(x1,y1));
      polygonPoints.push_back(T::Coordinate(x2,y1));
      polygonPoints.push_back(T::Coordinate(x2,y2));
      polygonPoints.push_back(T::Coordinate(x1,y2));
      polygonPoints.push_back(T::Coordinate(x1,y1));

      getGridValueListByPolygon(coordinateType,polygonPoints,valueList);
    }
    else
    {
      // We want to get values from the inside of the grid rectangle. This means that we have to
      // calculate the grid position of the opposite corners first and after that we can define
      // the missing corners.

      switch (coordinateType)
      {
        case T::CoordinateTypeValue::UNKNOWN:
        case T::CoordinateTypeValue::LATLON_COORDINATES:
        {
          double gx1 = 0;
          double gy1 = 0;
          double gx2 = 0;
          double gy2 = 0;
          std::vector<T::Coordinate> polygonPoints;
          getGridPointByLatLonCoordinates(y1,x1,gx1,gy1);
          getGridPointByLatLonCoordinates(y2,x2,gx2,gy2);

          polygonPoints.push_back(T::Coordinate(gx1,gy1));
          polygonPoints.push_back(T::Coordinate(gx1,gy2));
          polygonPoints.push_back(T::Coordinate(gx2,gy2));
          polygonPoints.push_back(T::Coordinate(gx2,gy1));
          polygonPoints.push_back(T::Coordinate(gx1,gy1));

          double lat1 = 0,lon1 = 0;
          double lat2 = 0,lon2 = 0;
          getGridLatLonCoordinatesByGridPosition(gx1,gy2,lat1,lon1);
          getGridLatLonCoordinatesByGridPosition(gx2,gy1,lat2,lon2);

          //printf("LATLON AREA %f,%f  %f,%f  %f,%f  %f,%f\n",y1,x1,lat1,lon1,y2,x2,lat2,lon2);

          //printf("GRID AREA %f,%f  %f,%f  %f,%f  %f,%f\n",gx1,gy1,gx1,gy2,gx2,gy2,gx2,gy1);

          getGridValueListByPolygon(T::CoordinateTypeValue::GRID_COORDINATES,polygonPoints,valueList);
        }
        break;

        case T::CoordinateTypeValue::GRID_COORDINATES:
        {
          std::vector<T::Coordinate> polygonPoints;
          polygonPoints.push_back(T::Coordinate(x1,y1));
          polygonPoints.push_back(T::Coordinate(x1,y2));
          polygonPoints.push_back(T::Coordinate(x2,y2));
          polygonPoints.push_back(T::Coordinate(x2,y1));
          polygonPoints.push_back(T::Coordinate(x1,y1));
          getGridValueListByPolygon(T::CoordinateTypeValue::GRID_COORDINATES,polygonPoints,valueList);
        }
        break;

        case T::CoordinateTypeValue::ORIGINAL_COORDINATES:
        {
          double gx1 = 0;
          double gy1 = 0;
          double gx2 = 0;
          double gy2 = 0;
          std::vector<T::Coordinate> polygonPoints;
          getGridPointByOriginalCoordinates(x1,y1,gx1,gy1);
          getGridPointByOriginalCoordinates(x2,y2,gx2,gy2);
          polygonPoints.push_back(T::Coordinate(gx1,gy1));
          polygonPoints.push_back(T::Coordinate(gx1,gy2));
          polygonPoints.push_back(T::Coordinate(gx2,gy2));
          polygonPoints.push_back(T::Coordinate(gx2,gy1));
          polygonPoints.push_back(T::Coordinate(gx1,gy1));
          getGridValueListByPolygon(T::CoordinateTypeValue::GRID_COORDINATES,polygonPoints,valueList);
        }
        break;

        default:
        {
          SmartMet::Spine::Exception exception(BCP,"Unknow coordinate type!",nullptr);
          exception.addParameter("Coordinate Type",std::to_string(coordinateType));
          throw exception;
        }
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void Message::getGridValueVectorByCoordinateList(T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,short interpolationMethod,T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    for (auto it = coordinates.begin(); it != coordinates.end(); ++it)
    {
      T::ParamValue value;
      getGridValueByPoint(coordinateType,it->x(),it->y(),interpolationMethod,value);
      values.push_back(value);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the closest or the interpolated value in the given grid position.
    The basic idea is that the given position is inside the rectangular area which
    opposite corners are (floor(grid_i),floor(grid_j)) and (floor(grid_i)+1,floor(grid_j)+1).
    The 'interpolationMethod' parameter indicates whether we should return the value of
    the closest grid point or calculate it by interpolating.

        \param grid_i                 The grid i-position.
        \param grid_j                 The grid j-position.
        \param interpolationMethod    The interpolation method.
*/

T::ParamValue Message::getGridValueByGridPoint(double grid_i,double grid_j,short interpolationMethod) const
{
  FUNCTION_TRACE
  try
  {
    short ipm = interpolationMethod;

    if (interpolationMethod == T::AreaInterpolationMethod::Undefined)
      ipm = getDefaultInterpolationMethod();

    switch (ipm)
    {
      case T::AreaInterpolationMethod::None:
        return getGridValueByGridPoint_noInterpolation(grid_i,grid_j);

      case T::AreaInterpolationMethod::Nearest:
        return getGridValueByGridPoint_nearest(grid_i,grid_j);

      case T::AreaInterpolationMethod::Linear:
        return getGridValueByGridPoint_linearInterpolation(grid_i,grid_j);

      case T::AreaInterpolationMethod::Min:
        return getGridValueByGridPoint_min(grid_i,grid_j);

      case T::AreaInterpolationMethod::Max:
        return getGridValueByGridPoint_max(grid_i,grid_j);

      case T::AreaInterpolationMethod::External:
        return getGridValueByGridPoint_nearest(grid_i,grid_j);

      default:
        return getGridValueByGridPoint_nearest(grid_i,grid_j);
        // throw SmartMet::Spine::Exception(BCP,"Unknown 'interpolationMethod' parameter value!");
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the closest or the interpolated parameter value
    in the given latlon coordinates.

        \param lat                    The latitude.
        \param lon                    The longitude.
        \param interpolationMethod    The interpolation method.
        \return                       The closest of the interpolated value
                                      in the given latlon coordinates.
*/

T::ParamValue Message::getGridValueByLatLonCoordinate(double lat,double lon,short interpolationMethod) const
{
  FUNCTION_TRACE
  try
  {
    double grid_i = 0;
    double grid_j = 0;
    if (getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j))
    {
      return getGridValueByGridPoint(grid_i,grid_j,interpolationMethod);
    }

    return ParamValueMissing;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns grid point values in the given area (without any interpolation).

        \param grid_i_start  The start grid i-position.
        \param grid_j_start  The start grid j-position.
        \param grid_i_end    The end grid i-position.
        \param grid_j_end    The end grid j-position.
        \return              The parameter values in the given grid area.
*/

void Message::getGridValueVectorByRectangle(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,T::GridPointValue_vec& gridPointValues) const
{
  FUNCTION_TRACE
  try
  {
    T::TimeString tm = getForecastTime();

    for (uint j=grid_j_start; j<= grid_j_end; j++)
    {
      for (uint i=grid_i_start; i<= grid_i_end; i++)
      {
        auto val = getGridValueByGridPoint(i,j);
        gridPointValues.push_back(T::GridPointValue(getFileId(),getMessageIndex(),i,j,getGridParameterLevel(),tm,val));
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns grid point values in the given area (without any interpolation).

        \param grid_i_start  The start grid i-position.
        \param grid_j_start  The start grid j-position.
        \param grid_i_end    The end grid i-position.
        \param grid_j_end    The end grid j-position.
        \return              The parameter values in the given grid area.
*/

void Message::getParameterValuesByRectangle(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,T::GridPointValueList& gridPointValues) const
{
  FUNCTION_TRACE
  try
  {
    T::TimeString tm = getForecastTime();

    for (uint j=grid_j_start; j<= grid_j_end; j++)
    {
      for (uint i=grid_i_start; i<= grid_i_end; i++)
      {
        T::ParamValue val = getGridValueByGridPoint(i,j);
        gridPointValues.addGridPointValue(new T::GridPointValue(getFileId(),getMessageIndex(),i,j,getGridParameterLevel(),tm,val));
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the value of the rounded grid position.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The closest value of the given grid position.
*/

T::ParamValue Message::getGridValueByGridPoint_noInterpolation(double grid_i,double grid_j) const
{
  FUNCTION_TRACE
  try
  {
    return getGridValueByGridPoint(floor(grid_i),floor(grid_j));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the closest value of the given grid position.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The closest value of the given grid position.
*/

T::ParamValue Message::getGridValueByGridPoint_nearest(double grid_i,double grid_j) const
{
  FUNCTION_TRACE
  try
  {
    double x = grid_i;
    double y = grid_j;

    uint x1 = C_UINT(floor(x));
    uint y1 = C_UINT(floor(y));
    uint x2 = x1+1;
    uint y2 = y1+1;

    double dist_x1 = x - C_DOUBLE(x1);
    double dist_x2 = C_DOUBLE(x2) - x;
    double dist_y1 = y - C_DOUBLE(y1);
    double dist_y2 = C_DOUBLE(y2) - y;

    if (dist_x1 == 0  &&  dist_y1 == 0)
      return getGridValueByGridPoint(round(grid_i),round(grid_j));

    double dist_q11 = (dist_x1)*(dist_x1) + (dist_y1)*(dist_y1);
    double dist_q21 = (dist_x2)*(dist_x2) + (dist_y1)*(dist_y1);
    double dist_q12 = (dist_x1)*(dist_x1) + (dist_y2)*(dist_y2);
    double dist_q22 = (dist_x2)*(dist_x2) + (dist_y2)*(dist_y2);

    if (dist_q11 < dist_q21  &&  dist_q11 <= dist_q12 && dist_q11 <= dist_q22)
      return getGridValueByGridPoint(x1,y1);

    if (dist_q21 < dist_q11  &&  dist_q21 <= dist_q12 && dist_q21 <= dist_q22)
      return getGridValueByGridPoint(x2,y1);

    if (dist_q12 < dist_q11  &&  dist_q12 <= dist_q21   &&  dist_q12 <= dist_q22)
      return getGridValueByGridPoint(x1,y2);

    return getGridValueByGridPoint(x2,y2);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::ParamValue Message::getGridValueByGridPoint_min(double grid_i,double grid_j) const
{
  FUNCTION_TRACE
  try
  {
    double x = grid_i;
    double y = grid_j;

    uint x1 = C_UINT(floor(x));
    uint y1 = C_UINT(floor(y));
    uint x2 = C_UINT(x1+1);
    uint y2 = C_UINT(y1+1);

    std::set<T::ParamValue> values;
    values.insert(getGridValueByGridPoint(x1,y1));
    values.insert(getGridValueByGridPoint(x2,y1));
    values.insert(getGridValueByGridPoint(x1,y2));
    values.insert(getGridValueByGridPoint(x2,y2));

    return *values.begin();

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::ParamValue Message::getGridValueByGridPoint_max(double grid_i,double grid_j) const
{
  FUNCTION_TRACE
  try
  {
    double x = grid_i;
    double y = grid_j;

    uint x1 = C_UINT(floor(x));
    uint y1 = C_UINT(floor(y));
    uint x2 = C_UINT(x1+1);
    uint y2 = C_UINT(y1+1);

    std::set<T::ParamValue> values;
    values.insert(getGridValueByGridPoint(x1,y1));
    values.insert(getGridValueByGridPoint(x2,y1));
    values.insert(getGridValueByGridPoint(x1,y2));
    values.insert(getGridValueByGridPoint(x2,y2));

    return *values.rbegin();

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns an interpolated value of the given grid position.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The interpolated value of the given grid position.
*/

T::ParamValue Message::getGridValueByGridPoint_linearInterpolation(double grid_i,double grid_j) const
{
  FUNCTION_TRACE
  try
  {
    // https://en.wikipedia.org/wiki/Bilinear_interpolation

    double x = grid_i;
    double y = grid_j;

    uint x1 = C_UINT(floor(x));
    uint y1 = C_UINT(floor(y));
    uint x2 = C_UINT(x1+1);
    uint y2 = C_UINT(y1+1);

    // Reading values of the corner grid points

    auto val_q11 = getGridValueByGridPoint(x1,y1);
    auto val_q21 = getGridValueByGridPoint(x2,y1);
    auto val_q12 = getGridValueByGridPoint(x1,y2);
    auto val_q22 = getGridValueByGridPoint(x2,y2);

    return linearInterpolation(x,y,x1,y1,x2,y2,val_q11,val_q21,val_q22,val_q12);
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

void Message::print(std::ostream& stream,uint level,uint optionFlags) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}




}
}
