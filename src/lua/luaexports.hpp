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


#ifndef LUAEXPORTS_H
#define LUAEXPORTS_H

#include <cinttypes>
#include <stdexcept>

#include "os.hpp"
#include "library/library.hpp"

#include "gamesdk/ILuaInterface.hpp"

namespace glt::lua {
	void GetExports();

	typedef int (__CDECL__* luaL_loadbufferfn)(glt::ssdk::lua_State*, const char*, size_t, const char*);
	typedef int (__CDECL__* lua_setfenvfn)(glt::ssdk::lua_State*, int);

	extern luaL_loadbufferfn luaL_loadbuffer;
	extern lua_setfenvfn lua_setfenv;
}

#endif
