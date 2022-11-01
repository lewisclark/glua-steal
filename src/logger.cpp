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


#include "logger.hpp"

static std::shared_ptr<spdlog::logger> logger = nullptr;

void glt::InitLogger() {
	spdlog::flush_every(std::chrono::seconds(1));
	spdlog::set_pattern("[%d-%m-%C - %T.%e] [%l] %v");

	const auto& logpath = file::GetLogFilePath();

	logger = spdlog::basic_logger_mt("gluasteal", logpath.string());
}

spdlog::logger* glt::GetLogger() {
	return logger.get();
}
