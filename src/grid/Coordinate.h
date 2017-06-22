#pragma once

#include <vector>

namespace SmartMet
{
namespace T
{

class Coordinate
{
  public:
    Coordinate(double X, double Y) : mX(X), mY(Y){};

    double x() const { return mX; }
    double y() const { return mY; }

  private:
    double mX;
    double mY;
};

typedef std::vector<T::Coordinate> Coordinate_vec;

}
}  // namespace SmartMet

