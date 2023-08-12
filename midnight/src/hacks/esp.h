#pragma once

#include <Windows.h>
#include <iostream>

#include<d3d9.h>
#include<d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include "../valve/offsets.h"
#include "../util/draw.h"
#include "../core/interfaces.h"
#include "../valve/centity.h"
#include "../valve/cmatrix.h"
#include "../valve/cvector.h"
#include "../core/settings.h"
#include "../valve/studio.h"
#include "../util/w2s.h"
#include "../core/globals.h"


namespace ESP
{
	void LoopEntities(IDirect3DDevice9* d3d9device);

	void Bone(IDirect3DDevice9* d3d9device, CEntity* entity, float Matrix[16]);
	void Box(IDirect3DDevice9* d3d9device, CEntity* entity, float Matrix[16]);
	void health(IDirect3DDevice9* d3d9device, CEntity* entity, float Matrix[16]);
	void SnapLines(IDirect3DDevice9* d3d9device, CEntity* entity, float Matrix[16]);

	vec3 GetBone(CEntity* entity, int id);
}