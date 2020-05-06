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


#include "luaexports.hpp"

void glt::lua::GetExports() {
	const auto& libluashared = lib::Library("lua_shared");

	luaL_loadbuffer = libluashared.GetSymbol<luaL_loadbufferfn>("luaL_loadbuffer");
	lua_setfenv = libluashared.GetSymbol<lua_setfenvfn>("lua_setfenv");
}

glt::lua::luaL_loadbufferfn glt::lua::luaL_loadbuffer = nullptr;
glt::lua::lua_setfenvfn glt::lua::lua_setfenv = nullptr;
