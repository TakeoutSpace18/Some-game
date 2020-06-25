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
		"cur_win_width"			: 704,
		"cur_win_height"		: 396,
		"last_win_width"		: 704,
		"last_win_height"		: 396,
		"min_win_width"			: 704,
		"min_win_height"		: 396,
		"win_title"				: "Some-game",
		"is_fullscreen"			: false,
		"show_fps"				: true,
		"ui_scale"				: 1,
		"state_change_duration" : 1
		})";

	json m_file;
};

