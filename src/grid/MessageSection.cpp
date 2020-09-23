#include "MessageSection.h"
#include <macgyver/Exception.h>


namespace SmartMet
{
namespace GRID
{


/*! \brief The constructor of the class. */

MessageSection::MessageSection()
{
}





/*! \brief The copy constructor of the class. */

MessageSection::MessageSection(const MessageSection& other)
{
}





/*! \brief The destructor of the class. */

MessageSection::~MessageSection()
{
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current section.
*/

void MessageSection::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
}





/*! \brief The method returns the section start position in the grib file.

        \return  The section's start position in the grib file.
*/

T::FilePosition MessageSection::getFilePosition() const
{
  throw Fmi::Exception(BCP,"Not implemented!");
}





/*! \brief The method returns the length of the section (in the grib file).

         \return  The length of the section expressed in bytes.
*/

std::uint32_t MessageSection::getSectionLength() const
{
  throw Fmi::Exception(BCP,"Not implemented!");
}





/*! \brief The method returns the section number. */

std::uint8_t MessageSection::getSectionNumber() const
{
  throw Fmi::Exception(BCP,"Not implemented!");
}





/*! \brief The method returns the name of the section. */

std::string MessageSection::getSectionName() const
{
  throw Fmi::Exception(BCP,"Not implemented!");
}





/*! \brief The method prints the content of the current object into the given stream.

      \param ostream      The output stream.
      \param level        The print level (used when printing multi-level structures).
      \param optionFlags  The printing options expressed in flag-bits.
*/

void MessageSection::print(std::ostream& stream,uint level,uint optionFlags) const
{
  throw Fmi::Exception(BCP,"Not implemented!");
}



}  // namespace GRID
}  // namespace SmartMet

