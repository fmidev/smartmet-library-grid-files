#pragma once

#include "Typedefs.h"

namespace SmartMet
{
namespace T
{


// ====================================================================================
/*! \brief A single grid value together with its (x, y) coordinates.
 *
 *  Holds either a numeric value, a string representation, or both. */
// ====================================================================================

class GridValue
{
  public:
                  GridValue();
                  //GridValue(const GridValue& gridValue);
                  /*! \brief Construct with numeric value only.
                   *  \param[in] x      Grid x-coordinate.
                   *  \param[in] y      Grid y-coordinate.
                   *  \param[in] value  Parameter value. */
                  GridValue(double x,double y, T::ParamValue value);
                  /*! \brief Construct with string value only.
                   *  \param[in] x            Grid x-coordinate.
                   *  \param[in] y            Grid y-coordinate.
                   *  \param[in] valueString  String representation of the value. */
                  GridValue(double x,double y, const char *valueString);
                  //! \overload
                  GridValue(double x,double y, std::string& valueString);
                  /*! \brief Construct with both numeric and string value.
                   *  \param[in] x            Grid x-coordinate.
                   *  \param[in] y            Grid y-coordinate.
                   *  \param[in] value        Numeric parameter value.
                   *  \param[in] valueString  String representation. */
                  GridValue(double x,double y, T::ParamValue value, std::string& valueString);
                  //! \overload
                  GridValue(double x,double y, T::ParamValue value, const char *valueString);
    virtual       ~GridValue();

    /*! \brief Print the grid value to a stream (for debugging).
     *  \param[in] stream      Output stream.
     *  \param[in] level       Indentation level.
     *  \param[in] optionFlags Print option flags. */
    void          print(std::ostream& stream,uint level,uint optionFlags);

    double        mX;           //!< Grid x-coordinate or longitude
    double        mY;           //!< Grid y-coordinate or latitude
    T::ParamValue mValue;       //!< Numeric parameter value (ParamValueMissing if absent)
    std::string   mValueString; //!< Optional string representation of the value
};



}
}  // namespace SmartMet
