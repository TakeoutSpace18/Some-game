#include "Main_menu.h"
#include "../Application.h"
#include "../UI/Button.h"

State::Main_menu::Main_menu(Application& app) : State_Base(app)
{
	onWindowResize();
}

void State::Main_menu::onWindowResize()
{
	float scale_factor = 2;
	m_buttons.clear();
	m_buttons.push_back(Button(sf::Vector2f(m_p_application->getWindowSize().x / 2, m_p_application->getWindowSize().y / 2),
							button_size, "Button test", 26, *m_p_application));
}

void State::Main_menu::update(sf::Time& dt)
{

}

void State::Main_menu::input(sf::Event& event) {};

void State::Main_menu::render()
{
	for (int i = 0; i < m_buttons.size(); i++)
		m_p_application->draw(m_buttons[i]);
}