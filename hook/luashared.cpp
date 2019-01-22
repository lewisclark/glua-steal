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

typedef glt::ssdk::ILuaInterface* (__THISCALL__* CreateLuaInterfaceFn)(glt::ssdk::ILuaShared*,
	std::uint8_t, bool);
static CreateLuaInterfaceFn CreateLuaInterfaceOrig = nullptr;

typedef void (__THISCALL__* CloseLuaInterfaceFn)(glt::ssdk::ILuaShared*, glt::ssdk::ILuaInterface*);
static CloseLuaInterfaceFn CloseLuaInterfaceOrig = nullptr;

static glt::ssdk::ILuaInterface* __FASTCALL__ CreateLuaInterfaceHk(glt::ssdk::ILuaShared* thisptr,
		std::uintptr_t*, std::uint8_t c, bool b) {

	glt::ssdk::ILuaInterface* lua = CreateLuaInterfaceOrig(thisptr, c, b);

	if (c == 0) {
		glt::ssdk::g_clientluainterface = lua;
	}

	glt::g_logger->LogFormat("Lua interface {} (0x{:02x}) created\n",
		c, reinterpret_cast<std::uintptr_t>(lua));

	return lua;
}

static void __FASTCALL__ CloseLuaInterfaceHk(glt::ssdk::ILuaShared* thisptr, std::uintptr_t*,
	glt::ssdk::ILuaInterface* lua) {

	if (lua == glt::ssdk::g_clientluainterface) {
		glt::ssdk::g_clientluainterface = nullptr;
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

	auto vt = CreateVTHook(luashared);

	CreateLuaInterfaceOrig = vt->HookMethod<CreateLuaInterfaceFn>(
		reinterpret_cast<std::uintptr_t>(CreateLuaInterfaceHk), 4);

	CloseLuaInterfaceOrig = vt->HookMethod<CloseLuaInterfaceFn>(
		reinterpret_cast<std::uintptr_t>(CloseLuaInterfaceHk), 5);

	return (CreateLuaInterfaceOrig && CloseLuaInterfaceOrig);
}
