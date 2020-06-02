#pragma once
#include "State_Base.h"

namespace State
{
	class Splash_screen : public State_Base
	{
	public:
		Splash_screen(Application& app);

		void update(sf::Time& dt);
		void input(sf::Event& event);
		void render();
	private:
		void onWindowResize();

		sf::Sprite m_logo;
		sf::RectangleShape m_background;
		sf::Clock m_clock;
	};
}