# GPGUI - Group Policy Editor GUI

## Contents

* [Introduction](#introduction)
* [Prerequisites](#prerequisites)

* * *

## Introduction

The project consists of C++11 backend with C interface - `libgptbackend`
and C++11/Qt5 frontend - GUI. There is also a plan for providing
`curses` UI.

The backend is needed to parse and write PReg (Registry.pol) files,
.reg files and many other Windows-specific formats used by Windows
Active Directory Domains. The backend may be compiled separately in
order to be used in side projects.

The frontend is needed to provide something similar to RSAT for UNIX
platforms.

The code is compiled and tested under ALT Linux and FreeBSD.

The code is MIT-licensed. The author encourages further project
improvement and re-licensing if needed.

## Prerequisites

## ALT Linux

* qt5-base-devel
* catch2-devel

## FreeBSD

* qt5 - Qt5 GUI library
* libiconv - Character codepage conversion library.
* catch - Catch2 unit testing framework

