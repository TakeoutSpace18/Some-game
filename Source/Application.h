#pragma once
#include <SFML/Graphics.hpp>

#include <memory>
#include <deque>

#include "States/State_Base.h"
#include "Settings.h"
#include "Tools/Statistics.h"
#include "Resourse_Managers/Resourses.h"
#include "Signal.hpp"

const short g_tilesize = 16;
const short g_pixel_scale_factor = 2;

class Application
{
public:

	Application();

	void runMainLoop();
	void draw(const sf::Drawable& obj, const sf::RenderStates& states = sf::RenderStates::Default);
	void pushState(std::unique_ptr<State::State_Base> state);
	void popState();
	void setView(sf::View view);
	void handleSignal(Signal signal);

	float getScaleFactor();
	ResourseHolder& getResourses() { return m_resourses; }
	Settings& getSettings() { return m_settings; }
	sf::Vector2f getWindowSize() { return sf::Vector2f(m_window.getSize().x, m_window.getSize().y); }
	sf::Vector2i getMousePosition() { return sf::Mouse::getPosition(m_window); }

	const sf::Texture& getTexture(Textures id) const { return m_resourses.textures.get(id); }
	const sf::Font& getFont(Fonts id) const { return m_resourses.fonts.get(id); }
	std::vector<Frame>& getAnimation(std::string name) { return m_resourses.animations.get(name); }

	void loadTexture(Textures id, const std::string& filename) { m_resourses.textures.load(id, filename); }

	void loadAnimation(const std::string& name, json& animation, TilesetManager& tileset)
	{
		m_resourses.animations.load(name, animation, tileset);
	}

private:

	void handleEvents();
	void toggleFullscreen();
	void configureWindow();

	unsigned int m_draw_calls_counter;

	ResourseHolder m_resourses;
	Settings m_settings;
	Statistics m_statistics{*this};

	sf::RenderWindow m_window;
	std::deque<std::unique_ptr<State::State_Base>> m_states;
};
