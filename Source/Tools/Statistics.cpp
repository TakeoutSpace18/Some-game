#include "Statistics.h"
#include "../Application.h"
#include "../Resourse_Managers/Resourses.h"

Statistics::Statistics(Application& app) : m_p_application(&app)
{
	m_frames = 0;
	m_text.setFont(m_p_application->getFont(Fonts::SegoeUI));
	m_text.setPosition(10, 10);
	m_text.setCharacterSize(20);
	m_text.setFillColor(sf::Color::Red);
}

void Statistics::update(sf::Time delta, unsigned int draw_calls_counter)
{
	m_updateTime += delta;
	m_frames++;

	if (m_updateTime > sf::seconds(1.0f))
	{
		m_cur_fps = m_frames;
		m_frames = 0;
		m_updateTime -= sf::seconds(1.0f);
	}
	
	m_text.setString("FPS: " + std::to_string(m_cur_fps) + "\nDCpF: " + std::to_string(draw_calls_counter));
}

void Statistics::render()
{
	m_p_application->draw(m_text);
}
