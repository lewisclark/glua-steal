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


#ifndef VTABLE_H
#define VTABLE_H

#include <cstring>

#include "../os.h"

#if (defined(OS_LINUX) || defined(OS_MAC)) 
#include <unistd.h>
#include <sys/mman.h>
#elif (defined(OS_WINDOWS))

#endif

class VTHook {
	public:
	VTHook(std::uintptr_t** vt_base) { // Double pointer to base of vt
		bInitialize(vt_base);
	}

	~VTHook() {
		UnHook();
	}

	bool bInitialize(std::uintptr_t** vt_base) {
		m_vtbase = vt_base;
		m_oldvt = *vt_base;
		m_vtsize = GetVTCount(*vt_base);
		m_newvt = new std::uintptr_t[m_vtsize];
		memcpy(m_newvt, m_oldvt, sizeof(std::uintptr_t) * m_vtsize);

		if (!MemoryUnprotect(*vt_base)) {
			glt::g_logger->LogString("Failed to MemoryUnprotect vtable\n");

			return false;
		}

		*vt_base = m_newvt;

		return true;
	}

	void UnHook() {
		if (m_vtbase) {
			*m_vtbase = m_oldvt;
		}

		delete[] m_newvt;
	}

	void ReHook() {
		if (m_vtbase) {
			*m_vtbase = m_newvt;
		}
	}

	int iGetFuncCount() {
		return m_vtsize;
	}

	std::uintptr_t GetFuncAddress(int index) {
		if (index >= 0 && index <= m_vtsize && m_oldvt != nullptr) {
			return m_oldvt[index];
		}

		return 0;
	}

	std::uintptr_t* GetOldVT() {
		return m_oldvt;
	}

	std::uintptr_t* GetNewVT() {
		return m_newvt;
	}

	template <typename T>
	T HookMethod(std::uintptr_t new_fn, int index) {
		if (m_newvt && m_oldvt && index <= m_vtsize && index >= 0) {
			m_newvt[index] = new_fn;

			return reinterpret_cast<T>(m_oldvt[index]);
		}

		return 0;
	}

	int GetVTCount(std::uintptr_t* vt) {
		int i;

		for (i = 0; vt[i]; i++) {
			if (!(vt[i])) {
				break;
			}
		}

		return i;
	}

	bool MemoryUnprotect(std::uintptr_t* addr) {
#if (defined(OS_LINUX) || defined(OS_MAC))
		std::uintmax_t page_size = sysconf(_SC_PAGE_SIZE);
		std::uintptr_t page_start = (std::uintptr_t)addr & ~(page_size - 1);

		return !mprotect((void*)page_start, page_size, PROT_READ | PROT_WRITE | PROT_EXEC);
#elif (defined(OS_WINDOWS))
		return true;
#endif
	}

	private:
	std::uintptr_t** m_vtbase;
	std::uintptr_t* m_newvt;
	std::uintptr_t* m_oldvt;
	int m_vtsize;
};

#endif
