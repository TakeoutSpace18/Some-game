#pragma once
#include <vector>
#include "State_Base.h"
#include "../UI/Button.h"

const sf::Vector2f button_size(140, 40);

namespace State
{
	class Main_menu : public State_Base
	{
	public:
		Main_menu(Application& app);

		void update(sf::Time& dt);
		void input(sf::Event& event);
		void render();
	private:
		void onWindowResize();

		std::vector<Button> m_buttons;
	};
}