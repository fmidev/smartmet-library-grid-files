#pragma once

#include "../definition/Unstructured.h"


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

    GridDefinition*   createGridDefinition() const;

    T::Coordinate_vec getGridCoordinates() const;
    T::Dimensions     getGridDimensions() const;
    bool              getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    void              initSpatialReference();
    void              read(MemoryReader& memoryReader);
};

}
}


