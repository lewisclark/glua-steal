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


#include "init.h"

std::uintptr_t* glt::Init(std::uintptr_t*) {
	auto workdir = glt::file::GetWorkDirectory();

	if (workdir.empty()) {
		return nullptr;
	}

	std::filesystem::create_directories(workdir);

	g_logger = std::make_unique<Logger>(glt::file::GetLogFilePath().string());
	g_logger->LogString("Initializing...\n");

	ssdk::g_engineclient = ssdk::GetInterface<ssdk::IVEngineClient>("engine", "VEngineClient015");

	if (!ssdk::g_engineclient) {
		g_logger->LogString("Failed to grab VEngineClient interface\n");

		return nullptr;
	}

	if (!hook::Init()) {
		g_logger->LogString("Failed to initialize hooks!\n");

		return nullptr;
	}

	g_logger->LogString("Successfully initialized\n");

	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1)); // Keep alive
	}

	return nullptr;
}
