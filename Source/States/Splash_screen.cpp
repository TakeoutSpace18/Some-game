#include "Splash_screen.h"
#include "Main_menu.h"
#include "../Application.h"

State::Splash_screen::Splash_screen(Application& app) : State_Base(app)
{
	m_logo.setTexture(m_p_application->getResourses().textures.get(Textures::Logo));
	m_logo.setColor(sf::Color(255, 255, 255, 0));
	m_background.setFillColor(sf::Color::White);
	onWindowResize();
	m_mode = Mode::FadeIn;
	m_fade = FadeManager(sf::seconds(1), 0, 255);
}

void State::Splash_screen::onWindowResize()
{
	m_background.setSize(m_p_application->getWindowSize());
	if (m_p_application->getWindowSize().x <= 770)
		m_logo.setScale(1, 1);
	else if (m_p_application->getWindowSize().x > 770 && m_p_application->getWindowSize().x <= 1300)
		m_logo.setScale(2, 2);
	else if (m_p_application->getWindowSize().x > 1300)
		m_logo.setScale(3, 3);
	
	m_logo.setPosition(m_p_application->getWindowSize().x / 2 - m_logo.getGlobalBounds().width / 2,
					   m_p_application->getWindowSize().y / 2 - m_logo.getGlobalBounds().height / 2);
}

void State::Splash_screen::update(sf::Time& dt)
{
	switch (m_mode)
	{	
	case State::Splash_screen::Mode::FadeIn:
		if (m_fade.isOver())
		{
			m_logo.setColor(sf::Color(255, 255, 255, 255));
			m_fade = FadeManager(sf::seconds(1));
			m_mode = Mode::Waiting;
			break;
		}
		m_logo.setColor(sf::Color(255, 255, 255, m_fade.getCurrentValue()));
		break;

	case State::Splash_screen::Mode::Waiting:
		if (m_fade.isOver())
		{
			m_p_application->pushState(std::make_unique<State::Main_menu>(*m_p_application));
			m_fade = FadeManager(sf::seconds(1), 255, 0);
			m_mode = Mode::FadeOut;
		}
		break;

	case State::Splash_screen::Mode::FadeOut:
		if (m_fade.isOver())
		{
			m_p_application->popState();
			break;
		}
		m_logo.setColor(sf::Color(255, 255, 255, m_fade.getCurrentValue()));
		m_background.setFillColor(sf::Color(255, 255, 255, m_fade.getCurrentValue()));
		break;
	}
}

void State::Splash_screen::input(sf::Event& event) {};

void State::Splash_screen::render()
{
	m_p_application->draw(m_background);
	m_p_application->draw(m_logo);
}