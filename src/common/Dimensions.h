#pragma once

#include "Typedefs.h"
#include <macgyver/Exception.h>

namespace SmartMet
{
namespace T
{


// ====================================================================================
/*! \brief Grid dimension descriptor for 1-D, 2-D, or 3-D grids.
 *
 *  Stores up to three axis sizes (nx, ny, nz) and the number of active dimensions.
 *  Constructed with one, two, or three size arguments; unused dimensions default to 0. */
// ====================================================================================

class Dimensions
{
  public:
    /*! \brief Construct an empty (0-dimensional) descriptor. */
                Dimensions();
                //Dimensions(const Dimensions& dimensions);

    /*! \brief Construct a 1-D descriptor with \p nx elements.
     *  \param[in] nx  Number of elements along the first axis. */
                Dimensions(uint nx);

    /*! \brief Construct a 2-D descriptor.
     *  \param[in] nx  Width (columns).
     *  \param[in] ny  Height (rows). */
                Dimensions(uint nx,uint ny);

    /*! \brief Construct a 3-D descriptor.
     *  \param[in] nx  Width.
     *  \param[in] ny  Height.
     *  \param[in] nz  Depth. */
                Dimensions(uint nx,uint ny,uint nz);
    virtual     ~Dimensions();

    /*! \brief Return the width (first axis size). */
    uint        nx() const;
    /*! \brief Return the height (second axis size, or 0 for 1-D). */
    uint        ny() const;
    /*! \brief Return the depth (third axis size, or 0 for 1-D/2-D). */
    uint        nz() const;
    /*! \brief Return the number of active dimensions (1, 2, or 3). */
    uint        getDimensions() const;

    /*! \brief Return the size of a specific axis.
     *  \param[in] dimension  Zero-based axis index (0 = x, 1 = y, 2 = z).
     *  \return Axis size, or 0 if \p dimension is out of range. */
    uint        getSize(uint dimension)  const;

    /*! \brief Print the dimension values to a stream.
     *  \param[in] stream      Output stream.
     *  \param[in] level       Indentation level.
     *  \param[in] optionFlags PrintFlag bit mask. */
    void        print(std::ostream& stream,uint level,uint optionFlags) const;

  private:

    uint        mDimensions;  //!< Number of active axes (1–3)
    uint        mSizes[3];    //!< Axis sizes indexed [0]=x, [1]=y, [2]=z
};

}
}  // namespace SmartMet
