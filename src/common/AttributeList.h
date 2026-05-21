#pragma once

#include <macgyver/Exception.h>
#include "Attribute.h"

namespace SmartMet
{
namespace T
{

// ====================================================================================
/*! \brief Ordered collection of Attribute (name/value) pairs with optional
 *  case-insensitive name lookup.
 *
 *  Used throughout the grid subsystem to attach diagnostic or descriptive metadata
 *  to messages, sections, and grid objects. */
// ====================================================================================

class AttributeList
{
  public:
    /*! \brief Construct an empty list (case-sensitive by default). */
                    AttributeList();
    /*! \brief Deep-copy constructor. */
                    AttributeList(const AttributeList& attributeList);
    virtual         ~AttributeList();

    /*! \brief Deep-copy assignment operator. */
    AttributeList&  operator=(const AttributeList& attributeList);

    /*! \brief Append a pre-allocated Attribute (ownership transferred).
     *  \param[in] attribute  Attribute to append; must be heap-allocated. */
    void            addAttribute(Attribute *attribute);

    /*! \brief Append a new attribute from a C-string name and string value.
     *  \param[in] name   Attribute name.
     *  \param[in] value  Attribute value. */
    void            addAttribute(const char *name,std::string value);

    //! \overload
    void            addAttribute(const std::string& name,const std::string& value);

    /*! \brief Update an existing attribute in place, or add it if not found.
     *  \param[in] name   Attribute name to look up.
     *  \param[in] value  New value to assign. */
    void            setAttribute(const char *name,const std::string& value);

    //! \overload
    void            setAttribute(const std::string& name,const std::string& value);

    /*! \brief Control whether name lookups are case-sensitive.
     *  \param[in] caseSensitive  True for case-sensitive matching (default). */
    void            setCaseSensitive(bool caseSensitive);

    /*! \brief Remove all attributes from the list. */
    void            clear();

    /*! \brief Return the number of attributes.
     *  \return Attribute count. */
    unsigned int    getLength() const;

    /*! \brief Find an attribute by name.
     *  \param[in] name  Attribute name to search for.
     *  \return Pointer to the first matching Attribute, or nullptr. */
    Attribute*      getAttribute(const char *name) const;

    /*! \brief Find an attribute whose name ends with \p nameEnd.
     *  \param[in] nameEnd  Suffix to match.
     *  \return Pointer to the first matching Attribute, or nullptr. */
    Attribute*      getAttributeByNameEnd(const char *nameEnd) const;

    /*! \brief Return the attribute at the given zero-based index.
     *  \param[in] index  Zero-based position.
     *  \return Pointer to the Attribute, or nullptr if out of range. */
    Attribute*      getAttributeByIndex(unsigned int index) const;

    /*! \brief Return the name of the attribute at \p index.
     *  \param[in] index  Zero-based position.
     *  \return C-string name, or nullptr if out of range. */
    const char*     getAttributeNameByIndex(unsigned int index) const;

    /*! \brief Return the value of the first attribute matching \p name.
     *  \param[in] name  Attribute name.
     *  \return C-string value, or nullptr if not found. */
    const char*     getAttributeValue(const char *name) const;

    /*! \brief Collect all values for attributes whose name matches \p name.
     *  \param[in]  name    Attribute name to search for.
     *  \param[out] values  Receives all matching values.
     *  \return Number of values found. */
    size_t          getAttributeValues(const char *name,std::vector<std::string>& values) const;

    /*! \brief Return the value of the attribute at \p index.
     *  \param[in] index  Zero-based position.
     *  \return C-string value, or nullptr if out of range. */
    const char*     getAttributeValueByIndex(unsigned int index) const;

    /*! \brief Compute a combined hash of all attributes.
     *  \return Hash value. */
    std::size_t     getHash();

    /*! \brief Print all attributes to a stream.
     *  \param[in] stream      Output stream.
     *  \param[in] level       Indentation level.
     *  \param[in] optionFlags PrintFlag bit mask. */
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

 protected:

    std::vector<Attribute_ptr>  mAttributeVector; //!< Ordered list of owned Attribute pointers
    bool                        mCaseSensitive;   //!< True when name lookups are case-sensitive
};


}
}
