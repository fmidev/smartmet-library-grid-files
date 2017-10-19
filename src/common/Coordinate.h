#pragma once

#include <vector>

namespace SmartMet
{
namespace T
{

class Coordinate
{
  public:

    Coordinate() : mX(0), mY(0) {};
    Coordinate(const Coordinate& coordinate) {mX = coordinate.mX; mY = coordinate.mY;}
    Coordinate(double x, double y) : mX(x), mY(y) {};

    inline double x() const { return mX; }
    inline double y() const { return mY; }
    inline void set(double x, double y) {mX = x;  mY = y;}

  private:

    double mX;
    double mY;
};

typedef std::vector<T::Coordinate> Coordinate_vec;

}
}  // namespace SmartMet

