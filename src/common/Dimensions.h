#pragma once

#include "Typedefs.h"
#include <macgyver/Exception.h>

namespace SmartMet
{
namespace T
{


class Dimensions
{
  public:
                Dimensions();
                //Dimensions(const Dimensions& dimensions);
                Dimensions(uint nx);
                Dimensions(uint nx,uint ny);
                Dimensions(uint nx,uint ny,uint nz);
    virtual     ~Dimensions();

    uint        nx() const;
    uint        ny() const;
    uint        nz() const;
    uint        getDimensions() const;
    uint        getSize(uint dimension)  const;

    void        print(std::ostream& stream,uint level,uint optionFlags) const;

  private:

    uint        mDimensions;
    uint        mSizes[3];
};

}
}  // namespace SmartMet
