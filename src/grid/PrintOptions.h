#pragma once


namespace SmartMet
{
namespace GRID
{
  enum PrintFlag
  {
    data        = 1 << 0,
    coordinates = 1 << 1,
    bitmap      = 1 << 2,
    no_messages = 1 << 3
  };

}
}
