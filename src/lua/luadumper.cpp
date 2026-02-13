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

static std::vector<glt::lua::LuaDumperEntry> entry_buffer;

static std::mutex mtx;
static std::vector<glt::lua::LuaDumperEntry> shared_entries;

void glt::lua::DumpLua(std::string filename, std::string code) {
	std::string server_name;
	if (glt::ssdk::g_engineclient->IsConnected()) {
		auto netchannel = glt::ssdk::g_engineclient->GetNetChannelInfo();

		server_name = netchannel ? netchannel->GetAddress() : "unknown";
	} else {
		server_name = "menustate";
	}

	entry_buffer.emplace_back(std::move(server_name), std::move(filename), std::move(code));

	std::unique_lock<std::mutex> lock{mtx, std::try_to_lock};
	if (lock.owns_lock()) {
		std::move(entry_buffer.begin(), entry_buffer.end(), std::back_inserter(shared_entries));
		entry_buffer.clear();
	}
}

void glt::lua::IoThread() {
	const auto& storepath = glt::file::GetServerStorePath();

	while (true) {
		{
			std::lock_guard<std::mutex> lock{mtx};

			if (!shared_entries.empty()) {
				for (auto& entry : shared_entries) {
					auto& server_name = entry.server_name;
					std::replace(server_name.begin(), server_name.end(), '.', '-');
					std::replace(server_name.begin(), server_name.end(), ':', '_');

					auto sanitized_filename = glt::file::SanitizeLuaFilePath(entry.filename);

					auto path = storepath;
					path /= server_name;
					path /= sanitized_filename;

					try {
						std::filesystem::create_directories(path.parent_path());
					}
					catch (const std::filesystem::filesystem_error& ex) {
						GetLogger()->critical("Failed to create_directories ({})\tpath1 -> {}\tpath2 -> {}",
							ex.what(), ex.path1().string(), ex.path2().string());
						continue;
					}

					auto of = std::ofstream(path, glt::config::GetConfig().stealer_write_mode | std::ofstream::binary);
					of << "-- " << sanitized_filename << std::endl;
					of << "-- Retrieved by https://github.com/lewisclark/glua-steal" << std::endl;
					of << entry.code << std::endl;
				}

				shared_entries.clear();
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
