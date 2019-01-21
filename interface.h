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


#ifndef INTERFACE_H
#define INTERFACE_H

#include "library.h"

namespace glt::ssdk {
	typedef std::uintptr_t*(* CreateInterfaceFn)(const char*, int*);

	template <typename T>
	T* GetInterface(const std::string& lib_name, const std::string& iface_name) {
		CreateInterfaceFn factory = reinterpret_cast<CreateInterfaceFn>(
			lib::GetSymbol(lib_name, "CreateInterface"));

		if (!factory) {
			return nullptr;
		}

		return reinterpret_cast<T*>(factory(iface_name.c_str(), nullptr));
	}
}

#endif
