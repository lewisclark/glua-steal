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


#include "luadumper.hpp"

void glt::lua::DumpLua(const std::string& filename, const std::string& code) {
	auto storepath = glt::file::GetServerStorePath();
	std::string strfilename = std::string(filename);

	if (glt::ssdk::g_engineclient->IsConnected()) {
		glt::ssdk::NetChannel* netchannel = glt::ssdk::g_engineclient->GetNetChannelInfo();

		if (netchannel) {
			auto servaddr = std::string(netchannel->GetAddress());
			std::replace(servaddr.begin(), servaddr.end(), '.', '-');
			std::replace(servaddr.begin(), servaddr.end(), ':', '_');

			storepath /= servaddr;
		}
		else {
			storepath /= "unknown";
		}

		storepath /= glt::file::SanitizeLuaFilePath(strfilename);
	}
	else {
		storepath /= "menustate";
		storepath /= glt::file::SanitizeLuaFilePath(strfilename);
	}

	try {
		std::filesystem::create_directories(storepath.parent_path());
	}
	catch (const std::filesystem::filesystem_error& ex) {
		GetLogger()->critical("Failed to create_directories ({})\tpath1 -> {}\tpath2 -> {}",
			ex.what(), ex.path1().string(), ex.path2().string());
		return;
	}

	auto ofluafile = std::ofstream(storepath, std::ofstream::app);
	ofluafile << "-- " << strfilename << "\n";
	ofluafile << "-- Retrieved by https://github.com/c4fe/glua-steal\n";
	ofluafile << code << "\n\n";
	ofluafile.close();
}
