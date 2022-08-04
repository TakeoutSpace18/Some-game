#pragma once
#include <SFML/Graphics.hpp>

#include "Signal.hpp"

class Application;

namespace State {

class Base {
   public:
    Base(Application& app);

    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual void handleEvents(const sf::Event& event) = 0;
    virtual void handleSignal(Signal signal) = 0;

    virtual void resize(sf::Vector2f newSize) = 0;

   protected:
    Application* _application;
};

}  // namespace State