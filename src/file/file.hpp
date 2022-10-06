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


#include <filesystem>
#include <fstream>
#include <sstream>

#include "os.hpp"
#include "logger.hpp"

#if (defined(OS_LINUX) || defined(OS_MAC))
	#include <unistd.h>
	#include <sys/types.h>
	#include <pwd.h>
#elif (defined(OS_WINDOWS))
	#include <shlobj_core.h>
#endif

namespace glt::file {
	std::filesystem::path GetWorkDirectory(); // Returns a path where everything is stored
	std::filesystem::path GetHomeDirectory();
	std::filesystem::path GetLogFilePath();
	std::filesystem::path GetConfigFilePath();
	std::filesystem::path GetServerStorePath();
	std::string ReadFile(const std::string& path); // Relative to work directory
	void CreateConfig();
}
