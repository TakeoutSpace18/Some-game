#include "Application.h"
#include "Icon.h"
#include "States/State_Test.h"
#include "Settings.h"

Application::Application()
{
	if (m_settings.get<bool>("is_fullscreen"))
	{
		m_window.create(sf::VideoMode::getDesktopMode(), m_settings.get<std::string>("win_title"), sf::Style::Fullscreen);
	}
	else
	{
		sf::VideoMode videomode(m_settings.get<unsigned int>("win_width"), m_settings.get<unsigned int>("win_height"));
		m_window.create(videomode, m_settings.get<std::string>("win_title"));
	}
	
	configureWindow();
	pushState(std::make_unique<State::Test>(*this));
	runMainLoop();
}

void Application::configureWindow()
{
	m_window.setIcon(icon.width, icon.height, icon.pixel_data);
	m_window.setKeyRepeatEnabled(false);
	m_window.setVerticalSyncEnabled(true);
}

void Application::toggleFullscreen()
{
	if (!m_settings.get<bool>("is_fullscreen"))
	{
		m_window.create(sf::VideoMode::getDesktopMode(), m_settings.get<std::string>("win_title"), sf::Style::Fullscreen);
	}
	else
	{
		sf::VideoMode videomode(m_settings.get<unsigned int>("win_width"), m_settings.get<unsigned int>("win_height"));
		m_window.create(videomode, m_settings.get<std::string>("win_title"));
	}

	configureWindow();
	m_states.top()->setViewSize(m_window.getDefaultView());
	m_settings["is_fullscreen"] = !m_settings.get<bool>("is_fullscreen");
}

void Application::runMainLoop()
{
	sf::Clock clock;

		while (m_window.isOpen())
		{
			sf::Time delta = clock.restart();
			handleEvents();
			m_window.clear();
			m_states.top()->update(delta);
			m_states.top()->render();
			if (m_settings.get<bool>("show_fps"))
			{
				m_fpscounter.update(delta);
				m_fpscounter.render();
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
			m_settings["win_width"] = event.size.width;
			m_settings["win_height"] = event.size.height;
			m_states.top()->setViewSize(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
		}

		else m_states.top()->input(event);
	}
}

void Application::draw(const sf::Drawable& obj)
{
	m_window.draw(obj);
}

void Application::pushState(std::unique_ptr<State::State_Base> state)
{
	m_states.push(std::move(state));
}

void Application::popState()
{
	m_states.pop();
}

void Application::setView(sf::View view)
{
	m_window.setView(view);
}