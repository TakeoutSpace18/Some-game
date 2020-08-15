#include "FadeManager.h"

FadeManager::FadeManager(sf::Time duration, int start_val, int target_val)
	: m_duration(duration), m_start_val(start_val), m_target_val(target_val)
{
}

FadeManager::FadeManager(sf::Time duration)
	: m_duration(duration)
{
}


int FadeManager::getCurrentValue()
{
	return m_clock.getElapsedTime().asMilliseconds() * (m_target_val - m_start_val) / m_duration.asMilliseconds() +
		m_start_val;
}

bool FadeManager::isOver()
{
	if (m_clock.getElapsedTime() >= m_duration)
		return true;
	return false;
}
