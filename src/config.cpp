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

#include <algorithm>
#include <cctype>

static glt::config::Config cfg;

glt::config::StealerWriteMode glt::config::ParseStealerWriteMode(std::string write_mode) {
	std::transform(write_mode.begin(), write_mode.end(), write_mode.begin(), [](unsigned char c) {
		return static_cast<char>(std::tolower(c));
	});

	if (write_mode == "append")
		return StealerWriteMode::Append;

	if (write_mode == "once")
		return StealerWriteMode::Once;

	return StealerWriteMode::Truncate;
}

const char* glt::config::GetStealerWriteModeName(StealerWriteMode write_mode) {
	switch (write_mode) {
		case StealerWriteMode::Append:
			return "append";
		case StealerWriteMode::Once:
			return "once";
		default:
			return "truncate";
	}
}

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

			if (table_stealer.contains("write_mode")) {
				const auto stealer_write_mode = toml::find(table_stealer, "write_mode");

				if (stealer_write_mode.is_string()) {
					cfg.stealer_write_mode = ParseStealerWriteMode(toml::get<std::string>(stealer_write_mode));
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

		if (t.contains("logger")) {
			const auto& table_logger = toml::find(t, "logger");

			if (table_logger.contains("level")) {
				const auto& logger_level = toml::find(table_logger, "level");

				if (logger_level.is_string()) {
					auto level = toml::get<std::string>(logger_level);

					std::transform(level.begin(), level.end(), level.begin(), [](unsigned char c) {
						return static_cast<char>(std::tolower(c));
					});

					if (level == "trace")
						cfg.logger_level = spdlog::level::trace;
					else if (level == "debug")
						cfg.logger_level = spdlog::level::debug;
					else if (level == "warn")
						cfg.logger_level = spdlog::level::warn;
					else if (level == "error")
						cfg.logger_level = spdlog::level::err;
					else if (level == "critical")
						cfg.logger_level = spdlog::level::critical;
					else
						cfg.logger_level = spdlog::level::info;
				}
			}
		}

		spdlog::set_level(cfg.logger_level);

		logger->debug("Config loaded");

		logger->debug(
			"stealer.enabled = {}, stealer.write_mode = {}, loader.file = {}, logger.level = {}",
			cfg.stealer_enabled,
			GetStealerWriteModeName(cfg.stealer_write_mode),
			cfg.loader_file,
			spdlog::level::to_string_view(cfg.logger_level)
		);
	}
	catch (const std::exception& ex) {
		logger->error("Failed to parse config!");
		logger->error(ex.what());
	}
}

const glt::config::Config glt::config::GetConfig() {
	return cfg;
}
