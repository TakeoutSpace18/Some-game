#pragma once
#include <SFML/Graphics.hpp>

#include "../Signal.hpp"

class Application;

namespace State {

class Base {
   public:
    Base(Application& app);

    virtual ~Base(){};

    virtual void update(float dt) = 0;
    virtual void input(sf::Event& event) = 0;
    virtual void handleSignal(Signal signal) = 0;
    virtual void render() = 0;

    void setViewSize(sf::View);
    // Is called on window resize event. Overrive if camera is specially
    // controlled
   private:
    virtual void onWindowResize() = 0;

   protected:
    Application* _application;
};
}