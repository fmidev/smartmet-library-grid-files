#include "Message.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include "identification/GribDef.h"


namespace SmartMet
{
namespace GRID
{


/*! \brief The constructor of the class. */

Message::Message()
{
  try
  {
    mMessageIndex = 0;
    mGrib1ParameterLevelId = 0;
    mGrib2ParameterLevelId = 0;
    mFmiParameterLevelId = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The copy constructor of the class. */

Message::Message(const Message& message)
{
  try
  {
    mMessageIndex = message.mMessageIndex;
    mGribParameterId = message.mGribParameterId;
    mGrib1ParameterLevelId = message.mGrib1ParameterLevelId;
    mGrib2ParameterLevelId = message.mGrib2ParameterLevelId;
    mFmiParameterId = message.mFmiParameterId;
    mFmiParameterLevelId = message.mFmiParameterLevelId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
  try
  {
    return mMessageIndex;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void Message::setMessageIndex(uint index)
{
  try
  {
    mMessageIndex = index;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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

T::Dimensions_opt Message::getGridDimensions() const
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





uint Message::getGridGeometryId() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





void Message::setGridGeometryId(uint geometryId)
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





bool Message::getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const
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
  try
  {
    return mGribParameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string Message::getGribParameterName() const
{
  try
  {
    return mGribParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string Message::getGribParameterDescription() const
{
  try
  {
    return mGribParameterDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string Message::getGribParameterUnits() const
{
  try
  {
    return mGribParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




/*! \brief The method returns the grib 1 parameter level id.

         \return   The parameter level type (= enum value).
*/


T::ParamLevelId Message::getGrib1ParameterLevelId() const
{
  try
  {
    return mGrib1ParameterLevelId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the grib 2 parameter level id.

         \return   The parameter level type (= enum value).
*/


T::ParamLevelId Message::getGrib2ParameterLevelId() const
{
  try
  {
    return mGrib2ParameterLevelId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




T::ParamId Message::getFmiParameterId() const
{
  try
  {
    return mFmiParameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::ParamLevelId Message::getFmiParameterLevelId() const
{
  try
  {
    return mFmiParameterLevelId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string Message::getFmiParameterName() const
{
  try
  {
    return mFmiParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string Message::getFmiParameterDescription() const
{
  try
  {
    return mFmiParameterDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string Message::getFmiParameterUnits() const
{
  try
  {
    return mFmiParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string Message::getCdmParameterId() const
{
  try
  {
    return mCdmParameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string Message::getCdmParameterName() const
{
  try
  {
    return mCdmParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string Message::getNewbaseParameterId() const
{
  try
  {
    return mNewbaseParameterId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string Message::getNewbaseParameterName() const
{
  try
  {
    return mNewbaseParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the parameter level.
    Sometime the parameter level is "included" in the parameter definition. I.e. there
    might be different parameterId for "temperature-2m" and "temperature-10m". On the other
    hand, there might be only one parameterId for "temperature" but several levels (2m, 10m, etc.).
    So, the same data can be defined in multiple ways.

         \return   The parameter level.
*/

T::ParamLevel Message::getParameterLevel() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the parameter level id.

         \return   The parameter level type (= enum value).
*/


T::ParamLevelId Message::getParameterLevelId() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the parameter level type string (define in Table 4.5).

        \return   The parameter level type (expressed in a string).
*/

std::string Message::getParameterLevelIdString() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the grid value in the given (exact) point.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.

        \return         The parameter value of the given grid point.
*/

T::ParamValue Message::getParameterValueByGridPoint(uint grid_i,uint grid_j) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the grid value in the given original grid point.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.

        \return         The parameter value of the given grid point.
*/

T::ParamValue Message::getParameterValueByOriginalGridPoint(uint grid_i,uint grid_j) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the minimum and maximum value used in the current grid.
    This functionality might help to visualize the grid data.

        \param minValue   The returned minimum parameter value in the grid.
        \param maxValue   The returned maximum parameter value in the grid.
*/

void Message::getParameterMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}



/*! \brief The method returns all grid data values (also missing values) as the grid
    would be regular. In the case of an irregular grid, the grid rows are filled so that
    the grid looks like a regular grid.

        \param values   The returned grid values.
*/

void Message::getParameterValues(T::ParamValue_vec& values) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





/*! \brief The method returns the original grid data values.
    If the grid is regular then the 'getParameterValues()' method returns the same
    result as this method. However, if the grid is irregular then the grid rows
    might contain different number of columns. In this case the data should be
    processed row-by-row and the 'getGridOriginalColumnCount()' method should be
    used in order to find out the number of the columns used in each row. Also
    the 'getGridOriginalValueIndex()' method can be used in order to locate values
    in the returned vector.

        \param values   The returned grid values (original).
*/

void Message::getParameterOriginalValues(T::ParamValue_vec& values) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





T::SpatialReference* Message::getSpatialReference() const
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




short Message::getForecastType() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}





short Message::getForecastNumber() const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
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

T::ParamValue Message::getParameterValueByGridPosition(double grid_i,double grid_j,T::InterpolationMethod interpolationMethod) const
{
  try
  {
    switch (interpolationMethod)
    {
      case T::InterpolationMethod::Nearest:
        return getParameterValueByGridPosition_nearest(grid_i,grid_j);

      case T::InterpolationMethod::Linear:
        return getParameterValueByGridPosition_linearInterpolation(grid_i,grid_j);

      default:
        throw SmartMet::Spine::Exception(BCP,"Unknown 'interpolationMethod' parameter value!");
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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

T::ParamValue Message::getParameterValueByLatLon(double lat,double lon,T::InterpolationMethod interpolationMethod) const
{
  try
  {
    double grid_i = 0;
    double grid_j = 0;
    if (getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j))
    {
      return getParameterValueByGridPosition(grid_i,grid_j,interpolationMethod);
    }

    return ParamValueMissing;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns grid point values in the given area (without any interpolation).

        \param grid_i_start  The start grid i-position.
        \param grid_j_start  The start grid j-position.
        \param grid_i_end    The end grid i-position.
        \param grid_j_end    The end grid j-position.
        \return              The parameter values in the given grid area.
*/

void Message::getParameterValuesByGridArea(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,T::GridPointValue_vec& gridPointValues) const
{
  try
  {
    T::TimeString tm = getForecastTime();

    for (uint j=grid_j_start; j<= grid_j_end; j++)
    {
      for (uint i=grid_i_start; i<= grid_i_end; i++)
      {
        auto val = getParameterValueByGridPoint(i,j);
        gridPointValues.push_back(T::GridPointValue(getFileId(),getMessageIndex(),i,j,getParameterLevel(),tm,val));
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns grid point values in the given area (without any interpolation).

        \param grid_i_start  The start grid i-position.
        \param grid_j_start  The start grid j-position.
        \param grid_i_end    The end grid i-position.
        \param grid_j_end    The end grid j-position.
        \return              The parameter values in the given grid area.
*/

void Message::getParameterValuesByGridArea(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,T::GridPointValueList& gridPointValues) const
{
  try
  {
    T::TimeString tm = getForecastTime();

    for (uint j=grid_j_start; j<= grid_j_end; j++)
    {
      for (uint i=grid_i_start; i<= grid_i_end; i++)
      {
        T::ParamValue val = getParameterValueByGridPoint(i,j);
        gridPointValues.addGridPointValue(new T::GridPointValue(getFileId(),getMessageIndex(),i,j,getParameterLevel(),tm,val));
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the closest value of the given grid position.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The closest value of the given grid position.
*/

T::ParamValue Message::getParameterValueByGridPosition_nearest(double grid_i,double grid_j) const
{
  try
  {
    double x = grid_i;
    double y = grid_j;

    double x1 = floor(x);
    double y1 = floor(y);
    double x2 = x1+1;
    double y2 = y1+1;

    double dist_x1 = x-x1;
    double dist_x2 = x2-x;
    double dist_y1 = y-y1;
    double dist_y2 = y2-y;

    if (dist_x1 == 0  &&  dist_y1 == 0)
      return getParameterValueByGridPoint((uint)grid_i,(uint)grid_j);

    double dist_q11 = (dist_x1)*(dist_x1) + (dist_y1)*(dist_y1);
    double dist_q21 = (dist_x2)*(dist_x2) + (dist_y1)*(dist_y1);
    double dist_q12 = (dist_x1)*(dist_x1) + (dist_y2)*(dist_y2);
    double dist_q22 = (dist_x2)*(dist_x2) + (dist_y2)*(dist_y2);

    if (dist_q11 < dist_q21  &&  dist_q11 <= dist_q12 && dist_q11 <= dist_q22)
      return getParameterValueByGridPoint((uint)x1,(uint)y1);

    if (dist_q21 < dist_q11  &&  dist_q21 <= dist_q12 && dist_q21 <= dist_q22)
      return getParameterValueByGridPoint((uint)x2,(uint)y1);

    if (dist_q12 < dist_q11  &&  dist_q12 <= dist_q21   &&  dist_q12 <= dist_q22)
      return getParameterValueByGridPoint((uint)x1,(uint)y2);

    return getParameterValueByGridPoint((uint)x2,(uint)y2);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns an interpolated value of the given grid position.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The interpolated value of the given grid position.
*/

T::ParamValue Message::getParameterValueByGridPosition_linearInterpolation(double grid_i,double grid_j) const
{
  try
  {
    // https://en.wikipedia.org/wiki/Bilinear_interpolation

    double x = grid_i;
    double y = grid_j;

    double x1 = floor(x);
    double y1 = floor(y);
    double x2 = x1+1;
    double y2 = y1+1;

    double dist_x1 = x-x1;
    double dist_x2 = x2-x;
    double dist_y1 = y-y1;
    double dist_y2 = y2-y;

    // If the given point is close enough the actual grid point
    // then there is no need for interpolation.

    double closeDist = 0.1;

    if (dist_x1 <= closeDist  &&  dist_y1 <= closeDist)
      return getParameterValueByGridPoint((uint)x1,(uint)y1);

    if (dist_x1 <= closeDist  &&  dist_y2 <= closeDist)
      return getParameterValueByGridPoint((uint)x1,(uint)y2);

    if (dist_x2 <= closeDist  &&  dist_y1 <= closeDist)
      return getParameterValueByGridPoint((uint)x2,(uint)y1);

    if (dist_x2 <= closeDist  &&  dist_y2 <= closeDist)
      return getParameterValueByGridPoint((uint)x2,(uint)y2);


    // Reading values of the corner grid points

    auto val_q11 = getParameterValueByGridPoint((uint)x1,(uint)y1);
    auto val_q21 = getParameterValueByGridPoint((uint)x2,(uint)y1);
    auto val_q12 = getParameterValueByGridPoint((uint)x1,(uint)y2);
    auto val_q22 = getParameterValueByGridPoint((uint)x2,(uint)y2);

    // If the given point is on the border then we can do simple
    // linear interpolation.

    if (dist_x1 == 0)
    {
      // Linear interpolation x1,y1 - x1,y2
      if (val_q11 != ParamValueMissing  &&  val_q12 != ParamValueMissing)
        return (T::ParamValue)(dist_y1*val_q11 + dist_y2*val_q12);

      return ParamValueMissing;
    }

    if (dist_x2 == 0)
    {
      // Linear interpolation x2,y1 - x2,y2
      if (val_q21 != ParamValueMissing  &&  val_q22 != ParamValueMissing)
        return (T::ParamValue)(dist_y1*val_q21 + dist_y2*val_q22);

      return ParamValueMissing;
    }

    if (dist_y1 == 0)
    {
      // Linear interpolation x1,y1 - x2,y1
      if (val_q11 != ParamValueMissing  &&  val_q21 != ParamValueMissing)
        return (T::ParamValue)(dist_x1*val_q11 + dist_x2*val_q21);

      return ParamValueMissing;
    }

    if (dist_y2 == 0)
    {
      // Linear interpolation x1,y2 - x2,y2
      if (val_q12 != ParamValueMissing  &&  val_q22 != ParamValueMissing)
        return (T::ParamValue)(dist_x1*val_q12 + dist_x2*val_q22);

      return ParamValueMissing;
    }

    // Bilinear interpolation

    if (val_q11 != ParamValueMissing && val_q21 != ParamValueMissing  &&
        val_q12 != ParamValueMissing &&  val_q22 != ParamValueMissing)
    {
      // All corners have a value.

      double fy1 = dist_x2*val_q11 + dist_x1*val_q21;
      double fy2 = dist_x2*val_q12 + dist_x1*val_q22;
      double f = dist_y2*fy1 + dist_y1*fy2;
      return (T::ParamValue)f;
    }

    // Three corners have a value (triangular interpolation).

    if (val_q11 == ParamValueMissing && val_q21 != ParamValueMissing  &&
        val_q12 != ParamValueMissing &&  val_q22 != ParamValueMissing)
    {
      double wsum = (dist_x2 * dist_y1 + dist_x1 * dist_y1 + dist_x1 * dist_y2);
      return (T::ParamValue)((dist_x1 * dist_y2 * val_q21 + dist_x2 * dist_y1 * val_q12 +
          dist_x1 * dist_y1 * val_q22) / wsum);
    }

    if (val_q11 != ParamValueMissing && val_q21 == ParamValueMissing  &&
        val_q12 != ParamValueMissing &&  val_q22 != ParamValueMissing)
    {
      double wsum = (dist_x2 * dist_y2 + dist_x2 * dist_y1 + dist_x1 * dist_y1);
      return (T::ParamValue)((dist_x2 * dist_y2 * val_q11 + dist_x2 * dist_y1 * val_q12 +
          dist_x1 * dist_y1 * val_q22) / wsum);
    }

    if (val_q11 != ParamValueMissing && val_q21 != ParamValueMissing  &&
        val_q12 == ParamValueMissing &&  val_q22 != ParamValueMissing)
    {
      double wsum = (dist_x1 * dist_y1 + dist_x2 * dist_y2 + dist_x1 * dist_y2);
      return (T::ParamValue)((dist_x2 * dist_y2 * val_q11 + dist_x1 * dist_y2 * val_q21 +
        dist_x1 * dist_y1 * val_q22) / wsum);
    }

    if (val_q11 != ParamValueMissing && val_q21 != ParamValueMissing  &&
        val_q12 != ParamValueMissing &&  val_q22 == ParamValueMissing)
    {
      double wsum = (dist_x2 * dist_y1 + dist_x2 * dist_y2 + dist_x1 * dist_y2);
      return (T::ParamValue)((dist_x2 * dist_y2 * val_q11 + dist_x1 * dist_y2 * val_q21 +
        dist_x2 * dist_y2 * val_q12) / wsum);
    }

    return ParamValueMissing;
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

void Message::print(std::ostream& stream,uint level,uint optionFlags) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in the child class!");
}




}
}
