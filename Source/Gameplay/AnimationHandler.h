﻿#pragma once
#include <SFML/Graphics.hpp>

#include "../Application.h"
#include "../Resourse_Managers/AnimationManager.h"

class AnimationHandler
{
public:
	AnimationHandler(Application& app);;
	AnimationHandler(sf::Sprite& sprite, Application& app);;
	AnimationHandler(sf::Sprite& sprite, sf::Vector2i texture_size, Application& app);;
	
	void setSprite(sf::Sprite& sprite) { m_p_sprite = &sprite; };
	void setTextureSize(sf::Vector2i size);
	void setAnimation(std::string& name, bool endless = true);

	void update();
	
private:
	bool m_is_endless;

	sf::IntRect m_texture_rect;
	std::vector<Frame>::const_iterator m_cur_frame;
	time_point<steady_clock> m_start;
	
	std::vector<Frame>* m_p_cur_animation;
	sf::Sprite* m_p_sprite;
	
	Application* m_p_application;
};