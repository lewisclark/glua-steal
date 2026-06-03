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

#include <cstdlib>
#include <optional>

static int include(lua_State*) {
	glt::ssdk::ILuaInterface* lua = glt::ssdk::g_clientluainterface;
	const char* filename = lua->CheckString(-1);

	try {
		glt::lua::RunLua(lua, filename, glt::lua::GetLuaFileContents(filename), "", "", 0);
	}
	catch (const std::exception& ex) {
		glt::GetLogger()->warn("Failed to include {}\t{}", filename, ex.what());
	}

	return 0;
}

static std::optional<std::string> get_environment_value(const char* key) {
#ifdef OS_WINDOWS
	char* value = nullptr;
	size_t length = 0;
	if (_dupenv_s(&value, &length, key) != 0 || value == nullptr) {
		return std::nullopt;
	}

	std::string result(value, length > 0 ? length - 1 : 0);
	free(value);
	return result;
#else
	const char* value = std::getenv(key);
	if (!value) {
		return std::nullopt;
	}

	return std::string(value);
#endif
}

static int getenv_fn(lua_State*) {
	glt::ssdk::ILuaInterface* lua = glt::ssdk::g_clientluainterface;
	const char* key = lua->CheckString(-1);
	const auto value = get_environment_value(key);

	if (value.has_value()) {
		lua->PushString(value->c_str(), static_cast<unsigned int>(value->length()));
	}
	else {
		lua->PushNil();
	}

	return 1;
}

void glt::lua::RunLua(ssdk::ILuaInterface* lua, const std::string& identifier, const std::string& code,
	const std::string& gfilename, const std::string& gcode, int results) {

	if (luaL_loadbuffer(lua->GetLuaState(), code.c_str(), code.length(), identifier.c_str())) {
		const char* errstr = lua->GetString(-1);
		lua->Pop(1);
		throw std::runtime_error(fmt::format("syntax error '{}'", errstr));
	}

	CreateEnvironment(lua, gfilename, gcode);

	if (lua->PCall(0, results, 0)) {
		const char* errstr = lua->GetString(-1);
		lua->Pop(1);
		throw std::runtime_error(fmt::format("execution error '{}'", errstr));
	}
}

glt::lua::LoaderResult glt::lua::LoadLua(ssdk::ILuaInterface* lua, const std::string& filename, const std::string& code) {
	const auto& loader_file = glt::config::GetConfig().loader_file;
	LoaderResult result;

	try {
		RunLua(lua, loader_file, GetLuaFileContents(loader_file), filename, code, 2);
	}
	catch (const std::filesystem::filesystem_error&) { // loader file does not exist, supress exception
		return result;
	}

	if (lua->IsType(-1, GarrysMod::Lua::Type::BOOL)) {
		result.should_write = lua->GetBool(-1);
	}

	if (lua->IsType(-2, GarrysMod::Lua::Type::BOOL)) {
		result.should_load = lua->GetBool(-2);
	}

	lua->Pop(2);

	return result;
}

std::string glt::lua::GetLuaFileContents(const std::string& path) {
	return file::ReadFile(path);
}

void glt::lua::CreateEnvironment(ssdk::ILuaInterface* lua, const std::string& filename, const std::string& code) {
	lua->CreateTable(); // env

	lua->CreateTable(); // env.gluasteal
		lua->PushString(filename.c_str(), static_cast<unsigned int>(filename.length()));
		lua->SetField(-2, "SCRIPT");

		lua->PushString(code.c_str(), static_cast<unsigned int>(code.length()));
		lua->SetField(-2, "SOURCE");

		lua->PushNumber(GLUASTEAL_VERSION);
		lua->SetField(-2, "VERSION");

		lua->PushCFunction(include);
		lua->SetField(-2, "include");

		lua->PushCFunction(getenv_fn);
		lua->SetField(-2, "getenv");
	lua->SetField(-2, "gluasteal");

	lua->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	lua->GetField(-1, "os");
	lua->CreateTable();
		lua->PushCFunction(getenv_fn);
		lua->SetField(-2, "getenv");
		if (lua->IsType(-2, GarrysMod::Lua::Type::TABLE)) {
			lua->CreateTable();
				lua->Push(-3);
				lua->SetField(-2, "__index");
			lua->SetMetaTable(-2);
		}
	lua->SetField(-4, "os");
	lua->Pop(2);

	lua->CreateTable(); // env metatable
		lua->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
		lua->SetField(-2, "__index");
	lua->SetMetaTable(-2);

	lua_setfenv(lua->GetLuaState(), -2);
}
