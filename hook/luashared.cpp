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


#include "luashared.h"

#if (defined(OS_LINUX) || defined(OS_MAC))
#define CREATELUAINTERFACE_INDEX 5
#define CLOSELUAINTERFACE_INDEX 6
#elif (defined(OS_WINDOWS))
#define CREATELUAINTERFACE_INDEX 4
#define CLOSELUAINTERFACE_INDEX 5
#endif

typedef glt::ssdk::ILuaInterface* (* CreateLuaInterfaceFn)(glt::ssdk::ILuaShared*,
	std::uint8_t, bool);
static CreateLuaInterfaceFn CreateLuaInterfaceOrig = nullptr;

typedef void (* CloseLuaInterfaceFn)(glt::ssdk::ILuaShared*, glt::ssdk::ILuaInterface*);
static CloseLuaInterfaceFn CloseLuaInterfaceOrig = nullptr;

glt::hook::LuaInterfaceHooker* luainterfacehooker;

static glt::ssdk::ILuaInterface* CreateLuaInterfaceHk(glt::ssdk::ILuaShared* thisptr, std::uint8_t c, bool b) {
	glt::ssdk::ILuaInterface* lua = CreateLuaInterfaceOrig(thisptr, c, b);

	if (c == 0) {
		glt::ssdk::g_clientluainterface = lua;

		luainterfacehooker = new glt::hook::LuaInterfaceHooker();
		if (!luainterfacehooker->Hook()) {
			glt::g_logger->LogString("Failed to hook lua interface\n");
			delete luainterfacehooker;
		}

	}

	glt::g_logger->LogFormat("Lua interface {} (0x{:02x}) created\n",
		c, reinterpret_cast<std::uintptr_t>(lua));

	return lua;
}

static void CloseLuaInterfaceHk(glt::ssdk::ILuaShared* thisptr, glt::ssdk::ILuaInterface* lua) {

	if (lua == glt::ssdk::g_clientluainterface) {
		glt::ssdk::g_clientluainterface = nullptr;
		delete luainterfacehooker;
	}

	glt::g_logger->LogFormat("Lua interface 0x{:02x} closing\n",
		reinterpret_cast<std::uintptr_t>(lua));

	CloseLuaInterfaceOrig(thisptr, lua);
}

bool glt::hook::LuaSharedHooker::Hook() {
	auto luashared = reinterpret_cast<std::uintptr_t**>(ssdk::g_luashared);

	if (!luashared) {
		return false;
	}

	g_logger->LogFormat("LUASHARED003 -> 0x{:02x}\n",
		reinterpret_cast<std::uintptr_t>(luashared));

	auto vt = CreateVTHook(luashared);

	CreateLuaInterfaceOrig = vt->HookMethod<CreateLuaInterfaceFn>(
		reinterpret_cast<std::uintptr_t>(CreateLuaInterfaceHk), CREATELUAINTERFACE_INDEX);

	CloseLuaInterfaceOrig = vt->HookMethod<CloseLuaInterfaceFn>(
		reinterpret_cast<std::uintptr_t>(CloseLuaInterfaceHk), CLOSELUAINTERFACE_INDEX);

	return (CreateLuaInterfaceOrig && CloseLuaInterfaceOrig);
}
