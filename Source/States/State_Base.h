#pragma once
#include <SFML/Graphics.hpp>

#include "../Signal.hpp"

class Application;

namespace State
{
	class State_Base
	{
	public:
		State_Base(Application& app);

		virtual ~State_Base()
		{
		};

		virtual void update(float dt) = 0;
		virtual void input(sf::Event& event) = 0;
		virtual void handleSignal(Signal signal) = 0;
		virtual void render() = 0;


		void setViewSize(sf::View);
		// вызывается при изменении размера окна. Переопределить при особом управлении камерой.
	private:
		virtual void onWindowResize() = 0;
	protected:
		Application* m_p_application;
	};
}
