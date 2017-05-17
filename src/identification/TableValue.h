#pragma once

#include "grid/Typedefs.h"


namespace SmartMet
{
namespace Identification
{

// ====================================================================================
/*!
  \brief This class contains common table value definitions that are read from
  the 'tables.csv' file.
*/
// ====================================================================================

class TableValue
{
  public:
                  TableValue();
                  TableValue(const TableValue& tableValue);
    virtual       ~TableValue();

    virtual void  print(std::ostream& stream,uint level,uint optionFlags) const;

    std::uint8_t  mGribVersion;
    std::uint8_t  mTableVersion;
    std::string   mTable;
    std::uint32_t mNumber;
    std::string   mName;
    std::string   mValue;
};


typedef std::vector<TableValue>  TableValue_vec;

}
}

