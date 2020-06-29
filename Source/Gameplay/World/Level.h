#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

#include "Block.h"
#include "../../Application.h"
#include "../../Resourse_Managers/Resourses.h"
#include "../../Tools/json.hpp"
#include "TilesetManager.h"

using json = nlohmann::json;

class Level
{
public:
	Level(Application& app);

	void load(unsigned char id);
	void render();

private:

	std::vector<Block> m_blocks;
	TilesetManager m_tileset;

	Application* m_p_application;
};

