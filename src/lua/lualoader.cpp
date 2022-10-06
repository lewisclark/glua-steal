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

static int include(lua_State*) {
	glt::ssdk::ILuaInterface* lua = glt::ssdk::g_clientluainterface;
	const char* filename = lua->CheckString(-1);

	try {
		glt::lua::RunLua(lua, filename, glt::lua::GetLuaFileContents(filename));
	}
	catch (const std::exception& ex) {
		glt::GetLogger()->warn("Failed to include {}\t{}", filename, ex.what());
	}

	return 0;
}

void glt::lua::RunLua(ssdk::ILuaInterface* lua, const std::string& identifier, const std::string& code,
	const std::string& gfilename, const std::string& gcode) {

	if (luaL_loadbuffer(lua->GetLuaState(), code.c_str(), code.length(), identifier.c_str())) {
		const char* errstr = lua->GetString(-1);
		lua->Pop(1);
		throw std::runtime_error(fmt::format("syntax error '{}'", errstr));
	}

	CreateEnvironment(lua, gfilename, gcode);

	if (lua->PCall(0, 1, 0)) {
		const char* errstr = lua->GetString(-1);
		lua->Pop(1);
		throw std::runtime_error(fmt::format("execution error '{}'", errstr));
	}
}

bool glt::lua::LoadLua(ssdk::ILuaInterface* lua, const std::string& filename, const std::string& code) {
	const auto& loader_file = glt::config::GetConfig().loader_file;

	try {
		RunLua(lua, loader_file, GetLuaFileContents(loader_file), filename, code);
	}
	catch (const std::filesystem::filesystem_error&) { // loader file does not exist, supress exception
		return true;
	}

	if (lua->IsType(-1, GarrysMod::Lua::Type::BOOL)) {
		bool shouldloadfile = lua->GetBool(-1);

		lua->Pop(1);

		return shouldloadfile;
	}

	lua->Pop(1);

	return true;
}

std::string glt::lua::GetLuaFileContents(const std::string& path) {
	return file::ReadFile(path);
}

void glt::lua::CreateEnvironment(ssdk::ILuaInterface* lua, const std::string& filename, const std::string& code) {
	lua->CreateTable(); // env

	lua->CreateTable(); // env.gluasteal
		lua->PushString(filename.c_str(), filename.length());
		lua->SetField(-2, "SCRIPT");

		lua->PushString(code.c_str(), code.length());
		lua->SetField(-2, "SOURCE");

		lua->PushNumber(GLUASTEAL_VERSION);
		lua->SetField(-2, "VERSION");

		lua->PushCFunction(include);
		lua->SetField(-2, "include");
	lua->SetField(-2, "gluasteal");

	lua->CreateTable(); // env metatable
		lua->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
		lua->SetField(-2, "__index");
	lua->SetMetaTable(-2);

	lua_setfenv(lua->GetLuaState(), -2);
}
