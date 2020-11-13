#include "menu.hpp"
#include "../../dependencies/utilities/config/config.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void menu::render() {
	ImGui::Begin("csgo-sdk", &menu::opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

	ImGui::BeginTabBar("main_tabs");
	if (ImGui::BeginTabItem("Aimbot", NULL)) { 
		ImGui::BeginChild(1, ImVec2(0, 0), true);
		ImGui::EndChild();
		ImGui::EndTabItem(); 
	}
	if (ImGui::BeginTabItem("Visuals", NULL)) { 
		ImGui::BeginChild(1, ImVec2(0, 0), true);

		ImGui::Checkbox("enemy glow", &vars::visuals::glow_enemy);
		ImGui::SameLine();
		ImGui::ColorEdit4("enemy##glow", vars::visuals::glow_enemy_color,
			ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
		ImGui::Checkbox("team glow", &vars::visuals::glow_team);
		ImGui::SameLine();
		ImGui::ColorEdit4("team##glow", vars::visuals::glow_team_color,
			ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
		ImGui::Checkbox("bomb glow", &vars::visuals::glow_bomb);
		ImGui::SameLine();
		ImGui::ColorEdit4("bomb##glow", vars::visuals::glow_bomb_color,
			ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

		ImGui::EndChild();
		ImGui::EndTabItem(); 
	}
	if (ImGui::BeginTabItem("Misc", NULL)) { 
		ImGui::BeginChild(1, ImVec2(0, 0), true);
		ImGui::Checkbox("bhop", &vars::misc::bhop);
		ImGui::Checkbox("rank reveal", &vars::misc::rank_reveal);
		ImGui::Checkbox("radar", &vars::misc::radar);
		if (ImGui::Button("save")) config::save();
		if (ImGui::Button("load")) config::load();
		ImGui::EndChild();
		ImGui::EndTabItem();
	}
	ImGui::EndTabBar();

	ImGui::End();
}

bool menu::initialize(IDirect3DDevice9* device) {
	hwnd = FindWindow("Valve001", "Counter-Strike: Global Offensive");
	original_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wndproc)));

	ImGui::CreateContext();  // ImGuiIO& io = ImGui::GetIO(); 
	//ImGui::StyleColorsCustom();
	ImGui::StyleColorsClassic();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX9_Init(device);

	initialized = true;
	return true;
}

void menu::release() {
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(original_wndproc));
}

LRESULT WINAPI menu::wndproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (opened && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	return CallWindowProc(original_wndproc, hWnd, msg, wParam, lParam);
}