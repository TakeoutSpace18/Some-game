#include "State_Test.h"
#include "../Application.h"

State::Test::Test(Application& app) : State_Base(app)
{
	m_square.setSize(sf::Vector2f(130, 130));
	m_square.setPosition(120, 120);
	m_square.setFillColor(sf::Color::Green);
}

void State::Test::update(sf::Time& dt)
{
	m_square.rotate(dt.asSeconds() * 20);
}

void State::Test::input(sf::Event& event)
{

}

void State::Test::render()
{
	m_p_application->draw(m_square);
}