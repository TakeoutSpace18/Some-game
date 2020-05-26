#include "Application.h"

#include "Icon.h"
#include "State_Test.h"

Application::Application()
{
	m_videomode = sf::VideoMode(300, 300);
	m_window.create(m_videomode, "Some-game");
	pushState(std::make_unique<State::Test>(*this));
	runMainLoop();
}

void Application::configureWindow()
{
	m_window.setIcon(icon.width, icon.height, icon.pixel_data);
	m_window.setKeyRepeatEnabled(false);
	m_window.setVerticalSyncEnabled(true);
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
		else m_states.top()->input(event);
	}
}

void Application::draw(const sf::Drawable& obj)
{
	m_window.draw(obj);
}

void Application::pushState(std::unique_ptr<State_Base> state)
{
	m_states.push(std::move(state));
}

void Application::popState()
{
	m_states.pop();
}