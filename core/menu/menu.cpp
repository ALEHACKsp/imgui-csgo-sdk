#include "menu.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void menu::render() {
	ImGui::Begin("csgo-sdk", &menu::opened, ImGuiWindowFlags_NoCollapse);

	ImGui::BeginTabBar("main_tabs");
	if (ImGui::BeginTabItem("Aimbot", NULL)) { tab = TAB_AIMBOT; ImGui::EndTabItem(); }
	if (ImGui::BeginTabItem("Visuals", NULL)) { tab = TAB_VISUALS; ImGui::EndTabItem(); }
	if (ImGui::BeginTabItem("Misc", NULL)) { tab = TAB_MISC; ImGui::EndTabItem(); }
	if (ImGui::BeginTabItem("Config", NULL)) { tab = TAB_CONFIG; ImGui::EndTabItem(); }
	ImGui::EndTabBar();

	switch (tab) {
	case TAB_AIMBOT:
		break;
	case TAB_VISUALS:
		ImGui::Columns(2, NULL, false);
		ImGui::SetColumnWidth(0, ImGui::GetWindowContentRegionWidth() * 0.6f);

		ImGui::Checkbox("enemy glow", &vars::visuals::glow_enemy);
		ImGui::Checkbox("team glow", &vars::visuals::glow_team);

		ImGui::NextColumn();
	
		ImGui::ColorEdit4("glow_enemy_color", vars::visuals::glow_enemy_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
		ImGui::ColorEdit4("glow_team_color", vars::visuals::glow_team_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
		break;
	case TAB_MISC:
		ImGui::Checkbox("bhop", &vars::misc::bhop);
		break;
	case TAB_CONFIG:
		break;
	}

	ImGui::End();
}

bool menu::initialize(IDirect3DDevice9* device) {
	hwnd = FindWindow("Valve001", "Counter-Strike: Global Offensive");
	original_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wndproc)));

	ImGui::CreateContext();  // ImGuiIO& io = ImGui::GetIO(); 
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