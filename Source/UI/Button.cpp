#include "Button.h"
#include "../Application.h"

Button::Button(sf::Vector2f center, sf::Vector2f size, const std::string& text, unsigned int text_size, float scale_factor, Application& app)
	: m_p_application(&app)
{
	m_isActive = false;
	m_inFade = false;

	m_shape.setPosition(sf::Vector2f(center.x - size.x * scale_factor / 2, center.y - size.y * scale_factor / 2));
	m_shape.setSize(size * scale_factor);
	m_shape.setFillColor(non_active_fill_color);
	m_shape.setOutlineColor(outline_color);
	m_shape.setOutlineThickness(3 * scale_factor);

	m_rect = m_shape.getGlobalBounds();

	m_text.setFont(m_p_application->getResourses().fonts.get(Fonts::SegoeUI));
	m_text.setCharacterSize(text_size * scale_factor);
	m_text.setFillColor(sf::Color::Black);
	m_text.setString(text);
	m_text.setOrigin(m_text.getGlobalBounds().left, m_text.getGlobalBounds().top);
	m_text.setPosition(center.x - m_text.getGlobalBounds().width / 2, center.y - m_text.getGlobalBounds().height / 2);
}

void Button::update()
{
	if (m_rect.contains(sf::Vector2f(m_p_application->getMousePosition())))
	{
		if (!m_isActive)
		{
			m_isActive = true;
			m_inFade = true;
			m_fade = ColorFadeManager(sf::seconds(0.1), non_active_fill_color, active_fill_color);
		}
	}
	else
	{
		if (m_isActive)
		{
			m_isActive = false;
			m_inFade = true;
			m_fade = ColorFadeManager(sf::seconds(0.1), active_fill_color, non_active_fill_color);
		}
	}

	if (m_inFade)
		if (m_fade.isOver())
		{
			m_inFade = false;			
			m_shape.setFillColor(m_fade.getFinalColor());
		}
		else
			m_shape.setFillColor(m_fade.getCurrentColor());
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape, states);
	target.draw(m_text, states);
}