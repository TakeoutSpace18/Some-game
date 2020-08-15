#include "ColorFadeManager.h"

ColorFadeManager::ColorFadeManager(sf::Time duration, sf::Color start_color, sf::Color target_color)
	: m_duration(duration), m_start_color(start_color), m_target_color(target_color)
{
}

sf::Color ColorFadeManager::getCurrentColor()
{
	sf::Uint8 r, g, b;
	sf::Int32 elapsedTime = m_clock.getElapsedTime().asMilliseconds();
	r = elapsedTime * (m_target_color.r - m_start_color.r) / m_duration.asMilliseconds() + m_start_color.r;
	g = elapsedTime * (m_target_color.g - m_start_color.g) / m_duration.asMilliseconds() + m_start_color.g;
	b = elapsedTime * (m_target_color.b - m_start_color.b) / m_duration.asMilliseconds() + m_start_color.b;
	return sf::Color(r, g, b);
}

bool ColorFadeManager::isOver()
{
	if (m_clock.getElapsedTime() >= m_duration)
		return true;
	return false;
}
