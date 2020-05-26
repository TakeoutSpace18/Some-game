#include "Application.h"

#include "Icon.h"
#include "States/State_Test.h"

Application::Application()
{
	m_isFullscreen = false;
	m_videomode = sf::VideoMode(300, 300);
	m_window.create(m_videomode, "Some-game");
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
	if (!m_isFullscreen)
	{
		m_window.create(sf::VideoMode::getDesktopMode(), "000", sf::Style::Fullscreen);
	}
	else
	{
		m_window.create(m_videomode, "000");
	}

	configureWindow();
	m_states.top()->setViewSize(m_window.getDefaultView());
	m_isFullscreen = !m_isFullscreen;
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
			m_window.display();
		}
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
			//m_states.top()->setViewSize(m_window.getDefaultView());
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