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

#if (defined(OS_LINUX) || defined(OS_MAC))
	struct library_entry {
		const char* name;
		void* lib;
	};

	int phdr_callback(struct dl_phdr_info* info, size_t, void* data) {
		library_entry* entry = reinterpret_cast<library_entry*>(data);

		if (strstr(info->dlpi_name, entry->name) != nullptr) {
			entry->lib = dlopen(info->dlpi_name, RTLD_NOLOAD | RTLD_NOW);
			return 1;
		}

		return 0;
	}
#endif

glt::lib::Library::Library(const std::string& pathname) :
	m_pathname(pathname) {

	std::string pathnamext(pathname + GetExtension());

#if (defined(OS_LINUX) || defined(OS_MAC))
	library_entry entry;
	entry.name = pathnamext.c_str();
	entry.lib = nullptr;

	dl_iterate_phdr(phdr_callback, (void*)&entry);

	m_handle = reinterpret_cast<std::uintptr_t*>(entry.lib);
#elif (defined(OS_WINDOWS))
	MODULEENTRY32 module_entry;
	HANDLE module_snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	module_entry.dwSize = sizeof(MODULEENTRY32);
	
	if (!Module32First(module_snap, &module_entry)) {
		throw std::runtime_error("failed to get process modules");
	}

	do {
		std::string module_name = module_entry.szModule;
		std::size_t found = module_name.find(pathnamext);

		if (found != std::string::npos) {
			m_handle = reinterpret_cast<std::uintptr_t*>(module_entry.hModule);
			break;
		}

	} while (Module32Next(module_snap, &module_entry));
#endif

	if (!m_handle) {
		throw std::runtime_error("failed to grab handle for library " + pathnamext);
	}
}

glt::lib::Library::~Library() {
#if (defined(OS_LINUX) || defined(OS_MAC))
	if (m_handle) {
		dlclose(m_handle);
	}
#endif
}

std::string glt::lib::Library::GetPathName() const {
	return m_pathname;
}

std::string glt::lib::Library::GetExtension() const {
#if (defined(OS_LINUX))
	return ".so";
#elif (defined(OS_MAC))
	return ".dylib"
#elif (defined(OS_WINDOWS))
	return ".dll";
#endif
}
