#include "TilesetManager.h"

#include <stdexcept>
#include <fstream>
#include <iostream>

void TilesetManager::load(short tileset_id, Textures texture_place)
{
	m_properties.clear();

	std::ifstream input("data\\tilesets\\tileset_" + std::to_string(tileset_id) + ".json");
	if (input.is_open())
	{
		json json_file;
		input >> json_file;
		input.close();

		m_columns = json_file["columns"];

		m_p_application->loadTexture(texture_place, "data" + json_file["image"].get<std::string>().erase(0, 2));


		for (auto& tile : json_file["tiles"])
		{
			Block_properties props;
			std::string animation_name = std::to_string(tile["id"].get<int>());

			for (auto property : tile["properties"])
			{
				if (property["type"] == "bool" && property["value"].get<bool>() == true)
				{
					if (property["name"] == "isSolid")
						props.isSolid = true;
					else if (property["name"] == "isBreakable")
						props.isBreakable = true;
					else if (property["name"] == "isTransparent")
						props.isTransparent = true;
				}

				else if (property["type"] == "string" && property["name"] == "animationName")
				{
					animation_name = property["value"].get<std::string>();
				}
			}

			if (!tile["animation"].is_null())
			{
				props.isAnimated = true;
				m_p_application->loadAnimation(animation_name, tile["animation"], *this);
			}

			m_properties.insert(std::make_pair(tile["id"].get<short>(), props));
		}
	}
	else
		throw std::runtime_error("Failed to load tileset" + std::to_string(tileset_id));
}

sf::Vector2u TilesetManager::getBlockUV(short id)
{
	return sf::Vector2u(id % m_columns * g_tilesize, id / m_columns * g_tilesize);
}

const Block_properties& TilesetManager::getBlockProperties(short id)
{
	auto found = m_properties.find(id);
	if (found == m_properties.end())
		return Block_properties();
	return found->second;
}
