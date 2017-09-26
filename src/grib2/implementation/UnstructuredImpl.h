#pragma once

#include "grib2/definition/Unstructured.h"


namespace SmartMet
{
namespace GRIB2
{

class UnstructuredImpl : public Unstructured
{
  public:

                      UnstructuredImpl();
                      UnstructuredImpl(const UnstructuredImpl& other);
    virtual           ~UnstructuredImpl();

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions_opt getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}


