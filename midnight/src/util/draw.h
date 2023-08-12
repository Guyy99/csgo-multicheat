#pragma once

#include "../valve/cvector.h"

#include<d3d9.h>
#include<d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

static double PI = 3.14159265358;

static ID3DXFont* font = nullptr;
static LPD3DXLINE line = NULL;

namespace draw {
	void Text(IDirect3DDevice9* device, int xPos, int yPos, LPCSTR msg);
	void Line(IDirect3DDevice9* d3d9device, vec2 point1, vec2 point2, float thickness = 1, D3DCOLOR color = D3DCOLOR_XRGB(255, 0, 0));
	void Box(IDirect3DDevice9* d3d9device, float x, float y, float w, float h, D3DCOLOR color = D3DCOLOR_XRGB(255, 0, 0));
	void Circle(IDirect3DDevice9* d3d9device, vec2 pos, float radius, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
}

