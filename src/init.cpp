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
	std::filesystem::create_directories(glt::file::GetWorkDirectory());
	InitLogger();

	const auto& logger = GetLogger();
	logger->info("Initializing gluasteal v{:.1f}", GLUASTEAL_VERSION);

	while (true) {
		try {
			lib::Library("engine").GetInterface<ssdk::IVEngineClient>("VEngineClient015");
			lib::Library("lua_shared").GetInterface<ssdk::ILuaShared>("LUASHARED003");
			break;
		}
		catch (const std::exception& ex) {}

		std::this_thread::sleep_for(std::chrono::seconds(3));
	}

	try {
		const auto& libengine = lib::Library("engine");
		const auto& libluashared = lib::Library("lua_shared");

		ssdk::g_engineclient = libengine.GetInterface<ssdk::IVEngineClient>("VEngineClient015");
		ssdk::g_luashared = libluashared.GetInterface<ssdk::ILuaShared>("LUASHARED003");

		lua::GetExports();

		luasharedhooker.Hook();
	}
	catch (const std::exception& ex) {
		logger->critical("Failed to initialize: {}", ex.what());
		return;
	}

	logger->info("Successfully initialized");
	logger->info("Join a server to retrieve the lua files");
	logger->info("Lua files will be saved to '{}'", file::GetServerStorePath().string());

	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1)); // Keep alive
	}
}
