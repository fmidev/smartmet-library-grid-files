#pragma once

#include <memory>
#include <vector>

namespace SmartMet
{
namespace T
{

class Coordinate
{
  public:

    Coordinate() : mX(0), mY(0) {};
    //Coordinate(const Coordinate& coordinate) {mX = coordinate.mX; mY = coordinate.mY;}
    Coordinate(double x, double y) : mX(x), mY(y) {};
    Coordinate(int x, int y) : mX(static_cast<double>(x)), mY(static_cast<double>(y)) {};
    Coordinate(unsigned int x, unsigned int y) : mX(static_cast<double>(x)), mY(static_cast<double>(y)) {};

    inline double x() const { return mX; }
    inline double y() const { return mY; }
    inline void set(double x, double y) {mX = x;  mY = y;}

  private:

    double mX;
    double mY;
};

typedef std::vector<T::Coordinate> Coordinate_vec;
typedef std::shared_ptr<std::vector<T::Coordinate>> Coordinate_svec;
typedef std::vector<Coordinate_vec> AreaCoordinates;
typedef std::vector<std::vector<T::Coordinate>> Polygon_vec;


}
}  // namespace SmartMet

