%define DIRNAME grid-files
%define LIBNAME smartmet-%{DIRNAME}
%define SPECNAME smartmet-library-%{DIRNAME}
Summary: grid file handling library
Name: %{SPECNAME}
Version: 21.11.15
Release: 1%{?dist}.fmi
License: MIT
Group: Development/Libraries
URL: https://github.com/fmidev/smartmet-library-grid-files
Source0: %{name}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires: rpm-build
BuildRequires: smartmet-library-newbase-devel >= 21.11.15
BuildRequires: smartmet-library-spine-devel >= 21.11.10
BuildRequires: smartmet-library-macgyver >= 21.10.4
BuildRequires: smartmet-library-tron-devel >= 21.6.21
BuildRequires: boost169-devel
BuildRequires: gcc-c++
BuildRequires: gdal33-devel
BuildRequires: geos39-devel
BuildRequires: make
BuildRequires: libaec-devel
BuildRequires: libjpeg-devel
BuildRequires: libjpeg-turbo-devel
BuildRequires: libpng-devel
BuildRequires: libjasper-devel
Provides: %{SPECNAME}
Requires: boost169-date-time
Requires: boost169-filesystem
Requires: boost169-iostreams
Requires: boost169-regex
Requires: boost169-system
Requires: boost169-thread
Requires: gdal33-libs
Requires: libaec
Requires: libjpeg-turbo
Requires: smartmet-library-newbase >= 21.11.15
Requires: smartmet-library-macgyver >= 21.10.4
Requires: smartmet-library-spine >= 21.11.10
Requires: smartmet-library-tron >= 21.6.21

%description
FMI Grid File handling library

%prep
rm -rf $RPM_BUILD_ROOT

%setup -q -n %{SPECNAME}

%build
make %{_smp_mflags}

%install
%makeinstall

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%defattr(0775,root,root,0775)
%{_libdir}/libsmartmet-%{DIRNAME}.so

%package -n %{SPECNAME}-devel
Summary: FMI Grid File library development files
Provides: %{SPECNAME}-devel
Requires: %{SPECNAME}

%description -n %{SPECNAME}-devel
FMI Grid File library development files

%files -n %{SPECNAME}-devel
%defattr(0664,root,root,0775)
%{_includedir}/smartmet/%{DIRNAME}

%changelog
* Mon Nov 15 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.11.15-1.fmi
- New CSV utility functions
* Thu Nov 11 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.11.11-1.fmi
- Repackaged since ValueFormatter ABI changed
* Fri Oct 29 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.10.29-1.fmi
- Added support for querydata
* Tue Oct 19 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.10.19-1.fmi
- Added low level filtering capability
* Mon Oct 11 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.10.11-1.fmi
- Simplified GRIB metadata structures
* Mon Oct  4 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.10.4-1.fmi
- Improved GRIB identification
- Simplified configuration files
* Wed Sep 15 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.9.15-1.fmi
- NetCDF support
* Tue Aug 31 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.8.31-1.fmi
- Repackaged due to Spine changes
* Tue Jun  8 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.6.8-1.fmi
- Reduced memory use of data archive browsers
* Tue Jun  1 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.6.1-1.fmi
- Reduced memory usage
* Tue May 25 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.5.25-1.fmi
- Enable overriding incorrect earth radius settings in GRIB files
* Tue Apr 13 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.4.13-1.fmi
- Converting negative longitude values when unsigned longitudes are required
* Fri Apr  9 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.4.9-1.fmi
- Faster contouring with the latest Tron library
- Allow grid point calculations outside the grid
- Fixed linear interpolation in the border areas
- Fixed grid handling when a GRIB bitmask is set
* Wed Mar 31 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.3.31-1.fmi
- Enable cropping over grid borders when the grid is global 
* Mon Mar 29 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.3.29-2.fmi
- Fixed grid size calculations to use correct units
* Mon Mar 29 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.3.29-1.fmi
- Fixed to landscaping
- Allow larger grid downloads (10000x10000)
- Fixes to array limit checks
* Tue Mar 23 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.3.23-1.fmi
- Fixed grid size calculations
- Added checks against uninitialized shared pointers
- Updated parameter and geometry definitions
* Thu Mar  4 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.3.4-1.fmi
- Avoid copying MessageInfo into message search structures if the message is already there
* Thu Feb 25 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.2.25-1.fmi
- Added lon_wrap support for data using 0...360 longitudes
* Wed Feb 24 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.2.24-1.fmi
- Fixed a rounding issue in coordinate comparisons
- Fixed linear interpolation to handle special cases where a coordinate is exactly on a vertex
* Mon Feb 15 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.2.15-1.fmi
- Ported to use the new Tron contouring API
* Wed Feb  3 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.2.3-1.fmi
- Prefer time_t over std::string for speed
* Wed Jan 27 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.1.27-1.fmi
- Performance improvements
* Thu Jan 21 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.1.21-1.fmi
- Improved thread safety
* Tue Jan 19 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.1.19-1.fmi
- Performance improvements
* Thu Jan 14 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.1.14-1.fmi
- Repackaged smartmet to resolve debuginfo issues
* Tue Jan 12 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.1.12-1.fmi
- Fixed rotated latlon projection code to work with GDAL 3.2
* Mon Jan 11 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.1.11-1.fmi
- Fixed projection code to work with GDAL 3.2
* Tue Jan  5 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.1.5-1.fmi
- Upgrade to GEOS 3.9
* Mon Jan  4 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.1.4-1.fmi
- Fixed deprecated copy constructor implementations
* Wed Dec 30 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.12.30-1.fmi
- Removed openjpeg dependency
* Mon Dec 28 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.12.28-1.fmi
- Performance improvements
- Fixed a grid dimension bug
* Thu Dec  3 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.12.3-1.fmi
- Added polygon path length calculation
- Optimized getting grid values by grid point
* Tue Nov 24 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.11.24-2.fmi
- Faster utcTimeFromTimeT
* Tue Nov 24 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.11.24-1.fmi
- Improved error messages
- Performance improvements
* Thu Oct 22 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.10.22-1.fmi
- Performance improvements
* Thu Oct 15 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.10.15-1.fmi
- Use Fmi::Exception
- Checking message position and size against the file size before message creation
- Minor improvements
* Thu Oct  1 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.10.1-1.fmi
- Checking message position and size against the file size before message creation
* Wed Sep 23 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.9.23-1.fmi
- Use Fmi::Exception instead of Spine::Exception
* Fri Sep 18 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.9.18-1.fmi
- Performance improvements
- delete[] fix
* Tue Sep 15 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.9.15-1.fmi
- ModificationLocks can now be disabled if the modifications are known to be safe
* Mon Sep 14 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.9.14-1.fmi
- Added LAEA projection support
* Tue Sep  8 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.9.8-2.fmi
- Fixed LCC coordinate calculation bug
* Tue Sep  8 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.9.8-1.fmi
- Fixed hash problem with the coordinate transform cache
* Mon Sep  7 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.9.7-1.fmi
- Updated grid coordinate processing and caching
* Mon Aug 31 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.8.31-1.fmi
- Speed improvements
* Fri Aug 21 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.8.21-2.fmi
- Use Fmi::to_string instead of std::to_string for speed
* Fri Aug 21 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.8.21-1.fmi
- Upgrade to fmt 6.2
* Thu Aug 20 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.8.20-1.fmi
- Bug fix to filesys2smartmet functions
* Wed Aug 19 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.8.19-2.fmi
- Fixed GRIB1 reference time calculation
* Wed Aug 19 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.8.19-1.fmi
- Fixed speed optimized version of time interpolation
* Tue Aug 18 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.8.18-1.fmi
- More speed improvements
* Fri Aug 14 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.8.14-1.fmi
- Further speed improvements
* Tue Aug 11 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.8.11-1.fmi
- Speed improvements
* Mon Aug 10 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.8.10-1.fmi
- Avoid POSIX localtime functions requiring thread safe access to TZ
* Mon Jun 15 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.6.15-1.fmi
- Fixed virtual file id initialization
* Mon Jun  8 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.6.8-1.fmi
- Added new radon configuration files
- Improved memory mapping safety
* Fri May 15 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.5.15-1.fmi
- Code generated from eccodes templates instead of grib_api ones
- Added forecast type metadata
* Thu Apr 30 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.4.30-1.fmi
- Improved error messages
- Improved parameter and producer handling
* Sat Apr 18 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.4.18-1.fmi
- Upgrade to Boost 1.69
* Fri Apr  3 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.4.3-1.fmi
- Improved time string handling
- Added a generic Message class for handling grids
* Tue Mar 10 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.3.10-1.fmi
- Expanded perturbation number detection functionality
* Thu Mar  5 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.3.5-1.fmi
- Integrated GRIB1 and GRIB2 handling to be able to support both versions in a single file
* Tue Feb 25 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.2.25-1.fmi
- Updated request counting functionality
* Thu Feb 20 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.2.20-1.fmi
- Fixed Info-view of grid-gui
* Wed Feb 19 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.2.19-1.fmi
- Fixed coordinate counting
- Enabled native message fetching
- Added thread protection for message reading
- Refactored code
* Wed Jan 29 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.1.29-1.fmi
- Improved bbox handling
- Improved parameter handling
* Thu Jan 16 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.1.16-1.fmi
- Fixes to forecast time calculations
- Added grid.llbox response
* Wed Dec 11 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.12.11-1.fmi
- Improvements to low level utility functions
* Thu Dec  5 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.12.5-1.fmi
- Fixed GRIB earth radius reader to use provided radius instead of major axis
* Wed Dec  4 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.12.4-1.fmi
- Added new response attributes
- Ensure all timesteps use the same bounding box
- Enable outer border definition for llbox
- Fixed crop area coordinates
* Fri Nov 22 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.11.22-1.fmi
- Added cropping support
- Geometry parameter fixes
* Wed Nov 20 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.11.20-1.fmi
- Rebuilt due to newbase and spine ABI changes
* Thu Nov  7 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.11.7-1.fmi
- Improved decimal precisions
* Thu Oct 31 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.10.31-1.fmi
- Fixed message counter
* Fri Oct 25 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.10.25-1.fmi
- Some minor fixes
* Tue Oct  1 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.10.1-2.fmi
- Improved rotated latlon spatial reference
* Tue Oct  1 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.10.1-1.fmi
- Fixed rotated latlon calculations
* Fri Sep 20 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.9.20-1.fmi
- Optimized SmartMet::toTimeT for speed (avoid using tzset)
* Thu Sep 19 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.9.19-1.fmi
- Fixed rotated latlon spatial reference
- Fixed potential eternal loop
* Fri Aug  9 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.8.9-1.fmi
- Numerous improvements
* Tue May 14 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.5.14-1.fmi
- Parameter mapping updated
- Bug fix to point data cache
* Fri May 10 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.5.10-1.fmi
- New attribute search methods
* Mon May  6 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.5.6-1.fmi
- Added possibility to download GRIB1/GRIB2 files
* Tue Apr  2 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.4.2-1.fmi
- Fix to Mercator projection
- Fix to a thread safety problem
* Wed Mar 20 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.3.20-1.fmi
- Fixed memory leak
* Tue Mar 19 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.3.19-1.fmi
- Fixed deadlock
* Fri Mar 15 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.3.15-1.fmi
- Various improvements
* Fri Feb 15 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.2.15-1.fmi
- Various improvements
* Thu Jan 17 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.1.17-1.fmi
- Various improvements
* Tue Oct 23 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.10.23-1.fmi
- Various improvements
* Mon Oct 15 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.10.15-1.fmi
- Implemented CCSDS packing
* Mon Oct  1 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.10.1-1.fmi
- New release
* Wed Sep 26 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.9.26-1.fmi
- New release
* Mon Sep 10 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.9.10-1.fmi
- New release
* Thu Aug 30 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.8.30-1.fmi
- Silenced CodeChecker warnings
* Tue Aug 28 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.8.28-1.fmi
- Package latest version
* Mon Aug 27 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.8.27-1.fmi
- Package latest version
* Thu Jun 14 2018 Roope Tervo <roope.tervo@fmi.fi> - 18.6.14-1.fmi
- Build for testing
* Thu Jan 25 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.1.25-1.fmi
- First packaged version
