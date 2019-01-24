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


#ifndef ILUAINTERFACE_H
#define ILUAINTERFACE_H

#include <cinttypes>

#include "GarrysMod/Lua/Interface.h"

namespace glt::ssdk {
	class lua_State;

	class ILuaInterface : public GarrysMod::Lua::ILuaBase {
		public:
		lua_State* GetLuaState() {
			return *reinterpret_cast<lua_State**>(reinterpret_cast<std::uint8_t*>(this) + 0x4);
		}
	};

	extern ILuaInterface* g_clientluainterface;
}

#endif
