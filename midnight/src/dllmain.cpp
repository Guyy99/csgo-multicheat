#include <windows.h>
#include <cstdio>
#include <iostream>

#include "core/interfaces.h"
#include "core/hooks.h"
#include "core/globals.h"
#include "core/gui.h"
#include "core/settings.h"
#include "valve/centity.h"
#include "valve/cmatrix.h"


DWORD hackMain(HMODULE hModule)
{
	FILE* f;
	AllocConsole();
	freopen_s(&f, "CONOUT$", "w", stdout);	

	skins::pop_skin_list();

	interfaces::Setup();
	hooks::Setup();
	

	bool bRunning = true;

	while (bRunning)
	{
		if (GetAsyncKeyState(VK_F9))
			bRunning = false;

		if (GetAsyncKeyState(VK_DELETE))
			settings::menuOpen = !settings::menuOpen;

		Sleep(100);
	}

	hooks::Remove();
	gui::Destroy();

	Sleep(1000);
	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;

}



BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hModule);
	if (fdwReason == DLL_PROCESS_ATTACH)
		if (const auto threadHandle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)hackMain, hModule, 0, nullptr))
			CloseHandle(threadHandle);
	return TRUE;
}
