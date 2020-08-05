#pragma once
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "AnimatedBlock.h"
#include "../../Application.h"
#include "../../Tools/json.hpp"

using json = nlohmann::json;

class Level : public sf::Transformable
{
public:
	Level(Application& app);

	void load(short id);
	void update();
	void render();
	
	void setScale(float scale);

	std::vector<sf::FloatRect>& getCollisionRects() { return m_collision_rects; }
	
private:
	sf::Vector2i m_level_size;
	sf::RenderStates m_renderstates;

	std::vector<sf::VertexArray> m_layers;
	std::vector<AnimatedBlock> m_animated_blocks;
	
	std::vector<sf::RectangleShape> m_visible_rects; // DEBUG

	std::vector<sf::FloatRect> m_collision_rects;

	Application* m_p_application;
};