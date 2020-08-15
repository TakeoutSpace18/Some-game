#pragma once
#include "State_Base.h"
#include "../Tools/FadeManager.h"

namespace State
{
	class Splash_screen : public State_Base
	{
	public:
		Splash_screen(Application& app);

		void update(float dt) override;
		void input(sf::Event& event) override;
		void handleSignal(Signal signal) override;
		void render() override;
	private:
		void onWindowResize() override;

		enum class Mode
		{
			Waiting,
			FadeIn,
			FadeOut
		};

		Mode m_mode;
		FadeManager m_fade;
		sf::Sprite m_logo;
		sf::RectangleShape m_background;
	};
}
