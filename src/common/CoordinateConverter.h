#pragma once

#include "Typedefs.h"
#include "AutoThreadLock.h"
#include <ogr_spatialref.h>
#include <macgyver/Exception.h>

namespace SmartMet
{


class CoordinateConverter
{
  public:
    CoordinateConverter()
    {
      transformation = nullptr;
      sr1 = nullptr;
      sr2 = nullptr;
    }

    CoordinateConverter(const CoordinateConverter& rec)
    {
      sr1 = rec.sr1->Clone();
      sr2 = rec.sr2->Clone();
      transformation = OGRCreateCoordinateTransformation(sr1,sr2);
    }

    CoordinateConverter(const OGRSpatialReference *sr_from,const OGRSpatialReference *sr_to)
    {
      sr1 = sr_from->Clone();
      sr2 = sr_to->Clone();
      transformation = OGRCreateCoordinateTransformation(sr1,sr2);
    }

    ~CoordinateConverter()
    {
      if (transformation != nullptr)
        OCTDestroyCoordinateTransformation(transformation);

      if (sr1 != nullptr)
        OGRSpatialReference::DestroySpatialReference(sr1);

      if (sr2 != nullptr)
        OGRSpatialReference::DestroySpatialReference(sr2);
    }

    bool convert(int nCount,double *x,double *y)
    {
      AutoThreadLock lock(&threadLock);
      if (transformation->Transform(nCount,x,y))
        return true;

      return false;
    }

  protected:

    OGRCoordinateTransformation *transformation;
    OGRSpatialReference *sr1;
    OGRSpatialReference *sr2;
    ThreadLock threadLock;
};


}

