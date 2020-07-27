#include "Application.h"

#include <iostream>

#include "Icon.h"
#include "Settings.h"
#include "Signal.hpp"
#include "States/Splash_screen.h"
#include "Tools/Random.hpp"

Application::Application()
{
	Random::init();
	
	if (m_settings.get<bool>("is_fullscreen"))
	{
		m_window.create(sf::VideoMode::getDesktopMode(), m_settings.get<std::string>("win_title"), sf::Style::Fullscreen);
	}
	else
	{
		sf::VideoMode videomode(m_settings.get<unsigned int>("cur_win_width"), m_settings.get<unsigned int>("cur_win_height"));
		m_window.create(videomode, m_settings.get<std::string>("win_title"));
	}
	
	configureWindow();
	pushState(std::make_unique<State::Splash_screen>(*this));
	runMainLoop();
}

void Application::configureWindow()
{
	m_window.setIcon(icon.width, icon.height, icon.pixel_data);
	m_window.setKeyRepeatEnabled(false);
	m_window.setVerticalSyncEnabled(false);
}

void Application::toggleFullscreen()
{
	if (!m_settings.get<bool>("is_fullscreen"))
	{
		m_settings["last_win_width"] = m_settings["cur_win_width"];
		m_settings["last_win_height"] = m_settings["cur_win_height"];
		m_window.create(sf::VideoMode::getDesktopMode(), m_settings.get<std::string>("win_title"), sf::Style::Fullscreen);
		m_settings["cur_win_width"] = m_window.getSize().x;
		m_settings["cur_win_height"] = m_window.getSize().y;
	}
	else
	{
		sf::VideoMode videomode(m_settings.get<unsigned int>("last_win_width"), m_settings.get<unsigned int>("last_win_height"));
		m_window.create(videomode, m_settings.get<std::string>("win_title"));
		m_settings["cur_win_width"] = m_settings["last_win_width"];
		m_settings["cur_win_height"] = m_settings["last_win_height"];
	}

	configureWindow();
	for (int i = 0; i < m_states.size(); i++)
	{
		m_states[i]->setViewSize(m_window.getDefaultView());
	}
	m_settings["is_fullscreen"] = !m_settings.get<bool>("is_fullscreen");
}

void Application::runMainLoop()
{
	sf::Clock clock;

		while (m_window.isOpen())
		{
			sf::Time delta = clock.restart();
			m_draw_calls_counter = 0;

			handleEvents();
			m_window.clear();

			for (auto &state : m_states)
				state->update(delta);

			for (auto &state : m_states)
				state->render();
		
			if (m_settings.get<bool>("show_statistics"))
			{
				m_statistics.update(delta, m_draw_calls_counter);
				m_statistics.render();
			}
			m_window.display();
		}
		m_settings.save();
}

void Application::handleEvents()
{
	sf::Event event;
	
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::F11)
			{
				toggleFullscreen();
			}
		}
		else if (event.type == sf::Event::Resized)
		{
			if (event.size.width < m_settings.get<unsigned int>("min_win_width"))
				event.size.width = m_settings.get<unsigned int>("min_win_width");
			if (event.size.height < m_settings.get<unsigned int>("min_win_height"))
				event.size.height = m_settings.get<unsigned int>("min_win_height");

			m_window.setSize(sf::Vector2u(event.size.width, event.size.height));
			m_settings["cur_win_width"] = event.size.width;
			m_settings["cur_win_height"] = event.size.height;
			for (int i = 0; i < m_states.size(); i++)
			{
				m_states[i]->setViewSize(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			}
		}

		m_states.front()->input(event);
	}
}

void Application::handleSignal(Signal signal)
{
	if (signal.type == Signal::ButtonClicked)
	{
		if (signal.button.id == Button::ID::Exit)
		{
			m_window.close();
		}
	}
	m_states.front()->handleSignal(signal);
}

float Application::getScaleFactor()
{
	if (m_window.getSize().x <= sf::VideoMode::getDesktopMode().width / 2)
		return m_settings.get<float>("ui_scale");
	else 
		return m_settings.get<float>("ui_scale") * 2;
}

void Application::draw(const sf::Drawable& obj, const sf::RenderStates& states)
{
	m_window.draw(obj, states);
	m_draw_calls_counter++;
}

void Application::pushState(std::unique_ptr<State::State_Base> state)
{
	m_states.push_front(std::move(state));
}

void Application::popState()
{
	m_states.pop_back();
}

void Application::setView(sf::View view)
{
	m_window.setView(view);
}