#pragma once


#include "../grid/Message.h"
#include "../grib2/Message.h"


namespace SmartMet
{
namespace GeoTiff
{

struct MessageInfo
{
  char*              mDataPtr = nullptr;
  uint               mDataSize = 0;
  uint               mDataType = 0;
  uint               mBitsPerValue = 0;
  time_t             mForecastTimeT = 0;
  uint               mColumns = 0;
  uint               mRows = 0;
  std::string        mParameterName;
  T::ParamLevelId    mLevelId = 0;
  T::ParamLevel      mLevel = 0;
  T::ForecastType    mForecastType = 0;
  T::ForecastNumber  mForecastNumber = 0;
  T::GeometryId      mGeometryId = 0;
};


using MessageInfoVec = std::vector<MessageInfo>;

class GeoTiffFile;


class Message : public GRID::Message
{
  public:

                        Message();
                        Message(const Message& message);
                        Message(GRID::GridFile *gridFile,GeoTiffFile *geoTiffFile,T::MessageIndex messageIndex,const GeoTiff::MessageInfo& messageInfo);
    ~Message() override;
    Message& operator=(const Message&) = default;

    void                getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const override;
    T::FileId           getFileId() const override;
    T::FileType         getMessageType() const override;
    T::ProducerId       getProducerId() const override;
    T::GenerationId     getGenerationId() const override;
    T::FilePosition     getFilePosition() const override;
    T::TimeString       getForecastTime() const override;
    time_t              getForecastTimeT() const override;
    T::ForecastType     getForecastType() const override;
    T::ForecastNumber   getForecastNumber() const override;

    void                getGridCellAverageSize(double& width,double& height) const override;
    T::Dimensions       getGridDimensions() const override;
    T::GeometryId       getGridGeometryId() const override;
    std::string         getGridGeometryString() const override;
    T::Hash             getGridHash() const override;
    bool                getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight) override;
    T::Coordinate_svec  getGridLatLonCoordinates() const override;
    bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const override;
    void                getGridLatLonCoordinatesByGridPointList(std::vector<T::Point>& gridPoints,T::Coordinate_vec& coordinates,std::vector<bool>& found) const override;
    bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const override;
    bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const override;
    bool                getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight) override;
    bool                getGridMetricCellSize(double& width,double& height) const override;
    bool                getGridMetricSize(double& width,double& height) const override;
    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const override;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const override;
    bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const override;
    std::size_t         getGridOriginalValueCount() const override;
    int                 getGridOriginalValueIndex(uint grid_i,uint grid_j) const override;
    void                getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;
    bool                getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j) const override;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const override;
    T::GridProjection   getGridProjection() const override;
    void                getGridProjectionAttributes(const std::string& prefix,T::AttributeList& attributeList) const override;
    std::size_t         getGridColumnCount() const override;
    std::size_t         getGridRowCount() const override;

    T::ParamValue       getGridValueByGridPoint(uint grid_i,uint grid_j) const override;
    void                getGridValueVector(T::ParamValue_vec& values) const override;
    void                getGridOriginalValueVector(T::ParamValue_vec& values) const override;
    T::ParamLevel       getGridParameterLevel() const override;
    T::ParamLevelId     getGridParameterLevelId() const override;
    void                getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const override;

    T::TimeString       getReferenceTime() const override;
    T::SpatialRef_sptr  getSpatialReference() const override;
    std::string         getWKT() const override;
    std::string         getProj4() const override;
    void                initSpatialReference() override;
    bool                isGridGlobal() const override;
    bool                isRelativeUV() const override;
    bool                reverseXDirection() const override;
    bool                reverseYDirection() const override;

    void                setGridSize(uint columns,uint rows);
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

    GRID::GridFile*     mGridFile;
    char*               mDataPtr;
    uint                mDataSize;
    uint                mDataType;
    uint                mBitsPerValue;
    T::ForecastType     mForecastType;
    T::ForecastNumber   mForecastNumber;
    std::string         mForecastTime;
    time_t              mForecastTimeT;
    GeoTiffFile*        mGeoTiffFile;
    GRIB2::GridDef_sptr mGeometryDef;
    T::GridProjection   mProjectionId;
    bool                mIsRead;
};



using MessagePtr = Message*;
using MessagePtr_vec = std::vector<MessagePtr>;


}  // namespace NetCDF
}  // namespace SmartMet


