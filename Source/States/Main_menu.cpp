#include "Main_menu.h"

#include "Playing_state.h"
#include "../Application.h"
#include "../UI/Button.h"

State::Main_menu::Main_menu(Application& app) : State_Base(app)
{
	m_mode = Mode::Active;
	m_background.setFillColor(sf::Color::White);
	onWindowResize();
}

void State::Main_menu::onWindowResize()
{
	m_background.setSize(m_p_application->getWindowSize());

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
	switch (m_mode)
	{
	case State::Main_menu::Mode::Active:

		for (int i = 0; i < m_buttons.size(); i++)
			m_buttons[i].update();
		break;

	case State::Main_menu::Mode::FadeOut:
		if (m_fade.isOver())
		{
			m_p_application->popState();
			break;
		}
		sf::Uint8 opacity = m_fade.getCurrentValue();
		m_background.setFillColor(sf::Color(255, 255, 255, opacity));
		for (int i = 0; i < m_buttons.size(); i++)
			m_buttons[i].setOpacity(opacity);
		break;
	}
}

void State::Main_menu::input(sf::Event& event)
{
	for (auto &button : m_buttons)
		button.input(event, m_buttons);
}

void State::Main_menu::handleSignal(Signal signal)
{
	if (signal.type == Signal::ButtonClicked)
	{
		if (signal.button.id == Button::ID::Play)
		{
			m_p_application->pushState(std::make_unique<State::Playing>(*m_p_application));
			m_fade = FadeManager(sf::seconds(m_p_application->getSettings().get<int>("state_change_duration")), 255, 0);
			m_mode = Mode::FadeOut;
		}
	}
}

void State::Main_menu::render()
{
	m_p_application->draw(m_background);
	for (auto &button : m_buttons)
		m_p_application->draw(button);
}