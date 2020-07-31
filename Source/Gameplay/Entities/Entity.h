#pragma once
#include "SFML/Graphics.hpp"
#include "../AnimationHandler.h"

class Entity : public sf::Drawable
{
public:
	Entity(std::vector<sf::FloatRect>& collision_rects, Application& app) : m_p_collision_rects(&collision_rects), m_p_application(&app) {};

	void check_collision();
	
	void update(sf::Time& dt);
	void render();

	void setScale(float scale);
	void setTextureSize(sf::Vector2i size) { m_animation_handler.setTextureSize(size); }

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	sf::Sprite m_sprite;
	AnimationHandler m_animation_handler{ m_sprite, *m_p_application };

	std::string m_name;
	
	sf::Vector2i m_targetSpeed;
	sf::Vector2i m_currentSpeed;

	std::vector<sf::FloatRect>* m_p_collision_rects;
	Application* m_p_application;
};