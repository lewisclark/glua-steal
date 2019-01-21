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


#include "hook.h"

typedef int(* loadbufferx_fn)(std::uintptr_t*, const char*, size_t, const char*, const char*);

static subhook::Hook loadbufferx_hook;

void loadbufferx_hk(std::uintptr_t* luastate, const char* buff,
	size_t bufsize, const char* name, const char* mode) {

	glt::g_logger->LogFormat("{} - \n{}\n\n\n", name, buff);

	((loadbufferx_fn)(loadbufferx_hook.GetTrampoline()))(luastate, buff, bufsize, name, mode);
}

bool glt::hook::Init() {
	std::uintptr_t* loadbufferx = lib::GetSymbol("lua_shared", "luaL_loadbufferx");

	if (!loadbufferx) {
		return false;
	}

	loadbufferx_hook.Install((void*)loadbufferx, (void*)loadbufferx_hk);

	return true;
}
