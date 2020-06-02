#pragma once
#include <string>
#include <SFML/Graphics.hpp>

#include "Tools/json.hpp"


using json = nlohmann::json;

class Settings
{
public:
	Settings();

	void load();
	void save();

	json& operator[](const char* key);

	template <typename T>
	T get(const char* key)
	{
		return m_file[key].get<T>();
	}

private:
	const std::string m_path = "data\\settings.json";
	const std::string m_defaultSettings =
		R"({
		"cur_win_width"     : 300,
		"cur_win_height"    : 250,
		"last_win_width"    : 300,
		"last_win_height"   : 250,
		"min_win_width"     : 450,
		"min_win_height"	: 300,
		"win_title"         : "Some-game",
		"is_fullscreen"     : false,
		"show_fps"          : true
		})";

	json m_file;
};

