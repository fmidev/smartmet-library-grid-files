#pragma once

#include "DataDefinition.h"
#include "../common/MemoryReader.h"

namespace SmartMet
{
namespace GRIB1
{


class SimplePacking : public DataDefinition
{
  public:
                  SimplePacking();
    virtual       ~SimplePacking();

    void          decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    PackingMethod getPackingMethod() const;
    bool          getValueByIndex(Message *message,uint index,T::ParamValue& value) const;
    void          print(std::ostream& stream,uint level,uint optionFlags) const;
};

}  // namespace GRIB1
}  // namespace SmartMet
