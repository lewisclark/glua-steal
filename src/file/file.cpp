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


#include "file.hpp"

std::filesystem::path glt::file::GetWorkDirectory() {
	const auto& home = GetHomeDirectory();

	if (home.empty()) {
		throw std::filesystem::filesystem_error("home directory path is empty", std::error_code());
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

std::string glt::file::ReadFile(const std::string& path) {
	auto iff = std::ifstream(GetWorkDirectory() / path);

	if (!iff.is_open()) {
		throw std::filesystem::filesystem_error("file does not exist", std::error_code());
	}

	std::stringstream ss;
	ss << iff.rdbuf();
	iff.close();

	return ss.str();
}
