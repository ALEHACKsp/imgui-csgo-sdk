#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_impl_dx9.h"
#include "../../dependencies/imgui/imgui_impl_win32.h"
#include "variables.hpp"

namespace menu {
	inline bool opened = false;
	inline bool initialized = false;
	inline HWND hwnd;
	inline WNDPROC original_wndproc;

	void render();

	bool initialize(IDirect3DDevice9* device);
	void release();

	LRESULT WINAPI wndproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
