#include "Playing_state.h"

State::Playing::Playing(Application& app) : State_Base(app)
{
	m_level.load(1);
	onWindowResize();
}

void State::Playing::update(sf::Time& dt)
{
	m_level.update();
}

void State::Playing::input(sf::Event& event)
{
}

void State::Playing::handleSignal(Signal signal)
{
}

void State::Playing::render()
{
	m_level.render();
}

void State::Playing::onWindowResize()
{
	float scale_factor = m_p_application->getScaleFactor();
	m_level.setScale(scale_factor);
}