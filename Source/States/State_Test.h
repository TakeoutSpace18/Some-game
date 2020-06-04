#pragma once
#include "State_Base.h"

namespace State
{
	class Test : public State_Base
	{
	public:
		Test(Application& app);

		void update(sf::Time& dt);
		void input(sf::Event& event);
		void render();

	private:
		void onWindowResize() {};

		sf::RectangleShape m_square;
	};
}