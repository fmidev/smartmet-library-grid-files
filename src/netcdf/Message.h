#pragma once


#include "../grid/Message.h"
#include "../grib2/Message.h"


namespace SmartMet
{
namespace NetCDF
{

struct MessageInfo
{
  std::uint64_t      mFilePosition;
  uint               mMessageSize;
  T::FileType        mMessageType;
  uint               mColumns;
  uint               mRows;
  uint               mRowMultiplier;
  uint               mColumnMultiplier;
  uint               mLevels;
  uchar              mDataType;
  double             mBaseValue;
  double             mScaleFactor;
  std::string        mParameterName;
  std::string        mParameterStandardName;
  T::ParamLevelId    mParameterLevelId;
  T::ParamLevel      mParameterLevel;
  std::string        mParameterUnits;
  T::ForecastType    mForecastType;
  T::ForecastNumber  mForecastNumber;
  time_t             mForecastTimeT;
  T::ParamValue      mMissingValue;
  T::GridProjection  mProjectionId;
  int                mGeometryId;
};

typedef std::vector<MessageInfo> MessageInfoVec;

class NetCdfFile;


class Message : public GRID::Message
{
  public:

                        Message();
                        Message(const Message& message);
                        Message(GRID::GridFile *gridFile,NetCdfFile *netCdfFile,uint messageIndex,NetCDF::MessageInfo& messageInfo);
    virtual             ~Message();

    void                getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const;
    uint                getFileId() const;
    T::FileType         getMessageType() const;
    uint                getProducerId() const;
    uint                getGenerationId() const;
    T::FilePosition     getFilePosition() const;
    T::TimeString       getForecastTime() const;
    time_t              getForecastTimeT() const;
    short               getForecastType() const;
    short               getForecastNumber() const;

    //uint                getFileMessageCount();

    void                getGridCellAverageSize(double& width,double& height) const;
    T::Dimensions       getGridDimensions() const;
    T::GeometryId       getGridGeometryId() const;
    std::string         getGridGeometryString() const;
    T::Hash             getGridHash() const;
    bool                getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    T::Coordinate_svec  getGridLatLonCoordinates() const;
    bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;
    bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    //T::GridLayout       getGridLayout() const;
    bool                getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    bool                getGridMetricCellSize(double& width,double& height) const;
    bool                getGridMetricSize(double& width,double& height) const;
    T::Coordinate_svec  getGridOriginalCoordinates() const;
    bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    //std::size_t         getGridColumnCount(std::size_t row) const;
    //std::size_t         getGridColumnCount() const;
    //std::size_t         getGridRowCount() const;
    std::size_t         getGridOriginalValueCount() const;
    int                 getGridOriginalValueIndex(uint grid_i,uint grid_j) const;
    void                getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    T::GridProjection   getGridProjection() const;
    void                getGridProjectionAttributes(const std::string& prefix,T::AttributeList& attributeList) const;
    //std::string         getGridProjectionString() const;
    std::size_t         getGridColumnCount() const;
    std::size_t         getGridRowCount() const;

    T::ParamValue       getGridValueByGridPoint(uint grid_i,uint grid_j) const;
    //T::ParamValue       getGridValueByOriginalGridPoint(uint grid_i,uint grid_j) const;
    void                getGridValueVector(T::ParamValue_vec& values) const;
    void                getGridOriginalValueVector(T::ParamValue_vec& values) const;
    T::ParamLevel       getGridParameterLevel() const;
    T::ParamLevelId     getGridParameterLevelId() const;
    //std::string         getGridParameterLevelIdString() const;
    void                getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const;

    T::TimeString       getReferenceTime() const;
    T::SpatialRef*      getSpatialReference() const;
    std::string         getWKT() const;
    std::string         getProj4() const;
    void                initSpatialReference();
    bool                isGridGlobal() const;
    bool                isRelativeUV() const;
    bool                reverseXDirection() const;
    bool                reverseYDirection() const;

    void                setGridGeometryId(T::GeometryId geometryId);
    void                setGridValues(T::ParamValue_vec& values);

    void                lockData();
    void                unlockData();

    bool                isRead();
    void                print(std::ostream& stream,uint level,uint optionFlags) const;
    void                read();
    void                read(MemoryReader& memoryReader);
    void                write(DataWriter& dataWriter);

  protected:

    std::uint64_t       mFilePosition;
    uint                mColumns;
    uint                mRows;
    uint                mRowMultiplier;
    uint                mColumnMultiplier;
    double              mBaseValue;
    double              mScaleFactor;
    std::string         mParameterName;
    std::string         mParameterUnits;
    std::string         mVariableName;
    T::ForecastType     mForecastType;
    T::ForecastNumber   mForecastNumber;
    std::string         mForecastTime;
    time_t              mForecastTimeT;
    T::ParamValue       mMissingValue;
    T::GridProjection   mProjectionId;
    GRID::GridFile*     mGridFile;
    uchar*              mDataStartPtr;
    uchar*              mDataEndPtr;
    NetCdfFile*         mNetCdfFile;
    GRIB2::GridDef_ptr  mGeometryDef;
    uchar               mDataType;
    bool                mIsRead;
};



typedef Message* MessagePtr;
typedef std::vector<MessagePtr> MessagePtr_vec;


}  // namespace NetCDF
}  // namespace SmartMet


