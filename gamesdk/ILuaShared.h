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


#ifndef ILUASHARED_H
#define ILUASHARED_H

#include "GarrysMod/Lua/Interface.h"

namespace glt::ssdk {
	typedef GarrysMod::Lua::ILuaBase ILuaInterface;

	class ILuaShared {
		public:
		virtual void pad_0() = 0;
		virtual void pad_1() = 0;
		virtual void pad_2() = 0;
		virtual void pad_3() = 0;
		virtual ILuaInterface* CreateLuaInterface(unsigned char, bool) = 0;
		virtual void CloseLuaInterface(ILuaInterface*) = 0;
		virtual ILuaInterface* GetLuaInterface(unsigned char) = 0;
	};

	extern ILuaShared* g_luashared;
}

#endif
