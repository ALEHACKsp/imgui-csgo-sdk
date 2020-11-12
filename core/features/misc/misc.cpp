#include "../features.hpp"

void features::misc::bunny_hop(c_usercmd* cmd) {
	if (!vars::misc::bhop) return;

	const int move_type = csgo::local_player->move_type();

	if (move_type == movetype_ladder || move_type == movetype_noclip ||
		move_type == movetype_observer) return;

	if (!(csgo::local_player->flags() & fl_onground))
		cmd->buttons &= ~in_jump;
};
