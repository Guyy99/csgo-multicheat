#pragma once
#include <Windows.h>
#include <iostream>
#include <functional>

#include<d3d9.h>
#include<d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include "../hacks/esp.h"
#include "../hacks/misc.h"
#include "../hacks/aimbot.h"
#include "../core/gui.h"
#include "../hacks/chams.h"
#include "../minhook/include/MinHook.h"
#include "../util/signatures.h"


static bool movedLastTick = false;

#define CREATE_HOOK(pointer, hook, og) MH_CreateHook(pointer, &hook, (LPVOID*)(&og)); MH_EnableHook(pointer)
#define REMOVE_HOOK(pointer) MH_DisableHook(pointer); MH_RemoveHook(pointer)

#define PAGE_EXECUTE_FLAGS \
    (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)


template <typename Signature>
class Hook;
template <typename R, typename ... As>
class Hook<std::function<R(As...)>>
{
private:
	using signature = R(APIENTRY*)(As...);
	signature function;
	LPVOID original;
	LPVOID pointer;
	LPVOID detour;

	bool hook_active;

public:

	template <typename Signature>
	std::function<Signature> cast(void* f)
	{
		return static_cast<Signature*>(f);
	}

	Hook(uintptr_t function_address, uintptr_t hook_function);


	void DeleteHook()
	{
		if (hook_active)
			MH_DisableHook(pointer);

		MH_RemoveHook(pointer);

		delete this;
	}

	R CallFunction(As... args)
	{
		return function(args...);
	}

	void DisableHook()
	{
		if (hook_active)
			MH_DisableHook(pointer);

		hook_active = false;
	}

	void EnableHook()
	{
		if (!hook_active)
			MH_EnableHook(pointer);

		hook_active = true;
	}

};

namespace hooks
{
	void Setup();

	void Remove();

	void APIENTRY HookedEndScene(IDirect3DDevice9* pDevice);
	static LPVOID endScenePointer;
	static Hook<std::function<HRESULT(LPDIRECT3DDEVICE9)>>* endSceneHook = nullptr;
	typedef HRESULT(APIENTRY* EndSceneFn)(LPDIRECT3DDEVICE9);
	static EndSceneFn originalEndScene = nullptr;

	
	using CreateMove = bool(__thiscall*)(void*, float, CUserCmd*);
	static CreateMove originalCreateMove = nullptr;
	inline void* g_clientMode = nullptr;
	bool __stdcall HookedCreateMove(float frameTime, CUserCmd* cmd);
	static LPVOID CreateMovePointer = nullptr;


	void APIENTRY HookedDrawModel(uintptr_t* pResults, const DrawModelInfo_t& info,	matrix3x4_t* pBoneToWorld, float* pFlexWeights, float* pFlexDelayedWeights, const vec3& modelOrigin, int flags);
	static LPVOID DrawModelPointer = nullptr;


	using FrameStageNotifyFn = void(__thiscall*)(void*, ClientFrameStage_t);
	static FrameStageNotifyFn originalFrameStageNotify = nullptr;
	void APIENTRY HookedFrameStageNotify(ClientFrameStage_t curStage);
	static LPVOID FrameStageNotifyPointer = nullptr;

	
}

