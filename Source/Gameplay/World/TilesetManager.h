#pragma once
#include <SFML/Graphics.hpp>
#include <map>

#include "../../Resourse_Managers/Resourses.h"
#include "Block.h"
#include "../../Tools/json.hpp"
#include "../../Application.h"

using json = nlohmann::json;

class TilesetManager
{
public:
	TilesetManager(){};
	TilesetManager(short tileset_id) { load(tileset_id); };

	void load(short tileset_id);
	Block getBlock(short id, sf::Vector2f position);
	sf::Vector2u getBlockUV(short id);

	const sf::Texture& getTexture() { return m_texture; }

private:
	std::map<short, Block_properties> m_properties;

	sf::Texture m_texture;

	short m_columns;
	short m_tilesize;
};