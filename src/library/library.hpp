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
	typedef std::uintptr_t*(* CreateInterfaceFn)(const char*, int*);

	class Library {
		public:
		Library(const std::string& pathname);
		~Library();

		template <typename T>
		T GetSymbol(const std::string& symname) {
#if (defined(OS_LINUX) || defined(OS_MAC)) 
			return reinterpret_cast<T>(dlsym(reinterpret_cast<void*>(m_handle),
				symname.c_str()));
#elif (defined(OS_WINDOWS))
			return reinterpret_cast<T>(GetProcAddress(reinterpret_cast<HMODULE>(m_handle),
				symname.c_str()));
#endif
		}

		template <typename T>
		T* GetInterface(const std::string& ifacename) {
			auto createinterface = GetSymbol<CreateInterfaceFn>("CreateInterface");

			if (createinterface) {
				return reinterpret_cast<T*>(createinterface(ifacename.c_str(), nullptr));
			}
			
			return nullptr;
		}
		
		private:
		std::string GetExtension();

		std::uintptr_t* m_handle = nullptr;
	};
}

#endif
