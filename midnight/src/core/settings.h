#pragma once

#include <vector>

enum weapon_types
{
	KNIFE,
	FAMAS,
	GALIL,
	M4A4,
	M4A1,
	AK47,
	AUG,
	SG,
	DEAGLE,
	REVOLVER,
	GLOCK,
	USPS,
	CZ,
	FIVESEVEN,
	P250,
	TEC,
	DUALEES,
	P2000,
	SSG,
	AWP,
	SCAR,
	G3SG1,
	MP9,
	MAC10,
	PPBIZON,
	MP7,
	UMP,
	P90,
	MP5,
	NOVA,
	XM,
	MAG7,
	SAWEDOFF,
	M249,
	NEGEV
};

struct knife_settings
{
	int type;
	int ID;
	float weapon_float = 0.00001f;
};

struct skin_settings
{
	int ID = 0;
	float weapon_float = 0.00001f;

};

namespace settings
{
	inline bool menuOpen = false;
	inline bool bBox = true, bBone = true, bHealth = false, bSnaplines = false;
	inline bool bBoxTeam = false, bBoneTeam = false, bHealthTeam = false;
	inline bool bBoxRainbow = false, bBoneRainbow = false, bSnapLinesRainbow = false;
	inline float BoxColor[3] = {1.f, 1.f, 1.f}, BoneColor[3] = { 1.f, 1.f, 1.f }, SnapLinesColor[3] = {1.f, 0.f, 0.f};
	

	inline bool bhop = true;
	inline bool bAimbot = false, bSilent = false, bForceFire = false, bAimAssist = false, bRCS = false, bRCSilent = false;
	inline float smoothing = 20.f, fov = 40.f;

	inline bool bChamsVisible = true, bChamsHidden = true;
	inline float hidden_chams_color[3] = {0.529f, 0.f, 1.f};
	inline float visible_chams_color[3] = { 0.f, 0.85f, 1.f };
	inline bool bChamsVisibleRainbow = false;
	inline bool bChamsHiddenRainbow = false;
	inline bool bWeaponChams = false, bViewModelChams = false;

	inline float screen_x = 1920, screen_y = 1080;
	inline int lean = 0;

	inline std::vector<skin_settings> skins;

	
}
