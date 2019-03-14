#pragma once

#include "MessageSection.h"
#include "Typedefs.h"
#include "GridPointValue.h"
#include "GridPointValueList.h"
#include "GridValueList.h"
#include "../common/AttributeList.h"
#include "../common/Coordinate.h"
#include "../common/Dimensions.h"
#include "../common/GraphFunctions.h"
#include "../common/ThreadLock.h"
#include "../common/RequestCounter.h"

#include <vector>
#include <string>
#include <memory>



namespace SmartMet
{
namespace GRID
{


typedef std::map<uint,T::ParamValue> PointCache;


// ====================================================================================
/*!
  \brief This class is a parent class for all messages in different grid files. It
  defines the basic methods that all its child classes should implement.

  The basic idea is that we should be able to access all grid related data and
  information through this class (i.e. applications should not need to know any
  implementation details that are behind this interface).
*/
// ====================================================================================

class Message
{
  public:

                              Message();
                              Message(const Message& message);
    virtual                   ~Message();

    virtual void              getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    virtual uint              getFileId() const;
    virtual uint              getProducerId() const;
    virtual uint              getGenerationId() const;
    virtual uint              getMessageIndex() const;
    virtual T::FilePosition   getFilePosition() const;
    virtual T::TimeString     getForecastTime() const;
    virtual short             getForecastType() const;
    virtual short             getForecastNumber() const;

    virtual std::string       getFmiProducerName() const;
    virtual T::ParamId        getFmiParameterId() const;
    virtual T::ParamLevelId   getFmiParameterLevelId() const;
    virtual std::string       getFmiParameterName() const;
    virtual std::string       getFmiParameterDescription() const;
    virtual std::string       getFmiParameterUnits() const;
    virtual std::string       getCdmParameterId() const;
    virtual std::string       getCdmParameterName() const;
    virtual std::string       getNewbaseParameterId() const;
    virtual std::string       getNewbaseParameterName() const;

    virtual uint              getGribCentre() const;
    virtual uint              getGribSubCentre() const;
    virtual T::ParamId        getGribParameterId() const;
    virtual std::string       getGribParameterName() const;
    virtual std::string       getGribParameterDescription() const;
    virtual std::string       getGribParameterUnits() const;
    virtual T::ParamLevelId   getGrib1ParameterLevelId() const;
    virtual T::ParamLevelId   getGrib2ParameterLevelId() const;

    virtual T::Coordinate_vec getGridCoordinates() const;
    virtual void              getGridIsobands(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::WkbData_vec& contours);
    virtual void              getGridIsobandsByGeometry(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::WkbData_vec& contours);
    virtual void              getGridIsobandsByGrid(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,std::vector<T::Coordinate>& projectionCoordinates,T::AttributeList& attributeList,T::WkbData_vec& contours);
    virtual void              getGridIsolines(T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::WkbData_vec& contours);
    virtual void              getGridIsolinesByGeometry(T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::WkbData_vec& contours);
    virtual void              getGridIsolinesByGrid(T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,std::vector<T::Coordinate>& projectionCoordinates,T::AttributeList& attributeList,T::WkbData_vec& contours);
    virtual T::Coordinate_vec getGridLatLonCoordinates() const;
    virtual T::Dimensions     getGridDimensions() const;
    virtual T::GeometryId     getGridGeometryId() const;
    virtual std::string       getGridGeometryString() const;
    virtual T::Hash           getGridHash() const;
    virtual bool              getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    virtual bool              getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;
    virtual bool              getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    virtual bool              getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    virtual bool              getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    virtual bool              getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    virtual T::GridLayout     getGridLayout() const;
    virtual std::size_t       getGridOriginalColumnCount(std::size_t row) const;
    virtual std::size_t       getGridOriginalColumnCount() const;
    virtual std::size_t       getGridOriginalRowCount() const;
    virtual std::size_t       getGridOriginalValueCount() const;
    virtual int               getGridOriginalValueIndex(uint grid_i,uint grid_j) const;
    virtual float             getGridPointAngleByLatLonCoordinates(double lat,double lon) const;
    virtual float             getGridPointAngle(T::CoordinateType coordinateType,double x,double y) const;
    virtual void              getGridPointAngles(std::vector<float>& angles) const;
    virtual bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    virtual bool              getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    virtual T::GridProjection getGridProjection() const;
    virtual void              getGridProjectionAttributes(std::string prefix,T::AttributeList& attributeList) const;
    virtual std::string       getGridProjectionString() const;

    virtual void              getGridValueByPoint(T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,T::ParamValue& value) const;
    virtual void              getGridValueListByCircle(T::CoordinateType coordinateType,double origoX,double origoY,double radius,T::GridValueList& valueList) const;
    virtual void              getGridValueListByPointList(T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,T::GridValueList& valueList) const;
    virtual void              getGridValueListByPolygon(T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,T::GridValueList& valueList) const;
    virtual void              getGridValueListByPolygonPath(T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,T::GridValueList& valueList) const;
    virtual void              getGridValueListByRectangle(T::CoordinateType coordinateType,double x1,double y1,double x2,double y2,bool gridRectangle,T::GridValueList& valueList) const;

    virtual void              getGridValueVector(T::ParamValue_vec& values) const;
    virtual void              getGridValueVectorWithCaching(T::ParamValue_vec& values) const;
    virtual void              getGridValueVectorByGeometry(T::AttributeList& attributeList,T::ParamValue_vec& values) const;
    virtual void              getGridValueVectorByCoordinateList(T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,T::ParamValue_vec& values) const;
    virtual void              getGridValueVectorByLatLonCoordinateList(std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,T::ParamValue_vec& values) const;
    virtual void              getGridValueVectorByGridPointList(std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,T::ParamValue_vec& values) const;

    virtual void              getGridOriginalValueVector(T::ParamValue_vec& values) const;
    virtual T::ParamLevel     getGridParameterLevel() const;
    virtual T::ParamLevelId   getGridParameterLevelId() const;
    virtual std::string       getGridParameterLevelIdString() const;
    virtual void              getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const;

    virtual void              getGridValueVectorByPoint(T::CoordinateType coordinateType,double x,double y,uint vectorType,double_vec& valueVector) const;
    virtual void              getGridValueVectorByGridPoint(double grid_i,double grid_j,uint vectorType,double_vec& valueVector) const;
    virtual void              getGridValueVectorByLatLonCoordinate(double lat,double lon,uint vectorType,double_vec& valueVector) const;

    virtual T::ParamValue     getGridValueByGridPoint(uint grid_i,uint grid_j) const;
    virtual T::ParamValue     getGridValueByGridPoint_byInterpolation(double grid_i,double grid_j,short areaInterpolationMethod) const;
    virtual T::ParamValue     getGridValueByGridPoint_noInterpolation(double grid_i,double grid_j) const;
    virtual T::ParamValue     getGridValueByGridPoint_nearest(double grid_i,double grid_j) const;
    virtual T::ParamValue     getGridValueByGridPoint_min(double grid_i,double grid_j) const;
    virtual T::ParamValue     getGridValueByGridPoint_max(double grid_i,double grid_j) const;
    virtual T::ParamValue     getGridValueByGridPoint_linearInterpolation(double grid_i,double grid_j) const;
    virtual T::ParamValue     getGridValueByLatLonCoordinate(double lat,double lon,short areaInterpolationMethod) const;
    virtual T::ParamValue     getGridValueByOriginalGridPoint(uint grid_i,uint grid_j) const;
    virtual void              getGridValueVectorByRectangle(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,T::GridPointValue_vec& gridPointValues) const;
    virtual void              getParameterValuesByRectangle(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,T::GridPointValueList& gridPointValues) const;
    virtual short             getDefaultInterpolationMethod() const;
    virtual T::TimeString     getReferenceTime() const;
    virtual T::SpatialRef*    getSpatialReference() const;
    virtual std::string       getWKT() const;
    virtual bool              isGridGlobal() const;
    virtual void              refreshIndexes(std::vector<uint>& indexes);
    virtual bool              reverseXDirection() const;
    virtual bool              reverseYDirection() const;

    virtual void              setMessageIndex(uint index);

    virtual void              setFmiParameterId(T::ParamId fmiParameterId);
    virtual void              setFmiParameterLevelId(T::ParamLevelId fmiParameterLevelId);
    virtual void              setFmiParameterName(std::string fmiParameterName);
    virtual void              setFmiParameterDescription(std::string fmiParameterDescr);
    virtual void              setFmiParameterUnits(std::string fmiParameterUnits);
    virtual void              setCdmParameterId(std::string cdmParameterId);
    virtual void              setCdmParameterName(std::string cdmParameterName);
    virtual void              setNewbaseParameterId(std::string newbaseParameterId);
    virtual void              setNewbaseParameterName(std::string newbaseParameterName);

    virtual void              setGridGeometryId(T::GeometryId geometryId);
    virtual void              setGridValues(T::ParamValue_vec& values);

    // Common Grib settings

    virtual void              setGribParameterId(T::ParamId gribParameterId);
    virtual void              setGribParameterName(std::string gribParameterName);
    virtual void              setGribParameterDescription(std::string gribParameterDescr);
    virtual void              setGribParameterUnits(std::string gribParameterUnits);

    // Grib 1 specific settings

    virtual void              setGrib1ParameterLevelId(T::ParamLevelId grib1ParameterLevelId);

    // Grib 2 specific settings

    virtual void              setGrib2ParameterLevelId(T::ParamLevelId grib2ParameterLevelId);


    virtual bool              setProperty(uint propertyId,long long value);

    virtual ulonglong         getRequestCounterKey() const;
    virtual void              setPointCacheEnabled(bool enabled);

    virtual void              addCachedValue(uint index,T::ParamValue value) const;
    virtual bool              getCachedValue(uint index,T::ParamValue& value) const;
    virtual void              clearCachedValues(uint hitsRequired,uint timePeriod) const;

    virtual void              print(std::ostream& stream,uint level,uint optionFlags) const;


protected:

    void                      incRequestCounter(uint index) const;


    /*! \brief  The index of the message in the file. */
    uint                      mMessageIndex;

    /*! \brief The grib parameter identifier. */
    T::ParamId                mGribParameterId;

    /*! \brief  The grib1 parameter level identifier. */
    T::ParamLevelId           mGrib1ParameterLevelId;

    /*! \brief  The grib2 parameter level identifier. */
    T::ParamLevelId           mGrib2ParameterLevelId;

    /*! \brief  The grib parameter name. */
    std::string               mGribParameterName;

    /*! \brief  The grib parameter description. */
    std::string               mGribParameterDescription;

    /*! \brief  The grib parameter units. */
    std::string               mGribParameterUnits;

    /*! \brief  The fmi producer name. */
    std::string               mFmiProducerName;

    /*! \brief  The fmi parameter identifier.*/
    T::ParamId                mFmiParameterId;

    /*! \brief  The fmi parameter level identifier. */
    T::ParamLevelId           mFmiParameterLevelId;

    /*! \brief  The fmi parameter name. */
    std::string               mFmiParameterName;

    /*! \brief  The fmi parameter description. */
    std::string               mFmiParameterDescription;

    /*! \brief  The fmi parameter units. */
    std::string               mFmiParameterUnits;

    /*! \brief  The cdm parameter id string. */
    std::string               mCdmParameterId;

    /*! \brief  The cdm parameter name. */
    std::string               mCdmParameterName;

    /*! \brief  The newbase parameter id string. */
    std::string               mNewbaseParameterId;

    /*! \brief  The newbase parameter name. */
    std::string               mNewbaseParameterName;

    /*! \brief  The virtual file id. If the value is bigger that zero, then the virtual message should be used
     * instead of this message
     * */
    uint                      mVirtualFileId;

    short                     mDefaultInterpolationMethod;

    mutable ThreadLock        mThreadLock;

    mutable bool              mRequestCounterEnabled;
    bool                      mPointCacheEnabled;
    mutable PointCache        mPointCache;
    mutable uint              mCacheHitCounter;
    mutable time_t            mLastCacheAccess;

};



typedef Message* MessagePtr;
typedef std::vector<MessagePtr> MessagePtr_vec;


}  // namespace GRID
}  // namespace SmartMet

