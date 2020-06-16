#include "Main_menu.h"
#include "../Application.h"
#include "../UI/Button.h"

State::Main_menu::Main_menu(Application& app) : State_Base(app)
{
	onWindowResize();
}

void State::Main_menu::onWindowResize()
{
	float scale_factor = m_p_application->getScaleFactor();
	m_buttons.clear();
	m_buttons.push_back(Button(Button::ID::Play, sf::Vector2f(m_p_application->getWindowSize().x / 2, m_p_application->getWindowSize().y / 2 - (button_size.y + button_spacing) * scale_factor),
							button_size, "Play", 26, scale_factor, *m_p_application));
	m_buttons.push_back(Button(Button::ID::Settings, sf::Vector2f(m_p_application->getWindowSize().x / 2, m_p_application->getWindowSize().y / 2),
							button_size, "Settings", 26, scale_factor, *m_p_application));
	m_buttons.push_back(Button(Button::ID::Exit, sf::Vector2f(m_p_application->getWindowSize().x / 2, m_p_application->getWindowSize().y / 2 + (button_size.y + button_spacing) * scale_factor),
							button_size, "Exit", 26, scale_factor, *m_p_application));
}

void State::Main_menu::update(sf::Time& dt)
{
	for (int i = 0; i < m_buttons.size(); i++)
		m_buttons[i].update();
}

void State::Main_menu::input(sf::Event& event)
{
	for (int i = 0; i < m_buttons.size(); i++)
		m_buttons[i].input(event, m_buttons);
}

void State::Main_menu::render()
{
	for (int i = 0; i < m_buttons.size(); i++)
		m_p_application->draw(m_buttons[i]);
}