#pragma once
#include <SFML/Graphics.hpp>

class Application;

class Statistics
{
public:
	Statistics(Application& app);

	void update(float delta, unsigned int draw_calls_counter);
	void render();

private:
	Application* m_p_application;
	sf::Text m_text;
	float m_updateTime;
	unsigned short m_frames, m_cur_fps;
};