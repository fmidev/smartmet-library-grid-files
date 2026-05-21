#pragma once

#include <vector>
#include "GridValue.h"


namespace SmartMet
{
namespace T
{


// ====================================================================================
/*! \brief A sequential list of GridValue objects with coordinate and statistics queries. */
// ====================================================================================

class GridValueList
{
  public:
                      GridValueList();
                      /*! \brief Copy constructor. */
                      GridValueList(const GridValueList& gridValueList);
     virtual          ~GridValueList();

     /*! \brief Assignment operator. */
     GridValueList&   operator=(const GridValueList& gridValueList);

     /*! \brief Append a grid value.
      *  \param[in] gridValue  Value to append. */
     void             addGridValue(GridValue& gridValue);

     /*! \brief Remove all entries. */
     void             clear();

     /*! \brief Compute the bounding box of all stored (x, y) coordinates.
      *  \param[out] minX  Minimum x.
      *  \param[out] minY  Minimum y.
      *  \param[out] maxX  Maximum x.
      *  \param[out] maxY  Maximum y. */
     void             getGridValueArea(double& minX,double& minY,double& maxX,double& maxY);

     /*! \brief Return a pointer to the entry at the given index.
      *  \param[in] index  Zero-based index.
      *  \return Pointer to the entry, or nullptr if out of range. */
     GridValue*       getGridValuePtrByIndex(uint index) const;

     /*! \brief Copy the entry at the given index into \p gridValue.
      *  \param[in]  index      Zero-based index.
      *  \param[out] gridValue  Receives the entry.
      *  \return True if the index was valid. */
     bool             getGridValueByIndex(uint index,GridValue& gridValue) const;

     /*! \brief Find the entry whose coordinates match (x, y).
      *  \param[in]  x          Grid x-coordinate.
      *  \param[in]  y          Grid y-coordinate.
      *  \param[out] gridValue  Receives the matching entry.
      *  \return True if a matching entry was found. */
     bool             getGridValueByCoordinates(double x,double y,GridValue& gridValue) const;

     /*! \brief Return the number of entries. */
     uint             getLength() const;

     /*! \brief Return the maximum parameter value in the list. */
     T::ParamValue    getMaxValue() const;

     /*! \brief Return the minimum parameter value in the list. */
     T::ParamValue    getMinValue() const;

     /*! \brief Return the arithmetic mean of all parameter values. */
     T::ParamValue    getAverageValue() const;

     /*! \brief Count entries whose value falls within [minValue, maxValue].
      *  \param[in] minValue  Lower bound.
      *  \param[in] maxValue  Upper bound.
      *  \return Number of matching entries. */
     uint             getNumOfValuesInValueRange(T::ParamValue minValue,T::ParamValue maxValue) const;

     /*! \brief Replace the entry at the given index.
      *  \param[in] index      Zero-based index.
      *  \param[in] gridValue  New value to store.
      *  \return True if the index was valid. */
     bool             setGridValueByIndex(uint index,GridValue& gridValue);

     /*! \brief Print the list to a stream (for debugging).
      *  \param[in] stream      Output stream.
      *  \param[in] level       Indentation level.
      *  \param[in] optionFlags Print option flags. */
     void             print(std::ostream& stream,uint level,uint optionFlags) const;

  protected:

     std::vector<GridValue>  mList; //!< Storage for grid values
};

}
}
