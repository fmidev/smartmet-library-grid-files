# grid-files developer guide

This guide is for developers who change `smartmet-library-grid-files` or build on it.
It covers the internal architecture, the main code paths, and the conventions you need
before editing the code.

For the identifier and mapping concepts (FMI, GRIB, NetCDF and Newbase identifiers, and
the CSV mapping files), read [doc/grid-files.md](../doc/grid-files.md) first. This guide
assumes you know them and does not repeat them.

## Contents

1. [What the library does](#1-what-the-library-does)
2. [Building and testing](#2-building-and-testing)
3. [Source tree](#3-source-tree)
4. [Core object model](#4-core-object-model)
5. [Reading a file: the full path](#5-reading-a-file-the-full-path)
6. [Parameter identification (GridDef)](#6-parameter-identification-griddef)
7. [Decoding values](#7-decoding-values)
8. [Coordinates and projections](#8-coordinates-and-projections)
9. [Value queries, reprojection and contouring](#9-value-queries-reprojection-and-contouring)
10. [Memory mapping and remote files](#10-memory-mapping-and-remote-files)
11. [Process-wide singletons and caches](#11-process-wide-singletons-and-caches)
12. [Thread safety](#12-thread-safety)
13. [Generated GRIB template classes](#13-generated-grib-template-classes)
14. [Coding conventions](#14-coding-conventions)
15. [Common tasks](#15-common-tasks)
16. [Known pitfalls](#16-known-pitfalls)

---

## 1. What the library does

grid-files is the lowest layer of the SmartMet grid stack. It reads GRIB1, GRIB2,
NetCDF (classic), QueryData and GeoTIFF files and gives all of them the same interface:

* a **`GRID::GridFile`** is one file,
* a **`GRID::Message`** is one 2D field in that file (one parameter, level, time and
  ensemble member).

Code above this library only uses `GridFile` and `Message`. It never needs to know
the file format. The library also maps each message to FMI identifiers (parameter,
level and geometry), so the same quantity from different producers and formats gets the
same name.

It runs inside the SmartMet Server process, used by:

| Consumer | What it uses |
|----------|--------------|
| `grid-content` | Content/Data/Query servers. The Data Server owns the `GridFile` objects and answers value, contour and coordinate queries through `Message`. |
| `engines/grid` | Initialises the library: `gridDef.init()`, `memoryMapper`, `valueCache`. It also exposes cache statistics and mapping lookups. |
| Plugins: `wms`, `wfs`, `edr`, `download`, `cross_section`, `grid-gui`, `grid-admin`, `timeseries` (via engine) | Types (`T::*`), attribute lists, `GridDef` lookups, and sometimes `Message` directly. |
| `tools-grid` | Command-line tools that open files directly with `GridFile`. |

A change to a public header (anything under `src/`, since all of it is installed) can
break these downstream packages at the source or ABI level. See
[§15.5](#155-changing-a-public-header).

## 2. Building and testing

```bash
make                 # builds libsmartmet-grid-files.so (checks for unresolved symbols)
make test            # builds the library, then test/*Test.cpp against ../libsmartmet-grid-files.so
make install         # headers -> $(includedir)/smartmet/grid-files/<module>/, lib -> $(libdir)
make rpm             # smartmet-library-grid-files{,-devel}
make doc             # Doxygen HTML into doc/html (the headers carry Doxygen comments)
```

Build dependencies come from the spec file: newbase, spine, macgyver, trax, GDAL, GEOS,
Boost (iostreams, thread), libpng, libjpeg, openjpeg2, libaec, libcurl, libwebp, zlib.
`REQUIRES = geos gdal webp filesystem` resolves the pkg-config parts. Everything else
is linked through `LIBS`.

Things to know:

* **All `src/**/*.cpp` are compiled.** `SRCS` is a wildcard over `src/*/*.cpp`,
  `src/*/definition/*.cpp` and `src/*/implementation/*.cpp`. A new file in an existing
  module directory is picked up automatically. A **new module directory** has to be
  added in four places in the `Makefile`: `vpath %.cpp`, `vpath %.h`, `objdir`, and
  `install` (both the `mkdir` and the `cp` lines).
* **Unresolved-symbol check.** After linking, `ldd -r` must report no undefined
  symbols, or the `.so` is deleted. If you add a call into a new external library,
  add it to `LIBS` too (or to `REQUIRES`, if it has a known pkg-config module).
* **`make format` does nothing useful.** `.clang-format` has `DisableFormat: true`,
  and the target globs `grid-files/*.h`, which does not exist. Do not reformat files.
  The code has its own hand-aligned column style (see [§14](#14-coding-conventions)).
* **Tests.** `test/` holds standalone programs (plain `main`, not Boost.Test) that
  print `FAIL …` and return non-zero on failure. Tests that need real data read
  fixtures from `/usr/share/smartmet/test/data/grib/...` (package
  `smartmet-test-data`) and a grid-files configuration from
  `/usr/share/smartmet/test/grid/library/grid-files.conf` (from the grid engine test
  fixtures). If either is missing, they print `SKIP` and succeed. So a green
  `make test` on a machine without the fixtures proves very little. Most behaviour is
  exercised indirectly by the `engines/grid`, `grid-content` and plugin test suites.

## 3. Source tree

```
src/
  grid/            Format-neutral API: GridFile, Message, MessageProcessing, value types,
                   ValueCache, IndexCache, GaussianLatitudeCache, Typedefs
  common/          Infrastructure: MemoryReader/Writer, MemoryMapper (+ DataFetcher_*),
                   HTTP/S3 clients, bit readers, interpolation, coordinate conversion,
                   GraphFunctions (contouring, WKB), image functions, locks,
                   ConfigurationFile, AttributeList, StringFactory, Log/ShowFunction
  grib1/           GRIB edition 1: sections, packings, Properties
    definition/      GENERATED from eccodes .def files - do not edit
    implementation/  Hand-written *Impl subclasses of the generated classes
  grib2/           GRIB edition 2: sections 0-7, Properties
    definition/      GENERATED (grid templates 3.x, product 4.x, representation 5.x, data 7.x)
    implementation/  Hand-written *Impl subclasses (projections, packings)
  identification/  GridDef + the *Def record types loaded from cfg/*.csv
  netcdf/          NetCdfFile (classic CDF-1/CDF-2 parser) + NetCDF::Message
  querydata/       QueryDataFile (wraps newbase NFmiQueryData) + QueryData::Message
  geotiff/         GeoTiffFile + GeoTiff::Message
  map/             Topography: land/sea mask and shading images
cfg/               Default configuration and mapping CSVs (not installed by the RPM)
php/               Code generators for definition/ classes and config files
doc/               Concept documentation (identifiers and mappings)
docs/              Developer documentation (this file, migration notes)
test/              Standalone regression tests
```

Namespaces follow the directories: `SmartMet::GRID`, `SmartMet::GRIB1`,
`SmartMet::GRIB2`, `SmartMet::NetCDF`, `SmartMet::QueryData`, `SmartMet::GeoTiff`,
`SmartMet::Identification`, and `SmartMet::T` for the shared types in
`grid/Typedefs.h` and `common/`.

## 4. Core object model

```
GRID::GridFile                          one file (local path or remote URL)
  |  owns  Message_ptr_map  mMessages   index -> Message*   (parsed messages)
  |        MessageInfo_map  mMessagePositions               (pre-scanned, not yet parsed)
  |        MapInfo_sptr     mMemoryMapInfo                  (mapping of the whole file)
  |        NetCdfFile* / QueryDataFile* / GeoTiffFile*      (container-format helpers)
  |
  +-- GRID::Message   (abstract API, ~200 virtuals; src/grid/Message.h)
        +-- GRIB1::Message   IndicatorSection, ProductSection, GridSection,
        |                    BitmapSection, DataSection
        +-- GRIB2::Message   Indicator, Identification, Local, Grid, Product,
        |                    Representation, Bitmap, Data sections
        +-- NetCDF::Message    one variable x level x time slice of a NetCdfFile
        +-- QueryData::Message one param x level x time slice of a QueryDataFile
        +-- GeoTiff::Message   one band/slice of a GeoTiffFile
```

GRIB messages parse their own bytes out of the file's memory map. NetCDF, QueryData
and GeoTIFF files are single containers. For those, a helper object parses the whole
file once and the `Message` objects are thin views that call back into it
(`NetCdfFile::getGridValue(...)` and similar).

### GRIB sections are composed from templates

Inside a GRIB2 message, each templated section holds a polymorphic definition object
chosen by its template number:

| Section | Holder | Factory | Base class | Examples |
|---------|--------|---------|------------|----------|
| 3 Grid | `GridSection` | `GridSection::createGridDefinition()` | `GRIB2::GridDefinition` | `LatLonImpl` (3.0), `RotatedLatLonImpl` (3.1), `LambertConformalImpl` (3.30), `PolarStereographicImpl` (3.20), `GaussianImpl` (3.40), `SpaceViewImpl` (3.90) … |
| 4 Product | `ProductSection` | `ProductSection::createProductDefinition()` | `GRIB2::ProductDefinition` | `NormalProductImpl` (4.0), `EnsembleForecastImpl` (4.1), `AggregateForecastImpl` (4.8) … |
| 5 Representation | `RepresentationSection` | `RepresentationSection::createRepresentationDefinition()` | `GRIB2::RepresentationDefinition` | `GridDataRepresentationImpl` (5.0 simple), `ComplexGridDataRepresentationImpl` (5.2), `ComplexDifferenceGridDataRepresentationImpl` (5.3), `JpegGridDataRepresentationImpl` (5.40), `PngGridDataRepresentationImpl` (5.41), `FloatingPointGridDataRepresentationImpl` (5.4) … |

Each `XxxImpl` inherits from a generated `Xxx` class (in `definition/`), and the
generated class inherits from the hand-written base (`GridDefinition` and so on). The
generated layer only reads, writes, prints and hashes the template fields. All
behaviour (coordinate maths, decoding) lives in the base classes and the `Impl`
classes. GRIB1 follows the same pattern for its grid definitions (`grib1/definition/`,
`grib1/implementation/`). Its packings are plain classes (`SimplePacking`,
`SecondOrderPacking`, `SphericalHarmonics*Packing`).

### Properties

`GRIB1::Property` and `GRIB2::Property` (`Properties.h`) give every header field a
numeric property id and a dotted name, for example
`Property::RepresentationSection::RepresentationTemplateNumber`. `Message::getProperty()`
and `setProperty()` dispatch on these ids down to the owning section. This is how
generic code (the grid-gui inspector, the download plugin's GRIB writer) reads and sets
header fields without knowing the section layout. A new generated field is only
reachable through this API once you also add it to `Properties.h`/`.cpp` and to the
section's `getProperty`/`setProperty` switch.

## 5. Reading a file: the full path

```cpp
#include <grid-files/grid/GridFile.h>
#include <grid-files/identification/GridDef.h>

SmartMet::Identification::gridDef.init("/path/to/grid-files.conf");  // once per process

SmartMet::GRID::GridFile file;
file.read("/data/ecmwf/2026092500_t.grib2");            // maps + scans + parses
for (std::size_t i = 0; i < file.getNumberOfMessages(); i++)
{
  SmartMet::GRID::Message* msg = file.getMessageByIndex(i);
  std::cout << msg->getFmiParameterName() << " " << msg->getForecastTime() << "\n";

  SmartMet::T::ParamValue_vec values;
  msg->getGridValueVector(values);                      // decoded, row-major, float
}
```

What happens inside:

1. **`GridFile::read(filename)`** stores the name and calls `mapToMemory()`. This asks
   `memoryMapper` for the file size and a mapping (see [§10](#10-memory-mapping-and-remote-files)).
   If a deletion time is set, the call refuses to map a file that will be deleted
   within 180 s.
2. **`searchMessageLocations()`** detects the format from the first bytes:
   * `CDF` → NetCDF (the whole file is one container)
   * `40 24 B0 A3 51` → QueryData
   * `II` / `MM` → GeoTIFF
   * otherwise it scans for `GRIB` and reads the edition byte and total length. Invalid
     candidates are skipped one byte at a time, because GRIB1 files often have garbage
     between messages.
3. For **GRIB**, each found message gets its own `MemoryReader` over
   `[start, nextStart)`, and `readGrib1Message` / `readGrib2Message` build the message.
   `GRIB2::Message::read(MemoryReader&)` walks the sections by section number. It stops
   at `7777`, or when the section number goes backwards. The grid section builds the
   message's CRS (`initSpatialReference()`) while it is read.
4. For **container formats**, the helper (`NetCdfFile`, `QueryDataFile`,
   `GeoTiffFile`) returns a `MessageInfoVec` and one `Message` is created per entry.
5. After the headers are parsed, each GRIB message calls **`initParameterInfo()`**,
   which runs identification ([§6](#6-parameter-identification-griddef)). **Data values
   are not decoded at this point.**

### Lazy construction from pre-scanned metadata

The content server does not want to parse millions of messages at startup. It stores
per-message metadata (offset, size, type, FMI ids, forecast time, geometry) and hands
it to the Data Server, which calls `GridFile::newMessage(index, MessageInfo&)`. That
only records a `MessageInfo` in `mMessagePositions`. The first
`getMessageByIndex(i)` then maps the file (if needed), calls `createMessage()` and parses
just that message. Code that iterates messages must therefore always go through
`getMessageByIndex()`, never through `mMessages` directly.

`getMessageByIndex()` also recovers from mapping errors. If the memory mapper flagged
the file, it waits 10 s, then unmaps it, deletes all parsed messages, and remaps on the
next call. **Any `Message*` you held from before that point is dangling.** Callers in
grid-content hold a `GridFile_sptr` and look messages up again for each request instead
of caching `Message*` across requests.

## 6. Parameter identification (GridDef)

`Identification::gridDef` (`src/identification/GridDef.h`) is a process-wide
registry built from the CSV files listed in `grid-files.conf`. It answers questions
like:

* which GRIB parameter id matches this message's header fields
  (`getGribParameterId(GRIB2::Message&)`, which matches the field lists in
  `grib2_parameters.csv`)
* which FMI parameter that GRIB id maps to (`fmi_parameterId_grib.csv`)
* FMI level id from the level header fields (`fmi_levelId_grib2.csv`)
* FMI geometry id from the grid definition (`fmi_geometries.csv`). Each geometry line is
  turned into a grid definition, and a message matches when its
  `getGridGeometryString()` is identical to that definition's string
* Newbase and NetCDF names for the same FMI parameter

`GRIB2::Message::initParameterInfo()` shows the order of resolution: FMI id (if it came
in through `MessageInfo`) → GRIB id → names and units → FMI level → Newbase and NetCDF
names → geometry id. If a GRIB2 geometry is not in the geometry files, it prints a
ready-made CSV line to stdout that you can paste into `fmi_geometries.csv` (or
`ext/fmi_geometries.csv`). The message stays usable but has geometry id 0, and
geometry-based queries on it will fail.

### Configuration

`cfg/grid-files.conf` is a libconfig file under `smartmet.library.grid-files`. Each key
lists one or more CSV files; later files extend or override earlier ones. `%(DIR)` is
replaced with the directory of the configuration file. The `ext/` files are the
conventional place for site-specific additions.

The `cfg/` directory is **not** installed by the RPM. Production servers keep their own
copy (the grid engine's `smartmet.library.grid-files.configFile` points at it), so
changes to `cfg/` here only reach production once someone copies them into the
deployment configuration.

### Reloading

Every public lookup calls `updateCheck()`. At most once every 60 s, it compares the
modification times of all the configured files and reloads the changed groups under the
write lock. You can therefore edit the CSVs on a running server. The downside is that
**lookups are not free**: each one takes a read lock, and mappings can change between
two lookups in the same request.

## 7. Decoding values

### GRIB2

`GRIB2::Message::getGridValueVector(values)`:

1. If `mCacheKey` is set and the `valueCache` still has the entry, it copies it out.
2. Otherwise it calls `premap()` (to prefetch remote pages), then
   `RepresentationSection::decodeValues()`. That dispatches to the `*Impl` for the
   packing and applies the bitmap: missing points become `ParamValueMissing`
   (`-16777216`).
3. It stores the result in `valueCache` **unless** the packing is simple packing (5.0)
   with no bitmap. Simple-packed values can be decoded straight from the mapping
   (`getValueByIndex`), so caching them would only cost memory.
4. If decoding fails, it sets `mValueDecodingFailed`. Later calls return an empty
   vector at once instead of retrying. The exception is printed, not thrown, unless the
   memory mapper reported an I/O error.

Single-point reads (`getGridValueByGridPoint`) use the fastest path available: direct
index decode for simple packing without a bitmap, then a cache lookup, and only then a
full-grid decode. Batched variants (`getGridValueVectorByLatLonCoordinateList`,
`getGridValuesByPointList`) resolve all indexes first and take the cache lock once.
When you add a new query method, follow the same pattern. Calling
`getGridValueByGridPoint` in a loop takes the cache lock once per point.

`getGridOriginalValueVector()` returns values in the file's own layout. For reduced
(for example reduced Gaussian) grids, rows can have different lengths. Use
`getGridColumnCount()` and `getGridOriginalValueIndex()` with it.
`getGridValueVector()` returns the regular expanded grid.

### GRIB1

The same structure, with `DataSection` choosing among `SimplePacking`,
`SecondOrderPacking` and the spherical-harmonics packings.

### NetCDF, QueryData, GeoTIFF

The message forwards to its container helper, which reads the slice from the mapped
file (NetCDF, GeoTIFF) or from `NFmiFastQueryInfo` (QueryData).

### Values are `float`

`T::ParamValue` is `float`. Missing is `ParamValueMissing`, not NaN. Code above the
library compares against the sentinel, so any new decoder must write
`ParamValueMissing` for missing points and must never produce NaN or ±inf. (trax, which
does the contouring, handles NaN but not inf.)

## 8. Coordinates and projections

There are three coordinate systems, selected with `T::CoordinateTypeValue`:

| Type | Meaning |
|------|---------|
| `LATLON_COORDINATES` | geographic lon/lat in degrees (WGS84 CRS in `latlonSpatialReference`) |
| `GRID_COORDINATES` | fractional grid indexes `(i, j)`; `(0, 0)` is the first stored point |
| `ORIGINAL_COORDINATES` | native projection coordinates (metres, or rotated degrees) |

The main conversions are implemented in `GRIB2::GridDefinition` / `GRIB1::GridDefinition`
and specialised in each `*Impl`:

* `getGridPointByLatLonCoordinates(lat, lon, i, j)` (cached per point in the transform
  caches)
* `getGridLatLonCoordinatesByGridPoint/Position`
* `getGridLatLonCoordinates()` / `getGridOriginalCoordinates()` (whole-grid coordinate
  vectors, cached by geometry hash in `latlonCoordinateCache` / `originalCoordinateCache`)
* `getGridPointListByLatLonCoordinates(latlon, points)` (the batched form; implement
  this, not a loop, for new projections)

Other things you need to know:

* **CRS objects.** Each geometry builds an `OGRSpatialReference` from its WKT or
  PROJ.4 string (`initSpatialReference()`). CRS objects are shared through
  `T::SpatialRef_sptr`. `common/CoordinateConversions.cpp` caches
  `CoordinateConverter`s keyed by the addresses of the source and target CRS. The
  converter keeps both `shared_ptr`s alive, so a freed address cannot be reused by a
  different CRS and return the wrong converter. Keep that invariant if you touch the
  cache.
* **Scanning mode.** GRIB grids may be stored north-to-south or east-to-west.
  `reverseYDirection()` / `reverseXDirection()` tell you the storage order. The
  "ByGeometry" fast path (see below) flips the rows to south-to-north and **must**
  also flip the reported `grid.llbox` / `grid.bbox`. `test/FastPathOrientationTest.cpp`
  guards this.
* **Global grids.** `isGridGlobal()` makes `i` wrap around (`grid_i % columns`).
  Nearest-point and interpolation code must handle the seam.
* **Earth shape.** The Earth shape in the GRIB header is often the model's sphere, not
  the datum the data is really on. The geometry definitions in `fmi_geometries.csv`
  carry explicit semi-axes. Be careful before "fixing" code to trust the header.
* **Gaussian latitudes** are computed once per N and cached in
  `gaussianLatitudeCache`.

## 9. Value queries, reprojection and contouring

Most `Message` query methods come in two overloads. The second takes
`(uint modificationOperation, double_vec& modificationParameters)` and transforms
values after decoding. The operations are in the `Operation` enum at the end of
`Message.h`: scalar arithmetic, unit conversions such as `K2C`, and `GRID_*` operations
used by `MessageProcessing`. The overload without them just forwards with
`Operation::NONE`.

### Area and point queries

`getGridValueListByCircle`, `…ByPolygon`, `…ByPolygonPath`, `…ByRectangle` and
`…ByPointList` accept any `CoordinateType` and return `T::GridValueList` (x, y, value).
Polygon queries in lat/lon are the expensive case, because every candidate grid point
has to be transformed. Batch the transforms (`getGridPointListByLatLonCoordinates`)
instead of converting point by point.

### Reprojection via attribute lists

The `…ByGeometry`, `…ByGrid` and `…ByCrop` methods take a `T::AttributeList`. It says
**what output grid is wanted**, and the method writes back **what it produced**. The
same list goes on to the contouring and image code. The main keys:

| Key | Direction | Meaning |
|-----|-----------|---------|
| `grid.geometryId` | in | target FMI geometry. If it is the message's own geometry, the values are copied directly (fast path). |
| `grid.crs` | in/out | target CRS as a string that GDAL accepts. `data` means the message's own CRS, and `crop` (for `…ByCrop`) means a sub-area of the original grid. Written back as WKT. |
| `grid.bbox` / `grid.llbox` | in/out | target extent in CRS or lat/lon units |
| `grid.width` / `grid.height` | in/out | target raster size |
| `grid.size`, `grid.center` | in | an alternative way to give the extent |
| `grid.areaInterpolationMethod` | in | a `T::AreaInterpolationMethod` value; defaults to the parameter's configured method |
| `grid.original.*` | out | properties of the source grid (`crs`, `width`, `height`, `reverseYDirection`, `global`, `relativeUV`, cell sizes …) |
| `contour.coordinateType`, `contour.interpolation.type`, `contour.smooth.size`, `contour.smooth.degree`, `contour.threads` | in | contouring options |

The keys are plain strings spread over `Message.cpp` and `MessageProcessing.cpp`. There
is no central list, so `grep '"grid\.'` is the way to find every key. Downstream plugins
(wms, download, grid-gui) depend on these names. Treat them as part of the API.

### Contours and streamlines

`getGridIsolines*`, `getGridIsobands*` and `getGridStreamlines*` produce WKB byte
vectors (`T::ByteData_vec`), one per contour value or band. Contouring is done by trax
through `common/GraphFunctions.cpp`. The results are in the requested
`contour.coordinateType`.

### MessageProcessing

`GRID::MessageProcessing` interpolates between **two or four** messages (by level, by
time, or by both) before extracting values or contours. The Query Server uses it when
the requested time or level falls between stored messages. The interpolation methods
come from `grid.timeInterpolationMethod` and `grid.levelInterpolationMethod`.

## 10. Memory mapping and remote files

Everything reads through a pointer into a mapped file. `SmartMet::memoryMapper`
(`common/MemoryMapper.h`) supports two modes:

**Disabled (default).** `map()` uses `Fmi::MappedFile` (a read-only mmap of a local
file). This is the normal production setup for files on local disk or NFS.

**Enabled** (`memoryMapper.setEnabled(true)`, set by the grid engine from
`smartmet.library.grid-files.memoryMapper.enabled`). This mode reserves an anonymous
region and registers it with **`userfaultfd`**. When code first touches a page, the
kernel sends a fault to `faultHandlerThread`, and `faultProcessingThread` workers fetch
the page through a `DataFetcher`:

* `DataFetcher_filesys` for local files,
* `DataFetcher_network` for HTTP, HTTPS, S3 and THREDDS servers (`HttpClient`,
  `HttpsClient`, with credentials from `setAccessFile()` / `addAccessInfo()`).

Pages go into a fixed-size page cache (`setPageCacheSize`). `premap()` fetches a
message's whole byte range up front, so that decoding does not take one fault per page.
`Message::premap()` calls it before any full decode.

A `GridFile` describes where its bytes come from with `setServerType()`
(`MapInfo::ServerType::Filesys|S3|THREDDS|HTTPD`), `setProtocol()` (`None|HTTP|HTTPS`)
and `setServer()`. The content server stores these per file.

If a remote fetch fails, the mapper sets `mappingError` on the `MapInfo` and fills the
page with zeros, so the faulting thread is not blocked forever. Decoders then call
`mGridFilePtr->hasMemoryMapperError()` and **throw instead of returning the zeros as
data**. Any new decoding path must do the same check after reading.

If the kernel refuses `userfaultfd` (for example with `vm.unprivileged_userfaultfd=0`
for a non-root process), `setEnabled(true)` prints a `### WARNING` to stdout and
returns without switching modes. Check the startup log when enabling it. Debug it with the state tree
from `memoryMapper.getStateAttributes()`, which the grid engine exposes.

**NFS caveat (both modes).** If a file on NFS is unlinked while it is mapped, a later
page fault raises `SIGBUS`. This cannot be caught safely. The content server's
`deletionTime` bookkeeping (and the 180 s guard in `mapToMemory`) exists to keep readers
off files that are about to be deleted.

## 11. Process-wide singletons and caches

The library relies on global objects. Know them before you write tests or tools:

| Object | Header | Purpose / initialisation |
|--------|--------|--------------------------|
| `Identification::gridDef` | `identification/GridDef.h` | Mapping registry. **You must call `init(configFile)` before reading any GRIB file.** Parsing calls into it, and uninitialised lookups throw. |
| `GRID::valueCache` | `grid/ValueCache.h` | Decoded value vectors, keyed by an opaque `uint`. `init(maxEntries, maxMegaBytes[, fileBacked])`. With `setCacheDir()`, entries are written to temporary files and mmapped, so they do not count against the heap. |
| `GRID::indexCache` | `grid/IndexCache.h` | Index vectors keyed by hash. Currently unused. |
| `GRID::gaussianLatitudeCache` | `grid/GaussianLatitudeCache.h` | Gaussian latitudes per N. |
| `memoryMapper` | `common/MemoryMapper.h` | See [§10](#10-memory-mapping-and-remote-files). |
| `stringFactory` | `common/StringFactory.h` | String interning. `Message` stores parameter names and units as `uint` ids (`mFmiParameterName` …). Use `stringFactory[id]` to get the `const char*`. Strings are never freed. |
| GRIB1 and GRIB2 `latlonCoordinateCache`, `originalCoordinateCache`, `transformCache1..3`, `spatialReferenceCache` | `grib*/GridDefinition.cpp` | Coordinate vectors and point transforms. Statistics are exported through the `*_stats` globals. |
| `coordinateConverterCache` | `common/CoordinateConversions.cpp` | OGR transformation objects keyed by CRS pair. |

The caches use `Fmi::Cache::Cache` from macgyver. Their sizes are compile-time
constants in the `.cpp` files (`COORDINATE_VEC_CACHE_SIZE`, `TRANSFORM_VEC_CACHE_SIZE`),
except for `valueCache`, whose size is set by the grid engine.

## 12. Thread safety

The Data Server calls into the same `GridFile` and `Message` objects from many request
threads, so almost everything must be safe for concurrent readers:

* `GridFile::mMemoryMappingLock` serialises mapping, remapping and lazy message creation.
* `Message::mThreadLock` guards `read()` (lazy parsing) and the lazily computed members.
  Many accessors are `const` but fill `mutable` members (`mCacheKey`, `mPremapped`,
  `mValueDecodingFailed`, …). Take the lock or use an atomic when you add another one.
* `GridDef` uses a `ModificationLock` (read/write) around every lookup and reload.
* `ValueCache` has its own read/write lock. `getValues*` copy out while holding it.
* The CRS and PROJ objects are the fragile part. An `OGRSpatialReference` must not be
  mutated while another thread uses it, and a shared `OGRCoordinateTransformation` must
  not be used concurrently. Heap corruption in unrelated places (for example a jsoncpp
  crash in WMS) has come from exactly this. Clone a CRS before you configure it, and
  create transformations per thread or per cache entry, the way `CoordinateConverter`
  does.

The shared-lock types are in `common/` (`ThreadLock`, `ModificationLock`,
`AutoThreadLock`, `AutoReadLock`, `AutoWriteLock`). New code can use them or the
standard library. Stay consistent within a class.

## 13. Generated GRIB template classes

`src/grib1/definition/*` and `src/grib2/definition/*` are generated by
`php/createClassDefinitions_grib{1,2}.php` from the eccodes definition files in
`/usr/share/eccodes/definitions/grib{1,2}/`. Each directory's `Makefile` lists exactly
which templates are generated. The files start with `DO NOT EDIT THIS FILE`.

* **Make behavioural changes in `implementation/*Impl.{h,cpp}` or in the base classes.**
* The generated files are **committed**. `make delete_def` deletes them and
  `make create_def` regenerates them from whatever eccodes version is installed. A newer
  eccodes can rename fields or change templates, which then breaks the `*Impl` classes
  and `Properties.cpp`. Only regenerate on purpose, then review the diff and rebuild
  everything downstream.
* To support a **new template**:
  1. add a rule and the `H_FILES` / `CPP_FILES` entries in `definition/Makefile`,
  2. generate the file (`cd src/grib2/definition && make NewThing.h`),
  3. write `implementation/NewThingImpl.{h,cpp}`,
  4. add a `case` to the section's `create…Definition()` factory,
  5. if needed, add properties to `Properties.{h,cpp}` and to the section's
     get/set switch.

## 14. Coding conventions

Match the surrounding code:

* **Error handling.** Almost every function body is:

  ```cpp
  void Foo::bar()
  {
    FUNCTION_TRACE
    try
    {
      ...
    }
    catch (...)
    {
      Fmi::Exception exception(BCP,"Operation failed!",nullptr);
      exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
      throw exception;
    }
  }
  ```

  The nested `Fmi::Exception` chain is the stack trace users see in server logs, so add
  context parameters such as file name, message index or position. Do not catch and
  ignore errors, except in the documented "decode failed, remember and return empty"
  case.
* **`FUNCTION_TRACE`.** Each `.cpp` defines it as `FUNCTION_TRACE_OFF` at the top.
  Switch one file to `FUNCTION_TRACE_ON` locally (and set `globalTraceLog`) to trace
  function entry and exit. Do not commit it on.
* **Layout.** The code uses hand-aligned declarations and 2-space indentation, and
  clang-format is disabled (see [§2](#2-building-and-testing)). Headers carry Doxygen
  `/*! \brief ... */` comments on every public member; keep them updated.
* **Types.** Use the `T::` typedefs (`T::ParamValue`, `T::GeometryId`,
  `T::FmiParamId`, `T::Coordinate_vec`, …) rather than raw types in public signatures.
* Use `Fmi::to_string` and `fmt::format` for formatting, and `boost::regex` rather
  than `std::regex`.

## 15. Common tasks

### 15.1 Supporting a new GRIB2 grid, product or packing template

Follow [§13](#13-generated-grib-template-classes). For a **grid** template, implement
at least `getGridLatLonCoordinatesByGridPosition`, `getGridPointByLatLonCoordinates`,
the whole-grid coordinate methods, `getGridDimensions`, `getGridGeometryString`,
`initSpatialReference` (WKT/PROJ) and `countHash`. `getGridGeometryString()` is what
geometry identification compares against `fmi_geometries.csv`, so it must be exact and
must include every field that affects the geometry. The hash is used as a cache key for
the coordinate caches, so it must include those fields too. For a
**packing**, implement `decodeValues` and, if single values can be decoded cheaply,
`getValueByIndex`.

### 15.2 Adding a parameter, level or geometry mapping

This is a configuration change, not code. Edit the CSVs described in
[doc/grid-files.md](../doc/grid-files.md), preferably the `ext/` files. Running servers
pick up the change within 60 s ([§6](#6-parameter-identification-griddef)). Remember to
update the deployment configuration, not just `cfg/`.

### 15.3 Adding a new `Message` method

1. Declare it `virtual` in `GRID::Message`, with a default implementation that is
   generic (built on the existing primitives) or that throws "Not implemented".
2. Override it in the format classes that can do better.
3. If it takes value modifications, provide both overloads.
4. Remember the base class is used polymorphically across a shared-library boundary.
   See the next section.

### 15.4 Adding a new file format

1. Add a `T::FileTypeValue` entry.
2. Add a detection branch in `GridFile::searchMessageLocations()`, before the GRIB scan.
3. Add a container helper (`XxxFile`) and a `Xxx::Message : GRID::Message`, following
   `geotiff/`.
4. Add cases in `GridFile::read(MemoryReader&, …)`, `createMessage()` and
   `newMessage()`.
5. Register the new directory in the `Makefile` ([§2](#2-building-and-testing)).

### 15.5 Changing a public header

Every header under `src/` is installed and used by grid-content, the grid engine and
the plugins. Adding, removing or reordering a **virtual** function in `GRID::Message`,
`GridFile` or the section and definition base classes, or changing data members of an
installed class, changes the ABI. Downstream `.so` files built against the old headers
will then call the wrong vtable slots or read the wrong offsets and crash at runtime,
often in unrelated-looking places. When you do this:

* bump `Version:` in the spec and the `BuildRequires`/`Requires` floors in every
  dependent package's spec,
* rebuild and release grid-content, the grid engine and the plugins that include the
  changed headers together with this library.

## 16. Known pitfalls

* **Missing geometry means geometry id 0.** A message with an unknown geometry still
  loads (with a stdout hint, see [§6](#6-parameter-identification-griddef)), but
  geometry-based queries on it fail. Check the logs for `GRIB2 Geometry not configured`.
* **`Message*` lifetime.** Pointers are invalidated when the file is remapped after a
  mapping error ([§5](#5-reading-a-file-the-full-path)), and when the owning `GridFile`
  is destroyed.
* **GRIB Earth-shape metadata is unreliable.** See [§8](#8-coordinates-and-projections).
* **Tests skip silently** when fixtures are absent ([§2](#2-building-and-testing)).
* See also [gis-spatialreference-migration.md](gis-spatialreference-migration.md) for
  the planned move from raw `OGRSpatialReference` to `Fmi::SpatialReference`.
