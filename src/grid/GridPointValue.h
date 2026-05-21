#pragma once

#include "Typedefs.h"
#include <macgyver/Exception.h>

namespace SmartMet
{
namespace T
{

// ====================================================================================
/*! \brief A single grid point value with its spatiotemporal coordinates.
 *
 *  Carries a parameter value together with the file/message origin, spatial
 *  position (x, y), vertical level, and valid time.  Used for time-series
 *  delivery and multi-time value collections. */
// ====================================================================================

class GridPointValue
{
  public:

    /*! \brief Ordering key used when sorting or searching GridPointValue collections. */
    enum class ComparisonMethod
    {
      none                    = 0,  //!< No ordering
      time_x_y_level_value    = 1,  //!< Sort by: time, x, y, level, value
      x_y_level_time_value    = 2,  //!< Sort by: x, y, level, time, value
      y_x_level_time_value    = 3,  //!< Sort by: y, x, level, time, value
      value_x_y_level_time    = 4,  //!< Sort by: value, x, y, level, time
      file_message_x_y_level  = 5,  //!< Sort by: file, message, x, y, level, value
    };

  public:
                    GridPointValue();
                    /*! \brief Copy constructor. */
                    GridPointValue(const GridPointValue& gridPointValue);
                    /*! \brief Construct with all fields.
                     *  \param[in] fileId        Source file identifier.
                     *  \param[in] messageIndex  Message index within the file.
                     *  \param[in] x             Grid x-coordinate.
                     *  \param[in] y             Grid y-coordinate.
                     *  \param[in] level         Vertical level.
                     *  \param[in] valueTime     Valid time of the value.
                     *  \param[in] value         Parameter value. */
                    GridPointValue(T::FileId fileId,T::MessageIndex messageIndex,double x,double y,T::ParamLevel level,time_t valueTime,T::ParamValue value);
    virtual         ~GridPointValue();

    /*! \brief Assignment operator. */
    GridPointValue& operator=(const GridPointValue& gridPointValue);

    /*! \brief Compare this object against another using the specified ordering.
     *  \param[in] comparisonMethod  Field ordering to use.
     *  \param[in] gridPointValue   Object to compare against.
     *  \return Negative, zero, or positive per standard comparator convention. */
    int             compare(ComparisonMethod comparisonMethod,GridPointValue *gridPointValue);

    /*! \brief Return a heap-allocated copy of this object.
     *  \return Pointer to the new copy; caller owns the memory. */
    GridPointValue* duplicate();

    /*! \brief Print the object to a stream (for debugging).
     *  \param[in] stream      Output stream.
     *  \param[in] level       Indentation level.
     *  \param[in] optionFlags Print option flags. */
    virtual void    print(std::ostream& stream,uint level,uint optionFlags) const;

    /*! \brief The grid file identifier. */
    uint            mFileId;

    /*! \brief The index of the message in the grid file. The first index is 0.*/
    uint            mMessageIndex;

    /*! \brief The valid time of the value. */
    time_t          mTime;

    /*! \brief The grid value. */
    T::ParamValue   mValue;

    /*! \brief The grid x-coordinate or position. */
    double          mX;

    /*! \brief The grid y-coordinate or position. */
    double          mY;

    T::ParamLevel   mLevel;  //!< Vertical level identifier
};


typedef std::vector<GridPointValue> GridPointValue_vec;
typedef GridPointValue* GridPointValuePtr;


}
}  // namespace SmartMet
