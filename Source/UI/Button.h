#pragma once
#include <SFML/Graphics.hpp>

#include "../Tools/ColorFadeManager.h"

const sf::Color outline_color(117, 117, 117);
const sf::Color non_active_fill_color(214, 214, 214);
const sf::Color active_fill_color(166, 166, 166);

class Application;

class Button : public sf::Drawable
{
public:
	Button(sf::Vector2f center, sf::Vector2f size, const std::string& text, unsigned int text_size, float scale_factor, Application& app);

	void update();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool m_isActive;
	bool m_inFade;
	sf::Text m_text;
	sf::RectangleShape m_shape;
	sf::FloatRect m_rect;
	ColorFadeManager m_fade;
	Application* m_p_application;
};