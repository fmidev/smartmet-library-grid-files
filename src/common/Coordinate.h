#pragma once

#include <vector>

namespace SmartMet
{
namespace T
{

class Coordinate
{
  public:
    Coordinate(double x, double y) : mX(x), mY(y) {};

    double x() const { return mX; }
    double y() const { return mY; }

    void set(double x, double y) {mX = x;  mY = y;}

  private:
    double mX;
    double mY;
};

typedef std::vector<T::Coordinate> Coordinate_vec;

}
}  // namespace SmartMet

