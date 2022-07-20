#pragma once
#include <SFML/Graphics.hpp>

class Application;

class Statistics {
   public:
    Statistics(Application& app);

    void update(float delta);
    void render();

   private:
	void setString();

    float _updateTime;
    uint16_t _frames;
	uint16_t _curFps;

    sf::Text _text;

	// Remove
	Application* _application;
};
