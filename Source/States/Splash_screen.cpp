#include "Splash_screen.h"
#include "../Application.h"

State::Splash_screen::Splash_screen(Application& app) : State_Base(app)
{
	m_logo.setTexture(m_p_application->getResourses().textures.get(Textures::Logo));
	m_background.setFillColor(sf::Color::White);
	onWindowResize();
}

void State::Splash_screen::onWindowResize()
{
	m_background.setSize(m_p_application->getWindowSize());
	if (m_p_application->getWindowSize().x <= 600)
		m_logo.setScale(1, 1);
	else if (m_p_application->getWindowSize().x > 600)
		m_logo.setScale(2, 2);
	
	m_logo.setPosition(m_p_application->getWindowSize().x / 2 - m_logo.getGlobalBounds().width / 2,
					   m_p_application->getWindowSize().y / 2 - m_logo.getGlobalBounds().height / 2);
}

void State::Splash_screen::update(sf::Time& dt)
{

}

void State::Splash_screen::input(sf::Event& event)
{

}

void State::Splash_screen::render()
{
	m_p_application->draw(m_background);
	m_p_application->draw(m_logo);
}