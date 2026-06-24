# Migration plan: use gis-library `SpatialReference` / `CoordinateTransformation`

**Status:** proposed — NOT started. Too large to combine with unrelated changes; schedule
on its own.

**Goal:** replace grid-files' direct use of GDAL `OGRSpatialReference` /
`OGRCoordinateTransformation` (and the home-grown caching around them) with the
SmartMet `gis` library wrappers `Fmi::SpatialReference` and
`Fmi::CoordinateTransformation`.

## Why

The gis wrappers are content-addressed, which is the proper fix for the coordinate-converter
cache aliasing bug (see `src/common/CoordinateConversions.cpp`). That bug was hotfixed in
26.6.24-2 by pinning the source/target CRS shared_ptrs inside the cached converter
(`CoordinateConverter::keepAlive`), but the underlying design — a cache keyed on raw CRS
**pointer addresses** — remains.

- `Fmi::SpatialReference` — internally cached; exposes content-based `hashValue()` and
  `WKT()`; constructible from EPSG int, WKT/PROJ string, or an existing
  `OGRSpatialReference` / `std::shared_ptr<OGRSpatialReference>` ("for legacy code").
- `Fmi::CoordinateTransformation` — built from two `SpatialReference`s; internally uses
  `OGRCoordinateTransformationFactory::Create(source.projStr(), target.projStr())`, a
  **content-keyed, pooled** transformation cache, and computes its own `hashValue()` from
  the two CRS hashes.

Migrating lets us **delete**: the custom `CoordinateConverter` slot pool, `CoordinateConversions.cpp`,
the address-keyed `coordinateConverterCache`, the `keepAlive` pin, and both
`spatialReferenceCache`s (grib1 + grib2). The gis library's content caches replace all of it.

## Scope inventory (as of 26.6.24)

| Repo | OGR touch | Detail |
|------|-----------|--------|
| **grid-files** | ~57 files | Whole projection/transform stack lives here |
| **grid-content** | 1 site | `src/queryServer/implementation/ServiceImplementation.cpp:5430` — a local `OGRSpatialReference sr` parsing a user CRS string (`SetFromUserInput` / `exportToProj4`); also calls `newMessage->initSpatialReference()` |
| **grid-engine** | 0 | No direct OGR use; only consumes grid-files' API transitively |

Within grid-files:

- **47 procedural projection builders** — 29 `initSpatialReference()` in
  `src/grib2/implementation/*Impl.cpp` + 18 in `src/grib1/implementation/*Impl.cpp`. Each
  calls `SetGeogCS` / `SetTM` / `SetLCC` / `SetMercator2SP` / `SetStereographic` /
  `SetProjParm` / `SetAxisMappingStrategy` / `Validate`.
- **3 caches**: `coordinateConverterCache` (`src/common/CoordinateConversions.cpp`) + two
  `spatialReferenceCache` (`src/grib1/GridDefinition.cpp`, `src/grib2/GridDefinition.cpp`).
  grib1 and grib2 each have their own near-duplicate `GridDefinition`.
- **Public API surface** — `src/grid/Typedefs.h`:
  ```cpp
  typedef OGRSpatialReference                  SpatialRef;
  typedef std::shared_ptr<OGRSpatialReference> SpatialRef_sptr;
  ```
  `Message::getSpatialReference()` and both `GridDefinition::getSpatialReference()` return
  `T::SpatialRef_sptr`; `mSpatialReference` is a member of both GridDefinitions.
- Two ad-hoc transforms in `getGridMetricArea()` (grib1 + grib2) build EPSG:4326 ↔
  EPSG:3395 by hand with `OGRCreateCoordinateTransformation`.

## The two real friction points

1. **No procedural builder on `Fmi::SpatialReference`.** It constructs only from
   EPSG/WKT/string/existing-OGR — there is no `SetTM`/`SetGeogCS`. So the 47 builders are
   NOT rewritten into SpatialReference calls; keep building the raw `OGRSpatialReference`
   imperatively (all WGS84 / earth-shape logic stays put) and then **wrap** it:
   `Fmi::SpatialReference(builtRef)`. ~1–2 lines per site, not a rewrite.

2. **`SpatialReference` is non-default-constructible and non-assignable.** Today the code
   does `T::SpatialRef_sptr mSpatialReference;` (empty) then `mSpatialReference.reset(...)`.
   You cannot `reset()` or default-construct a `Fmi::SpatialReference`, so the member must
   become `std::optional<Fmi::SpatialReference>` (or `std::shared_ptr<Fmi::SpatialReference>`)
   and `getSpatialReference()`'s return type changes — **this is the public API change**
   that ripples to consumers. Blast radius is small: grid-engine doesn't use it, grid-content
   uses it in one place.

**Build dependency:** grid-files does NOT currently depend on the gis library
(`REQUIRES = geos gdal webp filesystem`). Migration adds a `grid-files → gis` dependency.
gis is a sibling level-2 lib that does not depend on grid-files, so it is only a build-order
tweak, but it is a real packaging change (spec `BuildRequires` / `Requires`).

## Recommended phasing

### Phase 1 — transformation layer only (high value, low risk, NO public API change)
Rewrite `src/common/CoordinateConversions.cpp` / `CoordinateConverter.h` to build a
`Fmi::CoordinateTransformation` from `Fmi::SpatialReference(sr_from)` / `(sr_to)` and call
`.transform(x, y)`. Keep `mSpatialReference` as `OGRSpatialReference` / `SpatialRef_sptr`
exactly as today and wrap at the 5 `convert(...)` call sites in `GridDefinition.cpp`. Delete
the slot pool, the address-keyed cache, and `keepAlive`. Fold in the two `getGridMetricArea()`
hand-built transforms (grib1 + grib2).

This is where the actual bug lives; ~3–5 files in one repo, zero downstream impact.
**Size: S–M.**

### Phase 2 — CRS storage + cache removal (optional, larger, public API change)
Change `mSpatialReference` to `std::optional<Fmi::SpatialReference>`, wrap the 47 builders'
output, and delete both `spatialReferenceCache`s (redundant once `SpatialReference`
self-caches by content). Update `getSpatialReference()` return type. Recompile grid-content
(1 trivial site) and verify grid-engine. Mechanical but spread across 47 files × 2 editions,
and ABI-affecting → needs a coordinated rebuild of grid-content + the grid engine/plugins.
**Size: L.**

### Phase 3 — grid-content / grid-engine cleanup
grid-content's single local becomes `Fmi::SpatialReference(crsStr)`; grid-engine needs only
a recompile against the new headers. **Size: XS.**

## Risks to verify before committing

- **Axis order** — every builder sets `OAMS_TRADITIONAL_GIS_ORDER`. Confirm the gis wrappers
  preserve lon/lat order (the `EPSGTreatsAsLatLong` / `isAxisSwapped` accessors suggest they
  manage this). Validate with a before/after coordinate diff on real tiles.
- **Custom CRSs** — builders produce `DATUM["UNKNOWN"]` references; verify `projStr()` is
  stable and distinct so factory cache keys do not collide (two UNKNOWN-datum projections
  differing only in parameters must hash differently).
- **Behavioral equivalence** — gis `transformGeometry` adds antimeridian handling; we only
  need plain `transform()`, so keep using that to avoid changing results.
- **Thread-safety** of the gis factories under grid-files' heavy concurrency (gis repo has
  TSAN test targets — run them).
- **grib1 + grib2 together** — do both editions or the bug is fixed in only half the paths.

## Bottom line

The clean root-cause fix is **Phase 1 alone**: contained, single-repo, no API ripple,
deletes more code than it adds, and gives content-keyed caching. Phases 2–3 are a worthwhile
consolidation (removes 47 duplicated builders' reliance on raw OGR and two redundant caches)
but are a larger, ABI-affecting sweep — schedule outside an RC crunch.
