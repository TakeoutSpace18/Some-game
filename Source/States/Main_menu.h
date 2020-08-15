#pragma once
#include <vector>
#include "State_Base.h"
#include "../UI/Button.h"
#include "../Tools/FadeManager.h"

const sf::Vector2f button_size(155, 40);
const int button_spacing(12);

namespace State
{
	class Main_menu : public State_Base
	{
	public:
		Main_menu(Application& app);

		void update(float dt) override;
		void input(sf::Event& event) override;
		void handleSignal(Signal signal) override;
		void render() override;

	private:

		enum class Mode
		{
			Active,
			FadeOut
		};

		void onWindowResize() override;

		Mode m_mode;
		FadeManager m_fade;
		std::vector<Button> m_buttons;
		sf::RectangleShape m_background;
	};
}
