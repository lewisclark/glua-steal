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


#include "os.hpp"
#include "init.hpp"

#if (defined(OS_LINUX) || defined(OS_MAC))
#include <pthread.h>

#ifdef OS_MAC
#include <stdlib.h>
#endif

void* InitWrap(void*) {
	glt::Init();

	return nullptr;
}

std::string get_process_name() {
#ifdef OS_MAC
	return std::string(getprogname());
#else
	return std::string(program_invocation_short_name);
#endif
}

bool is_game_process() {
	std::string proc_name = get_process_name();

	return proc_name == "gmod" || proc_name == "hl2_linux";
}

void __attribute__((constructor)) glt_main() {
	if (!is_game_process()) {
		return;
	}

	pthread_t th;
	pthread_create(&th, NULL, InitWrap, NULL);
	pthread_detach(th);
}

int __attribute__((destructor)) glt_kill() {
	return 0;
}

#endif



#ifdef OS_WINDOWS
#include <windows.h>

BOOL APIENTRY DllMain(HINSTANCE lib, DWORD reason, LPVOID) {
	switch (reason) {
		case DLL_PROCESS_ATTACH: {
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)glt::Init, 0, 0, 0);

			return true;
		}
		case DLL_PROCESS_DETACH: {
			return true;
		}
	}

	return false;
}
#endif
