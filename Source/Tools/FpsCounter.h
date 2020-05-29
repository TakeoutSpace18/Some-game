#pragma once
#include <SFML/Graphics.hpp>

class Application;

class FpsCounter
{
public:
	FpsCounter(Application& app);

	void update(sf::Time delta);
	void render();

private:
	Application* m_p_application;
	sf::Text m_text;
	sf::Time m_updateTime;
	unsigned short m_frames;

	sf::Font m_font; // временно! 
};
