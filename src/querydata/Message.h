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


