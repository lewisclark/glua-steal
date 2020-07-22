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


#ifndef LUADUMPER_H
#define LUADUMPER_H

#include <mutex>
#include "logger.hpp"
#include "file/file.hpp"
#include "file/sanitization.hpp"
#include "gamesdk/IVEngineClient.hpp"

namespace glt::lua {
	struct LuaDumperEntry {
		LuaDumperEntry(std::string server_name, std::string filename, std::string code) :
			server_name(server_name), filename(filename), code(code) {}

		std::string server_name;
		std::string filename;
		std::string code;
	};

	std::thread Init();
	void DumpLua(std::string filename, std::string code);
	void IoThread();
}

#endif
