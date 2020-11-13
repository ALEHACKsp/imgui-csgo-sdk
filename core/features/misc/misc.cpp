#include "../features.hpp"

void features::misc::bunny_hop(c_usercmd* cmd) {
	if (!vars::misc::bhop) return;

	const int move_type = csgo::local_player->move_type();

	if (move_type == movetype_ladder || move_type == movetype_noclip ||
		move_type == movetype_observer) return;

	if (!(csgo::local_player->flags() & fl_onground))
		cmd->buttons &= ~in_jump;
};

void features::misc::rank_reveal(c_usercmd* cmd) {
	if (!vars::misc::rank_reveal) return;

	if (cmd->buttons & in_score)
		interfaces::client->dispatch_user_message(cstrike15_user_message_t::cs_um_serverrankrevealall, NULL, NULL, nullptr);
}

void features::misc::radar() {
	if (!vars::misc::radar) return;
	if (!interfaces::engine->is_in_game()) return;

	for (auto i = 1; i < interfaces::globals->max_clients; i++)
	{
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

		if (!entity || !entity->is_alive() || entity->dormant()) continue;
		if (entity->team() == csgo::local_player->team()) continue;

		entity->spotted() = true;
	}
}
