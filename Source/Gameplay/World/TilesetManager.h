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
	TilesetManager(short tileset_id, Application& app) : m_p_application(&app) { load(tileset_id); };

	void load(short tileset_id);

	Block getBlock(short id, sf::Vector2f position);
	sf::Vector2u getBlockUV(short id);
	const Block_properties& getBlockProperties(short id);

private:
	std::map<short, Block_properties> m_properties;

	short m_columns;
	short m_tilesize;

	Application* m_p_application;
};