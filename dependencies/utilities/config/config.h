#pragma once

namespace config {
	inline const char* config_file = "C:\\Users\\Public\\Documents\\config.json";

	void exists(const char* file);
	void load();
	void save();
}