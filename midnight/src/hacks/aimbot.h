#pragma once

#include <iostream>
#include <cmath>

#include "../valve/cvector.h"
#include "../valve/centity.h"
#include "../valve/cmatrix.h"
#include "../valve/cusercmd.h"
#include "../valve/icliententitylist.h"

#include "../core/settings.h"
#include "../core/interfaces.h"
#include "../core/globals.h"
#include "../util/w2s.h"

namespace aimbot
{
	inline bool shotLastTick = false;

	void Aimbot(CUserCmd* &cmd);

	void rcs(CUserCmd*& cmd);

	CEntity* FindOptimalAimAssistHead();
	CEntity* findOptimalEntityHeadPos();
	float GetScreenDistance(vec2 p1, vec2 p2);
	vec3 calcAngle(vec3 local, vec3 enemy);
	float GetWorldDistance(vec3 p1, vec3 p2);
}
