#pragma once
#include "../util/memory.h"

#include "cclientclass.h"

enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,			// (haven't run any frames yet)
	FRAME_START,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,

	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};

class IBaseClientDLL
{
public:
	constexpr CClientClass* GetAllClasses() noexcept
	{
		return memory::Call<CClientClass*>(this, 8);
	}
	constexpr void FrameStageNotify(ClientFrameStage_t curStage)
	{
		return memory::Call<void>(this, 36, curStage);
	}
};