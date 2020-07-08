#pragma once
#include <SFML/Graphics.hpp>
#include <map>

#include "../../Resourse_Managers/Resourses.h"
#include "Block.h"
#include "../../Tools/json.hpp"

using json = nlohmann::json;

class TilesetManager
{
public:
	TilesetManager();
	TilesetManager(short tileset_id) { load(tileset_id); };

	void load(short tileset_id);
	Block getBlock(short id, sf::Vector2f position);

private:
	std::map<short, Block_properties> m_properties;
	ResourseManager<short, sf::Texture> m_textures;
};