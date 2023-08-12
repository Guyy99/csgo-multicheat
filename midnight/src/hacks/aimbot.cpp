#include "aimbot.h"


void aimbot::Aimbot(CUserCmd*& cmd)
{
	if (settings::bAimbot)
		if (!settings::bForceFire)
			if (!(cmd->buttons & CUserCmd::IN_ATTACK))
				return;

	CEntity* localPlayer = globals::UpdateLocalPlayer();
	CEntity* entity = nullptr;

	vec3 aimPunch; localPlayer->GetAimPunch(aimPunch);

	if (settings::bAimbot)
		entity = findOptimalEntityHeadPos();
	if (settings::bAimAssist)
		entity = FindOptimalAimAssistHead();

	if (!entity)
		return;

	if (!entity->GetIndex())
		return;

	matrix3x4_t bones[128];
	if (!entity->SetupBones(bones, 128, 0x7FF00, interfaces::globals->currentTime))
		return;

	vec3 localEyePosition;  localPlayer->GetEyePosition(localEyePosition);
	
	if (settings::bAimAssist)
		cmd->viewAngles = cmd->viewAngles + (aimbot::calcAngle(localEyePosition, bones[8].Origin()) - cmd->viewAngles - aimPunch).Scale((100-settings::smoothing)/100);
	else
		cmd->viewAngles = cmd->viewAngles + (aimbot::calcAngle(localEyePosition, bones[8].Origin()) - cmd->viewAngles - aimPunch);

	if (settings::bForceFire)
	{
		if (!shotLastTick)
		{
			cmd->buttons |= CUserCmd::IN_ATTACK;
			shotLastTick = true;
		}
			
		else
		{
			cmd->buttons &= ~CUserCmd::IN_ATTACK;
			shotLastTick = false;
		}
			
	}

		
}

void aimbot::rcs(CUserCmd*& cmd)
{
	CEntity* localPlayer = interfaces::EntityList->GetClientEntityFromID(interfaces::engine->GetLocalPlayerIndex());

	vec3 aimPunch; localPlayer->GetAimPunch(aimPunch);
	cmd->viewAngles = cmd->viewAngles - aimPunch;
}

CEntity* aimbot::FindOptimalAimAssistHead()
{
	static DWORD client = (DWORD)GetModuleHandle("client.dll");
	float Matrix[16];
	memcpy(&Matrix, (PBYTE*)(client + offsets::dwViewMatrix), sizeof(Matrix));

	vec2 crosshair{ (settings::screen_x / 2),(settings::screen_y / 2) };

	float optimalDistance = NULL;
	CEntity* optimalEntity = nullptr;

	CEntity* localPlayer = globals::UpdateLocalPlayer();

	for (int i = 0; i < 64; i++)
	{
		CEntity* entity = interfaces::EntityList->GetClientEntityFromID(i);
		if (!entity) continue;

		if (entity->IsDormant()) continue;

		if (entity->GetTeam() == localPlayer->GetTeam()) continue;

		if (!entity->IsAlive()) continue;

		vec3 localEye, enemyHead;
		localPlayer->GetEyePosition(localEye);

		matrix3x4_t bones[128];
		if (!entity->SetupBones(bones, 128, 0x7FF00, interfaces::globals->currentTime))
			continue;
		enemyHead = bones[8].Origin();

		CTrace TraceRay;
		interfaces::engineTrace->TraceRay(
			{ localEye, enemyHead },
			0x46004009,
			localPlayer,
			TraceRay
		);

		if (!TraceRay.entity or !TraceRay.entity->IsPlayer())
			continue;

		vec2 screenHead;
		if (!WorldToScreen(enemyHead, screenHead, Matrix, settings::screen_x, settings::screen_y))
			continue;

		if ((screenHead.x > settings::screen_x) or (screenHead.x < 0))
			continue;
		if ((screenHead.y > settings::screen_y) or (screenHead.y < 0))
			continue;

		float distance = GetScreenDistance(crosshair, screenHead);

		if (distance < settings::fov)
		{
			if (!optimalDistance)
			{
				optimalDistance = distance;
				optimalEntity = entity;
			}
				
			else
			{
				if (optimalDistance > distance)
				{
					optimalDistance = distance;
					optimalEntity = entity;
				}
			}
		}
	}

	return optimalEntity;
}



CEntity* aimbot::findOptimalEntityHeadPos()
{
	static DWORD client = (DWORD)GetModuleHandle("client.dll");
	float Matrix[16];
	memcpy(&Matrix, (PBYTE*)(client + offsets::dwViewMatrix), sizeof(Matrix));

	float optimalDistance = NULL;
	CEntity* optimalEntity = nullptr;

	CEntity* localPlayer = globals::UpdateLocalPlayer();

	for (int i = 0; i < 64; i++)
	{
		CEntity* entity = interfaces::EntityList->GetClientEntityFromID(i);
		if (!entity) continue;

		if (entity->IsDormant()) continue;

		if (entity->GetTeam() == localPlayer->GetTeam()) continue;

		if (!entity->IsAlive()) continue;

		vec3 localEye, enemyEye;
		localPlayer->GetEyePosition(localEye);
		
		matrix3x4_t bones[128];
		if (!entity->SetupBones(bones, 128, 0x7FF00, interfaces::globals->currentTime))
			continue;
		enemyEye = bones[8].Origin();

		CTrace TraceRay;
		interfaces::engineTrace->TraceRay(
			{ localEye, enemyEye },
			0x46004009,
			localPlayer,
			TraceRay
			);

		if (!TraceRay.entity or !TraceRay.entity->IsPlayer())
			continue;

		float distance = GetWorldDistance(enemyEye, localEye);

		if (!optimalDistance)
			optimalDistance = distance;


		if (distance < optimalDistance)
			optimalDistance = distance;	optimalEntity = entity;

	}
	return optimalEntity;
	
}

float aimbot::GetScreenDistance(vec2 p1, vec2 p2)
{
	return sqrt(pow((p2.x-p1.x),2) + pow((p2.y - p1.y), 2));
}

float aimbot::GetWorldDistance(vec3 p1, vec3 p2)
{
	return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2) + pow((p2.z-p1.z),2));
}

vec3 aimbot::calcAngle(vec3 local, vec3 enemy)
{
	return (enemy - local).ToAngle();
}