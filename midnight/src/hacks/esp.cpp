#include "esp.h"

void ESP::LoopEntities(IDirect3DDevice9* d3d9device)
{


	float Matrix[16];
	memcpy(&Matrix, (PBYTE*)((DWORD)GetModuleHandle("client.dll") + offsets::dwViewMatrix), sizeof(Matrix));

	int localPlayerIndex = interfaces::engine->GetLocalPlayerIndex();
	

	for (int i = 1; i < 64; ++i)
	{
		CEntity* entity = interfaces::EntityList->GetClientEntityFromID(i);
		

		if (!entity)
			continue;

		if (i == localPlayerIndex)
			continue;

		if (entity->GetHealth() < 1)
			continue;

		if (entity->IsDormant())
			continue;

		
		if (entity->GetTeam() == interfaces::EntityList->GetClientEntityFromID(localPlayerIndex)->GetTeam())
		{
			if (settings::bBoneTeam && settings::bBone)
				ESP::Bone(d3d9device, entity, Matrix);
			if (settings::bBox && settings::bBoxTeam)
				ESP::Box(d3d9device, entity, Matrix);
			if (settings::bHealth && settings::bHealthTeam)
				ESP::health(d3d9device, entity, Matrix);
			if (settings::bSnaplines && settings::bHealthTeam)
				ESP::SnapLines(d3d9device, entity, Matrix);
		}
		else
		{
			if (settings::bBone)
				ESP::Bone(d3d9device, entity, Matrix);
			if (settings::bBox)
				ESP::Box(d3d9device, entity, Matrix);
			if (settings::bHealth)
				ESP::health(d3d9device, entity, Matrix);
			if (settings::bSnaplines)
				ESP::SnapLines(d3d9device, entity, Matrix);
		}
	
		
		


	}
}

void ESP::Bone(IDirect3DDevice9* d3d9device, CEntity* entity, float Matrix[16])
{
	if (entity->IsDormant())
		return;

	CModel* model = entity->GetModel();

	if (!model)
		return;
	
	CStudioHdr* hdr = interfaces::g_pModelInfo->GetStudioModel(model);
	
	if (!hdr)
		return;

	matrix3x4_t bones[128];
	if (!entity->SetupBones(bones, 128, 0x7FF00, interfaces::globals->currentTime))
		return;


	for (int j = 0; j < hdr->numBones; ++j)
	{
		CStudioBone* pBone = hdr->GetBone(j);

		if (!pBone || !(pBone->flags & BONE_USED_BY_HITBOX) || pBone->parent == -1) continue; 	

		vec3 bone1 = bones[j].Origin();
		vec3 bone2 = bones[pBone->parent].Origin();

		if (bone2 == vec3{}) continue;

		vec2 b1, b2;

		if (!WorldToScreen(vec3{bones[j][0][3],bones[j][1][3] ,bones[j][2][3] }, b1, Matrix, settings::screen_x, settings::screen_y))
			continue;
		if (!WorldToScreen(vec3{ bones[pBone->parent][0][3],bones[pBone->parent][1][3] ,bones[pBone->parent][2][3] }, b2, Matrix, settings::screen_x, settings::screen_y))
			continue;

		draw::Line(d3d9device, b1, b2, 1.0f, D3DCOLOR_XRGB((int)(settings::BoneColor[0]*255), (int)(settings::BoneColor[1] * 255), (int)(settings::BoneColor[2] * 255)));

	}

}

void ESP::Box(IDirect3DDevice9* d3d9device, CEntity* entity, float Matrix[16])
{


	vec2 head, feet;

	if (!WorldToScreen(ESP::GetBone(entity, 8) + vec3{0.f, 0.f, 11.f}, head, Matrix, settings::screen_x, settings::screen_y))
		return;

	if (!WorldToScreen(entity->GetAbsOrigin() - vec3{0.f, 0.f, 10.f}, feet, Matrix, settings::screen_x, settings::screen_y))
		return;

	const float h = feet.y - head.y;
	const float w = h / 2.f;

	draw::Box(d3d9device, (head.x - w / 2), head.y, w, h, D3DCOLOR_XRGB((int)(settings::BoxColor[0] * 255), (int)(settings::BoxColor[1] * 255), (int)(settings::BoxColor[2] * 255)));
}

void ESP::health(IDirect3DDevice9* d3d9device, CEntity* entity, float Matrix[16]) // FIX WEIRD HEALTH MOVING THING
{

	vec2 head, feet;

	if (!WorldToScreen(ESP::GetBone(entity, 8) + vec3{ 0.f, 0.f, 11.f }, head, Matrix, settings::screen_x, settings::screen_y))
		return;

	if (!WorldToScreen(entity->GetAbsOrigin() - vec3{ 0.f, 0.f, 10.f }, feet, Matrix, settings::screen_x, settings::screen_y))
		return;

	const float height = head.y - feet.y;
	const float w = (height / 2.4f);

	vec2 newTop = head;
	newTop.x += w;

	vec2 newBottom = newTop;
	newBottom.y -= height;

	if ((newTop.x < 0) || (newBottom.x < 0))
		return;

	draw::Line(d3d9device, newBottom, newTop, 3.f, D3DCOLOR_XRGB(255, 0, 0));

	const int health = entity->GetHealth();
	const float hpPercent = health / 100.f;

	vec2 healthTop = newTop;
	healthTop.y -= height * (1 - hpPercent);

	draw::Line(d3d9device, newBottom, healthTop, 3.f, D3DCOLOR_XRGB(0, 255, 0));
	

}

void ESP::SnapLines(IDirect3DDevice9* d3d9device, CEntity* entity, float Matrix[16])
{
	vec2 base{ 960, 1080 };

	vec3 vecOrigin = entity->GetAbsOrigin();

	vec2 screenOrigin;
	if (!WorldToScreen(vecOrigin, screenOrigin, Matrix, 1920, 1080))
		return;

	draw::Line(d3d9device, base, screenOrigin, 1.0f, D3DCOLOR_XRGB((int)(settings::SnapLinesColor[0] * 255), (int)(settings::SnapLinesColor[1] * 255), (int)(settings::SnapLinesColor[2] * 255)));
}
vec3 ESP::GetBone(CEntity* entity, int id)
{
	vec3 bone;

	bone.x = *(float*)(*(uintptr_t*)(entity + offsets::m_dwBoneMatrix) + (0x30 * id) + 0xC);
	bone.y = *(float*)(*(uintptr_t*)(entity + offsets::m_dwBoneMatrix) + (0x30 * id) + 0x1C);
	bone.z = *(float*)(*(uintptr_t*)(entity + offsets::m_dwBoneMatrix) + (0x30 * id) + 0x2C);

	return bone;
}

