#pragma once


namespace SmartMet
{
namespace GRID
{

/*! \brief Bit flags controlling what sections are included in Message::print() output. */
enum PrintFlag
{
  data        = 1 << 0,  //!< Include grid data values
  coordinates = 1 << 1,  //!< Include grid coordinate values
  bitmap      = 1 << 2,  //!< Include bitmap (missing-value mask)
  no_messages = 1 << 3   //!< Suppress per-message output
};

}
}
