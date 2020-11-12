#pragma once

namespace hooks {
	bool initialize();
	void release();

	inline unsigned int get_virtual(void* _class, unsigned int index) { return static_cast<unsigned int>((*static_cast<int**>(_class))[index]); }

	namespace create_move {
		using fn = bool(__stdcall*)(float, c_usercmd*);
		bool __stdcall hook(float input_sample_frametime, c_usercmd* cmd);
	};

	namespace paint_traverse {
		using fn = void(__thiscall*)(i_panel*, unsigned int, bool, bool);
		void __stdcall hook(unsigned int panel, bool force_repaint, bool allow_force);
	}

	namespace endscene {
		using fn = HRESULT(__thiscall*)(void*, IDirect3DDevice9*);
		HRESULT __stdcall hook(IDirect3DDevice9* device);
	}

	namespace reset {
		using fn = long(__thiscall*)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
		long __stdcall hook(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params);
	}

	namespace do_post_screen_effects {
		using fn = bool(__thiscall*)(void*, view_setup_t*);
		bool __stdcall hook(view_setup_t* setup);
	}
}
