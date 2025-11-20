Name:    lib42
Version: @PROJECT_VERSION_MAJOR@.@PROJECT_VERSION_MINOR@.@PROJECT_VERSION_PATCH@
Release: 0%{?dist}
Summary: C Standard Library for the School 42 projects

# Do not mark this package noarch: it produces compiled libraries per-architecture.
License: LGPL-3.0-or-later
URL: https://github.com/cliftontoaster-reid/lib42
Source0: %{name}-%{version}.tar.gz

# Build requirements
BuildRequires: cmake
BuildRequires: make
BuildRequires: gcc
BuildRequires: pkgconfig
BuildRequires: redhat-rpm-config
BuildRequires: doxygen

%description
lib42 is a small C utility library (42-style) providing string, memory,
I/O, and basic data structure helpers for projects and exercises.

%prep
%autosetup -n %{name}-%{version}

%build
%cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF -DCMAKE_INSTALL_LIBDIR=%{_libdir}
%cmake_build

%install
%cmake_install

# Main package contains shared library and runtime helpers
%files
%license LICENCE.md
%doc README.md
%{_libdir}/lib42.so*
%{_libdir}/pkgconfig/42.pc

# Development package with headers and static archive
%package devel
Summary: Headers and development libraries for lib42
Requires: %{name} = %{version}-%{release}

%description devel
Development headers and static libraries to compile software against lib42.
This package contains header files, static library archives and cmake helper files used by developers.

%files devel
%{_includedir}/42/*
%{_libdir}/lib42.a
%{_libdir}/cmake/lib42/*

%changelog
* Wed Nov 19 2025 Your Name <you@example.com> - %{version}-%{release}
- Initial RPM packaging for lib42

