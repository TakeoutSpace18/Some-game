#pragma once
#include <SFML/Graphics.hpp>

class Application;
namespace State
{
	class State_Base
	{
	public:
		State_Base(Application& app);
		virtual ~State_Base() {};

		virtual void update (sf::Time& dt)       = 0;
		virtual void input  (sf::Event& event)   = 0;
		virtual void render ()                   = 0;

		
		void setViewSize(sf::View);   // ���������� ��� ��������� ������� ����. �������������� ��� ������ ���������� �������.
	private:
		virtual void onWindowResize() = 0;
	protected:
		Application* m_p_application;
	};
}