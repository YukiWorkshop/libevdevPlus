Name:     libevdevPlus
Version:  0.1.0
Release:  1
Summary:  Library for ydotool
License:  MIT
URL:      https://github.com/YukiWorkshop/libevdevPlus
Source0:  https://github.com/YukiWorkshop/libevdevPlus/archive/%{name}-%{version}.tar.gz

BuildRequires: cmake make gcc-c++

%description
Library required for ydotool

%prep
%autosetup

%build
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
make

%make_install

%files
%{_libdir}/libevdevPlus*
%{_libdir}/pkgconfig/*
%{_includedir}/*

%doc README.md

%license LICENSE

%changelog
* Wed Feb 12 2020 Bob Hepple <bob.hepple@gmail.com> - 0.1.0-1
- Initial version of the package
