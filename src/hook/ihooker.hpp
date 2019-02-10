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


#ifndef IHOOKER_H
#define IHOOKER_H

#include <vector>
#include <memory>
#include <cinttypes>

#include "vtable.hpp"

namespace glt::hook {
	class IHooker {
		public:
		virtual ~IHooker() {
			
		}

		virtual void Hook() = 0;

		protected:
		VTHook* CreateVTHook(std::uintptr_t** ppvtbase) {
			m_vthooks.push_back(std::make_unique<VTHook>(ppvtbase));

			return m_vthooks.back().get();
		}

		private:
		std::vector<std::unique_ptr<VTHook>> m_vthooks;
	};
}

#endif
