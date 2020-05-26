#pragma once
#include <SFML/Graphics.hpp>

#include <memory>
#include <stack>

#include "States/State_Base.h"

class Application
{
public:

	Application();

	void runMainLoop();
	void draw(const sf::Drawable& obj);
	void pushState(std::unique_ptr<State_Base> state);
	void popState();

private:

	void handleEvents();
	void toggleFullscreen();
	void configureWindow();

	sf::RenderWindow m_window;
	sf::VideoMode m_videomode;
	std::stack<std::unique_ptr<State_Base>> m_states;

};

