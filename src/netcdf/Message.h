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

using MessageInfoVec = std::vector<MessageInfo>;

class NetCdfFile;


class Message : public GRID::Message
{
  public:

                        Message();
                        Message(const Message& message);
                        Message(GRID::GridFile *gridFile,NetCdfFile *netCdfFile,uint messageIndex,NetCDF::MessageInfo& messageInfo);
                ~Message() override;

    void                getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const override;
    uint                getFileId() const override;
    T::FileType         getMessageType() const override;
    uint                getProducerId() const override;
    uint                getGenerationId() const override;
    T::FilePosition     getFilePosition() const override;
    T::TimeString       getForecastTime() const override;
    time_t              getForecastTimeT() const override;
    short               getForecastType() const override;
    short               getForecastNumber() const override;

    //uint                getFileMessageCount();

    void                getGridCellAverageSize(double& width,double& height) const override;
    T::Dimensions       getGridDimensions() const override;
    T::GeometryId       getGridGeometryId() const override;
    std::string         getGridGeometryString() const override;
    T::Hash             getGridHash() const override;
    bool                getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight) override;
    T::Coordinate_svec  getGridLatLonCoordinates() const override;
    bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const override;
    bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const override;
    bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const override;
    T::GridLayout       getGridLayout() const override;
    bool                getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight) override;
    bool                getGridMetricCellSize(double& width,double& height) const override;
    bool                getGridMetricSize(double& width,double& height) const override;
    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const override;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const override;
    bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const override;
    std::size_t         getGridOriginalColumnCount(std::size_t row) const override;
    std::size_t         getGridOriginalColumnCount() const override;
    std::size_t         getGridOriginalRowCount() const override;
    std::size_t         getGridOriginalValueCount() const override;
    int                 getGridOriginalValueIndex(uint grid_i,uint grid_j) const override;
    void                getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;
    bool                getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j) const override;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const override;
    T::GridProjection   getGridProjection() const override;
    void                getGridProjectionAttributes(const std::string& prefix,T::AttributeList& attributeList) const override;
    std::string         getGridProjectionString() const override;
    std::size_t         getGridColumnCount() const override;
    std::size_t         getGridRowCount() const override;

    T::ParamValue       getGridValueByGridPoint(uint grid_i,uint grid_j) const override;
    T::ParamValue       getGridValueByOriginalGridPoint(uint grid_i,uint grid_j) const override;
    void                getGridValueVector(T::ParamValue_vec& values) const override;
    void                getGridOriginalValueVector(T::ParamValue_vec& values) const override;
    T::ParamLevel       getGridParameterLevel() const override;
    T::ParamLevelId     getGridParameterLevelId() const override;
    std::string         getGridParameterLevelIdString() const override;
    void                getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const override;

    T::TimeString       getReferenceTime() const override;
    T::SpatialRef*      getSpatialReference() const override;
    std::string         getWKT() const override;
    std::string         getProj4() const override;
    void                initSpatialReference() override;
    bool                isGridGlobal() const override;
    bool                isRelativeUV() const override;
    bool                reverseXDirection() const override;
    bool                reverseYDirection() const override;

    void                setGridGeometryId(T::GeometryId geometryId) override;
    void                setGridValues(T::ParamValue_vec& values) override;

    void                lockData() override;
    void                unlockData() override;

    bool                isRead() override;
    void                print(std::ostream& stream,uint level,uint optionFlags) const override;
    void                read() override;
    void                read(MemoryReader& memoryReader) override;
    void                write(DataWriter& dataWriter) override;

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



using MessagePtr = Message *;
using MessagePtr_vec = std::vector<MessagePtr>;


}  // namespace NetCDF
}  // namespace SmartMet


