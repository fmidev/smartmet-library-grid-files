#pragma once


#include "../grid/Message.h"
#include "../grib2/Message.h"


namespace SmartMet
{
namespace NetCDF
{

/*! \brief Metadata record describing one NetCDF variable/level/time slice as a grid message.
 *
 *  Populated by NetCdfFile::createMessageInfoList() and passed to the Message constructor. */
struct MessageInfo
{
  std::uint64_t      mFilePosition = 0;          //!< Byte offset of the variable data in the NetCDF file.
  uint               mMessageSize = 0;           //!< Size of the encoded data block in bytes.
  T::FileType        mMessageType = 0;           //!< File type tag (always NetCDF for this struct).
  uint               mColumns = 0;              //!< Number of grid columns (longitude dimension).
  uint               mRows = 0;                 //!< Number of grid rows (latitude dimension).
  uint               mRowMultiplier = 0;        //!< Sub-sampling stride in the row direction.
  uint               mColumnMultiplier = 0;     //!< Sub-sampling stride in the column direction.
  uint               mLevels = 0;               //!< Number of vertical levels in the variable.
  uchar              mDataType = 0;             //!< NetCDF data type code for the stored values.
  double             mBaseValue = 0.0;            //!< add_offset attribute value.
  double             mScaleFactor = 0.0;          //!< scale_factor attribute value.
  std::string        mParameterName;        //!< NetCDF variable long_name or name.
  std::string        mParameterStandardName;//!< CF standard_name of the variable.
  T::ParamLevelId    mParameterLevelId = 0;     //!< FMI level type identifier.
  T::ParamLevel      mParameterLevel = 0;       //!< Level value (pressure, height, etc.).
  std::string        mParameterUnits;       //!< CF units attribute string.
  T::ForecastType    mForecastType = 0;         //!< Forecast type code.
  T::ForecastNumber  mForecastNumber = 0;       //!< Ensemble member or perturbation number.
  time_t             mForecastTimeT = 0;        //!< Forecast valid time as a Unix timestamp.
  T::ParamValue      mMissingValue = 0.0F;         //!< Fill/missing value used for undefined grid points.
  T::GridProjection  mProjectionId = 0;         //!< Grid projection type.
  int                mGeometryId = 0;           //!< FMI geometry identifier.
};

using MessageInfoVec = std::vector<MessageInfo>;

class NetCdfFile;


// ====================================================================================
/*! \brief NetCDF message — adapts one NetCDF variable/level/time slice to the
 *  GRID::Message interface.
 *
 *  Constructed by NetCdfFile::read() for each detected variable slice; metadata is
 *  provided via a MessageInfo record.  Values are decoded on first access and then
 *  served through the standard grid value accessors inherited from GRID::Message.
 *  The underlying NetCDF data may be scaled (add_offset / scale_factor). */
// ====================================================================================

class Message : public GRID::Message
{
  public:

                        Message();
                        Message(const Message& message);
                        Message(GRID::GridFile *gridFile,NetCdfFile *netCdfFile,T::MessageIndex messageIndex,const NetCDF::MessageInfo& messageInfo);
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

    std::uint64_t       mFilePosition;    //!< Byte offset of the variable slice in the file.
    uint                mColumns;         //!< Number of grid columns.
    uint                mRows;            //!< Number of grid rows.
    uint                mRowMultiplier;   //!< Sub-sampling stride in the row direction.
    uint                mColumnMultiplier;//!< Sub-sampling stride in the column direction.
    double              mBaseValue;       //!< add_offset attribute value.
    double              mScaleFactor;     //!< scale_factor attribute value.
    std::string         mParameterName;   //!< Human-readable parameter name.
    std::string         mParameterUnits;  //!< CF units string.
    std::string         mVariableName;    //!< NetCDF variable name.
    T::ForecastType     mForecastType;    //!< Forecast type code.
    T::ForecastNumber   mForecastNumber;  //!< Ensemble member or perturbation number.
    std::string         mForecastTime;    //!< Forecast valid time as an ISO-8601 string.
    time_t              mForecastTimeT;   //!< Forecast valid time as a Unix timestamp.
    T::ParamValue       mMissingValue;    //!< Fill/missing value for undefined grid points.
    T::GridProjection   mProjectionId;    //!< Grid projection type.
    GRID::GridFile*     mGridFile;        //!< Owning GridFile (not owned by this object).
    uchar*              mDataStartPtr;    //!< Start of the memory-mapped data region.
    uchar*              mDataEndPtr;      //!< One-past-end of the memory-mapped data region.
    NetCdfFile*         mNetCdfFile;      //!< Parser object that decoded the NetCDF metadata.
    GRIB2::GridDef_sptr mGeometryDef;    //!< Grid geometry definition derived from projection metadata.
    uchar               mDataType;        //!< NetCDF storage type code for the packed values.
    bool                mIsRead;          //!< True after grid values have been decoded.
};



using MessagePtr = Message*;                   //!< Non-owning pointer to a NetCDF Message.
using MessagePtr_vec = std::vector<MessagePtr>; //!< Vector of non-owning NetCDF Message pointers.


}  // namespace NetCDF
}  // namespace SmartMet


