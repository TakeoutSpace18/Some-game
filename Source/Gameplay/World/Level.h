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

class Level : public sf::Transformable
{
public:
	Level(Application& app);

	void load(short id);
	void render();
	void setScale(float scale);

private:
	sf::Vector2i m_level_size;
	sf::RenderStates m_renderstates;

	std::vector<sf::VertexArray> m_layers;
	std::vector<sf::RectangleShape> m_visible_rects;

	std::vector<sf::FloatRect> m_collision_rects;

	Application* m_p_application;
};

