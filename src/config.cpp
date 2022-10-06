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


#include "config.hpp"

static glt::config::Config cfg;

void glt::config::LoadConfig() {
	glt::file::CreateConfig();

	const auto& logger = GetLogger();

	try {
		const auto t = toml::parse(glt::file::GetConfigFilePath());

		if (t.contains("stealer")) {
			const auto& table_stealer = toml::find(t, "stealer");

			if (table_stealer.contains("enabled")) {
				const auto stealer_enabled = toml::find(table_stealer, "enabled");

				if (stealer_enabled.is_boolean()) {
					cfg.stealer_enabled = toml::get<bool>(stealer_enabled);
				}
			}
		}

		if (t.contains("loader")) {
			const auto& table_loader = toml::find(t, "loader");

			if (table_loader.contains("file")) {
				const auto& loader_file = toml::find(table_loader, "file");

				if (loader_file.is_string()) {
					cfg.loader_file = toml::get<std::string>(loader_file);
				}
			}
		}

		logger->info("Config loaded");

		logger->debug("stealer.enabled = {}, loader.file = {}", cfg.stealer_enabled, cfg.loader_file);
	}
	catch (const std::exception& ex) {
		logger->error("Failed to parse config!");
		logger->error(ex.what());
	}
}

const glt::config::Config glt::config::GetConfig() {
	return cfg;
}
