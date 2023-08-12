#include "gui.h"
#include <d3d9.h>

LRESULT CALLBACK gui::user_wndproc(HWND window, UINT message_type, WPARAM w_param, LPARAM l_param) 
{
	if (ImGui_ImplWin32_WndProcHandler(window, message_type, w_param, l_param) && settings::menuOpen) { 
		return 1l;
	}

	return CallWindowProc(gameWindow::game_wndproc, window, message_type, w_param, l_param);
}

void gui::Setup(IDirect3DDevice9* device)
{
	auto CP = D3DDEVICE_CREATION_PARAMETERS{};
	device->GetCreationParameters(&CP);
	HWND window = CP.hFocusWindow;
	gameWindow::game_window = window;
	gameWindow::game_wndproc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)gui::user_wndproc);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);
	initialized = true;
	return;
}

void gui::Render()
{
	ImGui::SetNextWindowSize(ImVec2{ 800,505 });

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Midnight");

	
	ImGui::BeginTabBar("Cheats");

	// Define the first tab and its contents
	if (ImGui::BeginTabItem("Aim"))
	{
		ImGui::Spacing();

		ImGui::BeginGroup(); //begins the group
		ImGui::PushItemWidth(200.f); //item width
		ImGui::BeginChild("Aimbot", ImVec2(300, 110), true); //begins the child and the size of the child.

		ImGui::LabelText("", "Aimbot");

		ImGui::Checkbox("Toggle", &settings::bAimbot);
		ImGui::Checkbox("Silent Aim", &settings::bSilent);
		ImGui::Checkbox("Force Fire", &settings::bForceFire);


		ImGui::Spacing();

		ImGui::EndChild(); //ends the child
		ImGui::PopItemWidth(); //pops the item width
		ImGui::EndGroup(); //ends the group

		ImGui::SameLine();

		ImGui::BeginGroup(); //begins the group
		ImGui::PushItemWidth(200.f); //item width
		ImGui::BeginChild("Aim Assist", ImVec2(300, 110), true);

		ImGui::LabelText("", "Aim Assist");

		ImGui::Checkbox("Toggle", &settings::bAimAssist);
		ImGui::SliderFloat("Fov", &settings::fov, 0.f, 100.f);
		ImGui::SliderFloat("Smoothing", &settings::smoothing, 0.f, 99.f);

		ImGui::Spacing();

		ImGui::EndChild(); //ends the child
		ImGui::PopItemWidth(); //pops the item width
		ImGui::EndGroup();

		ImGui::BeginGroup(); //begins the group
		ImGui::PushItemWidth(200.f); //item width
		ImGui::BeginChild("RCS", ImVec2(300, 110), true);

		ImGui::LabelText("", "RCS");

		ImGui::Checkbox("Toggle", &settings::bRCS);
		ImGui::Checkbox("Silent", &settings::bRCSilent);

		ImGui::Spacing();

		ImGui::EndChild(); //ends the child
		ImGui::PopItemWidth(); //pops the item width
		ImGui::EndGroup();

		ImGui::EndTabItem();

	}

	// Define the second tab and its contents
	if (ImGui::BeginTabItem("Visuals"))
	{
		// BOX ESP ===============================================

		ImGui::Spacing();

		ImGui::BeginGroup(); //begins the group
		ImGui::PushItemWidth(200.f); //item width
		ImGui::BeginChild("Box ESP", ImVec2(300, 135), true);

		ImGui::LabelText("", "Box ESP");

		ImGui::Checkbox("Toggle", &settings::bBox);
		ImGui::Checkbox("Toggle For Team", &settings::bBoxTeam);
		ImGui::Checkbox("Rainbow", &settings::bBoxRainbow);
		ImGui::ColorEdit3("Color", settings::BoxColor);

		ImGui::Spacing();

		ImGui::EndChild(); //ends the child
		ImGui::PopItemWidth(); //pops the item width
		ImGui::EndGroup();

		// BONE ESP ===============================================

		ImGui::SameLine();

		ImGui::BeginGroup(); //begins the group
		ImGui::PushItemWidth(200.f); //item width
		ImGui::BeginChild("Bone ESP", ImVec2(300, 135), true);

		ImGui::LabelText("", "Bone ESP");

		ImGui::Checkbox("Toggle", &settings::bBone);
		ImGui::Checkbox("Toggle For Team", &settings::bBoneTeam);
		ImGui::Checkbox("Rainbow", &settings::bBoneRainbow);
		ImGui::ColorEdit4("Color", settings::BoneColor);

		ImGui::Spacing();

		ImGui::EndChild(); //ends the child
		ImGui::PopItemWidth(); //pops the item width
		ImGui::EndGroup();

		// HEALTH ==============================================

		ImGui::Spacing();

		ImGui::BeginGroup(); //begins the group
		ImGui::PushItemWidth(200.f); //item width
		ImGui::BeginChild("Health ESP", ImVec2(300, 135), true);

		ImGui::LabelText("", "Health ESP");

		ImGui::Checkbox("Toggle", &settings::bHealth);
		ImGui::Checkbox("Toggle For Team", &settings::bHealthTeam);

		ImGui::Spacing();

		ImGui::EndChild(); //ends the child
		ImGui::PopItemWidth(); //pops the item width
		ImGui::EndGroup();

		// SNAPLINES ============================================

		ImGui::SameLine();

		ImGui::BeginGroup(); //begins the group
		ImGui::PushItemWidth(200.f); //item width
		ImGui::BeginChild("SnapLines", ImVec2(300, 135), true);

		ImGui::LabelText("", "Snaplines");

		ImGui::Checkbox("Toggle", &settings::bSnaplines);
		ImGui::Checkbox("Rainbow", &settings::bSnapLinesRainbow);
		ImGui::ColorEdit4("Color", settings::SnapLinesColor);

		ImGui::Spacing();

		ImGui::EndChild(); //ends the child
		ImGui::PopItemWidth(); //pops the item width
		ImGui::EndGroup();

		// CHAMS =================================================

		ImGui::BeginGroup(); //begins the group
		ImGui::PushItemWidth(200.f); //item width
		ImGui::BeginChild("Chams", ImVec2(300, 180), true);

		ImGui::LabelText("", "Chams");
		ImGui::Checkbox("Hidden", &settings::bChamsHidden);
		ImGui::ColorEdit4("Hidden Color", settings::hidden_chams_color);
		ImGui::Checkbox("Hidden Color Rainbow", &settings::bChamsHiddenRainbow);
		ImGui::Checkbox("Visible", &settings::bChamsVisible);
		ImGui::ColorEdit4("Visible Color", settings::visible_chams_color);
		ImGui::Checkbox("Visible Color Rainbow", &settings::bChamsVisibleRainbow);


		ImGui::EndChild(); //ends the child
		ImGui::PopItemWidth(); //pops the item width
		ImGui::EndGroup();

		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Misc"))
	{
		ImGui::Checkbox("Bhop", &settings::bhop);
		ImGui::EndTabItem();
		
	}
	if (ImGui::BeginTabItem("Skins"))
	{
		ImGui::BeginGroup(); //begins the group
		ImGui::PushItemWidth(200.f); //item width
		ImGui::BeginChild("Weapons", ImVec2(200, 490), true);

		const char* const items[35] = {"Knife", "Famas", "Galil", "M4A4", "M4A1-S", "AK-47", "AUG", "SG-553", "Deagle", "R8-Revolver", "Glock-17", "USP-S", "CZ75-Auto", "Five-SeveN", "P250", "Tec-9", "Dual Berettas", "P2000", "SSG-08", "AWP", "SCAR-20", "G3SG1", "MP9", "MAC-10", "PP-Bizon", "MP7", "UMP-45", "P90", "MP5-SD", "Nova", "XM1014", "MAG-7", "Sawed-Off", "M429", "Negev"};

	    static const char* current_item = "AK-47";

		static int currItem = 0;
		static bool is_selected = 0;

		
		

		if (ImGui::BeginListBox("Weapon", ImVec2(200, 470))) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); ++n) {
				if (ImGui::Selectable(items[n], &is_selected)) 
				{ 
					currItem = n;

				}

				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (n == currItem) { ImGui::SetItemDefaultFocus(); }
			}
			ImGui::EndListBox();
		}

		ImGui::EndChild(); //ends the child
		//ImGui::PopItemWidth(); //pops the item width
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup(); //begins the group
		ImGui::PushItemWidth(200.f); //item width
		ImGui::BeginChild("Skins", ImVec2(200, 490), true);

		static int currSkin = 0;

		if (ImGui::BeginListBox("Skins", ImVec2(200, 470))) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(skins::skin_list); ++n) {
				if (ImGui::Selectable(skins::skin_list[n], &is_selected))
				{
					currSkin = n;

				}

				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (n == currSkin) { ImGui::SetItemDefaultFocus(); }
			}
			ImGui::EndListBox();
		}


		static float* weaponFloat = nullptr;

		settings::skins[currItem].ID = skins::skinEnumToID(currSkin);
		weaponFloat = &settings::skins[currItem].weapon_float;

		ImGui::EndChild(); //ends the child
		//ImGui::PopItemWidth(); //pops the item width
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup(); //begins the group
		ImGui::PushItemWidth(200.f); //item width
		ImGui::BeginChild("Settings", ImVec2(200, 470), true);
		

		ImGui::SliderFloat("Weapon Float", weaponFloat, 0.00001f, 0.99999f);


		if (ImGui::Button("Update Skins"))
		{
			skins::update();
		}

		ImGui::EndChild(); //ends the child
		//ImGui::PopItemWidth(); //pops the item width
		ImGui::EndGroup();

		ImGui::EndTabItem();

	}

	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	
}	

void gui::Destroy()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	SetWindowLongPtr(gameWindow::game_window, GWL_WNDPROC, (LONG_PTR)gameWindow::game_wndproc);
}


