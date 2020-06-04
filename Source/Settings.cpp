#include <fstream>
#include <iomanip>

#include "Tools/json.hpp"
#include "Settings.h"

using json = nlohmann::json;

Settings::Settings()
{
	load();
}

void Settings::load()
{
	std::ifstream input(m_path);
	if (input.is_open())
	{
		input >> m_file;
		input.close();
	}
	else
	{
		m_file = json::parse(m_defaultSettings);
	}
}

void Settings::save()
{
	std::ofstream output(m_path);
	output << std::setw(4) << m_file;
	output.close();
}

json& Settings::operator[](const char* key)
{
	return m_file[key];
}