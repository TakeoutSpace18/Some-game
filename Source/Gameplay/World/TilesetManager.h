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

	void load(unsigned char tileset_id);
	Block getBlock(unsigned char id, sf::Vector2f position);

private:
	std::map<unsigned char, Block_properties> m_properties;
	ResourseManager<unsigned char, sf::Texture> m_textures;
};