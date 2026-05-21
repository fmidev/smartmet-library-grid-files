#pragma once

#include <memory>
#include <string>
#include <vector>



namespace SmartMet
{
namespace T
{



// ====================================================================================
/*! \brief Tree node for hierarchical diagnostic state reporting.
 *
 *  Each node has a name, an optional scalar value, and a list of child nodes.
 *  Used by components like `ValueCache::getStateAttributes()` to expose internal
 *  state as a structured attribute tree. */
// ====================================================================================

class AttributeNode
{
  public:
    /*! \brief Construct an unnamed, valueless root node. */
                    AttributeNode();
    /*! \brief Copy constructor (deep-copies the sub-attribute tree). */
                    AttributeNode(const AttributeNode& attributeNode);

    /*! \brief Construct a leaf node with a name and string value.
     *  \param[in] name   Node name.
     *  \param[in] value  Node value. */
                    AttributeNode(const char *name,std::string value);

    //! \overload
                    AttributeNode(const char *name,const char *value);

    /*! \brief Construct a named interior node without a value.
     *  \param[in] name  Node name. */
                    AttributeNode(const char *name);
     virtual        ~AttributeNode();

    /*! \brief Append a child node with the given name and no value.
     *  \param[in] name  Child node name.
     *  \return Shared pointer to the newly created child. */
     std::shared_ptr<AttributeNode> addAttribute(const char *name);

    /*! \brief Append a child node with a string value.
     *  \param[in] name   Child node name.
     *  \param[in] value  Child node value.
     *  \return Shared pointer to the new child. */
     std::shared_ptr<AttributeNode> addAttribute(const char *name,std::string value);

     //! \overload
     std::shared_ptr<AttributeNode> addAttribute(const char *name,const char *value);

    /*! \brief Append a child node with an integer value (converted to string).
     *  \param[in] name   Child node name.
     *  \param[in] value  Integer value.
     *  \return Shared pointer to the new child. */
     std::shared_ptr<AttributeNode> addAttribute(const char *name,int value);

    /*! \brief Print the node and its children to a stream.
     *  \param[in] stream      Output stream.
     *  \param[in] level       Indentation level.
     *  \param[in] optionFlags PrintFlag bit mask. */
     void           print(std::ostream& stream,uint level,uint optionFlags);

     std::string    mName;  //!< Node name
     std::string    mValue; //!< Node value (empty for interior nodes)

     std::vector<std::shared_ptr<AttributeNode>> mSubAttributes; //!< Child nodes
};



}
}
