#pragma once

#include <memory>
#include <vector>

namespace SmartMet
{
namespace T
{

// ====================================================================================
/*! \brief Lightweight 2-D coordinate pair (x, y) stored as double-precision floats.
 *
 *  Used throughout the grid subsystem to represent geographic (lon/lat), projected
 *  (metres), or grid-index coordinates depending on context. */
// ====================================================================================

class Coordinate
{
  public:

    /*! \brief Construct the origin (0, 0). */
    Coordinate() : mX(0), mY(0) {};
    //Coordinate(const Coordinate& coordinate) {mX = coordinate.mX; mY = coordinate.mY;}

    /*! \brief Construct from double-precision coordinates.
     *  \param[in] x  Horizontal component.
     *  \param[in] y  Vertical component. */
    Coordinate(double x, double y) : mX(x), mY(y) {};

    /*! \brief Construct from integer coordinates (widened to double).
     *  \param[in] x  Horizontal component.
     *  \param[in] y  Vertical component. */
    Coordinate(int x, int y) : mX(static_cast<double>(x)), mY(static_cast<double>(y)) {};

    //! \overload
    Coordinate(unsigned int x, unsigned int y) : mX(static_cast<double>(x)), mY(static_cast<double>(y)) {};

    /*! \brief Return the horizontal component. */
    inline double x() const { return mX; }
    /*! \brief Return the vertical component. */
    inline double y() const { return mY; }

    /*! \brief Set both components.
     *  \param[in] x  New horizontal value.
     *  \param[in] y  New vertical value. */
    inline void set(double x, double y) {mX = x;  mY = y;}

  private:

    double mX; //!< Horizontal coordinate
    double mY; //!< Vertical coordinate
};

typedef std::vector<T::Coordinate> Coordinate_vec;                           //!< Ordered list of coordinates
typedef std::shared_ptr<std::vector<T::Coordinate>> Coordinate_svec;         //!< Shared coordinate list
typedef std::vector<Coordinate_vec> AreaCoordinates;                         //!< Multi-ring polygon as lists of rings
typedef std::vector<std::vector<T::Coordinate>> Polygon_vec;                 //!< List of closed polygon rings


}
}  // namespace SmartMet

