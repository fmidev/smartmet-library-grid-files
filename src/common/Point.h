#pragma once


namespace SmartMet
{
namespace T
{


/*! \brief Integer 2-D grid-index point (column, row). */
struct Point
{
  /*! \brief Construct from integer grid indices.
   *  \param[in] x  Column index.
   *  \param[in] y  Row index. */
  Point(const int x, const int y)
  {
    mX = x;
    mY = y;
  }

  /*! \brief Return the column index. */
  int x() const { return mX; }
  /*! \brief Return the row index. */
  int y() const { return mY; }

  private:
    int mX; //!< Column index
    int mY; //!< Row index
};

}
}  // namespace SmartMet
