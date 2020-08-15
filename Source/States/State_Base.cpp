#include "State_Base.h"
#include "../Application.h"

State::State_Base::State_Base(Application& app)
	: m_p_application(&app)
{
}

void State::State_Base::setViewSize(sf::View view)
{
	m_p_application->setView(view);
	onWindowResize();
}
