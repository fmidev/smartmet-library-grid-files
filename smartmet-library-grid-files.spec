%define DIRNAME grid-files
%define LIBNAME smartmet-%{DIRNAME}
%define SPECNAME smartmet-library-%{DIRNAME}
Summary: grid file handling library
Name: %{SPECNAME}
Version: 19.3.20
Release: 1%{?dist}.fmi
License: MIT
Group: Development/Libraries
URL: https://github.com/fmidev/smartmet-library-grid-files
Source0: %{name}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires: rpm-build
BuildRequires: smartmet-library-newbase-devel >= 19.3.14
BuildRequires: smartmet-library-spine-devel >= 19.3.14
BuildRequires: smartmet-library-macgyver >= 18.11.24
BuildRequires: smartmet-library-tron >= 17.9.20
BuildRequires: boost-devel
BuildRequires: gcc-c++
BuildRequires: gdal-devel
BuildRequires: make
BuildRequires: libaec-devel
BuildRequires: libjpeg-devel
BuildRequires: libjpeg-turbo-devel
BuildRequires: openjpeg-devel
BuildRequires: libpng-devel
BuildRequires: libjasper-devel
Provides: %{SPECNAME}
Requires: boost-date-time
Requires: boost-filesystem
Requires: boost-iostreams
Requires: boost-regex
Requires: boost-system
Requires: boost-thread
Requires: gdal
Requires: openjpeg
Requires: libaec
Requires: libjpeg-turbo
Requires: smartmet-library-newbase >= 19.3.14
Requires: smartmet-library-macgyver >= 18.11.24
Requires: smartmet-library-spine >= 19.3.14

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
