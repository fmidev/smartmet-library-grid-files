#pragma once

#include "common/Exception.h"
#include "grid/Typedefs.h"

namespace SmartMet
{
namespace T
{

// ====================================================================================
/*!
  \brief This class can be used for delivering grid values over a time period.
*/
// ====================================================================================

class GridPointValue
{
  public:

    enum class ComparisonMethod
    {
      none                    = 0,    // No comparison
      time_x_y_level_value    = 1,    // Comparison order: time,x,y,level,value
      x_y_level_time_value    = 2,    // Comparison order: x,y,level,time,value
      y_x_level_time_value    = 3,    // Comparison order: y,x,level,time,value
      value_x_y_level_time    = 4,    // Comparison order: value,x,y,level,time
      file_message_x_y_level  = 5,    // Comparison order: file,message,x,y,level,value
    };

  public:
                    GridPointValue();
                    GridPointValue(const GridPointValue& gridPointValue);
                    GridPointValue(uint fileId,uint messageIndex,double x,double y,T::ParamLevel level,T::TimeString valueTime,T::ParamValue value);
    virtual         ~GridPointValue();

    void            operator=(GridPointValue& gridPointValue);
    int             compare(ComparisonMethod comparisonMethod,GridPointValue *gridPointValue);
    GridPointValue* duplicate();

    virtual void    print(std::ostream& stream,uint level,uint optionFlags) const;

    /*! \brief The grid file identifier. */
    uint            mFileId;

    /*! \brief The index of the message in the grid file. The first index is 0.*/
    uint            mMessageIndex;

    /*! \brief The time of the value. */
    T::TimeString   mTime;

    /*! \brief The grid value. */
    T::ParamValue   mValue;

    /*! \brief The grid x-coordinate or position. */
    double          mX;

    /*! \brief The grid y-coordinate or position. */
    double          mY;

    T::ParamLevel   mLevel;
};


typedef std::vector<GridPointValue> GridPointValue_vec;
typedef GridPointValue* GridPointValuePtr;


}
}  // namespace SmartMet
