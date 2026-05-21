#pragma once

#include "Message.h"
#include "Typedefs.h"
#include "GridPointValue.h"
#include "GridPointValueList.h"
#include "GridValueList.h"
#include "../common/AttributeList.h"
#include "../common/Coordinate.h"
#include "../common/Dimensions.h"
#include "../common/GraphFunctions.h"
#include "../common/ThreadLock.h"

#include <vector>
#include <string>
#include <memory>


namespace SmartMet
{
namespace GRID
{


// ====================================================================================
/*! \brief Algorithms that combine two or four Message objects to produce
 *         level-interpolated or time-interpolated contours and value vectors.
 *
 *  Each family of methods exists in three "domain" variants:
 *  - **ByLevel** – vertical interpolation between two adjacent level messages.
 *  - **ByTime**  – temporal interpolation between two adjacent time-step messages.
 *  - **ByTimeAndLevel** – bilinear interpolation in both time and level using four messages.
 *
 *  Within each family, output variants are:
 *  - (no suffix)       – contours/values on the native grid of message1.
 *  - **AndGeometry**   – reprojected to the geometry specified in attributeList.
 *  - **AndGrid**       – reprojected to an explicit (gridWidth × gridHeight) target grid.
 *
 *  Every method also has a `+modificationOperation` overload (marked `\\overload`)
 *  that transforms decoded values before contouring/extraction. */
// ====================================================================================

class MessageProcessing
{
  public:

                 MessageProcessing();
    virtual      ~MessageProcessing();

    // -----------------------------------------------------------------------
    // Isoband extraction
    // -----------------------------------------------------------------------

    /*! \brief Compute isobands after vertically interpolating two level messages.
     *  \param[in]  message1,message2     Messages at the two bracketing levels.
     *  \param[in]  newLevel              Target level to interpolate to.
     *  \param[in]  contourLowValues      Lower bound of each isoband interval.
     *  \param[in]  contourHighValues     Upper bound of each isoband interval.
     *  \param[in]  attributeList         Rendering/output attributes.
     *  \param[out] contours              Encoded polygon data for each isoband. */
    virtual void getGridIsobandsByLevel(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    //! \overload
    virtual void getGridIsobandsByLevel(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const;

    /*! \brief Level-interpolated isobands reprojected to the geometry in \p attributeList. */
    virtual void getGridIsobandsByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    //! \overload
    virtual void getGridIsobandsByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const;

    /*! \brief Level-interpolated isobands reprojected onto an explicit target grid. */
    virtual void getGridIsobandsByLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours);
    //! \overload
    virtual void getGridIsobandsByLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours);

    /*! \brief Time-interpolated isobands on the native grid. */
    virtual void getGridIsobandsByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    //! \overload
    virtual void getGridIsobandsByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const;

    /*! \brief Time-interpolated isobands on an explicit target grid. */
    virtual void getGridIsobandsByTimeAndGrid(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours);
    //! \overload
    virtual void getGridIsobandsByTimeAndGrid(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours);

    /*! \brief Time-interpolated isobands reprojected to the geometry in \p attributeList. */
    virtual void getGridIsobandsByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    //! \overload
    virtual void getGridIsobandsByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const;

    /*! \brief Bilinear time+level-interpolated isobands on the native grid.
     *  \param[in]  message1           Message at (t1, level1).
     *  \param[in]  message2           Message at (t2, level1).
     *  \param[in]  message3           Message at (t1, level2).
     *  \param[in]  message4           Message at (t2, level2).
     *  \param[in]  newTime            Target interpolation time.
     *  \param[in]  newLevel           Target interpolation level.
     *  \param[in]  contourLowValues   Lower bounds of isoband intervals.
     *  \param[in]  contourHighValues  Upper bounds of isoband intervals.
     *  \param[in]  attributeList      Rendering attributes.
     *  \param[out] contours           Encoded polygon data. */
    virtual void getGridIsobandsByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    //! \overload
    virtual void getGridIsobandsByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const;

    /*! \brief Bilinear time+level isobands reprojected to the geometry in \p attributeList. */
    virtual void getGridIsobandsByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    //! \overload
    virtual void getGridIsobandsByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const;

    /*! \brief Bilinear time+level isobands on an explicit target grid. */
    virtual void getGridIsobandsByTimeLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    //! \overload
    virtual void getGridIsobandsByTimeLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const;

    // -----------------------------------------------------------------------
    // Isoline extraction
    // -----------------------------------------------------------------------

    /*! \brief Level-interpolated isolines on the native grid.
     *  \param[in]  message1       Message at the lower bracketing level.
     *  \param[in]  message2       Message at the upper bracketing level.
     *  \param[in]  newLevel       Target interpolation level.
     *  \param[in]  contourValues  Isoline threshold levels.
     *  \param[in]  attributeList  Rendering attributes.
     *  \param[out] contours       Encoded polyline data. */
    virtual void getGridIsolinesByLevel(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    //! \overload
    virtual void getGridIsolinesByLevel(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const;

    /*! \brief Level-interpolated isolines reprojected to the geometry in \p attributeList. */
    virtual void getGridIsolinesByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    //! \overload
    virtual void getGridIsolinesByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const;

    /*! \brief Level-interpolated isolines on an explicit target grid. */
    virtual void getGridIsolinesByLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours);
    //! \overload
    virtual void getGridIsolinesByLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours);

    /*! \brief Time-interpolated isolines on the native grid. */
    virtual void getGridIsolinesByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    //! \overload
    virtual void getGridIsolinesByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const;

    /*! \brief Time-interpolated isolines reprojected to the geometry in \p attributeList. */
    virtual void getGridIsolinesByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    //! \overload
    virtual void getGridIsolinesByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const;

    /*! \brief Time-interpolated isolines on an explicit target grid. */
    virtual void getGridIsolinesByTimeAndGrid(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours);
    //! \overload
    virtual void getGridIsolinesByTimeAndGrid(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours);

    /*! \brief Bilinear time+level isolines on the native grid. */
    virtual void getGridIsolinesByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    //! \overload
    virtual void getGridIsolinesByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const;

    /*! \brief Bilinear time+level isolines reprojected to the geometry in \p attributeList. */
    virtual void getGridIsolinesByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    //! \overload
    virtual void getGridIsolinesByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const;

    /*! \brief Bilinear time+level isolines on an explicit target grid. */
    virtual void getGridIsolinesByTimeLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours) const;
    //! \overload
    virtual void getGridIsolinesByTimeLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours) const;

    // -----------------------------------------------------------------------
    // Streamline extraction
    // -----------------------------------------------------------------------

    /*! \brief Level-interpolated streamlines on the native grid. */
    virtual void getGridStreamlinesByLevel(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::AttributeList& attributeList,T::ByteData_vec& streamlines) const;
    //! \overload
    virtual void getGridStreamlinesByLevel(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines) const;

    /*! \brief Level-interpolated streamlines reprojected to the geometry in \p attributeList. */
    virtual void getGridStreamlinesByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::AttributeList& attributeList,T::ByteData_vec& streamlines) const;
    //! \overload
    virtual void getGridStreamlinesByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines) const;

    /*! \brief Level-interpolated streamlines on an explicit target grid. */
    virtual void getGridStreamlinesByLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,double newLevel,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& streamlines);
    //! \overload
    virtual void getGridStreamlinesByLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,double newLevel,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines);

    /*! \brief Time-interpolated streamlines on the native grid. */
    virtual void getGridStreamlinesByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::AttributeList& attributeList,T::ByteData_vec& streamlines) const;
    //! \overload
    virtual void getGridStreamlinesByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines) const;

    /*! \brief Time-interpolated streamlines reprojected to the geometry in \p attributeList. */
    virtual void getGridStreamlinesByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::AttributeList& attributeList,T::ByteData_vec& streamlines) const;
    //! \overload
    virtual void getGridStreamlinesByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines) const;

    /*! \brief Time-interpolated streamlines on an explicit target grid. */
    virtual void getGridStreamlinesByTimeAndGrid(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& streamlines);
    //! \overload
    virtual void getGridStreamlinesByTimeAndGrid(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines);

    /*! \brief Bilinear time+level streamlines on the native grid. */
    virtual void getGridStreamlinesByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::AttributeList& attributeList,T::ByteData_vec& streamlines) const;
    //! \overload
    virtual void getGridStreamlinesByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines) const;

    /*! \brief Bilinear time+level streamlines reprojected to the geometry in \p attributeList. */
    virtual void getGridStreamlinesByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::AttributeList& attributeList,T::ByteData_vec& streamlines) const;
    //! \overload
    virtual void getGridStreamlinesByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines) const;

    /*! \brief Bilinear time+level streamlines on an explicit target grid. */
    virtual void getGridStreamlinesByTimeLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,T::ByteData_vec& streamlines) const;
    //! \overload
    virtual void getGridStreamlinesByTimeLevelAndGrid(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines) const;

    // -----------------------------------------------------------------------
    // Single-point value queries
    // -----------------------------------------------------------------------

    /*! \brief Interpolate a single value with level interpolation.
     *  \param[in]  message1,message2          Messages at two adjacent levels.
     *  \param[in]  level1,level2              Level values of message1 and message2.
     *  \param[in]  newLevel                   Target interpolation level.
     *  \param[in]  coordinateType             Coordinate system of (x, y).
     *  \param[in]  x,y                        Query coordinates.
     *  \param[in]  areaInterpolationMethod    Horizontal interpolation method.
     *  \param[in]  levelInterpolationMethod   Vertical interpolation method.
     *  \param[out] value                      Interpolated parameter value. */
    virtual void getGridValueByLevelAndPoint(const GRID::Message& message1,const GRID::Message& message2,int level1,int level2,double newLevel,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short levelInterpolationMethod,T::ParamValue& value) const;
    //! \overload
    virtual void getGridValueByLevelAndPoint(const GRID::Message& message1,const GRID::Message& message2,int level1,int level2,double newLevel,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue& value) const;

    /*! \brief Interpolate a single value with time interpolation.
     *  \param[in]  message1,message2          Messages at two adjacent time steps.
     *  \param[in]  newTime                    Target interpolation time.
     *  \param[in]  coordinateType             Coordinate system of (x, y).
     *  \param[in]  x,y                        Query coordinates.
     *  \param[in]  areaInterpolationMethod    Horizontal interpolation method.
     *  \param[in]  timeInterpolationMethod    Temporal interpolation method.
     *  \param[out] value                      Interpolated parameter value. */
    virtual void getGridValueByTimeAndPoint(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short timeInterpolationMethod,T::ParamValue& value) const;
    //! \overload
    virtual void getGridValueByTimeAndPoint(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short timeInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue& value) const;

    /*! \brief Interpolate a single value with bilinear time+level interpolation.
     *  \param[in]  message1                Message at (t1, level1).
     *  \param[in]  level1                  Level value of message1.
     *  \param[in]  message2                Message at (t2, level1).
     *  \param[in]  level2                  Level value of message2.
     *  \param[in]  message3                Message at (t1, level2).
     *  \param[in]  level3                  Level value of message3.
     *  \param[in]  message4                Message at (t2, level2).
     *  \param[in]  level4                  Level value of message4.
     *  \param[in]  newTime                 Target interpolation time.
     *  \param[in]  newLevel                Target interpolation level.
     *  \param[in]  coordinateType          Coordinate system of (x, y).
     *  \param[in]  x                       Query x coordinate.
     *  \param[in]  y                       Query y coordinate.
     *  \param[in]  areaInterpolationMethod   Horizontal interpolation method.
     *  \param[in]  timeInterpolationMethod   Temporal interpolation method.
     *  \param[in]  levelInterpolationMethod  Vertical interpolation method.
     *  \param[out] value                   Interpolated parameter value. */
    virtual void getGridValueByTimeLevelAndPoint(const GRID::Message& message1,int level1,const GRID::Message& message2,int level2,const GRID::Message& message3,int level3,const GRID::Message& message4,int level4,time_t newTime,double newLevel,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,T::ParamValue& value) const;
    //! \overload
    virtual void getGridValueByTimeLevelAndPoint(const GRID::Message& message1,int level1,const GRID::Message& message2,int level2,const GRID::Message& message3,int level3,const GRID::Message& message4,int level4,time_t newTime,double newLevel,T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue& value) const;

    // -----------------------------------------------------------------------
    // Value list queries
    // -----------------------------------------------------------------------

    /*! \brief Level-interpolated values within a circle.
     *  \param[in]  message1                 Message at the lower bracketing level.
     *  \param[in]  message2                 Message at the upper bracketing level.
     *  \param[in]  newLevel                 Target interpolation level.
     *  \param[in]  coordinateType           Coordinate system of (origoX, origoY).
     *  \param[in]  origoX                   Circle centre x coordinate.
     *  \param[in]  origoY                   Circle centre y coordinate.
     *  \param[in]  radius                   Circle radius.
     *  \param[in]  levelInterpolationMethod Vertical interpolation method.
     *  \param[out] valueList                Receives matching values with positions. */
    virtual void getGridValueListByLevelAndCircle(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short levelInterpolationMethod,T::GridValueList& valueList) const;
    //! \overload
    virtual void getGridValueListByLevelAndCircle(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    /*! \brief Level-interpolated values at a list of points. */
    virtual void getGridValueListByLevelAndPointList(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const;
    //! \overload
    virtual void getGridValueListByLevelAndPointList(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    /*! \brief Level-interpolated values within a polygon. */
    virtual void getGridValueListByLevelAndPolygon(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short levelInterpolationMethod,T::GridValueList& valueList) const;
    //! \overload
    virtual void getGridValueListByLevelAndPolygon(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    /*! \brief Level-interpolated values within a multi-polygon. */
    virtual void getGridValueListByLevelAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short levelInterpolationMethod,T::GridValueList& valueList) const;
    //! \overload
    virtual void getGridValueListByLevelAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    /*! \brief Time-interpolated values within a circle. */
    virtual void getGridValueListByTimeAndCircle(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short timeInterpolationMethod,T::GridValueList& valueList) const;
    //! \overload
    virtual void getGridValueListByTimeAndCircle(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short timeInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    /*! \brief Time-interpolated values at a list of points. */
    virtual void getGridValueListByTimeAndPointList(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short timeInterpolationMethod,T::GridValueList& valueList) const;
    //! \overload
    virtual void getGridValueListByTimeAndPointList(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short timeInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    /*! \brief Time-interpolated values within a polygon. */
    virtual void getGridValueListByTimeAndPolygon(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short timeInterpolationMethod,T::GridValueList& valueList) const;
    //! \overload
    virtual void getGridValueListByTimeAndPolygon(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short timeInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    /*! \brief Time-interpolated values within a multi-polygon. */
    virtual void getGridValueListByTimeAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short timeInterpolationMethod,T::GridValueList& valueList) const;
    //! \overload
    virtual void getGridValueListByTimeAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short timeInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    /*! \brief Bilinear time+level values within a circle. */
    virtual void getGridValueListByTimeLevelAndCircle(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const;
    //! \overload
    virtual void getGridValueListByTimeLevelAndCircle(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,double origoX,double origoY,double radius,short timeInterpolationMethod,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    /*! \brief Bilinear time+level values at a list of points. */
    virtual void getGridValueListByTimeLevelAndPointList(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const;
    //! \overload
    virtual void getGridValueListByTimeLevelAndPointList(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    /*! \brief Bilinear time+level values within a polygon. */
    virtual void getGridValueListByTimeLevelAndPolygon(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const;
    //! \overload
    virtual void getGridValueListByTimeLevelAndPolygon(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,short timeInterpolationMethod,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    /*! \brief Bilinear time+level values within a multi-polygon. */
    virtual void getGridValueListByTimeLevelAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short timeInterpolationMethod,short levelInterpolationMethod,T::GridValueList& valueList) const;
    //! \overload
    virtual void getGridValueListByTimeLevelAndPolygonPath(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,short timeInterpolationMethod,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    // -----------------------------------------------------------------------
    // Full grid value vector queries
    // -----------------------------------------------------------------------

    /*! \brief Level-interpolated full grid value vector.
     *  \param[in]  message1                 Message at the lower bracketing level.
     *  \param[in]  message2                 Message at the upper bracketing level.
     *  \param[in]  newLevel                 Target interpolation level.
     *  \param[in]  levelInterpolationMethod Vertical interpolation method.
     *  \param[out] values                   Receives the interpolated value vector. */
    virtual void getGridValueVectorByLevel(const GRID::Message& message1,const GRID::Message& message2,double newLevel,short levelInterpolationMethod,T::ParamValue_vec& values) const;
    //! \overload
    virtual void getGridValueVectorByLevel(const GRID::Message& message1,const GRID::Message& message2,double newLevel,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;

    /*! \brief Level-interpolated values at a coordinate list. */
    virtual void getGridValueVectorByLevelAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,T::ParamValue_vec& values) const;
    //! \overload
    virtual void getGridValueVectorByLevelAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;

    /*! \brief Level-interpolated values resampled to the geometry in \p attributeList. */
    virtual void getGridValueVectorByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::AttributeList& attributeList,T::ParamValue_vec& values) const;
    //! \overload
    virtual void getGridValueVectorByLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,double newLevel,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;

    /*! \brief Time-interpolated full grid value vector.
     *  \param[in]  message1                Message at the earlier time step.
     *  \param[in]  message2                Message at the later time step.
     *  \param[in]  newTime                 Target interpolation time.
     *  \param[in]  timeInterpolationMethod Temporal interpolation method.
     *  \param[out] values                  Receives the interpolated value vector. */
    virtual void getGridValueVectorByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,short timeInterpolationMethod,T::ParamValue_vec& values) const;
    //! \overload
    virtual void getGridValueVectorByTime(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,short timeInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;

    /*! \brief Time-interpolated values at a coordinate list. */
    virtual void getGridValueVectorByTimeAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,T::ParamValue_vec& values) const;
    //! \overload
    virtual void getGridValueVectorByTimeAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;

    /*! \brief Time-interpolated values resampled to the geometry in \p attributeList. */
    virtual void getGridValueVectorByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::AttributeList& attributeList,T::ParamValue_vec& values) const;
    //! \overload
    virtual void getGridValueVectorByTimeAndGeometry(const GRID::Message& message1,const GRID::Message& message2,time_t newTime,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;

    /*! \brief Bilinear time+level full grid value vector. */
    virtual void getGridValueVectorByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,T::ParamValue_vec& values) const;
    //! \overload
    virtual void getGridValueVectorByTimeAndLevel(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,short areaInterpolationMethod,short timeInterpolationMethod,short levelInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;

    /*! \brief Bilinear time+level values resampled to the geometry in \p attributeList. */
    virtual void getGridValueVectorByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::AttributeList& attributeList,T::ParamValue_vec& values) const;
    //! \overload
    virtual void getGridValueVectorByTimeLevelAndGeometry(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;

    /*! \brief Bilinear time+level values at a coordinate list. */
    virtual void getGridValueVectorByTimeLevelAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,T::ParamValue_vec& values) const;
    //! \overload
    virtual void getGridValueVectorByTimeLevelAndCoordinateList(const GRID::Message& message1,const GRID::Message& message2,const GRID::Message& message3,const GRID::Message& message4,time_t newTime,double newLevel,T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;
};



}  // namespace GRID
}  // namespace SmartMet

