#pragma once
#include <SFML/Graphics.hpp>

#include <memory>
#include <stack>

#include "States/State_Base.h"
#include "Settings.h"
#include "Tools/FpsCounter.h"
#include "Resourse_Managers/Resourses.h"

class Application
{
public:

	Application();

	void runMainLoop();
	void draw(const sf::Drawable& obj);
	void pushState(std::unique_ptr<State::State_Base> state);
	void popState();
	void setView(sf::View view);

	const ResourseHolder& getResourses() const { return m_resourses; }

private:

	void handleEvents();
	void toggleFullscreen();
	void configureWindow();

	ResourseHolder m_resourses;
	Settings m_settings;
	FpsCounter m_fpscounter{ *this };

	sf::RenderWindow m_window;
	std::stack<std::unique_ptr<State::State_Base>> m_states;

};

