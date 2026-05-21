#pragma once

#include "Typedefs.h"
#include "../common/AttributeList.h"


namespace SmartMet
{
namespace GRID
{

// ====================================================================================
/*! \brief Abstract base class for all message sections in GRIB1, GRIB2, and other grid files.
 *
 *  Defines the common interface that every section class (Indicator, Product, Grid, …) must
 *  implement.  Concrete subclasses live in src/grib1/ and src/grib2/. */
// ====================================================================================

class MessageSection
{
  public:
                            MessageSection();
    virtual                 ~MessageSection();

    /*! \brief Populate an AttributeList with all section fields as key/value pairs.
     *  \param[in]  prefix         String prepended to every attribute key.
     *  \param[out] attributeList  Receives the section attributes. */
    virtual void            getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const;

    /*! \brief Return the byte offset of this section within the enclosing file.
     *  \return File byte position. */
    virtual T::FilePosition getFilePosition() const;

    /*! \brief Return the total byte length of this section.
     *  \return Section length in bytes. */
    virtual std::uint32_t   getSectionLength() const;

    /*! \brief Return a human-readable name for this section (e.g. "Grid Definition Section").
     *  \return Section name string. */
    virtual std::string     getSectionName() const;

    /*! \brief Return the GRIB section number (0–8 for GRIB2).
     *  \return Section number byte. */
    virtual std::uint8_t    getSectionNumber() const;

    /*! \brief Print the section contents to a stream (for debugging).
     *  \param[in] stream      Output stream.
     *  \param[in] level       Indentation level.
     *  \param[in] optionFlags PrintFlag bit mask. */
    virtual void            print(std::ostream& stream,uint level,uint optionFlags) const;
};


}  // namespace GRID
}  // namespace SmartMet

