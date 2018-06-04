#pragma once

#include "Exception.h"

namespace SmartMet
{
namespace T
{


struct Dimensions
{
  Dimensions(const unsigned int nx, const unsigned int ny)
  {
    mNx = nx;
    mNy = ny;
  }

  unsigned int nx() const { return mNx; }
  unsigned int ny() const { return mNy; }

  private:
    unsigned int mNx;
    unsigned int mNy;
};

}
}  // namespace SmartMet
