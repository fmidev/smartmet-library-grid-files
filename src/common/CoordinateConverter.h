#pragma once

#include "Typedefs.h"
#include "AutoThreadLock.h"
#include <ogr_spatialref.h>
#include <macgyver/Exception.h>
#include <memory>

namespace SmartMet
{

#define CONVERTER_COUNT 10  //!< Number of parallel OGR transformation slots

// ====================================================================================
/*! \brief Thread-safe OGR coordinate transformation wrapper with a fixed-size slot pool.
 *
 *  Maintains `CONVERTER_COUNT` `OGRCoordinateTransformation` instances that are
 *  checked out round-robin and used concurrently without locking via per-slot
 *  in-progress flags and a `ThreadLock` per slot.  This avoids the serialisation
 *  bottleneck that would result from a single transformation object. */
// ====================================================================================

class CoordinateConverter
{
  public:
    /*! \brief Construct an empty converter (no transformations until copy or OGR constructor). */
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

    /*! \brief Copy constructor — clones spatial references and creates fresh transformations. */
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
      mPinFrom = rec.mPinFrom;
      mPinTo = rec.mPinTo;
    }

    /*! \brief Construct from two OGR spatial references.
     *  \param[in] sr_from  Source spatial reference (cloned).
     *  \param[in] sr_to    Target spatial reference (cloned). */
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

    /*! \brief Pin the original spatial references for the lifetime of this converter.
     *
     *  The converter-cache key is derived from the addresses of the source and target
     *  spatial references. Once the original shared_ptr owners are released (e.g. the
     *  spatialReferenceCache evicts them), the freed address can be reused by a
     *  completely different CRS, after which the cache would return this converter for
     *  the wrong projection. Holding the original shared_ptrs here keeps those addresses
     *  reserved as long as the converter stays cached, so the key remains unique.
     *  The transformations themselves use the internal clones (sr1/sr2); these pinned
     *  references are kept solely to guarantee key stability. */
    inline void keepAlive(const std::shared_ptr<OGRSpatialReference>& sr_from,
                          const std::shared_ptr<OGRSpatialReference>& sr_to)
    {
      mPinFrom = sr_from;
      mPinTo = sr_to;
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


    /*! \brief Acquire a free transformation slot index (spins until one is available).
     *  \return Slot index in [0, CONVERTER_COUNT). */
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


    /*! \brief Transform \p nCount coordinate pairs in place.
     *  \param[in]     nCount  Number of coordinate pairs.
     *  \param[in,out] x       X values (overwritten with transformed values).
     *  \param[in,out] y       Y values (overwritten with transformed values).
     *  \return True on success. */
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

    OGRCoordinateTransformation *transformation[CONVERTER_COUNT]; //!< OGR transformation objects per slot
    bool tranformationInProgress[CONVERTER_COUNT];                //!< True while slot is in use
    OGRSpatialReference *sr1;                                     //!< Source spatial reference (owned)
    OGRSpatialReference *sr2;                                     //!< Target spatial reference (owned)
    ThreadLock threadLock[CONVERTER_COUNT];                       //!< Per-slot mutex
    timespec r1, r2;                                              //!< nanosleep spin interval
    std::shared_ptr<OGRSpatialReference> mPinFrom;                //!< Pins source CRS address while cached
    std::shared_ptr<OGRSpatialReference> mPinTo;                  //!< Pins target CRS address while cached
};


}

