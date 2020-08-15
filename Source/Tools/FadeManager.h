#pragma once
#include <SFML/Graphics.hpp>

class FadeManager
{
public:
	FadeManager()
	{
	};
	FadeManager(sf::Time duration);
	FadeManager(sf::Time duration, int start_val, int target_val);

	int getCurrentValue();
	bool isOver();

private:
	sf::Clock m_clock;
	sf::Time m_duration;
	int m_start_val{0};
	int m_target_val{0};
};
