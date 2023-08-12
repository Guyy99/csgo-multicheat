#pragma once


#include "../core/interfaces.h"
#include "../core/settings.h"

#include <iostream>

namespace chams
{
	void set_entity_chams(const DrawModelInfo_t& info, bool visible);

	bool weapon(const DrawModelInfo_t& info);
}

namespace hooks
{
	using DrawModelFn = void(__thiscall*)(void*, uintptr_t*, const DrawModelInfo_t&, matrix3x4_t*, float*, float*, const vec3&, int);
	static DrawModelFn originalDrawModel = nullptr;
}