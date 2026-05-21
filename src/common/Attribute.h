#pragma once

#include <string>



namespace SmartMet
{
namespace T
{



// ====================================================================================
/*! \brief Simple name/value string pair used in AttributeList and diagnostic output. */
// ====================================================================================

class Attribute
{
  public:
    /*! \brief Construct an empty attribute. */
                    Attribute();
    /*! \brief Copy constructor. */
                    Attribute(const Attribute& attribute);

    /*! \brief Construct with explicit name and value.
     *  \param[in] name   Attribute name.
     *  \param[in] value  Attribute value. */
                    Attribute(const std::string& name,const std::string& value);
     virtual        ~Attribute();

     /*! \brief Compute a hash of name and value.
      *  \return Combined hash value. */
     std::size_t    getHash();

     /*! \brief Assignment operator. */
     Attribute&     operator=(const Attribute& attribute);

     /*! \brief Return a heap-allocated copy of this attribute.
      *  \return Newly allocated Attribute; caller owns the memory. */
     Attribute*     duplicate();

     /*! \brief Print the attribute to a stream.
      *  \param[in] stream      Output stream.
      *  \param[in] level       Indentation level.
      *  \param[in] optionFlags PrintFlag bit mask. */
     void           print(std::ostream& stream,uint level,uint optionFlags);

     std::string    mName;  //!< Attribute name
     std::string    mValue; //!< Attribute value (always stored as a string)
};


typedef Attribute* Attribute_ptr;


}
}
