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


#include "library.hpp"

glt::lib::Library::Library(const std::string& pathname) {
	std::string pathnamext(pathname + GetExtension());

#if (defined(OS_LINUX) || defined(OS_MAC))
	m_handle = reinterpret_cast<std::uintptr_t*>(dlopen(pathnamext.c_str(), RTLD_NOLOAD));
#elif (defined(OS_WINDOWS))
	m_handle = reinterpret_cast<std::uintptr_t*>(GetModuleHandle(pathnamext.c_str()));
#endif
}

glt::lib::Library::~Library() {
#if (defined(OS_LINUX) || defined(OS_MAC))
	if (m_handle) {
		dlclose(m_handle);
	}
#endif
}

std::string glt::lib::Library::GetExtension() {
#if (defined(OS_LINUX))
	return ".so";
#elif (defined(OS_MAC))
	return ".dylib"
#elif (defined(OS_WINDOWS))
	return ".dll";
#endif
}
