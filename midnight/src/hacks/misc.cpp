#include "misc.h"

void misc::bhop(CUserCmd*& cmd)
{
	static DWORD client = (DWORD)GetModuleHandle("client.dll");

	const DWORD localPlayer = *reinterpret_cast<DWORD*>(client + offsets::dwLocalPlayer);

	int flags = *reinterpret_cast<int*>(localPlayer + offsets::m_fFlags);

	if (!(flags & FL_ONGROUND))
	{
		cmd->buttons &= ~CUserCmd::ECommandButton::IN_JUMP;
	}
}

void misc::antiCrouch(CUserCmd*& cmd)
{
	static DWORD client = (DWORD)GetModuleHandle("client.dll");

	const DWORD localPlayer = *reinterpret_cast<DWORD*>(client + offsets::dwLocalPlayer);

	int flags = *reinterpret_cast<int*>(localPlayer + offsets::m_fFlags);

	if (!(flags & (1 << 2)))
	{
		cmd->buttons &= ~CUserCmd::ECommandButton::IN_DUCK;
	}
}

vec3 misc::rainbow()
{
	static uint32_t cnt = 0;
	float freq = 0.001f;

	if (cnt++ >= (uint32_t)-1)
		cnt = 0;

	vec3 ret = { std::sin(freq * cnt + 0) * 0.5f + 0.5f, std::sin(freq * cnt + 2) * 0.5f + 0.5f , std::sin(freq * cnt + 4) * 0.5f + 0.5f };
	return ret;
}

void misc::update_rainbows()
{

	vec3 color;

	if (settings::bBoneRainbow)
	{
		color = misc::rainbow();
		settings::BoneColor[0] = color.x;
		settings::BoneColor[1] = color.y;
		settings::BoneColor[2] = color.z;
	}
	if (settings::bBoxRainbow)
	{
		color = misc::rainbow();
		settings::BoxColor[0] = color.x;
		settings::BoxColor[1] = color.y;
		settings::BoxColor[2] = color.z;
	}
	if (settings::bSnapLinesRainbow)
	{
		color = misc::rainbow();
		settings::SnapLinesColor[0] = color.x;
		settings::SnapLinesColor[1] = color.y;
		settings::SnapLinesColor[2] = color.z;
	}
	if (settings::bChamsHiddenRainbow)
	{
		color = misc::rainbow();
		settings::hidden_chams_color[0] = color.x;
		settings::hidden_chams_color[1] = color.y;
		settings::hidden_chams_color[2] = color.z;
	}
	if (settings::bChamsVisibleRainbow)
	{
		color = misc::rainbow();
		settings::visible_chams_color[0] = color.x;
		settings::visible_chams_color[1] = color.y;
		settings::visible_chams_color[2] = color.z;
	}
}
