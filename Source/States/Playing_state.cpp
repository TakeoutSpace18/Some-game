#include "Playing_state.h"
#include "../Resourse_Managers/TilesetManager.h"

State::Playing::Playing(Application& app) : State_Base(app)
{
	m_level.load(1);
	TilesetManager tileset{ 2, Textures::Main_tileset, *m_p_application };
	m_player = Player(m_level.getCollisionRects(), *m_p_application);
	onWindowResize();
}

void State::Playing::update(float dt)
{
	m_level.update();
	m_player.update(dt);
}

void State::Playing::input(sf::Event& event)
{
	m_player.input(event);
}

void State::Playing::handleSignal(Signal signal)
{
}

void State::Playing::render()
{
	m_level.render();
	m_p_application->draw(m_player);
}

void State::Playing::onWindowResize()
{
	float scale_factor = m_p_application->getScaleFactor();
	m_level.setScale(scale_factor);
	m_player.setScale(scale_factor);
}