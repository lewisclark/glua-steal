/* Copyright (C) 2019 Lewis Clark

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>. */


#ifndef OS_H
#define OS_H

#if (defined(_WIN32))
#define OS_WINDOWS
#elif (defined(__linux__))
#define OS_LINUX
#elif (defined(__APPLE__) || defined(__MACH__))
#define OS_MAC
#else
#error "Operating system not found!"
#endif


// Calling conventions
#if (defined(__GNUC__))
#define __FASTCALL__ __attribute__((fastcall))
#define __THISCALL__ __attribute__((thiscall))
#define __CDECL__ __attribute__((cdecl))
#define __STDCALL__ __attribute__((stdcall))
#elif defined(_MSC_VER)
#define __FASTCALL__ __fastcall
#define __THISCALL__ __thiscall
#define __CDECL__ __cdecl
#define __STDCALL__ __stdcall
#endif


#endif
