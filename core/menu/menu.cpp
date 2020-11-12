#include "menu.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void menu::render() {
	ImGui::Begin("csgo-sdk");
	ImGui::Checkbox("bhop", &vars::misc::bhop);
	ImGui::End();
}

bool menu::initialize(IDirect3DDevice9* device) {
	hwnd = FindWindow("Valve001", "Counter-Strike: Global Offensive");
	original_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wndproc)));

	ImGui::CreateContext();  // ImGuiIO& io = ImGui::GetIO(); 
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