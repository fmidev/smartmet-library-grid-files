#pragma once


#include "../grid/Message.h"
#include "../grib2/Message.h"


namespace SmartMet
{
namespace QueryData
{

/*! \brief Metadata record identifying one parameter/level/time slice inside a QueryData file.
 *
 *  Populated by QueryDataFile::read() and passed to the Message constructor. */
struct MessageInfo
{
  uint        mColumns;          //!< Number of grid columns.
  uint        mRows;             //!< Number of grid rows.
  UInt64      mParameterIndex;   //!< Index into the NFmiFastQueryInfo parameter dimension.
  UInt64      mLevelIndex;       //!< Index into the NFmiFastQueryInfo level dimension.
  UInt64      mTimeIndex;        //!< Index into the NFmiFastQueryInfo time dimension.
  uint        mNewbaseId;        //!< Newbase parameter identifier.
  int         mParameterLevelId; //!< FMI level type identifier.
  int         mParameterLevel;   //!< Level value (pressure, height, etc.).
  time_t      mForecastTimeT;    //!< Forecast valid time as a Unix timestamp.
  int         mGeometryId;       //!< FMI geometry identifier.
};


typedef std::vector<MessageInfo> MessageInfoVec;

class QueryDataFile;


// ====================================================================================
/*! \brief QueryData message — adapts one NFmiQueryData parameter/level/time slice to
 *  the GRID::Message interface.
 *
 *  Constructed by reading the NFmiFastQueryInfo index provided in a MessageInfo record.
 *  Grid values are retrieved on demand from the owning QueryDataFile object, which
 *  keeps the NFmiFastQueryInfo alive for the lifetime of all messages derived from it. */
// ====================================================================================

class Message : public GRID::Message
{
  public:

                        Message();
                        Message(const Message& message);
                        Message(GRID::GridFile *gridFile,QueryDataFile *queryDataFile,T::MessageIndex messageIndex,QueryData::MessageInfo& messageInfo);
    ~Message() override;

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

    GRID::GridFile*     mGridFile;          //!< Owning GridFile (not owned by this object).
    uint                mColumns;           //!< Number of grid columns.
    uint                mRows;              //!< Number of grid rows.
    UInt64              mParameterIndex;    //!< Parameter index in NFmiFastQueryInfo.
    UInt64              mLevelIndex;        //!< Level index in NFmiFastQueryInfo.
    UInt64              mTimeIndex;         //!< Time index in NFmiFastQueryInfo.
    int                 mParameterLevelId;  //!< FMI level type identifier.
    int                 mParameterLevel;    //!< Level value (pressure, height, etc.).
    int                 mGeometryId;        //!< FMI geometry identifier.
    T::ForecastType     mForecastType;      //!< Forecast type code.
    T::ForecastNumber   mForecastNumber;    //!< Ensemble member or perturbation number.
    std::string         mForecastTime;      //!< Forecast valid time as an ISO-8601 string.
    time_t              mForecastTimeT;     //!< Forecast valid time as a Unix timestamp.
    QueryDataFile*      mQueryDataFile;     //!< QueryData file that owns the underlying NFmiFastQueryInfo.
    GRIB2::GridDef_sptr mGeometryDef;      //!< Grid geometry definition.
    T::GridProjection   mProjectionId;      //!< Grid projection type.
    bool                mIsRead;            //!< True after grid values have been decoded.
};



typedef Message* MessagePtr;                    //!< Non-owning pointer to a QueryData Message.
typedef std::vector<MessagePtr> MessagePtr_vec;  //!< Vector of non-owning QueryData Message pointers.


}  // namespace NetCDF
}  // namespace SmartMet


