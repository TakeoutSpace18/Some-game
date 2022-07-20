#pragma once
#include <SFML/Graphics.hpp>

class Window {
   public:
    static void init();

    static void draw(sf::Drawable& obj, const sf::RenderStates& states = sf::RenderStates::Default);
    static void display();
    static void clear();
    static uint32_t currentDrawCallsAmount();

    static void toggleFullscreen();
    static bool isOpen();
    static void close();

    static sf::Vector2f getSize();
    static sf::Vector2f setSize(const sf::Vector2f& size);

    static void setView(sf::View view);
    static const sf::View& getDefaultView();

    static bool pollEvent(sf::Event& event);

    static sf::Vector2i getMousePosition();

   private:
    static void createWindow();

    static inline sf::RenderWindow _renderWindow;
    static inline uint32_t _drawCallsCounter;
};