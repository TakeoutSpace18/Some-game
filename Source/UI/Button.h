#pragma once
#include <SFML/Graphics.hpp>

const sf::Color outline_color(117, 117, 117);
const sf::Color non_active_fill_color(214, 214, 214);
const sf::Color active_fill_color(166, 166, 166);

class Application;

class Button : public sf::Drawable
{
public:
	Button(sf::Vector2f center, sf::Vector2f size, const std::string& text, unsigned int text_size, Application& app);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Text m_text;
	sf::RectangleShape m_rectangle;
	Application* m_p_application;
};