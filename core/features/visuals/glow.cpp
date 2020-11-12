#include "../features.hpp"

void features::visuals::glow() {
	if (!vars::visuals::glow_enemy && !vars::visuals::glow_team) return;
	if (!csgo::local_player || !interfaces::engine->is_in_game()) return;

	for (auto i = 0; i < interfaces::glow_manager->size; i++) {
		if (interfaces::glow_manager->objects[i].unused() || !interfaces::glow_manager->objects[i].entity) continue;

		auto glow = &interfaces::glow_manager->objects[i];

		switch (glow->entity->client_class()->class_id) {
		case class_ids::ccsplayer:
			if (glow->entity->team() != csgo::local_player->team() && vars::visuals::glow_enemy)
				glow->set(vars::visuals::glow_enemy_color);
			if (glow->entity->team() == csgo::local_player->team() && vars::visuals::glow_team)
				glow->set(vars::visuals::glow_team_color);
			break;
		}
	}
}