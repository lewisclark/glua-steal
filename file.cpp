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


#include "file.h"

std::filesystem::path glt::file::GetWorkDirectory() {
	auto home = GetHomeDirectory();

	if (home.empty()) {
		return std::filesystem::path();
	}

	return (home / "gluasteal");
}

std::filesystem::path glt::file::GetHomeDirectory() {
	std::filesystem::path path;

#if (defined(OS_LINUX) || defined(OS_MAC))
	struct passwd* pw = getpwuid(getuid());
	path = std::string(pw->pw_dir);
#elif (defined(OS_WINDOWS))
	PWSTR winpath = nullptr;
	SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_DEFAULT, nullptr, &winpath);

	path = std::wstring(winpath);
#endif

	return path;
}

std::filesystem::path glt::file::GetLogFilePath() {
	return (GetWorkDirectory() / "log.txt");
}

std::filesystem::path glt::file::GetServerStorePath() {
	return (GetWorkDirectory() / "servers");
}

#if (defined(OS_LINUX) || defined(OS_MAC))
static std::vector<std::string> reserved {

};
#elif (defined(OS_WINDOWS))
static std::vector<std::string> reserved {
	"con", "prn", "aux", "nul", "com1", "com2", "com3", "com4", "com5",
	"com6", "com7", "com8", "com9", "com10", "lpt1", "lpt2", "lpt3",
	"lpt4", "lpt5", "lpt6", "lpt7", "lpt8", "lpt9", "lpt10"
};
#endif

static char is_bad_char(char c) {
	if (c >= 0x0 && c <= 0x1f) {
		return true;
	}

	if (c == '_' || c == '-' || c == '.' || c == '/' || c == '\\' || isalnum(c)) {
		return false;
	}

	return true;
}

std::filesystem::path glt::file::SanitizeLuaFilePath(std::string pathstr) {
	std::transform(pathstr.begin(), pathstr.end(), pathstr.begin(), ::tolower);
	pathstr.erase(std::remove_if(pathstr.begin(), pathstr.end(), is_bad_char));

#if (defined(OS_WINDOWS))
	while (!pathstr.empty() && (pathstr.back() == ' ' || pathstr.back() == '.')) {
		pathstr.pop_back();
	}
#endif

	if (pathstr.length() >= 200) {
		return std::filesystem::path("longfilename.lua"); // TODO: Do something better than this
	}

	auto path = std::filesystem::path(pathstr).relative_path();

	if (!path.has_filename()) {
		path.replace_filename("noname");
	}

	if (path.extension() != ".lua") {
		path.replace_extension(".lua");
	}

	auto newpath = std::filesystem::path();

	for (auto& e : path) {
		if (e.filename() == ".." || e.filename() == "." ||
			std::find(reserved.begin(), reserved.end(), e.filename().string()) != reserved.end()) {

			continue;
		}

		newpath /= e;
	}

	return newpath;
}
