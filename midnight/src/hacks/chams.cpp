#include "chams.h"


void chams::set_entity_chams(const DrawModelInfo_t& info, bool visible)
{
	CEntity* entity = info.renderable->GetUnknownEntity()->GetBaseEntity();

	CEntity* localPlayer = interfaces::EntityList->GetClientEntityFromID(interfaces::engine->GetLocalPlayerIndex());

	if (localPlayer->GetTeam() == entity->GetTeam() || !entity || entity->GetHealth() <= 0)
	{
		return;
	}

	static IMaterial* material = interfaces::materialSystem->FindMaterial("debug/debugambientcube");

	if (!material)
		return;

	material->SetMaterialVarFlag(IMaterial::WIREFRAME, false);

	interfaces::studioRender->SetAlphaModulation(1.f);

	if (visible)
	{
		material->SetMaterialVarFlag(IMaterial::IGNOREZ, false);
		interfaces::studioRender->SetColorModulation(settings::visible_chams_color);
	}
	else
	{
		material->SetMaterialVarFlag(IMaterial::IGNOREZ, true);
		interfaces::studioRender->SetColorModulation(settings::hidden_chams_color);
	}

	interfaces::studioRender->ForcedMaterialOverride(material);

}

bool chams::weapon(const DrawModelInfo_t& info)
{
	CEntity* entity = info.renderable->GetUnknownEntity()->GetBaseEntity();

	if (!entity)
		return false;

	if (*entity->GetModelIndexPointer() != *interfaces::EntityList->GetClientEntityFromID(interfaces::engine->GetLocalPlayerIndex())->GetActiveWeapon()->GetModelIndexPointer())
		return false;

	static IMaterial* material = interfaces::materialSystem->FindMaterial("debug/debugambientcube");

	if (!material)
		return true;

	interfaces::studioRender->SetAlphaModulation(1.f);


	material->SetMaterialVarFlag(IMaterial::IGNOREZ, false);
	material->SetMaterialVarFlag(IMaterial::WIREFRAME, true);
	interfaces::studioRender->SetColorModulation(settings::visible_chams_color);

	interfaces::studioRender->ForcedMaterialOverride(material);
	return true;

	
}
