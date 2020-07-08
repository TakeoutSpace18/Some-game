#include "TilesetManager.h"

#include <stdexcept>
#include <fstream>
#include <iostream>

TilesetManager::TilesetManager()
{
}

void TilesetManager::load(short tileset_id)
{
	std::ifstream input("data\\tilesets\\tileset_" + std::to_string(tileset_id) + ".json");
	if (input.is_open())
	{
		json json_file;
		input >> json_file;
		input.close();
		for (auto tile : json_file["tiles"])
		{
			m_textures.load(tile["id"].get<short>(), "data" + tile["image"].get<std::string>().erase(0, 2));
			Block_properties props;
			for (auto property : tile["properties"])
			{
				if (property["value"].get<bool>() == true)
				{
					if (property["name"] == "isSolid")
						props.isSolid = true;
					else if (property["name"] == "isBreakable")
						props.isBreakable = true;
					else if (property["name"] == "isTransparent")
						props.isTransparent = true;
				}
			}

			m_properties.insert(std::make_pair(tile["id"].get<short>(), std::move(props)));
		}
	}
	else
		throw std::runtime_error("Failed to load tileset" + std::to_string(tileset_id));
}

Block TilesetManager::getBlock(short id, sf::Vector2f position)
{
	return Block(m_textures.get(id), m_properties.find(id)->second, position);
}