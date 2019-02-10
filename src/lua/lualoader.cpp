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


#include "lualoader.hpp"

bool glt::lua::LoadLua(ssdk::ILuaInterface* lua, const std::string& filename) {
	const std::string& luacode = GetLuaFileContents();

	if (luaL_loadbuffer(lua->GetLuaState(), luacode.c_str(), luacode.length(), "gluasteal")) {
		throw std::runtime_error(fmt::format("syntax error '{}'", lua->GetString(-1)));
	}

	CreateEnvironment(lua, filename);

	if (lua->PCall(0, 1, 0)) {
		throw std::runtime_error(fmt::format("execution error '{}'", lua->GetString(-1)));
	}
	else if (lua->IsType(-1, GarrysMod::Lua::Type::BOOL)) {
		bool shouldloadfile = lua->GetBool(-1);

		lua->Pop(1);

		return shouldloadfile;
	}

	lua->Pop(1);

	return true;
}

std::string glt::lua::GetLuaFileContents() {
	try {
		return file::ReadFile("gluasteal.lua");
	}
	catch (const std::exception&) {
		return "--";
	}
}

void glt::lua::CreateEnvironment(ssdk::ILuaInterface* lua, const std::string& filename) {
	lua->CreateTable();

	lua->PushString(filename.c_str(), filename.length());
	lua->SetField(-2, "SCRIPT");

	lua->CreateTable();
		lua->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
		lua->SetField(-2, "__index");
	lua->SetMetaTable(-2);

	lua_setfenv(lua->GetLuaState(), -2);
}
