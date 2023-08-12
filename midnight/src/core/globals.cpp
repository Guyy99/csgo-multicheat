#include "globals.h"

#include <iostream>

CEntity* globals::UpdateLocalPlayer()
{
	const std::uint32_t localPlayerIndex = interfaces::engine->GetLocalPlayerIndex();
	return interfaces::EntityList->GetClientEntityFromID(localPlayerIndex);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE; // skip to next window

	gameWindow::game_window = handle;
	return FALSE; // window found abort search

}

void globals::FindProcessWindow()
{
	gameWindow::game_window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);

}