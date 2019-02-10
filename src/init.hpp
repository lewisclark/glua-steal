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


#ifndef INIT_H
#define INIT_H

#include <cinttypes>
#include <thread>

#include "logger.hpp"
#include "file/file.hpp"
#include "library/library.hpp"

#include "lua/luaexports.hpp"

#include "gamesdk/IVEngineClient.hpp"
#include "gamesdk/ILuaShared.hpp"
#include "gamesdk/ILuaInterface.hpp"

#include "hook/luashared.hpp"
#include "hook/luainterface.hpp"

namespace glt {
	void Init();
}

#endif
