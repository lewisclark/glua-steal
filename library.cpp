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


#include "library.h"

std::uintptr_t* glt::lib::GetSymbol(const std::string& lib_name, const std::string& sym_name) {
#if (defined(OS_LINUX) || defined(OS_MAC))
	void* lib = dlopen(lib_name.c_str(), RTLD_NOLOAD);

	if (lib) {
		return reinterpret_cast<std::uintptr_t*>(dlsym(lib, sym_name.c_str()));
	}
#elif (defined(OS_WINDOWS))
	HMODULE lib = GetModuleHandleA(lib_name.c_str());

	if (lib) {
		reinterpret_cast<std::uintptr_t*>(GetProcAddress(lib, sym_name.c_str()));
	}
#endif

	return nullptr;
}
