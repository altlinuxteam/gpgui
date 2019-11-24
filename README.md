# GPGUI - Group Policy Editor GUI

## Contents

* [Introduction](#introduction)
* [Prerequisites](#prerequisites)
* [License](#license)

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

The code is BSD 3-clause licensed. The author encourages further project
improvement and re-licensing if needed.

## Prerequisites

## ALT Linux

* qt5-base-devel
* catch2-devel

## FreeBSD

* qt5 - Qt5 GUI library
* libiconv - Character codepage conversion library.
* catch - Catch2 unit testing framework


## License


Copyright (c) 2019 Igor Chudov <nir@sarfsc.ru>

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. Neither the name of the Igor Chudov nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

