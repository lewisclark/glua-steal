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


#include "lualoader.h"

bool glt::lua::LoadLua(glt::ssdk::ILuaInterface* lua, const std::string& filename) {
	auto ifluafile = std::ifstream(glt::file::GetWorkDirectory() / "gluasteal.lua", std::ifstream::binary);
	
	if (!ifluafile.is_open()) { // file doesn't exist
		return true;
	}

	std::stringstream luacodess;
	luacodess << ifluafile.rdbuf();
	ifluafile.close();
	const auto& luacode = luacodess.str();

	luaL_loadbuffer(lua->GetLuaState(), luacode.c_str(), luacode.length(), "gluasteal");

	lua->CreateTable();

	lua->PushString(filename.c_str(), filename.length());
	lua->SetField(-2, "__FILENAME__");

	lua->CreateTable();
		lua->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
		lua->SetField(-2, "__index");
	lua->SetMetaTable(-2);

	lua_setfenv(lua->GetLuaState(), -2);

	if (lua->PCall(0, 1, 0)) {
		g_logger->LogFormat("Lua loader script error\n{}\n\n", lua->GetString(-1));

		lua->Pop(1);
	}
	else {
		if (lua->IsType(-1, GarrysMod::Lua::Type::BOOL)) {
			bool shouldloadfile = lua->GetBool(-1);

			lua->Pop(1);

			return shouldloadfile;
		}

		lua->Pop(1);
	}

	return true;
}
