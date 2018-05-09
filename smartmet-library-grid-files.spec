%define DIRNAME grid-files
%define LIBNAME smartmet-%{DIRNAME}
%define SPECNAME smartmet-library-%{DIRNAME}
Summary: grid file handling library
Name: %{SPECNAME}
Version: 18.1.25
Release: 1%{?dist}.fmi
License: MIT
Group: Development/Libraries
URL: https://github.com/fmidev/smartmet-library-grid-files
Source0: %{name}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires: rpm-build
BuildRequires: smartmet-library-newbase-devel >= 18.1.22
BuildRequires: smartmet-library-spine-devel >= 18.1.15
BuildRequires: boost-devel
BuildRequires: gcc-c++
BuildRequires: gdal-devel
BuildRequires: make
Provides: %{SPECNAME}
Requires: boost-date-time
Requires: boost-filesystem
Requires: boost-iostreams
Requires: boost-regex
Requires: boost-system
Requires: boost-thread
Requires: gdal
Requires: openjpeg
Requires: smartmet-library-newbase >= 18.1.22
Requires: smartmet-library-spine >= 18.1.15

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
* Thu Jan 25 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.1.25-1.fmi
- First packaged version

