#pragma once

#include <string>
#include <unordered_map>
#include "ModificationLock.h"

namespace SmartMet
{

typedef char* pchar;                                         //!< Mutable C-string pointer
typedef pchar* StringArray;                                  //!< Array of C-string pointers
typedef std::unordered_map<std::string,uint> StringIndex;    //!< String → numeric id index

// ====================================================================================
/*! \brief Thread-safe string intern table.
 *
 *  Assigns each unique string a stable numeric identifier and stores one copy of the
 *  string data.  Callers use `create()` to obtain an id and `operator[]` to retrieve
 *  the string pointer.  Used to avoid repeated heap allocation of frequently repeated
 *  strings (parameter names, geometry tags, etc.).
 *
 *  A global instance `stringFactory` is defined at the end of this header. */
// ====================================================================================

class StringFactory
{
  public:
                  StringFactory();
                  ~StringFactory();

    /*! \brief Intern a string and return its numeric identifier.
     *  \param[in] str  C-string to intern.
     *  \return Stable numeric id (same string always yields the same id). */
    uint          create(const char *str);

    //! \overload
    uint          create(std::string str);

    /*! \brief Return the interned string for the given id.
     *  \param[in] index  Numeric id returned by create().
     *  \return Pointer to the interned string, or nullptr if out of range. */
    pchar         operator[](uint index);

  protected:

    StringArray   *stringTable;       //!< Paged array of C-string pointers
    StringIndex   stringIndex;        //!< Reverse index (string → id)
    uint          stringArraySize;    //!< Total allocated slots
    uint          stringArrayCount;   //!< Number of interned strings so far

    ModificationLock  modificationLock; //!< Guards concurrent create() calls
};


extern StringFactory stringFactory;

}
