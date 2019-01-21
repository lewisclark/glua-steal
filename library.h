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


#ifndef LIBRARY_H
#define LIBRARY_H

#include <cinttypes>
#include <string>

#include "os.h"

#if (defined(OS_LINUX) || defined(OS_MAC))
#include <dlfcn.h>
#elif (defined(OS_WINDOWS))
#include <windows.h>
#endif

namespace glt::lib {
	std::uintptr_t* GetSymbol(std::string lib_name, const std::string& sym_name);
	std::string GetSharedExtension(); // Get the shared library extension for this OS
}

#endif
