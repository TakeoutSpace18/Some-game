#pragma once
#include <string>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Settings {
   public:
    static void load();
    static void loadDefault();
    static void save();

    static json& get(const char* key);

    template <typename T>
    static T get(const char* key) {
        return _file[key].get<T>();
    }

   private:
    inline static constexpr auto _jsonFilePath = "data\\settings.json";
    inline static constexpr auto _defaultSettings =
        R"({
		"windowedModeWidth"		: 704,
		"windowedModeHeight"	: 396,
		"minimalWindowWidth"	: 704,
		"minimalWindowHeight"	: 396,
		"isFullscreen"			: false,
		"showStatistics"		: true,
		"uiScale"				: 2,
		})";

    inline static json _file;
};
