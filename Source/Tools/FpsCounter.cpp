#include "FpsCounter.h"
#include "../Application.h"
#include "../Resourse_Managers/Resourses.h"

FpsCounter::FpsCounter(Application& app) : m_p_application(&app)
{
	m_frames = 0;
	m_text.setFont(m_p_application->getResourses().fonts.get(Fonts::Sansation));
	m_text.setPosition(10, 10);
	m_text.setCharacterSize(20);
}

void FpsCounter::update(sf::Time delta)
{
	m_updateTime += delta;
	m_frames++;

	if (m_updateTime > sf::seconds(1.0f))
	{
		m_text.setString("FPS: " + std::to_string(m_frames));
		m_frames = 0;
		m_updateTime -= sf::seconds(1.0f);
	}
}

void FpsCounter::render()
{
	m_p_application->draw(m_text);
}
