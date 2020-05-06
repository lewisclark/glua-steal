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
#include <stdexcept>
#include <cstring>

#include "os.hpp"

#if (defined(OS_LINUX) || defined(OS_MAC))
#include <dlfcn.h>
#include <link.h>
#elif (defined(OS_WINDOWS))
#include <windows.h>
#include <tlhelp32.h>
#endif

namespace glt::lib {
	typedef std::uintptr_t*(* CreateInterfaceFn)(const char*, int*);

	class Library {
		public:
		Library(const std::string& pathname);
		~Library();

		std::string GetPathName() const;

		template <typename T>
		T GetSymbol(const std::string& symname) const {
			std::uintptr_t* sym;

#if (defined(OS_LINUX) || defined(OS_MAC)) 
			sym = reinterpret_cast<std::uintptr_t*>(dlsym(reinterpret_cast<void*>(m_handle),
				symname.c_str()));
#elif (defined(OS_WINDOWS))
			sym = reinterpret_cast<std::uintptr_t*>(GetProcAddress(reinterpret_cast<HMODULE>(m_handle),
				symname.c_str()));
#endif

			if (!sym) {
				throw std::runtime_error("failed to get symbol " + symname + " from " + m_pathname);
			}

			return reinterpret_cast<T>(sym);
		}

		template <typename T>
		T* GetInterface(const std::string& ifacename) const {
			const auto& createinterface = GetSymbol<CreateInterfaceFn>("CreateInterface");
			T* iface = reinterpret_cast<T*>(createinterface(ifacename.c_str(), nullptr));

			if (!iface) {
				throw std::runtime_error("failed to get interface " + ifacename + " from " + m_pathname);
			}
			
			return iface;
		}
		
		private:
		std::string GetExtension() const;

		std::uintptr_t* m_handle = nullptr;
		std::string m_pathname;
	};
}

#endif
