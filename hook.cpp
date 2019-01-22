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

// cannot allocate these inside loadbufferx_hk for some reason (subhook?)
static std::string servaddr; 
static std::filesystem::path luapath;
static std::ofstream ofluafile;

void loadbufferx_hk(std::uintptr_t* lua, const char* buf,
	size_t bufsize, const char* name, const char* mode) {

	if (glt::ssdk::g_engineclient->IsConnected()) {
		glt::ssdk::NetChannel* netchannel = glt::ssdk::g_engineclient->GetNetChannelInfo();

		if (netchannel) {
			servaddr = std::string(netchannel->GetAddress());
			std::replace(servaddr.begin(), servaddr.end(), '.', '-');
			std::replace(servaddr.begin(), servaddr.end(), ':', '_');

			luapath = glt::file::GetServerStorePath();
			luapath /= servaddr;
			luapath /= glt::file::SanitizeLuaFilePath(name + 1); // +1 to skip @ char

			std::filesystem::create_directories(luapath.parent_path());

			ofluafile.open(luapath);
			ofluafile << buf;
			ofluafile.close();
		}
	}

	((loadbufferx_fn)(loadbufferx_hook.GetTrampoline()))(lua, buf, bufsize, name, mode);
}

bool glt::hook::Init() {
	std::uintptr_t* loadbufferx = lib::GetSymbol("garrysmod/bin/lua_shared", "luaL_loadbufferx");

	if (!loadbufferx) {
		return false;
	}

	loadbufferx_hook.Install((void*)loadbufferx, (void*)loadbufferx_hk);

	return true;
}
