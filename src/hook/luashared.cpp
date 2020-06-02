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


#include "luashared.hpp"

#if (defined(OS_LINUX) || defined(OS_MAC))
#define CREATELUAINTERFACE_INDEX 5
#define CLOSELUAINTERFACE_INDEX 6
#elif (defined(OS_WINDOWS))
#define CREATELUAINTERFACE_INDEX 4
#define CLOSELUAINTERFACE_INDEX 5
#endif

#if (defined(OS_LINUX) || defined(OS_MAC) || (defined(OS_WINDOWS) && defined(ARCH_64BIT)))
typedef glt::ssdk::ILuaInterface* (* CreateLuaInterfaceFn)(glt::ssdk::ILuaShared*, std::uint8_t, bool);
typedef void (* CloseLuaInterfaceFn)(glt::ssdk::ILuaShared*, glt::ssdk::ILuaInterface*);
#elif (defined(OS_WINDOWS) && defined(ARCH_32BIT))
typedef glt::ssdk::ILuaInterface* (__THISCALL__* CreateLuaInterfaceFn)(glt::ssdk::ILuaShared*, std::uint8_t, bool);
typedef void (__THISCALL__* CloseLuaInterfaceFn)(glt::ssdk::ILuaShared*, glt::ssdk::ILuaInterface*);
#endif
static CreateLuaInterfaceFn CreateLuaInterfaceOrig = nullptr;
static CloseLuaInterfaceFn CloseLuaInterfaceOrig = nullptr;

glt::hook::LuaInterfaceHooker* luainterfacehooker;

#if (defined(OS_LINUX) || defined(OS_MAC) || (defined(OS_WINDOWS) && defined(ARCH_64BIT)))
static glt::ssdk::ILuaInterface* CreateLuaInterfaceHk(glt::ssdk::ILuaShared* thisptr, std::uint8_t c, bool b) {
#elif (defined(OS_WINDOWS) && defined(ARCH_32BIT))
static glt::ssdk::ILuaInterface* __FASTCALL__ CreateLuaInterfaceHk(glt::ssdk::ILuaShared* thisptr, std::uintptr_t*, std::uint8_t c, bool b) {
#endif
	glt::ssdk::ILuaInterface* lua = CreateLuaInterfaceOrig(thisptr, c, b);

	if (c == 0) {
		glt::ssdk::g_clientluainterface = lua;

		luainterfacehooker = new glt::hook::LuaInterfaceHooker();
		luainterfacehooker->Hook();
	}

	return lua;
}

#if (defined(OS_LINUX) || defined(OS_MAC) || (defined(OS_WINDOWS) && defined(ARCH_64BIT)))
static void CloseLuaInterfaceHk(glt::ssdk::ILuaShared* thisptr, glt::ssdk::ILuaInterface* lua) {
#elif (defined(OS_WINDOWS) && defined(ARCH_32BIT))
static void __FASTCALL__ CloseLuaInterfaceHk(glt::ssdk::ILuaShared* thisptr, std::uintptr_t*, glt::ssdk::ILuaInterface* lua) {
#endif
	if (lua == glt::ssdk::g_clientluainterface) {
		glt::ssdk::g_clientluainterface = nullptr;
		delete luainterfacehooker;
	}

	CloseLuaInterfaceOrig(thisptr, lua);
}

void glt::hook::LuaSharedHooker::Hook() {
	auto luashared = reinterpret_cast<std::uintptr_t**>(ssdk::g_luashared);
	auto vt = CreateVTHook(luashared);

	CreateLuaInterfaceOrig = vt->HookMethod<CreateLuaInterfaceFn>(
		reinterpret_cast<std::uintptr_t>(CreateLuaInterfaceHk), CREATELUAINTERFACE_INDEX);

	CloseLuaInterfaceOrig = vt->HookMethod<CloseLuaInterfaceFn>(
		reinterpret_cast<std::uintptr_t>(CloseLuaInterfaceHk), CLOSELUAINTERFACE_INDEX);

	if (!CreateLuaInterfaceOrig || !CloseLuaInterfaceOrig) {
		throw std::runtime_error("failed to hook CreateLuaInterface/CloseLuaInterface");
	}
}
