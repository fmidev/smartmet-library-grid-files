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
  uint               mDataType;
  uint               mBitsPerValue;
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


typedef std::vector<MessageInfo> MessageInfoVec;

class GeoTiffFile;


class Message : public GRID::Message
{
  public:

                        Message();
                        Message(const Message& message);
                        Message(GRID::GridFile *gridFile,GeoTiffFile *geoTiffFile,T::MessageIndex messageIndex,GeoTiff::MessageInfo& messageInfo);
    virtual             ~Message();

    void                getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const;
    T::FileId           getFileId() const;
    T::FileType         getMessageType() const;
    T::ProducerId       getProducerId() const;
    T::GenerationId     getGenerationId() const;
    T::FilePosition     getFilePosition() const;
    T::TimeString       getForecastTime() const;
    time_t              getForecastTimeT() const;
    T::ForecastType     getForecastType() const;
    T::ForecastNumber   getForecastNumber() const;

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
    bool                getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    bool                getGridMetricCellSize(double& width,double& height) const;
    bool                getGridMetricSize(double& width,double& height) const;
    T::Coordinate_svec  getGridOriginalCoordinates() const;
    bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    std::size_t         getGridOriginalValueCount() const;
    int                 getGridOriginalValueIndex(uint grid_i,uint grid_j) const;
    void                getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    T::GridProjection   getGridProjection() const;
    void                getGridProjectionAttributes(const std::string& prefix,T::AttributeList& attributeList) const;
    std::size_t         getGridColumnCount() const;
    std::size_t         getGridRowCount() const;

    T::ParamValue       getGridValueByGridPoint(uint grid_i,uint grid_j) const;
    void                getGridValueVector(T::ParamValue_vec& values) const;
    void                getGridOriginalValueVector(T::ParamValue_vec& values) const;
    T::ParamLevel       getGridParameterLevel() const;
    T::ParamLevelId     getGridParameterLevelId() const;
    void                getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const;

    T::TimeString       getReferenceTime() const;
    T::SpatialRef_sptr  getSpatialReference() const;
    std::string         getWKT() const;
    std::string         getProj4() const;
    void                initSpatialReference();
    bool                isGridGlobal() const;
    bool                isRelativeUV() const;
    bool                reverseXDirection() const;
    bool                reverseYDirection() const;

    void                setGridSize(uint columns,uint rows);
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



typedef Message* MessagePtr;
typedef std::vector<MessagePtr> MessagePtr_vec;


}  // namespace NetCDF
}  // namespace SmartMet


