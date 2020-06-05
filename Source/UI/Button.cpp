#include "Button.h"
#include "../Application.h"

Button::Button(sf::Vector2f center, sf::Vector2f size, const std::string& text, unsigned int text_size, float scale_factor, Application& app)
	: m_p_application(&app)
{
	m_rectangle.setPosition(sf::Vector2f(center.x - size.x * scale_factor / 2, center.y - size.y * scale_factor / 2));
	m_rectangle.setSize(size * scale_factor);
	m_rectangle.setFillColor(sf::Color(non_active_fill_color));
	m_rectangle.setOutlineColor(sf::Color(outline_color));
	m_rectangle.setOutlineThickness(3 * scale_factor);

	m_text.setFont(m_p_application->getResourses().fonts.get(Fonts::SegoeUI));
	m_text.setCharacterSize(text_size * scale_factor);
	m_text.setFillColor(sf::Color::Black);
	m_text.setString(text);
	m_text.setOrigin(m_text.getGlobalBounds().left, m_text.getGlobalBounds().top);
	m_text.setPosition(center.x - m_text.getGlobalBounds().width / 2, center.y - m_text.getGlobalBounds().height / 2);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_rectangle, states);
	target.draw(m_text, states);
}