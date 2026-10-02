#!/bin/sh
# Generates the NetCDF fixture of OtherFormatsTest (needs ncgen). The grid-files GeoTIFF
# reader only reads FMI GeoTIFFs with private metadata tags, so it has no fixture here.
# The values are a known function of the grid position, see OtherFormatsTest.cpp.
set -e
cd "$(dirname "$0")"

# ---- NetCDF classic: t2m(time,lat,lon), lat 60..65 step 1, lon 20..27 step 1, 2 times ----
python3 - <<'PY'
nt, nlat, nlon = 2, 6, 8
vals = []
for t in range(nt):
    for j in range(nlat):
        for i in range(nlon):
            vals.append("%.2f" % (270 + t * 5 + j * 1.5 + i * 0.25))
with open("netcdf_latlon.cdl", "w") as f:
    f.write("""netcdf netcdf_latlon {
dimensions:
  time = 2 ;
  lat = 6 ;
  lon = 8 ;
variables:
  double time(time) ;
    time:units = "hours since 2026-01-01 00:00:00" ;
    time:standard_name = "time" ;
  float lat(lat) ;
    lat:units = "degrees_north" ;
    lat:standard_name = "latitude" ;
  float lon(lon) ;
    lon:units = "degrees_east" ;
    lon:standard_name = "longitude" ;
  float t2m(time, lat, lon) ;
    t2m:units = "K" ;
    t2m:standard_name = "air_temperature" ;
    t2m:long_name = "2 metre temperature" ;
data:
  time = 0, 6 ;
  lat = 60, 61, 62, 63, 64, 65 ;
  lon = 20, 21, 22, 23, 24, 25, 26, 27 ;
  t2m = %s ;
}
""" % ", ".join(vals))
PY
ncgen -k classic -o netcdf_latlon.nc netcdf_latlon.cdl
