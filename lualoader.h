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


#ifndef LUALOADER_H
#define LUALOADER_H

#include <memory>
#include <cinttypes>
#include <fstream>
#include <sstream>

#include "logger.h"
#include "luaexports.h"
#include "file.h"

#include "gamesdk/ILuaInterface.h"

namespace glt::lua {
	class LuaLoader {
		public:
		// Returns false if we should not load the current file
		bool LoadLua(ssdk::ILuaInterface* lua, const std::string& filename);

		private:
		void CreateTables(ssdk::ILuaInterface* lua);

		int m_env = -1;
		int m_envmt = -1;
	};

	extern std::unique_ptr<LuaLoader> g_lualoader;
}

#endif
