#pragma once
#include "State_Base.h"
#include "../Gameplay/World/Level.h"

namespace State
{
	class Playing : public State_Base
	{
	public:
		Playing(Application& app);

		void update(sf::Time& dt);
		void input(sf::Event& event);
		void handleSignal(Signal signal);
		void render();
	private:

		void onWindowResize();

		Level m_level{*m_p_application};
	};
}