%define _unpackaged_files_terminate_build 1

Name: gpgui
Version: 0.0.1
Release: alt1

Summary:
License: MIT
Group: Other
Url: http://git.altlinux.org/

Source: %name-%version.tar

BuildRequires: qt5-base-devel

%description
Multiplatform GPO and GPT editor.

%prep
%setup

%build
cd src
%make_build

%install

%files

%changelog

