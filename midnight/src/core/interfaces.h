#pragma once
#include <Windows.h>

#include "../valve/icliententitylist.h"
#include "../valve/cclientclass.h"
#include "../valve/iglobalvars.h"
#include "../valve/IVDebugOverlay.h"
#include "../valve/studio.h"
#include "../valve/IBaseClientDLL.h"
#include "../valve/ivengineclient.h"
#include "../valve/ienginetrace.h"
#include "../valve/studiorender.h"
#include "../valve/imaterialsystem.h"

typedef void* (__cdecl* tCreateInterface)(const char* name, int* returnCode);

namespace interfaces
{
	void* GetInterface(const char* dllname, const char* interfaceName);

	void Setup();

	inline IClientEntityList* EntityList = nullptr;
	inline CClientClass* client = nullptr;
	inline IGlobalVars* globals = nullptr;
	inline IVDebugOverlay* debugOverlay = nullptr;
	inline IVModelInfo* g_pModelInfo = nullptr;
	inline IBaseClientDLL* baseClient = nullptr;
	inline IVEngineClient* engine = nullptr;
	inline IEngineTrace* engineTrace = nullptr;
	inline IStudioRender* studioRender = nullptr;
	inline IMaterialSystem* materialSystem = nullptr;




}
	