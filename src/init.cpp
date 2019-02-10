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


#include "init.hpp"

static glt::hook::LuaSharedHooker luasharedhooker;

void glt::Init() {
	const auto& workdir = glt::file::GetWorkDirectory();
	std::filesystem::create_directories(workdir);

	g_logger = std::make_unique<Logger>(glt::file::GetLogFilePath().string());
	g_logger->LogFormat("Initializing gluasteal v{:.1f}\n", GLUASTEAL_VERSION);

	try {
		const auto& libengine = lib::Library("engine");
		const auto& libluashared = lib::Library("garrysmod/bin/lua_shared");

		ssdk::g_engineclient = libengine.GetInterface<ssdk::IVEngineClient>("VEngineClient015");
		ssdk::g_luashared = libluashared.GetInterface<ssdk::ILuaShared>("LUASHARED003");

		lua::GetExports();

		luasharedhooker.Hook();
	}
	catch (const std::exception& ex) {
		g_logger->LogFormat("Failed to initialize: {}", ex.what());
		return;
	}

	g_logger->LogString("Successfully initialized.\nJoin a server to retrieve the lua files.\n");
	g_logger->LogFormat("Lua files will be saved to '{}'\n", file::GetServerStorePath().string());

	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1)); // Keep alive
	}
}
