#pragma once
#include <map>
#include <SFML/Graphics.hpp>

#include "../Application.h"
#include "../Tools/json.hpp"

using json = nlohmann::json;

struct Block_properties
{
	bool isSolid = false;
	bool isBreakable = false;
	bool isTransparent = false;
	bool isAnimated = false;
};

class TilesetManager
{
public:
	TilesetManager(short tileset_id, Application& app) : m_p_application(&app) { load(tileset_id); };

	void load(short tileset_id);

	sf::Vector2u getBlockUV(short id);
	const Block_properties& getBlockProperties(short id);

private:
	std::map<short, Block_properties> m_properties;

	short m_columns;
	short m_tilesize;

	Application* m_p_application;
};