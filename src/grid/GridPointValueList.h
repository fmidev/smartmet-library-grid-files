#pragma once

#include "GridPointValue.h"


namespace SmartMet
{
namespace T
{


// ====================================================================================
/*! \brief A dynamic array of GridPointValue objects with query and statistics methods.
 *
 *  Supports sorted storage, spatial/temporal queries, and time-series interpolation. */
// ====================================================================================

class GridPointValueList
{
  public:
                          GridPointValueList();
                          /*! \brief Copy constructor (non-const). */
                          GridPointValueList(GridPointValueList& gridPointValueList);
                          //! \overload
                          GridPointValueList(const GridPointValueList& gridPointValueList);
     virtual              ~GridPointValueList();

     /*! \brief Assignment operator. */
     GridPointValueList&  operator=(GridPointValueList& gridPointValueList);
     //! \overload
     GridPointValueList&  operator=(const GridPointValueList& gridPointValueList);

     /*! \brief Append a GridPointValue; ownership follows mReleaseObjects setting.
      *  \param[in] gridPointValue  Pointer to the value to add. */
     void                 addGridPointValue(GridPointValue *gridPointValue);

     /*! \brief Remove all entries (and delete objects if mReleaseObjects is true). */
     void                 clear();

     /*! \brief Delete the entry at the given index.
      *  \param[in] index  Zero-based index.
      *  \return True if the index was valid and the entry was removed. */
     bool                 deleteGridPointValueByIndex(uint index);

     /*! \brief Binary-search for the entry whose sort key is closest to the given value.
      *  \param[in] comparisonMethod  Ordering to use.
      *  \param[in] gridPointValue   Reference value.
      *  \return Index of the closest entry, or -1 if the list is empty. */
     int                  getClosestIndex(GridPointValue::ComparisonMethod comparisonMethod,GridPointValue& gridPointValue);

     /*! \brief Compute the bounding box of all (x, y) coordinates in the list.
      *  \param[out] minX  Minimum x-coordinate.
      *  \param[out] minY  Minimum y-coordinate.
      *  \param[out] maxX  Maximum x-coordinate.
      *  \param[out] maxY  Maximum y-coordinate. */
     void                 getGridPointValueArea(double& minX,double& minY,double& maxX,double& maxY);

     /*! \brief Return the entry at the given index (with bounds check).
      *  \param[in] index  Zero-based index.
      *  \return Pointer to the entry, or nullptr if out of range. */
     GridPointValue*      getGridPointValueByIndex(uint index);

     /*! \brief Return the entry at the given index without bounds checking.
      *  \param[in] index  Zero-based index. */
     GridPointValue*      getGridPointValueByIndexNoCheck(uint index);

     /*! \brief Find the entry matching the given (x, y, level, time).
      *  \param[in] x      Grid x-coordinate.
      *  \param[in] y      Grid y-coordinate.
      *  \param[in] level  Vertical level.
      *  \param[in] time   Valid time.
      *  \return Pointer to the matching entry, or nullptr if not found. */
     GridPointValue*      getGridPointValueByPointAndTime(double x,double y,T::ParamLevel level,time_t time);

     /*! \brief Find the entry matching the given file, message, and grid point.
      *  \param[in] fileId        Source file identifier.
      *  \param[in] messageIndex  Message index within the file.
      *  \param[in] x             Grid x-coordinate.
      *  \param[in] y             Grid y-coordinate.
      *  \return Pointer to the matching entry, or nullptr if not found. */
     GridPointValue*      getGridPointValueByFileMessageAndPoint(T::FileId fileId,T::MessageIndex messageIndex,double x,double y);

     /*! \brief Find the entry for (x, y, level) with the largest time strictly before \p time.
      *  \param[in] x      Grid x-coordinate.
      *  \param[in] y      Grid y-coordinate.
      *  \param[in] level  Vertical level.
      *  \param[in] time   Reference time.
      *  \return Pointer to the entry, or nullptr if none exists. */
     GridPointValue*      getPreviousGridPointValueByPointAndTime(double x,double y,T::ParamLevel level,time_t time);

     /*! \brief Find the entry for (x, y, level) with the smallest time strictly after \p time.
      *  \param[in] x      Grid x-coordinate.
      *  \param[in] y      Grid y-coordinate.
      *  \param[in] level  Vertical level.
      *  \param[in] time   Reference time.
      *  \return Pointer to the entry, or nullptr if none exists. */
     GridPointValue*      getNextGridPointValueByPointAndTime(double x,double y,T::ParamLevel level,time_t time);

     /*! \brief Collect all entries for (x, y, level) across all times.
      *  \param[in]  x                    Grid x-coordinate.
      *  \param[in]  y                    Grid y-coordinate.
      *  \param[in]  level                Vertical level.
      *  \param[out] gridPointValueList   Receives matching entries. */
     void                 getGridPointValueListByPoint(double x,double y,T::ParamLevel level,GridPointValueList& gridPointValueList);

     /*! \brief Collect all entries within a bounding box.
      *  \param[in]  minX,minY,maxX,maxY  Bounding box coordinates.
      *  \param[in]  level                Vertical level filter.
      *  \param[out] gridPointValueList   Receives matching entries. */
     void                 getGridPointValueListByArea(double minX,double minY,double maxX,double maxY,T::ParamLevel level,GridPointValueList& gridPointValueList);

     /*! \brief Collect all entries with the given valid time.
      *  \param[in]  time                Valid time to match.
      *  \param[out] gridPointValueList  Receives matching entries. */
     void                 getGridPointValueListByTime(time_t time,GridPointValueList& gridPointValueList);

     /*! \brief Collect all entries whose valid time is within [startTime, endTime].
      *  \param[in]  startTime           Inclusive start of the time range.
      *  \param[in]  endTime             Inclusive end of the time range.
      *  \param[out] gridPointValueList  Receives matching entries. */
     void                 getGridPointValueListByTimeRange(time_t startTime,time_t endTime,GridPointValueList& gridPointValueList);

     /*! \brief Collect all entries whose value falls within [minValue, maxValue].
      *  \param[in]  minValue            Lower bound (inclusive).
      *  \param[in]  maxValue            Upper bound (inclusive).
      *  \param[out] gridPointValueList  Receives matching entries. */
     void                 getGridPointValueListByValueRange(T::ParamValue minValue,T::ParamValue maxValue,GridPointValueList& gridPointValueList);

     /*! \brief Collect values for a regular time-step sequence at a fixed point.
      *  \param[in]  x                  Grid x-coordinate.
      *  \param[in]  y                  Grid y-coordinate.
      *  \param[in]  level              Vertical level.
      *  \param[in]  startTime          First time step.
      *  \param[in]  numberOfSteps      Number of time steps.
      *  \param[in]  stepSizeInSeconds  Step interval in seconds.
      *  \param[out] gridPointValueList Receives the collected entries. */
     void                 getGridPointValueListByTimeSteps(double x,double y,T::ParamLevel level,time_t startTime,uint numberOfSteps,uint stepSizeInSeconds,GridPointValueList& gridPointValueList);

     /*! \brief Return the number of entries currently in the list. */
     uint                 getLength();

     /*! \brief Return true if the list will delete objects on removal. */
     bool                 getReleaseObjects();

     /*! \brief Pre-allocate capacity to at least \p newSize entries.
      *  \param[in] newSize  Desired minimum capacity. */
     void                 increaseSize(uint newSize);

     /*! \brief Set the comparison method used by sort() and getClosestIndex().
      *  \param[in] comparisonMethod  Desired ordering. */
     void                 setComparisonMethod(GridPointValue::ComparisonMethod comparisonMethod);

     /*! \brief Control whether the list deletes owned objects on clear() or removal.
      *  \param[in] releaseObjects  True to delete objects; false to leave memory management to the caller. */
     void                 setReleaseObjects(bool releaseObjects);

     /*! \brief Sort entries using the given comparison method.
      *  \param[in] comparisonMethod  Ordering to use. */
     void                 sort(GridPointValue::ComparisonMethod comparisonMethod);

     /*! \brief Return the maximum value across all entries. */
     T::ParamValue        getMaxValue();

     /*! \brief Return the maximum value among entries with the given valid time.
      *  \param[in] time  Valid time to filter by. */
     T::ParamValue        getMaxValueByTime(time_t time);

     /*! \brief Return the minimum value across all entries. */
     T::ParamValue        getMinValue();

     //! \overload
     T::ParamValue        getMinValueByTime(time_t time);

     /*! \brief Return the average value across all entries. */
     T::ParamValue        getAverageValue();

     //! \overload
     T::ParamValue        getAverageValueByTime(time_t time);

     /*! \brief Count entries whose value falls within [minValue, maxValue].
      *  \param[in] minValue  Lower bound.
      *  \param[in] maxValue  Upper bound.
      *  \return Number of matching entries. */
     uint                 getNumOfValuesInValueRange(T::ParamValue minValue,T::ParamValue maxValue);

     /*! \brief Linearly interpolate the value at (x, y, level) for the given time.
      *  \param[in] x      Grid x-coordinate.
      *  \param[in] y      Grid y-coordinate.
      *  \param[in] level  Vertical level.
      *  \param[in] time   Target interpolation time.
      *  \return Interpolated value, or ParamValueMissing if not possible. */
     T::ParamValue        getTimeInterpolatedValue(double x,double y,T::ParamLevel level,time_t time);

     /*! \brief Print the list contents to a stream (for debugging).
      *  \param[in] stream      Output stream.
      *  \param[in] level       Indentation level.
      *  \param[in] optionFlags Print option flags. */
     void                 print(std::ostream& stream,uint level,uint optionFlags);

  protected:

     GridPointValuePtr    *mArray;           //!< Dynamic pointer array of owned GridPointValue objects
     uint                 mSize;             //!< Allocated capacity of mArray
     uint                 mLength;           //!< Number of entries currently in use
     bool                 mReleaseObjects;   //!< If true, entries are deleted when removed

     GridPointValue::ComparisonMethod mComparisonMethod; //!< Current sort ordering
};



}
}
