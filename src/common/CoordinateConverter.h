#pragma once

#include "Typedefs.h"
#include "AutoThreadLock.h"
#include <ogr_spatialref.h>
#include <macgyver/Exception.h>

namespace SmartMet
{

#define CONVERTER_COUNT 10

class CoordinateConverter
{
  public:
    CoordinateConverter()
    {
      for (uint t=0; t<CONVERTER_COUNT; t++)
      {
        transformation[t] = nullptr;
        tranformationInProgress[t] = false;
      }

      sr1 = nullptr;
      sr2 = nullptr;

      r1.tv_sec = 0;
      r1.tv_nsec = 10;
    }

    CoordinateConverter(const CoordinateConverter& rec)
    {
      sr1 = rec.sr1->Clone();
      sr2 = rec.sr2->Clone();
      for (uint t=0; t<CONVERTER_COUNT; t++)
      {
        transformation[t] = OGRCreateCoordinateTransformation(sr1,sr2);
        tranformationInProgress[t] = false;
      }
      r1.tv_sec = 0;
      r1.tv_nsec = 10;
    }

    CoordinateConverter(const OGRSpatialReference *sr_from,const OGRSpatialReference *sr_to)
    {
      sr1 = sr_from->Clone();
      sr2 = sr_to->Clone();
      for (uint t=0; t<CONVERTER_COUNT; t++)
      {
        transformation[t] = OGRCreateCoordinateTransformation(sr1,sr2);
        tranformationInProgress[t] = false;
      }
      r1.tv_sec = 0;
      r1.tv_nsec = 10;
    }

    ~CoordinateConverter()
    {
      for (uint t=0; t<CONVERTER_COUNT; t++)
      {
        if (transformation[t])
          OCTDestroyCoordinateTransformation(transformation[t]);
      }

      if (sr1 != nullptr)
        OGRSpatialReference::DestroySpatialReference(sr1);

      if (sr2 != nullptr)
        OGRSpatialReference::DestroySpatialReference(sr2);
    }


    inline uint getTransform()
    {
      while (true)
      {
        for (uint t=0; t<CONVERTER_COUNT; t++)
        {
          if (!tranformationInProgress[t])
          {
            tranformationInProgress[t] = true;
            return t;
          }
        }
        nanosleep(&r1,&r2);
      }
    }


    inline bool convert(int nCount,double *x,double *y)
    {
      uint idx = getTransform();
      AutoThreadLock lock(&threadLock[idx]);
      if (transformation[idx]->Transform(nCount,x,y))
      {
        tranformationInProgress[idx] = false;
        return true;
      }

      tranformationInProgress[idx] = false;
      return false;
    }

  protected:

    OGRCoordinateTransformation *transformation[CONVERTER_COUNT];
    bool tranformationInProgress[CONVERTER_COUNT];
    OGRSpatialReference *sr1;
    OGRSpatialReference *sr2;
    ThreadLock threadLock[CONVERTER_COUNT];
    timespec r1, r2;
};


}

