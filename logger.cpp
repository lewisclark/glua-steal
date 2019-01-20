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


#include "logger.h"

glt::Logger::Logger(const std::string& filename) {
	m_ofstream = std::ofstream(filename, std::ios_base::app);
}

void glt::Logger::LogString(const std::string& s) {
	m_ofstream << s;
	m_ofstream.flush();
}

std::unique_ptr<glt::Logger> glt::g_logger = nullptr;
