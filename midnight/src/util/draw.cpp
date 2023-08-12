#include "draw.h"

void draw::Text(IDirect3DDevice9* device, int xPos, int yPos, LPCSTR msg)
{
	if (!font)
		D3DXCreateFont(device, 17, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	RECT rect;
	rect.bottom = yPos + 200;
	rect.top = yPos;
	rect.left = xPos;
	rect.right = 1024;

	font->DrawTextA(NULL, msg, -1, &rect, 0, D3DCOLOR_ARGB(255, 0, 0, 255));
}

void draw::Line(IDirect3DDevice9* d3d9device, vec2 point1, vec2 point2, float thickness, D3DCOLOR color)
{
	if (!line)
		D3DXCreateLine(d3d9device, &line);

	D3DXVECTOR2 points[] = {
		D3DXVECTOR2(point1.x,point1.y),
		D3DXVECTOR2(point2.x,point2.y)
	};

	line->SetWidth(thickness);
	line->Begin();
	line->Draw(points, 2, color);
	line->End();
	line->SetWidth(1);
}

void draw::Box(IDirect3DDevice9* d3d9device, float x, float y, float w, float h, D3DCOLOR color)
{
	draw::Line(d3d9device, vec2{ x,y }, vec2{ x ,y + h }, 1, color);
	draw::Line(d3d9device, vec2{ x + w,y + h }, vec2{ x,y + h }, 1, color);
	draw::Line(d3d9device, vec2{ x + w,y + h }, vec2{ x + w,y }, 1, color);
	draw::Line(d3d9device, vec2{ x,y }, vec2{ x + w,y }, 1, color);

}

void draw::Circle(IDirect3DDevice9* d3d9device, vec2 pos, float radius, D3DCOLOR color)
{
	{
		D3DXVECTOR2 Line[128];
		float Step = PI * 2.0 / 28;
		int Count = 0;
		for (float a = 0; a < PI * 2.0; a += Step)
		{
			float X1 = radius * cos(a) + pos.x;
			float Y1 = radius * sin(a) + pos.y;
			float X2 = radius * cos(a + Step) + pos.x;
			float Y2 = radius * sin(a + Step) + pos.y;
			Line[Count].x = X1;
			Line[Count].y = Y1;
			Line[Count + 1].x = X2;
			Line[Count + 1].y = Y2;
			Count += 2;
		}
		line->Begin();
		line->Draw(Line, Count, color);
		line->End();
	}
}