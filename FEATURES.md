# smartmet-library-grid-files — Feature List

A structured inventory of capabilities provided by the grid-files library.
Use as a checklist when drafting release notes. When new functionality is
added, append the new entry under the matching section (and bump the
*Last updated* line at the bottom).

`smartmet-library-grid-files` is the foundation driver layer in the SmartMet
grid stack. It opens, parses, and serves data from grid files (GRIB1, GRIB2,
NetCDF, QueryData, GeoTIFF) through a single unified C++ API
(`SmartMet::GRID::Message`). Upper layers (grid-content, grid-engine,
plugins) talk only to this abstraction and remain format-agnostic.

---

## 1. Supported grid file formats

Auto-detected from file magic bytes when opened via `GridFile`:

- **GRIB edition 1** (`GRIB1::Message`)
- **GRIB edition 2** (`GRIB2::Message`)
- **NetCDF** classic and NetCDF-4 / HDF5 (`NetCDF::Message`)
- **QueryData** — FMI's native binary format (`QueryData::Message`)
- **GeoTIFF** (`GeoTiff::Message`)

## 2. Unified Message API

A single `GRID::Message` abstraction (~250 virtual methods) exposes the
following per-message capabilities regardless of underlying format:

- **Identity** — file ID, message index, file position, message size,
  producer ID, generation ID, forecast time (T-string + time_t), forecast
  type (deterministic / ensemble / control), forecast number.
- **Parameter identity** — GRIB parameter ID + name, FMI parameter ID + name
  + units, Newbase parameter ID + name, NetCDF variable name.
- **Vertical coordinate** — FMI level ID, level value, level units.
- **Grid geometry** — geometry ID, grid dimensions (cols × rows), cell average
  size, projection definition (WKT), scanning direction flags.
- **Raw access** — pointer to mapped memory, message size, GRIB section
  positions, GRIB version / centre / sub-centre / generating-process-ID /
  table-version.

## 3. Grid value retrieval

- Whole-grid read (`getGridValueVector`).
- Per-cell read (`getGridValueByPoint`) by grid index, latlon, or projection
  (original) coordinates.
- Polygon / rectangle reads.
- Reprojection to a different geometry via the grid engine (the library
  exposes the coordinate-transform plumbing).

## 4. Interpolation

- **Area interpolation methods** — Nearest, Linear, Min, Max, List, Logarithmic,
  external Lua functions; selectable per call via `T::AttributeList`.
- **Time interpolation methods** — Nearest, Linear, External-Lua.
- **Level interpolation methods** — Nearest, Linear, Logarithmic.
- **Modification operations** — apply per-call value transforms (unit
  conversion, additive offsets, scaling) via `modificationOperation` +
  `modificationParameters`.

## 5. Contouring & streamlines

Produced as binary geometries (typically WKB) directly from grid values:

- **Isobands** (filled contours) — by message, by target geometry, by
  arbitrary grid.
- **Isolines** (contour lines) — by message, by target geometry, by
  arbitrary grid.
- **Streamlines** — vector-field line tracing for U/V or speed/direction
  pairs, by message, by geometry, or by arbitrary grid.
- All three honor the area-interpolation method and modification operations
  set in the attribute list.

## 6. Coordinate & projection support

- **Per-cell latlon coordinate vectors** — `getGridLatLonCoordinates` /
  `…ByGeometryId`.
- **Per-cell projected coordinate vectors** — `getGridOriginalCoordinates` /
  `…ByGeometryId`.
- **Point transformations** — latlon ↔ projected ↔ grid-index in both
  directions, batched (vector) or single-point.
- **Spatial reference deduplication** — equal `OGRSpatialReference` objects
  are shared by hash so identical projections cost one copy.
- **Coordinate-line lookup** — pre-computed lat/lon outline points for map
  overlays.
- **WKT export** for any geometry.

## 7. Memory-mapped file access

`MemoryMapper`:

- **Local files** — standard `mmap` of disk files.
- **Remote files** — lazy page-faulted loading via Linux `userfaultfd`
  - over **HTTP/HTTPS** with credentialed access
  - over **S3** with AWS credentials
- **Per-server credentials** — registered by host; multiple servers
  supported.
- **Prefetch** — read-ahead for sequential message scans.
- **Queue tuning** — configurable `userfaultfd` message queue depth.
- **Reader thread** — background page-fault servicing.

## 8. FMI identifier mapping system

A central registry (`Identification::gridDef`) translates between formats:

- **Parameter mapping** — GRIB ID ↔ FMI ID, Newbase ID ↔ FMI ID, NetCDF
  name ↔ FMI ID.
- **Level mapping** — GRIB1 / GRIB2 / Newbase level IDs ↔ FMI level IDs.
- **Geometry definitions** — FMI geometry catalogue with grid dimensions,
  projection, area, and matching rules per format.
- **Geometry groups** — group multiple geometry IDs into a single producer-
  level abstraction (e.g. time-varying resolution).
- **Forecast-type / aggregation / processing-type catalogues** — full FMI
  vocabulary.
- **Site-specific extensions** — drop CSV files into `cfg/ext/` to add or
  override entries without rebuilding the library.
- **Runtime configurable coordinate-cache sizes** via
  `smartmet.library.grid-files.cache.*` keys.

## 9. Auto-generated GRIB template support

- **GRIB1 grid definitions** — LatLon, Rotated LatLon, Mercator, Polar
  Stereographic, Lambert Conformal, plus stretched/rotated/Gaussian/
  spherical-harmonic variants (~25 templates).
- **GRIB2 grid definitions** — all of the above plus Transverse Mercator,
  Lambert Azimuthal Equal Area, Space View, Equatorial Azimuthal
  Equidistant, Hovmoller, Cross-section, Triangular, Unstructured,
  Irregular LatLon (~30 templates).
- **GRIB2 product templates** — deterministic, ensemble forecast,
  ensemble-derived, percentile, probability, time-interval aggregates,
  satellite, aerosol, atmospheric chemical, etc. (~70 templates).
- **GRIB2 data representations** — Simple packing, JPEG2000, PNG, complex,
  complex-difference, spectral, matrix, logarithmic, floating-point.
- **PHP-driven regeneration** — `make create_def` rebuilds the C++ classes
  from eccodes definition files.
- **Manual extension classes** in `*/implementation/` add logic on top of
  the auto-generated definitions.

## 10. Topography & maps

- **Land/sea mask** — per-point land detection from packed mask file.
- **Land-shading / sea-shading** — light and shadow intensities for hill-
  shading effects.
- **High-resolution and low-resolution** mask sets selectable from the
  config.

## 11. Caching

In-process LRU caches for hot data, sized at static-init time and runtime-
resizable via `setCacheSizes()` and the `cache.*` config keys:

- **`latlonCoordinateCache`** — full per-geometry lat/lon coordinate
  vectors (the dominant memory consumer).
- **`originalCoordinateCache`** — full per-geometry projected coordinate
  vectors.
- **`transformCache1`** — latlon → projected single-point transforms.
- **`transformCache2`** — projected → latlon single-point transforms.
- **`transformCache3`** — vector-of-points transforms.
- **`spatialReferenceCache`** — OGRSpatialReference objects deduplicated by
  geometry hash.
- All caches expose `CacheStats` counters for hit/miss monitoring.

## 12. Configuration

- **libconfig** format (`cfg/grid-files.conf`) with SmartMet extensions
  (`@include`, `@ifdef`, `$(VAR)`, `%(DIR)`).
- **CSV catalogues** for parameters, levels, geometries, forecast types,
  aggregations, processing types, mappings.
- **Site overrides** under `cfg/ext/`.

## 13. Utilities & common library

The `src/common/` module ships reusable building blocks used by the rest
of the SmartMet grid stack:

- **AttributeList** — typed key/value parameter passing for grid queries.
- **MemoryReader / MemoryWriter** — endian-aware binary I/O over mapped
  memory.
- **BitArrayReader / BitArrayWriter** — bit-level packing/unpacking for
  GRIB.
- **InterpolationFunctions** — reusable area/time/level interpolators.
- **CoordinateConversions** — GDAL/PROJ-backed projection transforms.
- **ImageFunctions / ImagePaint** — PNG / JPEG / OpenJPEG / WebP rendering
  utilities used by the grid-gui plugin.
- **GraphFunctions** — line/polygon plotting primitives.
- **HttpClient / HttpsClient / TcpClient** — networking for remote file
  access.
- **DataFetcher** — pluggable backends for filesystem, HTTP, S3.
- **ThreadLock / AutoReadLock / AutoWriteLock** — read/write locks.
- **ModificationLock** — config-file hot-reload guard.
- **ConfigurationFile** — libconfig wrapper with the SmartMet extensions.
- **Log / Session / RequestCounter** — operational instrumentation.

## 14. Build & integration

- **Library output**: `libsmartmet-grid-files.so`.
- **Build**: `make` (release) / `make debug`.
- **Regenerate auto-generated templates**: `make create_def` (needs eccodes
  definitions installed).
- **Install**: `make install` (default `PREFIX=/usr`).
- **RPM**: `make rpm`.
- **Doxygen HTML**: `make doc`.
- **CI**: CircleCI on RHEL 8 and RHEL 10 via `ci-build` + the
  `fmidev/smartmet-cibase-{8,10}` Docker images.
- **Public headers** installed under `/usr/include/smartmet/grid-files/`.

---

*Last updated: 2026-06-01.*
