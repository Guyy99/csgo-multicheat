#pragma once

#include "../valve/cvector.h"

inline bool WorldToScreen(vec3 pos, vec2& screen, float matrix[16], int windowWidth, int windowHeight) {

	vec4 clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
	clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
	clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
	clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];
	if (clipCoords.w < 0.1f)
		return false;
	vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w; NDC.y = clipCoords.y / clipCoords.w; NDC.z = clipCoords.z / clipCoords.w;
	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2); screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}
