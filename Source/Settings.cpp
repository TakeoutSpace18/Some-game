#include "Settings.h"

#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void Settings::load() {
    std::ifstream input(_jsonFilePath);
    if (input.is_open()) {
        input >> _file;
        input.close();
    } else {
        loadDefault();
    }
}

void Settings::loadDefault() {
    _file = json::parse(_defaultSettings);
}

void Settings::save() {
    std::ofstream output(_jsonFilePath);
    output << std::setw(4) << _file;
    output.close();
}

json& Settings::get(const char* key) {
    return _file[key];
}
