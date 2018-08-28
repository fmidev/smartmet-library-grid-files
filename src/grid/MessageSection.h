#pragma once

#include "Typedefs.h"
#include "../common/AttributeList.h"


namespace SmartMet
{
namespace GRID
{

// ====================================================================================
/*!
  \brief This class is a parent class for all message sections in different grid files.
  It defines the basic methods that all its child classes should implement.
*/
// ====================================================================================

class MessageSection
{
  public:
                            MessageSection();
                            MessageSection(const MessageSection& other);
    virtual                 ~MessageSection();

    // ### Common methods for all message sections

    virtual void            getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    virtual T::FilePosition getFilePosition() const;
    virtual std::uint32_t   getSectionLength() const;
    virtual std::string     getSectionName() const;
    virtual std::uint8_t    getSectionNumber() const;
    virtual void            print(std::ostream& stream,uint level,uint optionFlags) const;
};


}  // namespace GRID
}  // namespace SmartMet

