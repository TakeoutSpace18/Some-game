#pragma once
#include "Tools/json.hpp"
#include <string>

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
		"win_width"     : 300,
		"win_height"    : 250,
		"win_title"     : "Some-game",
		"is_fullscreen" : false,
		"show_fps"      : true
		})";

	json m_file;
};

