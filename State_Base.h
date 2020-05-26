#pragma once
#include <SFML/Graphics.hpp>

class Application;

class State_Base
{
public:
	State_Base(Application& app);
	virtual ~State_Base() {};

	virtual void update (sf::Time& dt)       = 0;
	virtual void input  (sf::Event& event)   = 0;
	virtual void render ()                   = 0;

protected:
	Application* m_p_application;
};

