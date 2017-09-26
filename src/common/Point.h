#pragma once


namespace SmartMet
{
namespace T
{


struct Point
{
  Point(const int x, const int y)
  {
    mX = x;
    mY = y;
  }

  int x() const { return mX; }
  int y() const { return mY; }

  private:
    int mX;
    int mY;
};

}
}  // namespace SmartMet
