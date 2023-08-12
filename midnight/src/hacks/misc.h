#pragma once

#include <Windows.h>
#include <iostream>

#include "../valve/offsets.h"
#include "../valve/cusercmd.h"
#include "../core/settings.h"

#define	FL_ONGROUND	 (1 << 0)
//#define IN_DUCK		 (1 << 2)

namespace misc
{
	void bhop(CUserCmd* &cmd);
	void antiCrouch(CUserCmd*& cmd);

	vec3 rainbow();
	void update_rainbows();
}
