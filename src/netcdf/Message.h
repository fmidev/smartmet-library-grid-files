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
  std::uint64_t      mFilePosition;          //!< Byte offset of the variable data in the NetCDF file.
  uint               mMessageSize;           //!< Size of the encoded data block in bytes.
  T::FileType        mMessageType;           //!< File type tag (always NetCDF for this struct).
  uint               mColumns;              //!< Number of grid columns (longitude dimension).
  uint               mRows;                 //!< Number of grid rows (latitude dimension).
  uint               mRowMultiplier;        //!< Sub-sampling stride in the row direction.
  uint               mColumnMultiplier;     //!< Sub-sampling stride in the column direction.
  uint               mLevels;               //!< Number of vertical levels in the variable.
  uchar              mDataType;             //!< NetCDF data type code for the stored values.
  double             mBaseValue;            //!< add_offset attribute value.
  double             mScaleFactor;          //!< scale_factor attribute value.
  std::string        mParameterName;        //!< NetCDF variable long_name or name.
  std::string        mParameterStandardName;//!< CF standard_name of the variable.
  T::ParamLevelId    mParameterLevelId;     //!< FMI level type identifier.
  T::ParamLevel      mParameterLevel;       //!< Level value (pressure, height, etc.).
  std::string        mParameterUnits;       //!< CF units attribute string.
  T::ForecastType    mForecastType;         //!< Forecast type code.
  T::ForecastNumber  mForecastNumber;       //!< Ensemble member or perturbation number.
  time_t             mForecastTimeT;        //!< Forecast valid time as a Unix timestamp.
  T::ParamValue      mMissingValue;         //!< Fill/missing value used for undefined grid points.
  T::GridProjection  mProjectionId;         //!< Grid projection type.
  int                mGeometryId;           //!< FMI geometry identifier.
};

typedef std::vector<MessageInfo> MessageInfoVec;

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
                        Message(GRID::GridFile *gridFile,NetCdfFile *netCdfFile,T::MessageIndex messageIndex,NetCDF::MessageInfo& messageInfo);
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



typedef Message* MessagePtr;                   //!< Non-owning pointer to a NetCDF Message.
typedef std::vector<MessagePtr> MessagePtr_vec; //!< Vector of non-owning NetCDF Message pointers.


}  // namespace NetCDF
}  // namespace SmartMet


