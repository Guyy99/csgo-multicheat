#include "interfaces.h"

void* interfaces::GetInterface(const char* dllname, const char* interfaceName)
{
	tCreateInterface CreateInterface = (tCreateInterface)GetProcAddress(GetModuleHandle(dllname), "CreateInterface");

	int returnCode = 0;
	void* Interface = CreateInterface(interfaceName, &returnCode);

	return Interface;
}

void interfaces::Setup()
{
	interfaces::EntityList = (IClientEntityList*)interfaces::GetInterface("client.dll", "VClientEntityList003");
	interfaces::client = (CClientClass*)interfaces::GetInterface("client.dll", "VClient018");
	interfaces::globals = **reinterpret_cast<IGlobalVars***>((*reinterpret_cast<uintptr_t**>(interfaces::client))[11] + 10);
	interfaces::debugOverlay = (IVDebugOverlay*)interfaces::GetInterface("engine.dll", "VDebugOverlay004");
	interfaces::g_pModelInfo = (IVModelInfo*)interfaces::GetInterface("engine.dll", "VModelInfoClient004");
	interfaces::baseClient = (IBaseClientDLL*)interfaces::GetInterface("client.dll", "VClient017");
	interfaces::engine = (IVEngineClient*)interfaces::GetInterface("engine.dll", "VEngineClient014");
	interfaces::engineTrace = (IEngineTrace*)interfaces::GetInterface("engine.dll", "EngineTraceClient004");
	interfaces::studioRender = (IStudioRender*)interfaces::GetInterface("studiorender.dll", "VStudioRender026");
	interfaces::materialSystem = (IMaterialSystem*)interfaces::GetInterface("materialsystem.dll", "VMaterialSystem080");
}