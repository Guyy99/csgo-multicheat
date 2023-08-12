#pragma once

#include <Windows.h>
#include <iostream>

#include "../ext/imgui/backends/imgui_impl_dx9.h"
#include "../ext/imgui/backends/imgui_impl_win32.h"
#include "../valve/offsets.h"
#include "../core/settings.h"
#include "../core/globals.h"
#include "../hacks/skin_changer.h"

namespace gui
{
	enum windows
	{
		COMBAT,
		VISUALS,
		MISC
	};

	void Setup(IDirect3DDevice9* device);
	void Render();
	void Destroy();

	LRESULT __stdcall user_wndproc(HWND window, UINT message_type, WPARAM w_param, LPARAM l_param);

	inline bool initialized = false;
	inline int screen = COMBAT;

}

namespace gameWindow
{
	inline HWND game_window;
	inline WNDPROC game_wndproc;
}