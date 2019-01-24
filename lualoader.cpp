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

bool glt::lua::LuaLoader::LoadLua(glt::ssdk::ILuaInterface* lua, const std::string&) {
	if (m_env == -1 || m_envmt == -1) {
		CreateTables(lua);
	}

	auto ifluafile = std::ifstream(glt::file::GetWorkDirectory() / "run.lua", std::ifstream::binary);
	
	if (!ifluafile.is_open()) { // file doesn't exist
		return true;
	}

	std::stringstream luacodess;
	luacodess << ifluafile.rdbuf();
	const auto& luacode = luacodess.str();

	luaL_loadbuffer(lua->GetLuaState(), luacode.c_str(), luacode.length(), "weewoo");
	lua->ReferencePush(m_env);
	lua->ReferencePush(m_envmt);
	lua->SetMetaTable(-2);
	lua_setfenv(lua->GetLuaState(), -2);
	lua->Call(0, 0);

	return true;
}

void glt::lua::LuaLoader::CreateTables(glt::ssdk::ILuaInterface* lua) {
	lua->CreateTable();
		lua->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
		lua->SetField(-2, "__index");
	m_envmt = lua->ReferenceCreate();

	lua->CreateTable();
	m_env = lua->ReferenceCreate();
}

std::unique_ptr<glt::lua::LuaLoader> glt::lua::g_lualoader = nullptr;
