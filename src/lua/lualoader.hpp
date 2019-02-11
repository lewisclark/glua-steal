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

#include <fstream>
#include <sstream>

#include "luaexports.hpp"
#include "logger.hpp"
#include "file/file.hpp"

namespace glt::lua {
	// For running our own lua in a seperate environment
	// TODO: Too many args. Refactor.
	void RunLua(ssdk::ILuaInterface* lua, const std::string& identifier, const std::string& code,
		const std::string& gfilename = "", const std::string& gcode = "");

	// Called by RunStringEx to determine if the lua file 'filename' should be blocked from executing
	// Returns false if we should not load the current file (filename)
	bool LoadLua(ssdk::ILuaInterface* lua, const std::string& filename, const std::string& code);
	std::string GetLuaFileContents(const std::string& path = "gluasteal.lua"); // Returns the lua code to run

	// filename and code are the variables to be filled by RunStringEx to indicate the garrys mod lua file
	void CreateEnvironment(ssdk::ILuaInterface* lua, const std::string& filename, const std::string& code);
}

#endif
