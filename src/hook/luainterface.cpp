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
#if (defined(OS_LINUX) || defined(OS_MAC) || (defined(OS_WINDOWS) && defined(ARCH_64BIT)))
typedef bool (* RunStringExFn)(glt::ssdk::ILuaInterface*, const char*, const char*, const char*,
	bool, bool, bool, bool);
#elif (defined(OS_WINDOWS) && defined(ARCH_32BIT))
typedef bool (__THISCALL__* RunStringExFn)(glt::ssdk::ILuaInterface*, const char*, const char*, const char*,
	bool, bool, bool, bool);
#endif
static RunStringExFn RunStringExOrig = nullptr;

// TODO: Tidy this up
#if (defined(OS_LINUX) || defined(OS_MAC) || (defined(OS_WINDOWS) && defined(ARCH_64BIT)))
static bool RunStringExHk(glt::ssdk::ILuaInterface* thisptr,
#elif (defined(OS_WINDOWS) && defined(ARCH_32BIT))
static bool __FASTCALL__ RunStringExHk(glt::ssdk::ILuaInterface* thisptr, std::uintptr_t*,
#endif
	const char* filename, const char* path, const char* buf, bool b1, bool b2, bool b3, bool b4) {

	std::string strfilename = filename;
	std::string strcode = buf;

	bool load = true;
	bool dump = true;
	try {
		auto ret = glt::lua::LoadLua(thisptr, strfilename, strcode);

		if (!std::get<0>(ret)) {
			glt::GetLogger()->debug("Blocked the execution of {}", strfilename);
			load = false;
		}

		if (!std::get<1>(ret)) {
			glt::GetLogger()->debug("Blocked the dumping of {}", strfilename);
			dump = false;
		}
	}
	catch (const std::exception& ex) {
		glt::GetLogger()->warn("Failed to run lua file\t{}", ex.what());
	}

	bool ret = false;
	if (load) {
		ret = RunStringExOrig(thisptr, filename, path, buf, b1, b2, b3, b4);
	}

	if (glt::config::GetConfig().stealer_enabled && dump)
		glt::lua::DumpLua(std::move(strfilename), std::move(strcode));

	return ret;
}

void glt::hook::LuaInterfaceHooker::Hook() {
	auto luainterface = reinterpret_cast<std::uintptr_t**>(ssdk::g_clientluainterface);
	auto vt = CreateVTHook(luainterface);

	RunStringExOrig = vt->HookMethod<RunStringExFn>(reinterpret_cast<std::uintptr_t>(RunStringExHk), 111);

	if (!RunStringExOrig) {
		throw std::runtime_error("failed to hook RunStringEx");
	}
}
