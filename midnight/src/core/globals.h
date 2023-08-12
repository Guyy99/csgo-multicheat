#pragma once

#include "../valve/centity.h"
#include "gui.h"
#include "interfaces.h"
#include <cstdint>

namespace globals
{
	CEntity* UpdateLocalPlayer();
	void FindProcessWindow();

	inline bool isCreateMoveHooked = false;
	inline bool InitializedCreateMove = false;
	
}
