#include "hooks.h"


void APIENTRY hooks::HookedEndScene(IDirect3DDevice9* pDevice)
{
	std::cout << "ENDSCENEEEE" << std::endl;
	if (!gui::initialized)
	{
		gui::Setup(pDevice);
		gui::initialized = true;
	}

	if (settings::menuOpen)
		gui::Render();

	if (!interfaces::engine->IsInGame())
	{
		hooks::originalEndScene(pDevice);
		return;
	}

	misc::update_rainbows();


	ESP::LoopEntities(pDevice);

	if (settings::bAimAssist)
		draw::Circle(pDevice, vec2{ (settings::screen_x/2),(settings::screen_y/2)}, settings::fov);

	//hooks::endSceneHook->CallFunction(pDevice);
	hooks::originalEndScene(pDevice);
}

bool __stdcall hooks::HookedCreateMove(float frameTime, CUserCmd* cmd)
{

	const bool result = hooks::originalCreateMove(hooks::g_clientMode, frameTime, cmd);

	if (!interfaces::engine->IsInGame())
		return result;

	if (!cmd or !cmd->commandNumber)
		return result;

	if ((settings::bAimbot && !settings::bSilent) or (settings::bAimAssist))
		aimbot::Aimbot(cmd);

	if (settings::bRCS && !settings::bRCSilent)
		aimbot::rcs(cmd);

	if (hooks::originalCreateMove(hooks::g_clientMode, frameTime, cmd))
		interfaces::engine->SetViewAngles(cmd->viewAngles);

	if (settings::bhop)
		if (GetAsyncKeyState(VK_SPACE))
			misc::bhop(cmd);

	if (settings::bRCS && settings::bRCSilent)
		aimbot::rcs(cmd);

	if (settings::bAimbot && settings::bSilent)
		aimbot::Aimbot(cmd);
	

	return false;
}

void APIENTRY hooks::HookedDrawModel(uintptr_t* pResults, const DrawModelInfo_t& info,
	matrix3x4_t* pBoneToWorld, float* pFlexWeights, float* pFlexDelayedWeights, const vec3& modelOrigin, int flags)
{
	if (!info.renderable)
		return;

	if (settings::bWeaponChams)
	{
		if (chams::weapon(info))
		{
			hooks::originalDrawModel(interfaces::studioRender, pResults, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, modelOrigin, flags);
			return interfaces::studioRender->ForcedMaterialOverride(nullptr);
		}
	}

	if (settings::bChamsHidden)
	{
		chams::set_entity_chams(info, false);
		hooks::originalDrawModel(interfaces::studioRender, pResults, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, modelOrigin, flags);
	}
	if (settings::bChamsVisible)
	{
		chams::set_entity_chams(info, true);
		hooks::originalDrawModel(interfaces::studioRender, pResults, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, modelOrigin, flags);
	}

	if (!settings::bChamsHidden && !settings::bChamsVisible)
		hooks::originalDrawModel(interfaces::studioRender, pResults, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, modelOrigin, flags);

	return interfaces::studioRender->ForcedMaterialOverride(nullptr);

}
void APIENTRY hooks::HookedFrameStageNotify(ClientFrameStage_t curStage)
{
	if (curStage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		return hooks::originalFrameStageNotify(interfaces::baseClient, curStage);

	skins::change();



	return hooks::originalFrameStageNotify(interfaces::baseClient, curStage);
}




void hooks::Setup()
{
	// EndScene hook

	MH_Initialize();

	IDirect3DDevice9* device = *(IDirect3DDevice9**)((uintptr_t)GetModuleHandle("shaderapidx9.dll") + offsets::dwppDirect3DDevice9);
	hooks::endScenePointer = (LPVOID)(*(void***)(*(IDirect3DDevice9**)((uintptr_t)GetModuleHandle("shaderapidx9.dll") + offsets::dwppDirect3DDevice9)))[42]; // gets address of endscene

	CREATE_HOOK((LPVOID)hooks::endScenePointer, hooks::HookedEndScene, hooks::originalEndScene);

	


	
	

	// Create move Hook
	
	hooks::g_clientMode = **reinterpret_cast<void***>((*reinterpret_cast<DWORD**>(interfaces::client))[10] + 0x5);
	hooks::CreateMovePointer = (*(void***)(hooks::g_clientMode))[24];
	CREATE_HOOK(hooks::CreateMovePointer, hooks::HookedCreateMove, hooks::originalCreateMove);


	// Draw Model Hook
	hooks::DrawModelPointer = (*(void***)(interfaces::studioRender))[29];
	CREATE_HOOK(hooks::DrawModelPointer, hooks::HookedDrawModel, hooks::originalDrawModel);


	// Frame Stage Notify Hook

	hooks::FrameStageNotifyPointer = (*(void***)(interfaces::client))[37];
	CREATE_HOOK(hooks::FrameStageNotifyPointer, hooks::HookedFrameStageNotify, hooks::originalFrameStageNotify);

	
}

BOOL IsExecutableAddress(LPVOID pAddress)
{
	MEMORY_BASIC_INFORMATION mi;
	VirtualQuery(pAddress, &mi, sizeof(mi));

	return (mi.State == MEM_COMMIT && (mi.Protect & PAGE_EXECUTE_FLAGS));
}


void hooks::Remove()
{

	//hooks::endSceneHook->DeleteHook();
	REMOVE_HOOK(hooks::endScenePointer);

	
	REMOVE_HOOK(hooks::CreateMovePointer);
	REMOVE_HOOK(hooks::DrawModelPointer);
	REMOVE_HOOK(hooks::FrameStageNotifyPointer);
	
}

template<typename R, typename ...As>
inline Hook<std::function<R(As...)>>::Hook(uintptr_t function_address, uintptr_t hook_function)
{
	pointer = (LPVOID)function_address;
	detour = (LPVOID)hook_function;

	CREATE_HOOK((LPVOID)function_address, hooks::endSceneHook, hooks::originalEndScene);

	hook_active = true;
}

