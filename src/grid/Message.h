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
#include "../common/AutoThreadLock.h"
#include "../common/AutoWriteLock.h"
#include "../common/AutoReadLock.h"
#include "../common/ThreadLock.h"
#include "../common/RequestCounter.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../common/StringFactory.h"

#include <vector>
#include <string>
#include <memory>



namespace SmartMet
{
namespace GRID
{

struct MessageInfo
{
  ulonglong          mFilePosition;
  uint               mMessageSize;
  uint               mProducerId;
  uint               mGenerationId;
  T::FmiParamId      mFmiParameterId;
  uint               mFmiParameterName;
  T::ParamLevelId    mFmiParameterLevelId;
  T::ParamLevel      mParameterLevel;
  T::ForecastType    mForecastType;
  T::ForecastNumber  mForecastNumber;
  T::GeometryId      mGeometryId;
};

typedef std::map<uint,MessageInfo> MessageInfo_map;
typedef std::unordered_map<uint,T::ParamValue> PointCache;

class GridFile;

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
    virtual                     ~Message();

    virtual void                getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const;
    virtual uint                getFileId() const;
    virtual uint                getProducerId() const;
    virtual uint                getGenerationId() const;
    virtual uint                getMessageIndex() const;
    virtual uint                getMessageSize() const;
    virtual T::FilePosition     getFilePosition() const;
    virtual T::TimeString       getForecastTime() const;
    virtual time_t              getForecastTimeT() const;
    virtual short               getForecastType() const;
    virtual short               getForecastNumber() const;

    virtual const char*         getFmiProducerName() const;
    virtual T::FmiParamId       getFmiParameterId() const;
    virtual T::ParamLevelId     getFmiParameterLevelId() const;
    virtual const char*         getFmiParameterName() const;
    virtual const char*         getFmiParameterUnits() const;
    virtual T::NewbaseParamId   getNewbaseParameterId() const;
    virtual const char*         getNewbaseParameterName() const;

    virtual uint                getGribVersion() const;
    virtual uint                getGribCentre() const;
    virtual uint                getGribSubCentre() const;
    virtual uint                getGribGeneratingProcessIdentifier() const;
    virtual uint                getGribTableVersion() const;
    virtual void                getSectionPositions(std::set<T::FilePosition>& positions);

    virtual T::GribParamId      getGribParameterId() const;
    virtual const char*         getGribParameterName() const;
    virtual const char*         getGribParameterUnits() const;
    virtual T::ParamLevelId     getGrib1ParameterLevelId() const;
    virtual T::ParamLevelId     getGrib2ParameterLevelId() const;

    virtual void                getGridCellAverageSize(double& width,double& height) const;
    virtual T::Dimensions       getGridDimensions() const;
    virtual T::GeometryId       getGridGeometryId() const;
    virtual std::string         getGridGeometryString() const;
    virtual T::Hash             getGridHash() const;
    virtual void                getGridIsobands(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours);
    virtual void                getGridIsobandsByGeometry(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours);
    virtual void                getGridIsobandsByGrid(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,std::vector<T::Coordinate>& projectionCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours);
    virtual void                getGridIsolines(T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours);
    virtual void                getGridIsolinesByGeometry(T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours);
    virtual void                getGridIsolinesByGrid(T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,std::vector<T::Coordinate>& projectionCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours);
    virtual bool                getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    virtual T::Coordinate_svec  getGridLatLonCoordinates() const;
    virtual bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    virtual bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;
    virtual bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    virtual T::GridLayout       getGridLayout() const;
    virtual bool                getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    virtual bool                getGridMetricCellSize(double& width,double& height) const;
    virtual bool                getGridMetricSize(double& width,double& height) const;
    virtual T::Coordinate_svec  getGridOriginalCoordinates() const;
    virtual bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    virtual bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    virtual bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    virtual std::size_t         getGridOriginalColumnCount(std::size_t row) const;
    virtual std::size_t         getGridOriginalColumnCount() const;
    virtual std::size_t         getGridOriginalRowCount() const;
    virtual std::size_t         getGridOriginalValueCount() const;
    virtual int                 getGridOriginalValueIndex(uint grid_i,uint grid_j) const;
    virtual float               getGridPointAngleByLatLonCoordinates(double lat,double lon) const;
    virtual float               getGridPointAngle(T::CoordinateType coordinateType,double x,double y) const;
    virtual void                getGridPointAngles(std::vector<float>& angles) const;
    virtual void                getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const;
    virtual bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    virtual bool                getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j) const;
    virtual bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    virtual T::GridProjection   getGridProjection() const;
    virtual void                getGridProjectionAttributes(const std::string& prefix,T::AttributeList& attributeList) const;
    virtual std::string         getGridProjectionString() const;
    virtual std::size_t         getGridColumnCount() const;
    virtual std::size_t         getGridRowCount() const;
    virtual uint                getGridWidth() const;
    virtual uint                getGridHeight() const;

    virtual void                getGridValueByPoint(T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,T::ParamValue& value) const;
    virtual void                getGridValueListByCircle(T::CoordinateType coordinateType,double origoX,double origoY,double radius,T::GridValueList& valueList) const;
    virtual void                getGridValueListByPointList(T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,T::GridValueList& valueList) const;
    virtual void                getGridValueListByPolygon(T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,T::GridValueList& valueList) const;
    virtual void                getGridValueListByPolygonPath(T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,T::GridValueList& valueList) const;
    virtual void                getGridValueListByRectangle(T::CoordinateType coordinateType,double x1,double y1,double x2,double y2,bool gridRectangle,T::GridValueList& valueList) const;

    virtual void                getGridValueVector(T::ParamValue_vec& values) const;
    virtual void                getGridValueVectorWithCaching(T::ParamValue_vec& values) const;
    virtual void                getGridValueVectorByCrop(T::AttributeList& attributeList,T::ParamValue_vec& values) const;
    virtual void                getGridValueVectorByGeometry(T::AttributeList& attributeList,T::ParamValue_vec& values) const;
    virtual void                getGridValueVectorByCoordinateList(T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,T::ParamValue_vec& values) const;
    virtual void                getGridValueVectorByLatLonCoordinateList(std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,T::ParamValue_vec& values) const;
    virtual void                getGridValueVectorByGridPointList(std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,T::ParamValue_vec& values) const;

    virtual void                getGridOriginalValueVector(T::ParamValue_vec& values) const;
    virtual T::ParamLevel       getGridParameterLevel() const;
    virtual T::ParamLevelId     getGridParameterLevelId() const;
    virtual std::string         getGridParameterLevelIdString() const;
    virtual void                getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const;

    virtual void                getGridValueVectorByPoint(T::CoordinateType coordinateType,double x,double y,uint vectorType,double_vec& valueVector) const;
    virtual void                getGridValueVectorByGridPoint(double grid_i,double grid_j,uint vectorType,double_vec& valueVector) const;
    virtual void                getGridValueVectorByLatLonCoordinate(double lat,double lon,uint vectorType,double_vec& valueVector) const;

    virtual T::ParamValue       getGridValueByGridPoint(uint grid_i,uint grid_j) const;
    virtual T::ParamValue       getGridValueByGridPoint_byInterpolation(double grid_i,double grid_j,short areaInterpolationMethod) const;
    virtual T::ParamValue       getGridValueByGridPoint_noInterpolation(double grid_i,double grid_j) const;
    virtual T::ParamValue       getGridValueByGridPoint_nearest(double grid_i,double grid_j) const;
    virtual T::ParamValue       getGridValueByGridPoint_min(double grid_i,double grid_j) const;
    virtual T::ParamValue       getGridValueByGridPoint_max(double grid_i,double grid_j) const;
    virtual T::ParamValue       getGridValueByGridPoint_linearInterpolation(double grid_i,double grid_j) const;
    virtual T::ParamValue       getGridValueByLatLonCoordinate(double lat,double lon,short areaInterpolationMethod) const;
    virtual T::ParamValue       getGridValueByOriginalGridPoint(uint grid_i,uint grid_j) const;
    virtual void                getGridValueVectorByRectangle(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,T::GridPointValue_vec& gridPointValues) const;
    virtual void                getParameterValuesByRectangle(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,T::GridPointValueList& gridPointValues) const;
    virtual short               getDefaultInterpolationMethod() const;
    virtual T::TimeString       getReferenceTime() const;
    virtual T::SpatialRef*      getSpatialReference() const;
    virtual std::string         getWKT() const;
    virtual std::string         getProj4() const;
    virtual void                initSpatialReference();
    virtual bool                isGridGlobal() const;
    virtual bool                isRelativeUV() const;
    virtual bool                reverseXDirection() const;
    virtual bool                reverseYDirection() const;

    virtual void                setMessageIndex(uint index);
    virtual void                setGridFilePtr(GridFile *gridFilePtr);

    virtual void                setFmiParameterId(T::FmiParamId fmiParameterId);
    virtual void                setFmiParameterLevelId(T::ParamLevelId fmiParameterLevelId);
    virtual void                setFmiParameterName(const char* fmiParameterName);
    virtual void                setFmiParameterUnits(const char* fmiParameterUnits);
    virtual void                setNewbaseParameterId(T::NewbaseParamId newbaseParameterId);
    virtual void                setNewbaseParameterName(const char* newbaseParameterName);

    virtual void                setGridGeometryId(T::GeometryId geometryId);
    virtual void                setGridValues(T::ParamValue_vec& values);

    // Common Grib settings

    virtual void                setGribParameterId(T::GribParamId gribParameterId);
    virtual void                setGribParameterName(const char* gribParameterName);
    virtual void                setGribParameterUnits(const char* gribParameterUnits);

    // Grib 1 specific settings

    virtual void                setGrib1ParameterLevelId(T::ParamLevelId grib1ParameterLevelId);

    // Grib 2 specific settings

    virtual void                setGrib2ParameterLevelId(T::ParamLevelId grib2ParameterLevelId);

    virtual bool                getProperty(uint propertyId,long long& value);
    virtual bool                getProperty(const char *propertyName,long long& value);

    virtual bool                setProperty(uint propertyId,char value);
    virtual bool                setProperty(uint propertyId,short value);
    virtual bool                setProperty(uint propertyId,int value);
    virtual bool                setProperty(uint propertyId,long value);
    virtual bool                setProperty(uint propertyId,unsigned char value);
    virtual bool                setProperty(uint propertyId,unsigned short value);
    virtual bool                setProperty(uint propertyId,unsigned int value);
    virtual bool                setProperty(uint propertyId,unsigned long value);
    virtual bool                setProperty(uint propertyId,long long value);
    virtual bool                setProperty(uint propertyId,double value);

    virtual bool                setProperty(const char *propertyName,char value);
    virtual bool                setProperty(const char *propertyName,short value);
    virtual bool                setProperty(const char *propertyName,int value);
    virtual bool                setProperty(const char *propertyName,long value);
    virtual bool                setProperty(const char *propertyName,unsigned char value);
    virtual bool                setProperty(const char *propertyName,unsigned short value);
    virtual bool                setProperty(const char *propertyName,unsigned int value);
    virtual bool                setProperty(const char *propertyName,unsigned long value);
    virtual bool                setProperty(const char *propertyName,long long value);
    virtual bool                setProperty(const char *propertyName,double value);

    virtual void                setPointCacheEnabled(bool enabled);

    virtual void                addCachedValue(uint index,T::ParamValue value) const;
    virtual bool                getCachedValue(uint index,T::ParamValue& value) const;
    virtual void                clearCachedValues(uint hitsRequired,uint timePeriod) const;

    virtual void                lockData();
    virtual void                unlockData();

    virtual bool                isRead();
    virtual void                print(std::ostream& stream,uint level,uint optionFlags) const;
    virtual void                read();
    virtual void                read(MemoryReader& memoryReader);
    virtual void                write(DataWriter& dataWriter);


  protected:

    /*! \brief  The index of the message in the file. */
    uint                        mMessageIndex;

    /*! \brief  The size of the message in bytes. */
    uint                        mMessageSize;

    /*! \brief  The fmi parameter identifier.*/
    T::FmiParamId               mFmiParameterId;

    /*! \brief  The newbase parameter id string. */
    T::NewbaseParamId           mNewbaseParameterId;

    /*! \brief The grib parameter identifier. */
    T::GribParamId              mGribParameterId;

    /*! \brief  The geometry identifier. */
    T::GeometryId               mGeometryId;


    /*! \brief  The fmi parameter name. */
    uint                        mFmiParameterName;

    /*! \brief  The newbase parameter name. */
    uint                        mNewbaseParameterName;

    /*! \brief  The grib parameter name. */
    uint                        mGribParameterName;

    /*! \brief  The fmi parameter units. */
    uint                        mFmiParameterUnits;

    /*! \brief  The grib parameter units. */
    uint                        mGribParameterUnits;

    /*! \brief  The fmi producer name. */
    uint                        mFmiProducerName;



    /*! \brief  The file type. */
    uchar                       mFileType;

    /*! \brief  The grib1 parameter level identifier. */
    T::ParamLevelId             mGrib1ParameterLevelId;

    /*! \brief  The grib2 parameter level identifier. */
    T::ParamLevelId             mGrib2ParameterLevelId;

    /*! \brief  The fmi parameter level identifier. */
    T::ParamLevelId             mFmiParameterLevelId;

    /*! \brief  The parameter level. */
    T::ParamLevel               mParameterLevel;


    /*! \brief  The virtual file id. If the value is bigger that zero, then the virtual message should be used
     * instead of this message
     * */
    uint                        mVirtualFileId;
    uint                        mRowCount;
    uint                        mColumnCount;
    mutable uint                mCacheHitCounter;

    mutable time_t              mLastCacheAccess;
    GridFile*                   mGridFilePtr;
    mutable ThreadLock          mThreadLock;
    mutable ModificationLock    mCacheModificationLock;
    mutable PointCache          mPointCache;
    short                       mDefaultInterpolationMethod;
    bool                        mPointCacheEnabled;
};



typedef Message* MessagePtr;
typedef std::vector<MessagePtr> MessagePtr_vec;


}  // namespace GRID
}  // namespace SmartMet

