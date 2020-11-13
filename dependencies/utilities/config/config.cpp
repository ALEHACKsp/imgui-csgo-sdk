#include "config.h"
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <fstream>
#include <experimental/filesystem>

#include "../../json/json.hpp"
#include "../../../core/menu/variables.hpp"

// j = nlohmann::json object
// var = variable name found in variables.hpp
// space = namespace of variable excluding the "vars" namespace
#define READ(j, var, space) vars::space::var = j[#space][#var];
#define READ_ARR(j, var, space) std::copy(j[#space][#var].begin(), j[#space][#var].end(), vars::space::var);
#define WRITE(j, var, space) j[#space][#var] = vars::space::var;

void config::exists(const char* file) {
	if (std::experimental::filesystem::exists(file)) return;
	else save();
}

void config::load() {
	exists(config_file);

	nlohmann::json j;
	std::fstream read(config_file);
	read >> j;
	read.close();

	READ(j, glow_enemy, visuals)
	READ(j, glow_team, visuals)
	READ(j, glow_bomb, visuals)
	READ_ARR(j, glow_enemy_color, visuals)
	READ_ARR(j, glow_team_color, visuals)
	READ_ARR(j, glow_bomb_color, visuals)

	READ(j, bhop, misc)
	READ(j, rank_reveal, misc)
	READ(j, radar, misc)
}

void config::save() {
	nlohmann::json j;

	WRITE(j, glow_enemy, visuals)
	WRITE(j, glow_team, visuals)
	WRITE(j, glow_bomb, visuals)
	WRITE(j, glow_enemy_color, visuals)
	WRITE(j, glow_team_color, visuals)
	WRITE(j, glow_bomb_color, visuals)

	WRITE(j, bhop, misc)
	WRITE(j, rank_reveal, misc)
	WRITE(j, radar, misc)

	std::ofstream write(config_file);
	write << j << std::endl;
	write.close();
}