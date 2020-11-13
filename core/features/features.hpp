#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "../menu/variables.hpp"

namespace features {
	namespace visuals {
		void glow();
	}

	namespace misc {
		void bunny_hop(c_usercmd* cmd);	
		void rank_reveal(c_usercmd* cmd);
		void radar();
	}
}