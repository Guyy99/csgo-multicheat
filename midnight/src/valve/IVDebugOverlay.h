#pragma once

#include "cvector.h"
#include "cmatrix.h"
#include "../util/memory.h"

class IVDebugOverlay
{
public:
	virtual void AddEntityTextOverlay(int entityIndex, int lineOffset, float duration, int r, int g, int b, int a, const char* fmt, ...) = 0;
	virtual void AddBoxOverlay(const vec3& origin, const vec3& min, const vec3& max, const vec3& orientation, int r, int g, int b, int a, float duration) = 0;
	virtual void AddSphereOverlay(const vec3& origin, float flRadius, int nTheta, int nPhi, int r, int g, int b, int a, float duration) = 0;
	virtual void AddTriangleOverlay(const vec3& p1, const vec3& p2, const vec3& p3, int r, int g, int b, int a, bool noDepthTest, float duration) = 0;
	virtual void AddLineOverlay(const vec3& origin, const vec3& dest, int r, int g, int b, bool noDepthTest, float duration) = 0;
	virtual void AddTextOverlay(const vec3& origin, float duration, const char* fmt, ...) = 0;
	virtual void AddTextOverlay(const vec3& origin, int lineOffset, float duration, const char* fmt, ...) = 0;
	virtual void AddScreenTextOverlay(float x, float y, float duration, int r, int g, int b, int a, const char* text) = 0;
	virtual void AddSweptBoxOverlay(const vec3& start, const vec3& end, const vec3& min, const vec3& max, const vec3& angles, int r, int g, int b, int a, float duration) = 0;
	virtual void AddGridOverlay(const vec3& origin) = 0;
	virtual void AddCoordFrameOverlay(const matrix3x4_t& frame, float scale, int colorTable[3][3] = nullptr) = 0;
	virtual int ScreenPosition(const vec3& worldPosition, vec3& screen) = 0;
	virtual int ScreenPosition(float flXPos, float flYPos, vec3& vecScreen) = 0;
	virtual void* GetFirst() = 0;
	virtual void* GetNext(void* pCurrent) = 0;
	virtual void ClearDeadOverlays() = 0;
	virtual void ClearAllOverlays() = 0;
	virtual void AddTextOverlayRGB(const vec3& vecOrigin, int iLineOffset, float flDuration, float r, float g, float b, float a, const char* fmt, ...) = 0;
	virtual void AddTextOverlayRGB(const vec3& vecOrigin, int iLineOffset, float flDuration, int r, int g, int b, int a, const char* fmt, ...) = 0;
	virtual void AddLineOverlayAlpha(const vec3& vecOrigin, const vec3& dest, int r, int g, int b, int a, bool bNoDepthTest, float flDuration) = 0;
	virtual void AddBoxOverlay2(const vec3& vecOrigin, const vec3& vecAbsMin, const vec3& vecAbsMax, const vec3& angOrientation, const int& faceColor, const int& edgeColor, float flDuration) = 0;
	virtual void AddLineOverlay(const vec3& vecOrigin, const vec3& vecDest, int r, int g, int b, int a, float flThickness, float flDuration) = 0;
	virtual void PurgeTextOverlays() = 0;
	virtual void AddCapsuleOverlay(const vec3& vecAbsMin, const vec3& vecAbsMax, const float& flRadius, int r, int g, int b, int a, float flDuration) = 0;
	virtual void DrawPill(vec3& vecAbsMin, vec3& vecAbsMax, float flRadius, int r, int g, int b, int a, float flDuration) = 0;
};