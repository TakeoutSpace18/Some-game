#include <fstream>
#include <iostream>
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
		std::cout << "case 1";
	}
	else
	{
		m_file = json::parse(m_defaultSettings);
		std::cout << "case 2" << std::endl << m_file;
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