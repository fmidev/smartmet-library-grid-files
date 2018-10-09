Grid Files Library
====================
## Introduction

This library is used by the SmartMet Server grid support. The library offers a common service interface in order to access different kinds of grid files. At the moment, the library supports GRIB-1 and GRIB-2 files.

The basic idea is that we should be able to access different kind of grid files (GRIB-1,GRIB-2, NetCDF, jne.) in the same way (i.e. by using the same methods). So, this library is a kind of "driver layer" that makes all grid files to look same to upper libraries, services and applications.

The point is that in this way upper libraries, different services and applications can search, query and fetch information from different grid files in the same way, and they do not need to worry about actual grid file structures.


## Licence
The Grid Files Library is a part of the SmartMet Server (https://github.com/fmidev/smartmet-server), which is published with MIT-license.

## How to contribute
Found a bug? Want to implement a new feature? Your contribution is very welcome!

Small changes and bug fixes can be submitted via pull request. In larger contributions, premilinary plan is recommended (in GitHub wiki). 

CLA is required in order to contribute. Please contact us for more information!

## Documentation
SmartMet Server Grid support (https://github.com/fmidev/smartmet-tools-grid/raw/master/doc/grid-support.pdf)


## Communication and Resources
You may contact us from following channels:
* Email: beta@fmi.fi
* Facebook: https://www.facebook.com/fmibeta/
* GitHub: [issues](../../issues)

Other resources which may be useful:  
* Presentation about the server: http://www.slideshare.net/tervo/smartmet-server-providing-metocean-data  
* Our public web pages (in Finnish): http://ilmatieteenlaitos.fi/avoin-lahdekoodi   




