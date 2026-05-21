#pragma once

#include <map>
#include <string>
#include <vector>
#include <ostream>

namespace SmartMet
{


typedef std::map<std::string,std::string> ParameterList; //!< XML element attribute map


// ====================================================================================
/*! \brief Lightweight DOM-style XML parser used for THREDDS and S3 directory listings.
 *
 *  Parses a byte buffer into a tree of XmlElement nodes without requiring an external
 *  XML library.  Each node holds its tag name, attribute map, text content, and a list
 *  of child elements. */
// ====================================================================================

class XmlElement
{
  public:

    /*! \brief Construct an empty root element. */
                  XmlElement();

    /*! \brief Parse \p data and build the element tree rooted at this object.
     *  \param[in] data  XML text buffer.
     *  \param[in] size  Size of \p data in bytes. */
                  XmlElement(const char *data,int size);
    virtual       ~XmlElement();

    /*! \brief Parse \p data into \p xmlRoot (static factory method).
     *  \param[in]  data     XML text buffer.
     *  \param[in]  size     Size of \p data in bytes.
     *  \param[out] xmlRoot  Receives the parsed element tree. */
    static void   parseXml(const char *data,int size,XmlElement& xmlRoot);

    /*! \brief Print the element tree to a stream.
     *  \param[in] stream      Output stream.
     *  \param[in] level       Indentation level.
     *  \param[in] optionFlags PrintFlag bit mask. */
    void          print(std::ostream& stream,uint level,uint optionFlags);

    int           filePosition;                  //!< Byte offset of this tag in the source buffer
    XmlElement    *parent;                        //!< Parent element (nullptr for the root)
    std::string   tag;                            //!< Element tag name
    ParameterList parameters;                     //!< Attribute name → value map
    std::string   value;                          //!< Text content of the element

    std::vector<XmlElement*> elementList;         //!< Owned child elements

  protected:

    static int    getTagNameAndType(const char *data,char *name,ParameterList& parameterList);
};


}
