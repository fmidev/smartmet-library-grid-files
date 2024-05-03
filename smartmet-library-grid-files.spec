%define DIRNAME grid-files
%define LIBNAME smartmet-%{DIRNAME}
%define SPECNAME smartmet-library-%{DIRNAME}
Summary: grid file handling library
Name: %{SPECNAME}
Version: 24.5.3
Release: 1%{?dist}.fmi
License: MIT
Group: Development/Libraries
URL: https://github.com/fmidev/smartmet-library-grid-files
Source0: %{name}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

%if 0%{?rhel} && 0%{rhel} < 9
%define smartmet_boost boost169
%else
%define smartmet_boost boost
%endif

BuildRequires: rpm-build
BuildRequires: smartmet-utils-devel >= 24.3.13
BuildRequires: smartmet-library-newbase-devel >= 24.4.24
BuildRequires: smartmet-library-spine-devel >= 24.4.23
BuildRequires: smartmet-library-macgyver >= 24.1.17
BuildRequires: smartmet-library-trax-devel >= 23.8.17
BuildRequires: %{smartmet_boost}-devel
BuildRequires: gcc-c++
BuildRequires: gdal35-devel
BuildRequires: geos311-devel
BuildRequires: libwebp13-devel >= 1.3.2
BuildRequires: make
BuildRequires: libaec-devel
BuildRequires: libcurl-devel
BuildRequires: libjpeg-devel
BuildRequires: libjpeg-turbo-devel
BuildRequires: libpng-devel
BuildRequires: libjasper-devel
BuildRequires: openssl-devel
Provides: %{SPECNAME}
Requires: %{smartmet_boost}-date-time
Requires: %{smartmet_boost}-filesystem
Requires: %{smartmet_boost}-iostreams
Requires: %{smartmet_boost}-regex
Requires: %{smartmet_boost}-system
Requires: %{smartmet_boost}-thread
Requires: gdal35-libs
Requires: libaec
Requires: libcurl
Requires: libjpeg-turbo
Requires: libwebp13 >= 1.3.2
Requires: smartmet-library-newbase >= 24.4.24
Requires: smartmet-library-macgyver >= 24.1.17
Requires: smartmet-library-spine >= 24.4.23
Requires: smartmet-library-trax >= 23.8.17

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
Requires: %{SPECNAME} = %{version}-%{release}
Requires: smartmet-library-newbase-devel >= 24.4.24
Requires: smartmet-library-spine-devel
Requires: smartmet-library-macgyver >= 24.1.17
Requires: smartmet-library-trax-devel
Requires: %{smartmet_boost}-devel
Requires: libcurl-devel
Requires: gdal35-devel

%description -n %{SPECNAME}-devel
FMI Grid File library development files

%files -n %{SPECNAME}-devel
%defattr(0664,root,root,0775)
%{_includedir}/smartmet/%{DIRNAME}

%changelog
* Fri May  3 2024 Mika Heiskanen <mika.heiskanen@fmi.fi> - 24.5.3-1.fmi
- Improved caching
- Added level type information that defines relationship of level values (linear, logarithmic, just a number)
* Tue Mar 26 2024 Mika Heiskanen <mika.heiskanen@fmi.fi> - 24.3.26-1.fmi
- Fixed localTimeToUtcTime to work for spring time DST changes
* Fri Mar 22 2024 Andris Pavēnis <andris.pavenis@fmi.fi> 24.3.22-1.fmi
- Add method to common/GeneralFunctions
* Wed Mar 20 2024 Mika Heiskanen <mika.heiskanen@fmi.fi> - 24.3.20-1.fmi
- Added safety checks against accessing empty arrays
* Sat Mar 16 2024 Mika Heiskanen <mika.heiskanen@fmi.fi> - 24.3.16-1.fmi
- Fixed cache statistics reset
* Fri Feb 23 2024 Mika Heiskanen <mika.heiskanen@fmi.fi> 24.2.23-1.fmi
- Full repackaging
* Thu Feb 22 2024 Mika Heiskanen <mheiskan@rhel8.dev.fmi.fi> - 24.2.22-1.fmi
- Fixed RotatedLatLon scanning mode settings
* Tue Feb 20 2024 Mika Heiskanen <mheiskan@rhel8.dev.fmi.fi> - 24.2.20-1.fmi
- Enabled caching grids to disk
* Tue Feb  6 2024 Mika Heiskanen <mheiskan@rhel8.dev.fmi.fi> - 24.2.6-1.fmi
- Print more information on Boost MappedFile failures
* Mon Feb  5 2024 Mika Heiskanen <mheiskan@rhel8.dev.fmi.fi> - 24.2.5-1.fmi
- Concurrency improvements for loading remove files
- Improvements to writing GRIB files
* Tue Jan 30 2024 Mika Heiskanen <mika.heiskanen@fmi.fi> 24.1.30-1.fmi
- Repackaged due to newbase ABI changes
* Thu Jan  4 2024 Mika Heiskanen <mika.heiskanen@fmi.fi> - 24.1.4-1.fmi
- Minor updates needed for writing GRIB files
- Removed unnecessary PROT_WRITE flag when using mmap()
* Fri Dec 22 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.12.22-1.fmi
- Added double lock detection
- Added errno information to mmap failures
* Mon Dec 18 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.12.18-1.fmi
- Fixed potential deadlock
- Enabled writing GRIB files
* Tue Dec 12 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.12.12-1.fmi
- Reset memory pointer after failed memory mapping attempt
* Thu Dec  7 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.12.7-1.fmi
- Updated exception information for memory mapping
* Tue Dec  5 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.12.5-1.fmi
- Fixed too large array allocation to use dynamic memory allocation
* Mon Dec  4 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.12.4-1.fmi
- Bug fix to bilinear interpolation when one grid cell value is missing
* Tue Nov 28 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.11.28-1.fmi
- Automatically disable own memory mapper code for kernels prior version 4
* Thu Nov 23 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.11.23-1.fmi
- Name of the memory mapped file added to the exception object
* Tue Nov 21 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.11.21-1.fmi
- Repackaged since MappedFile ABI changed
* Fri Nov 17 2023 Pertti Kinnia <pertti.kinnia@fmi.fi> - 23.11.17-1.fmi
- Added cooordinate cache and fixed emplace_back methods
* Thu Nov 16 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.11.16-1.fmi
- Improved grid point discovery when the area center and the radius is given
* Tue Nov 14 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.11.14-1.fmi
- Grid center and metric box definition enabled for all projections
* Mon Nov 13 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.11.13-1.fmi
- Fixed bbox coordinate calculations for metric grid with latlon center point
* Mon Nov  6 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.11.6-1.fmi
- Fixed grid size calculations
* Thu Nov  2 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.11.2-1.fmi
- Fixed coordinate conversion prosessing
* Mon Oct 30 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.10.30-1.fmi
- Fixed handling of rotated latlon projection
* Fri Oct 20 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.10.20-1.fmi
- Fixed a bug in ccsds packing
* Thu Oct 12 2023 Andris Pavēnis <andris.pavenis@fmi.fi> 23.10.12-1.fmi
- Fixed geometry addition notice
* Tue Oct  3 2023 Andris Pavēnis <andris.pavenis@fmi.fi> 23.10.3-1.fmi
- Repackage to require newer libwebp13 (CVE-2023-4863)
* Fri Sep 29 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.9.29-1.fmi
- Handle UserFault failures more gracefully, just disable our own memory mapping code
* Mon Sep 11 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.9.11-1.fmi
- Adding grid size coordinate cache statistics information
- Added cache for grid size coordinate conversions.
- Returning grid metric size in kilometers
* Mon Aug 21 2023 Andris Pavēnis <andris.pavenis@fmi.fi> 23.8.21-1.fmi
- Use Fmi::MappedFile
* Fri Aug  4 2023 Andris Pavēnis <andris.pavenis@fmi.fi> 23.8.4-1.fmi
- Fix memory leaks
* Fri Jul 28 2023 Andris Pavēnis <andris.pavenis@fmi.fi> 23.7.28-1.fmi
- Repackage due to bulk ABI changes in macgyver/newbase/spine
* Mon Jul 24 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.7.24-1.fmi
- Trax API now uses float for data values
* Mon Jul 10 2023 Andris Pavēnis <andris.pavenis@fmi.fi> 23.7.10-1.fmi
- Use postgresql 15, gdal 3.5, geos 3.11 and proj-9.0
* Tue Jun  6 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.6.6-1.fmi
- Minor fix to image rendering
* Thu Mar  9 2023 Mika Heiskanen <mheiskan@rhel8.dev.fmi.fi> - 23.3.9-1.fmi
- Use enums instead of static ints to make ASAN builds work
* Thu Feb 23 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.2.23-1.fmi
- Adding possibility to use default value when replacing variables
* Mon Feb 20 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.2.20-1.fmi
- Added streamline processing
* Tue Jan 24 2023 Andris Pavēnis <andris.pavenis@fmi.fi> 23.1.24-1.fmi
- Add missing RPM requires
* Mon Jan 23 2023 Andris Pavēnis <andris.pavenis@fmi.fi> 23.1.23-1.fmi
- Repackage due to new version of libwebp (1.3.0)
* Thu Jan 19 2023 Mika Heiskanen <mika.heiskanen@fmi.fi> - 23.1.19-1.fmi
- Added streamline counting functions and some image functions
* Thu Dec 22 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.12.22-1.fmi
- Thread safety fixes
- Fixed new/delete combinations for some arrays
* Mon Dec 19 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.12.19-1.fmi
- Repackaged since Trax ABI changed due to addition of Grid::shell()
* Mon Dec 12 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.12.12-1.fmi
- Value of the requested configuration parameter not changed if the parameter is not found
- Added filesys support for the grid cache
- Improved memory mapping
- Added AWS4-HMAC-SHA256 authentication support for the memory mapper
* Tue Nov  8 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.11.8-1.fmi
- More improvements to userfaultd based memory mapper
* Thu Oct 20 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.10.20-1.fmi
- Improved userfaultd mechanisms
* Tue Oct 11 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.10.11-1.fmi
- Delay userfaultfd initialization until needed since it is blocked in Docker containers
* Mon Oct 10 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.10.10-1.fmi
- Implemented user fault based memory mapping
* Thu Sep 29 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.9.29-1.fmi
- Repackaged with changed Trax API
* Wed Sep 21 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.9.21-1.fmi
- Fixed bug in isoline generation
* Tue Aug 23 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.6.23-1.fmi
- Added cache statistics
* Fri Jun 17 2022 Andris Pavēnis <andris.pavenis@fmi.fi> 22.6.17-1.fmi
- Add support for RHEL9. Update libpqxx to 7.7.0 (rhel8+) and fmt to 8.1.1
* Tue May 24 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.5.24-1.fmi
- Repackaged due to NFmiArea ABI changes
* Fri May 20 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.5.20-1.fmi
- Repackaged due to ABI changes to newbase LatLon methods
* Thu May 19 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.5.19-1.fmi
- Removed redundant newbase projection includes to avoid deprecated dependencies
* Mon May 16 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.5.16-1.fmi
- Use Trax instead of Tron for contouring
* Tue Mar 15 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.3.15-1.fmi
- Fixes to ModificationLock
* Tue Mar  8 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.3.8-1.fmi
- Using Fmi::ValueFormatter instead of Spine::ValueFormatter
* Mon Mar  7 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.3.7-1.fmi
- Fixed possible deadlock situation
* Mon Feb 28 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.2.28-1.fmi
- Performance improvements
* Wed Feb  9 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.2.9-1.fmi
- Improved attribute parsing
* Tue Jan 25 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.1.25-1.fmi
- Increased use of shared_ptr for memory management
* Fri Jan 21 2022 Andris Pavēnis <andris.pavenis@fmi.fi> 22.1.21-1.fmi
- Repackage due to upgrade of packages from PGDG repo: gdal-3.4, geos-3.10, proj-8.2
* Thu Jan 13 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.1.13-1.fmi
- Improved time interpolation
* Wed Jan  5 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.1.5-1.fmi
- Added small utility functions
* Tue Dec  7 2021 Andris Pavēnis <andris.pavenis@fmi.fi> 21.12.7-1.fmi
- Update to postgresql 13 and gdal 3.3
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
