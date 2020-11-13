#pragma once

namespace vars {
	namespace visuals {
		inline bool glow_enemy = false;
		inline bool glow_team = false;
		inline bool glow_bomb = false;
		inline float glow_enemy_color[4] = { 1.f, 0.f, 0.f, 1.f };
		inline float glow_team_color[4] = { 0.f, 0.f, 1.f, 1.f };
		inline float glow_bomb_color[4] = { 1.f, 0.5f, 0.f, 1.f };
	}

	namespace misc {
		inline bool bhop = false;
		inline bool rank_reveal = false;
		inline bool radar = false;
	}
}