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


#include "luainterface.hpp"

// TODO: Tidy this up
#if (defined(OS_LINUX) || defined(OS_MAC))
typedef bool (* RunStringExFn)(glt::ssdk::ILuaInterface*, const char*, const char*, const char*,
	bool, bool, bool, bool);
#elif (defined(OS_WINDOWS))
typedef bool (__THISCALL__* RunStringExFn)(glt::ssdk::ILuaInterface*, const char*, const char*, const char*,
	bool, bool, bool, bool);
#endif
static RunStringExFn RunStringExOrig = nullptr;

// TODO: Tidy this up
#if (defined(OS_LINUX) || defined(OS_MAC))
static bool RunStringExHk(glt::ssdk::ILuaInterface* thisptr,
#elif (defined(OS_WINDOWS))
static bool __FASTCALL__ RunStringExHk(glt::ssdk::ILuaInterface* thisptr, std::uintptr_t*,
#endif
	const char* filename, const char* path, const char* buf, bool b1, bool b2, bool b3, bool b4) {

	auto luapath = glt::file::GetServerStorePath();
	std::string strfilename = std::string(filename);

	if (glt::ssdk::g_engineclient->IsConnected()) {
		glt::ssdk::NetChannel* netchannel = glt::ssdk::g_engineclient->GetNetChannelInfo();

		if (netchannel) {
			auto servaddr = std::string(netchannel->GetAddress());
			std::replace(servaddr.begin(), servaddr.end(), '.', '-');
			std::replace(servaddr.begin(), servaddr.end(), ':', '_');

			luapath /= servaddr;
		}
		else {
			luapath /= "unknown";
		}

		luapath /= glt::file::SanitizeLuaFilePath(strfilename);
	}
	else {
		luapath /= "menustate";
		luapath /= glt::file::SanitizeLuaFilePath(strfilename);
	}

	std::filesystem::create_directories(luapath.parent_path());

	auto ofluafile = std::ofstream(luapath, std::ofstream::app);
	ofluafile << "-- " << strfilename << "\n";
	ofluafile << "-- Retrieved by https://github.com/lewez/glua-steal\n";
	ofluafile << buf << "\n\n";
	ofluafile.close();

	if (!glt::lua::LoadLua(thisptr, strfilename)) {
		glt::g_logger->LogFormat("Blocked the execution of {}\n", strfilename);

		return false;
	}

	return RunStringExOrig(thisptr, filename, path, buf, b1, b2, b3, b4);
}

void glt::hook::LuaInterfaceHooker::Hook() {
	auto luainterface = reinterpret_cast<std::uintptr_t**>(ssdk::g_clientluainterface);
	auto vt = CreateVTHook(luainterface);

	RunStringExOrig = vt->HookMethod<RunStringExFn>(reinterpret_cast<std::uintptr_t>(RunStringExHk), 111);

	if (!RunStringExOrig) {
		throw std::runtime_error("failed to hook RunStringEx");
	}
}
